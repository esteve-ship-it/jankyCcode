#include <stdio.h>
#include <stdlib.h>

/* Takes in a degree sequence as commandline arguments and returns whether
 * or not that it could be a graph
 */

typedef struct {
	int degree;
	void* previous;
	void* next;
} Vertices;

int strToInt(char* input) {
	int num = 0;
	while(*input>='0' && *input<='9') {
		num=num*10;
		num+=*input-'0';
		input++;
	}
	return num;
}

void rotateVertices(Vertices* a, Vertices* b) {
	Vertices* temp;
	temp = a->previous;
	temp->next = b;
	b->previous = temp;
	temp = b->next;
	a->next = temp;
	if (temp!=NULL) {
		temp->previous = a;
	}
	a->previous = b;
	b->next = a;
}


void sortList(Vertices* first){
	Vertices* list = first->next;
	while(list->next!=NULL){
		if(list->degree<((Vertices*) (list->next))->degree){
			rotateVertices(list, list->next);
			list=first;
		}
		list = list->next;
	}
}

void exitScript(Vertices* first){
	Vertices* temp;
	while(first->next!=NULL){
		temp=first;
		first=first->next;
		free(temp);
	}
	free(first);
}


int main(int argc, char **argv){
	//check for enough for an actual graph min 2 vertices
	if (argc<3) {
		printf("Not enough vertices\n");
		return 1;
	}
	Vertices* first = (Vertices*) malloc(sizeof(Vertices));
	Vertices* current = first;
	first->previous = NULL;
	for (int i=1; i<argc; i++) {
		current->next = (Vertices*) malloc(sizeof(Vertices));
		((Vertices*) current->next)->previous = current;
		current = current->next;
		current->degree = strToInt(argv[i]);
	}
	current->next = NULL;
	sortList(first);
	while(((Vertices*) (first->next))->degree>0){
		current = first->next;
		for (int i=0; current->next!=NULL && i<((Vertices*) (first->next))->degree; i++){
			current=current->next;
			if (current->degree>0){
				current->degree--;
			}else {
				exitScript(first);
				printf("Not graphic!\n");
				return 1;
			}
		}
		((Vertices*) (first->next))->degree = 0;
		sortList(first);
	}
	printf("Graphic\n");
	exitScript(first);
	return 0;
}
