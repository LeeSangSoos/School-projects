#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void main(int argc, char** argv) {
	char* buf = malloc(512 * sizeof(*buf));
	if (argc<2) {
		if (read(STDIN_FILENO, buf, 512) < 0) {
			perror("cp");
		}
		printf("%s", buf);
	}
	else {
		int fd1 = open(argv[1], O_RDONLY, 00777);
		if (fd1 < 0) {
			perror("cp");
		}
		else {
			if(read(fd1, buf, 512) < 0) {
				perror("cp");
			}
			else {
				printf("%s", buf);
			}
		}
		close(fd1);
	}
	free(buf);
}