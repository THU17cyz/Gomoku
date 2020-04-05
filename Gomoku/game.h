#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include "chessboard.h"
#include "player.h"
#include "robot.h"

/***************
* [ö��] ��ɫ
***************/
enum class Role {
	PLAYER = 0,		// ���
	ROBOT = 1,		// ����
};

/***************
* [��] ��Ϸ
* �������࣬������Ϸ�߼�
***************/
class Game: public Chessboard, public Player, public Robot {
public:
	Game() { }				// ���캯��
	~Game() { }				// ��������
	void start();			// ���к��� --- ������ѭ��
	void describe();		// �������� --- ���������Ϣ
private:
	// TODO

};
#endif