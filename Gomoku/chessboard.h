#pragma once
#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_
#include <string.h>
#include <vector>

/***************
* [����] ����
***************/
const int INF = 0x3f3f3f3f;	// ����ֵ
const int GRID_NUM = 15;	// ���̹�ģ

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
protected:
	// ������ּ�¼��ȡ��ǰ����
	inline int getCurrentStep() {
		return (chessRecord.size() + 1);
	}
	// ������ּ�¼��ȡ��ǰ��ɫ
	inline Chess getCurrentChess() {
		return ((chessRecord.size() & 1) ? Chess::BLACK : Chess::WHITE);
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
	}
};

#endif