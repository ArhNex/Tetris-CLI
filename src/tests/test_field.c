#include "test.h"

START_TEST(getGameInfo_t_test) {
  int check = 100;
  GameInfo_t *info = getGameInfo_t();
  info->score = check;
  GameInfo_t *new = getGameInfo_t();
  ck_assert_int_eq(check, new->score);
}
END_TEST

START_TEST(getVector_test) {
  PointsXY check;
  check.x = 1;
  check.y = 2;
  PointsXY *vec = getVector();
  *vec = check;
  ck_assert_int_eq(check.x, getVector()->x);
  ck_assert_int_eq(check.y, getVector()->y);
}
END_TEST

START_TEST(getSignal_test) {
  Signal_t check = GameOver;
  Signal_t *sign = getSignal();
  *sign = check;
  ck_assert_int_eq(check, *getSignal());
}
END_TEST

START_TEST(fieldInit_test) {
  int **field;
  int check = 0;
  int code = fieldInit(&field);
  ck_assert_ptr_nonnull(field);
  ck_assert_int_eq(check, code);
  fieldDel(&field);
}
END_TEST

START_TEST(insertSymbolInFild_test) {
  int h = 0;
  int l = 0;
  int sim;
  int check = WALL;
  insertSymbolInFild(h, l, &sim);
  ck_assert_int_eq(check, sim);
  h = HEIGHT_P_END;
  check = FLOOR;
  insertSymbolInFild(h, l, &sim);
  ck_assert_int_eq(check, sim);
  for (h = HEIGHT_P_START; h < HEIGHT_P_END; ++h) {
    for (l = LENGHT_P_START; l < LENGHT_P_END; ++l) {
      check = FREE_SPACE;
      insertSymbolInFild(h, l, &sim);
      ck_assert_int_eq(check, sim);
    }
  }
}
END_TEST

START_TEST(fieldDel_test) {
  int **field;
  fieldInit(&field);
  fieldDel(&field);
  ck_assert_ptr_null(field);
}
END_TEST

START_TEST(fieldUptime_test) {
  int **field;
  fieldInit(&field);
  Shape shape_keeper[SHAPE_COUNT];
  initAllShapes(shape_keeper);
  Shape active_shape = shape_keeper[I];
  PointsXY vec;
  vec.x = 0;
  vec.y = 0;
  fieldUptime(&field, &active_shape, vec);
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    ck_assert_int_eq(
        field[active_shape.shape_loc[i].y][active_shape.shape_loc[i].x],
        SHAPE_ACTIVE);
  }

  vec.x = 4;
  vec.y = 0;
  fieldUptime(&field, &active_shape, vec);
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    ck_assert_int_eq(
        field[active_shape.shape_loc[i].y][active_shape.shape_loc[i].x],
        SHAPE_ACTIVE);
  }

  vec.x = 0;
  vec.y = 20;
  fieldUptime(&field, &active_shape, vec);
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    ck_assert_int_eq(
        field[active_shape.shape_loc[i].y][active_shape.shape_loc[i].x],
        SHAPE_PASSIVE);
  }

  fieldDel(&field);
}
END_TEST

START_TEST(swapLine_test) {
  GameInfo_t info;
  fieldInit(&info.field);

  swapLine(&info, 0, 1);
  for (int i = LENGHT_P_START; i < LENGHT_P_END; ++i) {
    ck_assert_int_eq(info.field[0][i], FREE_SPACE);
    ck_assert_int_eq(info.field[1][i], WALL);
  }

  fieldDel(&info.field);
}
END_TEST

START_TEST(clearLine_test) {
  GameInfo_t info;
  fieldInit(&info.field);

  clearLine(&info, 0);
  for (int i = LENGHT_P_START; i < LENGHT_P_END; ++i) {
    ck_assert_int_eq(info.field[0][i], FREE_SPACE);
  }

  fieldDel(&info.field);
}
END_TEST

START_TEST(CheckDelLine_test) {
  for (int c = 1; c < 5; ++c) {
    GameInfo_t info;
    info.field = NULL;
    info.high_score = 0;
    info.speed = 0;
    info.score = 0;
    int check_score = 0;
    switch (c) {
      case 1:
        check_score = 100;
        break;
      case 2:
        check_score = 300;
        break;
      case 3:
        check_score = 700;
        break;
      case 4:
        check_score = 1500;
        break;
      default:
        break;
    }
    fieldInit(&info.field);
    Shape shape_keeper[SHAPE_COUNT];
    initAllShapes(shape_keeper);
    Shape active = shape_keeper[I];
    active.shape_loc[0].x = 4;
    active.shape_loc[0].y = 17;
    active.shape_loc[1].x = 4;
    active.shape_loc[1].y = 18;
    active.shape_loc[2].x = 4;
    active.shape_loc[2].y = 19;
    active.shape_loc[3].x = 4;
    active.shape_loc[3].y = 20;
    for (int l = 1; l <= c; ++l) {
      for (int i = LENGHT_P_START; i < LENGHT_P_END; ++i) {
        info.field[HEIGHT_P_END - l][i] = SHAPE_PASSIVE;
      }
    }

    CheckDelLine(&info, &active);
    ck_assert_int_eq(info.score, check_score);

    fieldDel(&info.field);
  }
}
END_TEST

Suite *field_tests(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("field_tests");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, getGameInfo_t_test);
  tcase_add_test(tc_core, getVector_test);
  tcase_add_test(tc_core, getSignal_test);
  tcase_add_test(tc_core, fieldInit_test);
  tcase_add_test(tc_core, insertSymbolInFild_test);
  tcase_add_test(tc_core, fieldDel_test);
  tcase_add_test(tc_core, fieldUptime_test);
  tcase_add_test(tc_core, swapLine_test);
  tcase_add_test(tc_core, clearLine_test);
  tcase_add_test(tc_core, CheckDelLine_test);
  suite_add_tcase(s, tc_core);

  return s;
}

int field_test() {
  int fail = 0;
  case_test(field_tests(), &fail);
  return fail;
}