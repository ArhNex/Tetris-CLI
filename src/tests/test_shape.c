#include "test.h"

START_TEST(initAllShapes_test) {
  Shape shape_keeper[SHAPE_COUNT];
  initAllShapes(shape_keeper);
  ck_assert_int_eq(shape_keeper[I].name, I);
  ck_assert_int_eq(shape_keeper[J].name, J);
  ck_assert_int_eq(shape_keeper[O].name, O);
  ck_assert_int_eq(shape_keeper[T].name, T);
  ck_assert_int_eq(shape_keeper[S].name, S);
  ck_assert_int_eq(shape_keeper[Z].name, Z);
}
END_TEST

START_TEST(createShape_test) {
  int **field;
  fieldInit(&field);
  int sym = SHAPE_ACTIVE;
  int game_over = FALSE;
  Shape shape_keeper[SHAPE_COUNT];
  initAllShapes(shape_keeper);
  Shape active = shape_keeper[I];

  Shape ret = createShape(field, active, sym, TRUE, &game_over);
  ck_assert_int_eq(ret.is_active, TRUE);
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    ck_assert_int_eq(field[ret.shape_loc[i].y][ret.shape_loc[i].x],
                     SHAPE_ACTIVE);
    field[ret.shape_loc[i].y][ret.shape_loc[i].x] = SHAPE_PASSIVE;
  }
  ck_assert_int_eq(game_over, FALSE);
  Shape act = shape_keeper[I];
  act = createShape(field, act, sym, TRUE, &game_over);
  ck_assert_int_eq(game_over, TRUE);
  fieldDel(&field);
}
END_TEST

START_TEST(delShape_test) {
  int **field;
  fieldInit(&field);
  int sym = SHAPE_ACTIVE;
  int game_over = FALSE;
  Shape shape_keeper[SHAPE_COUNT];
  initAllShapes(shape_keeper);
  Shape active = shape_keeper[I];

  Shape ret = createShape(field, active, sym, TRUE, &game_over);
  delShape(field, ret);
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    ck_assert_int_eq(field[ret.shape_loc[i].y][ret.shape_loc[i].x], FREE_SPACE);
  }
  fieldDel(&field);
}
END_TEST

START_TEST(setShapeLocation_test) {
  int **field;
  fieldInit(&field);
  int sym = SHAPE_ACTIVE;
  int game_over = FALSE;
  Shape shape_keeper[SHAPE_COUNT];
  initAllShapes(shape_keeper);
  Shape active = shape_keeper[I];

  Shape ret = createShape(field, active, sym, TRUE, &game_over);
  delShape(field, ret);
  PointsXY vec;
  vec.x = 1;
  vec.y = 0;
  setShapeLocation(&ret, vec);
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    ck_assert_int_eq(ret.shape_loc[i].x, active.shape_loc[i].x + 1);
    ck_assert_int_eq(ret.shape_loc[i].y, active.shape_loc[i].y);
  }
  fieldDel(&field);
}
END_TEST

START_TEST(castPointsToArrayShape_test) {
  Shape shape_keeper[SHAPE_COUNT];
  initAllShapes(shape_keeper);
  Shape active = shape_keeper[I];
  int **casted = NULL;
  casted = castPointsToArrayShape(active);
  ck_assert_ptr_nonnull(casted);
  delShapeFromArray(&casted);
}
END_TEST

START_TEST(delShapeFromArray_test) {
  Shape shape_keeper[SHAPE_COUNT];
  initAllShapes(shape_keeper);
  Shape active = shape_keeper[I];
  int **casted = NULL;
  casted = castPointsToArrayShape(active);
  delShapeFromArray(&casted);
  ck_assert_ptr_null(casted);
}
END_TEST

START_TEST(randomizeShape_test) {
  Shape shape_keeper[SHAPE_COUNT];
  initAllShapes(shape_keeper);
  Shape active = randomizeShape(shape_keeper);
  ck_assert_ptr_nonnull(active.shape_loc);
}
END_TEST

START_TEST(RotateShape_test) {
  for (int i = 0; i < SHAPE_COUNT; ++i) {
    GameInfo_t info;
    fieldInit(&info.field);
    int sym = SHAPE_ACTIVE;
    int game_over = FALSE;
    Shape shape_keeper[SHAPE_COUNT];
    initAllShapes(shape_keeper);
    Shape active = shape_keeper[i];

    Shape ret = createShape(info.field, active, sym, TRUE, &game_over);
    PointsXY vec;
    vec.x = 0;
    vec.y = 4;
    fieldUptime(&info.field, &ret, vec);
    RotateShape(&info.field, &ret);
    if (active.name != O) {
      ck_assert_int_ne(active.shape_loc->y, ret.shape_loc->y);
    }

    ck_assert_int_eq(active.name, ret.name);

    fieldDel(&info.field);
  }
}
END_TEST

Suite *shape_tests(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("shape_tests");
  tc_core = tcase_create("core");

  tcase_add_test(tc_core, initAllShapes_test);
  tcase_add_test(tc_core, createShape_test);
  tcase_add_test(tc_core, delShape_test);
  tcase_add_test(tc_core, setShapeLocation_test);
  tcase_add_test(tc_core, castPointsToArrayShape_test);
  tcase_add_test(tc_core, delShapeFromArray_test);
  tcase_add_test(tc_core, randomizeShape_test);
  tcase_add_test(tc_core, RotateShape_test);
  suite_add_tcase(s, tc_core);

  return s;
}

int shape_test() {
  int fail = 0;
  case_test(shape_tests(), &fail);
  return fail;
}