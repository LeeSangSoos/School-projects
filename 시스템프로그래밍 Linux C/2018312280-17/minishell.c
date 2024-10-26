#define MAXARGS   128
#define MAXLINE	  256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void eval(char* cmdline);
int parseline(char* buf, char** argv);
void command(char** argv);
int make_tokens(char* cmd, int i, char* arg[], char* target);
void make_tokens2(char* cmd, char* arg[], char* arg2[], char* target);
void make_tokens3(char* cmd, char* arg[], char* arg2, char* target);
void make_tokens4(char* cmd, char arg[], char arg2[], char* target);
void cd_cmd(char* dir);
void exit_cmd(int num);
pid_t pid;           /* Process id */
pid_t pids[200];
void sigstp_hand(int sig);
char head_p[MAXARGS];
char tail_p[MAXARGS];
char cat_p[MAXARGS];
char cp_p[MAXARGS];
char mv_p[MAXARGS];
char rm_p[MAXARGS];
char pwd_p[MAXARGS];

int main()
{
    char cmdline[MAXLINE]; /* Command line */
    char* ret;
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, sigstp_hand);
    realpath("head", head_p);
    realpath("tail", tail_p);
    realpath("cat", cat_p);
    realpath("cp", cp_p);
    realpath("mv", mv_p);
    realpath("rm", rm_p);
    realpath("pwd", pwd_p);
    while (1) {
        /* Read */
        printf("mini> ");
        ret = fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin) || ret == NULL)
            exit(0);
        
        //cd
        if (strstr(cmdline, "cd") != NULL) {
            char** ar = malloc(MAXARGS * sizeof(*ar));
            parseline(cmdline, ar);
            if (strcmp(ar[0], "cd") == 0) {
                if (ar[1] != NULL) {
                    int len = strlen(ar[1]);
                    if (ar[1][len - 1] == '\n')
                        ar[1][len - 1] = '\0';
                    if (chdir(ar[1]) < 0) {
                        perror("cd");
                    }
                }
                free(ar);
            }
            else {
                free(ar);
                eval(cmdline);
            }
        }
        else {
            //exit
            if (strstr(cmdline, "exit") != NULL) {
                char** ar = malloc(MAXARGS * sizeof(*ar));
                parseline(cmdline, ar);
                if (strcmp(ar[0], "exit") == 0) {
                    fprintf(stderr, "exit\n");
                    if (ar[1] != NULL) {
                        char* pos = NULL;
                        int num = strtol(ar[1], &pos, 10);
                        free(ar);
                        exit(num);
                    }
                    free(ar);
                    exit(0);
                }
                free(ar);
            }
            eval(cmdline);
        }
    }
}


void eval(char* cmdline){
    char buf[MAXLINE];   /* Holds modified command line */
    int bg=0;              /* Should the job run in bg or fg? */

    strcpy(buf, cmdline);
    /* Ignore empty lines */
    if (buf[0] == '\0')
        return;

    if ((pid = fork()) == 0) {
        setpgid(pid, 0);
        //printf("parent1: %ld in %ld\n", (long)getpid(), (long)getpgid(pid));
        char** argf = malloc(MAXARGS * sizeof(*argf));
        int a;
        if (strchr(buf, '|') != NULL) {
            a = make_tokens(buf, 0, argf, "|");
            int** fd = malloc((a - 1) * sizeof(*fd));
            for (int i = 0; i < a - 1; i++)
                fd[i] = malloc(2 * sizeof(**fd));

            for (int i = 0; i < a - 1; i++) {
                if (pipe(fd[i]) == -1) {
                    fprintf(stderr, "Error opening  pipe %d\n", i);
                }
            }

            if ((pids[0] = fork()) == 0) {
                //printf("child start: %ld in %ld\n", (long)getpid(), (long)getpgid(pid));
                close(fd[0][0]);
                for (int i = 1; i < a - 1; i++) {
                    close(fd[i][0]);
                    close(fd[i][1]);
                }
                if (strchr(argf[0], '<') != NULL) {
                    char** arg = malloc(MAXARGS * sizeof(*arg));
                    char** arg2 = malloc(MAXARGS * sizeof(*arg2));
                    make_tokens2(argf[0], arg, arg2, "<");
                    int fd1 = open(arg2[0], O_RDONLY, 00777);
                    if (fd1 < 0) {
                        perror("mini");
                        close(fd[0][1]);
                    }
                    else if (fd1 != -1) {
                        dup2(fd1, 0);
                        dup2(fd[0][1], 1);
                        close(fd[0][1]);
                        command(arg);
                    }
                    close(fd1);
                    free(arg);
                    free(arg2);
                }
                else {
                    char** arg = malloc(MAXARGS * sizeof(*arg));
                    parseline(argf[0], arg);
                    dup2(fd[0][1], 1);
                    close(fd[0][1]);
                    command(arg);
                    free(arg);
                }
                exit(0);
            }
            for (int i = 1; i < a - 1; i++) {
                if ((pids[i] = fork()) < 0) {
                    perror("fork");
                }
                if (pids[i] == 0) {
                    //printf("child mid: %ld in %ld\n", (long)getpid(), (long)getpgid(pid));
                    for (int j = 0; j < i - 1; j++) {
                        close(fd[j][0]);
                        close(fd[j][1]);
                    }
                    close(fd[i - 1][1]);
                    close(fd[i][0]);
                    for (int j = i + 1; j < a - 1; j++) {
                        close(fd[j][0]);
                        close(fd[j][1]);
                    }
                    char** arg = malloc(MAXARGS * sizeof(*arg));
                    parseline(argf[i], arg);
                    dup2(fd[i - 1][0], 0);
                    close(fd[i - 1][0]);
                    dup2(fd[i][1], 1);
                    close(fd[i][1]);
                    command(arg);
                    free(arg);
                    exit(0);
                }
            }
            if ((pids[a - 1] = fork()) < 0) {
                perror("fork");
            }
            if (pids[a - 1] == 0) {
                //printf("child last: %ld in %ld\n", (long)getpid(), (long)getpgid(pid));
                close(fd[a - 2][1]);
                for (int i = 0; i < a - 2; i++) {
                    close(fd[i][0]);
                    close(fd[i][1]);
                }
                if (strstr(argf[a - 1], ">>") != NULL) {
                    char** arg = malloc(MAXARGS * sizeof(*arg));
                    char** arg2 = malloc(MAXARGS * sizeof(*arg2));
                    make_tokens2(argf[a - 1], arg, arg2, ">>");
                    int fd1 = open(arg2[0], O_WRONLY | O_APPEND, 00777);
                    if (fd1 < 0) {
                        perror("mini");
                        close(fd[a - 2][0]);
                    }
                    else if (fd1 != -1) {
                        dup2(fd1, 1);
                        dup2(fd[a - 2][0], 0);
                        close(fd[a - 2][0]);
                        command(arg);
                    }
                    close(fd1);
                    free(arg);
                    free(arg2);
                }
                else if (strchr(argf[a - 1], '>') != NULL) {
                    char** arg = malloc(MAXARGS * sizeof(*arg));
                    char** arg2 = malloc(MAXARGS * sizeof(*arg2));
                    make_tokens2(argf[a - 1], arg, arg2, ">");
                    int fd1 = open(arg2[0], O_WRONLY, 00777);
                    if (fd1 < 0) {
                        perror("mini");
                        close(fd[a - 2][0]);
                    }
                    else if (fd1 != -1) {
                        dup2(fd1, 1);
                        dup2(fd[a - 2][0], 0);
                        close(fd[a - 2][0]);
                        command(arg);
                    }
                    close(fd1);
                    free(arg);
                    free(arg2);
                }
                else {
                    char** arg = malloc(MAXARGS * sizeof(*arg));
                    parseline(argf[a - 1], arg);
                    dup2(fd[a - 2][0], 0);
                    close(fd[a - 2][0]);
                    command(arg);
                    free(arg);
                }
                exit(0);
            }
            free(argf);
            free(fd);
            pid_t wpid;
            int status;
            for (int i = 0; i < a - 1; i++) {
                close(fd[i][0]);
                close(fd[i][1]);
            }
            for (int i = 0; i < a; i++) {
                wpid = waitpid(pids[i], &status, WUNTRACED);
            }
        }
        else {
            if (strchr(buf, '<') != NULL) {
                if (strstr(buf, ">>") != NULL) {
                    char** arg = malloc(MAXARGS * sizeof(*arg));
                    char* arg2 = malloc(MAXARGS * sizeof(char));
                    char* arg3 = malloc(MAXARGS * sizeof(char));
                    char* arg4 = malloc(MAXARGS * sizeof(char));
                    make_tokens3(buf, arg, arg2, "<");
                    make_tokens4(arg2, arg3, arg4, ">>");
                    int fd1 = open(arg3, O_RDONLY, 00777);
                    if (fd1 == -1) {
                        perror("mini");
                    }
                    int fd2 = open(arg4, O_WRONLY | O_APPEND, 00777);
                    if (fd2 == -1) {
                        perror("mini");
                    }
                    if (fd1 != -1 && fd2 != -1) {
                        dup2(fd1, 0);
                        dup2(fd2, 1);
                        command(arg);
                    }
                    close(fd1);
                    close(fd2);
                    free(arg);
                    free(arg2);
                    free(arg3);
                    free(arg4);
                }
                else if (strchr(buf, '>') != NULL) {
                    char** arg = malloc(MAXARGS * sizeof(*arg));
                    char* arg2 = malloc(MAXARGS * sizeof(char));
                    char* arg3 = malloc(MAXARGS * sizeof(char)); char* arg4 = malloc(MAXARGS * sizeof(char));
                    make_tokens3(buf, arg, arg2, "<");
                    make_tokens4(arg2, arg3, arg4, ">");
                    int fd1 = open(arg3, O_RDONLY, 00777);
                    if (fd1 == -1) {
                        perror("mini");
                    }
                    int fd2 = open(arg4, O_WRONLY, 00777);
                    if (fd2 == -1) {
                        perror("mini");
                    }
                    if (fd1 != -1 && fd2 != -1) {
                        dup2(fd1, 0);
                        dup2(fd2, 1);
                        command(arg);
                    }
                    close(fd1);
                    close(fd2);
                    free(arg);
                    free(arg2);
                    free(arg3);
                    free(arg4);
                }
                else {
                    char** arg = malloc(MAXARGS * sizeof(*arg));
                    char** arg2 = malloc(MAXARGS * sizeof(*arg2));
                    make_tokens2(buf, arg, arg2, "<");
                    int fd1 = open(arg2[0], O_RDONLY, 00777);
                    if (fd1 == -1) {
                        perror("mini");
                    }
                    else if (fd1 != -1) {
                        dup2(fd1, fileno(stdin));
                        command(arg);
                    }
                    close(fd1);
                    free(arg);
                    free(arg2);
                }
            }
            else if (strstr(buf, ">>") != NULL) {
                char** arg = malloc(MAXARGS * sizeof(*arg)); char** arg2 = malloc(MAXARGS * sizeof(*arg2));
                make_tokens2(buf, arg, arg2, ">>");
                int fd1 = open(arg2[0], O_WRONLY | O_APPEND, 00777);
                if (fd1 == -1) {
                    perror("mini");
                }
                else if (fd1 != -1) {
                    dup2(fd1, fileno(stdout));
                    command(arg);
                }
                close(fd1);
                free(arg);
                free(arg2);
            }
            else if (strchr(buf, '>') != NULL) {
                char** arg = malloc(MAXARGS * sizeof(*arg));
                char** arg2 = malloc(MAXARGS * sizeof(*arg2));
                make_tokens2(buf, arg, arg2, ">");
                int fd1 = open(arg2[0], O_WRONLY, 00777);
                if (fd1 == -1) {
                    perror("mini");
                }
                else if (fd1 != -1) {
                    dup2(fd1, fileno(stdout));
                    command(arg);
                }
                close(fd1);
                free(arg);
                free(arg2);
            }
            else {
                char** argv = malloc(MAXARGS * sizeof(*argv));
                parseline(buf, argv);
                command(argv);
                free(argv);
            }
        }
        if (strchr(buf, '&') != NULL) {

        }
        exit(0);//parent process exit
    }
    
    /* Parent waits for foreground job to terminate */
    int status;
    pid_t waitstate = waitpid(pid, &status, WUNTRACED);
}

int parseline(char* buf, char** argv){
    int argc;            /* Number of args */
    int bg;              /* Background job? */
    char* buf2=malloc(MAXLINE * sizeof(char));
    strcpy(buf2, buf);
    while (*buf2 && (*buf2 == ' '))
        buf2++;
    buf2[strlen(buf2) - 1] = ' ';/* Replace trailing '\n' with space */

    /* Build the argv list */
    argc = 0;
    char* ptr = strtok(buf2, " ");
    while (ptr != NULL) {
        argv[argc] = malloc(sizeof(**argv) * (strlen(ptr) + 1));
        if(argv[argc])
            strcpy(argv[argc++], ptr);
        ptr = strtok(NULL, " ");
    }
    argv[argc] = NULL;

    /* Ignore blank line */
    if (argc == 0)
        return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc - 1] == '&')) != 0)
        argv[--argc] = NULL;
    free(buf2);
    return bg;
}
/* $end parseline */

void command(char** argv) {
    if (!strcmp(argv[0], "ls") || !strcmp(argv[0], "man") || !strcmp(argv[0], "grep")
        || !strcmp(argv[0], "sort") || !strcmp(argv[0], "awk") || !strcmp(argv[0], "bc")) {
        if (execvp(argv[0], argv) < 0) {
            fprintf(stderr, "%s: Command not found.\n", argv[0]);
        }
    }
    else if (!strcmp(argv[0], "head")) {
        if (execv(head_p, argv) < 0) {
            fprintf(stderr, "%s: Command not found.\n", argv[0]);
        }
    }
    else if (!strcmp(argv[0], "tail")) {
        if (execv(tail_p, argv) < 0) {
            fprintf(stderr, "%s: Command not found.\n", argv[0]);
        }
    }
    else if (!strcmp(argv[0], "cat")) {
        if (execv(cat_p, argv) < 0) {
            fprintf(stderr, "%s: Command not found.\n", argv[0]);
        }
    }
    else if (!strcmp(argv[0], "cp")) {
        if (execv(cp_p, argv) < 0) {
            fprintf(stderr, "%s: Command not found.\n", argv[0]);

        }
    }
    else if (!strcmp(argv[0], "mv")) {
        if (execv(mv_p, argv) < 0) {
            fprintf(stderr, "%s: Command not found.\n", argv[0]);

        }
    }
    else if (!strcmp(argv[0], "rm")) {
        if (execv(rm_p, argv) < 0) {
            fprintf(stderr, "%s: Command not found.\n", argv[0]);

        }
    }
    else if (!strcmp(argv[0], "pwd")) {
        if (execv(pwd_p, argv) < 0) {
            fprintf(stderr, "%s: Command not found.\n", argv[0]);
        }
    }
    else {
        if (execv(argv[0], argv) < 0) {
            fprintf(stderr, "%s: Command not found.\n", argv[0]);
        }
    }
}

int make_tokens(char* cmd, int i, char* arg[], char* target) {
    char* left = "", * right = "", * ptr = "";
    int num = 0;
    char* cmd2=malloc(MAXLINE*sizeof(*cmd2));
    while (*cmd && (*cmd == ' '))
        cmd++;
    cmd[strlen(cmd) - 1] = ' ';
    strcpy(cmd2, cmd);

    left = strtok(cmd2, target);
    strcat(left, "\0");
    arg[i] = malloc(MAXARGS*sizeof(**arg));
    strcpy(arg[i],left);
    right = strtok(NULL, "");
    while (*right && (*right == ' '))
        right++;
    i++;

    if (strstr(right, target))
        i = make_tokens(right, i, arg, target);
    else {
        arg[i] = malloc(MAXARGS * sizeof(**arg));
        strcat(right, "\0");
        strcpy(arg[i],right);
        i++;
    }
    free(cmd2);
    return i;
}
void make_tokens2(char* cmd, char* arg[], char* arg2[], char* target) {
    char* left, * right, * ptr;
    int num = 0;
    char* cmd2=malloc(MAXLINE*sizeof(*cmd2));
    while (*cmd && (*cmd == ' '))
        cmd++;
    cmd[strlen(cmd) - 1] = ' ';
    strcpy(cmd2, cmd);

    left = strtok(cmd2, target);
    strcat(left, "\0");
    right = strtok(NULL, target);
    strcat(right, "\0");

    ptr = strtok(left, " ");
    while (ptr != NULL) {
        arg[num] = malloc(MAXARGS * sizeof(**arg));
        strcpy(arg[num++],ptr);
        ptr = strtok(NULL, " ");
    }
    arg[num] = NULL;

    num = 0;
    ptr = strtok(right, " ");
    while (ptr != NULL) {
        arg2[num] = malloc(MAXARGS * sizeof(**arg2));
        strcpy(arg2[num++], ptr);
        ptr = strtok(NULL, " ");
    }
    arg2[num] = NULL;

    free(cmd2);
    return;
}
void make_tokens3(char* cmd, char* arg[], char* arg2, char* target) {
    char* left, * right;
    char* ptr;
    int num = 0;
    char* cmd2=malloc(MAXLINE*sizeof(*cmd2));
    while (*cmd && (*cmd == ' '))
        cmd++;
    cmd[strlen(cmd) - 1] = ' ';
    strcpy(cmd2, cmd);

    left = strtok(cmd2, target);
    strcat(left, "\0");
    right = strtok(NULL, target);
    strcat(right, "\0");

    ptr = strtok(left, " ");
    while (ptr != NULL) {
        arg[num] = malloc(MAXARGS*sizeof(**arg));
        strcpy(arg[num++],ptr);
        ptr = strtok(NULL, " ");
    }
    arg[num] = NULL;

    strcpy(arg2, right);

    free(cmd2);
    return;
}
void make_tokens4(char* cmd, char argc[], char argc2[], char* target) {
    char* left = malloc(MAXARGS * sizeof(char)), * right = malloc(MAXARGS * sizeof(char));

    while (*cmd && (*cmd == ' '))
        cmd++;

    char* ptr = strtok(cmd, target);
    strcpy(left, ptr);

    ptr = strtok(NULL, target);
    strcpy(right, ptr);

    strcpy(argc, strtok(left, " "));
    strcpy(argc2, strtok(right, " "));

    free(left);
    free(right);
    return;
}
void sigstp_hand(int sig) {
    int status;
    pid_t pid2=waitpid(-1, &status, WNOHANG | WUNTRACED);
    kill(-pid2,SIGKILL);
}
