#include "config.h"
#include<string>
#include"Game.h"
#define DEBUG

using namespace std;


int main()
{

	char *res;
	string message;
	const char *engineName = "���¦�";
	Game game;

	while (1)
	{
		fflush(stdout);
		cin >> message;
		//����3.0�汾�Ķ�սƽ̨
		std::size_t foundNew = message.find("new");
		std::size_t foundMove = message.find("move");
		std::size_t foundEnd = message.find("end");
		std::size_t foundQuit= message.find("quit");
		if (foundMove != std::string::npos)       //�߷���Ϣ
		{
			cin>>message;
			fflush(stdin);
			Step step(message);
			res = game.move(step);
			printf("move %s\n", res);
		}
		
		else if (foundNew != std::string::npos)   //���������
		{
			cin >> message;
			fflush(stdin);
			game.init();
			if (message=="black")
			{
				Step moveStep;
				res = game.move(moveStep);
				printf("move %s\n", res);
			}
		}
		else if (message == "name?") //��������
		{
			fflush(stdin);

			printf("name %s\n", engineName);
		}
		else if (foundEnd != std::string::npos)   //�Ծֽ���
		{
			fflush(stdin);
		}
		else if (foundQuit != std::string::npos)  //�˳�����
		{
			fflush(stdin);
			printf("Quit!\n");
			break;
		}
	}

	return 0;
}