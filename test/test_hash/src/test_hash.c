#include "unity.h"

#include "hash.h"

void setUp(void) {}

void tearDown(void) {}


//Operations: y_test = rot(x,7) XOR rot(x,18) XOR shift_dx(x,3)
void test_sigma_0_shouldCalculateSigma0OperationSeriesTox(void) {
	TEST_ASSERT_EQUAL_UINT32(2629839711, sigma_0(44804));
}

int main(void) {

	UNITY_BEGIN();
	RUN_TEST(test_sigma_0_shouldCalculateSigma0OperationSeriesTox);
	return(UNITY_END());

}
