#include "robot.h"
#include <regex>
using namespace std;

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
	// black_regex[6] = std::regex("[2#]11000|[2#]10100|[2#]10010|00011[2#]|00101[2#]|01001[2#]");

	cost_self[0] = 300000; // ��
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
	cost_opp[8] = 1; // ��һ
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
Move Robot::getRobotDecision(Chessboard& chessboard, Chess chess) {
	// TODO
	return Move(1, 1);

}

/***************
* [����] ��ȡ�Ϸ����ӵ�
***************/
vector<Move> Robot::createMoves(Chessboard& chessboard) {
	// TODO
	vector<Move> moves;
	for (int i = 1; i <= GRID_NUM; i++) {
		for (int j = 1; j <= GRID_NUM; j++) {
			if (chessboard.possibleMoves[i][j] > 0 && chessboard.possibleMoves[i][j] < 25)
				moves.push_back(Move(i, j));
		}
	}
	return moves;
}

/***************
* [����] ��ֵ�㷨
***************/
int Robot::evaluate(Chessboard& chessboard) {
	int black_value = 0;
	int white_value = 0;
	int cost_black[10];
	int cost_white[10];

	// ���ݴ�ʱ�����巽��ֵ��������
	if (chessboard.getCurrentChess() == Chess::BLACK) {
		memcpy(cost_black, cost_self, 10 * sizeof(int));
		memcpy(cost_white, cost_opp, 10 * sizeof(int));
	}
	else {
		memcpy(cost_black, cost_opp, 10 * sizeof(int));
		memcpy(cost_white, cost_self, 10 * sizeof(int));
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		for (int j = 0; j < 6; j++)
		{
			int blacksum = 0, whitesum = 0;
			std::cmatch cm;
			if (i < GRID_NUM) {
				std::regex_search(chessboard.horizontals[i], cm, black_regex[i]);
				blacksum += cm.size();
				std::regex_search(chessboard.verticals[i], cm, black_regex[i]);
				blacksum += cm.size();
				std::regex_search(chessboard.horizontals[i], cm, white_regex[i]);
				whitesum += cm.size();
				std::regex_search(chessboard.verticals[i], cm, white_regex[i]);
				whitesum += cm.size();
			}
			
			std::regex_search(chessboard.up_diagonals[i], cm, black_regex[i]);
			blacksum += cm.size();
			std::regex_search(chessboard.down_diagonals[i], cm, black_regex[i]);
			blacksum += cm.size();
			std::regex_search(chessboard.up_diagonals[i], cm, white_regex[i]);
			whitesum += cm.size();
			std::regex_search(chessboard.down_diagonals[i], cm, white_regex[i]);
			whitesum += cm.size();

			black_value += cm.size() * cost_black[i];
			white_value += cm.size() * cost_white[i];
		}
	}
	/*
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 6; j++)
		{
			std::cmatch cm;
			std::regex_search(chessboard.verticals[i], cm, black_regex[i]);
			black_value += cm.size() * cost_self[i];
		}
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		for (int j = 0; j < 6; j++)
		{
			std::cmatch cm;
			std::regex_search(chessboard.up_diagonals[i], cm, black_regex[i]);
			black_value += cm.size() * cost_self[i];
		}
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		for (int j = 0; j < 6; j++)
		{
			std::cmatch cm;
			std::regex_search(chessboard.down_diagonals[i], cm, black_regex[i]);
			black_value += cm.size() * cost_self[i];
		}
	}*/
	if (chessboard.getCurrentChess() == Chess::BLACK)
	    return (black_value - white_value);
	else
	    return (white_value - black_value);
}
//����������������֧�Ӵ�ͨ���޷�ֱ��������ʤ���վ֣���������һ�����ʱ��Ҫ���ݾ��淵�����������
//�ο����ϣ�
//������, �⿡, ���. �������������ϵͳ�������������[J]. �����Ӧ��, 2012, 32(07):1969-1972.
//�Ჩ��. �������˹�����Ȩ�ع�ֵ�㷨[J]. ���Ա�̼�����ά��, 2008(6):69-75.
//https://www.cnblogs.com/maxuewei2/p/4825520.html

int Robot::evaluate(Chessboard& chessboard, Move& p) {
	return 0;
}

/***************
* [����] �����㷨
***************/
int Robot::searchMove(Chessboard& chessboard)  {
	return 0;
}
