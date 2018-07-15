#pragma once
class  Utils
{
public:
	//判断点是否出界
	static bool isLegal(int row, int col) {
		return row >= 0 && row <= 18 && col >= 0 && col <= 18;
	}

};
