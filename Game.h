#pragma once
#include <iostream>
#include <string>
#include <vector>

#define SIZE_FIELD  15
const int EMPTY = 0; // ������ ������
const int PLAYER_O = 1; // ����� 1 (������������)
const int PLAYER_X = 2; // ����� 2 (������)

class Game
{
public:
    // ������� ���� �������� 10x10
    int field[SIZE_FIELD][SIZE_FIELD];
    // ����������� ��� ������������� ����
    Game();
    // ����� ��� ��������� ����� �� ����
    void setPiece(int, int, int player);
    // ����� ��� ����������� ���� �� ������
    void printField() const;
    // ��������� �������
    int Evaluation() const;
    bool isWinningMove(int player);
    void printBoard();
    int minmax(int depth, bool maximizingPlayer, int alpha, int beta);
private:
    // ��������������� ������� ��� ������ ����� (������, ������� ��� ���������)
    static int evaluateLine(const int* line, int player);
    // ����������� ��������������� ������� ��� ������ ������� ��� ����������� ������
    static int EvaluationFunction(const int field[SIZE_FIELD][SIZE_FIELD], int this_player, int enemy_player);
    // ������� ��� ������ ����������
    static int point(int streak, bool prev_empty, bool post_empty);
    // ������� ���-����
};