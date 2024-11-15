#pragma once
#include <iostream>
#include <string>
#define SIZE_FIELD  15 

class Game
{
public:
    int field[SIZE_FIELD][SIZE_FIELD];// Игровое поле размером 10x10

    // Конструктор для инициализации поля
    Game()
    {
        for (int i = 0; i < SIZE_FIELD; ++i)
        {
            for (int j = 0; j < SIZE_FIELD; ++j)
            {
                field[i][j] = 0;
            }
        }
    }

    // Метод для установки фишки на поле
    void setPiece(int i, int j, int player)
    {
        if (i >= 0 && i < SIZE_FIELD && j >= 0 && j < SIZE_FIELD)
        {
            if (field[i][j] == 0)
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

    // Метод для отображения поля на экране
    void printField() const
    {
        std::cout << "   ";
        for (int j = 0; j < SIZE_FIELD; ++j)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < SIZE_FIELD; ++i)
        {
            std::cout << " " << i << "  |";
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

    // Оценочная функция
    int Evaluation() const
    {
        std::cout << "\nВычисление оценки позиции для компьютера:\n";
        int evalComputer = EvaluationFunction(field, 2, 1);         // Оценка для компьютера
        std::cout << "Оценка компьютера: " << evalComputer << "\n";

        std::cout << "Вычисление оценки позиции для игрока:\n";
        int evalPlayer = EvaluationFunction(field, 1, 2);           // Оценка для игрока
        std::cout << "Оценка игрока: " << evalPlayer << "\n";

        std::cout << "Общая оценка позиции (Компьютер - Игрок): " << (evalComputer - evalPlayer) << "\n\n";

        return evalComputer - evalPlayer;                          // Разница оценок
    }

private:
    // Вспомогательная функция для оценки линии (строка, столбец или диагональ)
    static int evaluateLine(const int* line, int player)
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

    // Статическая вспомогательная функция для оценки позиции для конкретного игрока
    static int EvaluationFunction(const int field[SIZE_FIELD][SIZE_FIELD], int this_player, int enemy_player)
    {
        int sum = 0;

        // Обработка строк
        std::cout << "Обработка строк:\n";
        for (int i = 0; i < SIZE_FIELD; ++i)
        {
            int row[SIZE_FIELD];
            for (int j = 0; j < SIZE_FIELD; ++j)
            {
                row[j] = field[i][j];                             // Копируем строку
            }
            std::cout << "Строка " << i << ": ";
            for (int j = 0; j < SIZE_FIELD; ++j)
            {
                std::cout << row[j] << " ";                       // Выводим строку
            }
            int lineSum = evaluateLine(row, this_player);         // Оцениваем строку
            sum += lineSum;
            std::cout << "| Текущая сумма: " << sum << "\n";
        }

        // Обработка столбцов
        std::cout << "\nОбработка столбцов:\n";
        for (int j = 0; j < SIZE_FIELD; ++j)
        {
            int column[SIZE_FIELD]; //колонка
            for (int i = 0; i < SIZE_FIELD; ++i)
            {
                column[i] = field[i][j];                          // Копируем столбец
            }
            std::cout << "Столбец " << j << ": ";
            for (int i = 0; i < SIZE_FIELD; ++i)
            {
                std::cout << column[i] << " ";                    // Выводим столбец
            }
            int lineSum = evaluateLine(column, this_player);      // Оцениваем столбец
            sum += lineSum;
            std::cout << "| Текущая сумма: " << sum << "\n";
        }

        // Обработка диагоналей (левый низ -> правый верх)
        std::cout << "\nОбработка диагоналей (левый низ -> правый верх):\n";
        for (int k = 0; k < SIZE_FIELD; ++k)
        {
            int diagonal[SIZE_FIELD];
            int size = 0;
            for (int i = 0; i < SIZE_FIELD; ++i)
            {
                int j = i + k;
                if (j >= 0 && j < SIZE_FIELD)
                {
                    diagonal[size++] = field[i][j];               // Копируем диагональ
                }
            }

            if (size < 5)
                continue;                                        // Пропускаем короткие диагонали

            std::cout << "Диагональ " << k << ": ";
            for (int i = 0; i < size; ++i)
            {
                std::cout << diagonal[i] << " ";                 // Выводим диагональ
            }
            int lineSum = evaluateLine(diagonal, this_player);   // Оцениваем диагональ
            sum += lineSum;
            std::cout << "| Текущая сумма: " << sum << "\n";
        }

        // Обработка диагоналей (левый верх -> правый низ)
        std::cout << "\nОбработка диагоналей (левый верх -> правый низ):\n";
        for (int k = 0; k < SIZE_FIELD; ++k)
        {
            int diagonal[SIZE_FIELD];
            int size = 0;
            for (int i = 0; i < SIZE_FIELD; ++i)
            {
                int j = k - i;
                if (j >= 0 && j < SIZE_FIELD)
                {
                    diagonal[size++] = field[i][j];              // Копируем диагональ
                }
            }

            if (size < 5)
                continue;                                        // Пропускаем короткие диагонали

            std::cout << "Диагональ " << k << ": ";
            for (int i = 0; i < size; ++i)
            {
                std::cout << diagonal[i] << " ";                 // Выводим диагональ
            }
            int lineSum = evaluateLine(diagonal, this_player);   // Оцениваем диагональ
            sum += lineSum;
            std::cout << "| Текущая сумма: " << sum << "\n";
        }

        std::cout << "Общая сумма оценки: " << sum << "\n\n";

        return sum;
    }

    // Функция для оценки комбинации
    static int point(int streak, bool prev_empty, bool post_empty)
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
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Game game;

    // Устанавливаем фишки игрока (1)
    game.setPiece(3, 3, 1);
    game.setPiece(4, 4, 1);
    game.setPiece(5, 5, 1);
    game.setPiece(6, 6, 1);
    game.setPiece(3, 4, 1);
    game.setPiece(5, 3, 1);

    // Устанавливаем фишки компьютера (2)
    game.setPiece(2, 3, 2);
    game.setPiece(3, 2, 2);
    game.setPiece(3, 5, 2);
    game.setPiece(4, 3, 2);
    game.setPiece(4, 5, 2);

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