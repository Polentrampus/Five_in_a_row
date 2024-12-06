#include "Game.h"
#include <conio.h> 
#include <iostream> 
#include <stdexcept>

int getPlayerInput()
{
    int x;
    std::cout << "����� 1, ������� ���������� (x y): ";
    std::cin >> x;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("�������� ����: ���������� ��������.");
    }

    if (x < 0 || x > 14 ) {
        throw std::out_of_range("������: ���������� ������ ���� �� 0 �� 14.");
    }
    return x;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Game game;
    int x, y;
    int currentPlayer = PLAYER_2; // �������� � ������ X
    game.setPiece(7, 7, PLAYER_2);

    bool gameOver = false;
    while (!gameOver)
    {
        system("cls");

        game.printField();
        int evaluation = game.Evaluation();
        std::cout << "\n������ �������: " << evaluation << std::endl;

        bool validMove = false;
        while (!validMove) // ����, ����� ��������� ������ ������� �������� ����������
        {
            try
            {
                x = getPlayerInput();
                y = getPlayerInput();

                // ������� ��������� ����� ������
                game.setPiece(x, y, PLAYER_1);
                validMove = true; // ���� � ��� ������ ��������� �������

                if (game.isWinningMove(PLAYER_1)) // �������� �� ������ ������
                {
                    game.printField();
                    std::cout << "����� 1 (��) �������!" << std::endl;
                    gameOver = true;
                    return 0;
                }
            }
            catch (const std::exception& e)
            {
                // ��������� ���������� - �������� �� ������ � ��������� ����
                std::cout << e.what() << std::endl;
                system("cls");

                game.printField();
                int evaluation = game.Evaluation();
                std::cout << "\n������ �������: " << evaluation << std::endl;
                std::cout << "\n����������, ���������� �����.\n";
            }
        }

        // ��� �� (����� O)
        int bestValue = std::numeric_limits<int>::min();
        int bestMoveX = -1, bestMoveY = -1;

        for (int i = 0; i < SIZE_FIELD; ++i)
        {
            for (int j = 0; j < SIZE_FIELD; ++j)
            {
                if (game.field[i][j] == EMPTY)
                {
                    game.field[i][j] = PLAYER_2; // ������� ���
                    int moveValue = game.minmax(2, false, std::numeric_limits<int>::max(), std::numeric_limits<int>::min());
                    game.field[i][j] = EMPTY; // ������� � ��������� ���������

                    if (moveValue > bestValue) // ���������� � �������� ������� ����������
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
            std::cout << "����� 2 (��) �������!" << std::endl;
            gameOver = true;
            return 0;
        }
        currentPlayer = PLAYER_1; // ����� �������
        std::cout << "\n������� ��������� �������� ����:\n";
    }
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