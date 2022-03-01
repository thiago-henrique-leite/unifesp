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
#include <pthread.h>

#define REQUEST_MAX_SIZE 1000
#define BLOCK_LENGTH 5000

#define GET_REQUEST "GET"

#define SUCCESS_STATUS_GET "[Success#Method] Método GET OK\n"
#define SUCCESS_STATUS_FILE "[Success#File] Arquivo encontrado e aberto com sucesso!\n"
#define SUCCESS_STATUS_POST "[Success#Method] Método POST OK\n"
#define ERROR_STATUS_METHOD "[Error#Method] Método inválido ou não implementado!\n"
#define ERROR_STATUS_FILE "[Error#File] Arquivo não encontrado ou não pode ser aberto!\n"

struct request_t {
    char file[256], method[128];
};

struct thread_args_t {
    struct sockaddr_in caddr;
    int sc;
};

typedef struct thread_args_t thread_args_t;
typedef struct request_t request_t;

void get_request(request_t *request, char *request_string) {
    bzero(request, sizeof(request_t));

    sscanf(request_string, "%s %s", request->method, request->file);
}

void send_file(int sock_fd, request_t request) {
   int fd, nr;

   unsigned char file_buffer[BLOCK_LENGTH];
   
   fd = open(request.file, O_RDONLY, S_IRUSR);
   
   if(fd == -1) {
        perror("open()");
        send(sock_fd, ERROR_STATUS_FILE,
        strlen(ERROR_STATUS_FILE), 0);
        return;
   }

   send(sock_fd, SUCCESS_STATUS_FILE, strlen(SUCCESS_STATUS_FILE), 0);
   
   do {
        bzero(file_buffer, BLOCK_LENGTH);
        nr = read(fd, file_buffer, BLOCK_LENGTH);

        if(nr > 0)
            send(sock_fd, file_buffer, nr, 0);
   } while(nr > 0);

   close(fd);
}

void proc_request(int sock_fd, request_t request) {
    if(strcmp(request.method, GET_REQUEST) == 0) {
        send(sock_fd, SUCCESS_STATUS_GET, strlen(SUCCESS_STATUS_GET), 0);
        send_file(sock_fd, request);
    } else {
        send(sock_fd, ERROR_STATUS_METHOD, strlen(ERROR_STATUS_METHOD), 0);
    }
}

void *client_thread(void *arguments)
{
    thread_args_t params = *(thread_args_t *) arguments;

    char request[REQUEST_MAX_SIZE];

    request_t req;

    if(params.sc == -1) {
        perror("accept");
    }

    printf("\nConectado com cliente %s:%d\n", inet_ntoa(params.caddr.sin_addr), ntohs(params.caddr.sin_port));

    bzero(request, REQUEST_MAX_SIZE);
    
    int nr = recv(params.sc, request, REQUEST_MAX_SIZE, 0);
    
    if(nr > 0) {
        get_request(&req, request);
        printf("\nMétodo: %s\nArquivo: %s\n", req.method, req.file);
        proc_request(params.sc, req);
    }

    close(params.sc);

    return 0;
}

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Modo de executar o programa: %s <porta>\n", argv[0]);
        return 0;
    }

    int sl = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if(sl == -1) {
        perror("socket()");
        return 0;
    }

    struct sockaddr_in saddr;
    
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(sl, (struct sockaddr*) &saddr, sizeof(struct sockaddr_in)) == -1) {
        perror("bind()");
        return 0;
    }

    if(listen(sl, 1000) == -1) {
        perror("listen()");
        return 0;
    }

    struct sockaddr_in caddr;

    int addr_len;
    int sc;
    
    while(1) {
        addr_len = sizeof(struct sockaddr_in);

        sc = accept(sl, (struct sockaddr*) &caddr, (socklen_t *) &addr_len);

        pthread_t client;

        thread_args_t params;

        params.sc = sc;
        params.caddr = caddr;

        pthread_create(&client, NULL, client_thread, (void *) &params);
    }
    pthread_exit((void *) NULL);
    close(sl);
    return 0;
}