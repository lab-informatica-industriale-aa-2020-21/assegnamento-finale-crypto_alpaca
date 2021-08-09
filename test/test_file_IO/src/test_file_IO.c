#include "unity.h"
#include "file_IO.h"
#include "format_string.h"

void test_write_block_ShouldWriteBlockInfoOnTxtFile(void) {
	FILE *fp;
	fp = fopen(TEST_BLOCKCHAIN_TXT, "r");
	//char test_string[ARG_LENGTH + 1];

	time_t creation_time = time(NULL);

	block test_block = {
        NULL,                                           //next_block
		NULL,											//*first_trans
		NULL,											//head_trans
		25,												//count_block
		NULL,											//prev_hash
		{213, 19232, 0, 191302, 1752, 1, 5, 12332},		//hash
		39291,											//nonce
		3,												//num_trans
		creation_time,
	};

	trans test_trans1 = {
		NULL,
		23913,
		9138432,
		1340,
		1
	};

	trans test_trans2 = {
		NULL,
		192323,
		1039,
		10923,
		2
	};

	trans test_trans3 = {
		NULL,
		12321,
		9834,
		10,
		3
	};

	test_block.head_trans = &test_trans3;
	test_block.first_trans = &test_trans1;
	test_trans1.next_trans = &test_trans2;
	test_trans2.next_trans = &test_trans3;;

	write_block(&test_block, fp);
	fclose(fp);

	//Da testare lettura file test_blockchain.txt
}

void test_get_arg_ShouldFillStringOfGivenBlockchainFileLine(void) {
	FILE *fp;
	fp = fopen(TEST_BLOCKCHAIN_TXT, "r");
	char test_string[ARG_LENGTH + 1];

	get_arg(fp, -5, test_string);
	fclose(fp);

	TEST_ASSERT_EQUAL_STRING_LEN("00003021", test_string, 8 + 1);

}

void test_get_arg_uint32Dec_ShouldReturnUint32FromGivenBlockchainFileLine(void) {
	FILE *fp;
	fp = fopen(TEST_BLOCKCHAIN_TXT, "r");
	uint32_t test_int = get_arg_uint32Dec(fp, -3);
	fclose(fp);

	TEST_ASSERT_EQUAL_UINT32(10, test_int);
}

void test_get_arg_uint32Hex_ShouldReturnUint32FromGivenBlockchainFileLine(void) {
	FILE *fp;
	fp = fopen(TEST_BLOCKCHAIN_TXT, "r");
	uint32_t test_int = get_arg_uint32Hex(fp, -4);
	fclose(fp);

	TEST_ASSERT_EQUAL_UINT32(9834, test_int);
}

void test_get_prev_hash_ShouldReadAndFillHashArray(void) {
	uint32_t test_prev_hash[8];
	uint32_t exp_prev_hash[8] = {213, 19232, 0, 191302, 1752, 1, 5, 12332};
	get_prev_hash(test_prev_hash, TEST_BLOCKCHAIN_TXT);

	TEST_ASSERT_EQUAL_UINT32_ARRAY(exp_prev_hash, test_prev_hash, 8);
}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_write_block_ShouldWriteBlockInfoOnTxtFile);
	RUN_TEST(test_get_arg_ShouldFillStringOfGivenBlockchainFileLine);
	RUN_TEST(test_get_arg_uint32Dec_ShouldReturnUint32FromGivenBlockchainFileLine);
	RUN_TEST(test_get_arg_uint32Hex_ShouldReturnUint32FromGivenBlockchainFileLine);
	RUN_TEST(test_get_prev_hash_ShouldReadAndFillHashArray);

	return UNITY_END();
}