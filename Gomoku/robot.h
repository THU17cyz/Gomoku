#pragma once
#ifndef _ROBOT_H_
#define _ROBOT_H_
#include "chessboard.h"

/***************
* [��] ����
* ������������㷨
***************/
class Robot {
public:
	Robot();					// ���캯��
	~Robot();					// ��������
	Move getRobotDecision(Chessboard& chessboard, Chess chess);	// [�ӿ�] ��ȡ��������
	
private:
	std::vector<Move> createMoves(Chessboard &chessboard);	// ��ȡ�Ϸ����ӵ�
	int evaluate(Chessboard& chessboard);					// ��ֵ�㷨�����ع�ֵ
	int evaluate(Chessboard& chessboard, Move& p);					// ��ֵ�㷨�����ع�ֵ
	int searchMove(Chessboard& chessboard);					// ��������
	std::regex black_regex[100];
	std::regex white_regex[100];
	int cost_self[10];
	int cost_opp[10];
};

#endif
