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
	Robot();			// ���캯��
	~Robot();			// ��������
	std::vector<Move> createMoves(Chessboard &chessboard);	// ��ȡ�Ϸ����ӵ�
	int evaluate(Chessboard& chessboard);					// ��ֵ�㷨�����ع�ֵ
	int searchMove(Chessboard& chessboard);					// ��������
};

#endif
