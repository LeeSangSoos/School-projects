#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(int argc, char** argv) {
	if (remove(argv[1]) != 0)
		perror("rm");
}