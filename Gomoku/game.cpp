#include "game.h"
#include <iostream>
#include <string>
using namespace std;

/***************
* [����] ���к��� --- ������ѭ��
***************/
void Game::start() {
	// TODO
	while (true) {
		// �����Ļ
		system("cls");
		// ��ӡ������Ϣ
		this->describe();
		// ��ӡ����
		this->printChessboard();
		// ���� - ��ȡ/����û�����
		this->getUserInput(Chess::BLACK);
		cout << int(this->getOperation()) << endl;
		cout << this->getMove().x << endl;
		cout << this->getMove().y << endl;
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