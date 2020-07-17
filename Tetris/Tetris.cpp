#include <iostream>
#include <time.h>
#include <cstdio>
#include <windows.h>
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include "data_type.h"

DWORD g_oldtime, g_newtime;//�δ�ʱ��
COLORREF m_gameMap[HEIGHT][WIDTH] = { BLACK };//��������
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
		//1��û���û����̣� 2���û��˼���
		g_newtime = GetTickCount(); //��ȡ����ϵͳ��������һ�������˶��ٸ�����
		if (g_newtime - g_oldtime >= 500) //����ʱʱ��ﵽ֮��Ӧ���õ�ǰͼ�������ƶ�һ��
		{
			g_oldtime = g_newtime;
			//�����ǰ��Ϸ���ĵ�ǰͼ��
			drawBlock(&g_curBlock, BLACK);
			//����һ��
			onLineDown(&g_curBlock);
			//���»��Ƶ�ǰͼ��
			drawBlock(&g_curBlock, g_curBlock.color);
		}
		if (_kbhit() == true) { // ����м�������
			checkKeyBoard(&g_curBlock);
		}
	}
	_getch();
	closeGame();

}

void initMSG()
{
	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 40);
	setaspectratio(1, 1);  // ����y���꣬����x����
	RECT r = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf[30] = { 0 };
	sprintf_s(buf, "w�ͷ����ϼ��� ͼ����ת");
	drawtext(buf, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 80);
	setaspectratio(1, 1);  // ����y���꣬����x����
	RECT r1 = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf1[30] = { 0 };
	sprintf_s(buf1, "a�ͷ�������� ͼ������");
	drawtext(buf1, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 120);
	setaspectratio(1, 1);  // ����y���꣬����x����
	RECT r2 = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf2[30] = { 0 };
	sprintf_s(buf2, "d�ͷ����Ҽ��� ͼ������");
	drawtext(buf2, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 160);
	setaspectratio(1, 1);  // ����y���꣬����x����
	RECT r3 = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf3[30] = { 0 };
	sprintf_s(buf3, "s�ͷ����¼��� ͼ������");
	drawtext(buf3, &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 200);
	setaspectratio(1, 1);  // ����y���꣬����x����
	RECT r4 = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf4[30] = { 0 };
	sprintf_s(buf4, "   �ո��    �� ͼ�γ���");
	drawtext(buf4, &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX + 240);
	setaspectratio(1, 1);  // ����y���꣬����x����
	RECT r5 = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf5[30] = { 0 };
	sprintf_s(buf5, "   p   �� ��Ϸ��ͣ");
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
	setorigin(0, 0); //�ָ�����ϵ
}

void pause_game()
{
	game_is_pause = !game_is_pause;
	if(game_is_pause)
	{
		setorigin(SPACE * 1 , SPACE * 2 + 4 * PIX + 80);
		setaspectratio(1, 1);  // ����y���꣬����x����
		RECT r = { 0, 0, 200,  30 };
		setfillcolor(LIGHTGRAY);
		solidrectangle(0, 0, 200, 30);
		TCHAR buf[30] = { 0 };
		sprintf_s(buf, "��Ϸ��ͣ�������������...");
		drawtext(buf, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		system("pause");

		setorigin(SPACE * 1, SPACE * 2 + 4 * PIX + 80);
		setaspectratio(1, 1);  // ����y���꣬����x����
		setfillcolor(BLACK);
		solidrectangle(0, 0, 200, 30);

		setorigin(0, 0); //�ָ�����ϵ
	}
}

void closeGame()
{
	closegraph();
}

void nextBlock(struct BlockInfo* p)
{
	p->type = rand() % 7;  //ͼ��ȡֵ��0-6
	p->dir = rand() % 4;	//ͼ���ķ���ȡֵ��0-3
	p->pos.x = (WIDTH - 4) / 2;
	p->pos.y = HEIGHT - 5;
	//��ʼ��������ɫ
	p->color = colors[rand() % 11];
	//���㷽�������
	blockCoordlinate(p);
}

void blockCoordlinate(struct BlockInfo* p)
{
	int idx = 0;
	unsigned short val = g_Blocks[p->type].dir[p->dir]; //��ͼ���Ӷ�ά������ȡ��
	for (int i = 15; i >= 0; i--, val <<= 1)
	{
		if (val & 0x8000) //�ж�val�����λ�Ƿ�Ϊ1
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
	//��������ϵ
	setorigin(SPACE, HEIGHT * PIX + SPACE); // ����ƽ�Ƶ����½�
	setaspectratio(1, -1);  // ����y���꣬����x����

	//��ȡÿ��С�������Ϣ(x,y),����С����
	for (int i = 0; i < 4; i++) {
		int x = p->offPos[i].x;
		int y = p->offPos[i].y;
		if (y < HEIGHT) {
			setfillcolor(color);
			solidrectangle(x * PIX + 1, y * PIX + 1, (x + 1) * PIX - 1, (y + 1) * PIX - 1);
			//g_oldtime = GetTickCount();
		}
	}
	//�ָ�����ϵ
	setaspectratio(1, -1);  // ����y���꣬����x����
	setorigin(0, 0); // ����ƽ�ƣ�0��0��
}

void drawNextBlock(struct BlockInfo* p)
{
	//��������ϵ
	setorigin(SPACE * 2 + WIDTH * PIX, 4 * PIX + SPACE); // ����ƽ�Ƶ����½�
	setaspectratio(1, -1);  // ����y���꣬����x����

	//��ȥ�����һ������ʾͼ��
	setfillcolor(BLACK);
	solidrectangle(0, 0, 4 * PIX, 4 * PIX);

	//��ȡÿ��С�������Ϣ(x,y),����С����
	for (int i = 0; i < 4; i++) {
		int x = p->basePos[i].x;
		int y = p->basePos[i].y;
		if (y < HEIGHT) {
			setfillcolor(p->color);
			solidrectangle(x * PIX + 1, y * PIX + 1, (x + 1) * PIX - 1, (y + 1) * PIX - 1);
		}
	}

	//�ָ�����ϵ
	setaspectratio(1, -1);  // ����y���꣬����x����
	setorigin(0, 0); // ����ƽ�ƣ�0��0��
}

void updateScore(int lines)
{
	m_score += scores[lines];
	setorigin(SPACE * 2 + WIDTH * PIX, SPACE * 2 + 4 * PIX);
	setaspectratio(1, 1);  // ����y���꣬����x����

	RECT r = { 0, 0, 200,  30 };
	setfillcolor(LIGHTGRAY);
	solidrectangle(0, 0, 200, 30);
	TCHAR buf[30] = { 0 };
	sprintf_s(buf, "������ %d", m_score);
	drawtext(buf, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//outtext(_T("hello world"));
}

void move(struct BlockInfo* p, int x, int y)
{
	p->pos.x += x; //�ı�4*4�����ԭ������
	p->pos.y += y;
	for (int i = 0; i < 4; i++) { //�ı�4��С���������
		p->offPos[i].x += x;
		p->offPos[i].y += y;
	}
}

int minY(struct BlockInfo* p)
{
	int miny = 1000;
	for (int i = 0; i < 4; i++) { //ȡ��4��С�����yֵȥ������
		miny = miny < p->offPos[i].y ? miny : p->offPos[i].y;
	}
	return miny; //���ص�ǰ��������С��y����
}

int maxY(struct BlockInfo* p)
{
	int maxy = 0;
	for (int i = 0; i < 4; i++) {
		maxy = maxy > p->offPos[i].y ? maxy : p->offPos[i].y;
	}
	return maxy;
}

// ģ���ƶ��� �����߽緶Χ�򷵻�false��ģ�鲻�ı䡣  ������Ҫ���ƶ�
// left( -1, 0 )   right( 1, 0 )   down( 0, -1 )  rotate( 0, 0 )
bool tryMove(struct BlockInfo block, int x, int y)
{
	//�ѵ�ǰ���鿽��һ�ݣ�����������ķ���ȥ�ƶ����ж��ƶ�֮���Ƿ񻹴�����Ϸ��
	int curx, cury;
	for (int i = 0; i < 4; i++) { //�����ƶ���ÿ��С���������
		curx = block.offPos[i].x + x;
		cury = block.offPos[i].y + y;
		if (curx < 0 || curx >= WIDTH || cury < 0) {  // �����ƶ�
			return false;
		}
		//��ײ���
		if (cury < HEIGHT && m_gameMap[cury][curx] != BLACK) {  // �����ƶ�
			return false;
		}
	}
	//  �����ƶ��� �ƶ����ػ�
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

void drawArr() //���ƹ̶������ķ���
{
	setorigin(SPACE, HEIGHT * PIX + SPACE); // ����ƽ�Ƶ����½�
	setaspectratio(1, -1);  // ����y����  �У�����x����  ��
	// ��������
	setfillcolor(BLACK);
	solidrectangle(0, 0, WIDTH * PIX, HEIGHT * PIX);

	for (int y = 0; y < HEIGHT; y++) {  //�����鵱�е���Ϣ������ȥ����ͼ��
		for (int x = 0; x < WIDTH; x++) {
			if (m_gameMap[y][x] != BLACK) {
				setfillcolor(m_gameMap[y][x]);
				solidrectangle(x * PIX + 1, y * PIX + 1, (x + 1) * PIX - 1, (y + 1) * PIX - 1);
			}
		}
	}
	// �ָ�����ϵ
	setaspectratio(1, -1);  // ����y���꣬����x����
	setorigin(0, 0); // ����ƽ�ƣ�0��0��
}

// ���У�
void removeFillLine()
{
	int lines = 0;
	//�ڵ�ǰ��������yֵ����Сyֵ������ȥ�ж���û����Ҫ��������
	for (int y = minY(&g_curBlock); y <= maxY(&g_curBlock); y++) { // ֻ�����͵�ǰ������ص��������
		//printf("%d\n", y );
		bool lineIsFull = true;
		for (int x = 0; x < WIDTH; x++) { //����һ�з����ƶ�����ǰ��
			if (m_gameMap[y][x] == BLACK) {    // �����ǰ����0��������
				lineIsFull = false;
				break;
			}
		}
		if (lineIsFull)  // ��ʼ��������
		{
			lines++;
			//printf( "remove line:: %d\n", lines);
			for (int k = y; k < HEIGHT; k++) {  // ��һ������
				for (int j = 0; j < WIDTH; j++) {
					m_gameMap[k][j] = m_gameMap[k + 1][j];
				}
			}
			for (int j = 0; j < WIDTH; j++) {  // ������һ������
				m_gameMap[HEIGHT - 1][j] = BLACK;
			}
			y--;
		}
	}
	// ���½���
	if (lines > 0) {
		updateScore(lines);
	}
	drawArr();
}

void blockDroped()
{
	// �����Ӧӳ�䵽��ά������
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
	// ���У����������жϣ�
	removeFillLine();
	// �����·���
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

struct BlockInfo onRotate(struct BlockInfo block)//ͼ�α仯
{
	BlockInfo tmp = block;
	tmp.dir++;
	tmp.dir = tmp.dir % 4;
	blockCoordlinate(&tmp);
	return tmp;
}

//w && ��72��ͼ��������ת  s && ��80��ͼ���½�һ��  ' ' �ո�ͼ������
//a && ��75��ͼ������һ��  d && ��77��ͼ������һ��  'p' p����ͣ/����
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
