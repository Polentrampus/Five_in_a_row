#include "Game.h"

bool isInBounds(int x, int y) {
    return x >= 0 && x < SIZE_FIELD && y >= 0 && y < SIZE_FIELD;
}

// ������� ��� ��������� ���������� ���������
std::vector<int> Game::SpiralMoves(int& x, int& y) {
    int centerX = SIZE_FIELD / 2;
    int centerY = SIZE_FIELD / 2;

    x = centerX;
    y = centerY;
    std::vector<int> arr;

    // �������� �� �������
    for (int radius = 1; radius < SIZE_FIELD; ++radius) {
        // ����������� �����, ������, ���� � �����
        for (int i = 0; i < radius; ++i) { // �����
            y = centerY + i; // ��������� ����� �� ������
            x = centerX - radius; // ������������� x ��� ����� ����� �����
            if (isInBounds(x, y) && field[x][y] == EMPTY) arr.push_back(field[x][y]);
        }
        for (int i = 0; i < radius; ++i) { // ������
            x = centerX + i; // ��������� �� ������ �����
            y = centerY + radius;
            if (isInBounds(x, y) && field[x][y] == EMPTY) arr.push_back(field[x][y]);
        }
        for (int i = 0; i < radius; ++i) { // ����
            x = centerX + radius; // ������������� x ��� ������ ����� �����
            y = centerY - i;
            if (isInBounds(x, y) && field[x][y] == EMPTY) arr.push_back(field[x][y]);
        }
        for (int i = 0; i < radius; ++i) { // �����
            x = centerX - i; // ��������� �� ����� �����
            y = centerY - radius;
            if (isInBounds(x, y) && field[x][y] == EMPTY) arr.push_back(field[x][y]);
        }
    }
    return arr;
}

int Game::minmax(int depth, bool maximizingPlayer, int alpha, int beta)
{
    if (isWinningMove(PLAYER_1)) return -10000 + depth; // ������ ��� ��������������� ������
    if (isWinningMove(PLAYER_2)) return 10000 - depth;  // ������ ��� ���������������� ������
    if (depth == 0) return Evaluation(); // �������� ������� ��� ����������

    int maxEval = std::numeric_limits<int>::min();
    int minEval = std::numeric_limits<int>::max();

    // ��������� ����� � ���������� �������
    int x, y;
    std::vector<int> arr;
    arr = SpiralMoves(x, y); // ������������� ��������� �� �������

    // ������� ���� ��������� �����
    //for (int radius = 0; radius < SIZE_FIELD; ++radius) {
    //    for (int dir = 0; dir < 4; ++dir) {
    //        switch (dir) {
    //        case 0: // �����
    //            x = SIZE_FIELD / 2 - radius;
    //            y = SIZE_FIELD / 2 + radius;
    //            break;
    //        case 1: // ������
    //            x = SIZE_FIELD / 2 + radius;
    //            y = SIZE_FIELD / 2 + radius;
    //            break;
    //        case 2: // ����
    //            x = SIZE_FIELD / 2 + radius;
    //            y = SIZE_FIELD / 2 - radius;
    //            break;
    //        case 3: // �����
    //            x = SIZE_FIELD / 2 - radius;
    //            y = SIZE_FIELD / 2 - radius;
    //            break;
    //        }

    for (auto it = arr.begin(); it != arr.end(); ++it)
    {
        if (isInBounds(x, y) && *it == EMPTY) {
            if (maximizingPlayer) {
                *it = PLAYER_2; // ����� ������ ���
                int eval = minmax(depth - 1, false, alpha, beta);
                *it = EMPTY; // ������� � ��������� ���������
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) break; // �����-���� ���������
            }
            else {
                *it = PLAYER_1;
                int eval = minmax(depth - 1, true, alpha, beta);
                *it = EMPTY;
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) break;
            }
        }

        return maximizingPlayer ? maxEval : minEval;
    }
}

