#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "chessboard.h"

/***************
* [ö��] ����
***************/
enum Operation {
	NEWBLACK = 0,	// ���� AI�ֺ����� 
	NEWWHITE = 1,	// ���� AI�ְ׺���
	MOVE = 2,		// ����
	WITHDRAW = 4,	// ����
	PROMPT = 5,		// ��ʾ
};

/***************
* [��] ���
* ��������ҽ������
***************/
class Player {
public:
	Player() { }	// ���캯��
	~Player() { }	// ��������
};


#endif