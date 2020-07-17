#include <iostream>
#include <time.h>
#include <cstdio>
#include <windows.h>
#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include "data_type.h"

DWORD g_oldtime, g_newtime;//滴答时间
COLORREF m_gameMap[HEIGHT][WIDTH] = { BLACK };//界面数组
COLORREF colors[11] = { BLUE, GREEN, RED, CYAN, MAGENTA, LIGHTBLUE, LIGHTGREEN, LIGHTRED, LIGHTCYAN, LIGHTMAGENTA, YELLOW };
struct BlockInfo g_curBlock, g_nextBlock;
int m_score = 0;
int scores[5] = { 0, 100, 300, 500, 800 };
bool game_is_pause = false;

int main()
{
	initGame();
	nextBlock(&g_nextBlock);
	g_curBlock = g_nextBlock;
	nextBlock(&g_nextBlock);
	drawNextBlock(&g_nextBlock);

	while (1) {
		//1、没有敲击键盘； 2、敲击了键盘
		g_newtime = GetTickCount(); //获取操作系统从启动后一共经历了多少个毫秒
		if (g_newtime - g_oldtime >= 500) //当定时时间达到之后，应该让当前图案往下移动一行
		{
			g_oldtime = g_newtime;
			//清除当前游戏区的当前图案
			drawBlock(&g_curBlock, BLACK);
			//下移一格
			onLineDown(&g_curBlock);
			//重新绘制当前图案
			drawBlock(&g_curBlock, g_curBlock.color);
		}
		if (_kbhit() == true) { // 如果有键盘输入
			checkKeyBoard(&g_curBlock);
		}
	}
	_getch();
	closeGame();

}

void initMSG()
{
	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 40);
	setaspectratio(1, 1);  // 向上y坐标，向右x坐标
	RECT r = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf[30] = { 0 };
	sprintf_s(buf, "w和方向上键： 图形旋转");
	drawtext(buf, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 80);
	setaspectratio(1, 1);  // 向上y坐标，向右x坐标
	RECT r1 = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf1[30] = { 0 };
	sprintf_s(buf1, "a和方向左键： 图形左移");
	drawtext(buf1, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 120);
	setaspectratio(1, 1);  // 向上y坐标，向右x坐标
	RECT r2 = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf2[30] = { 0 };
	sprintf_s(buf2, "d和方向右键： 图形右移");
	drawtext(buf2, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 160);
	setaspectratio(1, 1);  // 向上y坐标，向右x坐标
	RECT r3 = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf3[30] = { 0 };
	sprintf_s(buf3, "s和方向下键： 图形下移");
	drawtext(buf3, &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 200);
	setaspectratio(1, 1);  // 向上y坐标，向右x坐标
	RECT r4 = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf4[30] = { 0 };
	sprintf_s(buf4, "   空格键    ： 图形沉底");
	drawtext(buf4, &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 240);
	setaspectratio(1, 1);  // 向上y坐标，向右x坐标
	RECT r5 = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf5[30] = { 0 };
	sprintf_s(buf5, "   p   ： 游戏暂停");
	drawtext(buf5, &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void initGame()
{
	initgraph((WIDTH + M_MSG) * PIX + 3 * SPACE, HEIGHT * PIX + 2 * SPACE, SHOWCONSOLE);
	setbkcolor(LIGHTGRAY);
	cleardevice();

	setorigin(SPACE, SPACE);
	setfillcolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	setlinecolor(LIGHTRED);
	fillrectangle(-2, -2, WIDTH * PIX + 2, HEIGHT * PIX + 2);

	fillrectangle(-2 + SPACE + WIDTH * PIX, -2, SPACE * 2 + (WIDTH + 4) * PIX + 2, 4 * PIX + 2);

	updateScore(0);
	initMSG();
	setorigin(0, 0); //恢复坐标系
}

void pause_game()
{
	game_is_pause = !game_is_pause;
	if(game_is_pause)
	{
		setorigin(SPACE * 1 , SPACE * 2 + 4 * PIX + 80);
		setaspectratio(1, 1);  // 向上y坐标，向右x坐标
		RECT r = { 0, 0, 200,  30 };
		setfillcolor(LIGHTGRAY);
		solidrectangle(0, 0, 200, 30);
		TCHAR buf[30] = { 0 };
		sprintf_s(buf, "游戏暂停！按任意键继续...");
		drawtext(buf, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		system("pause");

		setorigin(SPACE * 1, SPACE * 2 + 4 * PIX + 80);
		setaspectratio(1, 1);  // 向上y坐标，向右x坐标
		setfillcolor(BLACK);
		solidrectangle(0, 0, 200, 30);

		setorigin(0, 0); //恢复坐标系
	}
}

void closeGame()
{
	closegraph();
}

void nextBlock(struct BlockInfo* p)
{
	p->type = rand() % 7;  //图案取值在0-6
	p->dir = rand() % 4;	//图案的方向取值在0-3
	p->pos.x = (WIDTH - 4) / 2;
	p->pos.y = HEIGHT - 5;
	//初始化方块颜色
	p->color = colors[rand() % 11];
	//计算方格的坐标
	blockCoordlinate(p);
}

void blockCoordlinate(struct BlockInfo* p)
{
	int idx = 0;
	unsigned short val = g_Blocks[p->type].dir[p->dir]; //把图案从二维数组中取出
	for (int i = 15; i >= 0; i--, val <<= 1)
	{
		if (val & 0x8000) //判断val的最高位是否为1
		{
			p->basePos[idx].x = i % 4;
			p->basePos[idx].y = i / 4;
			p->offPos[idx].x = p->pos.x + p->basePos[idx].x;
			p->offPos[idx].y = p->pos.y + p->basePos[idx].y;
			idx++;
		}
	}
}

void drawBlock(struct BlockInfo* p, COLORREF color)
{
	//设置坐标系
	setorigin(SPACE, HEIGHT * PIX + SPACE); // 坐标平移到左下角
	setaspectratio(1, -1);  // 向上y坐标，向右x坐标

	//读取每个小方块的信息(x,y),绘制小方块
	for (int i = 0; i < 4; i++) {
		int x = p->offPos[i].x;
		int y = p->offPos[i].y;
		if (y < HEIGHT) {
			setfillcolor(color);
			solidrectangle(x * PIX + 1, y * PIX + 1, (x + 1) * PIX - 1, (y + 1) * PIX - 1);
			//g_oldtime = GetTickCount();
		}
	}
	//恢复坐标系
	setaspectratio(1, -1);  // 向下y坐标，向右x坐标
	setorigin(0, 0); // 坐标平移（0，0）
}

void drawNextBlock(struct BlockInfo* p)
{
	//设置坐标系
	setorigin(SPACE * 2 + WIDTH * PIX, 4 * PIX + SPACE); // 坐标平移到左下角
	setaspectratio(1, -1);  // 向上y坐标，向右x坐标

	//先去清除上一个的提示图案
	setfillcolor(BLACK);
	solidrectangle(0, 0, 4 * PIX, 4 * PIX);

	//读取每个小方块的信息(x,y),绘制小方块
	for (int i = 0; i < 4; i++) {
		int x = p->basePos[i].x;
		int y = p->basePos[i].y;
		if (y < HEIGHT) {
			setfillcolor(p->color);
			solidrectangle(x * PIX + 1, y * PIX + 1, (x + 1) * PIX - 1, (y + 1) * PIX - 1);
		}
	}

	//恢复坐标系
	setaspectratio(1, -1);  // 向下y坐标，向右x坐标
	setorigin(0, 0); // 坐标平移（0，0）
}

void updateScore(int lines)
{
	m_score += scores[lines];
	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX);
	setaspectratio(1, 1);  // 向上y坐标，向右x坐标

	RECT r = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf[30] = { 0 };
	sprintf_s(buf, "分数： %d", m_score);
	drawtext(buf, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//outtext(_T("hello world"));
}

void move(struct BlockInfo* p, int x, int y)
{
	p->pos.x += x; //改变4*4网格的原点坐标
	p->pos.y += y;
	for (int i = 0; i < 4; i++) { //改变4个小方格的坐标
		p->offPos[i].x += x;
		p->offPos[i].y += y;
	}
}

int minY(struct BlockInfo* p)
{
	int miny = 1000;
	for (int i = 0; i < 4; i++) { //取出4个小方格的y值去做计算
		miny = miny < p->offPos[i].y ? miny : p->offPos[i].y;
	}
	return miny; //返回当前方块中最小的y坐标
}

int maxY(struct BlockInfo* p)
{
	int maxy = 0;
	for (int i = 0; i < 4; i++) {
		maxy = maxy > p->offPos[i].y ? maxy : p->offPos[i].y;
	}
	return maxy;
}

// 模块移动： 超出边界范围则返回false，模块不改变。  否则按照要求移动
// left( -1, 0 )   right( 1, 0 )   down( 0, -1 )  rotate( 0, 0 )
bool tryMove(struct BlockInfo block, int x, int y)
{
	//把当前方块拷贝一份，用这个拷贝的方块去移动，判断移动之后是否还存在游戏区
	int curx, cury;
	for (int i = 0; i < 4; i++) { //计算移动后每个小方块的坐标
		curx = block.offPos[i].x + x;
		cury = block.offPos[i].y + y;
		if (curx < 0 || curx >= WIDTH || cury < 0) {  // 不可移动
			return false;
		}
		//碰撞检测
		if (cury < HEIGHT && m_gameMap[cury][curx] != BLACK) {  // 不可移动
			return false;
		}
	}
	//  可以移动， 移动后重绘
	g_curBlock = block;
	move(&g_curBlock, x, y);
	return true;
}

void show()
{
	printf("+++++++++++++++++++++++\n");
	int i = 0, j = 0;
	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			printf("%02d ", m_gameMap[i][j]);
		}
		printf("\n");
	}
}

void drawArr() //绘制固定下来的方块
{
	setorigin(SPACE, HEIGHT * PIX + SPACE); // 坐标平移到左下角
	setaspectratio(1, -1);  // 向上y坐标  行，向右x坐标  列
	// 背景重置
	setfillcolor(BLACK);
	solidrectangle(0, 0, WIDTH * PIX, HEIGHT * PIX);

	for (int y = 0; y < HEIGHT; y++) {  //把数组当中的信息读出来去绘制图案
		for (int x = 0; x < WIDTH; x++) {
			if (m_gameMap[y][x] != BLACK) {
				setfillcolor(m_gameMap[y][x]);
				solidrectangle(x * PIX + 1, y * PIX + 1, (x + 1) * PIX - 1, (y + 1) * PIX - 1);
			}
		}
	}
	// 恢复坐标系
	setaspectratio(1, -1);  // 向下y坐标，向右x坐标
	setorigin(0, 0); // 坐标平移（0，0）
}

// 消行，
void removeFillLine()
{
	int lines = 0;
	//在当前方块的最大y值和最小y值区间内去判断有没有需要消除的行
	for (int y = minY(&g_curBlock); y <= maxY(&g_curBlock); y++) { // 只消除和当前方块相关的最多四行
		//printf("%d\n", y );
		bool lineIsFull = true;
		for (int x = 0; x < WIDTH; x++) { //将上一行方块移动到当前行
			if (m_gameMap[y][x] == BLACK) {    // 如果当前行有0，则不消除
				lineIsFull = false;
				break;
			}
		}
		if (lineIsFull)  // 开始消除处理
		{
			lines++;
			//printf( "remove line:: %d\n", lines);
			for (int k = y; k < HEIGHT; k++) {  // 上一层下移
				for (int j = 0; j < WIDTH; j++) {
					m_gameMap[k][j] = m_gameMap[k + 1][j];
				}
			}
			for (int j = 0; j < WIDTH; j++) {  // 最上面一层清零
				m_gameMap[HEIGHT - 1][j] = BLACK;
			}
			y--;
		}
	}
	// 更新界面
	if (lines > 0) {
		updateScore(lines);
	}
	drawArr();
}

void blockDroped()
{
	// 方块对应映射到二维数组中
	for (int i = 0; i < 4; ++i) {
		int x = g_curBlock.offPos[i].x;
		int y = g_curBlock.offPos[i].y;
		if (y > HEIGHT) {
			printf(" y > HEIGHT closeGame\n");
			closeGame();
			return;
		}
		m_gameMap[y][x] = g_curBlock.color;
	}
	// 消行（进行消行判断）
	removeFillLine();
	// 产生新方块
	g_curBlock = g_nextBlock;
	nextBlock(&g_nextBlock);
	// drawNextBlock
	drawNextBlock(&g_nextBlock);
}

void onLineDown(struct BlockInfo* p)
{
	if (tryMove(*p, 0, -1) == true)
	{
		return;
	}
	blockDroped();
}

void dropDown(struct BlockInfo* p)
{
	while (tryMove(*p, 0, -1) == true)
		;

	blockDroped();
}

struct BlockInfo onRotate(struct BlockInfo block)//图形变化
{
	BlockInfo tmp = block;
	tmp.dir++;
	tmp.dir = tmp.dir % 4;
	blockCoordlinate(&tmp);
	return tmp;
}

//w && 上72：图案进行旋转  s && 下80：图案下降一行  ' ' 空格：图案沉底
//a && 左75：图案左移一格  d && 右77：图案右移一格  'p' p：暂停/继续
void checkKeyBoard(struct BlockInfo* p)
{
	drawBlock(&g_curBlock, BLACK);
	char ch = _getch();
	//printf("%c\n", ch );
	switch (ch) {
	case 'w':
	case 72:
		tryMove(onRotate(*p), 0, 0);
		break;
	case 'a':
	case 75:
		tryMove(g_curBlock, -1, 0);
		break;
	case 's':
	case 80:
		onLineDown(&g_curBlock);
		break;
	case 'd':
	case 77:
		tryMove(g_curBlock, 1, 0);
		break;
	case ' ':
		dropDown(&g_curBlock);
		break;
	case 'p':
		pause_game();
		break;
	}
	drawBlock(&g_curBlock, g_curBlock.color);
}
