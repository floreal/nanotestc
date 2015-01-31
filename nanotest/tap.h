/*
 * ---------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <floreal@nimukaito.net> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return.
 * Floréal Toumikian
 * ---------------------------------------------------------------------------
 */

#ifndef __TAP_H__
#define __TAP_H__

#define SUCCESS (char) 1
#define FAILURE (char) 0

typedef struct s_test_result
{
  char result;
  const char* error_message;
  const char* description;
  long number;
} TestResult;

typedef TestResult (*TestFunction)(void);

typedef struct s_test_case
{
  TestFunction function;
  const char* description;
  struct s_test_case* next;
} TestCase;

typedef struct s_test_suite
{
  TestCase* first;
  TestCase* last;
  long size;
} TestSuite;

#define assert_eq_m(expected,actual, message) ((expected) == (actual) ? success() : fail(message))

#define stringify(EXP) #EXP
#define m_different(lhs,rhs) stringify(lhs is different from rhs)
#define assert_eq(expected,actual) assert_eq_m(expected, actual, m_different(actual,expected))

TestResult test_result_create(char success, const char* message);
TestResult fail(const char* message);
TestResult success();
void test_result_print(TestResult test_result);

TestCase* test_case_new(TestFunction function, const char* description);
void test_case_delete(TestCase* test_case);
TestResult test_case_run(TestCase* test_case, long number);

TestSuite* test_suite_new();
void test_suite_delete(TestSuite* test_suite);
void test_suite_add(TestSuite* test_suite, TestFunction function, const char* description);
void test_suite_run(TestSuite* test_suite);

#endif //__TAP_H__
