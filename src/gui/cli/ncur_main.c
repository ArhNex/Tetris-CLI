#include "ncur_main.h"

int main() {
  initscr();
  curs_set(0);
  draw_start_screen();
  endwin();

  return 0;
}

void draw_start_screen() {
  WINDOW *win_start = newwin(20, 20, 0, 0);
  refresh();
  mvprintw(5, 10, "Wellcome to the Tetris");
  mvprintw(6, 5, "Press any button to start the game!");
  wrefresh(win_start);
  getch();
  clear();
  userInput(Start, 0);
  gameLoop();
}

int gameLoop() {
  int code_return = 0;
  struct timeval before_now, now;
  static suseconds_t timer = DEFAULT_DELAY;
  int usr_inp;
  timeout(1);
  gettimeofday(&before_now, NULL);
  GameInfo_t info;
  do {
    if (*getSignal() == GameOver) {
      draw_game_over_screen(info);
    }
    PointsXY *vec2 = getVector();
    vec2->x = 0;
    vec2->y = 1;
    if ((usr_inp = getch()) != ERR) {
      userInput(usr_inp, FALSE);
      if (*correctInput()) {
        info = updateCurrentState();
        draw_play_screen(info);
      }
    }
    gettimeofday(&now, NULL);
    if (Update(before_now, now, timer)) {
      info = updateCurrentState();
      draw_play_screen(info);
      timer = info.speed;
      gettimeofday(&before_now, NULL);
    }
  } while (TRUE);
  return code_return;
}

int Update(struct timeval before_now, struct timeval now, suseconds_t timer) {
  return ((suseconds_t)(now.tv_sec * 1000000 + now.tv_usec) -
          ((suseconds_t)before_now.tv_sec * 1000000 + before_now.tv_usec)) >
         timer;
}

void draw_next_shape(GameInfo_t info) {
  for (int y = 0; y < 2; ++y) {
    for (int x = 0, x2 = 0; x < 4; ++x, ++x2) {
      mvprintw(
          3 + y, X_POSITION_DRAW + x + x2, "%c ",
          info.next[y][x] == SHAPE_PASSIVE ? SHAPE_ACTIVE : info.next[y][x]);
    }
  }
}

void draw_field(GameInfo_t info) {
  for (int y = 0; y < HEIGHT; ++y) {
    if (y == 0 || y == 21) continue;
    for (int x = 0, x2 = 0; x < LENGHT; ++x, ++x2) {
      if (x == 0 || x == 11) continue;
      if (info.field[y][x] == SHAPE_ACTIVE ||
          info.field[y][x] == SHAPE_PASSIVE) {
        mvprintw(y, x2 + x, "%c ", SHAPE_ACTIVE);
      } else {
        mvprintw(y, x2 + x, "%c ", '.');
      }
    }
  }
}

void draw_play_screen(GameInfo_t info) {
  WINDOW *win = newwin(20, 20, 0, 0);
  clear();
  mvprintw(2, X_POSITION_DRAW, "Next shape:");
  mvprintw(5, X_POSITION_DRAW, "Score: %d", info.score);
  mvprintw(6, X_POSITION_DRAW, "Max Score: %d", info.high_score);
  mvprintw(7, X_POSITION_DRAW, "Level: %d", info.level + 1);
  mvprintw(22, 0, "Game controle:");
  mvprintw(23, 0,
           "Start: %c, Pouse: %c, Terminate: %c, Left: %c, \n"
           "Right: %c, Up: %c, Down: %c, Action: space",
           Start, Pause, Terminate, Left, Right, Up, Down);
  draw_next_shape(info);
  draw_field(info);
  if (info.pause) {
    mvprintw(0, X_POSITION_DRAW, "ON PAUSE)");
    timeout(TIMEOUT_OWN);
    int ch = getch();
    timeout(1);
    userInput(ch, 0);
  }
  wrefresh(win);
}

void draw_game_over_screen(GameInfo_t info) {
  WINDOW *win_end = newwin(20, 20, 0, 0);
  clear();
  draw_field(info);
  mvprintw(2, 22, "Game Over)");
  if (info.score >= info.high_score) {
    mvprintw(3, 22, "You achive new max score:");
  } else {
    mvprintw(3, 22, "Your score:");
    mvprintw(5, 22, "Max score:");
    mvprintw(6, 22, "%d", info.high_score);
  }
  mvprintw(4, 22, "%d", info.score);
  mvprintw(22, 0, "Press button to quite.");
  timeout(TIMEOUT_OWN);
  getch();
  userInput(Terminate, 0);

  wrefresh(win_end);
}