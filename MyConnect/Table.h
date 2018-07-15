#pragma once
#include"Road.h"
#include"Config.h"
class Table
{
public:
	//路数组
	Road *roadVector[ROW * COL * 4];
	int size;
	Table() { size = 0; };

	void Add(Road &road)
	{
		roadVector[size] = &road;
		road.index = size++;
	}
	//删除元素，把最后一个元素放在被删除的元素上，然后减小size
	void Remove(Road &road)
	{
		roadVector[road.index] = roadVector[--size];
		roadVector[road.index]->index = road.index;
	}
};