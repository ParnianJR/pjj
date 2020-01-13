#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define R 4
#define COL 4
//1 S pacman
//2 . food
//0 * block
//3  empty

typedef struct{
	int x;
	int y;
}coord;
void gotoxy(int,int);
void drawMap(int Map[COL][R]);
void Move(int,coord*,int Map[COL][R]);
coord find(int Map[COL][R]);
void moveToFood(int Map[COL][R], coord);
coord pacman={0,0};

int main(){

	coord food;
	int Map[COL][R]={1,3,2,3,
			         3,0,3,3,
			         3,3,3,3,
			         0,3,2,3
    	};
	drawMap(Map);
	gotoxy(0,0);
	printf("%c",'S');
	sleep(1);
	while(1){
		gotoxy(pacman.x,pacman.y);
		printf(" ");	
		food=find(Map);
		if (food.x!=-10)
			moveToFood(Map,food);
		else break;
		gotoxy(pacman.x,pacman.y);
		printf("%c",'S');
		Sleep (500);
	}
	gotoxy (0, 10);
	printf ("FINISH:)");
}
void drawMap(int Map[COL][R]){
	char block;
	int a,b;
	for(a=0;a<COL;a++){
		for(b=0;b<R;b++){
			switch(Map [a][b]){
				case 0:
					block='*';
					break;
				case 2:
					block='.';
					break;
				case 3:
					block=' ';
					break;
			}
			printf("%c",block);
		}
		printf("\n");
	}
}
void gotoxy(int x,int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle,coord);	
}
coord find(int Map[COL][R]){
	static int i,j;
	coord food = {-10, -10};
	for(i=0;i<COL;i++)
		for(j=0;j<R;j++){
			if(Map[i][j]==2){
				food.x=j;
				food.y=i;
				return food;
			}
		}
		
	return food;
}
void moveToFood(int Map[COL][R], coord food){
		if(food.x<pacman.x) Move(3,&pacman,Map);
		if(food.x>pacman.x) Move(4,&pacman,Map);
		if(food.y<pacman.y) Move(1,&pacman,Map);
		if(food.y>pacman.y) Move(2,&pacman,Map);
}
void Move(int choice,coord *pacman,int Map[COL][R]){
		Map[pacman->y][pacman->x]=3;
		switch(choice){
			case 1:
				if(pacman->y&&Map[pacman->y-1][pacman->x])
					pacman->y--;
					break;
			case 2:
				if(pacman->y+1<COL&&Map[pacman->y+1][pacman->x])
					pacman->y++;
					break;
			case 3:
				if(pacman->x&&Map[pacman->y][pacman->x-1])
					pacman->x--;
					break;
			case 4:
				if(pacman->x+1<R&&Map[pacman->y][pacman->x+1])
					pacman->x++;
					break;
		}
		Map[pacman->y][pacman->x]=1;
}
