/**
 * @file ncur_main.h
 * @author jothosge
 * @brief Данный файл отвечает за отрисовку графики
 *
 */
#ifndef NCUR_MAIN_H_
#define NCUR_MAIN_H_
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../game_lib/tetris/tetris.h"

/**
 * @brief Функция с которой начинается проект
 * @return возвращает коды ошибок
 */
int main();

/**
 * @brief Рисует стартовый экран
 * @return ничего
 */
void draw_start_screen();

/**
 * @brief Игровой цикл запускаемый сразу после отрисовки начального экрана
 * отвечает за вызов всех необходимых функций
 * @return возвращает коды ошибок
 */
int gameLoop();

/**
 * @brief Данная функция использаутся для отрисовки игрового поля со всей
 * информацией которая берётся из структуры GameInfo_t
 * @param info принемает структуру GameInfo_t
 * @return ничего
 */
void draw_play_screen(GameInfo_t info);
/**
 * @brief Функция используется для отрисовки следующей фигуры. Вызывается из
 * функции draw_play_screen(GameInfo_t info)
 * @param info Использует из структуры info параметр next для отрисовки в
 * игровом поле
 * @return ничего
 */
void draw_next_shape(GameInfo_t info);
/**
 * @brief отрисовывет само игровое поле хранимое в структуре GameInfo_t в
 * параметре field
 * @param info Используется для отрисовки игрового поля
 * @return ничего
 */
void draw_field(GameInfo_t info);
/**
 * @brief Отрисовывает экран окончания игры используя данные из параметра info
 * @param info Необходим для отрисовки поля и другой информации
 * @return ничего
 */
void draw_game_over_screen(GameInfo_t info);

/**
 * @brief данная функция отвечает за работу tick(fps)
 * @param before_now первый раз вызванная
 * @param now нынешнее время
 * @param timer разница при достежения которой будет обнавления поля
 * @return возращает значения типа TRUE or FALSE
 */
int Update(struct timeval before_now, struct timeval now, suseconds_t timer);

#endif /* NCUR_MAIN_H_ */
