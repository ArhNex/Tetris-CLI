/**
 * @file types.h
 * @author jothosge
 * @brief Данный файл хранит в себе все типы данных которые были использованы
 * для написания библиотеки tetris
 */

#ifndef TYPES_H_
#define TYPES_H_

#include "defines.h"

/**
 * @brief Данное перечесление хранит в себе имена фигур которые могут быть в
 * игре тетрис имена взяты из данной статьи
 * @see https://en.wikipedia.org/wiki/Tetromino
 */
typedef enum { I, O, J, L, S, T, Z } NameShape;

/**
 * @brief Данная структура хранит в себе координаты по x и y, необходимы для
 * работы логики фигур и поля
 * @warning x и y имеют ограничения на значения
 */
typedef struct {
  int x;  ///< Может быть с 1 по 11
  int y;  ///< Может быть с 1 по 21
} PointsXY;

/**
 * @brief Данная структура хранит информации о фигурах
 */
typedef struct {
  PointsXY shape_loc[COUNT_SHAPE_POINTS];  ///< Массив координат на которых
                                           ///< распалагается фигура
  NameShape name;  ///< Имя данной фигуры
  int is_active;  ///< Может принимать значения 1 или 0 необхадима для
                  ///< определения активна ли данная фигура или нет
} Shape;

/**
 * @brief обязательное перечесление в данном проекте используется для храниния
 * клавишь которые будут задейственны в игре
 */
typedef enum {
  Start = 'p',
  Pause = 'e',
  Terminate = 'q',
  Left = 'a',
  Right = 'd',
  Up = 'w',
  Down = 's',
  Action = ' '
} UserAction_t;

/**
 * @brief Перечесления используемая для формирования сигналов чтобы было
 * возможно реализовать логику конечных автоматов
 */
typedef enum { Nothing, Rotate, Restart, S_Pause, GameOver, FallDown } Signal_t;

/**
 * @brief Данная структура является обязательной и хранит в себе всю информацию
 * для отрисовки в различных интерфейсах игру
 */
typedef struct {
  int **field;     ///< Игровое поле
  int **next;      ///< Следующая фигура для спавна
  int score;       ///< Текущий счёт
  int high_score;  ///< Наибольший счёт за всё время
  int level;       ///< текущий уровень
  int speed;       ///< скорость
  int pause;       ///< Пауза
} GameInfo_t;

#endif /* TYPES_H_ */