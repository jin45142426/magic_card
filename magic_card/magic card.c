/**************************************************************************************************************************

	*프로그램명 : magic_card ver. 0.1

	* 작성일 : 2024.03.21
	
	* 학  번 : 20214003	
	
	* 이  름 : 최우진

	*마술 카드를 구현해보자.(2주)
	
		-n장의 카드를 입력 받아 처리할 수 있는 마술 카드를 만드시오.

		-교재 1장에 있는 프로그래밍 실습에 있는 프로그램 활용(교재에서는 단지 5장의 카드만을 받아서 처리하는 프로그램)

		-프로그램이 실행되면 n 값을 입력하도록 하고 화면상에 카드를 하나씩 보여주고 그에 대해 Yes와 no 를 대답하도록 한다.

		-그러면 본인이 생각한 숫자가 얼마라고 카드를 보여준다.

***************************************************************************************************************************/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

//함수 선언
void CARD_NUMBER(int n, int number1, int k);

int main()
{
	//몇장의 카드를 받을지 변수 선언
	int n = 0;

	//2의 n승 저장
	int number1 = 0;

	//0 또는 1을 저장
	int HEARTNUM = 0;

	//생각한 숫자
	int RENUMBER = 0;

	//개행 숫자
	int k = 0;

	//사용자가 Yes 와 No 중에 입력한 값을 비교하기 위한 변수 선언
	char* Yes_NO = malloc(sizeof(char)*10);
	
	char* yes = { "Yes" };
	char* no = { "No" };

	printf("카드 장수를 선택해주세요: ");
	scanf("%d",&n);

	//number1에 2의 n승을 저장
	number1 = pow(2, n);
	k = n / 15;
	//입력받은 카드 장의 수 만큼 반복 
	for (int j = 1; j <= n; j++)
	{
		//숫자가 많아지면 세로로만 길어지는걸 방지하기위해 가로도 길어지는 반복문 선언
		if (k > 0)
		{
			printf("|");
			for (int i = 0; i < (n / 8) + 1; i++)
				printf("===========================================================================");
			printf("|\n");
		}
	
		else
			printf("|===========================================================================|\n");
	

		//함수 호출 ,j는 반복 횟수 , number1은 2의 n승 만큼의 수 k는 n / 15의 값 개행을 위한 값전달
		CARD_NUMBER(j, number1,k+1);

		//마지막 줄 = 출력
		if (k > 0)
		{
			printf("|\n");
			printf("|");
			for (int i = 0; i < k + 1; i++)
				printf("===========================================================================");
			printf("|\n");
		}
		else
		{
			printf("|\n");
			printf("|===========================================================================|\n");
			printf("\n");
		}
		


		printf("생각한 숫자가 있나요? 있으면 Yes 없으면 No을 입력해주세요: ");
		scanf("%s",Yes_NO);
	
		//카드안에 숫자가 있으면 1 없으면 0을 HEARTNUM에 저장
		if (strcmp(Yes_NO,yes)==0)
			HEARTNUM = 1;
		else if (strcmp(Yes_NO, no) == 0)
			HEARTNUM = 0;

		//Yes 또는 No 외의 문자나 숫자를 입력하면 프로그램 종료
		if (strcmp(Yes_NO, yes) != 0 && strcmp(Yes_NO, no) != 0)
		{
			printf("Yes또는 No만 입력해주시요!");
			return 0;
		}

		//상대방이 생각한 숫자를 계산
		RENUMBER += pow(2, j-1) * HEARTNUM;

		//콘솔창 초기화
		system("cls");
	}
	
	free(Yes_NO);

	printf("당신이 생각한 숫자는 %d입니다.", RENUMBER);
	
	return 0;
}


/*****************************************************************************************************************************

		*함수명 : CARD_NUMBER
		 
		*작성자 : 최우진
		
		*작성일 : 2024.03.21

		-이 함수는 n번째 카드에서  0 ~ (number1-1)의 수 사이에 경우의 수 0 과 1 중에 1에 해당하면 출력하게 만드는 함수이다.
		
		-원리는 카드의 장수가 하나씩 증가할때마다 0과 1은 2배씩 늘어난다. 이를 이용해서 1에 해당하는 숫자를 출력

******************************************************************************************************************************/
void CARD_NUMBER(int n, int number1, int k)
{
	//홀수 또는 짝수 변수 초기화
	int numberX = 0;

	//변수 초기화
	int trash = 0;

	//2의 n승 -1
	int POW = pow(2, n-1);

	//한 행에 숫자가 몇개 출력됐는지 알려주는 변수
	int j = 0;

	

	printf("|");
	//1 ~ number-1 숫자중에 1에 해당하는 숫자만 출력
	for(int i = 0; i < number1 ; i++)
	{
		// i / pow 를 나눈 몫이 홀수 인지 아닌지를 알기 위한 식
		numberX = i / POW;

		//만약에 numberX가 홀수고 i가 0보다크면 숫자 출력
		if (numberX % 2 != 0  && i > 0)
		{
			printf("%15d", i);
			j++;
		}

		//카드 크기를 맞추기 위한 변수 선언 ex) 5개의 숫자가 나와야 알맞게 카드를 만들 수 있는데 한 두개정도 숫자만 나오면 나머지 4,3,개를 공백으로 채운다.
		trash = (5 * k) - j;

		//빈 숫자만큼 공백 채우기
		if (i +1 == number1)
			for (int m = 0; m < trash; m++)
				printf("               ");

		//j가 6이면 개행
		if (j == 5 * k )
		{
			printf("|");
			printf("\n");
			printf("|");

			//j값 0으로 초기화
			j = 0;
		}

	}

}
