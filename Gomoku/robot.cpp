#include "robot.h"

using namespace std;


std::vector<Move> Robot::createMoves(Chessboard& chessboard) {
	// TODO
	return vector<Move>();
}

//估值算法，返回估值
int Robot::evaluate(Chessboard& chessboard) {

	return  0;
}
//由于五子棋搜索分支庞大，通常无法直接搜索到胜负终局，当搜索到一定深度时需要根据局面返回搜索结果。
//参考资料：
//张明亮, 吴俊, 李凡长. 五子棋机器博弈系统评估函数的设计[J]. 计算机应用, 2012, 32(07):1969-1972.
//裴博文. 五子棋人工智能权重估值算法[J]. 电脑编程技巧与维护, 2008(6):69-75.
//https://www.cnblogs.com/maxuewei2/p/4825520.html


//搜索函数主体
int Robot::searchMove(Chessboard& chessboard)  {
	return 0;
}
