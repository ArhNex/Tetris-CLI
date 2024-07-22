#include "tetris.h"

int* correctInput() {
  static int is_correct = FALSE;
  return &is_correct;
}

void userInput(UserAction_t action, bool hold) {
  hold = hold + 1;
  static int on_pause = FALSE;
  PointsXY* vec2 = getVector();
  Signal_t* sign = getSignal();
  *sign = Nothing;
  int* is_correct = correctInput();
  *is_correct = TRUE;
  switch (action) {
    case Start:
      *sign = Restart;
      break;
    case Left:
      vec2->y = 0;
      vec2->x = -1;
      break;
    case Right:
      vec2->y = 0;
      vec2->x = 1;
      break;
    case Pause:
      vec2->y = 0;
      vec2->x = 0;
      on_pause = on_pause == 1 ? 0 : 1;
      *sign = on_pause ? S_Pause : Nothing;
      break;
    case Terminate:
      vec2->y = 0;
      vec2->x = 0;
      endwin();
      fieldDel(&(getGameInfo_t()->field));
      exit(0);
      break;
    case Down:
      vec2->y = 0;
      vec2->x = 0;
      *sign = FallDown;
      break;
    case Action:
      vec2->y = 0;
      vec2->x = 0;
      *sign = Rotate;
      break;
    default:
      *is_correct = FALSE;
      break;
  }
}

int scoreRead() {
  FILE* score_f = NULL;
  int score = 0;
  score_f = fopen(SCORE_SAVE_FILE_NAME, "r");
  char str[MAX_NUMBER_STR];
  if (score_f != NULL) {
    char* s = fgets(str, 100, score_f);
    s = s + 1;
    score = atoi(str);
    fclose(score_f);
  }
  return score;
}

void scoreWrite(GameInfo_t info) {
  if (info.high_score <= info.score) {
    FILE* score_f = NULL;
    score_f = fopen(SCORE_SAVE_FILE_NAME, "w");
    if (score_f != NULL) {
      fprintf(score_f, "%d", info.score);
    }
    fclose(score_f);
  }
}

GameInfo_t updateCurrentState() {
  int code = 0;
  static int is_game = 0;
  static Shape shape_keeper[SHAPE_COUNT];
  static Shape now_shape;
  static Shape next_shape;
  GameInfo_t* now = getGameInfo_t();
  Signal_t* sign = getSignal();
  PointsXY* vec2 = getVector();
  now->pause = *sign == S_Pause;
  int game_over = FALSE;
  if (*sign == Restart && is_game == 1) {
    *sign = Nothing;
    fieldDel(&now->field);
    now->score = 0;
    is_game = 0;
  }
  if (is_game == 0) {
    *sign = Nothing;
    vec2->x = 0;
    vec2->y = 1;
    is_game = 1;
    now->speed = DEFAULT_DELAY;
    now->high_score = scoreRead();
    code = fieldInit(&now->field);
    initAllShapes(shape_keeper);
    now_shape = randomizeShape(shape_keeper);
    next_shape = randomizeShape(shape_keeper);
    now->next = castPointsToArrayShape(next_shape);
    if (code) userInput(Terminate, FALSE);
    now_shape =
        createShape(now->field, now_shape, SHAPE_ACTIVE, TRUE, &game_over);
  }
  if (*sign == Rotate) {
    *sign = Nothing;
    RotateShape(&now->field, &now_shape);
  }
  fieldUptime(&now->field, &now_shape, *vec2);
  fallDownShape(&now_shape, &now->field);
  if (now_shape.is_active == false) {
    CheckDelLine(now, &now_shape);
    updateLevel(now);
    now_shape =
        createShape(now->field, next_shape, SHAPE_ACTIVE, TRUE, &game_over);
    if (game_over) {
      scoreWrite(*now);
      *sign = GameOver;
    }
    next_shape = randomizeShape(shape_keeper);
    delShapeFromArray(&now->next);
    now->next = castPointsToArrayShape(next_shape);
  }
  return *now;
}

void updateLevel(GameInfo_t* info) {
  int tmp;
  tmp = info->score / 600;
  if (tmp != info->level && info->level != 9) {
    for (int i = info->level; i < tmp; ++i) {
      info->level += 1;
      info->speed -= DECRISE_DELAY;
    }
  }
}