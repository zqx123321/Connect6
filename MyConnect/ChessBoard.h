#pragma once
#include"Table.h"
#include"Utils.h"
#include"Step.h"
#include"Point.h"
class ChessBoard {
private:
	//���Ƿ�Χ
	int cover[ROW][COL];
	bool vis[ROW][COL];
	vector <Point> pointVector;

public:
	//tables[i][j]��ʾ����·���ҷ���i���ӣ��Է���2����
	Table tables[7][7];
	int board[ROW][COL];
	//ÿ�����ĸ������ϵ�·
	Road segment[ROW][COL][4];
	//���췽��
	ChessBoard() {
		for (int i = 0; i < ROW; i++){
			for (int j = 0; j < COL; j++){
				for (int k = 0; k < 4; k++){
					Road road(i, j, k, 0, 0, false, 0);
					segment[i][j][k] = road;
					if (Utils::isLegal(i + 5 * DIR[k][0], j + 5 * DIR[k][1])){
						road.active = true;
						tables[0][0].Add(road);
					}
				}
				cover[i][j] = 0;
				board[i][j] = NOCHESS;
			}
		}
	};
	//��ʼ��
	void init() {
		for (int i = 0; i < 7; i++){
			for (int j = 0; j < 7; j++){
				tables[i][j].size = 0;
			}
		}

		for (int i = 0; i < ROW; i++){
			for (int j = 0; j < COL; j++){
				for (int k = 0; k < 4; k++) {
					Road &road = (segment[i][j][k] = Road(i, j, k, 0, 0, false, 0));
					if (Utils::isLegal(i + 5 * DIR[k][0], j + 5 * DIR[k][1])) {
						road.active = true;
						tables[0][0].Add(road);
					}
				}
				cover[i][j] = 0;
				board[i][j] = NOCHESS;
			}
		}
	}

	//��ȡ�����ֵ
	int getValue(int type) {
		int res = 0;
		for (int i = 1; i <= 6; i++){
			res += tables[i][0].size * score[type][i] - tables[0][i].size * score[type^1][i];
		}
		//������ֵ��Է���ֵ��ͬ
		return (type == BLACK ? res : -res);
	}

	//��ȡ��ɫ
	int getCell(int row, int col){
		return board[row][col];
	}

	//��������
	void makeMove(int row, int col, int type){
		int xt, yt;
		board[row][col] = type;
		cover[row][col]++;
		//����֮����¸��Ƿ�Χ
		for (int i = 0; i < 24; i++){
			xt = row + range[i][0], yt = col + range[i][1];
			if (Utils::isLegal(xt, yt)){
				cover[xt][yt]++;
			}
		}
		//����·��
		for (int i = 0; i < 4; i++){
			xt = row, yt = col;
			if (segment[xt][yt][i].active){
				Road &road = segment[xt][yt][i];
				tables[road.num[0]][road.num[1]].Remove(road);
				road.num[type]++;
				tables[road.num[0]][road.num[1]].Add(road);
			}                                                                                                                                                                                                                                                                                                                                                                                                                                                         
			for (int j = 0; j < 5; j++){
				xt -= DIR[i][0], yt -= DIR[i][1];
				if (Utils::isLegal(xt, yt)){
					if (segment[xt][yt][i].active){
						Road &road = segment[xt][yt][i];
						tables[ road.num[0]][road.num[1]].Remove(road);
						road.num[type]++;
						tables[road.num[0]][road.num[1]].Add(road);
					}
				}
				else break;
			}
		}
	}
	//����ȡ������
	void unMakeMove(int row, int col, int type){
		int xt, yt;
		board[row][col] = NOCHESS;
		cover[row][col]--;
		for (int i = 0; i < 24; i++){
			xt = row + range[i][0], yt = col + range[i][1];
			if (Utils::isLegal(xt, yt)){
				cover[xt][yt]--;
			}
		}
		for (int i = 0; i < 4; i++){
			xt = row, yt = col;
			if (segment[xt][yt][i].active) {
				Road &road = segment[xt][yt][i];
				tables[road.num[0]][road.num[1]].Remove(road);
				road.num[type]--;
				tables[road.num[0]][road.num[1]].Add(road);
			}
			for (int j = 0; j < 5; j++){
				xt -= DIR[i][0], yt -= DIR[i][1];
				if (Utils::isLegal(xt, yt)){
					if (segment[xt][yt][i].active) {
						Road &road = segment[xt][yt][i];
						tables[road.num[0]][road.num[1]].Remove(road);
						road.num[type]--;
						tables[road.num[0]][road.num[1]].Add(road);
					}
				}
				else break;
			}
		}
	}
	//��������
	void virtualMakeMove(int row, int col, int type){
		int xt, yt;
		board[row][col] = type;
		for (int i = 0; i < 4; i++){
			xt = row, yt = col;
			if (segment[xt][yt][i].active){
				Road &road = segment[xt][yt][i];
				tables[road.num[0]][road.num[1]].Remove(road);
				road.num[type]++;
				tables[road.num[0]][road.num[1]].Add(road);
			}
			for (int j = 0; j < 5; j++){
				xt -= DIR[i][0], yt -= DIR[i][1];
				if (Utils::isLegal(xt, yt)){
					if (segment[xt][yt][i].active){
						Road &seg = segment[xt][yt][i];
						tables[seg.num[0]][seg.num[1]].Remove(seg);
						seg.num[type]++;
						tables[seg.num[0]][seg.num[1]].Add(seg);
					}
				}
				else break;
			}
		}
	}

	void unVirtualMakeMove(int row, int col, int type){
		int xt, yt;
		board[row][col] = NOCHESS;
		for (int i = 0; i < 4; i++){
			xt = row, yt = col;
			if (segment[xt][yt][i].active){
				Road &seg = segment[xt][yt][i];
				tables[seg.num[0]][seg.num[1]].Remove(seg);
				seg.num[type]--;
				tables[seg.num[0]][seg.num[1]].Add(seg);
			}
			for (int j = 0; j < 5; j++){
				xt -= DIR[i][0], yt -= DIR[i][1];
				if (Utils::isLegal(xt, yt)){
					if (segment[xt][yt][i].active){
						Road &seg = segment[xt][yt][i];
						tables[seg.num[0]][seg.num[1]].Remove(seg);
						seg.num[type]--;
						tables[seg.num[0]][seg.num[1]].Add(seg);
					}
				}
				else break;
			}
		}
	}

	//������Ч·
	void update() {
		for (int i = 0; i < ROW; i++){
			for (int j = 0; j < COL; j++){
				for (int k = 0; k < 4; k++){
					if (segment[i][j][k].num[0] > 0 && segment[i][j][k].num[1] > 0){
						segment[i][j][k].active = false;
					}
				}
			}
		}
	}

	//�����Ƿ����˫���ţ�TSS��������
	int countDoubleThreats(int type) {
		Table &four = (type == BLACK ? tables[0][4] : tables[4][0]);
		Table &five = (type == BLACK ? tables[0][5] : tables[5][0]);
		if (four.size + five.size == 0) return 0;
		//������־ʹ���˫���ţ�����һ������˫����
		Table &tab = (four.size == 0 ? five : four);

		for (int i = 0; i < 6; i++){
			int x = tab.roadVector[0]->row + i * DIR[tab.roadVector[0]->dir][0];
			int y = tab.roadVector[0]->col + i * DIR[tab.roadVector[0]->dir][1];
			if (getCell(x, y)!=NOCHESS)
				continue;
			//��ȡ�ո��������ӣ����������ʧ��֤���ǵ�����
			virtualMakeMove(x, y, type);
			int t = four.size + five.size;
			unVirtualMakeMove(x, y, type);
			if (t == 0) return 1;
		}
		return 2;
	}

	//�������е���������
	int countAllThreats(int type) {
		memset(vis, false, sizeof(vis));
		pointVector.clear();
		Table &four = (type == BLACK ? tables[0][4] : tables[4][0]);
		Table &five = (type == BLACK ? tables[0][5] : tables[5][0]);
		

		if (five.size + four.size == 0) return 0;

		Table &tab = (four.size == 0 ? five : four);

		for (int i = 0; i < 6; i++){
			int x = tab.roadVector[0]->row + i * DIR[tab.roadVector[0]->dir][0];
			int y = tab.roadVector[0]->col + i * DIR[tab.roadVector[0]->dir][1];
			if (getCell(x, y)!=NOCHESS)
				continue;
			
			virtualMakeMove(x, y, type);
			int t = four.size + five.size;
			unVirtualMakeMove(x, y, type);
			if (t == 0) return 1;
		}

		for (int i = 0; i < five.size; i++){
			for (int j = 0; j < 6; j++){
				int x = five.roadVector[i]->row + j * DIR[five.roadVector[i]->dir][0];
				int y = five.roadVector[i]->col + j * DIR[five.roadVector[i]->dir][1];
				if (getCell(x, y) != NOCHESS)
					continue;
				Point p(x, y);
				if (!vis[x][y]){
					vis[x][y] = true;
					pointVector.push_back(p);
				}
			}
		}

		for (int i = 0; i < four.size; i++){
			for (int j = 0; j < 6; j++){
				int x = four.roadVector[i]->row + j * DIR[four.roadVector[i]->dir][0];
				int y = four.roadVector[i]->col + j * DIR[four.roadVector[i]->dir][1];
				if (getCell(x, y) != NOCHESS)
					continue;
				Point p(x, y);
				if (!vis[x][y]){
					vis[x][y] = true;
					pointVector.push_back(p);
				}
			}
		}

		bool flag = false;
		int temp = pointVector.size();

		for (int i = 0; i < temp && !flag; i++){
			for (int j = i + 1; j < temp && !flag; j++){
				virtualMakeMove(pointVector[i].x, pointVector[i].y, type);
				virtualMakeMove(pointVector[j].x, pointVector[j].y, type);
				if (four.size + five.size == 0){
					flag = true;
				}
				unVirtualMakeMove(pointVector[i].x, pointVector[i].y, type);
				unVirtualMakeMove(pointVector[j].x, pointVector[j].y, type);
			}
		}

		return (flag ? 2 : 3);
	}

	//��ȡ���Ƿ�Χ��������ߵ��ŷ�
	Step getTopStep(int type) {
		Point pointI = getTopPoint(type);
		virtualMakeMove(pointI.x, pointI.y, type);
		Point pointJ = getTopPoint(type);
		virtualMakeMove(pointJ.x, pointJ.y, type);
		Step step(pointI.x, pointI.y, pointJ.x, pointJ.y);
		step.value = getValue(type);
		unVirtualMakeMove(pointJ.x, pointJ.y, type);
		unVirtualMakeMove(pointI.x, pointI.y, type);
		return step;
	}

	Point getTopPoint(int type) {
		Point respoint;
		respoint.value = -INF;

		for (int i = 0; i <ROW; i++) {
			for (int j = 0; j <COL; j++) {
				if (cover[i][j] && board[i][j] == NOCHESS) {
					Point point(i, j);
					virtualMakeMove(i, j, type);
					point.value = getValue(type);
					if (point.value > respoint.value) {
						respoint = point;
					}
					unVirtualMakeMove(i, j, type);
				}
			}
		}
		return respoint;
	}
	

};
