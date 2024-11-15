#include "Game.h"

int Game::minmax(int depth, bool maximizingPlayer, int alpha, int beta) {
    if (isWinningMove(PLAYER_O)) return -10000 + depth; // ������ ��� ��������������� ������
    if (isWinningMove(PLAYER_X)) return 10000 - depth;  // ������ ��� ���������������� ������

    // ������ �������� ��������� ��� ���������� ������������ �������
    if (depth == 0) return Evaluation();

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (int i = 0; i < SIZE_FIELD; ++i) {
            for (int j = 0; j < SIZE_FIELD; ++j) {
                if (field[i][j] == EMPTY) {
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
    else {
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

