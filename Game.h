#pragma once
#include <iostream>
#include <string>
#include <vector>

#define SIZE_FIELD  15
const int EMPTY = 0; // ������ ������
const int PLAYER_1 = 1; // ����� 1 (������������)
const int PLAYER_2 = 2; // ����� 2 (������)

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
    int minmax(int depth, bool maximizingPlayer, int alpha, int beta);
    void SpiralMoves(int& x, int& y);
private:
    // ��������������� ������� ��� ������ ����� (������, ������� ��� ���������)
    static int evaluateLine(const int* line, int player);
    // ����������� ��������������� ������� ��� ������ ������� ��� ����������� ������
    static int EvaluationFunction(const int field[SIZE_FIELD][SIZE_FIELD], int this_player, int enemy_player);
    // ������� ��� ������ ����������
    static int point(int streak, bool prev_empty, bool post_empty);
    // ������� ���-����
};