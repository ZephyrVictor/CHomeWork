#define SHOW_CONSOLE
#include <graphics.h>
#include <string.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <ege.h>
#include <math.h>
#include <ege/sys_edit.h>
#include <windows.h>
#include "sys.h"
#include<Windows.h>
#include<mmsystem.h>//������ý���豸�ӿ�ͷ�ļ�
#include <cstdlib> // ����rand������ͷ�ļ�
#pragma comment (lib,"winmm.lib")//���ؾ�̬��




// ȫ�ֱ���

int STU_NUM = 0;//�û������ѧ������
int SUB_NUM = 0;//ѧ������
char subname[MAX_EXAM][16];//����ѧ�Ƶ�����
void studentEntryWindow();//ѧ������¼�봰��
void studentManagementWindow();//������
void mainWindow();//������
void drawButton(const RoundRectButton* button);//������ť
bool click(const RoundRectButton* button, int x, int y);//�ж���ť���
void puttext(int x, int y, int size, const char* text);//����ı�
void initEditBox(sys_edit* editBox, int x, int y, int width, int height);//��ʼ���༭��
void draw_entry(int back_x,int back_y,BUTTON buttonarray[]);//���ƽ���
int addstudent(student stu[],int count,int back_x,int back_y,BUTTON buttonarray[]);//���ѧ��
int delstudent(student stu[], int count, int back_x, int back_y, BUTTON buttonarray[]);//ɾ��ѧ��
void printstudent(student stu[], char subname[MAX_EXAM][16]);//����ɼ�
void calculate_score(student stu[]);//����ѧ���ܷ�
void write_file(student stu[]);//д���ļ�
void read_file(student stu[], int* STU_NUM, int* SUB_NUM);//�����ļ�
void swap(student* a, student* b);//����������أ���������λ��
int partition(student arr[], int low, int high);//����������أ�ȷ����׼λ��
void quickSort(student arr[], int low, int high);//�����������壨��ΪҪ�漰�ܶ������//����ʹ�����Ч�ʽϸߵĿ�������������򣬼�����Դռ�ã�
int vaguesearch(const char* key, const char* str);//ģ������
int ranksearch(student stu[], int count, const char* input_number);//�������
bool IsProcessRunAsAdmin();//����Ƿ��ǹ���ԱȨ��






void studentManagementWindow()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);// ��ʼ��ͼ�δ���

	setbkcolor(EGERGB(0xFE, 0xFA, 0xE0));

	setcaption("��Ϣ������鿴");



	int BackButton_x, BackButton_y; //���������ķ��ذ�ť���ꡰ
	int AddInfoButton_x, AddInfoButton_y;//���������������Ϣ�İ�ť"
	int RemoveInfoButton_x, RemoveInfoButton_y;//"�����ɾ����Ϣ�İ�ť"

	int complete1button_x, complete1button_y; //"�����Ŀ������ɰ�ť"

	int back_x = 80;
	int back_y = 80;
	BUTTON buttonarray[8];
	const int buffSize = 100;//���뻺����
	char strBuffer[100] = "";//���뻺����
	sys_edit editBox;//��Ŀ����
	student stu[50]{}; //ѧ�����������50��
	read_file(stu, &STU_NUM, &SUB_NUM);
	int count = STU_NUM;//ѧ�����������ں�����������
	quickSort(stu, 0, count - 1);//��ѧ������
	int i, j;

	

	BUTTON back = {
		back_x,back_y,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"����"
	}; buttonarray[0] = { back }; //���ذ�ť
	BUTTON number_search = {
		800,back_y,
		130,80,
		CORNERADIUS,
		R,G,B,
		28,
		"��ѧ��ģ������"
	}; buttonarray[1] = { number_search }; //ѧ��������ť
	BUTTON add_student = {
		back_x, back_y + 200,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"���ѧ���ɼ�"
	}; buttonarray[2] = { add_student }; //���ѧ����ť
	BUTTON del_student = {
		back_x,back_y + 400,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"ɾ��ѧ��"
	}; buttonarray[3] = { del_student };//ɾ��ѧ����ť
	BUTTON check ={
		back_x, back_y + 600,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"�鿴����"
	}; buttonarray[4] = { check };//�鿴������ť
	BUTTON name_search = {
		800, back_y + 120,
		130,80,
		CORNERADIUS,
		R,G,B,
		28,
		"������ģ������"
	}; buttonarray[5] = { name_search };//����������ť
	BUTTON acc_name_search = {
		800,2 * back_y + 160,
		130,80,
		CORNERADIUS,
		R,G,B,
		28,
		"��������ȷ����"
	}; buttonarray[6] = { acc_name_search };//����������ť
	BUTTON acc_number_search = {
		800,3 * back_y + 200,
		130,80,
		CORNERADIUS,
		R,G,B,
		28,
		"��ѧ�ž�ȷ����"
	}; buttonarray[7] = { acc_number_search };//ѧ��������ť

	
	puttext(back_x + 100, back_y + 30, 25, "����ý���󣬳ɼ��Զ�����Ϊ����");

	for (i = 0; i < 8; i++)						//�������а�ť
	{
		drawButton(&buttonarray[i]);
	}

	// ����ѭ�������ڼ�������¼�
	while (1)
	{
		// ��ȡ�����Ϣ
		mouse_msg msg = getmouse();

		// �ж��Ƿ��������¼�
		if (msg.is_left())
		{
			// �ж��Ƿ���갴��
			if (msg.is_down())
			{
				// �������Ӱ�ť
				if (click(&add_student, msg.x, msg.y))
				{
					// �������ѧ�����������ظ��º��ѧ������
					count = addstudent(stu, count, back_x, back_y, buttonarray);

					// ��ջ�ͼ�豸
					cleardevice();

					// ���»��ƽ���
					draw_entry(back_x, back_y, buttonarray);

					// ����ȫ��ѧ������
					STU_NUM = count;

					// ����ѧ������
					calculate_score(stu);

					// ��ѧ����Ϣд���ļ�
					write_file(stu);

					// ����ȫ��ѧ������
					STU_NUM = count;

					// ��ѧ����Ϣ���п�������
					quickSort(stu, 0, count - 1);

					// ��ѧ����Ϣд���ļ�
					write_file(stu);
				}
				// �����ɾ����ť
				else if (click(&del_student, msg.x, msg.y))
				{
					// ����ɾ��ѧ�����������ظ��º��ѧ������
					count = delstudent(stu, count, back_x, back_y, buttonarray);

					// ����ȫ��ѧ������
					STU_NUM = count;

					// ��ѧ����Ϣ���п�������
					quickSort(stu, 0, count - 1);

					// ��ѧ����Ϣд���ļ�
					write_file(stu);
				}
				// ����˲鿴��ť
				else if (click(&check, msg.x, msg.y))
				{
					// ����������ʾ
					setcolor(RED);
					setfont(35, 0, "΢���ź�");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "��򿪿���̨�鿴");

					// ��ӡѧ����Ϣ������̨
					printstudent(stu, subname);
				}
				// ����˰�ѧ��������ť
				else if (click(&number_search, msg.x, msg.y))
				{
					char input[21];

					// ��������򣬻�ȡҪ������ѧ��
					inputbox_getline("������Ҫ������ѧ��", "������ѧ��ѧ��\nע�⣺1.���������ֻ�Ӣ��\n2.���λ��Ϊ10������ᱻ����\n3.������Ϊģ������������������Ⱥ�˳��\n4.��ѯ���Ϊ���а����",
						input, 11);

					// ����������ʾ
					setcolor(RED);
					setfont(35, 0, "΢���ź�");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "��򿪿���̨�鿴");

					int found = 0;
					printf("\nresults:\n");

					// ��ӡ��ͷ
					printf("%2s%11s%25s", "  ", "StudentID", "Name");
					for (i = 0; i < SUB_NUM; i++)
					{
						printf("%15s", subname[i]);
					}
					printf("%5s", "SUM");
					printf("\n");

					// ����ѧ����Ϣ������ģ������
					for (i = 0; i < count; i++)
					{
						if (vaguesearch(input, stu[i].number) == 1)
						{
							found = 1;
							// ���ѧ����Ϣ
							printf("%2d", i + 1);//������
							printf("%11s%25s", stu[i].number, stu[i].name);//����
							for (int j = 0; j < SUB_NUM; j++)
							{
								printf("%15d", stu[i].grade.subject[j]);//��Ŀ����
							}
							printf("%5d", stu[i].grade.sum);//�ܷ�
							printf("\n");
						}
					}

					// ���û���ҵ�ƥ���ѧ����Ϣ
					if (found == 0)
					{
						printf("No matched student!\n");
					}
				}
				// ����˰�����������ť
				else if (click(&name_search, msg.x, msg.y))
				{
					char input[21];

					// ��������򣬻�ȡҪ����������
					inputbox_getline("������Ҫ����������", "������ѧ������\nע�⣺1.���������ֻ�Ӣ��\n2.���λ��Ϊ20������ᱻ����\n3.������Ϊģ������,����������Ⱥ�˳��\n4.��ѯ���Ϊ���а����",
						input, 21);

					// ����������ʾ
					setcolor(RED);
					setfont(35, 0, "΢���ź�");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "��򿪿���̨�鿴");

					int found = 0;
					printf("\nresults:\n");

					// ��ӡ��ͷ
					printf("%2s%11s%25s", "  ", "StudentID", "Name");
					for (i = 0; i < SUB_NUM; i++)
					{
						printf("%15s", subname[i]);
					}
					printf("%5s", "SUM");
					printf("\n");

					// ����ѧ����Ϣ������ģ������
					for (i = 0; i < count; i++)
					{
						if (vaguesearch(input, stu[i].name) == 1)
						{
							found = 1;
							// ���ѧ����Ϣ
							printf("%2d", i + 1);//������
							printf("%11s%25s", stu[i].number, stu[i].name);//����
							for (int j = 0; j < SUB_NUM; j++)
							{
								printf("%15d", stu[i].grade.subject[j]);//��Ŀ����
							}
							printf("%5d", stu[i].grade.sum);//�ܷ�
							printf("\n");
						}
					}

					// ���û���ҵ�ƥ���ѧ����Ϣ
					if (found == 0)
					{
						printf("No matched student!\n");
					}
				}
				// ����˷��ذ�ť
				else if (click(&back, msg.x, msg.y))
				{
					// ��ջ�ͼ�豸
					cleardevice();

					// ����������
					mainWindow();

					// ����ѭ��
					break;
				}
				// ����˰�������׼������ť
				else if (click(&acc_name_search, msg.x, msg.y))
				{
					char input[21];
					int isfind = 0;
					int pos = -1;

					// ��������򣬻�ȡҪ����������
					inputbox_getline("������Ҫ����������", "������ѧ������\nע�⣺1.���������ֻ�Ӣ��\n2.���λ��Ϊ20������ᱻ����\n3.������Ϊ��ȷ����\n4.��ѯ���Ϊ���а����",
						input, 21);

					// ����������ʾ
					setcolor(RED);
					setfont(35, 0, "΢���ź�");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "��򿪿���̨�鿴");

					int found = 0;
					printf("\nresults:\n");

					// ��ӡ��ͷ
					printf("%2s%11s%25s", "  ", "StudentID", "Name");
					for (int i = 0; i < SUB_NUM; i++)
					{
						printf("%15s", subname[i]);
					}
					printf("%5s", "SUM");
					printf("\n");
					for (int i = 0; i < count; i++)
					{
						isfind = 0;
						if (strcmp(stu[i].name, input) == 0) // ��ȫ��� ���Ǿ�ȷ����
						{
							pos = i;
							isfind = 1;
						}
						if (isfind)
						{
							// ���ѧ����Ϣ
							printf("%2d", pos + 1);//������
							printf("%11s%25s", stu[pos].number, stu[pos].name);//����
							for (int j = 0; j < SUB_NUM; j++)
							{
								printf("%15d", stu[pos].grade.subject[j]);//��Ŀ����
							}
							printf("%5d", stu[pos].grade.sum);//�ܷ�
							printf("\n");
						}
					}
					// ���û���ҵ�ƥ���ѧ����Ϣ
					if (pos == -1)
					{
						printf("No matched student!\n");
					}
				}
				// ����˰�ѧ�ž�׼������ť
				else if (click(&acc_number_search, msg.x, msg.y))
				{
					char input[21];
					int isfind = 0;
					int pos = -1;

					// ��������򣬻�ȡҪ����������
					inputbox_getline("������Ҫ����������", "������ѧ��ѧ��\nע�⣺1.���������ֻ�Ӣ��\n2.���λ��Ϊ20������ᱻ����\n3.������Ϊ��ȷ����\n4.��ѯ���Ϊ���а����",
						input, 21);

					// ����������ʾ
					setcolor(RED);
					setfont(35, 0, "΢���ź�");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "��򿪿���̨�鿴");

					int found = 0;
					printf("\nresults:\n");

					// ��ӡ��ͷ
					printf("%2s%11s%25s", "  ", "StudentID", "Name");
					for (int i = 0; i < SUB_NUM; i++)
					{
						printf("%15s", subname[i]);
					}
					printf("%5s", "SUM");
					printf("\n");

					for (int i = 0; i < count; i++)
					{	
						isfind = 0;
						if (strcmp(stu[i].number, input) == 0) // ��ȫ��� ���Ǿ�ȷ����
						{
							pos = i;
							isfind = 1;
						}
						if (isfind)
						{
							// ���ѧ����Ϣ
							printf("%2d", pos + 1);//������
							printf("%11s%25s", stu[pos].number, stu[pos].name);//����
							for (int j = 0; j < SUB_NUM; j++)
							{
								printf("%15d", stu[pos].grade.subject[j]);//��Ŀ����
							}
							printf("%5d", stu[pos].grade.sum);//�ܷ�
							printf("\n");
						}
					}
					// ���û���ҵ�ƥ���ѧ����Ϣ
					if (pos == -1)
					{
						printf("No matched student!\n");
					}
				}
			}
		}
	}
}
void drawButton(const RoundRectButton* button)
{
	setfillcolor(EGEARGB(0xFF, R, G, B)); //�����ɫ
	//���ƾ���
	ege_fillrect((float)(button->x + button->radius), (float)(button->y),
		(float)(button->width - 2 * button->radius), float(button->height)
	);

	ege_fillrect((float)(button->x), (float)(button->y + button->radius),
		(float)(button->radius), (float)(button->height - 2 * button->radius)
	);

	ege_fillrect((float)(button->x + button->width - button->radius),
		(float)(button->y + button->radius),
		(float)(button->radius), (float)(button->height - 2 * button->radius)
	);

	//ȷ��Բ�ǰ뾶������
	float diameter = 2 * button->radius;
	float dx = button->width - diameter;
	float dy = button->height - diameter;

	//�����ĸ�Բ��
	ege_fillpie((float)(button->x + dx), (float)(button->y + dy), diameter, diameter, 0.0f, 90.0f);
	ege_fillpie((float)(button->x), (float)(button->y + dy), diameter, diameter, 90.0f, 90.0f);
	ege_fillpie((float)(button->x), (float)(button->y), diameter, diameter, 180.0f, 90.0f);
	ege_fillpie((float)(button->x + dx), (float)(button->y), diameter, diameter, 270.0f, 90.0f);
	//��䰴ť����
	setfillcolor(EGEARGB(0xff, 0x40, 0x40, 0x40));
	setbkmode(TRANSPARENT);
	setcolor(WHITE);
	setfont(24, 0, "΢���ź�");
	outtextxy(button->x + button->width / 2 - textwidth(button->label) / 2, button->y + button->height / 2 - textheight(button->label) / 2, button->label);

}
bool click(const RoundRectButton* button, int x, int y)
{
	bool inside = false;

	// ���ڰ�Χ������
	if ((x >= button->x) && (y >= button->y)
		&& (x < button->x + button->width)
		&& (y < button->y + button->height)
		) {

		float centerx = button->x + button->width / 2.0f;
		float centery = button->y + button->height / 2.0f;
		float dx = (float)fabs(x - centerx);
		float dy = (float)fabs(y - centery);
		float interWidth = button->width / 2.0f - button->radius;
		float interHeight = button->height / 2.0f - button->radius;

		// �㲻��Բ�ǿհ״� ()
		if (!((dx > interWidth)
			&& (dy > interHeight)
			&& ((dx - interWidth) * (dx - interWidth) + (dy - interHeight) * (dy - interHeight)
					> button->radius * button->radius)
			)
			) {
			inside = true;
		}
	}

	return inside;
}
void puttext(int x,int y,int size ,const char * text)
{
	setfillcolor(EGEARGB(0xff, 0x40, 0x40, 0x40));
	setbkmode(TRANSPARENT);
	setcolor(BLACK);
	setfont(size, 0, "΢���ź�");
	xyprintf(x, y , "%s",text);
}
void initEditBox(sys_edit* editBox, int x, int y, int width, int height)
{
	editBox->create(false);
	editBox->size(width, height + 8);
	editBox->setbgcolor(WHITE);
	editBox->setfont(24, 0, "����");
	editBox->move(x, y);
	editBox->visable(true);
	editBox->setfocus();
}
void mainWindow()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);// ��ʼ��ͼ�δ���

	setbkcolor(EGERGB(0xFE, 0xFA, 0xE0));
	setcaption("ѧ����Ϣ����ϵͳ");
	int button1_x, button1_y;  // ��ѧ����Ϣ¼�롱��ť����
	int button2_x, button2_y;  // ��ѧ����Ϣ������ť����z
	// ���㰴ť����
	button1_x = WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2;
	button1_y = WINDOW_HEIGHT / 2 - BUTTON_HEIGHT - 40;
	button2_x = WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2;
	button2_y = WINDOW_HEIGHT / 2 + 40;

	//��ť�ṹ��
	BUTTON button1 = {
		button1_x,button1_y,
		BUTTON_WIDTH,BUTTON_HEIGHT,
		CORNERADIUS,
		R,G,B,
		28,
		"ѧ����Ϣ��ʼ��"
	};

	BUTTON button2 = {
		button2_x,button2_y,
		BUTTON_WIDTH,BUTTON_HEIGHT,
		CORNERADIUS,
		R,G,B,
		28,
		"��Ϣ������鿴"
	};
	drawButton(&button1);
	drawButton(&button2);
	int clickbutton1 = 0;
	int clickbutton2 = 0;
	//����˵��
	puttext(100, 100, 35, "��ӭʹ��ѧ������ϵͳ");
	puttext(100, 135, 35, "��һ��¼��ɼ�����һ����ť����ӡ����򡢲��������������");
	puttext(100, 170, 35, "��Ҫ����¼����Ϣʱ������һ����ť��ʼ����Ϣ");
	puttext(100, 205, 35, "�����Ķ��ļ����е�README���˽�ʹ����֪");
	//��δ�����һ������¼����������ѭ��������᲻�ϻ�ȡ�����Ϣ����������¼������ͽ�����Ӧ�Ĳ����������߼����£�

	/*�������������ʱ�������жϡ�
		����������ǰ���״̬��ͨ������click()��������������λ���Ƿ��ڰ�ť1��ť2�ϣ�������Ӧ�Ĳ���ֵ����clickbutton1��clickbutton2��
		�����������̧��״̬������clickbutton1��clickbutton2��ֵ�����жϣ�
		���clickbutton1Ϊ�棬�������Ļ���ݲ���ʾѧ��¼�봰�ڡ�
		���clickbutton2Ϊ�棬�������Ļ���ݲ���ʾѧ�������ڡ�
		����������������������㣬�������һ��ѭ����
		���ͨ��delay()������ʱ10���룬�Ա������Ƶ����ѭ����*/

	while (1) {
		// ��ȡ�����Ϣ
		mouse_msg msg = getmouse();

		// �ж��������Ƿ���
		if (msg.is_left()) {
			// �ж��������Ƿ���
			if (msg.is_down()) {
				// ������İ�ť
				clickbutton1 = click(&button1, msg.x, msg.y);
				clickbutton2 = click(&button2, msg.x, msg.y);
			}
			// ������̧��
			else {
				// �����ť1�����
				if (clickbutton1) {
					// �����Ļ����
					cleardevice();
					// ��ʾѧ��¼�봰��
					studentEntryWindow();
				}
				// �����ť2�����
				else if (clickbutton2) {
					// �����Ļ����
					cleardevice();
					// ��ʾѧ��������
					studentManagementWindow();
				}
				// û�а�ť�����������ѭ��
				else {
					continue;
				}
			}
		}
		// ��ʱ10���룬�������Ƶ����ѭ��
		delay(10);
	}

	closegraph();
}
void studentEntryWindow()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  // ��ʼ��ͼ�δ���

	setbkcolor(EGERGB(0xFE,0xFA,0xE0));

	setcaption("ѧ����Ϣ��ʼ��");

	int BackButton_x, BackButton_y; //��¼�����ķ��ذ�ť���ꡰ
	int AddInfoButton_x, AddInfoButton_y;//��¼�����������Ϣ�İ�ť"

	int complete1button_x, complete1button_y; //"�����Ŀ������ɰ�ť"

	int back_x = 80;
	int back_y = 80;
	BUTTON buttonarray[6];
	const int buffSize = 100;//���뻺����
	char strBuffer[100] = "";//���뻺����
	sys_edit editBox;//��Ŀ����
	student stu[50]{}; //ѧ�����������50��
	int count = 0;//¼���ѧ������
	int i, j;

	BUTTON back = {
		back_x,back_y,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"����"
	}; buttonarray[0] = { back }; //���ذ�ť

	BUTTON confirm = {
		900,back_y,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"����ѧ����"
	}; buttonarray[1] = { confirm }; //ȷ����ť

	BUTTON add_student = {
		back_x, back_y + 400,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"���ѧ��"
	}; buttonarray[2] = { add_student }; //���ѧ����ť
	BUTTON set_sub = {
		back_x,back_y + 200,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"���ÿ�Ŀ����"
	}; buttonarray[3] = { set_sub };
	BUTTON check = 
	{
		back_x, back_y + 600,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"Ԥ��"
	}; buttonarray[4] = { check };

	puttext(back_x + 100, back_y + 30, 25, "�����ť�����Ŀ���������Ϊ5�����밴˳��¼����������Ŀ����ѧ�������Ԥ��");
	puttext(back_x + 100, back_y + 60, 25, "¼������������ǰ���ఴť���ɴ������˳��ý�����Ҫ����¼��");

	for (i = 0; i < 6; i++)						//�������а�ť
	{
		drawButton(&buttonarray[i]);
	}
	/*initEditBox(&editBox, back_x + 160 + textwidth("�������Ŀ���������Ϊ5����"), back_y + BACK_WIDTH / 4, 200, 30);*/
	;
	//��һ��֡ѭ����ȷ��¼���Ŀ����
	while (1) {
		int flag = 0;
		int is_confirm = 0;
		mouse_msg msg = getmouse();
		//�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣�
		if (msg.is_left()) {
			if (msg.is_down()) {
				//������İ�ť
				if (click(&confirm, msg.x, msg.y))
				{
					//��һ������
					{
						inputbox_getline("�������Ŀ����", "�������Ŀ����\nע�⣺1.����������\n2.����Ŀ��Ϊ5\n3.���س���������",
							strBuffer, buffSize);
						int res = sscanf(strBuffer, "%d", &SUB_NUM);
						if (res != 1 || SUB_NUM > 5 || SUB_NUM <= 0)
						{
							//������ʾ��Ϣ
							setfillcolor(EGEARGB(0xff, 0x40, 0x40, 0x40));
							setbkmode(TRANSPARENT);
							setcolor(BLACK);
							setfont(28, 0, "΢���ź�");
							xyprintf(WINDOW_WIDTH / 2, 600, "�������");
							Sleep(100);
							cleardevice();
							draw_entry(back_x, back_y, buttonarray);
							flag = 1;
							continue;

						}
						else
						{
							cleardevice();
							draw_entry(back_x, back_y, buttonarray);
						

							//������ʾ��Ϣ
							setfillcolor(EGEARGB(0xff, 0x40, 0x40, 0x40));
							setbkmode(TRANSPARENT);
							setcolor(BLACK);
							setfont(28, 0, "΢���ź�");
							xyprintf(800, back_y - 40, "������%d��ѧ��", SUB_NUM);
							break;
						}
					}
				}
				else if (click(&back, msg.x, msg.y))
				{
					editBox.destory();
					cleardevice();
					mainWindow();
					break;
				}
			}
		}
		delay(10);
	}
		//��⵽confirm��ť����ͱ��Ϊ�������
		
 //���ÿ�Ŀ
	while (1) {
		mouse_msg msg = getmouse();
		//�ж�������������������ȷ��λ�ã�̧��Ϊִ��ʱ�̣�
		if (msg.is_left()) {
			if (msg.is_down()) {
				//������İ�ť
				//�Ƿ񷵻�
			//���ÿ�Ŀ
				if (click(&set_sub, msg.x, msg.y))
				{
					for (i = 0; i < SUB_NUM; i++)
					{
						cleardevice();//�����ػ�
						draw_entry(back_x, back_y, buttonarray);

						/*setfillcolor(EGEARGB(0xff, 0x40, 0x40, 0x40));
						setbkmode(TRANSPARENT);*/
						setcolor(BLACK);
						setfont(28, 0, "΢���ź�");
						xyprintf(WINDOW_WIDTH / 2, 600, "�������%d��ѧ��", i + 1);
						xyprintf(WINDOW_WIDTH / 2, 650, "������Ӣ������");
						xyprintf(WINDOW_WIDTH / 2, 700, "���س�����");

						inputbox_getline("�������Ŀ����", "�������Ŀ����\nע�⣺1.������Ӣ��\n2.�²����ʾ��������ڼ�����Ŀ\n3.�ַ����Ȳ�����15",
							subname[i], 16);

						cleardevice();//�����ػ�
						delay(200);
					}
					draw_entry(back_x, back_y, buttonarray);
					break;
				}
				//����
				else if (click(&back, msg.x, msg.y))
				{
					cleardevice();
					mainWindow();
					break;
				}
			}
		}
	}
//¼��ѧ����鿴ѧ��
	while (1)
	{
		mouse_msg msg = getmouse();
		//�ж�������������������ȷ��λ�ã�
		if (msg.is_left())
		{
			if (msg.is_down())
			{
				//���ѧ��
				if (click(&add_student, msg.x, msg.y))
				{
					count = addstudent(stu, count, back_x, back_y, buttonarray);
					cleardevice();
					draw_entry(back_x, back_y, buttonarray);
					STU_NUM = count;
					calculate_score(stu);
					write_file(stu);

				}
				//Ԥ��
				else if (click(&check, msg.x, msg.y))
				{
					setcolor(RED);
					setfont(35, 0, "΢���ź�");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "��򿪿���̨�鿴");
					printstudent(stu,subname);
				}
				//�Ƿ񷵻�
				else if (click(&back, msg.x, msg.y))
				{
					cleardevice();
					mainWindow();
					break;
				}
			}
		}
	}
}
void draw_entry(int back_x, int back_y, BUTTON buttonarray[])
{
  // ��ʼ��ͼ�δ���
	int i;
	setbkcolor(EGERGB(0xFE, 0xFA, 0xE0));
	puttext(back_x + 100, back_y + 30, 25, "�����ť�����Ŀ���������Ϊ5�����밴˳��¼����������Ŀ����ѧ�������Ԥ��");
	puttext(back_x + 100, back_y + 50, 25, "���Ѿ�������ˣ������~");
	puttext(back_x + 100, back_y + 70, 25, "��������Ϣ������棬�ɼ���Ӵ�С�Զ��ź�");
	puttext(back_x + 100, back_y + 100, 25, "���ִ�Сд");
	for (i = 0; i < 8; i++)						//�������а�ť
	{
		drawButton(&buttonarray[i]);

	}
	setfillcolor(EGEARGB(0xff, 0x40, 0x40, 0x40));//����
	setbkmode(TRANSPARENT);
	setcolor(BLACK);
	setfont(28, 0, "΢���ź�");
}
// �������ƣ�addstudent
// ���ܣ����ѧ����Ϣ
// ������
// - stu��ѧ����Ϣ����
// - count����ǰ����ӵ�ѧ������
// - back_x�����ذ�ť��x����
// - back_y�����ذ�ť��y����
// - buttonarray����ť����
// ����ֵ�����º��ѧ������
int addstudent(student stu[], int count, int back_x, int back_y, BUTTON buttonarray[])
{
	int i;
	int add_flag = 0; // ��ӱ�־�����ڼ�¼�Ƿ�ɹ����ѧ����Ϣ
	char num[10]; // ѧ��������ַ�����

	// ¼��ѧ��ѧ��
	setcolor(BLACK);
	setfont(28, 0, "΢���ź�");
	xyprintf(WINDOW_WIDTH / 2, 600, "�������%d��ѧ��", count + 1);
	xyprintf(WINDOW_WIDTH / 2, 650, "������ѧ��");
	xyprintf(WINDOW_WIDTH / 2, 700, "���س�����");

	// ��ȡѧ��ѧ������
	inputbox_getline("������ѧ����Ϣ", "������ѧ��ѧ��\nע�⣺1.���������ֻ�Ӣ��\n2.���λ��Ϊ10������ᱻ����",
		stu[count].number, 11);

	// �����ػ�
	cleardevice();
	draw_entry(back_x, back_y, buttonarray);


	// ¼��ѧ������
	setcolor(BLACK);
	setfont(28, 0, "΢���ź�");
	xyprintf(WINDOW_WIDTH / 2, 600, "�������%d��ѧ��", count + 1);
	xyprintf(WINDOW_WIDTH / 2, 650, "����������");
	xyprintf(WINDOW_WIDTH / 2, 700, "���س�����");


	// ��ȡѧ����������
	inputbox_getline("������ѧ����Ϣ", "������ѧ������\nע�⣺1.������Ӣ��\n2.�����Ϊ20���ַ�������ᱻ����",
		stu[count].name, 21);

	cleardevice();
	draw_entry(back_x, back_y, buttonarray);

	// ��˳��¼��ѧ���ɼ�
	for (i = 0; i < SUB_NUM; i++)
	{
		cleardevice();
		draw_entry(back_x, back_y, buttonarray);
		setcolor(BLACK);
		setfont(24, 0, "΢���ź�");
		xyprintf(WINDOW_WIDTH / 2, 600, "�������%d��ѧ��%s�ĳɼ�", count + 1, subname[i]);
		xyprintf(WINDOW_WIDTH / 2, 650, "������ɼ���0-100��");
		xyprintf(WINDOW_WIDTH / 2, 700, "���س�����");

		// ��ȡѧ���ɼ�����
		inputbox_getline("������ѧ����Ϣ", "������ɼ�\nע�⣺1.��ΧΪ0-100����Ϊ����\n2.�²����ʾ���������ĸ���Ŀ",
			num, sizeof(stu[count].name) / sizeof(char));
		int res = sscanf(num, "%d", &stu[count].grade.subject[i]); // ���͸�ʽ¼��


		if (res != 1 || stu[count].grade.subject[i] < 0 || stu[count].grade.subject[i] > MAX_SCORE)
		{
			setcolor(BLACK);
			setfont(24, 0, "΢���ź�");
			xyprintf(WINDOW_WIDTH / 2, 550, "�ɼ����뷶Χ����");
			i--;
			Sleep(200);
			cleardevice(); // ����
			draw_entry(back_x, back_y, buttonarray);
			continue;
		}

		delay(200);
	}

	count++; // ����ѧ������
	return count;
}
// ������: delstudent
// ����: ɾ��ѧ����Ϣ
// ����:
//   - stu: ѧ����Ϣ����
//   - count: ѧ����Ϣ����Ĵ�С
//   - back_x, back_y: ���ذ�ť������
//   - buttonarray: ��ť����
// ����ֵ: ɾ����ѧ����Ϣ����Ĵ�С
int delstudent(student stu[], int count, int back_x, int back_y, BUTTON buttonarray[]) {
	int pos = -1;
	char input_number[11];
	int i;

	xyprintf(WINDOW_WIDTH / 2, 650, "ѧ��Ӧ��ȫƥ�䣬����ģ������,һ��ֻ��ɾ��һ��");
	xyprintf(WINDOW_WIDTH / 2, 700, "���س�����");

	inputbox_getline("������ѧ��ѧ��", "������ѧ��ѧ��\nע�⣺1.���������ֻ�Ӣ��\n2.���λ��Ϊ10,����ᱻ����\n3.һ��ֻ��ɾ��һ��ѧ��\n4.�뾫ȷ����ѧ�ţ����س�����",
		input_number, 11);


	pos = ranksearch(stu, count, input_number);
	if (pos != -1) {
		// �������Ԫ��������ǰ�ƶ�
		for (i = pos + 1; i < count; i++) {
			stu[i - 1] = stu[i];
		}
		count--; // ����ѧ����Ϣ����Ĵ�С

		cleardevice();
		draw_entry(back_x, back_y, buttonarray);
		setcolor(BLACK);
		setfont(24, 0, "΢���ź�");
		xyprintf(WINDOW_WIDTH / 2, 600, "ɾ���ɹ���");
		Sleep(300); // �ӳ�һ��ʱ�������ػ�
		cleardevice();
		draw_entry(back_x, back_y, buttonarray);
	}
	else {
		setcolor(BLACK);
		setfont(24, 0, "΢���ź�");
		xyprintf(WINDOW_WIDTH / 2, 600, "û���ҵ���ѧ����");
		Sleep(300); // �ӳ�һ��ʱ�������ػ�
		cleardevice();
		draw_entry(back_x, back_y, buttonarray);
	}

	return count;
}

//���ո�ʽ��ӡ�ɼ�
void printstudent(student stu[], char subname[MAX_EXAM][16])
{
	int i,j;
	printf("The Number of the student is %d\n", STU_NUM); // ��ӡѧ������

	printf("%2s%11s%25s", "  ", "StudentID", "Name"); // ��ӡ��ͷ

	for (i = 0; i < SUB_NUM; i++)
	{
		printf("%15s", subname[i]); // ��ӡ��Ŀ����
	}

	printf("%5s", "SUM"); // ��ӡ�ܷ��б���
	printf("\n");

	// �������
	for (i = 0; i < STU_NUM; i++)
	{
		printf("%2d", i + 1); // ������
		printf("%11s%25s", stu[i].number, stu[i].name); // ��ӡѧ��ѧ�ź�����

		for (j = 0; j < SUB_NUM; j++)
		{
			printf("%15d", stu[i].grade.subject[j]); // ��ӡѧ������Ŀ����
		}

		printf("%5d", stu[i].grade.sum); // ��ӡѧ���ܷ�
		printf("\n");
	}
}
//���ܷ�
void calculate_score(student stu[])
{
	//���ܷ�
	int i, j;
	int sum = 0; 
	for (i = 0; i < STU_NUM; i++)
	{
		sum = 0;
		for (j = 0; j < SUB_NUM; j++)
		{
			sum += stu[i].grade.subject[j];
		}
		stu[i].grade.sum = sum;
	}
}
//����Ϣд���ļ�
void write_file(student stu[])
{
	FILE* fp;
	int i, j;
	if ((fp = fopen("score.txt", "w")) == NULL)
	{
		printf("FAIL");
	}
	fprintf(fp, "%d\t%d\n", STU_NUM, SUB_NUM);
	for (i = 0; i < STU_NUM; i++)
	{
		fprintf(fp, "%11s%25s", stu[i].number, stu[i].name);
		for (j = 0; j < SUB_NUM; j++)
		{
			fprintf(fp, "%15d", stu[i].grade.subject[j]);
		}
		fprintf(fp, "%5d", stu[i].grade.sum);//�ܷ�
		fprintf(fp, "\n");
	}
	for (i = 0; i < SUB_NUM; i++)
	{
		fprintf(fp, "%15s", subname[i]);
	}
	fclose(fp);
}
//����Ϣ���ļ�����
void read_file(student stu[], int* STU_NUM, int* SUB_NUM)
{
	FILE* fp;
	int i, j;
	if ((fp = fopen("score.txt", "r")) == NULL)
	{
		puttext(180, 140, 28, "open fail");
	}
	fscanf(fp, "%d\t%d\n", STU_NUM, SUB_NUM);
	for (i = 0; i < *STU_NUM; i++)
	{
		fscanf(fp, "%11s%25s", stu[i].number, stu[i].name);
		for (j = 0; j < *SUB_NUM; j++)
		{
			fscanf(fp, "%15d", &stu[i].grade.subject[j]);
		}
		fscanf(fp, "%5d", &stu[i].grade.sum);//�ܷ�
	}
	for (i = 0; i < *SUB_NUM; i++)
	{
		fscanf(fp, "%15s", subname[i]);
	}
	fclose(fp);
}
// ��������ѧ���ṹ��ĺ���
void swap(student* a, student* b) {
	student temp = *a;
	*a = *b;
	*b = temp;
}
// ��������ķ�������
int partition(student arr[], int low, int high) {
	int pivot = arr[high].grade.sum; // ѡȡ���һ��Ԫ����Ϊ��ŦԪ���ܳɼ���
	int i = (low - 1);
	int j;

	for (j = low; j <= high - 1; j++) {
		if (arr[j].grade.sum >= pivot) { // �����ǰԪ�ص��ܳɼ����ڵ�����ŦԪ�����佻����ǰ�벿��
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]); // ����ŦԪ���õ���ȷ��λ��
	return (i + 1); // ������ŦԪ������
}
// ���������������
void quickSort(student arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high); // ��ȡ��ŦԪ������

		quickSort(arr, low, pi - 1);  // ����ŦԪ�������еݹ�����
		quickSort(arr, pi + 1, high); // ����ŦԪ���Ҳ���еݹ�����
	}
}
//ģ����������
int vaguesearch(const char* key, const char* str)
{
	/*��δ���ʵ����ģ�������ĺ���������������������һ���ǹؼ��� key����һ���Ǵ��������ַ��� str��
		���������ַ��� str ��Ѱ����ؼ��� key ƥ����Ӵ�����ͨ������Ƚ��Ӵ��ķ�ʽ�������������ȣ�����ȡ�ؼ��ʺʹ������ַ����ĳ��ȡ�
		Ȼ����ѭ�������������ַ����е�ÿ�����ܵ��Ӵ�������ַ���ؼ��ʽ��бȽϡ�����ҵ���ƥ����Ӵ����ͷ���1��ʾ�ҵ��ˣ����򷵻�0��ʾδ�ҵ���*/
	int i, j;
	int keyLen = strlen(key); // ��ȡ�ؼ��ʵĳ���
	int strLen = strlen(str); // ��ȡ�������ַ����ĳ���
	// ���αȽ��Ӵ�
	for (i = 0; i <= strLen - keyLen; i++) // ѭ�������������ַ����е�ÿ�����ܵ��Ӵ�
	{
		int match = 1; // ƥ���־�������ж��Ƿ��ҵ��ؼ���

		// �Ƚ�str��key��ÿ���ַ�
		for (j = 0; j < keyLen; j++) // ѭ�������ؼ����е�ÿ���ַ�
		{
			if (str[i + j] != key[j]) // �Ƚ϶�Ӧλ�õ��ַ��Ƿ����
			{
				match = 0; // ����в�ƥ����ַ�����ƥ���־��Ϊ0
				break; // �����ڲ�ѭ��
			}
		}

		if (match == 1) // ���ƥ���־Ϊ1����ʾ�ҵ��˹ؼ���
		{
			return 1; // �ҵ���
		}
	}

	return 0; // δ�ҵ�
}
//�����������
int ranksearch(student stu[], int count, const char* input_number) {
	// ʹ�������������ѧ��ƥ���ѧ��
	int max_attempts = count * 5; // ����Դ���Ϊѧ���������屶
	int attempts = 0; // ���Դ���
	int pos = -1; // �ҵ���λ��

	while (attempts < max_attempts && pos == -1) {
		int random_index = rand() % count; // �����������
		if (strcmp(stu[random_index].number, input_number) == 0) {
			pos = random_index;
		}
		attempts++;
	}

	return pos;
}
//�ж��Ƿ��й���ԱȨ��
bool IsProcessRunAsAdmin()
{
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;
	BOOL b = AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&AdministratorsGroup);
	if (b)
	{
		CheckTokenMembership(NULL, AdministratorsGroup, &b);
		FreeSid(AdministratorsGroup);
	}
	return b == TRUE;
}

//��С������������
int main()
{	
	int n = 0;
	int res = IsProcessRunAsAdmin();
	if (res == 0)
	{
		printf("�����Էǹ���ԱȨ������\n���Ҽ���ݷ�ʽ��ѡ�����ԣ�ѡ������ԣ�ѡ��\'�Թ���ԱȨ�����У�����������Ķ��ļ����µ�ʹ����֪.doc\'\n,�����Ҫǿ�����У����ܻ����Bug��������3.");
		scanf("%d", &n);
		if (n != 3)
		{
			system("pause");
			return 0;
		}
	}
	mciSendString("open bgm.mp3 alias a ", 0, 0, 0);//��������
	mciSendString("play a", 0, 0, 0);
	mainWindow();
	return 0;
}