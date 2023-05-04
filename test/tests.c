#include <unity.h>
#include <utils.h>

void setUp(void) {
    
}
void tearDown(void) {
    
}

void test_isAlpha(void) {
    TEST_ASSERT_EQUAL_INT(1, is_alpha('a'));
    TEST_ASSERT_EQUAL_INT(0, is_alpha('1'));
    TEST_ASSERT_EQUAL_INT(0, is_alpha('!'));
    TEST_ASSERT_EQUAL_INT(0, is_alpha(' '));
    TEST_ASSERT_EQUAL_INT(0, is_alpha('\t'));
}
 
int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_isAlpha);
  return UNITY_END();
}
