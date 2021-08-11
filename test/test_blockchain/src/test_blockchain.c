#include <limits.h>
#include <time.h>
#include <stdio.h>

#include "unity.h"
#include "blockchain.h"

void setUp() {}
void tearDown() {}

void test_new_trans_shouldAddNewTransactionToListOfTransactions(void) {

    trans *test_trans1 = new_trans(2839, 90243, 1240, NULL);
    trans *test_trans2 = new_trans(20943, 2390, 130, test_trans1);
    trans *test_trans3 = new_trans(3095, 9827346, 10, test_trans2);

    trans exp_trans1 = {
        test_trans2,
        2839,
        90243,
        1240,
        0
    };
    
    trans exp_trans2 = {
        test_trans3,
        20943,
        2390,
        130,
        1
    };

    trans exp_trans3 = {
        NULL,
        3095,
        9827346,
        10,
        2
    };

    TEST_ASSERT_EQUAL_MEMORY(&exp_trans1, test_trans1, sizeof(trans));
    TEST_ASSERT_EQUAL_MEMORY(&exp_trans2, test_trans2, sizeof(trans));
    TEST_ASSERT_EQUAL_MEMORY(&exp_trans3, test_trans3, sizeof(trans));
    free(test_trans1);
    free(test_trans2);
    free(test_trans3);
}


void test_new_block_shouldAddNewBlockToListOfBlocks(void) {
    block *test_block1 = new_block(NULL);
    block *test_block2 = new_block(test_block1);
    block *test_block3 = new_block(test_block2);

    time_t creation_time = (time_t)(0);

    block exp_block1 = {
        test_block2,
        NULL,
        NULL,
        0,
        NULL,
        {0xFFFFFFFF, 0, 0, 0, 0, 0, 0, 0},
        0,
        0,
        creation_time
    };

    block exp_block2 = {
        test_block3,
        NULL,
        NULL,
        1,
        test_block1 -> hash,
        {0xFFFFFFFF, 0, 0, 0, 0, 0, 0, 0},
        0,
        0,
        creation_time
    };

    block exp_block3 = {
        NULL,
        NULL,
        NULL,
        2,
        test_block2 -> hash,
        {0xFFFFFFFF, 0, 0, 0, 0, 0, 0, 0},
        0,
        0,
        creation_time
    };


    TEST_ASSERT_EQUAL_PTR(exp_block1.next_block, test_block1->next_block);
    TEST_ASSERT_EQUAL_PTR(exp_block2.next_block, test_block2->next_block);
    TEST_ASSERT_EQUAL_PTR(exp_block3.next_block, test_block3->next_block);

    TEST_ASSERT_EQUAL_PTR(exp_block1.prev_hash, test_block1->prev_hash);
    TEST_ASSERT_EQUAL_PTR(exp_block2.prev_hash, test_block2->prev_hash);
    TEST_ASSERT_EQUAL_PTR(exp_block3.prev_hash, test_block3->prev_hash);

    TEST_ASSERT_EQUAL_UINT32_ARRAY(exp_block1.prev_hash, test_block1->prev_hash, 8);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(exp_block2.prev_hash, test_block2->prev_hash, 8);
    TEST_ASSERT_EQUAL_UINT32_ARRAY(exp_block3.prev_hash, test_block3->prev_hash, 8);

    TEST_ASSERT_EQUAL_MEMORY(&exp_block1.creation_time, &test_block1->creation_time, sizeof(time_t));
    TEST_ASSERT_EQUAL_MEMORY(&exp_block2.creation_time, &test_block2->creation_time, sizeof(time_t));
    TEST_ASSERT_EQUAL_MEMORY(&exp_block3.creation_time, &test_block3->creation_time, sizeof(time_t));

    free(test_block1);
    free(test_block2);
    free(test_block3);
}

void test_new_chain_shouldAddNewChainToListOfChains(void) {
    chain *test_chain1 = new_chain(NULL);
    chain *test_chain2 = new_chain(test_chain1);
    chain *test_chain3 = new_chain(test_chain2);

    chain exp_chain1 = {
        test_chain2,
        NULL,
        NULL,
        0,
        0
    };

    chain exp_chain2 = {
        test_chain3,
        NULL,
        NULL,
        0,
        1
    };

    chain exp_chain3 = {
        NULL,
        NULL,
        NULL,
        0,
        2
    };

    TEST_ASSERT_EQUAL_MEMORY(&exp_chain1, test_chain1, sizeof(chain));
    TEST_ASSERT_EQUAL_MEMORY(&exp_chain2, test_chain2, sizeof(chain));
    TEST_ASSERT_EQUAL_MEMORY(&exp_chain3, test_chain3, sizeof(chain));

    free(test_chain1);
    free(test_chain2);
    free(test_chain3);
}

void test_get_str_creation_time_shoulAssignBlockCreationTime(void) {
    time_t creation_time = (time_t)(0);
    char test_string[TIMEINFO_STR_LEN];
    get_str_creation_time(creation_time, test_string);

    TEST_ASSERT_EQUAL_STRING_LEN("1970-01-01 00:00:00", test_string, TIMEINFO_STR_LEN);
}

int main(void) {
    UNITY_BEGIN();

    //Standard testing
    RUN_TEST(test_new_trans_shouldAddNewTransactionToListOfTransactions);
    RUN_TEST(test_new_block_shouldAddNewBlockToListOfBlocks);
    RUN_TEST(test_new_chain_shouldAddNewChainToListOfChains);
    RUN_TEST(test_get_str_creation_time_shoulAssignBlockCreationTime);


    return UNITY_END();
}