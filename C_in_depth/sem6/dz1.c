#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define STR_SIZE 2000
typedef struct list
{
	char* word;
	struct list *next;
}list;
/* Без заглавного элемента и без двойного
указателя*/
	list* insert2(char* value,list *head);
	void print_first_list(list * head);
	void print_last_list(list * head);
	void choose_sort_array_list(list * head);
	void swap_elements(list *e1,list *e2);
	void delete_list(list *head);

int main(int argc, char** argv){
	list *w_list=NULL;
	char word[STR_SIZE]="";
	int ch = ' ';
	int i=0;
	printf("enter sequence: ");
	while(EOF != (ch = getchar())){
		switch(ch){
			case '.':
			case ' ':
				word[i] = '\0';
				w_list = insert2(word, w_list);
				i=0;
				break;
			default:
				word[i++] = ch;
				if(i>=STR_SIZE)
					i=0;//Защита от переполнения строки
		}
if('.' == ch)
	break;
	}

	#ifdef DEBUG
	print_list(w_list);
	#endif
	//choose_sort_array_list(w_list);
	print_first_list(w_list);
	print_last_list(w_list);
	delete_list(w_list);
	return 0;
}

void delete_list(list * l){
	list * c =l;
	list * n;
	while(c != NULL) {
		n = c->next;
		free(c->word);//Очищаем память под слово
		free(c);
		c = n;
	}
}


/* Без заглавного элемента и без двойного указателя*/
list* insert2(char* value,list *head){
	list *res = (list*)calloc(1,sizeof(list));
	int len = strlen(value);//определяем размер строки
	res->word = malloc(len+1);//выделяем память под строку
	strcpy(res->word, value);//копируем строку в память
	res->next = head;//смещаем указатель на следующий
	return res;
}


void print_first_list(list * head)
{
	int count=0;
	for (list* i = head; i!=NULL; i=i->next,count++)
	{
		if(i->next==NULL)
		 printf("%s ", i->word);
		
	}
}

void print_last_list(list * head)
{
	int count=0;
	for (list* i = head; i!=NULL; i=i->next,count++)
	{
		if(count==0)
		{
			printf("%s ", i->word);
		}
	}
	putchar('\n');
}
