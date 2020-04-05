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
	Chess cur = getCurrentChess();	// ��������
	chessboard[x][y] = cur;

	// ���¸�������
	char c = chess2char(cur);
	horizontals[x - 1][y] = c;
	verticals[y - 1][x] = c;
	if (x + y <= GRID_NUM + 1) {
		up_diagonals[x + y - 2][y] = c;
	}
	else {
		up_diagonals[x + y - 2][GRID_NUM + 1 - x] = c;
	}
	if (y - x <= 0) {
		down_diagonals[y - x + GRID_NUM - 1][y] = c;
	}
	else {
		down_diagonals[y - x + GRID_NUM - 1][x] = c;
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
	horizontals[x - 1][y] = '0';
	verticals[y - 1][x] = '0';
	if (x + y <= GRID_NUM + 1) {
		up_diagonals[x + y - 2][y] = '0';
	}
	else {
		up_diagonals[x + y - 2][GRID_NUM + 1 - x] = '0';
	}
	if (y - x <= 0) {
		down_diagonals[y - x + GRID_NUM - 1][y] = '0';
	}
	else {
		down_diagonals[y - x + GRID_NUM - 1][x] = '0';
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
	Move last = getLastMove();
	int y = last.x, x = last.y;
	char hrz[10] = "";
	char vtc[10] = "";
	char upd[10] = "";
	char dnd[10] = "";
	int xi = x - 4 < 1 ? 1 - x : -4;
	int xj = x + 4 < GRID_NUM ? 4 : GRID_NUM - x;
	int i = 0;
	for (int j = xi; j <= xj; j++) {
		hrz[i++] = horizontals[y - 1][x + j];
		cout << x + j << " " << y << endl;
	}
	int yi = y - 4 < 1 ? 1 - y : -4;
	int yj = y + 4 < GRID_NUM ? 4 : GRID_NUM - y;
	i = 0;
	for (int j = yi; j <= yj; j++) {
		vtc[i++] = verticals[x - 1][y + j];
		cout << x << " " << y + j << endl;
	}
	int ui = xi < -yj ? -yj : xi;
	int uj = xj < -yi ? xj : -yi;
	i = 0;
	for (; ui <= uj; ui++) {
		upd[i++] = chess2char(chessboard[y - ui][x + ui]);
		cout <<x + ui << " " << y - ui << endl;
	}
	int di = xi < yi ? yi : xi;
	int dj = xj < yj ? xj : yj;
	i = 0;
	for (; di <= dj; di++) {
		dnd[i++] = chess2char(chessboard[y + di][x + di]);
		cout << x + di << " " << y + di << endl;
	}
	
	if (std::regex_search(hrz, black_win)) {
		return Status::G_BLACK;
	}
	if (std::regex_search(hrz, white_win)) {
		return Status::G_WHITE;
	}
	if (std::regex_search(vtc, black_win)) {
		return Status::G_BLACK;
	}
	if (std::regex_search(vtc, white_win)) {
		return Status::G_WHITE;
	}
	if (std::regex_search(upd, black_win)) {
		return Status::G_BLACK;
	}
	if (std::regex_search(upd, white_win)) {
		return Status::G_WHITE;
	}
	if (std::regex_search(dnd, black_win)) {
		return Status::G_BLACK;
	}
	if (std::regex_search(dnd, white_win)) {
		return Status::G_WHITE;
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