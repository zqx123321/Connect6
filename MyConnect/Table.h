#pragma once
#include"Road.h"
#include"Config.h"
class Table
{
public:
	//·����
	Road *roadVector[ROW * COL * 4];
	int size;
	Table() { size = 0; };

	void Add(Road &road)
	{
		roadVector[size] = &road;
		road.index = size++;
	}
	//ɾ��Ԫ�أ������һ��Ԫ�ط��ڱ�ɾ����Ԫ���ϣ�Ȼ���Сsize
	void Remove(Road &road)
	{
		roadVector[road.index] = roadVector[--size];
		roadVector[road.index]->index = road.index;
	}
};