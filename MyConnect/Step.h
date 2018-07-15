#pragma once
class Step {
public:
	int pos[4], value;
	Step(int x1,int y1,int x2,int y2) {
		this->pos[0] = x1;
		this->pos[1] = y1;
		this->pos[2] = x2;
		this->pos[3] = y2;
	}
	Step() {
		memset(pos, -1, sizeof(pos));
	};
	//用户启发式排序
	bool operator < (const Step p) const{
		return value > p.value;
	}
	//由message构建对象
	Step(string message) {
		memset(pos, -1, sizeof(pos));
		for (int i = 0; i < 4; i++)
			if (message[i] != '@')
				pos[i] = message[i] - 'A';
	}

};
