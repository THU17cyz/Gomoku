#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "chessboard.h"

/***************
* [����] ����
***************/
const int BUFFER_LENGTH = 128;	// ��������С

/***************
* [ö��] ����
***************/
enum class Operation {
	NEWBLACK = 0,	// ���� AI�ֺ����� 
	NEWWHITE = 1,	// ���� AI�ְ׺���
	MOVE = 2,		// ����
	WITHDRAW = 3,	// ����
	TIPS = 4,		// ��ʾ
	EXIT = 5,		// �˳�
};

/***************
* [��] ���
* ��������ҽ������
***************/
class Player {
public:
	Player();						// ���캯��
	~Player();						// ��������
	void getUserInput(Chess chess);	// ��ȡ�û�����
	inline Operation getOperation() {
		return operation;			// ��ȡ����
	}
	inline Move getMove() {
		return move;				// ��ȡ�߷�
	}
private:
	Operation operation;			// ��������
	Move move;						// �߷�����
	char buffer[128];				// ������
	char icon[16], order[16];		// ��ʱ�ַ���

};


#endif