#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 80

int read_with_timeout(int fd, char* buf, int buflen, int timeouts)
{
    int n = 0;
    struct    timeval  timeout;
    fd_set  	readFds;

    timeout.tv_sec = 0;
    timeout.tv_usec = timeouts * 1000;

    FD_ZERO(&readFds);
    FD_SET(fd, &readFds);
    select(fd + 1, &readFds, NULL, NULL, &timeout);

    if (FD_ISSET(fd, &readFds))
    {
        n = read(fd, buf, buflen);
    }

    return n;
}

int main (int argc, char *argv[]) {
    int n, cfd;
    struct hostent *h;
    struct sockaddr_in saddr;
    char buf[MAXLINE];
    char *host = argv[1];
    int port = atoi(argv[2]);
    
    if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket() failed.\n"); 
        exit(1);
    }
    if ((h = gethostbyname(host)) == NULL) {
        printf("invalid hostname %s\n", host); 
        exit(2);
    }   
    memset((char *)&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *)&saddr.sin_addr.s_addr, (char *)h->h_addr, h->h_length);
    saddr.sin_port = htons(port);

    if (connect(cfd,(struct sockaddr *)&saddr,sizeof(saddr)) < 0) {
        printf("connect() failed.\n");
        exit(3);
    }
    printf("Insert your name : ");
    fflush(stdout);
    while (1) {
        memset(buf, 0, MAXLINE);
        if ((n = read_with_timeout(0, buf, MAXLINE, 500)) > 0) {
            if (!strcmp(buf, "quit\n")) {
                write(cfd, buf, n);
                break;
            }
            write(cfd, buf, n);
        }
        n = read_with_timeout(cfd, buf, MAXLINE, 500);
        write(1, buf, n);
    }
    close(cfd);
    return 0;
}