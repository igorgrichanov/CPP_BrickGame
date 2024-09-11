#include "tetris_suites.h"

void run_testcase(Suite *testcase) {
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  // failed = srunner_ntests_failed(sr);
  srunner_free(sr);
}

void run_tests() {
  Suite *test_cases[] = {tetris_backend_test_suite(), matrix_test_suite(),
                         tetris_field_test_suite(), tetris_controller_test_suite(), NULL};
  for (Suite **current_testcase = test_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

int main() {
  srand(time(NULL));
  run_tests();
}