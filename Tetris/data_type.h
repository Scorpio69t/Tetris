#pragma once
#ifndef __DATA_TYPE_H
#define __DATA_TYPE_H

constexpr auto WIDTH = 10;
constexpr auto HEIGHT = 20;
constexpr auto PIX = 20;
constexpr auto SPACE = 10;
constexpr auto M_MSG = 10;

struct BLOCK //һ��ͼ����4������
{
	unsigned short dir[4];
};

//7��ͼ����4��ֵ
struct BLOCK g_Blocks[7] = {
					{0x00C6, 0x0264, 0x00C6, 0x0264},   // Z
					{0x0036, 0x0462, 0x0036, 0x0462},	// ��Z
					{0x0027, 0x0131, 0x0072, 0x0232},   // |-
					{0x0F00, 0x4444, 0x0F00, 0x4444},   // I
					{0x0660, 0x0660, 0x0660, 0x0660},   // ��
					{0x0446, 0x0017, 0x0622, 0x0074},	// L
					{0x0226, 0x0071, 0x0644, 0x0047},	// ��L
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
	struct Point pos; //4*4���������ԭ��
	struct Point basePos[4]; //�洢ÿ��С������4*4�����е�����
	struct Point offPos[4]; //�洢ÿ��С��������Ϸ�����������
};


void initGame();  //��ʼ����Ϸ����
void closeGame(); //�ر���Ϸ
void nextBlock(struct BlockInfo * p); //�����µ�ͼ������һ��ͼ��
void blockCoordlinate(struct BlockInfo* p); //����ͼ��λ��
void drawBlock(struct BlockInfo* p, COLORREF color); //����ǰͼ��
void drawNextBlock(struct BlockInfo* p); //����һ��ͼ��
void updateScore(int lines);
void move(struct BlockInfo* p, int x, int y); //ͼ���ƶ�
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
