#include "test.h"

void case_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main() {
  int fails = 0;
  fails += field_test();
  fails += shape_test();
  fails += tetris_test();

  return fails;
}