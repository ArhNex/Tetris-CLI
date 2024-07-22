#include "tetris.h"

void initAllShapes(Shape shapes[SHAPE_COUNT]) {
  for (int i = 0; i < SHAPE_COUNT; ++i) {
    shapes[i].name = (NameShape)i;
    shapes[i].is_active = FALSE;
  }
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i)
    shapes[I].shape_loc[i].x = i + 1 + CREATE_COR_X;
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) shapes[I].shape_loc[i].y = 1;
  shapes[O].shape_loc[0].x = 1 + CREATE_COR_X;
  shapes[O].shape_loc[1].x = 1 + CREATE_COR_X;
  shapes[O].shape_loc[2].x = 2 + CREATE_COR_X;
  shapes[O].shape_loc[3].x = 2 + CREATE_COR_X;

  shapes[O].shape_loc[0].y = 1;
  shapes[O].shape_loc[1].y = 2;
  shapes[O].shape_loc[2].y = 1;
  shapes[O].shape_loc[3].y = 2;

  shapes[L].shape_loc[0].x = 3 + CREATE_COR_X;
  shapes[L].shape_loc[0].y = 1;

  shapes[J].shape_loc[0].x = 1 + CREATE_COR_X;
  shapes[J].shape_loc[0].y = 1;
  for (int i = 1; i < COUNT_SHAPE_POINTS; ++i) {
    shapes[J].shape_loc[i].y = 2;
    shapes[J].shape_loc[i].x = i + CREATE_COR_X;
    shapes[L].shape_loc[i].x = i + CREATE_COR_X;
    shapes[L].shape_loc[i].y = 2;
  }

  shapes[Z].shape_loc[0].x = 1 + CREATE_COR_X;
  shapes[Z].shape_loc[1].x = 2 + CREATE_COR_X;
  shapes[Z].shape_loc[2].x = 2 + CREATE_COR_X;
  shapes[Z].shape_loc[3].x = 3 + CREATE_COR_X;

  shapes[S].shape_loc[0].x = 1 + CREATE_COR_X;
  shapes[S].shape_loc[1].x = 2 + CREATE_COR_X;
  shapes[S].shape_loc[2].x = 2 + CREATE_COR_X;
  shapes[S].shape_loc[3].x = 3 + CREATE_COR_X;
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    shapes[S].shape_loc[i].y = i < 2 ? 2 : 1;
    shapes[Z].shape_loc[i].y = i >= 2 ? 2 : 1;
  }
  shapes[T].shape_loc[3].x = 2 + CREATE_COR_X;
  shapes[T].shape_loc[3].y = 1;
  for (int i = 0; i < COUNT_SHAPE_POINTS - 1; ++i) {
    shapes[T].shape_loc[i].x = i + 1 + CREATE_COR_X;
    shapes[T].shape_loc[i].y = 2;
  }
}

Shape createShape(int** game_field, Shape shape, int symbol, int is_active,
                  int* game_over) {
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    shape.is_active = is_active;
    if (game_field[shape.shape_loc[i].y][shape.shape_loc[i].x] ==
        SHAPE_PASSIVE) {
      *game_over = TRUE;
      break;
    }

    game_field[shape.shape_loc[i].y][shape.shape_loc[i].x] = symbol;
  }
  return shape;
}

void delShape(int** game_field, Shape shape) {
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    shape.is_active = TRUE;
    game_field[shape.shape_loc[i].y][shape.shape_loc[i].x] = FREE_SPACE;
  }
}

void setShapeLocation(Shape* active_shape, PointsXY vec2) {
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    active_shape->shape_loc[i].x += vec2.x;
    active_shape->shape_loc[i].y += vec2.y;
  }
}

int checkNextSpace(int** game_field, Shape* active_shape, int* symbl) {
  int code = 0;
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    if (game_field[active_shape->shape_loc[i].y]
                  [active_shape->shape_loc[i].x] == FREE_SPACE) {
      *symbl = SHAPE_ACTIVE;
    } else if (game_field[active_shape->shape_loc[i].y]
                         [active_shape->shape_loc[i].x] == WALL) {
      *symbl = SHAPE_ACTIVE;
      code = 1;
    } else {
      active_shape->is_active = FALSE;
      *symbl = SHAPE_PASSIVE;
      code = 2;
      break;
    }
  }
  return code;
}

int** castPointsToArrayShape(Shape shape) {
  int** shape_trans = malloc(2 * sizeof(int*));
  for (int i = 0; i < 2; ++i) {
    shape_trans[i] = malloc(4 * sizeof(int));
  }

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 4; ++j) {
      shape_trans[i][j] = FREE_SPACE;
    }
  }

  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    shape_trans[shape.shape_loc[i].y - 1]
               [shape.shape_loc[i].x - CREATE_COR_X - 1] = SHAPE_PASSIVE;
  }
  return shape_trans;
}

void delShapeFromArray(int*** shape) {
  for (int i = 0; i < 2; ++i) {
    free((*shape)[i]);
  }
  free(*shape);
  *shape = NULL;
}

Shape randomizeShape(Shape shape_keeper[SHAPE_COUNT]) {
  srand(time(0));
  Shape shape = shape_keeper[rand() % 6 + rand() % 2];
  return shape;
}

void RotateShape(int*** field, Shape* shape) {
  if (shape->name == O)
    return;
  else if (shape->name == I) {
    Shape tmp_s = *shape;
    delShape(*field, *shape);
    for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
      int newX = shape->shape_loc[i].y - shape->shape_loc[0].y;
      int newY = shape->shape_loc[i].x - shape->shape_loc[0].x;
      shape->shape_loc[i].x = shape->shape_loc[0].x + newX;
      shape->shape_loc[i].y = shape->shape_loc[0].y + newY;
    }
    int symbl;
    int code = checkNextSpace(*field, shape, &symbl);
    if (code != 0) {
      *shape = tmp_s;
    }
    createShape(*field, *shape, SHAPE_ACTIVE, TRUE, FALSE);
  } else {
    RotateLeftShape(field, shape);
  }
}

void RotateLeftShape(int*** field, Shape* shape) {
  Shape tmp_s = *shape;
  delShape(*field, *shape);
  PointsXY tmp = shape->name == T ? shape->shape_loc[1] : shape->shape_loc[2];

  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    shape->shape_loc[i].x -= tmp.x;
    shape->shape_loc[i].y -= tmp.y;
  }
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    int tmp_x = shape->shape_loc[i].x;
    shape->shape_loc[i].x = -shape->shape_loc[i].y;
    shape->shape_loc[i].y = tmp_x;
  }
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    shape->shape_loc[i].x += tmp.x;
    shape->shape_loc[i].y += tmp.y;
  }
  int symbl;
  int code = checkNextSpace(*field, shape, &symbl);
  if (code != 0) {
    *shape = tmp_s;
  }
  createShape(*field, *shape, symbl, TRUE, FALSE);
}

void fallDownShape(Shape* shape_now, int*** field) {
  Signal_t* sign = getSignal();
  if (*sign == FallDown) {
    *sign = Nothing;
    PointsXY vec2;
    vec2.x = 0;
    vec2.y = 1;
    while (shape_now->is_active == TRUE) {
      fieldUptime(field, shape_now, vec2);
    }
  }
}
