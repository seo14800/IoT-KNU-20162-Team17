#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagNode
{
	char* Word;
	struct tagNode *NextNode;
}Node;

typedef struct tagSearch	// 검색을 통해 얻어내고자 하는 데이터들을 포함하고 있는 SearchData구조체
{
	char* Word;		// 단어
	int count;		// 단어의 개수
	int* index;		// 단어의 위치(들)
}SearchData;

Node* CreateNode(char* input);						// 노드 생성
void AppendNode(Node** Head, Node* NewNode);		// 리스트에 노드 추가
void DestroyNode(Node* Node);						// 노드 제거
void RemoveNode(Node** Head, Node* Remove);			// 리스트에서 노드 제거
SearchData* SearchWord(Node* Head, char* Search);	// 리스트에서 원하는 단어를 검색
Node* GetNodeAt(Node* Head, int Location);			// 노드 탐색 
int GetNodeCount(Node* Head);						// 리스트에서의 노드 개수계산
