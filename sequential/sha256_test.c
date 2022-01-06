#include "sha256.h"

void read_test_case(BYTE **text, BYTE *filename) {
	FILE *fp;
	unsigned long long len;

	printf("[Info]: Start to read file [%s]\n\n", filename);

	fp = fopen(filename, "rb");
	if (!fp) {
		printf("[Info]: Cannot open the file\n\n");
		exit(1);
	}
	fseek(fp, 0L, SEEK_END);
	len = ftell(fp);

	// rewind the file pointer to start of the file
	rewind(fp);

	// allocate
	*text = calloc(1, len+1);
	if (!(*text)) {
		printf("[Info]: Cannot allocate the memory\n\n");
		fclose(fp);
		exit(1);
	}

	// copy file to text
	if (fread(*text, len, sizeof(BYTE), fp) != 1 && strlen(*text) != len) {
		printf("[Info]: Cannot read the file\n\n");
		free(text);
		fclose(fp);
		exit(1);
	}

	printf("[Info]: Read [%s] file ------------- SUCCESS\n\n", filename);
	fclose(fp);
}

void terminal(BYTE **text) {
	free(*text);
}

unsigned int convert(BYTE letter) {
	if (letter >= 'a' && letter <= 'f') return letter - 'a' + 10;
	else return letter - '0';
}

void char_to_hex(BYTE **answer) {
	BYTE *result = (BYTE*)malloc(sizeof(BYTE)*32);
	unsigned int tmp = 0;

	for (int i = 0; i < 32; i++) {
		tmp = convert((*answer)[i*2]);
		tmp = tmp << 4;
		tmp += convert((*answer)[i*2+1]);
		result[i] = tmp;
	}
	free(*answer);
	*answer = result;
}

void sha256_test(const BYTE *input, const BYTE *output) {
	BYTE *text = NULL;
	BYTE *answer = NULL;

	// read the testcase
	read_test_case(&text, input);
	read_test_case(&answer, output);

	// convert char to hex for comparing
	char_to_hex(&answer);

	// result buffer
	BYTE buf[32];
	SHA256_CTX ctx;

	int idx;
	int pass = 1;

	// start to encrypt
	sha256_init(&ctx);
 	sha256_update(&ctx, &text, strlen(text));
 	sha256_final(&ctx, buf);
	
	// check the correctness
	pass = pass && !memcmp(answer, buf, 32);
	printf("[Info]: SHA-256 tests ------------- %s\n\n", pass ? "SUCCESS" : "FAIL");

	// show transformed sha256 value
	sha256_show_result(buf);

	terminal(&text);
	terminal(&answer);
}

int main(int argc, char **argv)
{
	sha256_test(argv[1], argv[2]);
	return(0);
}
