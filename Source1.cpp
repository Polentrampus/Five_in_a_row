#pragma once
#include <iostream>
#include <string>
#define SIZE_FIELD  15 

class Game
{
public:
    int field[SIZE_FIELD][SIZE_FIELD];// ������� ���� �������� 10x10

    // ����������� ��� ������������� ����
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

    // ����� ��� ��������� ����� �� ����
    void setPiece(int i, int j, int player)
    {
        if (i >= 0 && i < SIZE_FIELD && j >= 0 && j < SIZE_FIELD)
        {
            if (field[i][j] == 0)
            {
                field[i][j] = player;
                std::cout << "����� ������ " << player << " ����������� �� (" << i << ", " << j << ")\n";
            }
            else
            {
                std::cout << "������ (" << i << ", " << j << ") ��� ������.\n";
            }
        }
        else
        {
            std::cout << "������������ ����������: (" << i << ", " << j << ")\n";
        }
    }

    // ����� ��� ����������� ���� �� ������
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
                    std::cout << "1|";         // ����� ������
                }
                else if (field[i][j] == 2)
                {
                    std::cout << "2|";         // ����� ����������
                }
                else
                {
                    std::cout << " |";         // ������ ������
                }
            }
            std::cout << "\n";
        }
    }

    // ��������� �������
    int Evaluation() const
    {
        std::cout << "\n���������� ������ ������� ��� ����������:\n";
        int evalComputer = EvaluationFunction(field, 2, 1);         // ������ ��� ����������
        std::cout << "������ ����������: " << evalComputer << "\n";

        std::cout << "���������� ������ ������� ��� ������:\n";
        int evalPlayer = EvaluationFunction(field, 1, 2);           // ������ ��� ������
        std::cout << "������ ������: " << evalPlayer << "\n";

        std::cout << "����� ������ ������� (��������� - �����): " << (evalComputer - evalPlayer) << "\n\n";

        return evalComputer - evalPlayer;                          // ������� ������
    }

private:
    // ��������������� ������� ��� ������ ����� (������, ������� ��� ���������)
    static int evaluateLine(const int* line, int player)
    {
        int sum = 0;
        int streak = 0; //������
        bool prev_empty = false;
        bool post_empty = false;

        for (int i = 0; i < SIZE_FIELD; ++i)
        {
            if (line[i] == player)
            {
                if (streak == 0)
                {
                    prev_empty = (i > 0 && line[i - 1] == 0);     // ��������� ������ ������ ����� ������
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
                    post_empty = (line[i] == 0);                  // ��������� ������ ������ ����� �����
                    sum += point(streak, prev_empty, post_empty); // ��������� ������� �����
                    streak = 0;
                    prev_empty = false;
                    post_empty = false;
                }
            }
        }

        // ��������� ����� � ����� �����
        if (streak > 0)
        {
            post_empty = false;                                   // ��� ������ ����� ��������� �����
            sum += point(streak, prev_empty, post_empty);         // ��������� ��������� �����
        }

        return sum;
    }

    // ����������� ��������������� ������� ��� ������ ������� ��� ����������� ������
    static int EvaluationFunction(const int field[SIZE_FIELD][SIZE_FIELD], int this_player, int enemy_player)
    {
        int sum = 0;

        // ��������� �����
        std::cout << "��������� �����:\n";
        for (int i = 0; i < SIZE_FIELD; ++i)
        {
            int row[SIZE_FIELD];
            for (int j = 0; j < SIZE_FIELD; ++j)
            {
                row[j] = field[i][j];                             // �������� ������
            }
            std::cout << "������ " << i << ": ";
            for (int j = 0; j < SIZE_FIELD; ++j)
            {
                std::cout << row[j] << " ";                       // ������� ������
            }
            int lineSum = evaluateLine(row, this_player);         // ��������� ������
            sum += lineSum;
            std::cout << "| ������� �����: " << sum << "\n";
        }

        // ��������� ��������
        std::cout << "\n��������� ��������:\n";
        for (int j = 0; j < SIZE_FIELD; ++j)
        {
            int column[SIZE_FIELD]; //�������
            for (int i = 0; i < SIZE_FIELD; ++i)
            {
                column[i] = field[i][j];                          // �������� �������
            }
            std::cout << "������� " << j << ": ";
            for (int i = 0; i < SIZE_FIELD; ++i)
            {
                std::cout << column[i] << " ";                    // ������� �������
            }
            int lineSum = evaluateLine(column, this_player);      // ��������� �������
            sum += lineSum;
            std::cout << "| ������� �����: " << sum << "\n";
        }

        // ��������� ���������� (����� ��� -> ������ ����)
        std::cout << "\n��������� ���������� (����� ��� -> ������ ����):\n";
        for (int k = 0; k < SIZE_FIELD; ++k)
        {
            int diagonal[SIZE_FIELD];
            int size = 0;
            for (int i = 0; i < SIZE_FIELD; ++i)
            {
                int j = i + k;
                if (j >= 0 && j < SIZE_FIELD)
                {
                    diagonal[size++] = field[i][j];               // �������� ���������
                }
            }

            if (size < 5)
                continue;                                        // ���������� �������� ���������

            std::cout << "��������� " << k << ": ";
            for (int i = 0; i < size; ++i)
            {
                std::cout << diagonal[i] << " ";                 // ������� ���������
            }
            int lineSum = evaluateLine(diagonal, this_player);   // ��������� ���������
            sum += lineSum;
            std::cout << "| ������� �����: " << sum << "\n";
        }

        // ��������� ���������� (����� ���� -> ������ ���)
        std::cout << "\n��������� ���������� (����� ���� -> ������ ���):\n";
        for (int k = 0; k < SIZE_FIELD; ++k)
        {
            int diagonal[SIZE_FIELD];
            int size = 0;
            for (int i = 0; i < SIZE_FIELD; ++i)
            {
                int j = k - i;
                if (j >= 0 && j < SIZE_FIELD)
                {
                    diagonal[size++] = field[i][j];              // �������� ���������
                }
            }

            if (size < 5)
                continue;                                        // ���������� �������� ���������

            std::cout << "��������� " << k << ": ";
            for (int i = 0; i < size; ++i)
            {
                std::cout << diagonal[i] << " ";                 // ������� ���������
            }
            int lineSum = evaluateLine(diagonal, this_player);   // ��������� ���������
            sum += lineSum;
            std::cout << "| ������� �����: " << sum << "\n";
        }

        std::cout << "����� ����� ������: " << sum << "\n\n";

        return sum;
    }

    // ������� ��� ������ ����������
    static int point(int streak, bool prev_empty, bool post_empty)
    {
        if (streak >= 5)
        {
            return 10000; // ������!!!!!
        }
        else if (streak == 4)
        {
            if (prev_empty && post_empty)
                return 5000; // �������� ��������
            else if (prev_empty || post_empty)
                return 1000; // ������������ ��������
            else
                return 0; // �������� ��������
        }
        else if (streak == 3)
        {
            if (prev_empty && post_empty)
                return 500; // �������� ������
            else if (prev_empty || post_empty)
                return 100; // ������������ ������
            else
                return 0; //�������� ������
        }
        else if (streak == 2)
        {
            if (prev_empty && post_empty)
                return 50; // �������� ������
            else if (prev_empty || post_empty)
                return 10; // ������������ ������
            else
                return 0; // �������� ������
        }
        else if (streak == 1)
        {
            if (prev_empty && post_empty)
                return 2; // �������� �������
            else if (prev_empty || post_empty)
                return 1; // ������������ �������
            else
                return 0; // �������� �������
        }
        else
        {
            return 0; // ��� �������� ����������
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Game game;

    // ������������� ����� ������ (1)
    game.setPiece(3, 3, 1);
    game.setPiece(4, 4, 1);
    game.setPiece(5, 5, 1);
    game.setPiece(6, 6, 1);
    game.setPiece(3, 4, 1);
    game.setPiece(5, 3, 1);

    // ������������� ����� ���������� (2)
    game.setPiece(2, 3, 2);
    game.setPiece(3, 2, 2);
    game.setPiece(3, 5, 2);
    game.setPiece(4, 3, 2);
    game.setPiece(4, 5, 2);

    std::cout << "\n������� ��������� �������� ����:\n";
    game.printField();

    int evaluation = game.Evaluation();

    std::cout << "\n������ �������: " << evaluation << std::endl;

    if (evaluation > 0)
    {
        std::cout << "������������ ����������.\n";
    }
    else if (evaluation < 0)
    {
        std::cout << "������������ ������.\n";
    }
    else
    {
        std::cout << "������� ��������������.\n";
    }

    return 0;
}