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
	// ���ø�������
	for (int i = 0; i < GRID_NUM; i++) {
		for (int j = 1; j <= GRID_NUM; j++) {
			horizontals[i][j] = '0';
			verticals[i][j] = '0';
		}
		horizontals[i][0] = horizontals[i][GRID_NUM + 1] = '#';
		verticals[i][0] = verticals[i][GRID_NUM + 1] = '#';
		horizontals[i][GRID_NUM + 2] = verticals[i][GRID_NUM + 2] = '\0';
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		int len = 15 - abs(14 - i);
		for (int j = 1; j <= len; j++) {
			up_diagonals[i][j] = '0';
			down_diagonals[i][j] = '0';
		}
		up_diagonals[i][0] = up_diagonals[i][len + 1] = '#';
		down_diagonals[i][0] = down_diagonals[i][len + 1] = '#';
		up_diagonals[i][len + 2] = down_diagonals[i][len + 2] = '\0';
	}
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
	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			if (x + i < 1 || x + i > GRID_NUM || y + j < 1 || y + j > GRID_NUM)
				continue;
			possibleMoves[x + i][y + j]++;
		}
	}
	possibleMoves[x][y] += 25;
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

	// ����possibleMoves����
	// �ȸ��µ�ǰ��
	possibleMoves[x][y] -= 25;
	/*
	bool isPossible = false;
	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			if (x + i < 1 || x + i > GRID_NUM || y + j < 1 || y + j > GRID_NUM)
				continue;
			if (possibleMoves[x + i][y + j] == Chess::BLACK) {
				isPossible = true;
			}
		}
	}
	if (isPossible) {
		possibleMoves[x][y] = Chess::POSSIBLE;
	}
	else {
		possibleMoves[x][y] = Chess::BLANK;
	}*/
	
	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			if (x + i < 1 || x + i > GRID_NUM || y + j < 1 || y + j > GRID_NUM)
				continue;
			/*
			if (possibleMoves[x + i][y + j] == Chess::POSSIBLE) {
				bool isPossible = false;
				int s = x + i, t = y + j;
				for (int m = -2; m <= 2; m++) {
					for (int n = -2; n <= 2; n++) {
						if (s + m < 1 || s + m > GRID_NUM || t + n < 1 || t + n > GRID_NUM)
							continue;
						if (possibleMoves[s + m][t + n] == Chess::BLACK)
							isPossible = true;
					}
				}
				if (!isPossible)
				    possibleMoves[x + i][y + j] = Chess::BLANK;
			}	*/
			possibleMoves[x + i][y + j]--;
		}
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
	if (chessRecord.empty())
		return Status::G_CONTINUE;
	Move last = chessRecord.back();
	std::regex black_win("11111");
	std::regex white_win("22222");
	
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
	// ��ӡ������
	printf_s("   ");
	for (int i = 1; i <= 15; i++)
		printf_s("%2X", i);
	printf_s("\n");
	for (int i = 1; i <= 15; i++) {
		printf_s(" %2X", i);	// ��ӡ������
		for (int j = 1; j <= 15; j++) {
			if (chessboard[i][j] == Chess::BLACK)
				printf_s("��");		// ��ӡ����
			else if (chessboard[i][j] == Chess::WHITE)
				printf_s("��");		// ��ӡ����
			else {
				// �߽��ӡ
				if (i == 1 && j == 1)
					printf_s("�X ");
				else if (i == 1 && j == 15)
					printf_s("�[");
				else if (i == 15 && j == 1)
					printf_s("�^ ");
				else if (i == 15 && j == 15)
					printf_s("�a");
				else if (i == 1 && j != 15 && j != 1)
					printf_s("�� ");
				else if (i == 15 && j != 15 && j != 1)
					printf_s("�� ");
				else if (j == 1 && i != 15 && i != 1)
					printf_s("�� ");
				else if (j == 15 && i != 15 && i != 1)
					printf_s("��");
				else
					printf_s("�� ");
			}
		}
		printf_s("\n");
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
	if (step <= 0 || step > int(chessRecord.size()))
		return false;
	char label[20];
	sprintf_s(label, "����%d����", step);
	if (step & 1)
		printf("%-12s �� �� (%X, %X)\n", label, chessRecord[step - 1].x, chessRecord[step - 1].y);
	else
		printf("%-12s �� �� (%X, %X)\n", label, chessRecord[step - 1].x, chessRecord[step - 1].y);
	return true;
}