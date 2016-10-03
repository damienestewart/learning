#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

	FILE *infp;
	FILE *outfp;
	int key = 0;	


	if (argc < 3) {
		// handle error
		printf("Usage: %s <filename> <key>\n", argv[0]);
		exit(1);
	}

	if ((infp = fopen(argv[1], "r")) == NULL) {
		// handle error
		exit(1);
	}

	// create output filename
	char postfix[] = "_decrypted";
	char *outfilename = calloc(strlen(argv[1]) + strlen(postfix) + 1, 1);
	strcpy(outfilename, argv[1]);
	strcat(outfilename, postfix);

	if ((outfp = fopen(outfilename, "w")) == NULL) {
		// handle error
		exit(1);
	}

	key = atoi(argv[2]);

	int c;
	int d;
	char upper = 0;
	while ((c = fgetc(infp)) != EOF) {
		if (!isalpha(c)) {
			fputc(c, outfp);
			continue;
		}

		if (c > 65 && c < 91) {
			upper = 1;
			c -= 65;
			upper = 1;
		} else {
			c -= 97;
			upper = 0; 
		}

		d = (c + (26 - key)) % 26; // instead of (c - key) % 26 to avoid negative remainder.
		if (upper) {
			d += 65;
		} else {
			d += 97;
		}
		fputc(d, outfp);
	}
	fflush(outfp);
	fclose(outfp);
	fclose(infp);
	return 0;
}
