#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "mv: missing file operand\n");
	}
	else if (argc < 3) {
		fprintf(stderr, "mv: missing destination file operand after 'SOURCE'\n");
	}
	else {
		char* path1 = malloc(256 * sizeof(*path1));
		char* path2 = malloc(256 * sizeof(*path2));

		realpath(argv[1], path1);
		realpath(argv[2], path2);

		if (rename(path1, path2) != 0)
			perror("mv");

		free(path1);
		free(path2);
	}
}