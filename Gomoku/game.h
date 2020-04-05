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
	Stage stage;			// ��Ϸ�׶�
	// TODO

};
#endif
