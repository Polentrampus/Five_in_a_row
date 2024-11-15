#include "Game.h"

Game::Game()
{
    for (int i = 0; i < SIZE_FIELD; ++i)
    {
        for (int j = 0; j < SIZE_FIELD; ++j)
        {
            field[i][j] = 0;
        }
    }
}

void Game::setPiece(int i, int j, int player)
{
    if (i >= 0 && i < SIZE_FIELD && j >= 0 && j < SIZE_FIELD)
    {
        if (field[i][j] == EMPTY)
        {
            field[i][j] = player;
            std::cout << "Фишка игрока " << player << " установлена на (" << i << ", " << j << ")\n";
        }
        else
        {
            std::cout << "Клетка (" << i << ", " << j << ") уже занята.\n";
        }
    }
    else
    {
        std::cout << "Некорректные координаты: (" << i << ", " << j << ")\n";
    }
}

void Game::printField() const
{
    std::cout << "    ";
    for (int j = 0; j < SIZE_FIELD; ++j) { std::cout << " " << j; }

    std::cout << std::endl;

    for (int i = 0; i < SIZE_FIELD; ++i)
    {
        if (i >= 10) { std::cout << " " << i << " |"; }
        else { std::cout << " " << i << "  |"; }
        for (int j = 0; j < SIZE_FIELD; ++j)
        {
            if (field[i][j] == 1)
            {
                std::cout << "1|";         // Фишка игрока
            }
            else if (field[i][j] == 2)
            {
                std::cout << "2|";         // Фишка компьютера
            }
            else
            {
                std::cout << " |";         // Пустая клетка
            }
        }
        std::cout << "\n";
    }
}

int Game::Evaluation() const
{
    int evalComputer = EvaluationFunction(field, 2, 1);         // Оценка для компьютера
    int evalPlayer = EvaluationFunction(field, 1, 2);           // Оценка для игрока
    return evalComputer - evalPlayer;                          // Разница оценок
}

int Game::evaluateLine(const int* line, int player)
{
    int sum = 0;
    int streak = 0; //полоса
    bool prev_empty = false;
    bool post_empty = false;

    for (int i = 0; i < SIZE_FIELD; ++i)
    {
        if (line[i] == player)
        {
            if (streak == 0)
            {
                prev_empty = (i > 0 && line[i - 1] == 0);     // Проверяем пустую клетку перед серией
                streak = 1;
            }
            else
            {
                streak++;
            }
        }
        else
        {
            if (streak > 0)
            {
                post_empty = (line[i] == 0);                  // Проверяем пустую клетку после серии
                sum += point(streak, prev_empty, post_empty); // Оцениваем текущую серию
                streak = 0;
                prev_empty = false;
                post_empty = false;
            }
        }
    }

    // Обработка серии в конце линии
    if (streak > 0)
    {
        post_empty = false;                                   // Нет клетки после последней фишки
        sum += point(streak, prev_empty, post_empty);         // Оцениваем последнюю серию
    }

    return sum;
}

int Game::EvaluationFunction(const int field[SIZE_FIELD][SIZE_FIELD], int this_player, int enemy_player)
{
    int sum = 0;

    // Обработка строк
    for (int i = 0; i < SIZE_FIELD; ++i)
    {
        int row[SIZE_FIELD];
        for (int j = 0; j < SIZE_FIELD; ++j)
        {
            row[j] = field[i][j];                             // Копируем строку
        }

        int lineSum = evaluateLine(row, this_player);         // Оцениваем строку
        sum += lineSum;
    }

    // Обработка столбцов
    for (int j = 0; j < SIZE_FIELD; ++j)
    {
        int column[SIZE_FIELD]; //колонка
        for (int i = 0; i < SIZE_FIELD; ++i)
        {
            column[i] = field[i][j];                          // Копируем столбец
        }
        
        int lineSum = evaluateLine(column, this_player);      // Оцениваем столбец
        sum += lineSum;
    }

    // Обработка диагоналей (левый низ -> правый верх)
    for (int k = 0; k < SIZE_FIELD * 2 + 1; k++)
    {
        int diagonal[SIZE_FIELD * 2 + 1];
        int size = 0;
        for (int i = 0; i < SIZE_FIELD; i++)
        {
            int j = k - i;
            if (j >= 0 && j < SIZE_FIELD)
            {
                diagonal[size] = field[i][j];               // Копируем диагональ
                size++;
            }
        }

        if (size < 5)
            continue;                                        // Пропускаем короткие диагонали

        int lineSum = evaluateLine(diagonal, this_player);   // Оцениваем диагональ
        sum += lineSum;
    }

    // Обработка диагоналей (правый низ -> левый верх)
    for (int k = 0; k < SIZE_FIELD*2+1; k++)
    {
        int diagonal[SIZE_FIELD * 2 + 1];
        int size = 0;
        for (int i = 0; i < SIZE_FIELD; i++)
        {
            int j = k + i - (SIZE_FIELD - 1);
            if (j >= 0 && j < SIZE_FIELD)
            {
                diagonal[size] = field[i][j];              // Копируем диагональ
                size++;
            }
        }

        if (size < 5)
            continue;                                        // Пропускаем короткие диагонали

        int lineSum = evaluateLine(diagonal, this_player);   // Оцениваем диагональ
        sum += lineSum;
    }
    return sum;
}

int Game::point(int streak, bool prev_empty, bool post_empty)
{
    if (streak >= 5)
    {
        return 10000; // Победа!!!!!
    }
    else if (streak == 4)
    {
        if (prev_empty && post_empty)
            return 5000; // Открытая четверка
        else if (prev_empty || post_empty)
            return 1000; // Полуоткрытая четверка
        else
            return 0; // Закрытая четверка
    }
    else if (streak == 3)
    {
        if (prev_empty && post_empty)
            return 500; // Открытая тройка
        else if (prev_empty || post_empty)
            return 100; // Полуоткрытая тройка
        else
            return 0; //закрытая тройка
    }
    else if (streak == 2)
    {
        if (prev_empty && post_empty)
            return 50; // Открытая двойка
        else if (prev_empty || post_empty)
            return 10; // Полуоткрытая двойка
        else
            return 0; // Закрытая двойка
    }
    else if (streak == 1)
    {
        if (prev_empty && post_empty)
            return 2; // Открытая единица
        else if (prev_empty || post_empty)
            return 1; // Полуоткрытая единица
        else
            return 0; // Закрытая единица
    }
    else
    {
        return 0; // Нет значимой комбинации
    }
}

bool Game::isWinningMove(int this_player)
{
    int sum = 0;

    for (int i = 0; i < SIZE_FIELD; ++i)
    {
        int row[SIZE_FIELD];
        for (int j = 0; j < SIZE_FIELD; ++j)
        {
            row[j] = field[i][j];                             // Копируем строку
        }
        int lineSum = evaluateLine(row, this_player);         // Оцениваем строку
        sum += lineSum;
    }

    for (int j = 0; j < SIZE_FIELD; ++j)
    {
        int column[SIZE_FIELD];
        for (int i = 0; i < SIZE_FIELD; ++i)
        {
            column[i] = field[i][j];                          // Копируем столбец
        }
        int lineSum = evaluateLine(column, this_player);      // Оцениваем столбец
        sum += lineSum;
    }

    // Обработка диагоналей (левый низ -> правый верх)
    for (int k = 0; k < SIZE_FIELD * 2 + 1; k++)
    {
        int diagonal[SIZE_FIELD * 2 + 1];
        int size = 0;
        for (int i = 0; i < SIZE_FIELD; i++)
        {
            int j = k - i;
            if (j >= 0 && j < SIZE_FIELD)
            {
                diagonal[size] = field[i][j];               // Копируем диагональ
                size++;
            }
        }

        if (size < 5)
            continue;                                        // Пропускаем короткие диагонали

        int lineSum = evaluateLine(diagonal, this_player);   // Оцениваем диагональ
        sum += lineSum;
    }

    // Обработка диагоналей (правый низ -> левый верх)
    for (int k = 0; k < SIZE_FIELD * 2 + 1; k++)
    {
        int diagonal[SIZE_FIELD * 2 + 1];
        int size = 0;
        for (int i = 0; i < SIZE_FIELD; i++)
        {
            int j = k + i - (SIZE_FIELD - 1);
            if (j >= 0 && j < SIZE_FIELD)
            {
                diagonal[size] = field[i][j];              // Копируем диагональ
                size++;
            }
        }

        if (size < 5)
            continue;                                        // Пропускаем короткие диагонали

        int lineSum = evaluateLine(diagonal, this_player);   // Оцениваем диагональ
        sum += lineSum;
    }
    if (sum >= 10000){return true;}
    return false;
}