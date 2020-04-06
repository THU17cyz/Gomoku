#pragma once
#ifndef _ROBOT_H_
#define _ROBOT_H_
#include "chessboard.h"


/***************
* [����] ����
***************/
const int MAX_VALUE = 0x3f3f3f3f;		// ����ֵ
const int MIN_VALUE = -0x3f3f3f3f;		// ��Сֵ
const int MAX_DEPTH = 2;				// ����������

/***************
* [��] ����
* ������������㷨
***************/
class Robot {
public:
	Robot();					// ���캯��
	~Robot();					// ��������
	Move getRobotDecision(Chessboard& chessboard);	// [�ӿ�] ��ȡ��������
	
private:
	std::vector<Move> createMoves(Chessboard &chessboard);			// ��ȡ�Ϸ����ӵ�
	int evaluate(Chessboard& chessboard, Chess chess);				// ��ֵ�㷨
	Move searchMove(Chessboard& chessboard);						// �����㷨
	int maxValue(Chessboard& chessboard, int depth, int a, int b);	// minimax�Կ����� - MAX
	int minValue(Chessboard& chessboard, int depth, int a, int b);	// minimax�Կ����� - MIN
	std::regex black_regex[100];
	std::regex white_regex[100];
	int cost_self[10];
	int cost_opp[10];
};

#endif
