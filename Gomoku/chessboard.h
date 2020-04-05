#pragma once
#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_
#include <iostream>
#include <string.h>
#include <vector>
#include <regex>

/***************
* [����] ����
***************/
const int INF = 0x3f3f3f3f;	// ����ֵ
const int GRID_NUM = 15;	// ���̹�ģ
const int EFFECTIVE_DIAGONAL_NUM = 29; // �Խ�������

/***************
* [ö��] ��/��ɫ
***************/
enum class Chess {
	BLANK = 0,		// �հ�
	BLACK = 1,		// ����
	WHITE = 2		// ����
};
enum class Role {
	PLAYER = 0,		// ���
	ROBOT = 1,		// ����
};
enum class Status {
	S_OK = 0,		// ִ�гɹ�
	F_OUTSIDE = 1,	// ִ��ʧ�� - ����
	F_NOBLANK = 2,	// ִ��ʧ�� - �ǿ�
	F_NOLAST = 3,	// ִ��ʧ�� - ����һ��
	G_BLACK = 4,	// ��Ϸ���� - ���ӻ�ʤ
	G_WHITE = 5,	// ��Ϸ���� - ���ӻ�ʤ
	G_DRAW = 6,		// ��Ϸ���� - ����
	G_CONTINUE = 7,	// ��Ϸ���� - �޷��ж�ʤ��
};

/***************
* [�ṹ] �߷�
***************/
struct Move {
	int x;			// X ����
	int y;			// Y ����
	Move(int x, int y) : x(x), y(y) { }
};

/***************
* [��] ���
* ���������������غ���
***************/
class Chessboard {
public:
	Chessboard();										// ���캯��
	~Chessboard();										// ��������
	void initMove();									// ��ֳ�ʼ��
	Status makeMove(const int x, const int y);			// ���ִ���߷�
	Status unMakeMove();								// ��ֳ����߷�
	Status gameOver();									// �ж����ʤ�����
	void printChessboard();								// ��ӡ����

	char horizontals[GRID_NUM][GRID_NUM + 3]; // ˮƽ��
	char verticals[GRID_NUM][GRID_NUM + 3]; // ��ֱ��
	char up_diagonals[EFFECTIVE_DIAGONAL_NUM][GRID_NUM + 3]; // ����-���Ϸ���Խ���
	char down_diagonals[EFFECTIVE_DIAGONAL_NUM][GRID_NUM + 3]; // ����-���Ϸ���Խ���

protected:
	// ������ּ�¼��ȡ��ǰ����
	inline int getCurrentStep() {
		return (chessRecord.size() + 1);
	}
	// ������ּ�¼��ȡ��ǰ��ɫ
	inline Chess getCurrentChess() {
		return ((chessRecord.size() & 1) ? Chess::BLACK : Chess::WHITE);
	}
	inline Move getLastMove() {
		return chessRecord.back();
	}
private:
	// Role sente;										// ���з�
	Chess chessboard[GRID_NUM + 1][GRID_NUM + 1];		// ���̱���
	std::vector<Move> chessRecord;						// ��ּ�¼

	
	/*
	// ��ȡ��ǰ��ɫ
	inline Role getCurrentRole() {
		if (chessRecord.size() & 1)
			return (sente == Role::PLAYER ? Role::PLAYER : Role::ROBOT);
		else
			return (sente == Role::PLAYER ? Role::ROBOT : Role::PLAYER);
	}
	*/
	// �����з��Ƿ���������
	inline bool inChessboard(const int x, const int y) {
		return (x > 0 && x <= GRID_NUM && y > 0 && y <= GRID_NUM);	
	}
	// �������
	inline void clearChessboard() {
		memset(chessboard, 0, sizeof(chessboard));	
		
		// ���ø�������
		for (int i = 0; i < GRID_NUM; i++) {
			for (int j = 1; j <= GRID_NUM; j++) {
				horizontals[i][j] = '0';
				verticals[i][j] = '0';
			}
			horizontals[i][0] = horizontals[i][GRID_NUM + 1] = '#';
			verticals[i][0] = verticals[i][GRID_NUM + 1] = '#';
			horizontals[i][GRID_NUM + 2] = verticals[i][GRID_NUM + 2] = '\0';
		}
		for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
			int len = 15 - abs(14 - i);
			for (int j = 1; j <= len; j++) {
				up_diagonals[i][j] = '0';
				down_diagonals[i][j] = '0';
			}
			up_diagonals[i][0] = up_diagonals[i][len + 1] = '#';
			down_diagonals[i][0] = down_diagonals[i][len + 1] = '#';
			up_diagonals[i][len + 2] = down_diagonals[i][len + 2] = '\0';
		}
	}

	inline char chess2char(Chess x) {
		if (x == Chess::BLACK)
			return '1';
		else
			return '2';
	}
};

#endif