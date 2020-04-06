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
	DEFAULT = 0,	// Ĭ��
	PLAYER = 1,		// ���
	ROBOT = 2,		// ����

};
enum class Stage {
	DEFAULT = 0,	// Ĭ��
	UNDERWAY = 1,	// ���ڽ���
	GAMEOVER = 2,	// ��Ϸ����
};

/***************
* [��] ��Ϸ
* �������࣬������Ϸ�߼�
***************/
class Game: public Chessboard, public Player, public Robot {
public:
	Game();					// ���캯��
	~Game();				// ��������
	void start();			// ���к��� --- ������ѭ��
	void describe();		// �������� --- ���������Ϣ
private:
	Role sente;				// ���з�
	Chess winner;			// ��ʤ��
	Stage stage;			// ��Ϸ�׶�
	// TODO

};
#endif
