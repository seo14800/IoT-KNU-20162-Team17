#pragma warning(disable:4996)
#include "LinkedList.h"
#include <conio.h>

int main()
{
	FILE* file;
	char *wordToken;										//strtok ��ū���� ���� �����ͺ���
	char buffer[1024];										//txt������ ��Ƶ� ���ڿ�
	char trash[] = "\t\n!.,/\'<>\":;+-*#@$!%^&()-_=` ";		//�����ȣ�迭
	char input[50];
	int ListNum;

	Node* ListHead = NULL;	
	Node* inputNode = NULL;
	Node* CurrentNode = NULL;
	SearchData* Find = NULL;		//�˻��ܾ�� ���õ� ������ ���� SearchData �����ͺ���
	
	file = fopen("word.txt", "r");
	if (file == NULL)
	{
		printf("file error");
		return 0;
	}

	while (!feof(file))					//������ ���� �� ���� �о���δ�			
	{
		fgets(buffer, sizeof(buffer), file);	//Buffer�� ��Ƶд�
		wordToken = strtok(buffer, trash);		//���� �ѹ� ��ū�� �ɷ�����

		while (wordToken != NULL)
		{
			if (wordToken != NULL)
			{
				inputNode = CreateNode(wordToken);		// ��ū�� ���������� �ɷ����� ��� List�� �߰��� ��带 ����, Append �����ش�
				AppendNode(&ListHead, inputNode);
			}
			
			wordToken = strtok(NULL, trash);
		}
		
	}

	while (strcmp(input, "stop"))						// stop �Է½� ����
	{
		printf("Input Search or 'stop' : ");
		scanf("%s", input);

		Find = SearchWord(ListHead, input);
		if (Find->count != 0)							// 0�� ��� �ܾ �������� �ʴ� ��
		{
			printf("%s�� ������ %d�� �����մϴ�.", input, Find->count);
			printf("����Ʈ������ ��ġ�� ");
			for (int i = 0; i < Find->count; i++)
			{
				printf("'%d'�� ", Find->index[i]);
			}
			printf("��忡 ��ġ�մϴ�\n");
		}
		else if (strcmp(input, "stop") == 0)
			break;
		else
			printf("%s�� ã�� �� �����ϴ�.\n", input);
		printf("\n");
	}
		
	
	ListNum = GetNodeCount(ListHead);	// ����Ʈ�� �����ϴ� ����� ���� 
	for (int i = 0; i < ListNum; i++)	// ����Ʈ ����
	{
		CurrentNode = GetNodeAt(ListHead, i);

		if (CurrentNode != NULL)
		{
			RemoveNode(&ListHead, CurrentNode);
			DestroyNode(CurrentNode);
		}
	}

	fclose(file);
	_getch();
	return 0;
}