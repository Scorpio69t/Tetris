#pragma once
#ifndef __DATA_TYPE_H
#define __DATA_TYPE_H

constexpr auto WIDTH = 10;
constexpr auto HEIGHT = 20;
constexpr auto PIX = 20;
constexpr auto SPACE = 10;
constexpr auto M_MSG = 10;

struct BLOCK //一个图案的4个方向
{
	unsigned short dir[4];
};

//7种图案的4种值
struct BLOCK g_Blocks[7] = {
					{0x00C6, 0x0264, 0x00C6, 0x0264},   // Z
					{0x0036, 0x0462, 0x0036, 0x0462},	// 反Z
					{0x0027, 0x0131, 0x0072, 0x0232},   // |-
					{0x0F00, 0x4444, 0x0F00, 0x4444},   // I
					{0x0660, 0x0660, 0x0660, 0x0660},   // 口
					{0x0446, 0x0017, 0x0622, 0x0074},	// L
					{0x0226, 0x0071, 0x0644, 0x0047},	// 反L
};

struct Point
{
	int x;
	int y;
};

struct BlockInfo
{
	int type;
	int dir;
	COLORREF color;
	struct Point pos; //4*4网格的坐标原点
	struct Point basePos[4]; //存储每个小方格在4*4网格中的坐标
	struct Point offPos[4]; //存储每个小方格在游戏区里面的坐标
};


void initGame();  //初始化游戏界面
void closeGame(); //关闭游戏
void nextBlock(struct BlockInfo * p); //产生新的图案，下一个图案
void blockCoordlinate(struct BlockInfo* p); //计算图案位置
void drawBlock(struct BlockInfo* p, COLORREF color); //画当前图形
void drawNextBlock(struct BlockInfo* p); //画下一个图形
void updateScore(int lines);
void move(struct BlockInfo* p, int x, int y); //图形移动
int minY(struct BlockInfo* p);
int maxY(struct BlockInfo* p);
bool tryMove(struct BlockInfo block, int x, int y);
void show();
void drawArr();
void removeFillLine();
void blockDroped();
void onLineDown(struct BlockInfo* p);
void dropDown(struct BlockInfo* p);
struct BlockInfo onRotate(struct BlockInfo block);
void checkKeyBoard(struct BlockInfo* p);
void initMSG();
void pause_game();

#endif //__DATA_TYPE_H
