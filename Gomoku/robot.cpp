#include "robot.h"

#include <regex>
using namespace std;

int *compute_prefix(char *P, int m)
{
	int *pi = new int[m + 1];
	pi[1] = 0;
	int k = 0;
	for (int q = 2; q <= m; q++)
	{
		while (k > 0 && P[k + 1] != P[q]) k = pi[k];
		if (P[k + 1] == P[q]) k++;
		pi[q] = k;
	}
	return pi;
}
int KMP_matcher(char *P, char*T, int m, int n)
{
	int *pi = compute_prefix(P, m);
	int sum = 0;
	int q = 0;
	for (int i = 1; i <= n; i++)
	{
		while (q > 0 && P[q + 1] != T[i]) q = pi[q];
		if (P[q + 1] == T[i]) q++;
		if (q == m)
		{
			sum++;
			q = pi[q];
		}
	}
	delete []pi;
	return sum;
}

/***************
* [����] ���캯��
***************/
Robot::Robot() {
	black_regex[0] = std::regex("11111");
	
	black_regex[1] = std::regex("011110");
	black_regex[2] = std::regex("11110|01111|11011|11101|10111");

	black_regex[3] = std::regex("001110|011100|011010|010110");
	black_regex[4] = std::regex("01110|1(110|101|011)0|0(101|011|110)1");
	black_regex[5] = std::regex("001100|01010|010010");
	white_regex[0] = std::regex("22222");
	white_regex[1] = std::regex("022220");
	white_regex[2] = std::regex("22220|02222|22022|22202|20222");

	white_regex[3] = std::regex("002220|022200|022020|020220");
	white_regex[4] = std::regex("02220|2(220|202|022)0|0(202|022|220)2");
	white_regex[5] = std::regex("002200|02020|020020");
	// black_regex[6] = std::regex("[2#]11000|[2#]10100|[2#]10010|00011[2#]|00101[2#]|01001[2#]");
	black_p[0] = pattern(".11111", 5);
	black_p[1] = pattern(".011110", 6);
	black_p[2] = pattern(".11110", 5);
	black_p[3] = pattern(".01111", 5);
	black_p[4] = pattern(".11101", 5);
	black_p[5] = pattern(".10111", 5);
	black_p[6] = pattern(".11011", 5);
	black_p[7] = pattern(".001110", 6);
	black_p[8] = pattern(".011100", 6);
	black_p[9] = pattern(".011010", 6);
	black_p[10] = pattern(".010110", 6);
	black_p[11] = pattern(".001100", 6);
	white_p[0] = pattern(".22222", 5);
	white_p[1] = pattern(".022220", 6);
	white_p[2] = pattern(".22220", 5);
	white_p[3] = pattern(".02222", 5);
	white_p[4] = pattern(".22202", 5);
	white_p[5] = pattern(".20222", 5);
	white_p[6] = pattern(".22022", 5);
	white_p[7] = pattern(".002220", 6);
	white_p[8] = pattern(".022200", 6);
	white_p[9] = pattern(".022020", 6);
	white_p[10] = pattern(".020220", 6);
	white_p[11] = pattern(".002200", 6);

	cost_self[0] = 300000; // ��
	cost_self[1] = 10000; 
	cost_self[2] = 1000; 
	cost_self[3] = 1000; 
	cost_self[4] = 1000; 
	cost_self[5] = 1000; 
	cost_self[6] = 1000; 
	cost_self[7] = 1000; 
	cost_self[8] = 1000; 
	cost_self[9] = 1000;
	cost_self[10] = 1000;
	cost_self[11] = 100;

	cost_opp[0] = 300000; // ��
	cost_opp[1] = 10000;
	cost_opp[2] = 1000;
	cost_opp[3] = 1000;
	cost_opp[4] = 1000;
	cost_opp[5] = 1000;
	cost_opp[6] = 1000;
	cost_opp[7] = 1000;
	cost_opp[8] = 1000;
	cost_opp[9] = 1000;
	cost_opp[10] = 1000;
	cost_opp[11] = 100;
	/*cost_self[0] = 300000; // ��
	cost_self[1] = 10000; //����
	cost_self[2] = 1000; //����
	cost_self[3] = 1000; // ����
	cost_self[4] = 100; // ����
	cost_self[5] = 100; // ���
	cost_self[6] = 10; // ����
	cost_self[7] = 10; // ��һ
	cost_self[8] = 1; // ��һ

	cost_opp[0] = 300000; // ��
	cost_opp[1] = 10000; //����
	cost_opp[2] = 1000; //����
	cost_opp[3] = 1000; // ����
	cost_opp[4] = 100; // ����
	cost_opp[5] = 100; // ���
	cost_opp[6] = 10; // ����
	cost_opp[7] = 10; // ��һ
	cost_opp[8] = 1; // ��һ*/
	return;
}

/***************
* [����] ��������
***************/
Robot::~Robot() {
	return;
}

/***************
* [����] ��ȡ�������� --- �ӿ�
* ����  Chessboard& chessboard: ����, Chess chess: ��ɫ
***************/
Move Robot::getRobotDecision(Chessboard& chessboard) {
	// �ײ� - ��Ԫ
	if (chessboard.getCurrentStep() == 1)
		return Move((GRID_NUM + 1) >> 1, (GRID_NUM + 1) >> 1);
	// ��������
	int x = chessboard.getCurrentStep();
	cout << "ǰ��" << x << endl;

	chess = chessboard.getCurrentChess();	// ��¼��ִ��ɫ

	x = chessboard.getCurrentStep();
	cout << "��" << x << endl;
	

	return searchMove(chessboard);
}

/***************
* [����] ��ȡ�Ϸ����ӵ�
***************/
vector<Move> Robot::createMoves(Chessboard& chessboard) {
	vector<Move> moves;
	for (int i = 1; i <= GRID_NUM; i++)
		for (int j = GRID_NUM; j >= 1; j--)
			if (chessboard.possibleMoves[i][j] > 0 && chessboard.possibleMoves[i][j] <= chessboard.fnum)
				moves.push_back(Move(i, j));
    
	return moves;
}

/***************
* [����] ��ֵ�㷨
* ��������� chess, ȷ����ǰ��ɫ
***************/
int Robot::evaluate(Chessboard& chessboard) {
	int black_value = 0;
	int white_value = 0;
	int cost_black[20];
	int cost_white[20];
	// ���ݴ�ʱ�����巽��ֵ��������
	if (chess == Chess::BLACK) {
		memcpy(cost_black, cost_self, 20 * sizeof(int));
		memcpy(cost_white, cost_opp, 20 * sizeof(int));
	}
	else {
		memcpy(cost_black, cost_opp, 20 * sizeof(int));
		memcpy(cost_white, cost_self, 20 * sizeof(int));
	}
	/*
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		for (int j = 0; j < 6; j++)
		{
			int blacksum = 0, whitesum = 0;
			std::cmatch cm;
			if (i < GRID_NUM) {
				std::regex_search(chessboard.horizontals[i], cm, black_regex[j]);
				blacksum += cm.size();
				std::regex_search(chessboard.verticals[i], cm, black_regex[j]);
				blacksum += cm.size();
				std::regex_search(chessboard.horizontals[i], cm, white_regex[j]);
				whitesum += cm.size();
				std::regex_search(chessboard.verticals[i], cm, white_regex[j]);
				whitesum += cm.size();
			}

			std::regex_search(chessboard.up_diagonals[i], cm, black_regex[j]);
			blacksum += cm.size();
			std::regex_search(chessboard.down_diagonals[i], cm, black_regex[j]);
			blacksum += cm.size();
			std::regex_search(chessboard.up_diagonals[i], cm, white_regex[j]);
			whitesum += cm.size();
			std::regex_search(chessboard.down_diagonals[i], cm, white_regex[j]);
			whitesum += cm.size();

			black_value += blacksum * cost_black[j];
			white_value += whitesum * cost_white[j];
		}
	}
	*/
	/*
	std::regex exist_regex("[12]");
	for (int i = 0; i < 15; i++) {
		if (!std::regex_search(chessboard.horizontals[i], exist_regex))
			continue;
		for (int j = 0; j < 11; j++)
		{
			//std::cmatch cm;
			//std::regex_search(chessboard.horizontals[i], cm, black_regex[j]);
			
			//black_value += cm.size() * cost_black[j];
			black_value += KMP_matcher(black_p[j].P, chessboard.horizontals[i], black_p[j].m, GRID_NUM) * cost_black[j];
			white_value += KMP_matcher(white_p[j].P, chessboard.horizontals[i], white_p[j].m, GRID_NUM) * cost_white[j];
			
			//std::regex_search(chessboard.horizontals[i], cm, white_regex[j]);
			//white_value += cm.size() * cost_white[j];
		}
	}
	for (int i = 0; i < 15; i++) {
		if (!std::regex_search(chessboard.verticals[i], exist_regex))
			continue;
		for (int j = 0; j < 6; j++)
		{
			std::cmatch cm;
			std::regex_search(chessboard.verticals[i], cm, black_regex[j]);
			black_value += cm.size() * cost_black[j];
			std::regex_search(chessboard.verticals[i], cm, white_regex[j]);
			white_value += cm.size() * cost_white[j];
		}
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		if (!std::regex_search(chessboard.up_diagonals[i], exist_regex))
			continue;
		for (int j = 0; j < 6; j++)
		{
			std::cmatch cm;
			std::regex_search(chessboard.up_diagonals[i], cm, black_regex[j]);
			black_value += cm.size() * cost_black[j];
			std::regex_search(chessboard.up_diagonals[i], cm, white_regex[j]);
			white_value += cm.size() * cost_white[j];
		}
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		if (!std::regex_search(chessboard.down_diagonals[i], exist_regex))
			continue;
		for (int j = 0; j < 6; j++)
		{
			std::cmatch cm;
			std::regex_search(chessboard.down_diagonals[i], cm, black_regex[j]);
			black_value += cm.size() * cost_black[j];
			std::regex_search(chessboard.down_diagonals[i], cm, white_regex[j]);
			white_value += cm.size() * cost_white[j];
		}
	}
	*/
	std::regex exist_regex("[12]");
	for (int i = 0; i < GRID_NUM; i++) {
		if (!std::regex_search(chessboard.horizontals[i], exist_regex))
			continue;
		for (int j = 0; j < 12; j++)
		{
			black_value += KMP_matcher(black_p[j].P, chessboard.horizontals[i], black_p[j].m, GRID_NUM) * cost_black[j];
			white_value += KMP_matcher(white_p[j].P, chessboard.horizontals[i], white_p[j].m, GRID_NUM) * cost_white[j];
		}
	}
	for (int i = 0; i < GRID_NUM; i++) {
		if (!std::regex_search(chessboard.verticals[i], exist_regex))
			continue;
		for (int j = 0; j < 12; j++)
		{
			black_value += KMP_matcher(black_p[j].P, chessboard.verticals[i], black_p[j].m, GRID_NUM) * cost_black[j];
			white_value += KMP_matcher(white_p[j].P, chessboard.verticals[i], white_p[j].m, GRID_NUM) * cost_white[j];
		}
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		if (!std::regex_search(chessboard.up_diagonals[i], exist_regex))
			continue;
		int len = 15 - abs(14 - i);
		for (int j = 0; j < 12; j++)
		{
			black_value += KMP_matcher(black_p[j].P, chessboard.up_diagonals[i], black_p[j].m, len) * cost_black[j];
			white_value += KMP_matcher(white_p[j].P, chessboard.up_diagonals[i], white_p[j].m, len) * cost_white[j];
		}
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		if (!std::regex_search(chessboard.down_diagonals[i], exist_regex))
			continue;
		int len = 15 - abs(14 - i);
		for (int j = 0; j < 12; j++)
		{
			black_value += KMP_matcher(black_p[j].P, chessboard.down_diagonals[i], black_p[j].m, len) * cost_black[j];
			white_value += KMP_matcher(white_p[j].P, chessboard.down_diagonals[i], white_p[j].m, len) * cost_white[j];
		}
	}
	if (chess == Chess::BLACK)
		return (black_value - white_value);
	else
		return (white_value - black_value);
}
//����������������֧�Ӵ�ͨ���޷�ֱ��������ʤ���վ֣���������һ�����ʱ��Ҫ���ݾ��淵�����������
//�ο����ϣ�
//������, �⿡, ���. �������������ϵͳ�������������[J]. �����Ӧ��, 2012, 32(07):1969-1972.
//�Ჩ��. �������˹�����Ȩ�ع�ֵ�㷨[J]. ���Ա�̼�����ά��, 2008(6):69-75.
//https://www.cnblogs.com/maxuewei2/p/4825520.html

/***************
* [����] �����㷨
* ʹ�æ�-�¼�֦
***************/
Move Robot::searchMove(Chessboard& chessboard)  {
	int depth = 1, a = MIN_VALUE, b = MAX_VALUE;
	int max_value = MIN_VALUE, tmp_value = 0;
	Move move(0, 0);
	vector<Move> moves = createMoves(chessboard);
	for (auto m : moves) {
		chessboard.makeMove(m.x, m.y);
		tmp_value = minValue(chessboard, depth + 1, a, b);
		chessboard.unMakeMove();
		if (tmp_value > max_value) {
			max_value = tmp_value;
			move = m;
		}
		if (max_value > a)
			a = max_value;
	}
	return move;
}

/***************
* [����] minimax�Կ����� - MAX
* ʹ�æ�-�¼�֦
* ѭ������ʽ: ����ʱ����ʱ�ľ����ڴ��ҷ�����
* ѭ������ʽ: ����ǰ��chessboard״̬����
***************/
int Robot::maxValue(Chessboard& chessboard, int depth, int a, int b) {
	if (depth > MAX_DEPTH)
		return evaluate(chessboard);
	int max_value = MIN_VALUE, tmp_value = 0;
	vector<Move> moves = createMoves(chessboard);
	for (auto m : moves) {
		chessboard.makeMove(m.x, m.y);
		tmp_value = minValue(chessboard, depth + 1, a, b);
		chessboard.unMakeMove();
		if (tmp_value > max_value)
			max_value = tmp_value;
		if (max_value >= b)
			return max_value;
		if (max_value > a)
			a = max_value;
	}
	return max_value;
}

/***************
* [����] minimax�Կ����� - MIN
* ʹ�æ�-�¼�֦
* ѭ������ʽ: ����ʱ����ʱ�ľ����ڴ��Է�����
* ѭ������ʽ: ����ǰ��chessboard״̬����
***************/
int Robot::minValue(Chessboard& chessboard, int depth, int a, int b) {
	if (depth > MAX_DEPTH)
		return evaluate(chessboard);
	int min_value = MAX_VALUE, tmp_value = 0;
	vector<Move> moves = createMoves(chessboard);
	for (auto m : moves) {
		chessboard.makeMove(m.x, m.y);
		tmp_value = maxValue(chessboard, depth + 1, a, b);
		chessboard.unMakeMove();
		if (tmp_value < min_value)
			min_value = tmp_value;
		if (min_value <= a)
			return min_value;
		if (min_value < b)
			b = min_value;
	}
	return min_value;
}
