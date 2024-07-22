/**
 * @file tetris.h
 * @author jothosge
 * @brief Главный файл библиотеки tetris
 */
#ifndef TETRIS_H_
#define TETRIS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "defines.h"
#include "types.h"
#include "../../gui/cli/ncur_main.h"
#include "field.h"
#include "shape.h"


/**
 * @brief Данная функция является аналогом глобальной статической переменной и
 * используется для определения на ввод подданы клавиши из перечисления
 * UserAction_t
 * @return Возвращает указатель на статичную переменую которая может иметь
 * значения TRUE или FALSE
 */
int *correctInput();

/**
 * @brief Читает данные из файла объявленого в файле defines.h как
 * SCORE_SAVE_FILE_NAME
 * @return Возвращает предыдущий счёт если он был если его не было то 0
 */
int scoreRead();

/**
 * @brief Записывает счёт в файл для дальнейшего чтения при перезапуске игры
 * @param info Данный параметр используется для чтения текущего счёта и
 * сравнения с максимальным для записи в файл
 * @return ничего
 */
void scoreWrite(GameInfo_t info);

/**
 * @brief Данная функция принимает пользовательский ввод затем в зависимости от
 * необходимых действий изменят сигналы или pointXY или заканчивает игру
 * @param action пользовательский ввод
 * @param hold в данной реализации не задействован
 * @return ничего
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief В данной функции формируется GameInfo_t для дальнейшей отрисовки в gui
 * @return возвращает структуру GameInfo_t
 */
GameInfo_t updateCurrentState();

/**
 * @brief Данная функциия реализует логику увеличения уровней, а именно
 * увеличения скорости и уровня
 * @param info передается по указателю так как в нём могут быть изменены
 * следующие параметры score, speed
 * @return ничего
 */
void updateLevel(GameInfo_t *info);

#endif /* TETRIS_H_ */