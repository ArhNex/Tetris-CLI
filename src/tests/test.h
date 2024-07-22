#ifndef TEST_H_
#define TEST_H_
#include <check.h>
#include <stdio.h>

#include "../game_lib/tetris/tetris.h"

int main();

int field_test();
int shape_test();
int tetris_test();

void case_test(Suite *s, int *fail);

#endif  // TEST_H_
