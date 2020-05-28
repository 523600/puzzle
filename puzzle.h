#include <graphics.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#define SCR_WIDTH      360
#define SCR_HEIGHT     360
#define N  3

using namespace std;

class Puzzle
{

private:
    int grid[N][N];
    int x, y;

public:
    void init(void);
    void show(void);
    void move_space(void);
    bool isFinish(void);
    bool isEven(void);

};

void Puzzle::init(void)
{
	int a[9]={0,1,2,3,4,5,6,7,8};
	int i,w,t,j;
	static int k=0;

	for (i=0;i<9;i++)
	{
		a[i]=i;
	}

	srand((unsigned int)time(NULL));

	for (i=0;i<8;i++)
	{
		w=rand()%(8-i)+i;
 		t=a[i];
 		a[i]=a[w];
 		a[w]=t;
	}
	k=0;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			grid[i][j]=a[k];
			if(a[k]==0){
				x=i;
				y=j;
			}
			k++;
		}
	}
	k=0;
}

void Puzzle::show(void)
{
	initgraph(SCR_WIDTH, SCR_HEIGHT,0);
	setbkcolor(BLUE);
	setfont(36, 0, "??");
	setcolor(WHITE);
	line(0,120,360,120);
	line(0,240,360,240);
	line(120,0,120,360);
	line(240,0,240,360);//?????

	int xpos,ypos;
	int i,j,k;
	char grid_[9];
	int b[9]={0};

	memset(grid_,0,sizeof(grid_));

	k=0;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			b[k]=grid[i][j];
			k++;
		}
	}

	for(i=0;i<9;i++)
	{
		grid_[i]=b[i]+'0';
	}

	k=0;
	for(xpos=60;xpos<=300;xpos+=120)
	{
		for(ypos=60;ypos<=300;ypos+=120)
		{
			if(grid_[k]!='0'){
				outtextxy(xpos, ypos, grid_[k]);
			}
			k++;
		}
	}
}

bool Puzzle::isEven(void)
{
	int i,j,k=0,flag=0;
	int a[8]={0};

	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(grid[i][j]!=0){
				a[k]=grid[i][j];
				k++;
			}
		}
	}

	for(i=0;i<=7;i++)
	{
		for(j=i+1;j<=8;j++)
		{
			if(a[i]>a[j]&&a[i]!=0&&a[j]!=0)
			{
				flag++;
			}
		}
	}

	if(flag%2==0){
		return true;
	}else{
		return false;
	}

}

bool Puzzle::isFinish(void)
{
	int i,j,k=0,flag=0;
	int a[9]={1,2,3,4,5,6,7,8,0};

	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(a[k]!=grid[i][j])
			{
				flag=-1;
			}
			k++;
		}
	}
	if(flag==0){

		return true;
	}else if(flag==-1){
		return false;
	}

}
void Puzzle::move_space(void)
{
	char k;
	int temp;
	while(isFinish()==false){
		show();
    	k=getch();
		if(k=='s')
		{
			if(y!=0)
			{
				temp=grid[x][y];
				grid[x][y]=grid[x][y-1];
				grid[x][y-1]=temp;
				y--;
			}
		}
		if(k=='w')
		{
			if(y!=2)
			{
				temp=grid[x][y];
				grid[x][y]=grid[x][y+1];
				grid[x][y+1]=temp;
				y++;
			}
		}
		if(k=='d')
		{
			if(x!=0)
			{
				temp=grid[x][y];
				grid[x][y]=grid[x-1][y];
				grid[x-1][y]=temp;
				x--;
			}
		}
		if(k=='a')
		{
			if(x!=2)
			{
				temp=grid[x][y];
				grid[x][y]=grid[x+1][y];
				grid[x+1][y]=temp;
				x++;
			}
		}
	}

	show();
	cleardevice();
	setcolor(YELLOW);
	outtextxy(120, 160,"???");
	getch();
	closegraph();
}

void Gamerun(void)
{
    Puzzle puzzle;

	do{
		puzzle.init();
	}while(puzzle.isEven()==false);

	puzzle.move_space();
}
