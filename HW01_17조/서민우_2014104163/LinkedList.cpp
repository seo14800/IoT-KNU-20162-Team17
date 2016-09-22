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
	if ((*Head) == NULL)					// Head�� ���翩�θ� �ľ��ϰ� ���� ��� Head�� �߰������ν� ����Ʈ�� ����
		*Head = NewNode;
	else
	{
		Node* Tail = (*Head);				// Head���� ����
		while (Tail->NextNode != NULL)		// Head�������� NextNode�� NULL�� �� ����, �� List�� Tail�� ã�´�.
			Tail = Tail->NextNode;

		Tail->NextNode = NewNode;			// Tail�� NextNode�� ��带 �̾��ش�.
	}
}

void DestroyNode(Node* Node)
{
	free(Node);								// ��� ����
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
	int Position = 0;						// ��ġ

	Ex->count = 0;
	Ex->index = (int*)malloc(sizeof(int));	// �⺻������ int 1����ŭ�� ������ �Ҵ� ���ش�.
	Ex->Word = NULL;

	while (Current->NextNode != NULL)
	{
		if (strcmp(Search, Current->Word) == 0)
		{
			if (Ex->count != 0)
			{
				Ex->index = (int*)realloc(Ex->index, sizeof(int)*((Ex->count) + 1));	// �ߺ��ܾ �߰� �� ������ ������ �����͸� ������ä ���� ũ�⿡ int�� 1����ŭ ���� �޸� ũ�⸦ ���Ҵ� ���ش�.
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