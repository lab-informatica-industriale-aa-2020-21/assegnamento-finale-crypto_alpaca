#include <stdbool.h>
#include <limits.h>

#include "unity.h"
#include "hash.h"

void setUp(void) {}
void tearDown(void) {}


void test_rotate_shouldRotateGiven32bitUintWord(void) {
	TEST_ASSERT_EQUAL_UINT32(497166976, rotate(3884117, 25));
}

void boundary_test_rotate_shouldRotateGiven32bitUintWord(void) {
	TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, rotate(UINT32_MAX, 100));
	TEST_ASSERT_EQUAL_UINT32(2863311530, rotate(2863311530, 150));
	TEST_ASSERT_EQUAL_UINT32(1431655765, rotate(2863311530, 191));
	TEST_ASSERT_EQUAL_UINT32(0, rotate(0, 120));
}

//Operations: y_test = rot_r(x,7) XOR rot_r(x,18) XOR shift_r(x,3)
void test_sigma_0_shouldCalculateSigma0OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(2064801292, sigma_0(3884117));
}

void boundary_test_sigma_0_shouldCalculateSigma0OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(536870911, sigma_0(UINT32_MAX));
	TEST_ASSERT_EQUAL_UINT32(0, sigma_0(0));
}

//Operations: y_test = rot_r(x,2) XOR rot_r(x,13) XOR rot_r(x,22)
void test_usigma_0_shouldCalculateUsigma0OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(2411168975, usigma_0(3884117));
}

void boundary_test_usigma_0_shouldCalculateUsigma0OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, usigma_0(UINT32_MAX));
	TEST_ASSERT_EQUAL_UINT32(0, usigma_0(0));
}

//Operations: y_test = rot_r(x,17) XOR rot_r(x,19) XOR shift_r(x,10)
void test_sigma_1_shouldCalculateSigma1OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(3399495371, sigma_1(3884117));
}

void boundary_test_sigma_1_shouldCalculateSigma1OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(4194303, sigma_1(UINT32_MAX));
	TEST_ASSERT_EQUAL_UINT32(0, sigma_1(0));
}

//Operations: y_test = rot_r(x,6) XOR rot_r(x,11) XOR rot_r(x,25)
void test_usigma_1_shouldCalculateUsigma1OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(3271737593, usigma_1(3884117));
}

void boundary_test_usigma_1_shouldCalculateUsigma1OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, usigma_1(UINT32_MAX));
	TEST_ASSERT_EQUAL_UINT32(0, usigma_1(0));
}

void test_decimal_to_bin_shouldConvertUint32ToBinary(void) {
	bool exp_bin[32] = {1,1,1,0,0,1,1,1,1,0,0,0,0,0,1,0,
						1,1,1,0,1,1,1,0,0,0,0,0,1,0,1,0};
	bool test_bin[32];
	decimal_to_bin(3884117514, test_bin, 32);

	TEST_ASSERT_EQUAL_MEMORY (exp_bin, test_bin, 32);
}

void boundary_test_decimal_to_bin_shouldConvertUint32ToBinary(void) {
	bool exp_bin1[32] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
						 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	bool exp_bin2[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
						 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	bool exp_bin3[1] = {1};
	bool exp_bin4[1] = {0};
	bool test_bin[32];

	decimal_to_bin(UINT32_MAX, test_bin, 32);
	TEST_ASSERT_EQUAL_MEMORY (exp_bin1, test_bin, 32);
	decimal_to_bin(0, test_bin, 32);
	TEST_ASSERT_EQUAL_MEMORY(exp_bin2, test_bin, 32);
	decimal_to_bin(1, test_bin, 1);
	TEST_ASSERT_EQUAL_MEMORY(exp_bin3, test_bin, 1);
	decimal_to_bin(0, test_bin, 1);
	TEST_ASSERT_EQUAL_MEMORY(exp_bin4, test_bin, 1);
}

void test_bin_to_decimal_shouldConvertBinaryToUint32(void) {
	bool test_x[32] = {1,1,1,0,0,1,1,1,1,0,0,0,0,0,1,0,
					   1,1,1,0,1,1,1,0,0,0,0,0,1,0,1,0};
	TEST_ASSERT_EQUAL_UINT32(3884117514, bin_to_decimal(test_x, 32));
}

void boundary_test_bin_to_decimal_shouldConvertBinaryToUint32(void) {
	bool test_x1[32] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				    	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	bool test_x2[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	bool test_x3[1] = {1};
	bool test_x4[1] = {0};


	TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, bin_to_decimal(test_x1, 32));
	TEST_ASSERT_EQUAL_UINT32(0, bin_to_decimal(test_x2, 32));
	TEST_ASSERT_EQUAL_UINT32(1, bin_to_decimal(test_x3, 1));
	TEST_ASSERT_EQUAL_UINT32(0, bin_to_decimal(test_x4, 1));
}

void test_choice_shouldAssignYorXtoZdependingOnX(void) {
	TEST_ASSERT_EQUAL_UINT32(234101424,
							choice(3884117514, 93658048, 2398402234));
}

void boundary_test_choice_shouldAssignYorXtoZdependingOnX(void) {
	TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, choice(UINT32_MAX, UINT32_MAX, 0));
	TEST_ASSERT_EQUAL_UINT32(0, choice(UINT32_MAX, 0, UINT32_MAX));
}

void test_majority_shouldReturnsMajorityBitwiseXYZ(void) {
	TEST_ASSERT_EQUAL(1842722981, maggiority(3515164733, 1834274982, 1843249093));
}

void boundary_test_majority_shouldReturnsMajorityBitwiseXYZ(void) {
	TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, maggiority(UINT32_MAX, UINT32_MAX, 0));
	TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, maggiority(UINT32_MAX, 0, UINT32_MAX));
	TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, maggiority(0, UINT32_MAX, UINT32_MAX));
	TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, maggiority(UINT32_MAX, UINT32_MAX, UINT32_MAX));

	TEST_ASSERT_EQUAL_UINT32(0, maggiority(UINT32_MAX, 0, 0));
	TEST_ASSERT_EQUAL_UINT32(0, maggiority(0, 0, UINT32_MAX));
	TEST_ASSERT_EQUAL_UINT32(0, maggiority(0, UINT32_MAX, 0));
	TEST_ASSERT_EQUAL_UINT32(0, maggiority(0, 0, 0));
}


//Ricordarsi di togliere la funzione da hash.c
void test_int32_to_char_shouldReturnsStringRepresentingDigitsOfUint32(void) {
	char exp_array[11] = "1948430201";
	TEST_ASSERT_EQUAL_MEMORY(exp_array, int_32_to_char(1948430201), 11);
	TEST_ASSERT_EQUAL_STRING_LEN(exp_array, int_32_to_char(1948430201), 10);
}

void boundary_test_int32_to_char_shouldReturnsStringRepresentingDigitsOfUint32(void) {
	char exp_array1[11] = "4294967295";
	char exp_array2[11] = "0000000000";
	char exp_array3[11] = "0000000001";
	char exp_array4[11] = "0999999999";

	TEST_ASSERT_EQUAL_MEMORY(exp_array1, int_32_to_char(4294967295), 10);
	TEST_ASSERT_EQUAL_MEMORY(exp_array2, int_32_to_char(0), 10);
	TEST_ASSERT_EQUAL_MEMORY(exp_array3, int_32_to_char(1), 10);
	TEST_ASSERT_EQUAL_MEMORY(exp_array4, int_32_to_char(999999999), 10);
}
//


void test_copy_vector_shouldCopyVett1IntoVett2(void) {
	uint32_t vett1[10] = {1,2,3,4,5,6,7,8,9,0};
	uint32_t vett2[10];
	copy_vector(vett1, 10, vett2, 10);

	TEST_ASSERT_EQUAL_UINT32_ARRAY(vett1, vett2, 10);
}

void boundary_test_copy_vector_shouldCopyVett1IntoVett2(void) {
	uint32_t vett1[100000] = {0};
	uint32_t vett2[100000] = {0};

	for (int i = 0; i < 100000; i++)
		vett1[i] = UINT32_MAX;
	copy_vector(vett1, 100000, vett2, 100000);

	TEST_ASSERT_EQUAL_UINT32_ARRAY(vett1, vett2, 100000);
}

void test_sum_vector_shouldSaveIntoVett2TheSumOfVett1AndVett2(void) {
	uint32_t vett1[10] = {1,2,3,4,5,6,7,8,9,0};
	uint32_t vett2[10] = {0,3,6,2,5,9,8,4,1,7};
	uint32_t exp_vett[10] = {1,5,9,6,10,15,15,12,10,7};
	sum_vector(vett1, 10, vett2, 10);

	TEST_ASSERT_EQUAL_UINT32_ARRAY(exp_vett, vett2, 10);
}

void boundary_test_sum_vector_shouldSaveIntoVett2TheSumOfVett1AndVett2(void) {
	uint32_t vett1[100000];
	uint32_t vett2[100000];
	uint32_t exp_vett[100000];

	for (uint32_t i = 0; i < 100000; i++) {
		vett1[i] = 31 * i;
		vett2[i] = 5 * i;
		exp_vett[i] = 36 * i;
	}
	sum_vector(vett1, 100000, vett2, 100000);

	TEST_ASSERT_EQUAL_UINT32_ARRAY(exp_vett, vett2, 100000);
}

void test_shift_state_reg_shouldRightShiftVettOf1Position(void) {
	uint32_t vett[10] = {1,2,3,4,5,6,7,8,9,0};
	uint32_t exp_vett[10] = {1,1,2,3,4,5,6,7,8,9};
	shift_state_reg(vett, 10);

	TEST_ASSERT_EQUAL_UINT32_ARRAY(exp_vett, vett, 10);
}

void boundary_test_shift_state_reg_shouldRightShiftVettOf1Position(void) {
	uint32_t vett[100000];
	uint32_t exp_vett[100000];

	for (uint32_t i = 0; i < 100000; i++) {
		vett[i] = UINT32_MAX;
		exp_vett[i] = UINT32_MAX;
	}

	TEST_ASSERT_EQUAL_UINT32_ARRAY(exp_vett, vett, 100000);
}


void test_make_message_bits_shouldFillMessageBitsArrayWithAsciiValuesOfstr_input(void) {
	char test_string[] = "stodelirandolol";
	uint32_t test_message_bits[4];
	uint32_t exp_message_bits[4] = {1937010532, 1701603698, 1634624623, 1819241472};
	make_message_bits(test_string, test_message_bits);

	TEST_ASSERT_EQUAL_UINT32_ARRAY_MESSAGE(exp_message_bits, test_message_bits, 4, "Error: message_bits.");
}

int main(void) {

	UNITY_BEGIN();

	//Standard test
	RUN_TEST(test_rotate_shouldRotateGiven32bitUintWord);

	RUN_TEST(test_sigma_0_shouldCalculateSigma0OperationSeriesTox);
	RUN_TEST(test_usigma_0_shouldCalculateUsigma0OperationSeriesTox);
	RUN_TEST(test_sigma_1_shouldCalculateSigma1OperationSeriesTox);
	RUN_TEST(test_usigma_1_shouldCalculateUsigma1OperationSeriesTox);

	RUN_TEST(test_decimal_to_bin_shouldConvertUint32ToBinary);
	RUN_TEST(test_bin_to_decimal_shouldConvertBinaryToUint32);
	RUN_TEST(test_int32_to_char_shouldReturnsStringRepresentingDigitsOfUint32);

	RUN_TEST(test_choice_shouldAssignYorXtoZdependingOnX);
	RUN_TEST(test_majority_shouldReturnsMajorityBitwiseXYZ);

	RUN_TEST(test_copy_vector_shouldCopyVett1IntoVett2);
	RUN_TEST(test_sum_vector_shouldSaveIntoVett2TheSumOfVett1AndVett2);
	RUN_TEST(test_shift_state_reg_shouldRightShiftVettOf1Position);

	RUN_TEST(test_make_message_bits_shouldFillMessageBitsArrayWithAsciiValuesOfstr_input);

	//Boundary test
	RUN_TEST(boundary_test_rotate_shouldRotateGiven32bitUintWord);

	RUN_TEST(boundary_test_sigma_0_shouldCalculateSigma0OperationSeriesTox);
	RUN_TEST(boundary_test_usigma_0_shouldCalculateUsigma0OperationSeriesTox);
	RUN_TEST(boundary_test_sigma_1_shouldCalculateSigma1OperationSeriesTox);
	RUN_TEST(boundary_test_usigma_1_shouldCalculateUsigma1OperationSeriesTox);

	RUN_TEST(boundary_test_decimal_to_bin_shouldConvertUint32ToBinary);
	RUN_TEST(boundary_test_bin_to_decimal_shouldConvertBinaryToUint32);
	RUN_TEST(boundary_test_int32_to_char_shouldReturnsStringRepresentingDigitsOfUint32);

	RUN_TEST(boundary_test_choice_shouldAssignYorXtoZdependingOnX);
	RUN_TEST(boundary_test_majority_shouldReturnsMajorityBitwiseXYZ);

	RUN_TEST(boundary_test_copy_vector_shouldCopyVett1IntoVett2);
	RUN_TEST(boundary_test_sum_vector_shouldSaveIntoVett2TheSumOfVett1AndVett2);
	RUN_TEST(boundary_test_shift_state_reg_shouldRightShiftVettOf1Position);

	return(UNITY_END());
}