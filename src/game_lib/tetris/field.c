#include "tetris.h"

GameInfo_t* getGameInfo_t() {
  static GameInfo_t info;
  return &info;
}

PointsXY* getVector() {
  static PointsXY vector2;
  return &vector2;
}

Signal_t* getSignal() {
  static Signal_t sign;
  return &sign;
}

void insertSymbolInFild(int h, int l, int* sim) {
  if (h == 0 || h == HEIGHT_P_END || l == 0 || l == LENGHT_P_END) {
    if (h == HEIGHT_P_END) {
      *sim = FLOOR;
    } else {
      *sim = WALL;
    }
  } else {
    *sim = FREE_SPACE;
  }
}

int fieldInit(int*** field) {
  int code = 0;
  (*field) = malloc(HEIGHT * sizeof(int*));
  if (*field == NULL) code = 1;
  for (int i = 0; i < HEIGHT && code == 0; ++i) {
    (*field)[i] = malloc(LENGHT * sizeof(int));
    if ((*field)[i] == NULL) code = 1;
  }
  for (int h = 0; h < HEIGHT && code == 0; ++h) {
    for (int l = 0; l < LENGHT; ++l) {
      int sim_inp = ' ';
      insertSymbolInFild(h, l, &sim_inp);
      (*field)[h][l] = sim_inp;
    }
  }
  return code;
}

void fieldDel(int*** field) {
  if (*field == NULL) return;
  for (int i = 0; i < HEIGHT; ++i) {
    free((*field)[i]);
  }
  free(*field);
  *field = NULL;
}

void fieldUptime(int*** game_field, Shape* active_shape, PointsXY vector) {
  int game_over = 0;
  delShape(*game_field, *active_shape);
  setShapeLocation(active_shape, vector);
  int symbl;
  int code = checkNextSpace(*game_field, active_shape, &symbl);
  if (code == 2) {
    vector.x = -vector.x;
    vector.y = -vector.y;
    setShapeLocation(active_shape, vector);
  } else if (code == 1) {
    vector.x = -vector.x;
    vector.y = 0;
    setShapeLocation(active_shape, vector);
  }

  createShape(*game_field, *active_shape, symbl, active_shape->is_active,
              &game_over);
  game_over = game_over + 1;
}

void swapLine(GameInfo_t* info, int y1, int y2) {
  for (int x = LENGHT_P_START; x < LENGHT_P_END; x++) {
    int tmp = info->field[y1][x];
    info->field[y1][x] = info->field[y2][x];
    info->field[y2][x] = tmp;
  }
}

void clearLine(GameInfo_t* info, int y) {
  for (int x = LENGHT_P_START; x < LENGHT_P_END; x++) {
    info->field[y][x] = FREE_SPACE;
  }
}

void CheckDelLine(GameInfo_t* info, const Shape* shape) {
  int prev_y = 0;
  int count_del = 0;
  for (int i = 0; i < COUNT_SHAPE_POINTS; ++i) {
    int fill = 0;

    for (int x = LENGHT_P_START; x < LENGHT_P_END; ++x) {
      if (shape->shape_loc[i].y == prev_y) break;
      if (info->field[shape->shape_loc[i].y][x] == SHAPE_PASSIVE) {
        ++fill;
      }
    }
    if (fill == 10) {
      clearLine(info, shape->shape_loc[i].y);
      for (int y_n = shape->shape_loc[i].y; y_n > HEIGHT_P_START + 1; --y_n) {
        swapLine(info, y_n, y_n - 1);
      }
      ++count_del;
    }
    prev_y = prev_y == 0 ? shape->shape_loc[i].y : prev_y;
  }
  switch (count_del) {
    case 1:
      info->score += 100;
      break;
    case 2:
      info->score += 300;
      break;
    case 3:
      info->score += 700;
      break;
    case 4:
      info->score += 1500;
      break;
    default:
      break;
  }
  if (info->high_score < info->score) info->high_score = info->score;
}
