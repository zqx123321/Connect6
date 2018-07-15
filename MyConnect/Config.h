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

//按路估值分数评价，对方路和我方路的估值不同
const int score[2][7] = {
	{ 0, 9, 520, 2070, 7890, 10020, 1000000 },
	{ 0, 3, 480, 2670, 3887, 4900, 1000000 }
};

//四个方向
const int DIR[4][2] ={
	{ 0, 1 },{ 1, 0 },{ 1, 1 },{ 1, -1 }
};

//周围二十四子
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

//更新为动态开局库
const int open[4][4] = {
	{ 1,0,1,1 },
	{ 1,0,1,-1 },
	{ -1,0,-1,1 },
	{ -1,0,-1,-1 },
};