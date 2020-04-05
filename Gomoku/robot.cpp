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
	black_regex[2] = std::regex("11101|10111");
	black_regex[2] = std::regex("11011");
	black_regex[3] = std::regex("0011100|[2#]011100|001110[2#]|011010|010110");
	black_regex[4] = std::regex("[2#]011110[2#]|[2#]1(110|101|011)0|0(101|011|110)1[2#]");
	black_regex[5] = std::regex("001100|01010|010010");
	black_regex[6] = std::regex("[2#]11000|[2#]10100|[2#]10010|00011[2#]|00101[2#]|01001[2#]");
	cost[0] = 1000000;
	cost[1] = 50000;
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
	return vector<Move>();
}

/***************
* [����] ��ֵ�㷨
***************/
int Robot::evaluate(Chessboard& chessboard) {
	int black_value = 0;
	int white_value = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 6; j++)
		{
			std::cmatch cm;
			std::regex_search(chessboard.horizontals[i], cm, black_regex[i]);
			black_value += cm.size();
		}
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 6; j++)
		{
			std::cmatch cm;
			std::regex_search(chessboard.verticals[i], cm, black_regex[i]);
			black_value += cm.size();
		}
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		for (int j = 0; j < 6; j++)
		{
			std::cmatch cm;
			std::regex_search(chessboard.up_diagonals[i], cm, black_regex[i]);
			black_value += cm.size();
		}
	}
	for (int i = 0; i < EFFECTIVE_DIAGONAL_NUM; i++) {
		for (int j = 0; j < 6; j++)
		{
			std::cmatch cm;
			std::regex_search(chessboard.down_diagonals[i], cm, black_regex[i]);
			black_value += cm.size();
		}
	}
	return (black_value - white_value);
	return  0;
}
//����������������֧�Ӵ�ͨ���޷�ֱ��������ʤ���վ֣���������һ�����ʱ��Ҫ���ݾ��淵�����������
//�ο����ϣ�
//������, �⿡, ���. �������������ϵͳ�������������[J]. �����Ӧ��, 2012, 32(07):1969-1972.
//�Ჩ��. �������˹�����Ȩ�ع�ֵ�㷨[J]. ���Ա�̼�����ά��, 2008(6):69-75.
//https://www.cnblogs.com/maxuewei2/p/4825520.html


/***************
* [����] �����㷨
***************/
int Robot::searchMove(Chessboard& chessboard)  {
	return 0;
}
