//====================================================================
//구조체
//====================================================================
//-->사용자 정의 데이터 타입
//-->여러 개의 변수들의 조합으로 새로운 타입을 정의
//====================================================================
//사람의 데이터를 표현
//이름, 나이, 전화번호 등
//학생
//학번, 이름, 학년, 학과...
//====================================================================
/*
struct Book {
	char title[255];//제목
	char writer[32];//저자
	int price;//가격
};

//자동차
struct Car {
	int carNo;
	char carName[32];
};*/
//주소록
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
typedef struct NameCard {
	int no;		   //단축번호
	char name[32]; //이름
	char phone[12];//전화번호
}NAMECARD;

typedef int INT;//typedef (이것을)(이것으로도 쓰겠다.)

int main(void) {
	//구조체 변수
	INT a = 4885;
	NAMECARD card;
	card.no = 1234;
	//card.name = "유민우";
	//card.phone = "01011112222";//왜 오류가 나오는 지 과제
	strcpy(card.name, "유민우");
	strcpy(card.phone, "01020098840");

	printf("no:%d\n", card.no);
	printf("no:%s\n", card.name);
	printf("no:%s\n", card.phone);

	return 0;
}