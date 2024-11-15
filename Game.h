#pragma once
#include <iostream>
#include <string>
#include <vector>

#define SIZE_FIELD  15
const int EMPTY = 0; // Пустая клетка
const int PLAYER_O = 1; // Игрок 1 (пользователь)
const int PLAYER_X = 2; // Игрок 2 (машина)

class Game
{
public:
    // Игровое поле размером 10x10
    int field[SIZE_FIELD][SIZE_FIELD];
    // Конструктор для инициализации поля
    Game();
    // Метод для установки фишки на поле
    void setPiece(int, int, int player);
    // Метод для отображения поля на экране
    void printField() const;
    // Оценочная функция
    int Evaluation() const;
    bool isWinningMove(int player);
    void printBoard();
    int minmax(int depth, bool maximizingPlayer, int alpha, int beta);
private:
    // Вспомогательная функция для оценки линии (строка, столбец или диагональ)
    static int evaluateLine(const int* line, int player);
    // Статическая вспомогательная функция для оценки позиции для конкретного игрока
    static int EvaluationFunction(const int field[SIZE_FIELD][SIZE_FIELD], int this_player, int enemy_player);
    // Функция для оценки комбинации
    static int point(int streak, bool prev_empty, bool post_empty);
    // Функция мин-макс
};