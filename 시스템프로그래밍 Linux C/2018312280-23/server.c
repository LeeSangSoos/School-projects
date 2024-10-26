#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>
#include <pthread.h>
#include <stdio.h>

int seat[256];
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

typedef struct _query {
    int user;
    int action;
    int data;
} query;

int* upass;
int* ulog;

void* thread_func(void* arg) {
    int connfd = *((int*)arg);
    pthread_detach(pthread_self());
    free(arg);
    query q;
    uint32_t n, tmp;
    int use = -1;

    while (recv(connfd, (struct _query*)&q, sizeof(query), 0) > 0) {
        pthread_mutex_lock(&m);
        if (q.action == 1) {
            if (use == -1) {
                if (upass[q.user] == -1) {
                    //new user
                    n = 1;
                    tmp = htonl(n);
                    upass[q.user] = q.data;
                    ulog[q.user] = 1;
                    write(connfd, &tmp, sizeof(tmp));
                    use = q.user;
                }
                else {
                    //user exists
                    if (ulog[q.user] == 1) {
                        n = -1;
                        tmp = htonl(n);
                        write(connfd, &tmp, sizeof(tmp));
                    }
                    else {
                        if (upass[q.user] == q.data) {
                            ulog[q.user] = 1;
                            n = 1;
                            tmp = htonl(n);
                            write(connfd, &tmp, sizeof(tmp));
                            use = q.user;
                        }
                        else {
                            n = -1;
                            tmp = htonl(n);
                            write(connfd, &tmp, sizeof(tmp));
                        }
                    }
                }
            }
            else {
                n = -1;
                tmp = htonl(n);
                write(connfd, &tmp, sizeof(tmp));
            }
        }
        else if (q.action == 0) {
            if (q.user == 0 && q.data == 0) {
                ulog[use] = 0;
                use = -1;
                n = 256;
                tmp = htonl(n);
                write(connfd, &tmp, sizeof(tmp));
                break;
            }
        }
        else {
            if (ulog[q.user] == 1 && (q.user == use)) {
                if (q.action == 2) {
                    if (q.data < 0 || q.data>255) {
                        n = -1;
                        tmp = htonl(n);
                        write(connfd, &tmp, sizeof(tmp));
                    }
                    else if (seat[q.data] != -1) {
                        n = -1;
                        tmp = htonl(n);
                        write(connfd, &tmp, sizeof(tmp));
                    }
                    else {
                        seat[q.data] = q.user;
                        n = q.data;
                        tmp = htonl(n);
                        write(connfd, &tmp, sizeof(tmp));
                    }
                }
                else if (q.action == 3) {
                    int len = 0;
                    int* arr = malloc(256 * sizeof(*arr));
                    for (int i = 0; i < 256; i++) {
                        if (seat[i] == q.user) {
                            arr[len] = i;
                            len++;
                        }
                    }
                    if (len == 0) {
                        n = -1;
                        tmp = htonl(n);
                        write(connfd, &tmp, sizeof(tmp));
                    }
                    else {
                        n = len;
                        tmp = htonl(n);
                        write(connfd, &tmp, sizeof(tmp));
                        write(connfd, arr, len * sizeof(int));
                    }
                    free(arr);
                }
                else if (q.action == 4) {
                    int len = 0;
                    if (q.data < 0 || q.data>255) {
                        n = -1;
                        tmp = htonl(n);
                        write(connfd, &tmp, sizeof(tmp));
                    }
                    else {
                        for (int i = 0; i < 256; i++) {
                            if (seat[i] == q.user) {
                                len = 1;
                                break;
                            }
                        }
                        if (len == 1) {
                            if (seat[q.data] == -1) {
                                n = -1;
                                tmp = htonl(n);
                                write(connfd, &tmp, sizeof(tmp));
                            }
                            else if (seat[q.data] != q.user) {
                                n = -1;
                                tmp = htonl(n);
                                write(connfd, &tmp, sizeof(tmp));
                            }
                            else {
                                seat[q.data] = -1;
                                n = q.data;
                                tmp = htonl(n);
                                write(connfd, &tmp, sizeof(tmp));
                            }
                        }
                        else if (len == 0) {
                            n = -1;
                            tmp = htonl(n);
                            write(connfd, &tmp, sizeof(tmp));
                        }
                    }
                }
                else if (q.action == 5) {
                    if (q.user == use) {
                        ulog[q.user] = 0;
                        use = -1;
                        n = 1;
                        tmp = htonl(n);
                        write(connfd, &tmp, sizeof(tmp));
                    }
                    else {
                        n = -1;
                        tmp = htonl(n);
                        write(connfd, &tmp, sizeof(tmp));
                    }
                }
            }
            else if (ulog[q.user] == 0 || (q.user != use)) {
                n = -1;
                tmp = htonl(n);
                write(connfd, &tmp, sizeof(tmp));
            }
            else {
                n = -1;
                tmp = htonl(n);
                write(connfd, &tmp, sizeof(tmp));
            }
        }
        pthread_mutex_unlock(&m);
    }

    pthread_mutex_unlock(&m);
    close(connfd);
}

int main(int argc, char* argv[])
{
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr, caddr;
    upass = malloc(1050 * sizeof(int));
    ulog = malloc(1050 * sizeof(int));
    int caddrlen = sizeof(caddr);
    for (int i = 0; i < 1050; i++) {
        ulog[i] = 0;
        upass[i] = -1;
    }
    for (int i = 0; i < 256; i++) {
        seat[i] = -1;
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[1]));
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

    if (bind(listenfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
        return 0;

    if (listen(listenfd, 1024) < 0)
        return 0;

    int* connfdp;
    while (1) {
        connfdp = (int*)malloc(sizeof(int));
        pthread_t tid;

        if ((connfdp[0] = accept(listenfd, (struct sockaddr*)&caddr, (socklen_t*)&caddrlen)) < 0) {
            printf("accept() failed\n");
            free(connfdp);
            continue;
        }

        pthread_create(&tid, NULL, thread_func, connfdp);

    }

    free(upass);
    free(ulog);
    return 0;
}