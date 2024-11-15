#include "Game.h"

bool isInBounds(int x, int y) {
    return x >= 0 && x < SIZE_FIELD && y >= 0 && y < SIZE_FIELD;
}

// ������� ��� ��������� ���������� ���������
void Game::SpiralMoves(int& x, int& y) {
    int centerX = SIZE_FIELD / 2;
    int centerY = SIZE_FIELD / 2;

    x = centerX;
    y = centerY;

    // �������� �� �������
    for (int radius = 1; radius < SIZE_FIELD; ++radius) {
        // ����������� �����, ������, ���� � �����
        for (int i = 0; i < radius; ++i) { // �����
            y = centerY + i; // ��������� ����� �� ������
            x = centerX - radius; // ������������� x ��� ����� ����� �����
            if (isInBounds(x, y) && field[x][y] == EMPTY);
        }
        for (int i = 0; i < radius; ++i) { // ������
            x = centerX + i; // ��������� �� ������ �����
            y = centerY + radius;
            if (isInBounds(x, y) && field[x][y] == EMPTY);
        }
        for (int i = 0; i < radius; ++i) { // ����
            x = centerX + radius; // ������������� x ��� ������ ����� �����
            y = centerY - i;
            if (isInBounds(x, y) && field[x][y] == EMPTY);
        }
        for (int i = 0; i < radius; ++i) { // �����
            x = centerX - i; // ��������� �� ����� �����
            y = centerY - radius;
            if (isInBounds(x, y) && field[x][y] == EMPTY);
        }
    }
}

int Game::minmax(int depth, bool maximizingPlayer, int alpha, int beta) {
    if (isWinningMove(PLAYER_1)) return -10000 + depth; // ������ ��� ��������������� ������
    if (isWinningMove(PLAYER_2)) return 10000 - depth;  // ������ ��� ���������������� ������
    if (depth == 0) return Evaluation(); // �������� ������� ��� ����������

    int maxEval = std::numeric_limits<int>::min();
    int minEval = std::numeric_limits<int>::max();

    // ��������� ����� � ���������� �������
    int x, y;

    // ������� ���� ��������� �����
    for (int radius = 0; radius < SIZE_FIELD; ++radius) {
        for (int dir = 0; dir < 4; ++dir) {
            switch (dir) {
            case 0: // �����
                x = SIZE_FIELD / 2 - radius;
                y = SIZE_FIELD / 2 + radius;
                break;
            case 1: // ������
                x = SIZE_FIELD / 2 + radius;
                y = SIZE_FIELD / 2 + radius;
                break;
            case 2: // ����
                x = SIZE_FIELD / 2 + radius;
                y = SIZE_FIELD / 2 - radius;
                break;
            case 3: // �����
                x = SIZE_FIELD / 2 - radius;
                y = SIZE_FIELD / 2 - radius;
                break;
            }

            if (isInBounds(x, y) && field[x][y] == EMPTY) {
                if (maximizingPlayer) {
                    field[x][y] = PLAYER_2; // ����� ������ ���
                    int eval = minmax(depth - 1, false, alpha, beta);
                    field[x][y] = EMPTY; // ������� � ��������� ���������
                    maxEval = std::max(maxEval, eval);
                    alpha = std::max(alpha, eval);
                    if (beta <= alpha) break; // �����-���� ���������
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

