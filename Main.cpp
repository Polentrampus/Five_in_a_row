#include "Game.h"
#include <conio.h> 
#include <iostream> 
#include <stdexcept>

int getPlayerInput()
{
    int x;
    std::cout << "Игрок 1, введите координаты (x y): ";
    std::cin >> x;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Неверный ввод: нечисловое значение.");
    }

    if (x < 0 || x > 14 ) {
        throw std::out_of_range("Ошибка: координаты должны быть от 0 до 14.");
    }
    return x;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Game game;
    int x, y;
    int currentPlayer = PLAYER_2; // Начинаем с игрока X
    game.setPiece(7, 7, PLAYER_2);

    bool gameOver = false;
    while (!gameOver)
    {
        system("cls");

        game.printField();
        int evaluation = game.Evaluation();
        std::cout << "\nОценка позиции: " << evaluation << std::endl;

        bool validMove = false;
        while (!validMove) // Цикл, чтобы заставить игрока вводить валидные координаты
        {
            try
            {
                x = getPlayerInput();
                y = getPlayerInput();

                // Пробуем поставить фишку игрока
                game.setPiece(x, y, PLAYER_1);
                validMove = true; // Ввод и ход игрока завершены успешно

                if (game.isWinningMove(PLAYER_1)) // Проверка на победу игрока
                {
                    game.printField();
                    std::cout << "Игрок 1 (вы) выиграл!" << std::endl;
                    gameOver = true;
                    return 0;
                }
            }
            catch (const std::exception& e)
            {
                // Обработка исключения - сообщаем об ошибке и повторяем ввод
                std::cout << e.what() << std::endl;
                system("cls");

                game.printField();
                int evaluation = game.Evaluation();
                std::cout << "\nОценка позиции: " << evaluation << std::endl;
                std::cout << "\nПожалуйста, попробуйте снова.\n";
            }
        }

        // Ход ИИ (игрок O)
        int bestValue = std::numeric_limits<int>::min();
        int bestMoveX = -1, bestMoveY = -1;

        for (int i = 0; i < SIZE_FIELD; ++i)
        {
            for (int j = 0; j < SIZE_FIELD; ++j)
            {
                if (game.field[i][j] == EMPTY)
                {
                    game.field[i][j] = PLAYER_2; // Сделать ход
                    int moveValue = game.minmax(2, false, std::numeric_limits<int>::max(), std::numeric_limits<int>::min());
                    game.field[i][j] = EMPTY; // Возврат к исходному состоянию

                    if (moveValue > bestValue) // Сравниваем с текущими лучшими значениями
                    {
                        bestValue = moveValue;
                        bestMoveX = i;
                        bestMoveY = j;
                    }
                }
            }
        }
        game.setPiece(bestMoveX, bestMoveY, PLAYER_2);
        if (game.isWinningMove(PLAYER_2))
        {
            game.printField();
            std::cout << "Игрок 2 (ИИ) выиграл!" << std::endl;
            gameOver = true;
            return 0;
        }
        currentPlayer = PLAYER_1; // Смена игроков
        std::cout << "\nТекущее состояние игрового поля:\n";
    }
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