//====================================================================
//����ü
//====================================================================
//-->����� ���� ������ Ÿ��
//-->���� ���� �������� �������� ���ο� Ÿ���� ����
//====================================================================
//����� �����͸� ǥ��
//�̸�, ����, ��ȭ��ȣ ��
//�л�
//�й�, �̸�, �г�, �а�...
//====================================================================
/*
struct Book {
	char title[255];//����
	char writer[32];//����
	int price;//����
};

//�ڵ���
struct Car {
	int carNo;
	char carName[32];
};*/
//�ּҷ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
typedef struct NameCard {
	int no;		   //�����ȣ
	char name[32]; //�̸�
	char phone[12];//��ȭ��ȣ
}NAMECARD;

typedef int INT;//typedef (�̰���)(�̰����ε� ���ڴ�.)

int main(void) {
	//����ü ����
	INT a = 4885;
	NAMECARD card;
	card.no = 1234;
	//card.name = "���ο�";
	//card.phone = "01011112222";//�� ������ ������ �� ����
	strcpy(card.name, "���ο�");
	strcpy(card.phone, "01020098840");

	printf("no:%d\n", card.no);
	printf("no:%s\n", card.name);
	printf("no:%s\n", card.phone);

	return 0;
}