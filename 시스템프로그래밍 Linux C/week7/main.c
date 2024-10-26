#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int send_sig_cnt;
int recv_sig_cnt;
int recv_ack_cnt;
pid_t pid;

void proc_exit_handler(int sig) /* SIGINT */
{
	printf("receiver: recving signal: %d\n", recv_sig_cnt);
		exit(0);
}

void recv_ack_handler(int sig) /* SIGUSR1 Parent */
{
	recv_ack_cnt++;
	return;
}

void send_sig_handler(int sig)	/* SIGALRM, 1초 후에 send_sig_handler 호출 */
{
	if (recv_ack_cnt == send_sig_cnt) {
		kill(pid, SIGINT);
		printf("all signals are sended\n");
		exit(0);
	}
	else {
		kill(pid, SIGUSR1);
	}

	printf("sender: sending %d signal\n", send_sig_cnt - recv_ack_cnt);

	alarm(1);

	return;
}

void send_ack_handler(int sig) /* SIGUSR1 Child */
{
	kill(pid, SIGUSR1);
	recv_sig_cnt++;
	printf("receiver: receive %d signal and sending acks\n", recv_sig_cnt);

	return;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		fprintf(stderr, "The number of argument should be 2\n");
		exit(1);
	}

	send_sig_cnt = atoi(argv[1]);

	printf("sending signal: %d\n", send_sig_cnt);

	/* Install Signal Handler */

	if ((pid = fork()) == 0) {
		pid = getppid();
		signal(SIGINT, proc_exit_handler);
		signal(SIGUSR1, send_ack_handler);

		while (1);
	}
	else {
		signal(SIGUSR1, recv_ack_handler);
		signal(SIGALRM, send_sig_handler);

		alarm(1);	/* 1초 후에 send_sig_handler 호출 */

		while (1);
	}

	return 0;
}
