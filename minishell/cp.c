#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void main(int argc, char** argv) {
	if (argc<2) {
		fprintf(stderr, "cp: missing file operand\n");
	}
	else if (argc < 3) {
		fprintf(stderr, "cp: missing destination file operand after 'FILE1'\n");
	}
	else {
		int fd1= open(argv[1], O_RDONLY, 00777);
		int fd2;
		if (fd1 < 0) {
			perror("cp");
		}
		else {
			fd2 = open(argv[2], O_WRONLY | O_CREAT, 00777);
			if (fd2 < 0) {
				perror("cp");
			}
			char* buf=malloc(512*sizeof(*buf));
			int nbytes;
			if ((nbytes = read(fd1, buf, 512)) < 0) {
				perror("cp");
			}
			if (write(fd2, buf, nbytes) < 0) {
				perror("cp");
			}
			close(fd2);
			free(buf);
		}
		close(fd1);
	}
}