#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void main(int argc, char** argv) {
	char* buf = malloc(512 * sizeof(*buf));
	FILE* fd1;
	char** stack = malloc(512 * sizeof(*stack));
	if (argc < 2) {

		int j = 0;
		while (fgets(buf, 512, stdin) != NULL) {
			stack[j] = malloc(512 * sizeof(**stack));
			strcpy(stack[j],buf);
			j++;
		}

		for (int i = j - 10; i < j; i++) {
			printf("%s", stack[i]);
		}
	}
	else if (argc < 3) {
		fd1 = fopen(argv[1], "r");
		if (fd1 == NULL) {
			perror("tail");
		}
		else {
			int j = 0;
			while (fgets(buf, 512, fd1) != NULL) {
				stack[j] = malloc(512 * sizeof(**stack));
				strcpy(stack[j], buf);
				j++;
			}

			for (int i = j - 10; i < j; i++) {
				printf("%s", stack[i]);
			}
		}
		fclose(fd1);
	}
	else if (argc < 4) {
		int num = atoi(argv[2]);
		int j = 0;
		while (fgets(buf, 512, stdin) != NULL) {
			stack[j] = malloc(512 * sizeof(**stack));
			strcpy(stack[j], buf);
			j++;
		}

		for (int i = j - num; i < j; i++) {
			printf("%s", stack[i]);
		}
	}
	else {
		int num = atoi(argv[2]);
		fd1 = fopen(argv[3], "r");
		if (fd1 == NULL) {
			perror("tail");
		}
		else {
			int j = 0;
			while (fgets(buf, 512, fd1) != NULL) {
				stack[j] = malloc(512 * sizeof(**stack));
				strcpy(stack[j], buf);
				j++;
			}

			for (int i = j - num; i < j; i++) {
				printf("%s", stack[i]);
			}
		}
		fclose(fd1);
	}
	free(buf);
	free(stack);
}