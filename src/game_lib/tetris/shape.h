/**
 * @file shape.h
 * @author jothosge
 * @brief Данный файл хранит все функции для работы с фигурами
 */
#ifndef SHAPE_H_
#define SHAPE_H_

#include "tetris.h"

/**
 * @brief Данная функция заполняет массив shapes стандартными фигурами из игры
 * тетрис
 * @param shapes массив фигур который имеет размер SHAPE_COUNT
 * @see defines.h
 * @return nothing
 * @warning Должен передоваться массив размером в SHAPE_COUNT
 */
void initAllShapes(Shape shapes[SHAPE_COUNT]);

/**
 * @brief Создает фигуру на игравом поле при этом проверяя может ли она быть
 * созданна если же она не создана то игра заканчивается
 * @param game_field игровое поле
 * @param shape активная фигура
 * @param symbol каким символом будет заполнено место где будет фигура
 * @param is_active активна ли данная фигура
 * @param game_over закончить ли игру
 * @return возвращает переменую типа Shape уже провереную
 */
Shape createShape(int** game_field, Shape shape, int symbol, int is_active,
                  int* game_over);

/**
 * @brief данная функция убирает с поля фигуру то есть использует FREE_SPACE
 * define
 * @param game_field игровое поле с которого необходимо удалить фигуру
 * @param shape фигура координаты которой будут использованы для удаления её
 * @see define.h
 * @return nothing
 */
void delShape(int** game_field, Shape shape);

/**
 * @brief данная функция используется для установки новых координат фигуры
 * переданной по указателю
 * @param active_shape необходимо передать активную фигуру затем ей зададутся
 * новые смещённые координаты, которые были смещены vec2 параметром
 * @param vec2 параметр используемый для смещения активной фигуры
 * @return nothing
 */
void setShapeLocation(Shape* active_shape, PointsXY vec2);

/**
 * @brief данная функция провраят следующие координаты фигуры и в зависимости от
 * того что находиться на них может возвращать различные кодовые значения это 0
 * - всё хорошо можно отрисовать как активную фигуру 1 - сталкнулась со стеной
 * необходимо вернуть обратно координаты по x 2 - сталкнулась с полом или с
 * другой фигурай становиться пассивной
 * @param game_field игровое поле
 * @param active_shape активная фигура
 * @param symbl возвращает каким символом необходимо отрисовать координаты
 * @return возвращает коды описание выше
 */
int checkNextSpace(int** game_field, Shape* active_shape, int* symbl);

/**
 * @brief данная функция необходима для работы отрисовки следующей фигуры
 * создает матрицу и рисует по координатам фигуру
 * @param shape фигура которую необходимо превратить в матрицу
 * @return возвращает матрицу для отрисовки
 */
int** castPointsToArrayShape(Shape shape);

/**
 * @brief данная функция освобождает память задействованную для отрисовки
 * следующей фигуры в отведённом поле
 * @param shape матрица фигуры
 * @return nothing
 */
void delShapeFromArray(int*** shape);

/**
 * @brief данная функция берёт массив фигур и рандомным образом возвращает одну
 * из них
 * @param shape_keeper массив доступных фигур
 * @return возвращает одну из фигур
 */
Shape randomizeShape(Shape shape_keeper[SHAPE_COUNT]);

/**
 * @brief Данная функция поворачивает фигуры как в игре тетрис
 * @param field игровое поле
 * @param shape фигура которую необходимо перевернуть
 * @return nothing
 */
void RotateShape(int*** field, Shape* shape);

/**
 * @brief Данная функция переварачивает все фигуры кроме I и O
 * @param field игровое поле
 * @param shape фигура которую необходимо перевернуть
 * @return nothing
 */
void RotateLeftShape(int*** field, Shape* shape);

/**
 * @brief Данная функция опускает фигуу до конца 
 * @param shape фигура которую необходимо перевернуть
 * @param field игровое поле
 * @return nothing
 */
void fallDownShape(Shape* shape_now, int*** field);

#endif /* SHAPE_H_ */