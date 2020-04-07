#include "game.h"
#include <iostream>
#include <string>
using namespace std;

const bool DEBUG_MODE = true;

/***************
* [����] ���캯��
***************/
Game::Game(): sente(Role::DEFAULT), winner(Chess::BLANK), stage(Stage::DEFAULT) {
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
		if (!DEBUG_MODE) system("cls");					// �����Ļ			
		describe();						// ��ӡ������Ϣ
		printChessboard();				// ��ӡ����
		printChessRecord(-2);			// ��ӡ��ּ�¼
		printChessRecord(-1);			// ��ӡ��ּ�¼
		if (stage == Stage::GAMEOVER) {	// ��ӡ��ʤ��Ϣ
			printf_s("%-12s", "����Ϸ������ ");
			if (winner == Chess::BLACK)
				printf_s("�� ��ʤ��\n");
			else if (winner == Chess::WHITE)
				printf_s("�� ��ʤ��\n");
			else
				printf_s("���壡\n");
		}
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
			// <newblack>
			if (operation == Operation::NEWBLACK) {
				sente = Role::ROBOT;		// �������з�
				stage = Stage::UNDERWAY;	// ������Ϸ�׶�
				initMove();					// ��������
				break;
			}
			// <newwhite>
			if (operation == Operation::NEWWHITE) {
				sente = Role::PLAYER;		// �������з�
				stage = Stage::UNDERWAY;	// ������Ϸ�׶�
				initMove();					// ��������
				break;
			}
			// <move>
			if (operation == Operation::MOVE) {
				if (stage == Stage::UNDERWAY) {
					// ����
					status = makeMove(move.x, move.y);
					if (DEBUG_MODE)
						printf_s("@ ������ӣ�(%d,%d,%d)\n", move.x, move.y, status);
					if (status == Status::F_OUTSIDE) {
						printf_s("[��] �Ƿ����� - ���⣡\n");
						continue;
					}
					if (status == Status::F_NOBLANK) {
						printf_s("[��] �Ƿ����� - �ǿգ�\n");
						continue;
					}
					// ʤ���ж�
					status = gameOver();
					if (status == Status::G_BLACK) {
						winner = Chess::BLACK;
						stage = Stage::GAMEOVER;
					}
					else if (status == Status::G_WHITE) {
						winner = Chess::WHITE;
						stage = Stage::GAMEOVER;
					}
					else if (status == Status::G_DRAW) {
						winner = Chess::BLANK;
						stage = Stage::GAMEOVER;
					}
					break;
				}
				if (stage == Stage::GAMEOVER) {
					printf_s("[��] �Ծ��ѽ����������<newblack>/<newwhite>�Կ�ʼ�¶Ծ֡�\n");
					continue;
				}
				if (stage == Stage::DEFAULT) {
					printf_s("[��] �Ծ�δ��ʼ�������<newblack>/<newwhite>�Կ�ʼ�Ծ֡�\n");
					continue;
				}
			}
			// <withdraw>
			if (operation == Operation::WITHDRAW) {
				if (stage == Stage::UNDERWAY || stage == Stage::GAMEOVER) {
					// ���� ���������԰����������
					status = unMakeMove();
					status = unMakeMove();
					stage = Stage::UNDERWAY;	// ��Ϸ����
					break;
				}
				if (stage == Stage::DEFAULT) {
					printf_s("[��] �Ծ�δ��ʼ�������<newblack>/<newwhite>�Կ�ʼ�Ծ֡�\n");
					continue;
				}
			}
			// <tips>
			if (operation == Operation::TIPS) {
				if (stage == Stage::UNDERWAY) {
					move = getRobotDecision(*this);
					printf_s("[��] AI���飺(%X, %X)\n", move.x, move.y);
					continue;
				}
				if (stage == Stage::GAMEOVER) {
					printf_s("[��] ��Ϸ�ѽ����������<newblack>/<newwhite>�Կ�ʼ�¶Ծ֣������<withdraw>�Ի��塣\n");
					continue;
				}
				if (stage != Stage::DEFAULT) {
					printf_s("[��] �Ծ�δ��ʼ�������<newblack>/<newwhite>�Կ�ʼ�Ծ֡�\n");
					continue;
				}
			}
			// <exit>
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
		if (DEBUG_MODE)
			printf_s("@ AI����ǰ������(%d)\n", getCurrentStep());
		move = getRobotDecision(*this);						// ��ȡ��������
		if (DEBUG_MODE)
			printf_s("@ AI���ߺ�����(%d)\n", getCurrentStep());
		// ����
		if (DEBUG_MODE)
			printf_s("@ AI���ӣ�(%d,%d)\n", move.x, move.y);
		if (makeMove(move.x, move.y) != Status::S_OK) {	
			printf_s("[��] AI���߹��ϣ���������ֹ��\n");
			exit(1);
		}
		// ʤ���ж�
		status = gameOver();
		if (status == Status::G_BLACK) {
			winner = Chess::BLACK;
			stage = Stage::GAMEOVER;
		}
		else if (status == Status::G_WHITE) {
			winner = Chess::WHITE;
			stage = Stage::GAMEOVER;
		}
		else if (status == Status::G_DRAW) {
			winner = Chess::BLANK;
			stage = Stage::GAMEOVER;
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
