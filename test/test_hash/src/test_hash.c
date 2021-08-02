#include "unity.h"

#include "hash.h"

void setUp(void) {}

void tearDown(void) {}


//Operations: y_test = rot(x,7) XOR rot(x,18) XOR shift_dx(x,3)
void test_sigma_0_shouldCalculateSigma0OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_HEX(sigma_0(0x4AF), 0x5F2BC09C);
}

int main(void) {

	UNITY_BEGIN();
	RUN_TEST(test_sigma_0_shouldCalculateSigma0OperationSeriesTox);
	return(UNITY_END());

}
