#pragma once
#include "Move.h"
#include <cmath>
#include "Config.h"
class Search {
private:
	int computerSide;
	int grad;
	int t;
	int isFind;
	vector <Step> moveVector;
	vector <Step> firstSteps;
	Step bestMove;

public:

	Search() {
		grad = t = isFind = 0;
		grad = 2;
	}

	Step findBestMove(int type, ChessBoard &chessBoard) {
		/*time_t a = time(0);*/
		computerSide = type;

		//���Ƚ���TSS����
		for (int i = 1; i <= TSSDEPTH; i += 2) {
			if (TSS(type, chessBoard, i)) {
				cout << "TSS success " << endl;
				return bestMove;
			}
		}

		//TSSʧ�ܣ�����alphaBeta����
		firstSteps.clear();
		computerSide ^= 1;
		isFind = 0;
		int value = alphaBeta(DEPTH - grad, -INF, INF, type, chessBoard);
		if (!isFind)bestMove = firstSteps[0];
		//����ʱ�䣬�����ݶ�
		/*	time_t b = time(0);
		t += (b - a);
		if (t > 450) grad = 2;
		if (t > 920) grad = 3;*/
		return bestMove;
	}

	/*
	�������ܣ�������ֵ������alpha_beta + PVS��֦
	*/
	//https://chessprogramming.wikispaces.com/Principal+Variation+Search

	int alphaBeta(int depth, int alpha, int beta, int type, ChessBoard &chessBoard) {
		if (depth == 0) { return chessBoard.getValue(type); }

		int temp = -INF;
		bool flag = false;

		Move move;
		move.createMove(chessBoard, type);
		int num = move.moveList.size();
		num = min(num, MAXNODE + grad * 6);

		if (depth == DEPTH - grad) {
			for (int i = 0; i < num; i++) firstSteps.push_back(move.moveList[i]);
		}
		for (int i = 0; i < num; i++) {
			chessBoard.makeMove(move.moveList[i].pos[0], move.moveList[i].pos[1], type);
			chessBoard.makeMove(move.moveList[i].pos[2], move.moveList[i].pos[3], type);

			if (flag) {
				//�մ���̽
				temp = -alphaBeta(depth - 1, -alpha - 1, -alpha, type ^ 1, chessBoard);
				if (temp > alpha && temp < beta) {
					temp = -alphaBeta(depth - 1, -beta, -alpha, type ^ 1, chessBoard);
				}
			}
			else {
				temp = -alphaBeta(depth - 1, -beta, -alpha, type ^ 1, chessBoard);
			}

			chessBoard.unMakeMove(move.moveList[i].pos[0], move.moveList[i].pos[1], type);
			chessBoard.unMakeMove(move.moveList[i].pos[2], move.moveList[i].pos[3], type);


			if (temp >= beta) {
				return beta;
			}
			if (temp > alpha) {
				alpha = temp;
				flag = true;
				if (depth == DEPTH - grad) {
					chessBoard.makeMove(move.moveList[i].pos[0], move.moveList[i].pos[1], type);
					chessBoard.makeMove(move.moveList[i].pos[2], move.moveList[i].pos[3], type);
					if (!TSS(type ^ 1, chessBoard, 15)) {
						bestMove = move.moveList[i];
						isFind = 1;
					}
					chessBoard.unMakeMove(move.moveList[i].pos[0], move.moveList[i].pos[1], type);
					chessBoard.unMakeMove(move.moveList[i].pos[2], move.moveList[i].pos[3], type);
				}
			}
		}
		return alpha;
	}

	bool TSS(int type, ChessBoard& chessBoard, int depth) {
		//����ҷ�������return true��
		int temp = (computerSide == BLACK ? chessBoard.tables[6][0].size : chessBoard.tables[0][6].size);

		if (temp > 0) {
			bestMove = moveVector[0];
			return true;
		}
		//����Է�������в�������ҷ�û����в��return false��
		if (type == computerSide && chessBoard.countAllThreats(type)
			&& chessBoard.countAllThreats(type ^ 1) == 0) return false;

		//����ҷ���в����3��return true��
		if (type == (computerSide ^ 1) && (chessBoard.countAllThreats(type) >= 3)) {
			bestMove = moveVector[0];
			return true;
		}
		//depthΪ0��return false�� 
		if (depth == 0) return false;

		//����
		Move move;
		move.createDoubleThreatsMove(chessBoard, type);
		int num = move.moveList.size();

		for (int i = 0; i < num; i++) {
			chessBoard.makeMove(move.moveList[i].pos[0], move.moveList[i].pos[1], type);
			chessBoard.makeMove(move.moveList[i].pos[2], move.moveList[i].pos[3], type);
			moveVector.push_back(move.moveList[i]);
			bool flag = TSS(type ^ 1, chessBoard, depth - 1);
			moveVector.erase(moveVector.end() - 1);
			chessBoard.unMakeMove(move.moveList[i].pos[2], move.moveList[i].pos[3], type);
			chessBoard.unMakeMove(move.moveList[i].pos[0], move.moveList[i].pos[1], type);

			if (type == computerSide) {
				flag = false || flag;
				if (flag) return true;
			}
			else {
				flag = true && flag;
				if (!flag) return false;
			}
		}
	}
};