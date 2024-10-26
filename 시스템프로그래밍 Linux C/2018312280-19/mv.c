#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

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
		char* tmp = malloc(256 * sizeof(*tmp));
		char* tmp2 = malloc(256 * sizeof(*tmp));

		realpath(argv[2], path2);
		realpath(argv[1], path1);

		if (rename(path1, path2) != 0) {
			strcpy(tmp2,strtok(argv[1], "/"));
			while (1) {
				if (tmp2 != NULL) {
					strcpy(tmp, tmp2);
				}
				else {
					break;
				}
				tmp2 = strtok(NULL, "/");
			}
			strcat(path2, "/");
			strcat(path2, tmp);
			if (rename(path1, path2) != 0) {
				perror("mv");
			}
		}

		free(path1);
		free(path2);
		free(tmp);
	}
}