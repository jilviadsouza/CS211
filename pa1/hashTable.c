#include <stdio.h>
#include <stdlib.h>

//for storing an item in a LL
struct node {
  int key;
  struct node *next; 

};

//for storing an LL at each index of the hash table
struct list {
  struct node *head;
  struct node *tail;

};


int N = 10000;
struct list *hashTable;

//search, finds the given key 
//returns index
int searchCount = 0;
int search(struct node *head, int key){
  int index = 0;
  struct node *temp = head;

  while(temp != NULL){
    if(temp->key == key){
      return index;
    }
    temp = temp->next;
    index++;
  }
  return -1; //if key is not present in the table
}


int collisionCount = 0; //output 1
void insert(int key){
  int index = 0;

  if(key < 0){
    index = key + N; //if key is negative, add it to N and insert key at that value
    
  } else {
    index = key%N;
  }

  //creating a LL at the given index
  struct node *head = (struct node*) hashTable[index].head;

  //creating an item to insert in the table 
  struct node *item = (struct node*) malloc(sizeof(struct node));
  item->key = key;
  //item->value = val˜[ue;
  item->next = NULL;

  //if list is empty at current index, insert
  if(head == NULL){
    hashTable[index].head = item;
    hashTable[index].tail = item;

  } else { //LL is already created at the index, there is a value there!
    collisionCount++;
    int search_index = search(head, key);
    if (search_index == -1){ //duplicate not found
      //add to the end of the list 
      hashTable[index].tail->next = item;
      hashTable[index].tail = item;
    }else {
	    free(item);
    }
  }
  //printf("%d\n", collisionCount);

}

void freeNode(struct node* head){
    //for(int i =0; i < N; i++){
    //struct node *head = hashTable[i].head;
    struct node *temp;// = malloc(sizeof(node*));
    while(head != NULL){
      temp = head;
      head = head->next;
      free(temp);
      temp = NULL;
    }
}

//reads file 
//initialize hashtable 
//if i then insert, if s then search
int main(int argc, char* argv[])
{

  if(argc != 2){
    printf("insufficient arguments\n");
    return 0;
  }

  FILE *fp;
  char a;
  int b;

  fp = fopen(argv[1], "r");

  hashTable = (struct list*) malloc(N*sizeof(struct list));
  //initialize 
  int i = 0;
  for(i = 0; i < N; i++){
    
    hashTable[i].head = NULL;
    hashTable[i].tail = NULL;
  }

  while(fscanf(fp, "%c\t%d\n", &a, &b) > 0){
    if(a == 'i'){
      insert(b);
      //printf(collisionCount);
    } else if(a == 's'){
      if(b<0) b=b+N;
      int index = b%N;
      if(search(hashTable[index].head, b)!=-1) searchCount++;
      //printf(searchCount);
    }
  }

  printf("%d\n", collisionCount);
  printf("%d\n", searchCount);
  //free(item);
  for(int i =0; i < N; i++){
    freeNode(hashTable[i].head);    
//  free(hashTable[i]);
  }
  free(hashTable); 
  fclose(fp);
  return 0;
}
