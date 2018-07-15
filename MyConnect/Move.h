#pragma once
#include<vector>
#include<algorithm>
#include"ChessBoard.h"
using namespace std;
class Move {
public:
	vector <Step> moveList;
	vector <Point> pointList;
	bool vis[19][19];

	//�����ŷ�������alpha_beta����
	void createMove(ChessBoard &chessBoard, int type){
		moveList.clear();
		pointList.clear();
		//�ȵ���getWinMove�鿴��û�б�ʤ�ŷ�
		generateWinMove(chessBoard, type);
		if (moveList.size() != 0) return;
		//����Է���в
		int threats = chessBoard.countAllThreats(type);
		//��һ��������һ��
		if (threats == 1){
			generateSingleBlocks(chessBoard, type);
		}
		//����ȫ��������
		else if (threats >= 2){
			generateDoubleBlocks(chessBoard, type);
		}
		//�����õ�
		else{
			generateGoodValuePoints(chessBoard, type);
		}
		//��������ʽ����
		sortMove();
	}

	//����˫��в�ŷ�������TSS����
	void createDoubleThreatsMove(ChessBoard &chessBoard, int type){
		moveList.clear();
		pointList.clear();
		//�������ɱ�ʤ�ŷ�
		generateWinMove(chessBoard, type);
		if (moveList.size() != 0) return;
		//����Է���в��
		int threats = chessBoard.countDoubleThreats(type);
		//�Է�û����в��չ��˫��в����
		if (threats == 0){
			generateDoubleThreats(chessBoard, type);
		}
		//�Է�������в���������
		else{
			generateDoubleBlocks(chessBoard, type);
		}
	}


	void sortMove(){
		sort(moveList.begin(), moveList.end());
	}

	void findblanks(Road *road, ChessBoard &chessBoard) {
		for (int i = 0; i < 6; i++) {
			int x = road->row + i * DIR[road->dir][0];
			int y = road->col + i * DIR[road->dir][1];
			if (chessBoard.getCell(x, y) != NOCHESS)
				continue;
			if (vis[x][y] == false) {
				Point p(x, y);
				pointList.push_back(p);
				vis[x][y] = true;
			}
		}
	}

	//��ȡǱ���㣬�����ܳ�Ϊ��в�ĵ�
	void getPotentialPoints(ChessBoard &chessBoard, int type){
		//�ҷ��������������ĵ㼴ΪǱ����
		Table &ownTwo = (type == BLACK ? chessBoard.tables[2][0] : chessBoard.tables[0][2]);
		Table &ownThree = (type == BLACK ? chessBoard.tables[3][0] : chessBoard.tables[0][3]);
		int lenOwnTwo = ownTwo.size, lenOwnThree = ownThree.size;
		

		for (int k = 0; k < lenOwnThree; k++){
			findblanks(ownThree.roadVector[k], chessBoard);
		}

		for (int k = 0; k < lenOwnTwo; k++){
			findblanks(ownTwo.roadVector[k], chessBoard);
		}
	}

	//������ʤ�ŷ�
	void generateWinMove(ChessBoard &chessBoard, int type){
		Table &four = (type == BLACK ? chessBoard.tables[4][0] : chessBoard.tables[0][4]);
		Table &five = (type == BLACK ? chessBoard.tables[5][0] : chessBoard.tables[0][5]);
		Step step;
		if (four.size != 0){
			for (int i = 0, ind = 0; i < 6; i++){
				int x = four.roadVector[0]->row + i * DIR[four.roadVector[0]->dir][0];
				int y = four.roadVector[0]->col + i * DIR[four.roadVector[0]->dir][1];
				if (chessBoard.getCell(x,y)!=NOCHESS)
					continue;
				if (ind == 0){
					step.pos[0] = x;
					step.pos[1] = y;
					ind++;
				}
				else{
					step.pos[2] = x;
					step.pos[3] = y;
				}
			}
			chessBoard.virtualMakeMove(step.pos[0], step.pos[1], type);
			chessBoard.virtualMakeMove(step.pos[2], step.pos[3], type);
			step.value = chessBoard.getValue(type);
			chessBoard.unVirtualMakeMove(step.pos[0], step.pos[1], type);
			chessBoard.unVirtualMakeMove(step.pos[2], step.pos[3], type);
			moveList.push_back(step);
		}

		if (five.size != 0 && moveList.size() == 0){
			step = chessBoard.getTopStep(type);
			for (int i = 0; i < 6; i++){
				int x = five.roadVector[0]->row + i * DIR[five.roadVector[0]->dir][0];
				int y = five.roadVector[0]->col + i * DIR[five.roadVector[0]->dir][1];
				if (chessBoard.getCell(x,y)!=NOCHESS)
					continue;
				step.pos[0] = x;
				step.pos[1] = y;
			}
			chessBoard.virtualMakeMove(step.pos[0], step.pos[1], type);
			chessBoard.virtualMakeMove(step.pos[2], step.pos[3], type);
			step.value = chessBoard.getValue(type);
			chessBoard.unVirtualMakeMove(step.pos[0], step.pos[1], type);
			chessBoard.unVirtualMakeMove(step.pos[2], step.pos[3], type);
			moveList.push_back(step);
		}
	}

	//������ȫ��������
	void generateDoubleBlocks(ChessBoard &chessBoard, int type){
		//�Է����Ļ�������
		Table &four = (type == BLACK ? chessBoard.tables[0][4] : chessBoard.tables[4][0]);
		Table &five = (type == BLACK ? chessBoard.tables[0][5] : chessBoard.tables[5][0]);
		int lenfour = four.size, lenfive = five.size;
		pointList.clear();
		memset(vis, false, sizeof(vis));
		//�Ȱѿհ׿������
		for (int k = 0; k < lenfour; k++){
			findblanks(four.roadVector[k], chessBoard);
		}

		for (int k = 0; k < lenfive; k++) {
			findblanks(five.roadVector[k], chessBoard);
		}

		int rowlen = pointList.size();
		//����հ׿飬�������ܲ��������Ƴ���в
		for (int i = 0; i < rowlen; i++)
		{
			for (int j = i + 1; j < rowlen; j++)
			{
				chessBoard.virtualMakeMove(pointList[i].x, pointList[i].y, type);
				chessBoard.virtualMakeMove(pointList[j].x, pointList[j].y, type);
				//���Ƴ�������
				if (four.size + five.size == 0){
					Step step(pointList[i].x, pointList[i].y, pointList[j].x, pointList[j].y);
					step.value = chessBoard.getValue(type);
					moveList.push_back(step);
				}
				chessBoard.unVirtualMakeMove(pointList[j].x, pointList[j].y, type);
				chessBoard.unVirtualMakeMove(pointList[i].x, pointList[i].y, type);
			}
		}
		if (moveList.size() == 0){
			Step step = chessBoard.getTopStep(type);
			chessBoard.virtualMakeMove(step.pos[0], step.pos[1], type);
			chessBoard.virtualMakeMove(step.pos[2], step.pos[3], type);
			step.value = chessBoard.getValue(type);
			chessBoard.unVirtualMakeMove(step.pos[2], step.pos[3], type);
			chessBoard.unVirtualMakeMove(step.pos[0], step.pos[1], type);
			moveList.push_back(step);
		}
	}

	//��һ��������һ��
	void generateSingleBlocks(ChessBoard &chessBoard, int type){
		Table &four = (type == BLACK ? chessBoard.tables[0][4] : chessBoard.tables[4][0]);
		Table &five = (type == BLACK ? chessBoard.tables[0][5] : chessBoard.tables[5][0]);
		int lenfour = four.size, lenfive = five.size;
		pointList.clear();
		memset(vis, false, sizeof(vis));
		for (int k = 0; k < lenfour; k++){
			findblanks(four.roadVector[k], chessBoard);
		}

		for (int k = 0; k < lenfive; k++) {
			findblanks(five.roadVector[k], chessBoard);
		}

		//������һ���㣬�����ڶ�����
		int temp1 = pointList.size();
		getGoodConnectPoints(chessBoard, type);
		int temp2 = temp1 + (int)((pointList.size() - temp1));
		for (int i = 0; i < temp1; i++){
			//�Ƴ�
			chessBoard.virtualMakeMove(pointList[i].x, pointList[i].y, type);
			if (four.size + five.size == 0){
				for (int j = i + 1; j < temp2; j++)
				{
					chessBoard.virtualMakeMove(pointList[j].x, pointList[j].y, type);
					Step step(pointList[i].x, pointList[i].y, pointList[j].x, pointList[j].y);
					step.value = chessBoard.getValue(type);
					moveList.push_back(step);
					chessBoard.unVirtualMakeMove(pointList[j].x, pointList[j].y, type);
				}
			}
			chessBoard.unVirtualMakeMove(pointList[i].x, pointList[i].y, type);
		}
	}

	//���������ϵĺõ㣬����õ㣺�ҷ���1��2��3���Է���2��3
	void getGoodConnectPoints(ChessBoard &chessBoard, int type){
		Table &two = (type == BLACK ? chessBoard.tables[0][2] : chessBoard.tables[2][0]);
		Table &three = (type == BLACK ? chessBoard.tables[0][3] : chessBoard.tables[3][0]);
		Table &ownOne = (type == BLACK ? chessBoard.tables[1][0] : chessBoard.tables[0][1]);
		Table &ownTwo = (type == BLACK ? chessBoard.tables[2][0] : chessBoard.tables[0][2]);
		Table &ownThree = (type == BLACK ? chessBoard.tables[3][0] : chessBoard.tables[0][3]);

		int lenOwnOne = ownOne.size, lenOwnTwo = ownTwo.size, lenthree = three.size, lentwo = two.size, 
			lenOwnThree = ownThree.size;

		for (int k = 0; k < lenthree; k++){
			findblanks(three.roadVector[k], chessBoard);
		}

		for (int k = 0; k < lentwo; k++) {
			findblanks(two.roadVector[k], chessBoard);
		}
		for (int k = 0; k < lenOwnThree; k++) {
			findblanks(ownThree.roadVector[k], chessBoard);
		}
		for (int k = 0; k < lenOwnTwo; k++) {
			findblanks(ownTwo.roadVector[k], chessBoard);
		}

		for (int k = 0; k < lenOwnOne; k++) {
			findblanks(ownOne.roadVector[k], chessBoard);
		}
		int len = pointList.size();
		//��������
		for (int i = 0; i < len; i++)
		{
			chessBoard.virtualMakeMove(pointList[i].x, pointList[i].y, type);
			pointList[i].value = chessBoard.getValue(type);
			chessBoard.unVirtualMakeMove(pointList[i].x, pointList[i].y, type);
		}
	}

	//�ۺ������������õ��ŷ�
	void generateGoodValuePoints(ChessBoard &chessBoard, int type){
		pointList.clear();
		memset(vis, false, sizeof(vis));
		getGoodConnectPoints(chessBoard, type);
		sort(pointList.begin(), pointList.end());

		int len = pointList.size();
		int sum = 0;
		int temp = len;
		//�Ż���ȥ��С��ƽ��ֵ��
		for (int i = 0; i < len; i++){ 
			sum += pointList[i].value;
		}
		sum /= len;

		for (int i = 0; i < len; i++){
			if (pointList[i].value < sum){
				temp = i;
				break;
			}
		}

		for (int i = 0; i < len; i++){
			for (int j = i + 1; j < temp; j++) {
				chessBoard.virtualMakeMove(pointList[i].x, pointList[i].y, type);
				chessBoard.virtualMakeMove(pointList[j].x, pointList[j].y, type);
				Step step(pointList[i].x, pointList[i].y, pointList[j].x, pointList[j].y);
				step.value = chessBoard.getValue(type);
				moveList.push_back(step);
				chessBoard.unVirtualMakeMove(pointList[j].x, pointList[j].y, type);
				chessBoard.unVirtualMakeMove(pointList[i].x, pointList[i].y, type);
			}
			//�Ż������ļм�
			temp--;
		}
	}

	//����˫��в�ŷ�
	void generateDoubleThreats(ChessBoard &chessBoard, int type) {

		pointList.clear();
		memset(vis, false, sizeof(vis));
		getPotentialPoints(chessBoard, type);
		int len = pointList.size();

		for (int i = 0; i < len; i++) {
			for (int j = i + 1; j < len; j++) {
				//��Ǳ�����н���ɸѡ���õ�������в��
				chessBoard.virtualMakeMove(pointList[i].x, pointList[i].y, type);
				chessBoard.virtualMakeMove(pointList[j].x, pointList[j].y, type);
				if (chessBoard.countDoubleThreats(type ^ 1) >= 2) {
					Step step(pointList[i].x, pointList[i].y, pointList[j].x, pointList[j].y);
					moveList.push_back(step);
				}
				chessBoard.unVirtualMakeMove(pointList[j].x, pointList[j].y, type);
				chessBoard.unVirtualMakeMove(pointList[i].x, pointList[i].y, type);
			}
		}
	}
};