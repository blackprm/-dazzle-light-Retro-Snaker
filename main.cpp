#include<time.h>
#include<conio.h>
#include<windows.h>
#include<stdio.h>


struct snakeNode
{
	int x;
	int y;
	int role;				//role ��ʾ�����ڵ�Ľ�ɫ 
};
/*
role		1 ������ͷ
role		2 ��������
role		3 ������β
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


snake Jarry;					//�ߵ�����Jarry
int a[4] = { 2,4,6,8 };

int moveDirection = 6;				//��ʼ���ƶ�����

static int score = 0;   
int speed = 200;



void gameOver();
void SetColor(unsigned short ForeColor, unsigned short BackGroundColor)				//���ñ���ɫ �Լ�������ɫ
{

	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, (ForeColor % 16) | (BackGroundColor % 16 * 16));
}

void setcoord(int x, int y)					//���ù��λ��
{
	HANDLE consolehwnd;					//��þ��
	consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);//ʵ�������
	SetConsoleTextAttribute(consolehwnd, FOREGROUND_BLUE | FOREGROUND_INTENSITY);//����
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
void showFood()				// ʳ���λ��
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
				food.food_X = rand() % 45 + 2;			//保证食物的X坐标为奇数，这样蛇才能吃�?

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
		printf("��");
		food.flag = 1;

	}
	setcoord(food.food_X, food.food_Y);		//重复画食�?防止被覆�?
	SetColor(rand() % 6 + 1, 0);
	printf("��");
}
void foodState()
{
	if (food.food_X == Jarry.num[0].x && food.food_Y == Jarry.num[0].y)			//判断食物是否被吃
	{
		food.flag = 0;				//使食物存在状态为0
	}
}
void Wel()						//欢迎界面		
{
	setcoord(20, 10);
	printf("1 : ��ʼ��Ϸ");
	setcoord(20, 12);
	printf("2 : �˳���Ϸ");
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

		fflush(stdin);   /*清空缓冲区，也可以使用rewind(stdin);*/
	}
	setcoord(20, 10);
	printf("          ");
	setcoord(20, 12);
	printf("          ");
}
void showBorder()			//打印设置边框
{
	int x, i, j;
	int y = 0;
	for (i = 0; i < 50; i += 2)
	{

		x = i;
		setcoord(x, y);
		SetColor(rand() % 6 + 1, 0);
		printf("��");
	}
	x = 0;
	for (i = 0; i < 30; i++)
	{

		y = i;
		setcoord(x, y);
		SetColor(rand() % 6 + 1, 0);
		printf("��");
	}
	for (i = 0; i < 48; i += 2)
	{
		SetColor(rand() % 6 + 1, 0);
		printf("��");
	}
	x += 48;
	y = 28;
	for (j = y; j > 0; j--)
	{

		y = j;
		setcoord(x, y);
		SetColor(rand() % 6 + 1, 0);
		printf("��");
	}


}

void setSnakePos()							//蛇移动的原理
{
	int old_snake_x;
	int old_snake_y;				//记录蛇头的位�?

	int flag = 0;				//改变标志位使 一次循坏只更改一次尾�?
	if (moveDirection == 2)				//向下移动
	{

		for (int i = 0; i < Jarry.length; i++)
		{
			if (i == 0)
			{

				setcoord(Jarry.num[0].x, Jarry.num[0].y);
				printf(" ");
				old_snake_x = Jarry.num[0].x;
				old_snake_y = Jarry.num[0].y;
				Jarry.num[0].y += 1;			//移动蛇头
			}
			if (Jarry.num[i].role == 3 && flag == 0)
			{

				setcoord(Jarry.num[i].x, Jarry.num[i].y);
				printf(" ");

				Jarry.num[i].role = 2;				//将其设置为靠近蛇身的位置
				if (i - 1 == 0)
				{
					Jarry.num[Jarry.length - 1].role = 3;
				}
				Jarry.num[i - 1].role = 3;			//比如 1 2 3 4        将蛇头位置变�?然后将最后一位的节点补上去实现移�?1 4 2 3

				Jarry.num[i].x = old_snake_x;
				Jarry.num[i].y = old_snake_y;

				flag = 1;							//改变标志位使 一次循坏只更改一次尾�?

			}
		}
	}
	if (moveDirection == 4)				//向左移动
	{

		for (int i = 0; i < Jarry.length; i++)
		{
			if (i == 0)				//移动蛇头
			{

				setcoord(Jarry.num[0].x, Jarry.num[0].y);
				printf(" ");			//消除原来位置的图�?


				old_snake_x = Jarry.num[0].x;
				old_snake_y = Jarry.num[0].y;		//保存蛇头位置
				Jarry.num[0].x -= 2;			//移动蛇头
			}
			if (Jarry.num[i].role == 3 && flag == 0)
			{

				setcoord(Jarry.num[i].x, Jarry.num[i].y);
				printf(" ");					//消除蛇尾的位�?

				Jarry.num[i].role = 2;				//使当前蛇尾的身份变成蛇身

				if (i - 1 == 0)						//如果当前蛇尾在蛇头后面，则重置到尾部
				{
					Jarry.num[Jarry.length - 1].role = 3;
				}
				Jarry.num[i - 1].role = 3;			//比如 1 2 3 4        将蛇头位置变�?然后将最后一位的节点补上去实现移�?1 4 2 3

				Jarry.num[i].x = old_snake_x;
				Jarry.num[i].y = old_snake_y;					//使蛇尾的位置 �?之前蛇身

				flag = 1;							//改变标志位使 一次循坏只更改一次尾�?

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
				Jarry.num[0].y -= 1;			//移动蛇头
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
				Jarry.num[i - 1].role = 3;			//比如 1 2 3 4        将蛇头位置变�?然后将最后一位的节点补上去实现移�?1 4 2 3

				Jarry.num[i].x = old_snake_x;
				Jarry.num[i].y = old_snake_y;

				flag = 1;							//改变标志位使 一次循坏只更改一次尾�?

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
				Jarry.num[0].x += 2;			//移动蛇头
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
				Jarry.num[i - 1].role = 3;			//比如 1 2 3 4        将蛇头位置变�?然后将最后一位的节点补上去实现移�?1 4 2 3

				Jarry.num[i].x = old_snake_x;
				Jarry.num[i].y = old_snake_y;

				flag = 1;							//改变标志位使 一次循坏只更改一次尾�?

			}
		}

	}
}

void moveByUser()				//通过用户的输入来控制游戏
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
void startUp()			//��ʼ������
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

void showSnake()							//����
{
	for (int i = 0; i < Jarry.length; i++)
	{
		if (i == 0)
		{

			setcoord(Jarry.num[i].x, Jarry.num[i].y);
			SetColor(rand() % 6 + 1, 0);
			printf("��");
		}
		else
		{
			setcoord(Jarry.num[i].x, Jarry.num[i].y);
			SetColor(rand() % 6 + 1, 0);
			printf("��");
		}
	}
}
void snakeState()					//�ߵ�״̬ ����˵�Ե�ʳ�� ײǽ ҧ���Լ�
{
	int i = 0;
	int isfind = 0;					//�Ƿ��ҵ�β��
	if (food.food_X == Jarry.num[i].x && food.food_Y == Jarry.num[i].y)			//Jarrry �Ե�ʳ��
	{
		Jarry.length++;
		for (i = 0; i < Jarry.length - 1; i++)
		{
			if (Jarry.num[i].role = 3)
			{

				Jarry.num[Jarry.length - 1].x = Jarry.num[i].x;
				Jarry.num[Jarry.length - 1].y = Jarry.num[i].y;  
				Jarry.num[i].role = 2;								//β���������
				Jarry.num[Jarry.length - 1].role = 3;				//�µ�β������

				isfind = 1;
				showSnake();
			}
			if (isfind)
				break;		//�ҵ�������

		}
	}
	if (Jarry.num[0].y == 0 || Jarry.num[0].y == 29 || Jarry.num[0].x == -1 || (Jarry.num[0].x == -1 && moveDirection != 4) ||
		Jarry.num[0].x > 47 || (Jarry.num[0].x == 47 && moveDirection != 6))			//Jarry �ײǽ
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
		printf("��Ϸ����  ��������˳�");
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
	for (i = 0; i < 30; i++)
	{
		if (kbhit())
		{
			break;
		}
		for (j = 0; j < 49; j += 2)
		{
			setcoord(j, i);
			SetColor(rand() % 6 + 1, 0);
			if (flag == 0)

			{
				flag = 1;
				printf("��");
			}
			else
			{

				flag = 0;
				printf("��");
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
	printf("��ӭ����̰����");
	setcoord(30, 16);
	printf("-------by DZA");
	Sleep(1000);
	setcoord(12, 14);
	printf(" W A S D ���߷�������Ʒ���");
	setcoord(15, 15);
	printf("P ����ͣ  P�� ����");




}

int main()
{
	int speed0 = 30;
	startUp();
	system("mode con cols=50 lines=30");		// x = 50 y = 30
	gameStart();
	Wel();
	system("mode con cols=50 lines=34");		

	while (1)
	{	
		showBorder();
		moveByUser();			//�û�����Ӱ����Ϸ
		setSnakePos();			//�ߵ�λ��


		snakeState();			//�ߵ�״̬
		showSnake();



		foodState();			//ʳ���״̬
		showFood();				//��ʳ��
		if (speed0 > 20)	//�����ٶ�
			speed0 = speed - 2 * Jarry.length;
		Sleep(speed0);			//�ӻ����� �������ٶ�


		setcoord(0, 32);			
		printf("     ");
		SetColor(10, 0);
		printf("����  :  %d       �ٶ� : %d", score-1, (500 - speed + 20 * Jarry.length - 320) / 20);
	}




	return 0;
}