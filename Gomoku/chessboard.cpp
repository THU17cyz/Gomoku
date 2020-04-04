#include "chessboard.h"
#include <string.h> 
using namespace std;

/***************
* [����] ���캯��
***************/
Chessboard::Chessboard() {
	this->initMove();
	return;
}

/***************
* [����] ��������
***************/
Chessboard::~Chessboard() {
	return;
}

/***************
* [����] ��ֳ�ʼ��
***************/
void Chessboard::initMove() {
	this->clearChessboard();	// �������
	chessRecord.clear();		// ��ռ�¼
	return;
}

/***************
* [����] ���ִ���߷�
* ����  S_OK |  F_OUTSIDE | F_NOBLANK
***************/
Status Chessboard::makeMove(const int x, const int y) {
	// �ж��߷��Ƿ�Ϸ�
	if (!inChessboard(x, y))
		return Status::F_OUTSIDE;
	if (chessboard[x][y] != Chess::BLANK)
		return Status::F_NOBLANK;
	// ִ���߷�
	chessboard[x][y] = getCurrentChess();	// ��������
	chessRecord.push_back(Move(x, y));		// ���¼�¼
	return Status::S_OK;
}


/***************
* [����] ��ֳ����߷�
* ����  S_OK | F_NOLAST
***************/
Status Chessboard::unMakeMove() {
	// �ж��ܷ���
	if (chessRecord.empty())
		return Status::F_NOLAST;
	// �����߷�
	Move move = chessRecord.back();
	chessboard[move.x][move.y] = Chess::BLANK;	// ��������
	chessRecord.pop_back();						// ���¼�¼
	return Status::S_OK;
}

/***************
* [����] ���ʤ���ж�
* ����  G_BLACK | G_WHITE | G_DRAW | G_CONTINUE
***************/
Status Chessboard::gameOver() {
	// TODO
	return Status::G_CONTINUE;
}

/***************
* [����] ��ӡ����
***************/
void Chessboard::printChessboard() {
	// TODO
	for (int i = 0; i < 16; i++) {
		if (i == 0) {
			printf("  ");
			for (int j = 1; j < 16; j++)
				printf("%-2d", j);
			printf("\n");
			continue;
		}
		for (int j = 0; j < 16; j++) {
			if (j == 0) {
				printf("%2d", i);
				continue;
			}
			if (chessboard[i][j] == Chess::BLACK)		//�˴�Ϊ����
				printf("��");
			else if (chessboard[i][j] == Chess::WHITE)	//�˴�Ϊ����
				printf("��");
			else {
				// �߽��ӡ
				if (i == 1 && j == 1)
					printf("�X ");
				else if (i == 1 && j == 15)
					printf("�[");
				else if (i == 15 && j == 1)
					printf("�^ ");
				else if (i == 15 && j == 15)
					printf("�a");
				else if (i == 1 && j != 15 && j != 1)
					printf("�� ");
				else if (i == 15 && j != 15 && j != 1)
					printf("�� ");
				else if (j == 1 && i != 15 && i != 1)
					printf("�� ");
				else if (j == 15 && i != 15 && i != 1)
					printf("��");
				else
					printf("�� ");
			}
		}
		printf("\n");
	}
}