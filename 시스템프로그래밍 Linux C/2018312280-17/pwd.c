#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(int argc, char** argv) {
	char* cwd = malloc(256*sizeof(*cwd));
	if (getcwd(cwd, 256) != NULL) {
		if (printf("%s\n", cwd) < 0)
			perror("pwd");
	}
	else {
		perror("pwd");
	}
	free(cwd);
}