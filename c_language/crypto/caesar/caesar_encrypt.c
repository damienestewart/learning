#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	FILE *fp;	
	FILE *outfp;	
	char extension[] = "_encrypted";
	int key = 0;
	
	if (argc < 3) {
		printf("Usage: caesar_encrypt <filename> <key>\n");
		exit(1);
	}

	if ((fp = fopen(argv[1], "r")) == NULL) {
		// handle error
		exit(1);
	}

	key = atoi(argv[2]);	

	// create output filename
	int arr_size = 0;
	arr_size = strlen(argv[1]) + strlen(extension);
	char *outputname = calloc(arr_size + 1, 1);
	strcpy(outputname, argv[1]);
	strcat(outputname, extension);

	if ((outfp = fopen(outputname, "w")) == NULL) {
		// handle error
		exit(1);
	}

	int c;
	int d;
	char upper = 0;
	while ((c = fgetc(fp)) != EOF) {
		if (!isalpha(c)) {
			fputc(c, outfp);
			continue;
		}

		if (c > 65 && c < 91) {
			c -= 65;
			upper = 1;		
		} else {
			c -= 97;
			upper = 0;
		}

		d = (c + key) % 26;
		
		if (upper) {
			d += 65;
		} else {
			d += 97;
		}

		fputc(d, outfp);
	}
	fflush(outfp);

	fclose(outfp);
	fclose(fp);
	return 0;
}
