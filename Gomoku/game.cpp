#include "game.h"
#include <iostream>
#include <string>
using namespace std;

const bool DEBUG_MODE = false;

/***************
* [����] ���캯��
***************/
Game::Game(): sente(Role::PLAYER), stage(Stage::DEFAULT) {
	return;
}

/***************
* [����] ��������
***************/
Game::~Game() {
	return;
}

/***************
* [����] ���к��� --- ������ѭ��
***************/
void Game::start() {
	Status status = Status::S_OK;
	Chess chess = Chess::BLANK;
	Operation operation = Operation::NEWBLACK;
	Move move = Move(0, 0);
	while (true) {
		// *** ��ӡ��Ϸ��Ϣ ***
		system("cls");			// �����Ļ			
		describe();				// ��ӡ������Ϣ
		printChessboard();		// ��ӡ����
		printf_s("\n");
		printChessRecord(-2);	// ��ӡ��ּ�¼
		printChessRecord(-1);	// ��ӡ��ּ�¼
		// *** �û����о��� ***
		chess = getCurrentChess();
		while (true) {
			// * ��ȡ�û����� *
			getUserInput(chess);
			operation = getUserOperation();
			move = getUserMove();
			if (DEBUG_MODE)
				printf_s("@ �û����������(%d,%d,%d)\n", int(operation), move.x, move.y);
			// * �����û����� *
			if (operation == Operation::NEWBLACK) {
				sente = Role::ROBOT;		// �������з�
				stage = Stage::UNDERWAY;	// ������Ϸ�׶�
				initMove();					// ��������
				break;
			}
			if (operation == Operation::NEWWHITE) {
				sente = Role::PLAYER;		// �������з�
				stage = Stage::UNDERWAY;	// ������Ϸ�׶�
				initMove();					// ��������
				break;
			}
			if (operation == Operation::MOVE) {
				if (stage != Stage::UNDERWAY) {
					printf_s("[��] �Ծ�δ��ʼ�������<newblack>/<newwhite>�Կ�ʼ�Ծ֡�\n");
					continue;
				}
				status = makeMove(move.x, move.y);	// ����
				if (status == Status::F_OUTSIDE) {
					printf_s("[��] �Ƿ����� - ���⣡\n");
					continue;
				}
				if (status == Status::F_NOBLANK) {
					printf_s("[��] �Ƿ����� - �ǿգ�\n");
					continue;
				}
				break;
			}
			if (operation == Operation::WITHDRAW) {
				if (stage != Stage::UNDERWAY) {
					printf_s("[��] �Ծ�δ��ʼ�������<newblack>/<newwhite>�Կ�ʼ�Ծ֡�\n");
					continue;
				}
				status = unMakeMove();				// ���� - ����AI
				status = unMakeMove();				// ���� - �������
				break;
			}
			if (operation == Operation::TIPS) {
				if (stage != Stage::UNDERWAY) {
					printf_s("[��] �Ծ�δ��ʼ�������<newblack>/<newwhite>�Կ�ʼ�Ծ֡�\n");
					continue;
				}
				printf_s("[��] ֻҪ˼�벻���£������ܱȰ취�࣡\n");
				continue;
			}
			if (operation == Operation::EXIT) {
				printf_s("[��] ���˳���Ϸ��\n");
				exit(0);							// �˳�����
			}
		}
		// *** AI���о��� ***
		chess = getCurrentChess();
		if (stage != Stage::UNDERWAY)
			continue;
		if ((chess == Chess::BLACK) && (sente == Role::PLAYER))
			continue;
		if ((chess == Chess::WHITE) && (sente == Role::ROBOT))
			continue;
		move = getRobotDecision(*this);						// ��ȡ��������
		if (makeMove(move.x, move.y) != Status::S_OK) {		// ����
			printf_s("[��] AI���ϣ���������ֹ��\n");
			exit(1);
		}	
	}
	return;
}

/***************
* [����] �������� --- ���������Ϣ
***************/
void Game::describe() {
	printf_s("************* �������˻�����  Ver 0.1 *************\n\n");
	printf_s("<newblack>: ���Գֺ�����  <move x y>: ����  <tips>: ��ʾ\n");
	printf_s("<newwhite>: ���Գְ׺���  <withdraw>: ����  <exit>: �˳�\n\n");
	return;
}
