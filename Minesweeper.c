/*
 ============================================================================
 Name        : Minesweeper.c
 Author      : songjun lin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
struct location{//this structure is for holding the location of grid that users input.
	int line;
	int row;
};
struct location input;
void title(void);
int user_choice(void);//for users choosing level the game
void level_choice(void);//each level of the game actually executes here
void map(int x,int y,int z);//print out the map
int random_number(int x);//generates random number
void mine_maker(int row,int line,int mine_number);//arrange the mine in the map
void user_input(int line,int row);//let users input the grid they want to choose
int actual_play(int row,int line);//detect is there any mine adjacent to the grid that users input
void blank(int row, int line);//mark the blank grid if there are no mine adjacent to the grid that users input
void check_the_result(int line,int row, int switcher);//check if the user find out all the mines to win the game
char after_play(void);//ask the user continue playing or not
void clean_the_map(void);//clean the map back to the start so users can play a new round
int input_checking(int line, int row);//check if the user input is valid or not
int mine[16][30]={{0}};//the global variable for storing the result of map
void invalid_input(void);//show the warning when the input is invalid and clean the bufffer.
int main(void) {
	char user_input='y';
	title();
	do{
		level_choice();
		user_input=after_play();
		clean_the_map();
	}while(user_input=='y'||user_input=='Y');//when user input y continue playing
	printf("Game is Over.. GoodBye\n");
}

void title(void){
	printf("**********Welcome to Minesweeper***********\n");
}

int user_choice(void){
	int level,dummy;
	while(dummy!='\n'||level>3||level<1){
	printf("Please choose a difficulty level (1=Beginner, 2=Intermediate, 3=Expert):\n");
	scanf("%d",&level);
	dummy=getchar();
		if(dummy!='\n'||level>3||level<1){
			invalid_input();
		}//when user input something outside 1 to 3 it's going to ask the user to input it again.
	}
	return level;
}

void level_choice(void){
	int level,result=0;
	int switcher=0;
	int input_check=1;
	level=user_choice();
		if(level==1){
			mine_maker(9,9,10);//first 9 is row, second 9 is line. 10 is the number of mines
			map(9,9,result); //result is the number of the mine that adjecent to the grid of user picking
			while(switcher==0){//switcher is used to show if there are mine adjecent to the grid( 1 is yes, 0 is no)
				do{
			user_input(9,9);
			input_check=input_checking(9,9);
				if(input_check==1){
					map(9,9,result);
				}
				}while(input_check==1);//do loop to ensure the user input is valid
			result=actual_play(9,9); // result decide if the grid contains mine and hold the number of mine that adjecent to the grid
			if(result==10){//10 means the grid has mine
				map(9,9,result);
				printf("There is a Mine (*) at that position!... Game Over\n");
				switcher=1;
			}
			else if(result==0){//0 means no mines adjacent
				blank(9,9);
				map(9,9,result);
				printf("SELECTED OK. No adjacent mine left!\n");
			}
			else{//at least 1 mine adjacent
				mine[input.row][input.line]=result;
				map(9,9,result);
				printf("SELECTED OK. But %d adjacent(s) mine left!\n",result);
			}
			check_the_result(9,9,switcher);//check if the user win the game
		}
	}
		else if(level==2){//this is for the level 2. Basically it has the same structure with level 1 only with more mines and larger map.
			mine_maker(16,16,40);
			map(16,16,result);
			while(switcher==0){
				do{
				user_input(16,16);
				input_check=input_checking(16,16);
					if(input_check==1){
						map(16,16,result);
						printf("SELECTED FAIL, the grid has already been selected\n");
						}
				}while(input_check==1);
						result=actual_play(16,16);
						if(result==10){
							map(16,16,result);
							printf("There is a Mine (*) at that position!... Game Over\n");
							switcher=1;
						}
						else if(result==0){
							blank(16,16);
							map(16,16,result);
							printf("SELECTED OK. No adjacent mine left!\n");
						}
						else{
							mine[input.row][input.line]=result;
							map(16,16,result);
							printf("SELECTED OK. But %d adjacent(s) mine left!\n",result);
						}
						check_the_result(16,16,switcher);
				}
	}
		else if(level==3){//this is for level 3
			mine_maker(16,30,99);
			map(30,16,result);
			while(switcher==0){
				do{
				user_input(30,16);
				input_check=input_checking(30,16);
					if(input_check==1){
						map(30,16,result);
						printf("SELECTED FAIL, the grid has already been selected\n");
						}
					}while(input_check==1);
				result=actual_play(30,16);
				if(result==10){
					map(30,16,result);
					printf("There is a Mine (*) at that position!... Game Over\n");
					switcher=1;
					}
				else if(result==0){
					blank(30,16);
					map(30,16,result);
					printf("SELECTED OK. No adjacent mine left!\n");
					}
				else{
					mine[input.row][input.line]=result;
					map(30,16,result);
					printf("SELECTED OK. But %d adjacent(s) mine left!\n",result);
					}
				check_the_result(30,16,switcher);
			}
		}
}

void map(int x,int y,int z){//x is the row number each level should have. y is the line. z is the result.
	int line=0,row=0,grid=0;
	printf("     ");// this is the space left for the first row to point to the correspond grid
	while(line<y){
		if(line<10){
		printf(" |%d| ",line);
		}
		else{//if it's >=10, then there are two digits so we need to delete one space before the number.
		printf(" |%d|",line);
		}
		line++;
	}
	printf("\n");
	while(row<x){
		if(row<10){//same to the row
		printf(" |%d|  ",row);
		}
		else{
		printf("|%d|  ",row);
		}
			while(grid<y){
			if(z!=10){//this is the situation that the grid doesn't contain mine
				if(mine[row][grid]==0){// 0 indicates has not been selected
				printf("|-|  ");
				}
				else{
					if(mine[row][grid]==-1){// -1 indicates mine
						printf("|*|  ");
					}
					else if(mine[row][grid]==10){//10 indicates blank
						printf("|B|  ");
					}
					else{
						printf("|%d|  ",mine[row][grid]);//this indicates the number of mines that adjacent to the grid that has been selected.
					}
				}
			}
			else if(z==10){// when the grid contains a mine
					if(mine[row][grid]==-1){
					printf("|*|  ");
					}
					else {
					printf("|-|  ");
					}
				}
				grid++;//line++
			}
			grid=0; //make it back to zero so we can use it for counting the next line
			printf("\n");
			row++;//proceed to the next line.
	}
}

int random_number(int x){//x is the number of the grid that the level should hold
	int random_number;
	random_number=rand()%x;
	return random_number;
}

void mine_maker(int row,int line,int mine_number){
	int random_row,random_line,counter=0;
		while(counter<=mine_number){
		random_row=random_number(row);//I use 2d array, so this one for the first line
		random_line=random_number(line);//this one for the second line
		mine[random_line][random_row]=-1;//then this grid is a mine marked as -1
		counter++;
		}
}

void user_input(int line,int row){
	char dummy;
	printf("Enter x,y coordinates (both start at 0) of space to select (e.g. For x=0, y=3 enter 0,3):\n");
	while(dummy!='\n'||input.line>line||input.row>row){//if the user input is out of boundary or doesn't make sense then print out invalid input.
	scanf("%d,%d",&input.line,&input.row);
	dummy=getchar();
		if(dummy!='\n'||input.line>line||input.row>row){
			invalid_input();
		}
	printf("Enter x,y coordinates (both start at 0) of space to select (e.g. For x=0, y=3 enter 0,3):\n");
	}
}

int actual_play(int row,int line){
	int result=0;
	if(mine[input.row][input.line]==-1){
			result=10;//shows the grid has mine
	}
		else{
			if(input.line==line){//if the user pick a grid is on the right side of the boundary, six grid just need to be detected.
					if(mine[input.row][input.line-1]==-1){
						result++;
					}
					if(mine[input.row-1][input.line]==-1){
						result++;
					}
					if(mine[input.row-1][input.line-1]==-1){
						result++;
					}
					if(mine[input.row+1][input.line-1]==-1){
						result++;
					}
					if(mine[input.row+1][input.line]==-1){
						result++;
					}
			}
			else if(input.line==0){//if the user input is on the left side of the boundary
				if(mine[input.row][input.line+1]==-1){
					result++;
				}
				if(mine[input.row+1][input.line+1]==-1){
					result++;
				}
				if(mine[input.row-1][input.line+1]==-1){
					result++;
				}
				if(mine[input.row+1][input.line]==-1){
					result++;
				}
				if(mine[input.row-1][input.line]==-1){
					result++;
				}
			}
			else if(input.row==0&&input.line!=0&&input.line!=line){//if the user input is on the up side of the boundary without top left and top right.
				if(mine[input.row+1][input.line]==-1){
					result++;
				}
				if(mine[input.row+1][input.line+1]==-1){
					result++;
				}
				if(mine[input.row+1][input.line-1]==-1){
					result++;
				}
				if(mine[input.row][input.line+1]==-1){
					result++;
				}
				if(mine[input.row][input.line-1]==-1){
					result++;
				}
			}
			else if(input.row==row&&input.line!=0&&input.line!=line){//if the user input is on the bottom side of the boundary without bottom left and bottom right.
				if(mine[input.row-1][input.line]==-1){
					result++;
				}
				if(mine[input.row-1][input.line-1]==-1){
					result++;
				}
				if(mine[input.row-1][input.line+1]==-1){
					result++;
				}
				if(mine[input.row][input.line+1]==-1){
					result++;
				}
				if(mine[input.row][input.line-1]==-1){
					result++;
				}
			}
			else{//the rest of the scenario
				if(mine[input.row+1][input.line]==-1){
					result++;
				}
				if(mine[input.row+1][input.line+1]==-1){
					result++;
				}
				if(mine[input.row+1][input.line-1]==-1){
					result++;
				}
				if(mine[input.row][input.line+1]==-1){
					result++;
				}
				if(mine[input.row][input.line-1]==-1){
					result++;
				}
				if(mine[input.row-1][input.line]==-1){
					result++;
				}
				if(mine[input.row-1][input.line-1]==-1){
					result++;
				}
				if(mine[input.row-1][input.line+1]==-1){
					result++;
				}
			}
		}
		return result;
}

void blank(int row, int line){//print out the blank that adjacent to the grid depends on the location of the grid
		mine[input.row][input.line]=10;
		if(input.line==line){
			mine[input.row][input.line-1]=10;
			mine[input.row-1][input.line]=10;
			mine[input.row-1][input.line-1]=10;
			mine[input.row+1][input.line-1]=10;
			mine[input.row+1][input.line]=10;
		}
		else if(input.line==0){
			mine[input.row+1][input.line]=10;
			mine[input.row][input.line+1]=10;
			mine[input.row+1][input.line+1]=10;
			if(input.row!=0){
			mine[input.row-1][input.line+1]=10;
			mine[input.row-1][input.line]=10;
			}
		}
		else if(input.row==0&&input.line!=0&&input.line!=line){
			mine[input.row+1][input.line]=10;
			mine[input.row+1][input.line+1]=10;
			mine[input.row+1][input.line-1]=10;
			mine[input.row][input.line+1]=10;
			mine[input.row][input.line-1]=10;
		}
		else if(input.row==row&&input.line!=0&&input.line!=line){
			mine[input.row-1][input.line]=10;
			mine[input.row-1][input.line-1]=10;
			mine[input.row-1][input.line+1]=10;
			mine[input.row][input.line+1]=10;
			mine[input.row][input.line-1]=10;
		}
		else{
			mine[input.row][input.line-1]=10;
			mine[input.row-1][input.line]=10;
			mine[input.row-1][input.line-1]=10;
			mine[input.row+1][input.line-1]=10;
			mine[input.row+1][input.line]=10;
			mine[input.row][input.line+1]=10;
			mine[input.row+1][input.line+1]=10;
			mine[input.row-1][input.line+1]=10;
					}
}

void check_the_result(int line,int row, int switcher){//determine if the user win the game.
	int counter1=0,zero=0,counter2=0;
	while(counter1<row){
		while(counter2<line){//these two loop to detect all the grid on the map
			if(mine[counter1][counter2]==0){
			zero++;
			}
		counter2++;
		}
		counter1++;
	}
	if(zero==0){//if there is no 0(all the blank grids have been found out).
		printf("congratulations,you win the game!!!");
		switcher=1;
	}
}

char after_play(void){
	char user_input,dummy;
	while(dummy!='\n'||(user_input!='y'&&user_input!='n'&&user_input!='Y'&&user_input!='N')){//if user input is sth but not Y or N
	printf("Would you like to play again? Yes (enter 'y') OR No (enter 'n'): \n");
	scanf("%c",&user_input);
	dummy=getchar();
		if(dummy!='\n'||(user_input!='y'&&user_input!='n'&&user_input!='Y'&&user_input!='N')){
			invalid_input();
		}
	}
	return user_input;
}

void clean_the_map(void){
	int counter1,counter2;
	for(counter1=0;counter1<16;counter1++){
		for(counter2=0;counter2<30;counter2++){
			mine[counter1][counter2]=0;//reset all the elements in this array to 0.
		}
	}
}

int input_checking(int line, int row ){
	int input_check;
	if(mine[input.row][input.line]!=0&&mine[input.row][input.line]!=-1){//this is used to check if the user input has been selected before or not.
		input_check=1; //if has been selected return 1
		printf("SELECTED FAIL, the grid has already been selected\n");
	}
	else if(input.row>=row||input.line>=line){//this condition is used to check if the user input is out of the boundary.
		printf("ILLEGAL COORDINATES: Enter x,y coordinates (both start at 0) of space to select (e.g. For x=0, y=3 enter '0,3'):\n");
		input_check=1;
	}
	else{
		input_check=0;//all the inputs are valid
	}
	return input_check;
}

void invalid_input(void){
	printf("Invalid input\n");
	fflush(stdin);//clean the buffer.
}
