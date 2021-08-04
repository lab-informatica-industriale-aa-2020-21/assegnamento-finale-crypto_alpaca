#include "unity.h"
#include "file_IO.h"

void test_uint32_to_stringHex_ShouldConvertIntIntoFixedLenString(void) {
	char string_num[HEX_NUMB_LENGTH + 1];
	uint32_to_stringHex(68241, string_num);

	TEST_ASSERT_EQUAL_STRING_LEN("00010a91", string_num, HEX_NUMB_LENGTH);
}

void test_uint32_to_stringDec_ShouldConvertIntIntoFixedLenString(void) {
        char string_num[DEC_NUMB_LENGTH + 1];
        uint32_to_stringDec(68241, string_num);

        TEST_ASSERT_EQUAL_STRING_LEN("0000068241", string_num, DEC_NUMB_LENGTH);
}

void test_print_line_ShouldFormatFixedLenStringFromTitleAndArgument(void) {
	char test_line[LINE_LENGTH + 1];
	char test_title[TITLE_LENGTH + 1] = "title";
	char test_arg[ARG_LENGTH + 1] = "argument";
	print_line(test_title, test_arg, test_line);

	TEST_ASSERT_EQUAL_STRING_LEN("title                      argument", test_line, LINE_LENGTH);
}

void test_add_empty_line_ShouldAddEmptyLineToString(void) {
	char test_string[11 + LINE_LENGTH + 1] = "test string";
	add_empty_line(test_string);

	TEST_ASSERT_EQUAL_STRING_LEN("test string                                   \n",
								test_string, 11 + LINE_LENGTH + 1);

}

void test_print_block_header_ShouldFormatFixedLenStringWithBlockHeaderInfo(void) {
	char test_string[BLOCK_HEADER_LENGTH + 1];
	time_t creation_time = time(NULL);

	block test_block = {
		25,												//count_index
		NULL,											//prev_hash
		{213, 19232, 0, 191302, 1752, 1, 5, 12332},		//hash
		39291,											//nonce
		NULL,											//*first_trans
		3,												//num_trans
		creation_time,
		NULL											//head_block
	};
	print_block_header(&test_block, test_string);

	TEST_ASSERT_EQUAL_STRING_LEN("Index:                   0000000025\n"
								 "Creation time:           data e ora\n"
								 "Hash number:               000000d5\n"
								 "                           00004b20\n"
								 "                           00000000\n"
								 "                           0002eb46\n"
								 "                           000006d8\n"
								 "                           00000001\n"
								 "                           00000005\n"
								 "                           0000302c\n"
								 "Nonce number:              0000997b\n",
								 test_string, BLOCK_HEADER_LENGTH + 1);
}

void test_print_trans_ShouldFormatFixedLenStringWithSingleTransInfo(void) {
	char test_string[TRANS_LENGTH + 1];
	trans test_trans = {
		23913,
		9138432,
		1340,
		NULL,
		NULL,
		1
	};
	print_trans(&test_trans, test_string);

	TEST_ASSERT_EQUAL_STRING_LEN("Transaction n.           0000000001\n"
								 "Sender:                    00005d69\n"
								 "Receiver:                  008b7100\n"
								 "Amount:                  0000001340\n",
								 test_string, TRANS_LENGTH + 1);


}

void test_print_block_trans_ShouldFormatFixedLenStringWithAllBlockTransInfo(void) {
	char test_string[TRANS_LENGTH * 3 + LINE_LENGTH + 1 + 1];
	//char test_string[274] = "\0";
	
	time_t creation_time = time(NULL);

	block test_block = {
		25,												//count_index
		NULL,											//prev_hash
		{213, 19232, 0, 191302, 1752, 1, 5, 12332},		//hash
		39291,											//nonce
		NULL,											//*first_trans
		3,												//num_trans
		creation_time,
		NULL											//head_block
	};

	trans test_trans1 = {
		23913,
		9138432,
		1340,
		NULL,
		NULL,
		1
	};

	trans test_trans2 = {
		192323,
		1039,
		10923,
		NULL,
		NULL,
		2
	};

	trans test_trans3 = {
		12321,
		9834,
		10,
		NULL,
		NULL,
		3
	};

	test_block.first_trans = &test_trans1;
	test_trans1.next = &test_trans2;
	test_trans1.first_trans = &test_trans1;
	test_trans2.next = &test_trans3;
	test_trans2.first_trans = &test_trans1;
	test_trans3.first_trans = &test_trans1;

	print_block_trans(&test_block, test_string);

	TEST_ASSERT_EQUAL_STRING_LEN("Transaction n.           0000000001\n"
								 "Sender:                    00005d69\n"
								 "Receiver:                  008b7100\n"
								 "Amount:                  0000001340\n"
								 "Transaction n.           0000000002\n"
								 "Sender:                    0002ef43\n"
								 "Receiver:                  0000040f\n"
								 "Amount:                  0000010923\n"
								 "Transaction n.           0000000003\n"
								 "Sender:                    00003021\n"
								 "Receiver:                  0000266a\n"
								 "Amount:                  0000000010\n"
								 "N. di trans.                      3\n",
								 test_string, TRANS_LENGTH * 3 + LINE_LENGTH + 1 + 1);
}

void test_print_block_ShouldFormatFixedLenStringWithBlockInfo(void) {
	char test_string[BLOCK_HEADER_LENGTH + TRANS_LENGTH * 3 + LINE_LENGTH + 10];
	
	time_t creation_time = time(NULL);

	block test_block = {
		25,												//count_index
		NULL,											//prev_hash
		{213, 19232, 0, 191302, 1752, 1, 5, 12332},		//hash
		39291,											//nonce
		NULL,											//*first_trans
		3,												//num_trans
		creation_time,
		NULL											//head_block
	};

	trans test_trans1 = {
		23913,
		9138432,
		1340,
		NULL,
		NULL,
		1
	};

	trans test_trans2 = {
		192323,
		1039,
		10923,
		NULL,
		NULL,
		2
	};

	trans test_trans3 = {
		12321,
		9834,
		10,
		NULL,
		NULL,
		3
	};

	test_block.first_trans = &test_trans1;
	test_trans1.next = &test_trans2;
	test_trans1.first_trans = &test_trans1;
	test_trans2.next = &test_trans3;
	test_trans2.first_trans = &test_trans1;
	test_trans3.first_trans = &test_trans1;

	print_block(&test_block, test_string);

	TEST_ASSERT_EQUAL_STRING_LEN("Index:                   0000000025\n"
								 "Creation time:           data e ora\n"
								 "Hash number:               000000d5\n"
								 "                           00004b20\n"
								 "                           00000000\n"
								 "                           0002eb46\n"
								 "                           000006d8\n"
								 "                           00000001\n"
								 "                           00000005\n"
								 "                           0000302c\n"
								 "Nonce number:              0000997b\n"
								 "Transaction n.           0000000001\n"
								 "Sender:                    00005d69\n"
								 "Receiver:                  008b7100\n"
								 "Amount:                  0000001340\n"
								 "Transaction n.           0000000002\n"
								 "Sender:                    0002ef43\n"
								 "Receiver:                  0000040f\n"
								 "Amount:                  0000010923\n"
								 "Transaction n.           0000000003\n"
								 "Sender:                    00003021\n"
								 "Receiver:                  0000266a\n"
								 "Amount:                  0000000010\n"
								 "N. di trans.                      3\n",
								 test_string, BLOCK_HEADER_LENGTH + TRANS_LENGTH * 3 + LINE_LENGTH + 1);
}

int main(void) {
	UNITY_BEGIN();

	RUN_TEST(test_uint32_to_stringHex_ShouldConvertIntIntoFixedLenString);
	RUN_TEST(test_uint32_to_stringDec_ShouldConvertIntIntoFixedLenString);
	RUN_TEST(test_print_line_ShouldFormatFixedLenStringFromTitleAndArgument);
	RUN_TEST(test_add_empty_line_ShouldAddEmptyLineToString);
	RUN_TEST(test_print_block_header_ShouldFormatFixedLenStringWithBlockHeaderInfo);
	RUN_TEST(test_print_trans_ShouldFormatFixedLenStringWithSingleTransInfo);
	RUN_TEST(test_print_block_trans_ShouldFormatFixedLenStringWithAllBlockTransInfo);
	RUN_TEST(test_print_block_ShouldFormatFixedLenStringWithBlockInfo);

	return UNITY_END();
}