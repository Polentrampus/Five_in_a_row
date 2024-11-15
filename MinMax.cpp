#include "Game.h"

bool isInBounds(int x, int y) {
    return x >= 0 && x < SIZE_FIELD && y >= 0 && y < SIZE_FIELD;
}

void SpiralMove(int** arr, int centerX, int centerY)
{
    std::cout << "(" << centerX << ", " << centerY << ")\n"; // ��������� ������

    for (int radius = 1; radius < SIZE_FIELD; ++radius) {
        // ����������� ����� � �����
        for (int i = 0; i < radius; ++i) {
            if (isInBounds(centerX - radius, centerY + i)) // �����
                std::cout << "(" << centerX - radius << ", " << centerY + i << ")\n";
        }
        for (int i = 0; i < radius; ++i) {
            if (isInBounds(centerX - radius, centerY + radius)) // ������
                std::cout << "(" << centerX + i << ", " << centerY + radius << ")\n";
        }

        // ����������� ���� � �����
        for (int i = radius; i >= 0; --i) {
            if (isInBounds(centerX + radius, centerY + i)) // ����
                std::cout << "(" << centerX + radius << ", " << centerY + i << ")\n";
        }
        for (int i = radius; i > 0; --i) {
            if (isInBounds(centerX + i, centerY - radius)) // �����
                std::cout << "(" << centerX + i << ", " << centerY - radius << ")\n";
        }
    }
}

int Game::minmax(int depth, bool maximizingPlayer, int alpha, int beta) {
    if (isWinningMove(PLAYER_O)) return -10000 + depth; // ������ ��� ��������������� ������
    if (isWinningMove(PLAYER_X)) return 10000 - depth;  // ������ ��� ���������������� ������

    // ������ �������� ��������� ��� ���������� ������������ �������
    if (depth == 0) return Evaluation();

    if (maximizingPlayer) 
    {
        int maxEval = std::numeric_limits<int>::min();
        int centerX = SIZE_FIELD / 2;
        int centerY = SIZE_FIELD / 2;

        for (int i = 0; i < SIZE_FIELD; ++i) 
        {
            for (int j = 0; j < SIZE_FIELD; ++j)
            {

                if (field[i][j] == EMPTY)
                {
                    field[i][j] = PLAYER_X; // ����� ������ ���
                    int eval = minmax(depth - 1, false, alpha, beta);
                    field[i][j] = EMPTY; // ������� � ��������� ���������
                    maxEval = std::max(maxEval, eval);
                    alpha = std::max(alpha, eval);
                    if (beta <= alpha) break; // �����-���� ���������
                }
            }
        }
        return maxEval;
    }
    else 
    {
        int minEval = std::numeric_limits<int>::max();
        for (int i = 0; i < SIZE_FIELD; ++i) {
            for (int j = 0; j < SIZE_FIELD; ++j) {
                if (field[i][j] == EMPTY) {
                    field[i][j] = PLAYER_O; // ����� ������ ���
                    int eval = minmax(depth - 1, true, alpha, beta);
                    field[i][j] = EMPTY; // ������� � ��������� ���������
                    minEval = std::min(minEval, eval);
                    beta = std::min(beta, eval);
                    if (beta <= alpha) break; // �����-���� ���������
                }
            }
        }
        return minEval;
    }
}

