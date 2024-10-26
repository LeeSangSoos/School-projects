#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void main(int argc, char** argv) {
	char* buf = malloc(512 * sizeof(*buf));
	FILE* fd1;
	if (argc < 2) {
		for (int i = 0; i < 10; i++) {
			if (fgets(buf, 512, stdin) != NULL)
				printf("%s", buf);
		}
	}
	else if (argc < 3) {
		fd1 = fopen(argv[1],"r");
		if (fd1 == NULL) {
			perror("head");
		}
		else {
			for (int i = 0; i < 10; i++) {
				if (fgets(buf, 512, fd1) != NULL)
					printf("%s", buf);
			}
		}
		fclose(fd1);
	}
	else if (argc < 4) {
		int num = atoi(argv[2]);
		for (int i = 0; i < num; i++) {
			if (fgets(buf, 512, stdin) != NULL)
				printf("%s", buf);
		}
	}
	else {
		int num = atoi(argv[2]);
		fd1 = fopen(argv[3], "r");
		if (fd1 == NULL) {
			perror("head");
		}
		else {
			for (int i = 0; i < num; i++) {
				if (fgets(buf, 512, fd1) != NULL)
					printf("%s", buf);
			}
		}
		fclose(fd1);
	}
	free(buf);
}