#include "game.h"
#include <iostream>

using namespace std;

/***************
* [����] ���к��� --- ��ڵ�
***************/
void Game::start() {
	// TODO
	cout << "*************�������˻�����AI*************" << endl;
	cout << "����: newblack  ��������" << endl;
	cout << "����: newwhite  ���Ժ���" << endl;
	cout << "����: move x y  ��ʾ���ӵ�" << endl;
	this->printChessboard();	
	return;
}