#include "Game.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    Game game;
    int x, y;
    int currentPlayer = PLAYER_X; // Начинаем с игрока X
    game.setPiece(7, 7, PLAYER_X);
    while (true) 
    {
        game.printBoard();
        std::cout << "Игрок O, введите координаты (x y): ";
        std::cin >> x >> y;
        game.setPiece(x, y, PLAYER_O);
        if (game.isWinningMove(PLAYER_O)) {
            game.printBoard();
            std::cout << "Игрок X выиграл!" << std::endl;
            return 0;
        }
        currentPlayer = PLAYER_X; // Смена игроков

        // Ход ИИ (игрок O)
        int bestValue = std::numeric_limits<int>::min();
        int bestMoveX = -1, bestMoveY = -1;

        for (int i = 0; i < SIZE_FIELD; ++i) {
            for (int j = 0; j < SIZE_FIELD; ++j) {
                if (game.field[i][j] == EMPTY) {
                    game.field[i][j] = PLAYER_X; // Сделать ход
                    int moveValue = game.minmax(2, false, std::numeric_limits<int>::max(), std::numeric_limits<int>::min());
                    game.field[i][j] = EMPTY; // Возврат к исходному состоянию

                    if (moveValue > bestValue) { // Сравниваем с текущими лучшими значениями
                        bestValue = moveValue;
                        bestMoveX = i;
                        bestMoveY = j;
                    }
                }
            }
        }
        game.setPiece(bestMoveX, bestMoveY, PLAYER_X);
        if (game.isWinningMove(PLAYER_X)) {
            game.printBoard();
            std::cout << "Игрок O (ИИ) выиграл!" << std::endl;
            return 0;
        }
        currentPlayer = PLAYER_O; // Смена игроков
    }
    std::cout << "\nТекущее состояние игрового поля:\n";
    game.printField();

    int evaluation = game.Evaluation();

    std::cout << "\nОценка позиции: " << evaluation << std::endl;

    if (evaluation > 0)
    {
        std::cout << "Преимущество компьютера.\n";
    }
    else if (evaluation < 0)
    {
        std::cout << "Преимущество игрока.\n";
    }
    else
    {
        std::cout << "Позиция сбалансирована.\n";
    }

    return 0;
}