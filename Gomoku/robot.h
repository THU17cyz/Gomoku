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
<<<<<<< HEAD
	~Robot();			// ��������
=======
	~Robot() { }		// ��������
>>>>>>> 4c2ba6a736d724fbe7dc636807b22dbab7187711
	std::vector<Move> createMoves(Chessboard &chessboard);	// ��ȡ�Ϸ����ӵ�
	int evaluate(Chessboard& chessboard);					// ��ֵ�㷨�����ع�ֵ
	int searchMove(Chessboard& chessboard);					// ��������

	std::regex black_regex[100];
	std::regex white_regex[100];
	int cost[7];
};

#endif
