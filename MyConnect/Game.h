#pragma once
#include "Search.h"
class Game {
private:
	char resMove[5];
	int computerSide;
	Search search;

public:
	ChessBoard chessBoard;
	int choose;
	Game(){
		memset(resMove, '\0', sizeof(resMove));
		computerSide = -1;
	}

	void init(){
		chessBoard.init();
		computerSide = -1;
	}

	char* move(Step step){
		Step bestMove;
		if (step.pos[0] == -1){
			computerSide = BLACK;
			bestMove.pos[0] = 9;
			bestMove.pos[1] = 9;
			bestMove.pos[2] = -1;
			bestMove.pos[3] = -1;
		}
		else if (step.pos[2] == -1){
			makeMove(step, BLACK);
			computerSide = WHITE;

			for (int i = 0; i < 4; i++) {
				int x1 = step.pos[0] + open[i][0];
				int y1 = step.pos[1] + open[i][1];
				int x2 = step.pos[0] + open[i][2];
				int y2 = step.pos[1] + open[i][3];
				if (Utils::isLegal(x1, y1) && Utils::isLegal(x2, y2)) {
					bestMove.pos[0] = x1;
					bestMove.pos[1] = y1;
					bestMove.pos[2] = x2;
					bestMove.pos[3] = y2;
					break;
				}
			}
			
		}
		else{
			makeMove(step,computerSide^1);
			bestMove = search.findBestMove(computerSide, chessBoard);
		}

		makeMove(bestMove, computerSide);
		chessBoard.update();
		return getRes(bestMove);
	}

	void makeMove(Step step, int type)
	{
		if (step.pos[0] != -1)
			chessBoard.makeMove(step.pos[0], step.pos[1], type);
		if (step.pos[2] != -1)
			chessBoard.makeMove(step.pos[2], step.pos[3], type);
	}

	char* getRes(Step bestMove){
		if (bestMove.pos[0] != -1){
			resMove[0] = bestMove.pos[0] + 'A';
			resMove[1] = bestMove.pos[1] + 'A';
		}
		else{
			resMove[0] = '@';
			resMove[1] = '@';
		}
		if (bestMove.pos[2] != -1){
			resMove[2] = bestMove.pos[2] + 'A';
			resMove[3] = bestMove.pos[3] + 'A';
		}
		else{
			resMove[2] = '@';
			resMove[3] = '@';
		}
		resMove[4] = '\0';
		return resMove;
	}
};