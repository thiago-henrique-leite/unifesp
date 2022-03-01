#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_REQ_LEN 1000
#define FBLOCK_SIZE 4000
#define REQ_GET "GET"
#define COD_OK_GET "OK-0 method GET OK\n"
#define COD_OK_FILE "OK-1 file open successfully\n"
#define COD_ERROR_METHOD "ERROR-0 method not supported\n"
#define COD_ERROR_FILE "ERROR-1 file could not be open\n"

struct req_t{
    char method[128];
    char filename[256];
};
typedef struct req_t req_t;

void get_request(req_t *r, char *rstr){
    bzero(r, sizeof(req_t));
    sscanf(rstr, "%s %s", r->method, r->filename);

}

void send_file(int sockfd, req_t r){
   int fd, nr;
   unsigned char fbuff[FBLOCK_SIZE];
   fd = open(r.filename, O_RDONLY, S_IRUSR);
   if(fd == -1){
       perror("open");
       send(sockfd, COD_ERROR_FILE,
            strlen(COD_ERROR_FILE), 0);
        return;
   }
   send(sockfd, COD_OK_FILE, strlen(COD_OK_FILE), 0);
   do{
       bzero(fbuff, FBLOCK_SIZE);
       nr = read(fd, fbuff, FBLOCK_SIZE);
       if(nr > 0){
           send(sockfd, fbuff, nr, 0);
       }
   }while(nr > 0);
   close(fd);
}

void proc_request(int sockfd, req_t r){
   if(strcmp(r.method, REQ_GET) == 0){
       send(sockfd, COD_OK_GET,
            strlen(COD_OK_GET), 0);
        send_file(sockfd, r);
   }else{
       send(sockfd, COD_ERROR_METHOD,
            strlen(COD_ERROR_METHOD), 0);
   }
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Uso: %s <porta>\n", argv[0]);
        return 0;
    }
    int sl;
    sl = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sl == -1){
        perror("socket");
        return 0;
    }
    struct sockaddr_in saddr;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sl, (struct sockaddr *)&saddr,
            sizeof(struct sockaddr_in)) == -1){
                perror("bind");
                return 0;
    }
    if(listen(sl, 1000) == -1){
        perror("listen");
        return 0;
    }

    struct sockaddr_in caddr;
    int addr_len;
    int sc, nr;
    char request[MAX_REQ_LEN];
    req_t req;
    while(1){
        addr_len = sizeof(struct sockaddr_in);
        sc = accept(sl, (struct sockaddr*)&caddr,
                    (socklen_t *)&addr_len);
        if(sc == -1){
            perror("accept");
            continue;
        }
        printf("Conectado com cliente %s:%d\n",
                inet_ntoa(caddr.sin_addr),
                ntohs(caddr.sin_port));
        bzero(request, MAX_REQ_LEN);
        nr = recv(sc, request, MAX_REQ_LEN, 0);
        if(nr > 0){
            get_request(&req, request);
            printf("method: %s\n filename: %s\n", req.method, req.filename);
            proc_request(sc, req);
        }
        close(sc);
    }
    close(sl);
    return 0;
}
