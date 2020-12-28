#include <stdio.h>
#include <stdlib.h>

struct node {
	int val;
	struct node *left;
	struct node *right;
};

struct node* make_node(int val){
	struct node* newNode = malloc(sizeof(struct node));
	newNode->val = val;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}
struct node* insert(struct node* root, int val){

	if(root == NULL)
		//make a new root node
		return make_node(val);
	

	if(root->val < val)
		root->right = insert(root->right, val);
	 else if(root->val > val)
		root->left = insert(root->left, val);
	

	return root;
}

void inorder(struct node* root){
	if(root == NULL) return;
	

	inorder(root->left);
	printf("%d\t", root->val);
	inorder(root->right);
}

void free_bst(struct node* root){
	if (root == NULL){
		return;
	}
	free_bst(root->left);
	free_bst(root->right);
	free(root);
}

int main(int argc, char* argv[])
{
	if(argc != 2){
		printf("insufficient arguments\n");
		return 0;
	}

	FILE *fp;
	char i;
	int j;

	fp = fopen(argv[1], "r");

	if(fp == NULL){
		printf("error\n");
		return 0;
	}

	struct node* root =NULL; // malloc(sizeof(struct node));
	

	while(fscanf(fp, "%c\t%d\n", &i, &j) > 0){
		//if(i == 'i'){
			
		root = insert(root, j);
			
		//}

		
	}
	inorder(root);
	fclose(fp);
	free_bst(root);
	return 0;
}
