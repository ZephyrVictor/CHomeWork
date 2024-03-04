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
#include<mmsystem.h>//包含多媒体设备接口头文件
#include <cstdlib> // 包含rand函数的头文件
#pragma comment (lib,"winmm.lib")//加载静态库




// 全局变量

int STU_NUM = 0;//用户输入的学生数量
int SUB_NUM = 0;//学科数量
char subname[MAX_EXAM][16];//各个学科的名字
void studentEntryWindow();//学生数据录入窗口
void studentManagementWindow();//管理窗口
void mainWindow();//主窗口
void drawButton(const RoundRectButton* button);//创建按钮
bool click(const RoundRectButton* button, int x, int y);//判定按钮点击
void puttext(int x, int y, int size, const char* text);//输出文本
void initEditBox(sys_edit* editBox, int x, int y, int width, int height);//初始化编辑框
void draw_entry(int back_x,int back_y,BUTTON buttonarray[]);//绘制界面
int addstudent(student stu[],int count,int back_x,int back_y,BUTTON buttonarray[]);//添加学生
int delstudent(student stu[], int count, int back_x, int back_y, BUTTON buttonarray[]);//删除学生
void printstudent(student stu[], char subname[MAX_EXAM][16]);//输出成绩
void calculate_score(student stu[]);//计算学生总分
void write_file(student stu[]);//写入文件
void read_file(student stu[], int* STU_NUM, int* SUB_NUM);//读入文件
void swap(student* a, student* b);//快速排序相关，交换两数位置
int partition(student arr[], int low, int high);//快速排序相关，确定基准位置
void quickSort(student arr[], int low, int high);//快速排序主体（因为要涉及很多次排序，//所以使用相对效率较高的快速排序进行排序，减少资源占用）
int vaguesearch(const char* key, const char* str);//模糊搜索
int ranksearch(student stu[], int count, const char* input_number);//随机搜索
bool IsProcessRunAsAdmin();//检查是否是管理员权限






void studentManagementWindow()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);// 初始化图形窗口

	setbkcolor(EGERGB(0xFE, 0xFA, 0xE0));

	setcaption("信息管理与查看");



	int BackButton_x, BackButton_y; //”管理界面的返回按钮坐标“
	int AddInfoButton_x, AddInfoButton_y;//“管理界面的添加信息的按钮"
	int RemoveInfoButton_x, RemoveInfoButton_y;//"管理的删除信息的按钮"

	int complete1button_x, complete1button_y; //"输入科目数量完成按钮"

	int back_x = 80;
	int back_y = 80;
	BUTTON buttonarray[8];
	const int buffSize = 100;//输入缓冲区
	char strBuffer[100] = "";//输入缓冲区
	sys_edit editBox;//科目数量
	student stu[50]{}; //学生数量（最大50）
	read_file(stu, &STU_NUM, &SUB_NUM);
	int count = STU_NUM;//学生数量，便于后续函数操作
	quickSort(stu, 0, count - 1);//对学生排序
	int i, j;

	

	BUTTON back = {
		back_x,back_y,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"返回"
	}; buttonarray[0] = { back }; //返回按钮
	BUTTON number_search = {
		800,back_y,
		130,80,
		CORNERADIUS,
		R,G,B,
		28,
		"按学号模糊查找"
	}; buttonarray[1] = { number_search }; //学号搜索按钮
	BUTTON add_student = {
		back_x, back_y + 200,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"添加学生成绩"
	}; buttonarray[2] = { add_student }; //添加学生按钮
	BUTTON del_student = {
		back_x,back_y + 400,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"删除学生"
	}; buttonarray[3] = { del_student };//删除学生按钮
	BUTTON check ={
		back_x, back_y + 600,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"查看排名"
	}; buttonarray[4] = { check };//查看排名按钮
	BUTTON name_search = {
		800, back_y + 120,
		130,80,
		CORNERADIUS,
		R,G,B,
		28,
		"按姓名模糊查找"
	}; buttonarray[5] = { name_search };//姓名搜索按钮
	BUTTON acc_name_search = {
		800,2 * back_y + 160,
		130,80,
		CORNERADIUS,
		R,G,B,
		28,
		"按姓名精确查找"
	}; buttonarray[6] = { acc_name_search };//姓名搜索按钮
	BUTTON acc_number_search = {
		800,3 * back_y + 200,
		130,80,
		CORNERADIUS,
		R,G,B,
		28,
		"按学号精确查找"
	}; buttonarray[7] = { acc_number_search };//学号搜索按钮

	
	puttext(back_x + 100, back_y + 30, 25, "进入该界面后，成绩自动排序为降序");

	for (i = 0; i < 8; i++)						//绘制所有按钮
	{
		drawButton(&buttonarray[i]);
	}

	// 无限循环，用于监听鼠标事件
	while (1)
	{
		// 获取鼠标消息
		mouse_msg msg = getmouse();

		// 判断是否左键点击事件
		if (msg.is_left())
		{
			// 判断是否鼠标按下
			if (msg.is_down())
			{
				// 点击了添加按钮
				if (click(&add_student, msg.x, msg.y))
				{
					// 调用添加学生函数，返回更新后的学生数量
					count = addstudent(stu, count, back_x, back_y, buttonarray);

					// 清空绘图设备
					cleardevice();

					// 重新绘制界面
					draw_entry(back_x, back_y, buttonarray);

					// 更新全局学生数量
					STU_NUM = count;

					// 计算学生分数
					calculate_score(stu);

					// 将学生信息写入文件
					write_file(stu);

					// 更新全局学生数量
					STU_NUM = count;

					// 对学生信息进行快速排序
					quickSort(stu, 0, count - 1);

					// 将学生信息写入文件
					write_file(stu);
				}
				// 点击了删除按钮
				else if (click(&del_student, msg.x, msg.y))
				{
					// 调用删除学生函数，返回更新后的学生数量
					count = delstudent(stu, count, back_x, back_y, buttonarray);

					// 更新全局学生数量
					STU_NUM = count;

					// 对学生信息进行快速排序
					quickSort(stu, 0, count - 1);

					// 将学生信息写入文件
					write_file(stu);
				}
				// 点击了查看按钮
				else if (click(&check, msg.x, msg.y))
				{
					// 输入文字提示
					setcolor(RED);
					setfont(35, 0, "微软雅黑");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "请打开控制台查看");

					// 打印学生信息到控制台
					printstudent(stu, subname);
				}
				// 点击了按学号搜索按钮
				else if (click(&number_search, msg.x, msg.y))
				{
					char input[21];

					// 弹出输入框，获取要搜索的学号
					inputbox_getline("请输入要搜索的学号", "请输入学生学号\n注意：1.请输入数字或英文\n2.最大位数为10，多余会被忽略\n3.该搜索为模糊搜索，搜索结果无先后顺序\n4.查询序号为排行榜序号",
						input, 11);

					// 输入文字提示
					setcolor(RED);
					setfont(35, 0, "微软雅黑");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "请打开控制台查看");

					int found = 0;
					printf("\nresults:\n");

					// 打印表头
					printf("%2s%11s%25s", "  ", "StudentID", "Name");
					for (i = 0; i < SUB_NUM; i++)
					{
						printf("%15s", subname[i]);
					}
					printf("%5s", "SUM");
					printf("\n");

					// 遍历学生信息，进行模糊搜索
					for (i = 0; i < count; i++)
					{
						if (vaguesearch(input, stu[i].number) == 1)
						{
							found = 1;
							// 输出学生信息
							printf("%2d", i + 1);//输出序号
							printf("%11s%25s", stu[i].number, stu[i].name);//姓名
							for (int j = 0; j < SUB_NUM; j++)
							{
								printf("%15d", stu[i].grade.subject[j]);//科目分数
							}
							printf("%5d", stu[i].grade.sum);//总分
							printf("\n");
						}
					}

					// 如果没有找到匹配的学生信息
					if (found == 0)
					{
						printf("No matched student!\n");
					}
				}
				// 点击了按姓名搜索按钮
				else if (click(&name_search, msg.x, msg.y))
				{
					char input[21];

					// 弹出输入框，获取要搜索的姓名
					inputbox_getline("请输入要搜索的姓名", "请输入学生姓名\n注意：1.请输入数字或英文\n2.最大位数为20，多余会被忽略\n3.该搜索为模糊搜索,搜索结果无先后顺序\n4.查询序号为排行榜序号",
						input, 21);

					// 输入文字提示
					setcolor(RED);
					setfont(35, 0, "微软雅黑");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "请打开控制台查看");

					int found = 0;
					printf("\nresults:\n");

					// 打印表头
					printf("%2s%11s%25s", "  ", "StudentID", "Name");
					for (i = 0; i < SUB_NUM; i++)
					{
						printf("%15s", subname[i]);
					}
					printf("%5s", "SUM");
					printf("\n");

					// 遍历学生信息，进行模糊搜索
					for (i = 0; i < count; i++)
					{
						if (vaguesearch(input, stu[i].name) == 1)
						{
							found = 1;
							// 输出学生信息
							printf("%2d", i + 1);//输出序号
							printf("%11s%25s", stu[i].number, stu[i].name);//姓名
							for (int j = 0; j < SUB_NUM; j++)
							{
								printf("%15d", stu[i].grade.subject[j]);//科目分数
							}
							printf("%5d", stu[i].grade.sum);//总分
							printf("\n");
						}
					}

					// 如果没有找到匹配的学生信息
					if (found == 0)
					{
						printf("No matched student!\n");
					}
				}
				// 点击了返回按钮
				else if (click(&back, msg.x, msg.y))
				{
					// 清空绘图设备
					cleardevice();

					// 返回主窗口
					mainWindow();

					// 跳出循环
					break;
				}
				// 点击了按姓名精准搜索按钮
				else if (click(&acc_name_search, msg.x, msg.y))
				{
					char input[21];
					int isfind = 0;
					int pos = -1;

					// 弹出输入框，获取要搜索的姓名
					inputbox_getline("请输入要搜索的姓名", "请输入学生姓名\n注意：1.请输入数字或英文\n2.最大位数为20，多余会被忽略\n3.该搜索为精确搜索\n4.查询序号为排行榜序号",
						input, 21);

					// 输入文字提示
					setcolor(RED);
					setfont(35, 0, "微软雅黑");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "请打开控制台查看");

					int found = 0;
					printf("\nresults:\n");

					// 打印表头
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
						if (strcmp(stu[i].name, input) == 0) // 完全相等 这是精确查找
						{
							pos = i;
							isfind = 1;
						}
						if (isfind)
						{
							// 输出学生信息
							printf("%2d", pos + 1);//输出序号
							printf("%11s%25s", stu[pos].number, stu[pos].name);//姓名
							for (int j = 0; j < SUB_NUM; j++)
							{
								printf("%15d", stu[pos].grade.subject[j]);//科目分数
							}
							printf("%5d", stu[pos].grade.sum);//总分
							printf("\n");
						}
					}
					// 如果没有找到匹配的学生信息
					if (pos == -1)
					{
						printf("No matched student!\n");
					}
				}
				// 点击了按学号精准搜索按钮
				else if (click(&acc_number_search, msg.x, msg.y))
				{
					char input[21];
					int isfind = 0;
					int pos = -1;

					// 弹出输入框，获取要搜索的姓名
					inputbox_getline("请输入要搜索的姓名", "请输入学生学号\n注意：1.请输入数字或英文\n2.最大位数为20，多余会被忽略\n3.该搜索为精确搜索\n4.查询序号为排行榜序号",
						input, 21);

					// 输入文字提示
					setcolor(RED);
					setfont(35, 0, "微软雅黑");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "请打开控制台查看");

					int found = 0;
					printf("\nresults:\n");

					// 打印表头
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
						if (strcmp(stu[i].number, input) == 0) // 完全相等 这是精确查找
						{
							pos = i;
							isfind = 1;
						}
						if (isfind)
						{
							// 输出学生信息
							printf("%2d", pos + 1);//输出序号
							printf("%11s%25s", stu[pos].number, stu[pos].name);//姓名
							for (int j = 0; j < SUB_NUM; j++)
							{
								printf("%15d", stu[pos].grade.subject[j]);//科目分数
							}
							printf("%5d", stu[pos].grade.sum);//总分
							printf("\n");
						}
					}
					// 如果没有找到匹配的学生信息
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
	setfillcolor(EGEARGB(0xFF, R, G, B)); //填充颜色
	//绘制矩形
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

	//确定圆角半径和坐标
	float diameter = 2 * button->radius;
	float dx = button->width - diameter;
	float dy = button->height - diameter;

	//绘制四个圆角
	ege_fillpie((float)(button->x + dx), (float)(button->y + dy), diameter, diameter, 0.0f, 90.0f);
	ege_fillpie((float)(button->x), (float)(button->y + dy), diameter, diameter, 90.0f, 90.0f);
	ege_fillpie((float)(button->x), (float)(button->y), diameter, diameter, 180.0f, 90.0f);
	ege_fillpie((float)(button->x + dx), (float)(button->y), diameter, diameter, 270.0f, 90.0f);
	//填充按钮文字
	setfillcolor(EGEARGB(0xff, 0x40, 0x40, 0x40));
	setbkmode(TRANSPARENT);
	setcolor(WHITE);
	setfont(24, 0, "微软雅黑");
	outtextxy(button->x + button->width / 2 - textwidth(button->label) / 2, button->y + button->height / 2 - textheight(button->label) / 2, button->label);

}
bool click(const RoundRectButton* button, int x, int y)
{
	bool inside = false;

	// 点在包围矩形内
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

		// 点不在圆角空白处 ()
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
	setfont(size, 0, "微软雅黑");
	xyprintf(x, y , "%s",text);
}
void initEditBox(sys_edit* editBox, int x, int y, int width, int height)
{
	editBox->create(false);
	editBox->size(width, height + 8);
	editBox->setbgcolor(WHITE);
	editBox->setfont(24, 0, "黑体");
	editBox->move(x, y);
	editBox->visable(true);
	editBox->setfocus();
}
void mainWindow()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);// 初始化图形窗口

	setbkcolor(EGERGB(0xFE, 0xFA, 0xE0));
	setcaption("学生信息管理系统");
	int button1_x, button1_y;  // “学生信息录入”按钮坐标
	int button2_x, button2_y;  // “学生信息管理”按钮坐标z
	// 计算按钮坐标
	button1_x = WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2;
	button1_y = WINDOW_HEIGHT / 2 - BUTTON_HEIGHT - 40;
	button2_x = WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2;
	button2_y = WINDOW_HEIGHT / 2 + 40;

	//按钮结构体
	BUTTON button1 = {
		button1_x,button1_y,
		BUTTON_WIDTH,BUTTON_HEIGHT,
		CORNERADIUS,
		R,G,B,
		28,
		"学生信息初始化"
	};

	BUTTON button2 = {
		button2_x,button2_y,
		BUTTON_WIDTH,BUTTON_HEIGHT,
		CORNERADIUS,
		R,G,B,
		28,
		"信息管理与查看"
	};
	drawButton(&button1);
	drawButton(&button2);
	int clickbutton1 = 0;
	int clickbutton2 = 0;
	//文字说明
	puttext(100, 100, 35, "欢迎使用学生管理系统");
	puttext(100, 135, 35, "第一次录入成绩请点第一个按钮，添加、排序、查找请进入管理界面");
	puttext(100, 170, 35, "需要重新录入信息时请点击第一个按钮初始化信息");
	puttext(100, 205, 35, "可以阅读文件夹中的README来了解使用须知");
	//这段代码是一个鼠标事件处理的无限循环。程序会不断获取鼠标消息并根据鼠标事件的类型进行相应的操作。代码逻辑如下：

	/*当鼠标左键被点击时，进入判断。
		如果鼠标左键是按下状态，通过调用click()函数检测鼠标点击的位置是否在按钮1或按钮2上，并将相应的布尔值赋给clickbutton1和clickbutton2。
		如果鼠标左键是抬起状态，根据clickbutton1和clickbutton2的值进行判断：
		如果clickbutton1为真，则清除屏幕内容并显示学生录入窗口。
		如果clickbutton2为真，则清除屏幕内容并显示学生管理窗口。
		如果以上两个条件都不满足，则继续下一次循环。
		最后，通过delay()函数延时10毫秒，以避免过于频繁的循环。*/

	while (1) {
		// 获取鼠标消息
		mouse_msg msg = getmouse();

		// 判断鼠标左键是否点击
		if (msg.is_left()) {
			// 判断鼠标左键是否按下
			if (msg.is_down()) {
				// 检测点击的按钮
				clickbutton1 = click(&button1, msg.x, msg.y);
				clickbutton2 = click(&button2, msg.x, msg.y);
			}
			// 鼠标左键抬起
			else {
				// 如果按钮1被点击
				if (clickbutton1) {
					// 清除屏幕内容
					cleardevice();
					// 显示学生录入窗口
					studentEntryWindow();
				}
				// 如果按钮2被点击
				else if (clickbutton2) {
					// 清除屏幕内容
					cleardevice();
					// 显示学生管理窗口
					studentManagementWindow();
				}
				// 没有按钮被点击，继续循环
				else {
					continue;
				}
			}
		}
		// 延时10毫秒，避免过于频繁的循环
		delay(10);
	}

	closegraph();
}
void studentEntryWindow()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);  // 初始化图形窗口

	setbkcolor(EGERGB(0xFE,0xFA,0xE0));

	setcaption("学生信息初始化");

	int BackButton_x, BackButton_y; //”录入界面的返回按钮坐标“
	int AddInfoButton_x, AddInfoButton_y;//“录入界面的添加信息的按钮"

	int complete1button_x, complete1button_y; //"输入科目数量完成按钮"

	int back_x = 80;
	int back_y = 80;
	BUTTON buttonarray[6];
	const int buffSize = 100;//输入缓冲区
	char strBuffer[100] = "";//输入缓冲区
	sys_edit editBox;//科目数量
	student stu[50]{}; //学生数量（最大50）
	int count = 0;//录入的学生数量
	int i, j;

	BUTTON back = {
		back_x,back_y,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"返回"
	}; buttonarray[0] = { back }; //返回按钮

	BUTTON confirm = {
		900,back_y,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"输入学科数"
	}; buttonarray[1] = { confirm }; //确定按钮

	BUTTON add_student = {
		back_x, back_y + 400,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"添加学生"
	}; buttonarray[2] = { add_student }; //添加学生按钮
	BUTTON set_sub = {
		back_x,back_y + 200,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"设置科目名称"
	}; buttonarray[3] = { set_sub };
	BUTTON check = 
	{
		back_x, back_y + 600,
		100,80,
		CORNERADIUS,
		R,G,B,
		28,
		"预览"
	}; buttonarray[4] = { check };

	puttext(back_x + 100, back_y + 30, 25, "点击按钮输入科目数量（最大为5）：请按顺序录入数量、科目名、学生，最后预览");
	puttext(back_x + 100, back_y + 60, 25, "录入数量和名称前其余按钮不可触发，退出该界面需要重新录入");

	for (i = 0; i < 6; i++)						//绘制所有按钮
	{
		drawButton(&buttonarray[i]);
	}
	/*initEditBox(&editBox, back_x + 160 + textwidth("请输入科目数量（最大为5）："), back_y + BACK_WIDTH / 4, 200, 30);*/
	;
	//第一次帧循环，确定录入科目数量
	while (1) {
		int flag = 0;
		int is_confirm = 0;
		mouse_msg msg = getmouse();
		//判断鼠标左键点击（左键按下确定位置，抬起为执行时刻）
		if (msg.is_left()) {
			if (msg.is_down()) {
				//检测点击的按钮
				if (click(&confirm, msg.x, msg.y))
				{
					//第一次输入
					{
						inputbox_getline("请输入科目数量", "请输入科目数量\n注意：1.请输入数字\n2.最大科目数为5\n3.按回车结束输入",
							strBuffer, buffSize);
						int res = sscanf(strBuffer, "%d", &SUB_NUM);
						if (res != 1 || SUB_NUM > 5 || SUB_NUM <= 0)
						{
							//输入提示信息
							setfillcolor(EGEARGB(0xff, 0x40, 0x40, 0x40));
							setbkmode(TRANSPARENT);
							setcolor(BLACK);
							setfont(28, 0, "微软雅黑");
							xyprintf(WINDOW_WIDTH / 2, 600, "输入错误");
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
						

							//输入提示信息
							setfillcolor(EGEARGB(0xff, 0x40, 0x40, 0x40));
							setbkmode(TRANSPARENT);
							setcolor(BLACK);
							setfont(28, 0, "微软雅黑");
							xyprintf(800, back_y - 40, "输入了%d个学科", SUB_NUM);
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
		//检测到confirm按钮点击就标记为输入完毕
		
 //设置科目
	while (1) {
		mouse_msg msg = getmouse();
		//判断鼠标左键点击（左键按下确定位置，抬起为执行时刻）
		if (msg.is_left()) {
			if (msg.is_down()) {
				//检测点击的按钮
				//是否返回
			//设置科目
				if (click(&set_sub, msg.x, msg.y))
				{
					for (i = 0; i < SUB_NUM; i++)
					{
						cleardevice();//清屏重绘
						draw_entry(back_x, back_y, buttonarray);

						/*setfillcolor(EGEARGB(0xff, 0x40, 0x40, 0x40));
						setbkmode(TRANSPARENT);*/
						setcolor(BLACK);
						setfont(28, 0, "微软雅黑");
						xyprintf(WINDOW_WIDTH / 2, 600, "请输入第%d个学科", i + 1);
						xyprintf(WINDOW_WIDTH / 2, 650, "请输入英文名称");
						xyprintf(WINDOW_WIDTH / 2, 700, "按回车结束");

						inputbox_getline("请输入科目名称", "请输入科目名称\n注意：1.请输入英文\n2.下侧会提示正在输入第几个科目\n3.字符长度不超过15",
							subname[i], 16);

						cleardevice();//清屏重绘
						delay(200);
					}
					draw_entry(back_x, back_y, buttonarray);
					break;
				}
				//返回
				else if (click(&back, msg.x, msg.y))
				{
					cleardevice();
					mainWindow();
					break;
				}
			}
		}
	}
//录入学生与查看学生
	while (1)
	{
		mouse_msg msg = getmouse();
		//判断鼠标左键点击（左键按下确定位置）
		if (msg.is_left())
		{
			if (msg.is_down())
			{
				//添加学生
				if (click(&add_student, msg.x, msg.y))
				{
					count = addstudent(stu, count, back_x, back_y, buttonarray);
					cleardevice();
					draw_entry(back_x, back_y, buttonarray);
					STU_NUM = count;
					calculate_score(stu);
					write_file(stu);

				}
				//预览
				else if (click(&check, msg.x, msg.y))
				{
					setcolor(RED);
					setfont(35, 0, "微软雅黑");
					xyprintf(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "请打开控制台查看");
					printstudent(stu,subname);
				}
				//是否返回
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
  // 初始化图形窗口
	int i;
	setbkcolor(EGERGB(0xFE, 0xFA, 0xE0));
	puttext(back_x + 100, back_y + 30, 25, "点击按钮输入科目数量（最大为5）：请按顺序录入数量、科目名、学生，最后预览");
	puttext(back_x + 100, back_y + 50, 25, "若已经输入过了，请忽略~");
	puttext(back_x + 100, back_y + 70, 25, "若您在信息管理界面，成绩会从大到小自动排好");
	puttext(back_x + 100, back_y + 100, 25, "区分大小写");
	for (i = 0; i < 8; i++)						//绘制所有按钮
	{
		drawButton(&buttonarray[i]);

	}
	setfillcolor(EGEARGB(0xff, 0x40, 0x40, 0x40));//文字
	setbkmode(TRANSPARENT);
	setcolor(BLACK);
	setfont(28, 0, "微软雅黑");
}
// 函数名称：addstudent
// 功能：添加学生信息
// 参数：
// - stu：学生信息数组
// - count：当前已添加的学生数量
// - back_x：返回按钮的x坐标
// - back_y：返回按钮的y坐标
// - buttonarray：按钮数组
// 返回值：更新后的学生数量
int addstudent(student stu[], int count, int back_x, int back_y, BUTTON buttonarray[])
{
	int i;
	int add_flag = 0; // 添加标志，用于记录是否成功添加学生信息
	char num[10]; // 学号输入的字符数组

	// 录入学生学号
	setcolor(BLACK);
	setfont(28, 0, "微软雅黑");
	xyprintf(WINDOW_WIDTH / 2, 600, "请输入第%d个学生", count + 1);
	xyprintf(WINDOW_WIDTH / 2, 650, "请输入学号");
	xyprintf(WINDOW_WIDTH / 2, 700, "按回车结束");

	// 获取学生学号输入
	inputbox_getline("请输入学生信息", "请输入学生学号\n注意：1.请输入数字或英文\n2.最大位数为10，多余会被忽略",
		stu[count].number, 11);

	// 清屏重绘
	cleardevice();
	draw_entry(back_x, back_y, buttonarray);


	// 录入学生姓名
	setcolor(BLACK);
	setfont(28, 0, "微软雅黑");
	xyprintf(WINDOW_WIDTH / 2, 600, "请输入第%d个学生", count + 1);
	xyprintf(WINDOW_WIDTH / 2, 650, "请输入姓名");
	xyprintf(WINDOW_WIDTH / 2, 700, "按回车结束");


	// 获取学生姓名输入
	inputbox_getline("请输入学生信息", "请输入学生姓名\n注意：1.请输入英文\n2.名字最长为20个字符，多余会被忽略",
		stu[count].name, 21);

	cleardevice();
	draw_entry(back_x, back_y, buttonarray);

	// 按顺序录入学生成绩
	for (i = 0; i < SUB_NUM; i++)
	{
		cleardevice();
		draw_entry(back_x, back_y, buttonarray);
		setcolor(BLACK);
		setfont(24, 0, "微软雅黑");
		xyprintf(WINDOW_WIDTH / 2, 600, "请输入第%d个学生%s的成绩", count + 1, subname[i]);
		xyprintf(WINDOW_WIDTH / 2, 650, "请输入成绩（0-100）");
		xyprintf(WINDOW_WIDTH / 2, 700, "按回车结束");

		// 获取学生成绩输入
		inputbox_getline("请输入学生信息", "请输入成绩\n注意：1.范围为0-100，且为整数\n2.下侧会提示正在输入哪个科目",
			num, sizeof(stu[count].name) / sizeof(char));
		int res = sscanf(num, "%d", &stu[count].grade.subject[i]); // 整型格式录入


		if (res != 1 || stu[count].grade.subject[i] < 0 || stu[count].grade.subject[i] > MAX_SCORE)
		{
			setcolor(BLACK);
			setfont(24, 0, "微软雅黑");
			xyprintf(WINDOW_WIDTH / 2, 550, "成绩输入范围有误");
			i--;
			Sleep(200);
			cleardevice(); // 清屏
			draw_entry(back_x, back_y, buttonarray);
			continue;
		}

		delay(200);
	}

	count++; // 更新学生数量
	return count;
}
// 函数名: delstudent
// 功能: 删除学生信息
// 参数:
//   - stu: 学生信息数组
//   - count: 学生信息数组的大小
//   - back_x, back_y: 返回按钮的坐标
//   - buttonarray: 按钮数组
// 返回值: 删除后学生信息数组的大小
int delstudent(student stu[], int count, int back_x, int back_y, BUTTON buttonarray[]) {
	int pos = -1;
	char input_number[11];
	int i;

	xyprintf(WINDOW_WIDTH / 2, 650, "学号应完全匹配，并非模糊搜索,一次只能删除一个");
	xyprintf(WINDOW_WIDTH / 2, 700, "按回车结束");

	inputbox_getline("请输入学生学号", "请输入学生学号\n注意：1.请输入数字或英文\n2.最大位数为10,多余会被忽略\n3.一次只能删除一个学生\n4.请精确输入学号，按回车结束",
		input_number, 11);


	pos = ranksearch(stu, count, input_number);
	if (pos != -1) {
		// 将后面的元素依次向前移动
		for (i = pos + 1; i < count; i++) {
			stu[i - 1] = stu[i];
		}
		count--; // 更新学生信息数组的大小

		cleardevice();
		draw_entry(back_x, back_y, buttonarray);
		setcolor(BLACK);
		setfont(24, 0, "微软雅黑");
		xyprintf(WINDOW_WIDTH / 2, 600, "删除成功！");
		Sleep(300); // 延迟一段时间清屏重绘
		cleardevice();
		draw_entry(back_x, back_y, buttonarray);
	}
	else {
		setcolor(BLACK);
		setfont(24, 0, "微软雅黑");
		xyprintf(WINDOW_WIDTH / 2, 600, "没有找到该学生！");
		Sleep(300); // 延迟一段时间清屏重绘
		cleardevice();
		draw_entry(back_x, back_y, buttonarray);
	}

	return count;
}

//按照格式打印成绩
void printstudent(student stu[], char subname[MAX_EXAM][16])
{
	int i,j;
	printf("The Number of the student is %d\n", STU_NUM); // 打印学生数量

	printf("%2s%11s%25s", "  ", "StudentID", "Name"); // 打印表头

	for (i = 0; i < SUB_NUM; i++)
	{
		printf("%15s", subname[i]); // 打印科目名称
	}

	printf("%5s", "SUM"); // 打印总分列标题
	printf("\n");

	// 输出分数
	for (i = 0; i < STU_NUM; i++)
	{
		printf("%2d", i + 1); // 输出序号
		printf("%11s%25s", stu[i].number, stu[i].name); // 打印学生学号和姓名

		for (j = 0; j < SUB_NUM; j++)
		{
			printf("%15d", stu[i].grade.subject[j]); // 打印学生各科目分数
		}

		printf("%5d", stu[i].grade.sum); // 打印学生总分
		printf("\n");
	}
}
//算总分
void calculate_score(student stu[])
{
	//算总分
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
//将信息写入文件
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
		fprintf(fp, "%5d", stu[i].grade.sum);//总分
		fprintf(fp, "\n");
	}
	for (i = 0; i < SUB_NUM; i++)
	{
		fprintf(fp, "%15s", subname[i]);
	}
	fclose(fp);
}
//将信息从文件读出
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
		fscanf(fp, "%5d", &stu[i].grade.sum);//总分
	}
	for (i = 0; i < *SUB_NUM; i++)
	{
		fscanf(fp, "%15s", subname[i]);
	}
	fclose(fp);
}
// 交换两个学生结构体的函数
void swap(student* a, student* b) {
	student temp = *a;
	*a = *b;
	*b = temp;
}
// 快速排序的分区函数
int partition(student arr[], int low, int high) {
	int pivot = arr[high].grade.sum; // 选取最后一个元素作为枢纽元（总成绩）
	int i = (low - 1);
	int j;

	for (j = low; j <= high - 1; j++) {
		if (arr[j].grade.sum >= pivot) { // 如果当前元素的总成绩大于等于枢纽元，则将其交换到前半部分
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]); // 将枢纽元放置到正确的位置
	return (i + 1); // 返回枢纽元的索引
}
// 快速排序的主函数
void quickSort(student arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high); // 获取枢纽元的索引

		quickSort(arr, low, pi - 1);  // 对枢纽元的左侧进行递归排序
		quickSort(arr, pi + 1, high); // 对枢纽元的右侧进行递归排序
	}
}
//模糊搜索函数
int vaguesearch(const char* key, const char* str)
{
	/*这段代码实现了模糊搜索的函数。它接受两个参数，一个是关键词 key，另一个是待搜索的字符串 str。
		函数会在字符串 str 中寻找与关键词 key 匹配的子串。它通过逐个比较子串的方式进行搜索。首先，它获取关键词和待搜索字符串的长度。
		然后，它循环遍历待搜索字符串中的每个可能的子串，逐个字符与关键词进行比较。如果找到了匹配的子串，就返回1表示找到了，否则返回0表示未找到。*/
	int i, j;
	int keyLen = strlen(key); // 获取关键词的长度
	int strLen = strlen(str); // 获取待搜索字符串的长度
	// 依次比较子串
	for (i = 0; i <= strLen - keyLen; i++) // 循环遍历待搜索字符串中的每个可能的子串
	{
		int match = 1; // 匹配标志，用于判断是否找到关键词

		// 比较str和key的每个字符
		for (j = 0; j < keyLen; j++) // 循环遍历关键词中的每个字符
		{
			if (str[i + j] != key[j]) // 比较对应位置的字符是否相等
			{
				match = 0; // 如果有不匹配的字符，将匹配标志设为0
				break; // 跳出内层循环
			}
		}

		if (match == 1) // 如果匹配标志为1，表示找到了关键词
		{
			return 1; // 找到了
		}
	}

	return 0; // 未找到
}
//随机搜索函数
int ranksearch(student stu[], int count, const char* input_number) {
	// 使用随机搜索查找学号匹配的学生
	int max_attempts = count * 5; // 最大尝试次数为学生数量的五倍
	int attempts = 0; // 尝试次数
	int pos = -1; // 找到的位置

	while (attempts < max_attempts && pos == -1) {
		int random_index = rand() % count; // 生成随机索引
		if (strcmp(stu[random_index].number, input_number) == 0) {
			pos = random_index;
		}
		attempts++;
	}

	return pos;
}
//判断是否有管理员权限
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

//短小精悍的主函数
int main()
{	
	int n = 0;
	int res = IsProcessRunAsAdmin();
	if (res == 0)
	{
		printf("程序以非管理员权限运行\n请右键快捷方式，选择属性，选择兼容性，选择\'以管理员权限运行，具体操作请阅读文件夹下的使用须知.doc\'\n,如果想要强制运行（可能会出现Bug），输入3.");
		scanf("%d", &n);
		if (n != 3)
		{
			system("pause");
			return 0;
		}
	}
	mciSendString("open bgm.mp3 alias a ", 0, 0, 0);//来点音乐
	mciSendString("play a", 0, 0, 0);
	mainWindow();
	return 0;
}