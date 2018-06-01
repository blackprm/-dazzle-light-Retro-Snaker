#include<time.h>
#include<conio.h>
#include<windows.h>
#include<easyx.h>
#include<stdio.h>
#pragma comment(lib,"Winmm.lib")

struct snakeNode
{
	int x;
	int y;
	int role;				//role 表示各个节点的角色 
};
/*
role		1 代表蛇头
role		2 代表蛇身
role		3 代表蛇尾
*/
struct snake
{
	snakeNode num[1000];
	int length;
};


struct
{
	int food_X;
	int food_Y;
	int flag;
}food;


snake Jarry;					//蛇的名字Jarry
int a[4] = { 2,4,6,8 };

int moveDirection = 6;				//初始化移动方向

static int score = 0;   
int speed = 200;



void gameOver();
void SetColor(unsigned short ForeColor, unsigned short BackGroundColor)				//设置背景色 以及字体颜色
{

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, (ForeColor % 16) | (BackGroundColor % 16 * 16));
}

void setcoord(int x, int y)					//设置光标位置
{
	HANDLE consolehwnd;					//获得句柄
	consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);//实例化句柄
	SetConsoleTextAttribute(consolehwnd, FOREGROUND_BLUE | FOREGROUND_INTENSITY);//设置
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false; 
	SetConsoleCursorInfo(handle, &CursorInfo);

}
void showFood()				// 食物的位置
{

	int isOk = 1;
	int i;
	if (!food.flag)
	{
		score++;
		while (1)
		{
			srand(unsigned(time(NULL)));
			food.food_X = rand() % 45 + 2;
			while (food.food_X % 2 != 1)
				food.food_X = rand() % 45 + 2;

			food.food_Y = rand() % 28 + 1;
			for (i = 0; i < Jarry.length; i++)
			{
				if (food.food_X == Jarry.num[i].x && food.food_Y == Jarry.num[i].y)
					isOk = 0;
			}
			if (isOk)
			{
				break;
			}
		}

		setcoord(food.food_X, food.food_Y);
		SetColor(rand() % 6 + 1, 0);
		printf("●");
		food.flag = 1;

	}
	setcoord(food.food_X, food.food_Y);		
	SetColor(rand() % 6 + 1, 0);
	printf("●");
}
void foodState()
{
	if (food.food_X == Jarry.num[0].x && food.food_Y == Jarry.num[0].y)			
	{

		food.flag = 0;	
	}
}
void Wel()				
{
	setcoord(20, 10);
	printf("1 : 开始游戏");
	setcoord(20, 12);
	printf("2 : 退出游戏");
	char  ch = ' ';


	while (1)
	{
		ch = getch();
		{
			if (ch == '1')
			{
				break;
			}
			if (ch == '2')
				exit(0);
		}

		fflush(stdin);
	}
	setcoord(20, 10);
	printf("          ");
	setcoord(20, 12);
	printf("          ");
}
void showBorder()		
{

	int x, i, j;
	int y = 0;
	for (i = 0; i < 50; i += 2)
	{

		x = i;
		setcoord(x, y);
		SetColor(rand() % 6 + 1, 0);
		printf("●");
	}
	x = 0;
	for (i = 0; i < 30; i++)
	{

		y = i;
		setcoord(x, y);
		SetColor(rand() % 6 + 1, 0);
		printf("●");
	}
	for (i = 0; i < 48; i += 2)
	{
		SetColor(rand() % 6 + 1, 0);
		printf("●");
	}
	x += 48;
	y = 28;
	for (j = y; j > 0; j--)
	{

		y = j;
		setcoord(x, y);
		SetColor(rand() % 6 + 1, 0);
		printf("●");
	}


}

void setSnakePos()				
{
	int old_snake_x;
	int old_snake_y;			

	int flag = 0;				
	if (moveDirection == 2)		
	{

		for (int i = 0; i < Jarry.length; i++)
		{
			if (i == 0)
			{

				setcoord(Jarry.num[0].x, Jarry.num[0].y);
				printf(" ");
				old_snake_x = Jarry.num[0].x;
				old_snake_y = Jarry.num[0].y;
				Jarry.num[0].y += 1;			
			}
			if (Jarry.num[i].role == 3 && flag == 0)
			{

				setcoord(Jarry.num[i].x, Jarry.num[i].y);
				printf(" ");

				Jarry.num[i].role = 2;			
				if (i - 1 == 0)
				{
					Jarry.num[Jarry.length - 1].role = 3;
				}
				Jarry.num[i - 1].role = 3;			

				Jarry.num[i].x = old_snake_x;
				Jarry.num[i].y = old_snake_y;

				flag = 1;							

			}
		}
	}
	if (moveDirection == 4)			
	{

		for (int i = 0; i < Jarry.length; i++)
		{
			if (i == 0)			
			{

				setcoord(Jarry.num[0].x, Jarry.num[0].y);
				printf(" ");			


				old_snake_x = Jarry.num[0].x;
				old_snake_y = Jarry.num[0].y;		
				Jarry.num[0].x -= 2;			
			}
			if (Jarry.num[i].role == 3 && flag == 0)
			{

				setcoord(Jarry.num[i].x, Jarry.num[i].y);
				printf(" ");				

				Jarry.num[i].role = 2;			

				if (i - 1 == 0)						
				{
					Jarry.num[Jarry.length - 1].role = 3;
				}
				Jarry.num[i - 1].role = 3;		

				Jarry.num[i].x = old_snake_x;
				Jarry.num[i].y = old_snake_y;					

				flag = 1;							
			}
		}

	}
	if (moveDirection == 8)
	{
		for (int i = 0; i < Jarry.length; i++)
		{
			if (i == 0)
			{

				setcoord(Jarry.num[0].x, Jarry.num[0].y);
				printf(" ");
				old_snake_x = Jarry.num[0].x;
				old_snake_y = Jarry.num[0].y;
				Jarry.num[0].y -= 1;		
			}
			if (Jarry.num[i].role == 3 && flag == 0)
			{

				setcoord(Jarry.num[i].x, Jarry.num[i].y);
				printf(" ");

				Jarry.num[i].role = 2;
				if (i - 1 == 0)
				{
					Jarry.num[Jarry.length - 1].role = 3;
				}
				Jarry.num[i - 1].role = 3;		
				Jarry.num[i].x = old_snake_x;
				Jarry.num[i].y = old_snake_y;

				flag = 1;							
			}
		}

	}

	if (moveDirection == 6)
	{

		for (int i = 0; i < Jarry.length; i++)
		{
			if (i == 0)
			{

				setcoord(Jarry.num[0].x, Jarry.num[0].y);
				printf(" ");
				old_snake_x = Jarry.num[0].x;
				old_snake_y = Jarry.num[0].y;
				Jarry.num[0].x += 2;		
			}
			if (Jarry.num[i].role == 3 && flag == 0)
			{

				setcoord(Jarry.num[i].x, Jarry.num[i].y);
				printf(" ");

				Jarry.num[i].role = 2;
				if (i - 1 == 0)
				{
					Jarry.num[Jarry.length - 1].role = 3;
				}
				Jarry.num[i - 1].role = 3;			//

				Jarry.num[i].x = old_snake_x;
				Jarry.num[i].y = old_snake_y;

				flag = 1;					

			}
		}

	}
}

void moveByUser()				//閫氳繃鐢ㄦ埛鐨勮緭鍏ユ潵鎺у埗娓告垙
{
	char ch = 'm';
	if (kbhit())
	{

		ch = getch();
		fflush(stdin);

		if ((ch == 72 || ch == 'w') && moveDirection != 2)
		{
			moveDirection = 8;
		}
		if ((ch == 75 || ch == 'a') && moveDirection != 6)
		{
			moveDirection = 4;
		}
		if ((ch == 80 || ch == 's') && moveDirection != 8)
		{
			moveDirection = 2;
		}
		if ((ch == 77 || ch == 'd') && moveDirection != 4)
		{
			moveDirection = 6;
		}
		if (ch == 'p')
		{
			while (1)
			{
				ch = getch();
				if (ch == 'p')
					break;
			}
		}

	}
}
void startUp()			//初始化数据
{
	srand(unsigned(time(NULL)));
	moveDirection = a[rand() % 4];
	Jarry.num[0].x = 25;
	Jarry.num[0].y = 15;
	Jarry.num[0].role = 1;
	/*
	Jarry.num[1].x = 25;
	Jarry.num[1].y = 14;
	Jarry.num[1].role = 2;

	Jarry.num[2].x = 25;
	Jarry.num[2].y = 13;
	Jarry.num[2].role = 3;

	*/
	Jarry.length = 1;
	srand(unsigned(time(NULL)));
	food.flag = 0;

}

void showSnake()							//画蛇
{
	for (int i = 0; i < Jarry.length; i++)
	{
		if (i == 0)
		{

			setcoord(Jarry.num[i].x, Jarry.num[i].y);
			SetColor(rand() % 6 + 1, 0);
			printf("★");
		}
		else
		{
			setcoord(Jarry.num[i].x, Jarry.num[i].y);
			SetColor(rand() % 6 + 1, 0);
			printf("○");
		}
	}
}
void snakeState()					//蛇的状态 比如说吃到食物 撞墙 咬到自己
{
	int i = 0;
	int isfind = 0;					//是否找到尾部
	if (food.food_X == Jarry.num[i].x && food.food_Y == Jarry.num[i].y)			//Jarrry 吃到食物
	{
		
		mciSendString(_T("close mymusic2"), NULL, 0, NULL);
		mciSendString(_T("close mymusic"), NULL, 0, NULL);
		mciSendString(_T("open 1.mp3 alias mymusic"), NULL, 0, NULL);
		mciSendString(_T("play mymusic"), NULL, 0, NULL);
		Jarry.length++;
		for (i = 0; i < Jarry.length - 1; i++)
		{
			if (Jarry.num[i].role = 3)
			{

				Jarry.num[Jarry.length - 1].x = Jarry.num[i].x;
				Jarry.num[Jarry.length - 1].y = Jarry.num[i].y;  
				Jarry.num[i].role = 2;								//尾部变成身体
				Jarry.num[Jarry.length - 1].role = 3;				//新的尾部产生

				isfind = 1;
				showSnake();


			}
			if (isfind)
				break;		//找到后跳出

		}
	}
	if (Jarry.num[0].y == 0 || Jarry.num[0].y == 29 || Jarry.num[0].x == -1 || (Jarry.num[0].x == 1 && moveDirection != 4) ||
		Jarry.num[0].x > 47 || (Jarry.num[0].x == 47 && moveDirection != 6))			//Jarry 
	{
		setcoord(0, 0);
		gameOver();
		exit(0);
	}
	for (i = 1; i < Jarry.length - 1; i++)
	{
		if (Jarry.num[0].x == Jarry.num[i].x && Jarry.num[0].y == Jarry.num[i].y)
		{
			gameOver();
			exit(0);
		}
	}

}
void gameOver()
{
	int i = 0, j = 0;
	for (i = 0; i < 30; i++)			
		for (j = 0; j < 49; j += 1)
		{
			printf("  ");
		}
	setcoord(14, 13);
	while (1)
	{
		setcoord(14, 13);
		SetColor(rand() % 10 + 6, 0);
		printf("游戏结束  按任意键退出");
		Sleep(500);
		
		fflush(stdin);
		if (kbhit())
		{
			exit(0);
		}
	}



}
void gameStart()						
{
	int i = 0, j = 0, k = 0, m = 0;
	int flag = 0;
	mciSendString(_T("close mymusic3"), NULL, 0, NULL);
	mciSendString(_T("open 3.mp3 alias mymusic3"), NULL, 0, NULL);
	mciSendString(_T("play mymusic3"), NULL, 0, NULL);
	for (i = 0; i < 30; i++)
	{

		if (kbhit())
		{
			getch();
			break;
		}
		for (j = 0; j < 49; j += 2)
		{
			setcoord(j, i);
			SetColor(rand() % 6 + 1, 0);
			if (flag == 0)

			{
				flag = 1;
				printf("●");
			}
			else
			{

				flag = 0;
				printf("★");
			}
			Sleep(2);
		}
	}

	flag = 0;
	i = 0;
	j = 0;
	k = 29;
	m = 48;
	while (i != k + 1)
	{
		if (kbhit())
		{
			getch();
			break;
		}
		if (flag == 0)
		{

			for (; i < 30; i++)
			{

				for (j = 0; j < 49; j += 2)
				{


					setcoord(j, i);
					printf("  ");
					Sleep(5);
				}
				flag = 1;
				i++;
				break;
			}

		}
		if (flag == 1)
		{
			for (; k >= 0; k--)
			{

				for (m = 0; m < 49; m += 2)
				{
					setcoord(m, k);
					printf("  ");
					Sleep(5);

				}
				k--;
				flag = 0;
				break;
			}
		}

	}

	for (i = 0; i < 30; i++)		
		for (j = 0; j < 49; j += 1)
		{
			printf(" ");
		}

	setcoord(18, 14);
	SetColor(10, 0);

	printf("欢迎来到贪吃蛇");
	setcoord(30, 16);
	printf("-------by DZA");
	Sleep(1000);
	setcoord(12, 14);
	printf(" W A S D 或者方向键控制方向");
	setcoord(15, 15);
	printf("P 键暂停  P键 继续");


	fflush(stdin);

}

int main()
{
	SetConsoleTitle(_T("Snake"));   //改标题
	int speed0 = 30;
	startUp();
	system("mode con cols=50 lines=30");		// x = 50 y = 30
	gameStart();
	Wel();
	mciSendString(_T("close mymusic3"), NULL, 0, NULL);
	system("mode con cols=50 lines=34");		

	while (1)
	{	
		showBorder();
		moveByUser();			//用户输入影响游戏
		setSnakePos();			//蛇的位置


		snakeState();			//蛇的状态
		showSnake();



		foodState();			//食物的状态
		showFood();				//画食物
		if (speed0 > 20)	//控制速度
			speed0 = speed - 2 * Jarry.length;
		Sleep(speed0);			//延缓画面 来控制速度
//		mciSendString(_T("close mymusic2"), NULL, 0, NULL);
		mciSendString(_T("open 2.mp3 alias mymusic2"), NULL, 0, NULL);
		mciSendString(_T("play mymusic2 repeat"), NULL, 0, NULL);

		setcoord(0, 32);			
		printf("     ");
		SetColor(10, 0);
		printf("分数  :  %d       速度 : %d", score-1, (500 - speed + 20 * Jarry.length - 320) / 20);
	//	mciSendString(_T("close mymusic"), NULL, 0, NULL);
	}




	return 0;
}
