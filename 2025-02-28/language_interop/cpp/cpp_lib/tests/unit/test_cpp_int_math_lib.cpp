#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "cpp_int_math.h"

void test_add(void)
{
    CU_ASSERT(cpp_uint8_add(1, 2) == 3);
    CU_ASSERT(cpp_uint8_add(254, 1) == 255);
    CU_ASSERT(cpp_uint8_add(254, 3) == 255);
}

void test_sub(void)
{
    CU_ASSERT(cpp_uint8_sub(2, 1) == 1);
    CU_ASSERT(cpp_uint8_sub(2, 2) == 0);
    CU_ASSERT(cpp_uint8_sub(2, 3) == 0);
}


int main(void)
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("C++ int math tests", 0, 0);
    CU_add_test(suite, "test of cpp_uint8_add()", test_add);
    CU_add_test(suite, "test of cpp_uint8_sub()", test_sub);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}