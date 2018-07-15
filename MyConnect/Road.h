#pragma once
//长为六的路
class Road
{
public:
	int row;//起点行
	int col;//起点列
	int dir;//该路的方向
	int num[3]; //该路中白子黑子的数量
	int index; //路在tables中的下标
	bool active; //是否有效，定义有效：该路中白子为0或者黑子为0
	Road() {}
	Road(int row, int col, int dir, int whites, int blacks, bool active, int index)
	{
		this->row = row;
		this->col = col;
		this->num[0] = blacks;
		this->num[1] = whites;
		this->dir = dir;
		this->active = active;
		this->index = index;
	}
};