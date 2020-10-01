#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static FILE *my_fopen(const char *path, const char *mode) {
	FILE *file = fopen(path, mode);
	if (!file) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	return file;
}

static int my_fputc(int c, FILE *file) {
	int ret;
	if ((ret = fputc(c, file)) == EOF) {
		perror("fputc");
		exit(EXIT_FAILURE);
	}
	return ret;
}

#define fopen(x,y) my_fopen(x,y)
#define fputc(x,y) my_fputc(x,y)

int main(int argc, char **argv) {
	if (argc != 4) {
		fprintf(stderr, "Usage:\n  %s decode <encoded-file> <output>\n  %s encode <raw-file> <output>\n", argv[0], argv[0]);
		return EXIT_FAILURE;
	}

	// Decide on what to do
	enum {
		UnknownOperation = 0,
		DecodeOperation = 1,
		EncodeOperation = 2
	} operation = 0;
	if (strcmp(argv[1], "decode") == 0) operation = DecodeOperation;
	else if (strcmp(argv[1], "encode") == 0) operation = EncodeOperation;
	else {
		fprintf(stderr, "\"%s\" is not a valid action.\n", argv[1]);
		return EXIT_FAILURE;
	}

	// Open the input and output files
	FILE *in_file = fopen(argv[2], "rb");
	FILE *out_file = fopen(argv[3], "wb");

	// Persistent variables
	int final_byte = 0;

	// Do the conversion
	while (!feof(in_file)) {
		int read_byte = fgetc(in_file);
		if (read_byte == EOF) break;
		switch (operation) {
			case DecodeOperation:
			  final_byte += read_byte;
				if (read_byte != 0x7F) {
					if ((final_byte > 0xFF) || (final_byte < 0)) {
						fprintf(stderr, "The file contains invalid data.\n");
						return EXIT_FAILURE;
					}
					fputc(final_byte, out_file);
					final_byte = 0;
				}
				break;
			case EncodeOperation:
				while (read_byte >= 0x7F) {
					fputc(0x7F, out_file);
					read_byte -= 0x7F;
				}
				fputc(read_byte, out_file);
				break;
		}
	}

	return 0;
}