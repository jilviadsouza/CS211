#include <stdio.h>
#include <stdlib.h>

//linked list structure
struct node {
	int val;
	int count;
	struct node *next;
};

//traverse a linked list
/*void traverse(struct node* head){
	struct node *temp = head;
	while(temp != NULL){
		if (temp->next == NULL){
			printf("%d", temp->val);
			break;
		}
		printf("%d\t", temp->val);
		temp = temp->next;
	}
	return;
}*/

//inserts and orders a node
struct node* insert(struct node* head, int j){
	struct node *temp = malloc(sizeof(struct node));
	temp->val = j;
	temp->count = 1;
	temp->next = NULL;
	if (head == NULL){	//first insertion
			head = temp;
			return head;
	}

	if(temp->val < head->val){ 
		temp->next = head;
		return temp;
	}


	//sorts it
	struct node *Next = head->next;
	struct node *prev = head;
	while(Next != NULL && Next->val < temp->val){
		prev = Next;
		Next = Next->next;
	}

	temp->next = Next;
	prev->next = temp;

	return head;

}

//delete a note
struct node* delete(struct node* head, int a){
	if(head->val == a){
		
		head->count--;
		
		if(head->count == 0){
			struct node* temp = head->next;
			free(head);
			return temp;
		} 
		return head;
	}

	struct node *curr = head->next;
	struct node *prev = head;
	while(head != NULL && curr->val != a){
		prev = curr;
		curr = curr->next;
		
	}

	curr->count--;
	if (curr->count == 0){
		prev->next = curr->next;
		free(curr);
	} 

	return head;
}

//boolean method that checks if the node is already in the list
int present(struct node* head, int a){
	int counter = 0;

	while(head != NULL){
		if(head->val == a){
			counter = 1;
			break;
		}

		head = head->next;
	}
	return counter;
	
}

/*void memFree(struct node* head){
	struct node* curr = head;
	struct node* prev = NULL;

	while(curr != NULL){
		prev = curr;
		curr = curr->next;
		free(prev);
	}
} */

int main(int argc, char* argv[])
{
	if(argc != 2){
		printf("insufficient arguments \n");
		return 0;
	}

	FILE *fp;
	char i;
	int j ;

	fp = fopen(argv[1], "r");

	if(fp == NULL){
		printf("error");
		return 0;
	}

	int size = 0;
	struct node *head = NULL;

	while(fscanf(fp, "%c\t%d\n", &i, &j) > 0){
		int presence = present(head, j);
		//printf("%d\n", presence);

		if(i == 'i'){
			if(presence == 0){
				//struct node *temp = malloc(sizeof(struct node));
				//temp->val = j;
				//temp->next = NULL;
				head = insert(head, j);
				size++;

			} else { //presence = 1, there is a duplicate
				//go through, find the duplicate and increment count
				//we know the duplicate, it is j. 
			struct node *ptr = head;
			while(ptr != NULL ){
				if(ptr->val == j){
					ptr->count++;
					size++;
					break;
				}
				ptr = ptr->next;
		}

			}

		} else if (i == 'd'){
			if(head != NULL){
				if(presence == 1){
					head = delete(head, j);
					size--;
				}
			}
		}

	}

	printf("%d\n", size);
	//printf("\n");
	//traverse(head);
	struct node *temp = head;
	while(temp != NULL){
		if (temp->next == NULL){
			printf("%d", temp->val);
			break;
		}
		printf("%d\t", temp->val);
		temp = temp->next;
	}
	//memFree(head);
	struct node* curr = head;
	struct node* prev = NULL;

	while(curr != NULL){
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	fclose(fp);
	return 0;


	
}
