#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLINE 80

int main (int argc, char *argv[]) {

    int n, listenfd, connfd, caddrlen;
    struct hostent *h;
    struct sockaddr_in saddr, caddr;
    char buf[MAXLINE];
    int port = atoi(argv[1]);

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket() failed.\n");
        exit(1);
    }

    memset((char *)&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    if (bind(listenfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        printf("bind() failed.\n");
        exit(2);
    }

    if (listen(listenfd, 5) < 0) {
        printf("listen() failed.\n");
        exit(3);
    }

    fd_set readset, copyset;
    FD_ZERO(&readset);  /* initialize socket set */
    FD_SET(listenfd, &readset);
    int fdmax = listenfd, fdnum;
    char** names = malloc(256 * sizeof(*names));
    int users=0;
    char* nums;
    char says[100];
    memset(buf, 0, sizeof buf);
    memset(says, 0, sizeof says);
    while (1) {
        copyset = readset;
        /*
        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        */
        if((fdnum = select(fdmax + 1, &copyset, NULL, NULL, NULL)) < 0 ) {
            printf("select() failed.\n");
            exit(4);
        }
        /*
        if (fdnum == 0) {
            printf("Time out.\n");
            continue;
        }
        */
        for (int i = 0; i < fdmax + 1; i++) {
            if (FD_ISSET(i, &copyset)) {
                if (i == listenfd) {
                    caddrlen = sizeof(caddr);
                    if ((connfd = accept(listenfd, (struct sockaddr *)&caddr,
                        (socklen_t *)&caddrlen)) < 0) {
                        printf ("accept() failed.\n");
                        continue;
                    }

                    FD_SET(connfd, &readset);

                    if (fdmax < connfd)
                        fdmax = connfd;
                    users++;
                }
                else {
                    if ((n = read(i, buf, MAXLINE)) > 0) {
                        if (names[i]==NULL) {
                            names[i] = malloc(15 * sizeof(**names));
                            buf[strlen(buf) - 1] = ' ';
                            strcpy(names[i], buf);
                            sprintf(buf, "%sjoined. %d current users\n", names[i], users);
                            int n = strlen(buf);
                            for (int j = listenfd + 1; j <= fdmax; j++) {
                                if (j != i) {
                                    write(j, buf, n);
                                }
                            }
                        }
                        else {
                            if (strcmp(buf, "quit\n")==0) {
                                users--;
                                sprintf(buf, "%sleaved. %d current users\n", names[i], users);
                                int n = strlen(buf);
                                for (int j = listenfd+1; j <= fdmax; j++) {
                                    if (j != i) {
                                        write(j, buf, n);
                                    }
                                }
                                FD_CLR(i, &readset);
                                fflush(stdout);
                                close(i);
                            }
                            else {
                                printf("got %d bytes from client.\n", n);
                                fflush(stdout);
                                sprintf(says, "%s: %s", names[i], buf);
                                int n = strlen(says);
                                for (int j = listenfd + 1; j <= fdmax; j++) {
                                    if (j != i) {
                                        write(j, says, n);
                                    }
                                }
                            }
                        }
                        memset(buf, 0, sizeof buf);
                        memset(says, 0, sizeof says);
                    }
                    else {
                        FD_CLR(i, &readset);
                        printf("connection terminated.\n");
                        close(i);
                    }
                }

            }
           
        }

    }
    free(names);
    return 0;

}

