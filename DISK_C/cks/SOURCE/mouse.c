#include"mouse.h"
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "SVGA.h"
//#include "draw.h"
#define  H 16
#define  W 12



int mouse_shape_1[H][W] =    //鼠标形状二维数组（光标）
{
    {1,1,0,0,0,0,0,0,0,0,0,0},
	{1,2,1,0,0,0,0,0,0,0,0,0},
	{1,2,2,1,0,0,0,0,0,0,0,0},
	{1,2,2,2,1,0,0,0,0,0,0,0},
	{1,2,2,2,2,1,0,0,0,0,0,0},
	{1,2,2,2,2,2,1,0,0,0,0,0},
	{1,2,2,2,2,2,2,1,0,0,0,0},
	{1,2,2,2,2,2,2,2,1,0,0,0},
	{1,2,2,2,2,2,2,2,2,1,0,0},
	{1,2,2,2,2,2,2,2,2,2,1,0},
	{1,2,2,2,2,2,2,1,1,1,1,1},
	{1,2,2,1,2,2,2,1,0,0,0,0},
	{1,2,1,0,1,2,2,1,0,0,0,0},
	{1,1,0,0,1,2,2,2,1,0,0,0},
	{1,0,0,0,0,1,2,1,1,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0}
};

int mouse_shape_2[H][W] =    //鼠标形状二维数组（手指）
{
    {0,0,0,1,1,1,0,0,0,0,0,0},
	{0,0,0,1,2,1,0,0,0,0,0,0},
	{0,0,0,1,2,1,0,0,0,0,0,0},
	{0,0,0,1,2,1,0,0,0,0,0,0},
	{0,0,0,1,2,1,0,0,0,0,0,0},
	{0,0,0,1,2,1,1,1,1,0,0,0},
	{1,1,0,1,2,1,2,1,2,1,1,0},
	{1,2,1,1,2,1,2,1,2,1,2,1},
	{1,2,2,2,2,2,2,2,2,1,2,1},
	{0,1,2,2,2,2,2,2,2,2,2,1},
	{0,1,2,2,2,2,2,2,2,2,2,1},
	{0,0,1,2,2,2,2,2,2,2,1,0},
	{0,0,1,2,2,2,2,2,2,2,1,0},
	{0,0,0,1,2,2,2,2,2,1,0,0},
	{0,0,0,1,2,2,2,2,2,1,0,0},
	{0,0,0,1,1,1,1,1,1,1,0,0}
};

int mouse_shape_3[H][W] =    //鼠标形状二维数组（文本标）
{
    {1,1,0,1,1,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0},
	{1,1,0,1,1,0,0,0,0,0,0,0}
};



unsigned int mouse_bk[20][20];           //存放被鼠标覆盖的区域
MOUSE mouse={0, 0, 0, 0};            //定义一个鼠标结构变量
 



/***鼠标初始化***/
void mouse_init()
{
	MouseInit();                  //鼠标复位，检测是否安装鼠标
	MouseRange(0,0,1012,752);         //鼠标范围设置
	mouse.state=0;					//设置为光标状态
	MouseGet(&mouse);                  //得到鼠标状态
	MouseSpeed(6,4);
	mouse_on(mouse);                 //显示鼠标
}


/***鼠标复位***/
void MouseInit()
{
	union REGS regs;
	regs.x.ax=0;
	int86(0x33,&regs,&regs);
	if(regs.x.ax==0)
	{
		printf("mouse error");
		delay(5000);
		exit(1);
	}
}
/********************************
	功能说明：设置鼠标计数与像素比,值越大鼠标移动速度越慢 
	参数说明：int   vx,	鼠标横向的；int   vy	鼠标纵向的
**
********************************/
void MouseSpeed(int x, int y)
{
	union REGS regs;
	regs.x.ax=0x0f;
	regs.x.cx=x;
    regs.x.dx=y;
	int86(0x33,&regs,&regs);
}
/**********************************************************************
	功能说明：设置鼠标灵敏度；设置鼠标倍速阈值；
	参数说明：x为水平灵敏度，y为竖直灵敏度,v为鼠标即将设定的倍速阈值
	返回值说明：无
*********************************************************************/
void SetMouseSen(int x,int y)
{
	union REGS regs;
    regs.x.ax=0x1a;
	regs.x.bx=x;
	regs.x.cx=y;
   // regs.x.dx=v;
	int86(51,&regs,&regs);
}
/***得到某一点的颜色值***/
unsigned int Getpixel64k(int x, int y)
{
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;
	unsigned char page;                                                  //要切换的页面号
	unsigned long int page_dev;                                           //对应显存地址偏移量                       
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))           //判断点是否在屏幕范围内，不在就退出 
	{
		printf("out of range");
	}
	page_dev = ((unsigned long int)y << 10) + x;                              //计算显存地址偏移量和对应的页面号，做换页操作
	page = page_dev >> 15;	//32k个点一换页，除以32k的替代算法
	Selectpage(page);
	return video_buffer[page_dev];	 //返回颜色
}

/***鼠标范围设置***/
void MouseRange(int x1, int y1, int x2, int y2)
{
	union REGS mouse;
	/*设置横坐标范围*/
	mouse.x.ax = 7;
	mouse.x.cx = x1;
	mouse.x.dx = x2;
	int86(0x33, &mouse, &mouse);
	/*设置纵坐标范围*/
	mouse.x.ax = 8;
	mouse.x.cx = y1;
	mouse.x.dx = y2;
	int86(0x33, &mouse, &mouse);
}


/***得到鼠标按键状态(不传递鼠标坐标)***/
int MouseBut(MOUSE * mouse)
{ 
	union REGS regs;
	regs.x.ax = 3;
	int86(0x33, &regs, &regs);
	mouse->key = regs.x.bx;
	return mouse->key;
}


/***得到鼠标位置，按键状态***/
int MouseGet(MOUSE * mouse)
{ 
	union REGS regs;
	regs.x.ax = 3;
	int86(0x33, &regs, &regs);
	mouse->x = regs.x.cx;
	mouse->y = regs.x.dx;
	mouse->key = regs.x.bx;
	return mouse->key;
}

/***设置鼠标显示位置***/
void MouseSet(int x,int y)
{
	union REGS regs;
    regs.x.ax=4;
	regs.x.cx=x;
    regs.x.dx=y;
	int86(0x33,&regs,&regs);      //设置鼠标当前坐标	
	mouse_on(mouse);               //画鼠标	
}

/***判断鼠标是否在指定区域内部***/
int mouse_in(int x1, int y1, int x2, int y2)
{ 
	MOUSE mouse = {0,0,0};                       //very important，设置一个鼠标结构，用来减少对主鼠标结构的调用 
	MouseGet(&mouse);       
	if ((mouse.x >= x1)
		&& (mouse.x <= x2)
		&& (mouse.y >= y1)
		&& (mouse.y <= y2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/***判断鼠标左键是否在指定区域内按下***/
int mouse_press(int x1, int y1, int x2, int y2)
{ 
	MOUSE mouse = {0,0,0,0};                       
	MouseGet(&mouse);       
	if ((mouse.x >= x1)
		&& (mouse.x <= x2)
		&& (mouse.y >= y1)
		&& (mouse.y <= y2)
		&& ((mouse.key & 1) == 1))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/***鼠标显示***/
void mouse_on(MOUSE mouse)
{
	int i, j;
	if(mouse.state==0)
	{
		for (i = 0; i < H; i++)
		{
			for (j = 0; j < W; j++)
			{
				
				mouse_bk[i][j] = Getpixel64k(j + mouse.x, i + mouse.y);  //存储鼠标覆盖区
				/***画鼠标***/
				if (mouse_shape_1[i][j] == 1)
					Putpixel64k(mouse.x + j, mouse.y + i, 0);
				else if (mouse_shape_1[i][j] == 2)
					Putpixel64k(mouse.x + j, mouse.y + i, 0xffff);
			}
		}
	}
	else if(mouse.state==1)
	{
		for (i = 0; i < H; i++)
		{
			for (j = 0; j < W; j++)
			{
				
				mouse_bk[i][j] = Getpixel64k(j + mouse.x, i + mouse.y);  //存储鼠标覆盖区
				/***画鼠标***/
				if (mouse_shape_2[i][j] == 1)
					Putpixel64k(mouse.x + j, mouse.y + i, 0);
				else if (mouse_shape_2[i][j] == 2)
					Putpixel64k(mouse.x + j, mouse.y + i, 0xffff);
			}
		}
	}
	else
	{
		for (i = 0; i < H; i++)
		{
			for (j = 0; j < W; j++)
			{
				
				mouse_bk[i][j] = Getpixel64k(j + mouse.x, i + mouse.y);  //存储鼠标覆盖区
				/***画鼠标***/
				if (mouse_shape_3[i][j] == 1)
					Putpixel64k(mouse.x + j, mouse.y + i, 0);
				else if (mouse_shape_3[i][j] == 2)
					Putpixel64k(mouse.x + j, mouse.y + i, 0xffff);
			}
		}
	}

}


/***鼠标每次移动重新显示***/
void mouse_show(MOUSE *mouse)
{  
	int i,j;       //循环变量
	int color;     //鼠标某点颜色
	int x,y;
	x=mouse->x;             //鼠标原位置坐标
	y=mouse->y;         
	MouseGet(mouse);    //得到新鼠标状态
	if(mouse->x!=x||mouse->y!=y)         //鼠标移动就重新画鼠标
	{
		for (i = 0; i < H; i++)           	
		{
			for(j = 0; j < W; j++)
			{
				if(mouse->state==0)
				{
					if (mouse_shape_1[i][j] == 0)
					continue;
				}
				else if(mouse->state==1)
				{
					if (mouse_shape_2[i][j] == 0)
					continue;
				}
				else
				{
					if (mouse_shape_3[i][j] == 0)
					continue;
				}
				Putpixel64k(x + j, y + i, mouse_bk[i][j]);   //画出原鼠标覆盖区
			}
		}
		mouse_on(*mouse);                            //在新位置显示鼠标
	}
}

/***鼠标形态转换***/
void mouse_trans(int state)
{
	if(mouse.state!=state)		//如果指定形态与当前状态不同
	{
		mouse_off(&mouse);
		mouse.state=state;
	}
	mouse_show(&mouse);
}

/***鼠标隐藏***/
void mouse_off(MOUSE *mouse)
{
	int i,j;
	int x,y;
	x=mouse->x;
	y=mouse->y;
	for (i = 0; i <H; i++)
		for (j = 0; j < W; j++)
		{
			if(mouse->state==0)
			{
				if (mouse_shape_1[i][j] == 0)
				continue;
			}
			else if(mouse->state==1)
			{
				if (mouse_shape_2[i][j] == 0)
				continue;
			}
			else
			{
				if (mouse_shape_3[i][j] == 0)
				continue;
			}
			Putpixel64k(x + j, y + i, mouse_bk[i][j]);   //画出原鼠标覆盖区
		}
}
