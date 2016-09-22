#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagNode
{
	char* Word;
	struct tagNode *NextNode;
}Node;

typedef struct tagSearch	// �˻��� ���� ������ �ϴ� �����͵��� �����ϰ� �ִ� SearchData����ü
{
	char* Word;		// �ܾ�
	int count;		// �ܾ��� ����
	int* index;		// �ܾ��� ��ġ(��)
}SearchData;

Node* CreateNode(char* input);						// ��� ����
void AppendNode(Node** Head, Node* NewNode);		// ����Ʈ�� ��� �߰�
void DestroyNode(Node* Node);						// ��� ����
void RemoveNode(Node** Head, Node* Remove);			// ����Ʈ���� ��� ����
SearchData* SearchWord(Node* Head, char* Search);	// ����Ʈ���� ���ϴ� �ܾ �˻�
Node* GetNodeAt(Node* Head, int Location);			// ��� Ž�� 
int GetNodeCount(Node* Head);						// ����Ʈ������ ��� �������
