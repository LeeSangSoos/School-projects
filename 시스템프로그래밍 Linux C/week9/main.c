#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#include <signal.h>

struct msg
{
	long msgtype;
	char text[256];
};

struct msg_ack 
{
	long msgtype;
	char time[256];
};

int main()
{
	/* 
	 * @ int uid: user ID
	 * @ int receiver_id: receiver's ID
	 */ 
	int uid; 
	int receiver_id;
	int pid;

	printf("my id is \n");
	scanf("%d", &uid);
	getchar(); // flush

	printf("who to send ? \n");
	scanf("%d", &receiver_id); 
	getchar(); // flush  
		
	/* code to get key and QID */
	key_t k = ftok(".", 'a');
	int qid = msgget(k, IPC_CREAT | 0770);
	if (qid == -1) {
		perror("msgget error : ");
		exit(1);
	}
	struct msg* msg = malloc(sizeof(struct msg));
	msg->msgtype = uid;
	struct msg_ack* msg_ack = malloc(sizeof(struct msg_ack));
	msg_ack->msgtype = uid+1;

	if ((pid=fork()) == 0) {
		while (1) {
			/* receive message */ 
			/* get msg from queue and print out */ 
			if (msgrcv(qid, (void*)msg, sizeof(msg->text), receiver_id, 0)>0) {
				printf("RECEIVED %s\n", msg->text);

				time_t current_time = time(NULL);
				strcpy(msg_ack->time, ctime(&current_time));
				if (msgsnd(qid, (void*)msg_ack, sizeof(msg_ack->time), 0) == -1) {
					perror("msgrscv error:");
					exit(1);
				}
			}			
		}
	} else {
		while (1) {
			/* send message */ 
			/* get user input and send to the msg queue */
			size_t len = 0;
			char* line = NULL;
			getline(&line,&len,stdin);
			strcpy(msg->text, line);
			if (!strcmp(msg->text,"quit\n")) {
				free(msg);
				free(msg_ack);
				kill(pid, SIGINT);
				msgctl(qid, IPC_RMID, NULL);
				exit(0);
			}
			if (msgsnd(qid, (void*)msg, sizeof(msg->text), 0) == -1) {
				perror("msgsnd error:");
				exit(0);
			}

			if (msgrcv(qid, (void*)msg_ack, sizeof(msg_ack->time), receiver_id + 1, 0) > 0) {
				printf("%d read message at: %s\n", receiver_id, msg_ack->time);
			}
			
		}
	}	

	free(msg);
	free(msg_ack);
	kill(pid, SIGINT);
	msgctl(qid, IPC_RMID, NULL);
	return 0;
}
