#pragma once

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <fstream>
#include <ctime>
#include <queue>

#define INF 5000000
#define BLACK 0
#define WHITE 1
#define NOCHESS 2
#define ROW 19
#define COL 19
#define DEPTH 6
#define TSSDEPTH 13
#define MAXNODE 100

using namespace std;

//��·��ֵ�������ۣ��Է�·���ҷ�·�Ĺ�ֵ��ͬ
const int score[2][7] = {
	{ 0, 9, 520, 2070, 7890, 10020, 1000000 },
	{ 0, 3, 480, 2670, 3887, 4900, 1000000 }
};

//�ĸ�����
const int DIR[4][2] ={
	{ 0, 1 },{ 1, 0 },{ 1, 1 },{ 1, -1 }
};

//��Χ��ʮ����
const int range[24][2] ={
	{ 1, 0 },
	{ 0, 1 },
	{ -1, 0 },
	{ 0, -1 },
	{ 1, -1 },
	{ -1, 1 },
	{ 1, 1 },
	{ -1, -1 },
	{ 2, 0 },
	{ 0, 2 },
	{ -2, 0 },
	{ 0, -2 },
	{ 2, -2 },
	{ -2, 2 },
	{ 2, 2 },
	{ -2, -2 },
	{ 3, 0 },
	{ 0, 3 },
	{ -3, 0 },
	{ 0, -3 },
	{ 3, -3 },
	{ -3, 3 },
	{ 3, 3 },
	{ -3, -3 }
};

//����Ϊ��̬���ֿ�
const int open[4][4] = {
	{ 1,0,1,1 },
	{ 1,0,1,-1 },
	{ -1,0,-1,1 },
	{ -1,0,-1,-1 },
};