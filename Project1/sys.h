#pragma once
#define WINDOW_WIDTH 1024    // ���ڿ��
#define WINDOW_HEIGHT 768  // ���ڸ߶�

#define SUBJECTS_WIDTH 240 //�ı�����
#define SUBJECTS_HEIGHT 80 //�ı���߶�

#define BUTTON_WIDTH 240    // ��ť���
#define BUTTON_HEIGHT 80    // ��ť�߶�
#define CORNERRADIUS 10    //Բ��

#define BACK_WIDTH 100//���ذ�ť���
#define BACK_HEIGHT 70//���ذ�ť�߶�

#define MAX_EXAM 5		//����Ŀ����
#define MAX_STU 50		//���ѧ������

#define MAX_SCORE 100//����
#define WINDOW_WIDTH 1024    // ���ڿ��
#define WINDOW_HEIGHT 768  // ���ڸ߶�
#define CORNERADIUS 10 //Բ��
#define R 0xC7 //��ɫ����R
#define G 0xBF  //G
#define B 0xC4  //B
#define NUM 10 //һҳ���10��
typedef struct RoundRectButton	   //Բ�Ǿ��ΰ�ť
{
	int x, y; //����
	int width, height;  //��Ⱥ͸߶�
	float radius;//Բ��
	int r, g, b;//��ɫ
	int fontsize;//�����С
	char label[30];//��ť����

}BUTTON;

typedef struct studentgrade
{
	int subject[MAX_EXAM];//ÿ��ѧ�Ƶķ���
	int sum;//�ܷ�
}stugrade;

typedef struct student
{
	char number[11];
	char name[21];
	stugrade grade;
}student;
typedef struct {
	int index;       // ѧ������
	int matchScore;  // ƥ��÷�
} SearchResult;