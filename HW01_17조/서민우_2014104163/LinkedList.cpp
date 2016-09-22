#include "LinkedList.h"

Node* CreateNode(char* input)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Word = input;
	NewNode->NextNode = NULL;
	
	NewNode->NextNode = NULL;

	return NewNode;
}

void AppendNode(Node** Head, Node* NewNode)
{
	if ((*Head) == NULL)					// Head의 존재여부를 파악하고 없을 경우 Head를 추가함으로써 리스트를 생성
		*Head = NewNode;
	else
	{
		Node* Tail = (*Head);				// Head에서 시작
		while (Tail->NextNode != NULL)		// Head에서부터 NextNode가 NULL일 때 까지, 즉 List의 Tail을 찾는다.
			Tail = Tail->NextNode;

		Tail->NextNode = NewNode;			// Tail의 NextNode에 노드를 이어준다.
	}
}

void DestroyNode(Node* Node)
{
	free(Node);								// 노드 해제
}

void RemoveNode(Node** Head, Node* Remove)
{
	if (*Head == Remove)					
		*Head = Remove->NextNode;
	else
	{
		Node* Current = *Head;

		while (Current != NULL && Current->NextNode != Remove)
			Current = Current->NextNode;

		if (Current != NULL)
			Current->NextNode = Remove->NextNode;
	}
}

SearchData* SearchWord(Node* Head, char* Search)
{
	SearchData* Ex = (SearchData*)malloc(sizeof(SearchData));
	Node* Current = Head;
	int Position = 0;						// 위치

	Ex->count = 0;
	Ex->index = (int*)malloc(sizeof(int));	// 기본적으로 int 1개만큼의 공간을 할당 해준다.
	Ex->Word = NULL;

	while (Current->NextNode != NULL)
	{
		if (strcmp(Search, Current->Word) == 0)
		{
			if (Ex->count != 0)
			{
				Ex->index = (int*)realloc(Ex->index, sizeof(int)*((Ex->count) + 1));	// 중복단어가 발견 될 때마다 기존의 데이터를 복사한채 본래 크기에 int형 1개만큼 더한 메모리 크기를 재할당 해준다.
			}
			Ex->index[Ex->count] = Position;
			Ex->count++;
		}
		Position++;
		Current = Current->NextNode;
	}

	return Ex;
}

Node* GetNodeAt(Node* Head, int Location)
{
	Node* Current = Head;

	while (Current != NULL && (--Location) >= 0)
		Current = Current->NextNode;

	return Current;
}

int GetNodeCount(Node* Head)
{
	int Count = 0;
	Node* Current = Head;

	while (Current != NULL)
	{
		Current = Current->NextNode;
		Count++;
	}

	return Count;
}