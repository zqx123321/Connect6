#pragma once
class Point {
public:
	int x, y, value;
	Point(int x,int y) {
		this->x = x;
		this->y = y;
	}
	Point() {};
	//�û�����ʽ����
	bool operator < (const Point p) const{
		return value > p.value;
	}
};