/*
 * ---------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <floreal@nimukaito.net> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return.
 * Floréal Toumikian
 * ---------------------------------------------------------------------------
 */

#include "tap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

TestResult test_result_create(char success, const char* message)
{
  TestResult instance = {
    success,
    message,
    "",
    0
  };

  return instance;
}

TestResult success()
{
  return test_result_create(SUCCESS, "");
}

TestResult fail(const char* message)
{
  return test_result_create(FAILURE, message);
}

void test_result_print(TestResult self) {
  static char* ok[2] = {"not ok", "ok"};
  printf("%s - %ld %s\n", ok[self.result], self.number, self.description);
  if (self.result == FAILURE && strlen(self.error_message) > 0) {
    printf("   %s\n", self.error_message);
  }
}

TestCase* test_case_new(TestFunction function, const char* description)
{
  TestCase *instance = malloc(sizeof(TestCase));
  instance->function = function;
  instance->description = description;
  instance->next = NULL;
}

void test_case_delete(TestCase* self)
{
  if (self->next != NULL) {
    test_case_delete(self->next);
  }
  free(self);
}

TestResult test_case_run(TestCase* self, long number)
{
  TestResult result = self->function();
  result.number = number;
  result.description = self->description;
  return result;
}

TestSuite* test_suite_new() {
  TestSuite* instance = malloc(sizeof(TestSuite));
  instance->first = NULL;
  instance->last = NULL;
  instance->size = 0;
}

void test_suite_delete(TestSuite* self)
{
  if (self->first == NULL) {
    return;
  }
  
  test_case_delete(self->first);
  free(self);
}

void test_suite_add(TestSuite* self, TestFunction function, const char* description)
{
  TestCase* test_case = test_case_new(function, description);
  if (self->first == NULL) {
    self->first = test_case;
  } else {
    self->last->next = test_case;
  }
  self->size++;
  self->last = test_case;
};

void test_suite_run(TestSuite* self)
{
  TestCase* current = self->first;
  long counter = 0;
  long failed = 0;
  long passed = 0;

  if (self->size == 0) {
    return;
  }

  printf("1..%ld\n", self->size);
  
  while (current != NULL)
  {
    TestResult result = test_case_run(current, ++counter);
    test_result_print(result);
    current = current->next;
  }
}
