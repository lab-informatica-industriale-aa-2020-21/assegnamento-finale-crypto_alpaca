#include "unity.h"

#include "hash.h"

void setUp(void) {}

void tearDown(void) {}


void test_rotate_shouldRotateGiven32bitUintWord(void) {
	TEST_ASSERT_EQUAL_UINT32(497166976, rotate(3884117));
}

//Operations: y_test = rot_r(x,7) XOR rot_r(x,18) XOR shift_r(x,3)
void test_sigma_0_shouldCalculateSigma0OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(2064801292, sigma_0(3884117));
}

//Operations: y_test = rot_r(x,2) XOR rot_r(x,13) XOR rot_r(x,22)
void test_usigma_0_shouldCalculateUsigma0OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(2411168975, usigma_0(3884117));
}

//Operations: y_test = rot_r(x,17) XOR rot_r(x,19) XOR shift_r(x,10)
void test_sigma_1_shouldCalculateSigma1OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(3399495371, sigma_1(3884117));
}

//Operations: y_test = rot_r(x,6) XOR rot_r(x,11) XOR rot_r(x,25)
void test_usigma_1_shouldCalculateUsigma1OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(3271737593, usigma_1(3884117));
}

int main(void) {

	UNITY_BEGIN();

	RUN_TEST(test_rotate_shouldRotateGiven32bitUintWord);

	RUN_TEST(test_sigma_0_shouldCalculateSigma0OperationSeriesTox);
	RUN_TEST(test_usigma_0_shouldCalculateUsigma0OperationSeriesTox);
	RUN_TEST(test_sigma_1_shouldCalculateSigma1OperationSeriesTox);
	RUN_TEST(test_usigma_1_shouldCalculateUsigma1OperationSeriesTox);

	return(UNITY_END());
}