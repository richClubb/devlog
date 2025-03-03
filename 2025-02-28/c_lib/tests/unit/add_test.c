#include <CUnit.h>

void test_add()
{
    CU_ASSERT_EQUAL(add_uint8_t(1, 2), 3);
}