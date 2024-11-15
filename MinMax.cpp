#include "Game.h"

bool isInBounds(int x, int y) {
    return x >= 0 && x < SIZE_FIELD && y >= 0 && y < SIZE_FIELD;
}

// Функция для генерации спиральных координат
void Game::SpiralMoves(int& x, int& y) {
    int centerX = SIZE_FIELD / 2;
    int centerY = SIZE_FIELD / 2;

    x = centerX;
    y = centerY;

    // Проходим по уровням
    for (int radius = 1; radius < SIZE_FIELD; ++radius) {
        // Перемещение вверх, вправо, вниз и влево
        for (int i = 0; i < radius; ++i) { // Вверх
            y = centerY + i; // Двигаемся вверх по прямой
            x = centerX - radius; // Устанавливаем x для левой части круга
            if (isInBounds(x, y) && field[x][y] == EMPTY);
        }
        for (int i = 0; i < radius; ++i) { // Вправо
            x = centerX + i; // Двигаемся по правой части
            y = centerY + radius;
            if (isInBounds(x, y) && field[x][y] == EMPTY);
        }
        for (int i = 0; i < radius; ++i) { // Вниз
            x = centerX + radius; // Устанавливаем x для нижней части круга
            y = centerY - i;
            if (isInBounds(x, y) && field[x][y] == EMPTY);
        }
        for (int i = 0; i < radius; ++i) { // Влево
            x = centerX - i; // Двигаемся по левой части
            y = centerY - radius;
            if (isInBounds(x, y) && field[x][y] == EMPTY);
        }
    }
}

int Game::minmax(int depth, bool maximizingPlayer, int alpha, int beta) {
    if (isWinningMove(PLAYER_1)) return -10000 + depth; // Победа для минимизирующего игрока
    if (isWinningMove(PLAYER_2)) return 10000 - depth;  // Победа для максимизирующего игрока
    if (depth == 0) return Evaluation(); // Достигли глубины или завершение

    int maxEval = std::numeric_limits<int>::min();
    int minEval = std::numeric_limits<int>::max();

    // Генерация ходов в спиральном порядке
    int x, y;

    // Перебор всех возможных ходов
    for (int radius = 0; radius < SIZE_FIELD; ++radius) {
        for (int dir = 0; dir < 4; ++dir) {
            switch (dir) {
            case 0: // Вверх
                x = SIZE_FIELD / 2 - radius;
                y = SIZE_FIELD / 2 + radius;
                break;
            case 1: // Вправо
                x = SIZE_FIELD / 2 + radius;
                y = SIZE_FIELD / 2 + radius;
                break;
            case 2: // Вниз
                x = SIZE_FIELD / 2 + radius;
                y = SIZE_FIELD / 2 - radius;
                break;
            case 3: // Влево
                x = SIZE_FIELD / 2 - radius;
                y = SIZE_FIELD / 2 - radius;
                break;
            }

            if (isInBounds(x, y) && field[x][y] == EMPTY) {
                if (maximizingPlayer) {
                    field[x][y] = PLAYER_2; // Игрок делает ход
                    int eval = minmax(depth - 1, false, alpha, beta);
                    field[x][y] = EMPTY; // Возврат к исходному состоянию
                    maxEval = std::max(maxEval, eval);
                    alpha = std::max(alpha, eval);
                    if (beta <= alpha) break; // Альфа-бета отсечение
                }
                else {
                    field[x][y] = PLAYER_1; 
                    int eval = minmax(depth - 1, true, alpha, beta);
                    field[x][y] = EMPTY;
                    minEval = std::min(minEval, eval);
                    beta = std::min(beta, eval);
                    if (beta <= alpha) break;
                }
            }
        }
    }

    return maximizingPlayer ? maxEval : minEval;
}

