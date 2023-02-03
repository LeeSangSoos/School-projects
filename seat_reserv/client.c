#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>

typedef struct _query {
    int user;
    int action;
    int data;
} query;

int main(int argc, char* argv[])
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    int rd, sn, wn;
    FILE* fd;
    char buf[100];
    uint32_t rt, data;
    int check = 1;
    query q;
    struct hostent* h;
    char* host = argv[1];
    char* pos = NULL;
    char* a;

    if (argc == 3) {
        /* Insert your code for terminal input */
    }
    else if (argc == 4) {
        fd = fopen(argv[3], "r");
        /* Insert your code for file input */
    }
    else {
        printf("Follow the input rule below\n");
        printf("==================================================================\n");
        printf("argv[1]: server address, argv[2]: port number\n");
        printf("or\n");
        printf("argv[1]: server address, argv[2]: port number, argv[3]: input file\n");
        printf("==================================================================\n");
        exit(1);
    }
    if ((h = gethostbyname(host)) == NULL) {
        printf("invalid hostname %s\n", host);
        exit(2);
    }

    memset((char*)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    memcpy((char*)&server_addr.sin_addr.s_addr, (char*)h->h_addr, h->h_length);

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        printf("Connection failed\n");
        exit(1);
    }

    char* a1;
    char* b1;
    char* c1;
    if (argc == 3) {
        while (1) {
            if ((wn = read(0, buf, 100)) > 0) {
                buf[wn - 1] = '\0';
                errno = 0;
                if (buf[0] == ' ') {
                    printf("invalid query\n");
                    check = 0;
                }
                else {
                    if ((a1 = strpbrk(buf, " ")) != NULL) {
                        if (a1[1] == ' ') {
                            printf("invalid query\n");
                            check = 0;
                        }
                        else {
                            a1++;
                            if ((b1 = strpbrk(a1, " ")) != NULL) {
                                if (b1[1] == ' ') {
                                    printf("invalid query\n");
                                    check = 0;
                                }
                                else {
                                    b1++;
                                    if ((c1 = strpbrk(b1, " ")) != NULL) {
                                        printf("invalid query\n");
                                        check = 0;
                                    }
                                    else {
                                        a = strtok(buf, " ");
                                        if (a != NULL) {
                                            q.user = strtol(a, &pos, 10);
                                            if (errno != 0) {
                                                printf("invalid query\n");
                                                check = 0;
                                                errno = 0;
                                            }
                                            else if (q.user < 0 || q.user > 1023) {
                                                printf("invalid query\n");
                                                check = 0;
                                            }
                                            else {
                                                a = strtok(NULL, " ");
                                                if (a != NULL) {
                                                    q.action = strtol(a, &pos, 10);
                                                    if (errno != 0) {
                                                        printf("invalid query\n");
                                                        check = 0;
                                                        errno = 0;
                                                    }
                                                    else if (q.action < 0 || q.action>5) {
                                                        printf("invalid query\n");
                                                        check = 0;
                                                    }
                                                    else {
                                                        a = strtok(NULL, " ");
                                                        if (a != NULL) {
                                                            q.data = strtol(a, &pos, 10);
                                                            if (errno != 0) {
                                                                printf("invalid query\n");
                                                                check = 0;
                                                                errno = 0;
                                                            }
                                                            else {
                                                                a = strtok(NULL, " ");
                                                                if (a != NULL) {
                                                                    printf("invalid query\n");
                                                                    check = 0;
                                                                }
                                                            }
                                                            if (q.action == 5 || q.action == 3)
                                                                q.data = -1;
                                                        }
                                                        else {
                                                            printf("invalid query\n");
                                                            check = 0;
                                                        }
                                                    }
                                                }
                                                else {
                                                    printf("invalid query\n");
                                                    check = 0;
                                                }
                                            }
                                        }
                                        else {
                                            printf("invalid query\n");
                                            check = 0;
                                        }
                                        if (q.action == 0 && check != 0) {
                                            if (q.user == 0 && q.data == 0) {

                                            }
                                            else {
                                                printf("invalid query\n");
                                                check = 0;
                                            }
                                        }
                                    }
                                }
                            }
                            else {
                                printf("invalid query\n");
                                check = 0;
                            }
                        }
                    }
                    else {
                        printf("invalid query\n");
                        check = 0;
                    }
                }
                if (check == 1) {
                    sn = send(client_socket, (struct query*)&q, sizeof(q), 0);
                    if (q.action == 1) {
                        if ((wn = read(client_socket, &data, sizeof(data))) > 0) {
                            rt = ntohl(data);
                            if (rt == 1) {
                                printf("Login success\n");
                            }
                            else if (rt == -1) {
                                printf("Login failed\n");
                            }
                        }
                    }
                    else if (q.action == 2) {
                        if (wn = read(client_socket, &data, sizeof(data)) > 0) {
                            rt = ntohl(data);
                            if (rt == -1) {
                                printf("Reservation failed\n");
                            }
                            else if (rt == q.data) {
                                printf("Seat %d is reserved\n", q.data);
                            }
                        }
                    }
                    else if (q.action == 3) {
                        if (wn = read(client_socket, &data, sizeof(data)) > 0) {
                            rt = ntohl(data);
                            if (rt == -1) {
                                printf("Reservation check failed\n");
                            }
                            else {
                                int* arr = malloc(256 * sizeof(*arr));
                                if (read(client_socket, arr, 256 * sizeof(int)) > 0) {
                                    printf("Reservation: ");
                                    for (int i = 0; i < rt; i++) {
                                        if (arr[i] == 1) {
                                            printf("%d, ", i);
                                        }
                                    }
                                    printf("%d\n",rt);
                                }
                                free(arr);
                            }
                        }
                    }
                    else if (q.action == 4) {
                        if (wn = read(client_socket, &data, sizeof(data)) > 0) {
                            rt = ntohl(data);
                            if (rt == -1) {
                                printf("Cancel failed\n");
                            }
                            else if (rt == q.data) {
                                printf("Seat %d is canceled\n", q.data);
                            }
                        }
                    }
                    else if (q.action == 5) {
                        if (wn = read(client_socket, &data, sizeof(data)) > 0) {
                            rt = ntohl(data);
                            if (rt == 1) {
                                printf("Logout success\n");
                            }
                            else if (rt == -1) {
                                printf("Logout failed\n");
                            }
                        }
                    }
                    else if (q.action == 0) {
                        if ((wn = read(client_socket, &data, sizeof(data))) > 0) {
                            rt = ntohl(data);
                            if (rt == 256) {
                                break;
                            }
                        }
                    }
                    else {
                        printf("invalid query\n");
                    }
                }
                check = 1;
            }
        }
    }
    else if (argc == 4) {
        while (1) {
            fgets(buf, 100, fd);
            buf[strcspn(buf, "\n")] = '\0';
            errno = 0;
            if (buf[0] == ' ') {
                printf("invalid query\n");
                check = 0;
            }
            else {
                if ((a1 = strpbrk(buf, " ")) != NULL) {
                    if (a1[1] == ' ') {
                        printf("invalid query\n");
                        check = 0;
                    }
                    else {
                        a1++;
                        if ((b1 = strpbrk(a1, " ")) != NULL) {
                            if (b1[1] == ' ') {
                                printf("invalid query\n");
                                check = 0;
                            }
                            else {
                                b1++;
                                if ((c1 = strpbrk(b1, " ")) != NULL) {
                                    printf("invalid query\n");
                                    check = 0;
                                }
                                else {
                                    a = strtok(buf, " ");
                                    if (a != NULL) {
                                        q.user = strtol(a, &pos, 10);
                                        if (errno != 0) {
                                            printf("invalid query\n");
                                            check = 0;
                                            errno = 0;
                                        }
                                        else if (q.user < 0 || q.user > 1023) {
                                            printf("invalid query\n");
                                            check = 0;
                                        }
                                        else {
                                            a = strtok(NULL, " ");
                                            if (a != NULL) {
                                                q.action = strtol(a, &pos, 10);
                                                if (errno != 0) {
                                                    printf("invalid query\n");
                                                    check = 0;
                                                    errno = 0;
                                                }
                                                else if (q.action < 0 || q.action>5) {
                                                    printf("invalid query\n");
                                                    check = 0;
                                                }
                                                else {
                                                    a = strtok(NULL, " ");
                                                    if (a != NULL) {
                                                        q.data = strtol(a, &pos, 10);
                                                        if (errno != 0) {
                                                            printf("invalid query\n");
                                                            check = 0;
                                                            errno = 0;
                                                        }
                                                        else {
                                                            a = strtok(NULL, " ");
                                                            if (a != NULL) {
                                                                printf("invalid query\n");
                                                                check = 0;
                                                            }
                                                        }
                                                        if (q.action == 5 || q.action == 3)
                                                            q.data = -1;
                                                    }
                                                    else {
                                                        printf("invalid query\n");
                                                        check = 0;
                                                    }
                                                }
                                            }
                                            else {
                                                printf("invalid query\n");
                                                check = 0;
                                            }
                                        }
                                    }
                                    else {
                                        printf("invalid query\n");
                                        check = 0;
                                    }
                                    if (q.action == 0 && check != 0) {
                                        if (q.user == 0 && q.data == 0) {

                                        }
                                        else {
                                            printf("invalid query\n");
                                            check = 0;
                                        }
                                    }
                                }
                            }
                        }
                        else {
                            printf("invalid query\n");
                            check = 0;
                        }
                    }
                }
                else {
                    printf("invalid query\n");
                    check = 0;
                }
            }
            if (check == 1) {
                sn = send(client_socket, (struct _query*)&q, sizeof(q), 0);
                if (q.action == 1) {
                    if ((wn = read(client_socket, &data, sizeof(data))) > 0) {
                        rt = ntohl(data);
                        if (rt == 1) {
                            printf("Login success\n");
                        }
                        else if (rt == -1) {
                            printf("Login failed\n");
                        }
                    }
                }
                else if (q.action == 2) {
                    if (wn = read(client_socket, &data, sizeof(data)) > 0) {
                        rt = ntohl(data);
                        if (rt == -1) {
                            printf("Reservation failed\n");
                        }
                        else if (rt == q.data) {
                            printf("Seat %d is reserved\n", q.data);
                        }
                    }
                }
                else if (q.action == 3) {
                    if (wn = read(client_socket, &data, sizeof(data)) > 0) {
                        rt = ntohl(data);
                        if (rt == -1) {
                            printf("Reservation check failed\n");
                        }
                        else {
                            int* arr = malloc(256 * sizeof(*arr));
                            if (read(client_socket, arr, 256 * sizeof(int)) > 0) {
                                printf("Reservation: ");
                                for (int i = 0; i < rt; i++) {
                                    if (arr[i] == 1) {
                                        printf("%d, ", i);
                                    }
                                }
                                printf("%d\n", rt);
                            }
                            free(arr);
                        }
                    }
                }
                else if (q.action == 4) {
                    if (wn = read(client_socket, &data, sizeof(data)) > 0) {
                        rt = ntohl(data);
                        if (rt == -1) {
                            printf("Cancel failed\n");
                        }
                        else if (rt == q.data) {
                            printf("Seat %d is canceled\n", q.data);
                        }
                    }
                }
                else if (q.action == 5) {
                    if (wn = read(client_socket, &data, sizeof(data)) > 0) {
                        rt = ntohl(data);
                        if (rt == 1) {
                            printf("Logout success\n");
                        }
                        else if (rt == -1) {
                            printf("Logout failed\n");
                        }
                    }
                }
                else if (q.action == 0) {
                    if ((wn = read(client_socket, &data, sizeof(data))) > 0) {
                        rt = ntohl(data);
                        if (rt == 256) {
                            break;
                        }
                    }
                }
                else {
                    printf("invalid query\n");
                }
            }
            check = 1;
            if (feof(fd)) {
                q.user = 0;
                q.action = 0;
                q.data = 0;
                sn = send(client_socket, (struct _query*)&q, sizeof(q), 0);
                if ((wn = read(client_socket, &data, sizeof(data))) > 0) {
                    rt = ntohl(data);
                    if (rt == 256) {
                        break;
                    }
                }
            }
        }
        fclose(fd);
    }
    close(client_socket);
    return 0;
}
