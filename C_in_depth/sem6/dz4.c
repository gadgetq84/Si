#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define STR_SIZE 2000
typedef struct list
{
	int index;
	char* word;
	struct list *next;
}list;

/* Без заглавного элемента и без двойного
указателя*/
	list* insert2(char* value,list *head,int index);
	void print_list(list * head);
	void print_reversed(list * head);
	void choose_sort_array_list(list * head);
	void swap_elements(list *e1,list *e2);
	void delete_list(list *head);
	void del_odd(list ** l);

int main(int argc, char** argv){
	list *w_list=NULL;
	char word[STR_SIZE]="";
	int ch = ' ';
	int i=0;
	int index=0;
	printf("enter sequence: ");
	while(EOF != (ch = getchar())){
		switch(ch){
			case '.':
			case ' ':
				word[i] = '\0';
				w_list = insert2(word, w_list,index);
				i=0;
				index++;
				break;
			default:
				word[i++] = ch;
				if(i>=STR_SIZE)
					i=0;//Защита от переполнения строки
		}
if('.' == ch)
	break;
	}
	del_odd(&w_list);
	//print_list(w_list);
	print_reversed(w_list);
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


list* insert2(char* value,list *head,int index){
	list *res = (list*)calloc(1,sizeof(list));
	
	int len = strlen(value);//определяем размер строки
	res->word = malloc(len+1);//выделяем память под строку
	res->index= index;
	strcpy(res->word, value);//копируем строку в память
	res->next = head;//смещаем указатель на следующий
	return res;
}


void print_list(list * head)
{
for (list* i = head; i!=NULL; i=i->next)
	printf(" %s ", i->word);
putchar('\n');
}

void print_reversed(list * head)
{
    if (head != NULL) {
        print_reversed(head->next);
        printf("%s ", head->word);
    }
}
//aa ss dd ff gg hh jj kk ll tt.
//aa ss dd ff gg hh jj kk ll.
void del_odd(list **l){
	list * c =(*l);
	list * n=NULL;
	while(c->next != NULL ) {
		
		if(c->index%2!=0)
		{
			n=(*l)->next;
			free(c->word);
			free(c);
			(*l)=n;
			c=n;
		}
				////printf("%d ", c->index);
				n = c->next->next;
				free(c->next->word);//Очищаем память под слово
				free(c->next);
				c->next = n;
			 	c=c->next;
		
	}
}

