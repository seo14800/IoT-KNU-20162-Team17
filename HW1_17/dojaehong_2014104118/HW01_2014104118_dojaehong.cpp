#include "txtreader.h"


void main()
{
	
	headNode *fhead = createHead();
	char split[] = "~!@#$%^&*()_+`-={}[]\\|;:'\"<>,./?\n\t ";
	char check=78;//N ASCII

	filereader(fhead, split);//파일 읽기
	while(check==78||check==110){
		search(fhead);
		
		while(true){
			printf("\nwanna finish?(Y/N)");
			fflush(stdin);
			check = getchar();
			if (check == 78 || check == 89 || check == 121 || check == 110)
				break;
		}
		system("cls");
	}
}