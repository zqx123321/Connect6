#include "config.h"
#include<string>
#include"Game.h"
#define DEBUG

using namespace std;


int main()
{

	char *res;
	string message;
	const char *engineName = "αβγ";
	Game game;

	while (1)
	{
		fflush(stdout);
		cin >> message;
		//兼容3.0版本的对战平台
		std::size_t foundNew = message.find("new");
		std::size_t foundMove = message.find("move");
		std::size_t foundEnd = message.find("end");
		std::size_t foundQuit= message.find("quit");
		if (foundMove != std::string::npos)       //走法信息
		{
			cin>>message;
			fflush(stdin);
			Step step(message);
			res = game.move(step);
			printf("move %s\n", res);
		}
		
		else if (foundNew != std::string::npos)   //创建新棋局
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
		else if (message == "name?") //引擎名字
		{
			fflush(stdin);

			printf("name %s\n", engineName);
		}
		else if (foundEnd != std::string::npos)   //对局结束
		{
			fflush(stdin);
		}
		else if (foundQuit != std::string::npos)  //退出引擎
		{
			fflush(stdin);
			printf("Quit!\n");
			break;
		}
	}

	return 0;
}