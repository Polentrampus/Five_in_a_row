#include "Game.h"
#include <conio.h> 
#include <iostream> 

int main()
{
    setlocale(LC_ALL, "Russian");
    Game game;
    int x, y;
    int currentPlayer = PLAYER_2; // �������� � ������ X
    game.setPiece(7, 7, PLAYER_2);
    while (true) 
    {
        system("cls");

        game.printField();
        int evaluation = game.Evaluation();
        std::cout << "\n������ �������: " << evaluation << std::endl;

        std::cout << "����� 1, ������� ���������� (x y): ";
        std::cin >> x >> y;
        game.setPiece(x, y, PLAYER_1);
        if (game.isWinningMove(PLAYER_1)) {
            game.printField();
            std::cout << "����� X �������!" << std::endl;
            return 0;
        }
        currentPlayer = PLAYER_2; // ����� �������

        // ��� �� (����� O)
        int bestValue = std::numeric_limits<int>::min();
        int bestMoveX = -1, bestMoveY = -1;

        for (int i = 0; i < SIZE_FIELD; ++i) {
            for (int j = 0; j < SIZE_FIELD; ++j) {
                if (game.field[i][j] == EMPTY) {
                    game.field[i][j] = PLAYER_2; // ������� ���
                    int moveValue = game.minmax(2, false, std::numeric_limits<int>::max(), std::numeric_limits<int>::min());
                    game.field[i][j] = EMPTY; // ������� � ��������� ���������

                    if (moveValue > bestValue) { // ���������� � �������� ������� ����������
                        bestValue = moveValue;
                        bestMoveX = i;
                        bestMoveY = j;
                    }
                }
            }
        }
        game.setPiece(bestMoveX, bestMoveY, PLAYER_2);
        if (game.isWinningMove(PLAYER_2)) {
            game.printField();
            std::cout << "����� O (��) �������!" << std::endl;
            return 0;
        }
        currentPlayer = PLAYER_1; // ����� �������
    }
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