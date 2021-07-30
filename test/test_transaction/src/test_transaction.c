#include <limits.h>

#include "unity.h"
#include "transaction.h"

void setUp(void) {}
void tearDown(void) {}

void test_new_trans_shouldAssignParametersToNewTransaction(void) {
	int test_count = 10;
	trans *test_trans = new_trans(1023, 10848, 249, &test_count);

	TEST_ASSERT_EQUAL_INT32(1023, test_trans->sender);
	TEST_ASSERT_EQUAL_INT32(10848, test_trans->receiver);
	TEST_ASSERT_EQUAL_INT32(249, test_trans->amount);
	TEST_ASSERT_EQUAL_INT(test_count+1, count);
}

void test_new_trans_bound_shouldAssignParametersToNewTransaction(void) {
	int test_count = INT_MAX - 1;
	trans *test_trans = new_trans(UINT_MAX, UINT_MAX, UINT_MAX, &test_count);

	TEST_ASSERT_EQUAL_INT32(UINT_MAX, test_trans->sender);
	TEST_ASSERT_EQUAL_INT32(UINT_MAX, test_trans->receiver);
	TEST_ASSERT_EQUAL_INT32(UINT_MAX, test_trans->amount);
	TEST_ASSERT_EQUAL_INT(INT_MAX, count);

	test_count = INT_MIN;
	trans *test_trans = new_trans(0, 0, 0, &test_count);

	TEST_ASSERT_EQUAL_INT32(0, test_trans->sender);
	TEST_ASSERT_EQUAL_INT32(0, test_trans->receiver);
	TEST_ASSERT_EQUAL_INT32(0, test_trans->amount);
	TEST_ASSERT_EQUAL_INT(INT_MIN+1, count);
}

int main(void) {

        UNITY_BEGIN();
	RUN_TEST(test_new_trans_shouldAssignParametersToNewTransaction);
        return(UNITY_END());

}
