#include "game.h"
#include <iostream>
#include <string>
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
	char buffer[100] = "";
	char a[100], b[100], c[200];
	int x; int y;
	while (true) {
		printf_s("[��] ���Ļغϣ����������:");
		scanf_s("%[^\n]%*c", buffer, sizeof(buffer));
		sscanf_s(buffer, "%s %d %d", a, sizeof(a), &x, &y);
		cout << a << endl << x << endl << y << endl;
	}
	return;
}
