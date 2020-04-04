#include "chessboard.h"
#include <string.h> 
#include <regex>
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
	Chess cur = getCurrentChess();	// ��������
	chessboard[x][y] = cur;

	// ���¸�������
	char c = chess2char(cur);
	horizontals[y - 1][x] = c;
	verticals[x - 1][y] = c;
	if (x + y <= GRID_NUM + 1) {
		up_diagonals[x + y - 2][x] = c;
	}
	else {
		up_diagonals[x + y - 2][GRID_NUM + 1 - y] = c;
	}
	if (x - y <= 0) {
		down_diagonals[x - y + GRID_NUM - 1][x] = c;
	}
	else {
		down_diagonals[x - y + GRID_NUM - 1][y] = c;
	}
	
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
	int x = move.x, y = move.y;
	chessboard[x][y] = Chess::BLANK;	 // ��������

	// ���¸�������
	horizontals[y - 1][x] = '0';
	verticals[x - 1][y] = '0';
	if (x + y <= GRID_NUM + 1) {
		up_diagonals[x + y - 2][x] = '0';
	}
	else {
		up_diagonals[x + y - 2][GRID_NUM + 1 - y] = '0';
	}
	if (x - y <= 0) {
		down_diagonals[x - y + GRID_NUM - 1][x] = '0';
	}
	else {
		down_diagonals[x - y + GRID_NUM - 1][y] = '0';
	}

	chessRecord.pop_back();						// ���¼�¼
	return Status::S_OK;
}

/***************
* [����] ���ʤ���ж�
* ����  G_BLACK | G_WHITE | G_DRAW | G_CONTINUE
***************/
Status Chessboard::gameOver() {
	// ������ʽ�ж��Ƿ������������
	std::regex black_win("11111");
	std::regex white_win("22222");
	for (int i = 0; i < GRID_NUM; i++) {
		if (std::regex_match(horizontals[i], black_win)) {
			return Status::G_BLACK;
		}
		if (std::regex_match(horizontals[i], white_win)) {
			return Status::G_WHITE;
		}
	}
	for (int i = 0; i < GRID_NUM; i++) {
		if (std::regex_match(verticals[i], black_win)) {
			return Status::G_BLACK;
		}
		if (std::regex_match(verticals[i], white_win)) {
			return Status::G_WHITE;
		}
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		if (std::regex_match(up_diagonals[i], black_win)) {
			return Status::G_BLACK;
		}
		if (std::regex_match(up_diagonals[i], white_win)) {
			return Status::G_WHITE;
		}
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		if (std::regex_match(down_diagonals[i], black_win)) {
			return Status::G_BLACK;
		}
		if (std::regex_match(down_diagonals[i], white_win)) {
			return Status::G_WHITE;
		}
	}
	
	if (getCurrentStep() > GRID_NUM * GRID_NUM) {
		return Status::G_DRAW; // �;�
	}
	return Status::G_CONTINUE;
}

/***************
* [����] ��ӡ����
***************/
void Chessboard::printChessboard() {
	// ��ӡ������
	printf("   ");
	for (int i = 1; i <= 15; i++)
		printf("%2X", i);
	printf("\n");
	for (int i = 1; i <= 15; i++) {
		printf(" %2X", i);	// ��ӡ������
		for (int j = 1; j <= 15; j++) {
			if (chessboard[i][j] == Chess::BLACK)
				printf("��");		// ��ӡ����
			else if (chessboard[i][j] == Chess::WHITE)
				printf("��");		// ��ӡ����
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
	return;
}

/***************
* [����] ��ӡ���̼�¼
* ����  ��������������������
* ����  true - ��ӡ�ɹ�, false - ��ӡʧ��
***************/
bool Chessboard::printChessRecord(int step) {
	if (step <= 0)
		step += (chessRecord.size() + 1);
	if (step <= 0 || step > chessRecord.size())
		return false;
	char label[20];
	sprintf_s(label, "����%d����", step);
	if (step & 1)
		printf("%-12s �� �� (%X, %X)\n", label, chessRecord[step - 1].x, chessRecord[step - 1].y);
	else
		printf("%-12s �� �� (%X, %X)\n", label, chessRecord[step - 1].x, chessRecord[step - 1].y);
	return true;
}