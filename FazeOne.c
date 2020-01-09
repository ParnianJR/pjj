#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define R 4
#define COL 4
//1 pacman
//2 food
//0 block
//3 empty
int count;
typedef struct{
	int x;
	int y;
}coord;
void gotoxy(int,int);
void drawMap(int Map[COL][R]);
void Move(int,coord*,int Map[COL][R]);
coord find(int Map[COL][R]);
void moveToFood();
coord pacman={0,0};
coord food;
    int Map={1,3,2,3,
			 3,0,3,3,
			 3,3,3,3,
			 0,3,2,3
    	};
int main(){
	drawMap(Map);
	while(1){
		gotoxy(pacman.x,pacman.y);
		printf("%c",'S');
		food=find(Map);
		gotoxy(pacman.x,pacman.y);
		printf(" ");
		if(food.x>0&&food.y>0)
			moveToFood();
	}
}
void drawMap(int Map[COL][R]){
	char block;
	int i,j;
	for(i=0;i<COL;i++){
		for(j=0;j<R;j++){
			switch(Map [i][j]){
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
	static int i=0,j=0;
	coord food;
	for(i;i<COL;i++){
		for(j;j<R;j++){
			if(Map[i][j]==2){
				food.x=i;
				food.y=j;
				return food;	
			}
		}
	}
	food.x=-1;
	food.y=-1;
	return food;
}
void moveToFood(){
	while(food.x!=pacman.x||food.y!=pacman.y){
		if(food.x<pacman.x) Move(1,&pacman,Map);
		if(food.x>pacman.x) Move(2,&pacman,Map);
		if(food.y<pacman.y) Move(3,&pacman,Map);
		if(food.y>pacman.y) Move(4,&pacman,Map);
	}
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
