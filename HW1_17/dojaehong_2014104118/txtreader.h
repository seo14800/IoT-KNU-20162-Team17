#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct pstrNode{//구조체
	char* txtstring;
	int index;
	pstrNode* link;
}strNode;

typedef struct{
	int size;
	strNode* head;
}headNode;

strNode *createNode(int index, char *string);
headNode *createHead();
void filereader(headNode *fhead, char* split);
void searchStr(headNode *headNode, char *targetstring, int searchnum);
void insertnode(headNode *head, strNode *insNode);
void printallnode(headNode *head);//test용
void search(headNode *fhead);
void searchIndex(headNode *headNode, int searchnum);

headNode *createHead(){
	headNode *head = (headNode*)malloc(sizeof(headNode));
	head->head = NULL;
	head->size = 0;
	return head;
}

void filereader(headNode *fhead,char* split){
	FILE *tfile;
	char *token = NULL;
	char strbuf[1024];
	strNode *sptr;
	int index = 0;

	tfile = fopen("target.txt", "r");
	if (tfile == NULL){
		printf("File open error!\n");
	}

	else{

		while (!feof(tfile)){//파일 끝까지 읽어서 voca linked list 만듦

			fgets(strbuf, sizeof(strbuf), tfile);
			token = strtok(strbuf, split);
			if (token != NULL){
				//printf("%s\n", token);
				index++;
				char *buf = (char*)calloc(255, sizeof(char));
				strcpy(buf, token);
				sptr = createNode(index, buf);
				insertnode(fhead, sptr);
			}

			while (token != NULL){
				token = strtok(NULL, split);
				if (token != NULL){
					//printf("%s\n", token);
					index++;
					char *buf = (char*)calloc(255, sizeof(char));
					strcpy(buf, token);
					sptr = createNode(index, buf);
					insertnode(fhead, sptr);
				}

			}

		}
		//printallnode(fhead);
	}
	//printf("File load complete.\n");
}
strNode *createNode(int index, char *string){
	strNode *sNode=(strNode*)malloc(sizeof(strNode));

	if (!sNode)//메모리 할당 실패
		return NULL;

	sNode->index = index;
	sNode->txtstring = string;
	sNode->link = NULL;

	return sNode;
}

void searchStr(headNode *headNode,char *targetstring){

	strNode* buf;
	int count = 0;
	if(headNode->head == NULL){
		printf("Null file.\n");
	}
	else{
		buf = headNode->head;
		printf("Target voca:%s\n", targetstring);
		for(int i=0;i<headNode->size;i++){
			if (strcmp(buf->txtstring, targetstring) == 0){
				printf("list[%d]:%s\n", buf->index, buf->txtstring);
				count++;
			}
			buf = buf->link;
		}
	}

	if (count == 0)
		printf("search failed!\n");
	else
		printf("finded:%d", count);
}

void searchIndex(headNode *headNode, int searchnum){

	strNode* buf;
	int count = 0;
	if (headNode->head == NULL){
		printf("Null file.\n");
	}
	else{
		buf = headNode->head;
		printf("Target Index:%d\n", searchnum);
		for (int i = 0; i<headNode->size; i++){
			if (buf->index==searchnum){
				printf("list[%d]:%s\n", buf->index, buf->txtstring);
				count++;
			}
			buf = buf->link;
		}
	}

	if (count == 0)
		printf("search failed!\n");
	else
		printf("finded:%d", count);
}

void insertnode(headNode *head,strNode *insNode){

	if (head->size == 0){
		head->head = insNode;
		(head->size)++;
	}
	else
	{
		strNode *ptr=head->head;
		while (ptr->link != NULL){
			ptr = ptr->link;
		}
		ptr->link = insNode;
		(head->size)++;
	}
}

void printallnode(headNode *head){
	strNode *printNode;
	printNode = head->head;
	while (printNode->link != NULL){
			printf("%s[%d]->", printNode->txtstring,printNode->index);
			printNode=printNode->link;
	}
	printf("%s[%d]", printNode->txtstring, printNode->index);
}

void search(headNode *fhead){

	char *targetvoca = (char*)malloc(255 * sizeof(char));
	int ch=0;
	int targetnum;
	
	
	do{
		printf("1.voca mode\n2.number mode\nSelect(1 or 2):");
		scanf("%d",&ch);
	} while (!(ch == 1 || ch == 2));

	printf("\n");

	if (ch == 1){
		printf("Search Target(Voca):");
		scanf("%s",targetvoca);
		searchStr(fhead, targetvoca);
	}
	else if (ch == 2){
		printf("Search Target(index):");
		scanf("%d",&targetnum);
		searchIndex(fhead, targetnum);
	}


}