#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10
#define MEMORY_SIZE 2048
#define STACK_SIZE 2048


char *read_code(char *filename) {
	FILE *input = NULL;

	char *code = NULL;
	char buffer[BUFFER_SIZE];
	size_t current_size = 0;
	size_t read_bytes = 0;

	if (!(input = fopen(filename, "r"))) {
		return NULL;
	}

	do {
		read_bytes = fread(buffer, sizeof(char), BUFFER_SIZE, input);
		code = (char *)realloc(code, current_size + read_bytes + 1);
		strncpy(&code[current_size], buffer, read_bytes);
		current_size += read_bytes;
	} while (read_bytes == BUFFER_SIZE);

	code[current_size] = '\0';

	fclose(input);
	return code;
}


int main(int argc, char *argv[]) {
	char *code = NULL, *ip = NULL;

	char *stack[STACK_SIZE] = {NULL};
	char sp = 0;

	unsigned char m[MEMORY_SIZE] = {0};
	unsigned char *p = m;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s filename.bf\n", argv[0]);
		return 1;
	}

	code = ip = read_code(argv[1]);
	if (!code) {
		fprintf(stderr, "Error opening file %s\n", argv[1]);
		return 1;
	}

	while (*ip) {
		switch (*ip) {
			case '>': p++; break;
			case '<': p--; break;
			case '+': (*p)++; break;
			case '-': (*p)--; break;
			case ',': *p = getchar(); break;
			case '.': putchar(*p); break;
			case '[':
				if (sp >= sizeof(stack)) return 1;
				stack[sp] = ip;
				sp++;
				break;
			case ']':
				if (sp <= 0) return 1;
				if (!*p) break;
				sp--;
				ip = stack[sp];
				continue;
		}
		ip++;
	}

	return 0;
}
