#pragma once
#define WINDOW_WIDTH 1024    // 窗口宽度
#define WINDOW_HEIGHT 768  // 窗口高度

#define SUBJECTS_WIDTH 240 //文本框宽度
#define SUBJECTS_HEIGHT 80 //文本框高度

#define BUTTON_WIDTH 240    // 按钮宽度
#define BUTTON_HEIGHT 80    // 按钮高度
#define CORNERRADIUS 10    //圆角

#define BACK_WIDTH 100//返回按钮宽度
#define BACK_HEIGHT 70//返回按钮高度

#define MAX_EXAM 5		//最大科目数量
#define MAX_STU 50		//最大学生数量

#define MAX_SCORE 100//满分
#define WINDOW_WIDTH 1024    // 窗口宽度
#define WINDOW_HEIGHT 768  // 窗口高度
#define CORNERADIUS 10 //圆角
#define R 0xC7 //颜色常量R
#define G 0xBF  //G
#define B 0xC4  //B
#define NUM 10 //一页最多10人
typedef struct RoundRectButton	   //圆角矩形按钮
{
	int x, y; //坐标
	int width, height;  //宽度和高度
	float radius;//圆角
	int r, g, b;//颜色
	int fontsize;//字体大小
	char label[30];//按钮文字

}BUTTON;

typedef struct studentgrade
{
	int subject[MAX_EXAM];//每们学科的分数
	int sum;//总分
}stugrade;

typedef struct student
{
	char number[11];
	char name[21];
	stugrade grade;
}student;
typedef struct {
	int index;       // 学生索引
	int matchScore;  // 匹配得分
} SearchResult;