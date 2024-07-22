/**
 * @file field.h
 * @author jothosge
 * @brief Данный файл хранит все функции для работы с игровым полем
 */

#ifndef FIELD_H_
#define FIELD_H_

#include "tetris.h"

/**
 * @brief Данная функция создаёт внутренне игровое поле
 * @param field переменная переданая по указателю для создания поля
 * @return возвращает ошибку(1) если не выделилась память]
 */
int fieldInit(int*** field);

/**
 * @brief Данная функция удаляет внутренние игровое поле
 * @param field игровое поле из GameInfo_t
 * @return nothing
 */
void fieldDel(int*** field);

/**
 * @brief Обнавляет игровое поле и расположение координат по x y у активной
 * фигуры
 * @param game_field суда передается игровое поле из GameInfo_t
 * @param active_shape подаётся для отрисовки по координатом а затем изменяются
 * и фигуры
 * @param vector от данной структуры зависит куда переместиться активная фигура
 * @return nothing
 */
void fieldUptime(int*** game_field, Shape* active_shape, PointsXY vector);

/**
 * @brief используется при иницилизации поля где вставляются необходимые символы
 * в заранее прописанные места
 * @param h высота то есть y
 * @param l ширина то есть x
 * @param sim символ который будет вставлен
 * @return nothing
 */
void insertSymbolInFild(int h, int l, int* sim);

/**
 * @brief меняет линии местами
 * @param info игровое поля для изменения его внутри
 * @param y1 линия по y
 * @param y2 линия по y другая
 * @return nothing
 */
void swapLine(GameInfo_t* info, int y1, int y2);

/**
 * @brief очищает задонную по y
 * @param info игровое поля которое будет изменено
 * @param y Строка которую необходимо очистить
 * @return nothing
 */
void clearLine(GameInfo_t* info, int y);

/**
 * @brief проверят нужно ли удалить страку и начислить очки после того как
 * активная фигура коснулась другой фигуры или пола
 * @param info игровое поля которое будет изменено
 * @param shape координаты фигуры
 * @return nothing
 */
void CheckDelLine(GameInfo_t* info, const Shape* shape);

/**
 * @brief данная функция используется для статичного хранения структуры
 * GameInfo_t
 * @return возвращает указатель на структуру GameInfo_t
 */
GameInfo_t* getGameInfo_t();

/**
 * @brief данная функция используется для статичного хранения структуры PointsXY
 * для указания направления движения активной фигуры
 * @return возвращает указатель на структуру PointsXY
 */
PointsXY* getVector();

/**
 * @brief данная функция используется для статичного хранения перечесления
 * Signal_t для работы final state machine
 * @return возвращает указатель на статичную переменную Signal_t
 */
Signal_t* getSignal();

#endif /* FIELD_H_ */