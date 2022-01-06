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
	if (fread(*text, len, sizeof(BYTE), fp) != 1) {
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
		//printf("%lu\n", tmp);
		tmp << 2;
		tmp += convert((*answer)[i*2+1]);
		//printf("%lu\n", tmp);
		result[i] = tmp;
		//printf("%x\n", result[i]);
	}
	free(*answer);
	*answer = result;
}

int sha256_test(const BYTE *input, const BYTE *output) {
	BYTE *text = NULL;
	BYTE *answer = NULL;

	read_test_case(&text, input);
	read_test_case(&answer, output);

	char_to_hex(&answer);

	BYTE buf[32];
	SHA256_CTX ctx;

	int idx;
	int pass = 1;

	//printf("%s\n", buf);
	//printf("%s\n", answer);

	sha256_init(&ctx);
 	sha256_update(&ctx, text, strlen(text));
 	sha256_final(&ctx, buf);
	sha256_show_result(buf);
	pass = pass && !memcmp(answer, buf, 32);

	terminal(&text);
	terminal(&answer);

	return pass;
}

// int sha256_test()
// {
// 	BYTE text1[] = {"abc"};
// 	BYTE text2[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
// 	BYTE text3[] = {"yang mei tang is really pretty and ivan is really excellent"};
// 	BYTE *text4;

// 	BYTE hash1[32] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
// 	                                0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};
// 	BYTE hash2[32] = {0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,
// 	                                0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};
// 	BYTE hash3[32] = {0xf2,0x45,0x11,0xc0,0x55,0x60,0x76,0xde,0x9c,0x65,0x4f,0x6d,0xb8,0xc5,0xfd,0x74,
// 									0x89,0x8f,0x27,0xdd,0xb3,0x6d,0x3c,0x67,0x41,0x93,0x2a,0x78,0x0c,0x0b,0x66,0x24};
// 	BYTE buf[32];

// 	SHA256_CTX ctx;

// 	int idx;
// 	int pass = 1;

// 	sha256_init(&ctx);
// 	sha256_update(&ctx, text1, strlen(text1));
// 	sha256_final(&ctx, buf);
// 	sha256_show_result(buf);
// 	pass = pass && !memcmp(hash1, buf, 32);

// 	sha256_init(&ctx);
// 	sha256_update(&ctx, text2, strlen(text2));
// 	sha256_final(&ctx, buf);
// 	sha256_show_result(buf);
// 	pass = pass && !memcmp(hash2, buf, 32);

// 	sha256_init(&ctx);
// 	sha256_update(&ctx, text3, strlen(text3));
// 	sha256_final(&ctx, buf);
// 	sha256_show_result(buf);
// 	pass = pass && !memcmp(hash3, buf, 32);

// 	return(pass);
// }

int main(int argc, char **argv)
{
	printf("[Info]: SHA-256 tests ------------- %s\n\n", sha256_test(argv[1], argv[2]) ? "SUCCEEDED" : "FAILED");
	return(0);
}
