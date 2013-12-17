/*
 ============================================================================
 Name        : slot.c
 Author      : songjun lin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

 typedef struct {
	 	 int face;
 }column;

 typedef struct {
	 	 column column1;
	 	 column column2;
	 	 column column3;
 }slot;


int result_interface(slot s);
void result_1(int a,int b,int c);
void main_face(void);
int full_horse(int x);
int half_horse(int x);
int empty_horse(int x);
int credit_1 (int f,int credit,int a);
void credit_interface(int f ,int x, int a);
int choice_of_play (int a);
int input_credit(int a);


int main() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
	int user_input,credit=10, y=1,g;
	slot s;
	main_face();
	while(y==1){
	user_input=input_credit(credit);
	g=result_interface(s);
	credit_interface(user_input,credit,g);
	credit=credit_1(user_input,credit,g);
	y=choice_of_play(credit);
	}
}

int result_interface (slot s){
	int a,b,c,result;
	s.column1.face=1+(rand()%3);
	s.column2.face=1+(rand()%3);
	s.column3.face=1+(rand()%3);
	a=s.column1.face;
	b=s.column2.face;
	c=s.column3.face;
	result_1(a,b,c);
		if(a==b&&b==c&&a==c){
			result=1;
		}
		if(a==b&&a!=c){
			result=2;
		}
		if(a==c&&a!=b){
			result=2;
		}
		if(b==c&&b!=a){
			result=2;
		}
		if(a!=c&&a!=b&&b!=c){
			result=3;
		}
	return(result);
}
void result_1(int a,int b,int c){
	printf("Your selection:\t");
	switch(a){
	case 1:
		printf("|apple| ");
		break;
	case 2:
		printf("|banana| ");
		break;
	case 3:
		printf("|orange| ");
		break;
	}
	switch(b){
	case 1:
		printf("|apple| ");
		break;
	case 2:
		printf("|banana| ");
		break;
	case 3:
		printf("|orange| ");
		break;
			}
	switch(c){
	case 1:
		printf("|apple|\n ");
		break;
	case 2:
		printf("|banana|\n ");
		break;
	case 3:
		printf("|orange|\n ");
		break;
			}

}

void main_face(void){
	printf("******Welcome to my Slot Machine****\n");
	printf("Your available credit is 10\n");
}

int full_horse(int x){
	return (x);
}

int half_horse(int x){
	x=x/2;
	return (x);
}

int empty_horse(int x){
	return (x);
}


int credit_1 (int f,int credit,int a){
	int b;


		if(a==1){
			b=full_horse(f);
			credit=credit+b;
		}
		if(a==2){
			b=half_horse(f);
			credit=credit+b;
		}
		if(a==3){
			b=empty_horse(f);
			credit=credit-b;
		}

	return(credit);
}

void credit_interface(int f ,int x, int a){
	int b;

			if(a==1){
				b=full_horse(f);
				printf("*****you win %d credits*****\n", b);
				x=x+b;
			}
			if(a==2){
				b=half_horse(f);
				printf("*****you win %d credits******\n", b);
				x=x+b;
			}
			if(a==3){
				b=empty_horse(f);
				printf("******you lose %d credits******\n",b);
				x=x-b;
			}

		printf("current credit balance=%d\n",x);
}



int choice_of_play (int a){
	char yes_no;
	char dummy;
	int b,c=1;

		printf("play again?\n");
		dummy=getchar();
		yes_no=getchar();
		if(yes_no=='y'||yes_no=='Y'){
			if(a<=2){
				printf("Sorry, but you ain't got any credit, Bye!!!\n");
				c=0;
			}
			else{
			c=1;
			}
		}
		else if(yes_no=='n'||yes_no=='N'){

			if (a>=10){
				b=a-10;
				printf("****End of Game: total amount WON = %d credits****\n",b);
			}

			if(a<10){
				b=10-a;
				printf("****End of Game: total amount LOST = %d credits****\n",b);
			}
				c=0;
		}
		else{
		printf("invalid input\n");
		c=choice_of_play(a);
		}
		return(c);
}

int input_credit(int a){
	int user_input;
	printf("How much you want to bet?\n");
	scanf("%d",&user_input);
	/*if (user_input<2){
	printf("Sorry, input credit should be larger than 2.\n");
	user_input=input_credit(a);
	}
	else if(user_input>a){
	printf("Sorry, you don't have enough credit.\n");
	user_input=input_credit(a);
	}*/

	return(user_input);
	}
