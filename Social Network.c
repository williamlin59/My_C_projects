/*
 ============================================================================
 Name        : ListArray.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Some code for handling an array of lists
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1024 //constant used to get a line of text
struct line_number{
	int line;
	struct line_number *next;
};					//structure set for linked list
struct line_number *head[65];// head file for each linked list.
struct line_number *current[65];//current file for each linked list.
FILE *open_file(char*file_name,char mode); //create file pointer for read or write into/from file.
int copy_contents_to_array(FILE *fp);//copy the name to 2d array
void read_text_line(FILE *fp,int number);//read text line by line, search the first occurance of each name and store it into correspond list.
struct line_number *add_to_list(int line_number, int list_number);//add line number to each correspond list.
void set_list(int n);//set the linked list
struct line_number* create_list(int line_number, int list_number);//initialize each lists.
void creat_file(int list_number,int compare_number,struct line_number *b,struct line_number *a,FILE *fp);//compare each elments in the lists and print it into the fire
char names[65][100];//global variable for storing names.
int main() {
	FILE *fopen(),*fp;//file pointer for read and write.
	int name_no,counter=0,counter1=1;
	fp=open_file("Les-Mis-Names.txt",'r');//r means read
	name_no=copy_contents_to_array(fp);//copy names into array and return the number of name on the list
	fp=open_file("Les-Mis-full-text.txt",'r');
	set_list(name_no);//set list with name_no.
	read_text_line(fp,name_no);
	fp=open_file("Name_List.txt",'a');//a for append,
	while(counter<name_no){//first counter for the row
		counter1=counter+1;
		while(head[counter]!=NULL){//second counter for each element in the row.
			while(counter1<name_no){
				creat_file(counter,counter1,head[counter1],head[counter],fp);//compare all the elements and rea
				counter1++;
			}
			counter1=counter+1;
			head[counter]=head[counter]->next;
		}
		counter++;
	}
	fclose(fp);
}

void creat_file(int list_number,int compare_number,struct line_number *b,struct line_number *a,FILE *fp){
	int occurance;
    struct line_number *ptr = b;//pointer for the first row
    struct line_number *ptr2 = a;//pointer for the compared row.
   	 while(ptr!=NULL){
   		 occurance=ptr->line-ptr2->line;
        	if(occurance<5&&occurance>-5){//if the line number is within 5.
        		fputs(names[list_number],fp);//put first name into the file
        		fputs("\t\t",fp);//put some spaces between two names
        		fputs(names[compare_number],fp);//put  second name into the file
        		fputs("\n",fp);//put newline character.
        		printf("%s%d %d	          %s%d %d\n",names[list_number],list_number,ptr->line,names[compare_number],compare_number,ptr2->line);
        	 }//this prints out all the name with line number for debug.
        ptr= ptr->next;
    }
}

FILE *open_file(char*file_name,char mode){
	FILE *fopen(),*fp;
	if(mode=='r'){//this is for reading
	fp=fopen(file_name,"r");
		if(fp==NULL){
			printf("Can't open the file: %s!",file_name);
		}
	}
	else if(mode=='a'){//this is for writing
		fp=fopen(file_name,"a+");
		if(fp==NULL){
			printf("Can't open the file: %s !",file_name);
		}
	}
	return fp;
}

int copy_contents_to_array(FILE *fp){
	int c,counter1=0,counter2=0;
	while(!feof(fp)){
		c=getc(fp);
			if(c=='\n'||c==EOF){
				names[counter1][counter2]='\0';//put \0 at the end of the string.
				counter1++;
				counter2=0;
			}
			else{
			names[counter1][counter2]=c;
			counter2++;
			}
	}
		fclose(fp);
		return counter1-1;//because last counter1++plus one more at the end.
}

void read_text_line(FILE *fp,int number){
	char *dp,line[BUFFSIZE];
	int line_number=1,counter=0;
	while(!feof(fp)){
		fgets(line,BUFFSIZE,fp);//get a line of text.
		while(counter<number){//this loop compare each name with this line of string
		dp=strstr(line,names[counter]);
			if(dp!=NULL){//if it's occured.
				add_to_list(line_number, counter);//add the number to the list.
			}
			counter++;
		}
		counter=0;
		line_number++;//move to the next line.
	}
	fclose(fp);
}

void set_list(int n){//initialize list into null.
 	int a;
 	for(a=0; a<n; a++){
 		head[a] = NULL;
 		current[a] = head[a];
 	}
 }

 struct line_number* create_list(int line_number, int list_number){//once it's not created, create the list
     struct line_number *ptr = (struct line_number *)malloc(sizeof(struct line_number));
     ptr->line = line_number;
     ptr->next = NULL;
     head[list_number] = current[list_number] = ptr;
     return ptr;
 }

 struct line_number *add_to_list(int line_number, int list_number){//add the line number to the existed list.
     if( head[list_number]==NULL){
         return (create_list(line_number, list_number));
     }
     struct line_number *ptr = (struct line_number*)malloc(sizeof(struct line_number));
     ptr->line = line_number;
     ptr->next = NULL;
     current[list_number]->next = ptr;
     current[list_number] = ptr;
    return ptr;
 }

