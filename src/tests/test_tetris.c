#include "test.h"

START_TEST(correctInput_test) {
  int *is_cor = correctInput();
  *is_cor = TRUE;
  ck_assert_int_eq(*is_cor, *correctInput());
}
END_TEST

START_TEST(scoreWriteRead_test) {
  GameInfo_t info;
  info.score = 100;
  info.high_score = 0;
  scoreWrite(info);
  ck_assert_int_eq(scoreRead(), info.score);
}
END_TEST

START_TEST(updateLevel_test) {
  GameInfo_t info;

  info.level = 0;
  info.score = 0;
  for (int i = 1; i < 10; ++i) {
    info.score += 600;
    updateLevel(&info);
    ck_assert_int_eq(info.level, i);
  }
}
END_TEST

START_TEST(updateCurrentState_test) {
  GameInfo_t info = updateCurrentState();
  info.high_score = 0;
  ck_assert_ptr_nonnull(info.field);
  ck_assert_ptr_nonnull(info.next);
  ck_assert_int_eq(info.high_score, 0);
  ck_assert_int_eq(info.score, 0);
  ck_assert_int_eq(info.pause, 0);
  ck_assert_int_eq(info.level, 0);
  *getSignal() = Rotate;
  updateCurrentState();
  getGameInfo_t()->score = 100;
  *getSignal() = Restart;
  updateCurrentState();
  ck_assert_int_eq(updateCurrentState().score, 0);
}
END_TEST

START_TEST(userInput_test) {
  UserAction_t action = Start;
  userInput(action, FALSE);
  ck_assert_int_eq(*getSignal(), Restart);

  action = Left;
  userInput(action, FALSE);
  ck_assert_int_eq(getVector()->y, 0);
  ck_assert_int_eq(getVector()->x, -1);

  action = Right;
  userInput(action, FALSE);
  ck_assert_int_eq(getVector()->y, 0);
  ck_assert_int_eq(getVector()->x, 1);

  action = Pause;
  userInput(action, FALSE);
  ck_assert_int_eq(getVector()->y, 0);
  ck_assert_int_eq(getVector()->x, 0);

  action = Down;
  userInput(action, FALSE);
  ck_assert_int_eq(getVector()->y, 0);
  ck_assert_int_eq(getVector()->x, 0);
  ck_assert_int_eq(*getSignal(), FallDown);

  action = Action;
  userInput(action, FALSE);
  ck_assert_int_eq(getVector()->y, 0);
  ck_assert_int_eq(getVector()->x, 0);
  ck_assert_int_eq(*getSignal(), Rotate);

  action = Up;
  userInput(action, FALSE);
  ck_assert_int_eq(*correctInput(), FALSE);
}
END_TEST

Suite *tetris_tests(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("tetris_tests");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, correctInput_test);
  tcase_add_test(tc_core, scoreWriteRead_test);
  tcase_add_test(tc_core, updateLevel_test);
  tcase_add_test(tc_core, updateCurrentState_test);
  tcase_add_test(tc_core, userInput_test);
  suite_add_tcase(s, tc_core);

  return s;
}

int tetris_test() {
  int fail = 0;
  case_test(tetris_tests(), &fail);
  return fail;
}