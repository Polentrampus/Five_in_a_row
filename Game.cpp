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

int Game::Evaluation() const
{
    int evalComputer = EvaluationFunction(field, 2, 1);         // ������ ��� ����������
    int evalPlayer = EvaluationFunction(field, 1, 2);           // ������ ��� ������
    return evalComputer - evalPlayer;                          // ������� ������
}

int Game::evaluateLine(const int* line, int player)
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

int Game::EvaluationFunction(const int field[SIZE_FIELD][SIZE_FIELD], int this_player, int enemy_player)
{
    int sum = 0;

    // ��������� �����
    for (int i = 0; i < SIZE_FIELD; ++i)
    {
        int row[SIZE_FIELD];
        for (int j = 0; j < SIZE_FIELD; ++j)
        {
            row[j] = field[i][j];                             // �������� ������
        }

        int lineSum = evaluateLine(row, this_player);         // ��������� ������
        sum += lineSum;
    }

    // ��������� ��������
    for (int j = 0; j < SIZE_FIELD; ++j)
    {
        int column[SIZE_FIELD]; //�������
        for (int i = 0; i < SIZE_FIELD; ++i)
        {
            column[i] = field[i][j];                          // �������� �������
        }
        
        int lineSum = evaluateLine(column, this_player);      // ��������� �������
        sum += lineSum;
    }

    // ��������� ���������� (����� ��� -> ������ ����)
    for (int k = 0; k < SIZE_FIELD * 2 + 1; k++)
    {
        int diagonal[SIZE_FIELD * 2 + 1];
        int size = 0;
        for (int i = 0; i < SIZE_FIELD; i++)
        {
            int j = k - i;
            if (j >= 0 && j < SIZE_FIELD)
            {
                diagonal[size] = field[i][j];               // �������� ���������
                size++;
            }
        }

        if (size < 5)
            continue;                                        // ���������� �������� ���������

        int lineSum = evaluateLine(diagonal, this_player);   // ��������� ���������
        sum += lineSum;
    }

    // ��������� ���������� (������ ��� -> ����� ����)
    for (int k = 0; k < SIZE_FIELD*2+1; k++)
    {
        int diagonal[SIZE_FIELD * 2 + 1];
        int size = 0;
        for (int i = 0; i < SIZE_FIELD; i++)
        {
            int j = k + i - (SIZE_FIELD - 1);
            if (j >= 0 && j < SIZE_FIELD)
            {
                diagonal[size] = field[i][j];              // �������� ���������
                size++;
            }
        }

        if (size < 5)
            continue;                                        // ���������� �������� ���������

        int lineSum = evaluateLine(diagonal, this_player);   // ��������� ���������
        sum += lineSum;
    }
    return sum;
}

int Game::point(int streak, bool prev_empty, bool post_empty)
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

bool Game::isWinningMove(int this_player)
{
    int sum = 0;

    for (int i = 0; i < SIZE_FIELD; ++i)
    {
        int row[SIZE_FIELD];
        for (int j = 0; j < SIZE_FIELD; ++j)
        {
            row[j] = field[i][j];                             // �������� ������
        }
        int lineSum = evaluateLine(row, this_player);         // ��������� ������
        sum += lineSum;
    }

    for (int j = 0; j < SIZE_FIELD; ++j)
    {
        int column[SIZE_FIELD];
        for (int i = 0; i < SIZE_FIELD; ++i)
        {
            column[i] = field[i][j];                          // �������� �������
        }
        int lineSum = evaluateLine(column, this_player);      // ��������� �������
        sum += lineSum;
    }

    // ��������� ���������� (����� ��� -> ������ ����)
    for (int k = 0; k < SIZE_FIELD * 2 + 1; k++)
    {
        int diagonal[SIZE_FIELD * 2 + 1];
        int size = 0;
        for (int i = 0; i < SIZE_FIELD; i++)
        {
            int j = k - i;
            if (j >= 0 && j < SIZE_FIELD)
            {
                diagonal[size] = field[i][j];               // �������� ���������
                size++;
            }
        }

        if (size < 5)
            continue;                                        // ���������� �������� ���������

        int lineSum = evaluateLine(diagonal, this_player);   // ��������� ���������
        sum += lineSum;
    }

    // ��������� ���������� (������ ��� -> ����� ����)
    for (int k = 0; k < SIZE_FIELD * 2 + 1; k++)
    {
        int diagonal[SIZE_FIELD * 2 + 1];
        int size = 0;
        for (int i = 0; i < SIZE_FIELD; i++)
        {
            int j = k + i - (SIZE_FIELD - 1);
            if (j >= 0 && j < SIZE_FIELD)
            {
                diagonal[size] = field[i][j];              // �������� ���������
                size++;
            }
        }

        if (size < 5)
            continue;                                        // ���������� �������� ���������

        int lineSum = evaluateLine(diagonal, this_player);   // ��������� ���������
        sum += lineSum;
    }
    if (sum >= 10000){return true;}
    return false;
}