#pragma once
//��Ϊ����·
class Road
{
public:
	int row;//�����
	int col;//�����
	int dir;//��·�ķ���
	int num[3]; //��·�а��Ӻ��ӵ�����
	int index; //·��tables�е��±�
	bool active; //�Ƿ���Ч��������Ч����·�а���Ϊ0���ߺ���Ϊ0
	Road() {}
	Road(int row, int col, int dir, int whites, int blacks, bool active, int index)
	{
		this->row = row;
		this->col = col;
		this->num[0] = blacks;
		this->num[1] = whites;
		this->dir = dir;
		this->active = active;
		this->index = index;
	}
};