#pragma warning(disable:4996)
#include "LinkedList.h"
#include <conio.h>

int main()
{
	FILE* file;
	char *wordToken;										//strtok 토큰으로 쓰일 포인터변수
	char buffer[1024];										//txt파일을 담아둘 문자열
	char trash[] = "\t\n!.,/\'<>\":;+-*#@$!%^&()-_=` ";		//문장부호배열
	char input[50];
	int ListNum;

	Node* ListHead = NULL;	
	Node* inputNode = NULL;
	Node* CurrentNode = NULL;
	SearchData* Find = NULL;		//검색단어와 관련된 정보를 가진 SearchData 포인터변수
	
	file = fopen("word.txt", "r");
	if (file == NULL)
	{
		printf("file error");
		return 0;
	}

	while (!feof(file))					//파일이 끝날 때 까지 읽어들인다			
	{
		fgets(buffer, sizeof(buffer), file);	//Buffer에 담아둔다
		wordToken = strtok(buffer, trash);		//먼저 한번 토큰을 걸러낸다

		while (wordToken != NULL)
		{
			if (wordToken != NULL)
			{
				inputNode = CreateNode(wordToken);		// 토큰이 성공적으로 걸러졌을 경우 List에 추가할 노드를 생성, Append 시켜준다
				AppendNode(&ListHead, inputNode);
			}
			
			wordToken = strtok(NULL, trash);
		}
		
	}

	while (strcmp(input, "stop"))						// stop 입력시 종료
	{
		printf("Input Search or 'stop' : ");
		scanf("%s", input);

		Find = SearchWord(ListHead, input);
		if (Find->count != 0)							// 0일 경우 단어가 존재하지 않는 것
		{
			printf("%s는 문서에 %d개 존재합니다.", input, Find->count);
			printf("리스트에서의 위치는 ");
			for (int i = 0; i < Find->count; i++)
			{
				printf("'%d'번 ", Find->index[i]);
			}
			printf("노드에 위치합니다\n");
		}
		else if (strcmp(input, "stop") == 0)
			break;
		else
			printf("%s를 찾을 수 없습니다.\n", input);
		printf("\n");
	}
		
	
	ListNum = GetNodeCount(ListHead);	// 리스트에 존재하는 노드의 개수 
	for (int i = 0; i < ListNum; i++)	// 리스트 제거
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