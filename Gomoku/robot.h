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
struct pattern {
	char P[7];
	int m;
	pattern() {}
	pattern(const char *P_, int m_) { memcpy(P, P_, 7); m = m_; }
};
int *compute_prefix(char *P, int m);
int KMP_matcher(char *P, char*T, int m, int n);

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
	int evaluate(Chessboard& chessboard);							// ��ֵ�㷨
	Move searchMove(Chessboard& chessboard);						// �����㷨
	int maxValue(Chessboard& chessboard, int depth, int a, int b);	// minimax�Կ����� - MAX
	int minValue(Chessboard& chessboard, int depth, int a, int b);	// minimax�Կ����� - MIN
	Chess chess;					// ��ִ��ɫ

	pattern black_p[20];
	pattern white_p[20];
	std::regex black_regex[100];	// ��������
	std::regex white_regex[100];	// ��������
	int cost_self[20];				// ��������
	int cost_opp[20];				// ��������

};

#endif
