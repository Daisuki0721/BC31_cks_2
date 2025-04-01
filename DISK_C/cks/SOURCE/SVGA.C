#include "SVGA.h"
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <ghz.h>
#include <direct.h>
#include "mouse.h"
/**************************************
   SVGA的功能号ax说明
   0x4f00  读SVGA卡信息
   0x4f01  读显示模式信息
   0x4f02  设置显示模式
   0x4f03  读当前显示模式
   0x4f04  存储或恢复SVGA的视频状态
   0x4f05  控制内存页区域切换
   0x4f06  设置或读取逻辑扫描线宽度
   0x4f07  设置或读取视频内存与屏幕的初始对应位置
   0x4f08  设置或读取DAC各原色有效位数
   SVGA显示模式号bx：
		模式号		分辨率		颜色数		颜色位定义
		0x101		640*480		256				-
		0x103		800*600		256				-
		0x104		1024*768	16				-
		0x105		1024*768	256				-
		0x110		640*480		32K			1:5:5:5
		0x111		640*480		64K			5:6:5
		0x112		640*480		16.8M		8:8:8
		0x113		800*600		32K			1:5:5:5
		0x114		800*600		64K			5:6:5
		0x115		800*600		16.8M		8:8:8
		0x116		1024*768	32K			1:5:5:5
		0x117		1024*768	64K			5:6:5
		0x118		1024*768	16.8M		8:8:8
**************************************************/
void SetSVGA256(void)
{
	/*****************************************************
	在dos.h中REGS的定义如下：
	struct WORDREGS
	{
		unsigned int ax, bx, cx, dx, si, di, cflag, flags;
	};
	
	struct BYTEREGS
	{
		unsigned char al, ah, bl, bh, cl, ch, dl, dh;
	};
	
	union REGS
	{
		struct WORDREGS x;
		struct BYTEREGS h;
	};
	这样al对应ax的低八位，ah对应ax的高八位，以此类推。
	调用时需要查表决定各入口参数取值,获取返回值表示的信息。
	*****************************************************/
	union REGS graph_regs;
	
	/*设置VESA VBE模式的功能号*/
	graph_regs.x.ax = 0x4f02;
	graph_regs.x.bx = 0x105;
	int86(0x10, &graph_regs, &graph_regs);
	
	/*ax != 0x004f意味着初始化失败，输出错误信息见上,下同*/
	if (graph_regs.x.ax != 0x004f)
	{
		printf("Error in setting SVGA mode!\nError code:0x%x\n", graph_regs.x.ax);
		delay(5000);
		exit(1);
	}
}

/**********************************************************
Function：		SetSVGA64k

Description：	SVGA显示模式设置函数，设为0x117

Calls：			int86
				delay
				printf
				exit

Called By：		AutoSimulate
				HandOperate
				
Input：			None

Output：		错误信息

Return：		None				
Others：		None
**********************************************************/
void SetSVGA64k(void)
{
	/*REGS联合体见上*/
	union REGS graph_regs;
	
	/*设置VESA VBE模式的功能号*/
	graph_regs.x.ax = 0x4f02;
	graph_regs.x.bx = 0x117;
	int86(0x10, &graph_regs, &graph_regs);
	
	/*ax != 0x004f意味着初始化失败，输出错误信息见上,下同*/
	if (graph_regs.x.ax != 0x004f)
	{
		printf("Error in setting SVGA mode!\nError code:0x%x\n", graph_regs.x.ax);
		delay(5000);
		exit(1);
	}
}

/**********************************************************
Function：		GetSVGA

Description：	获取SVGA显示模式号bx。摘录常用的模式号如下：
				模式号		分辨率		颜色数		颜色位定义
				0x101		640*480		256				-
				0x103		800*600		256				-
				0x104		1024*768	16				-
				0x105		1024*768	256				-
				0x110		640*480		32K			1:5:5:5
				0x111		640*480		64K			5:6:5
				0x112		640*480		16.8M		8:8:8
				0x113		800*600		32K			1:5:5:5
				0x114		800*600		64K			5:6:5
				0x115		800*600		16.8M		8:8:8
				0x116		1024*768	32K			1:5:5:5
				0x117		1024*768	64K			5:6:5
				0x118		1024*768	16.8M		8:8:8

Calls：			int86
				delay
				printf
				exit

Called By：		Unknown
Input：			None

Output：		初始化失败时会屏幕输出错误号。

Return：		unsigned int graph_regs.x.bx	显示模式号

Others：		None
**********************************************************/
unsigned int GetSVGA(void)
{
	/*REGS联合体见上*/
	union REGS graph_regs;
	
	/*获取当前VESA VBE模式的功能号*/
	graph_regs.x.ax = 0x4f03;
	int86(0x10, &graph_regs, &graph_regs);
	
	/*显示错误信息*/
	if (graph_regs.x.ax != 0x004f)
	{
		printf("Error in getting SVGA mode!\nError code:0x%x\n", graph_regs.x.ax);
		delay(5000);
		exit(1);
	}
	
	return graph_regs.x.bx;
}

/**********************************************************
Function：		Selectpage

Description：	带判断功能的换页函数，解决读写显存时跨段寻址问题

Calls：			int86

Called By：		Putpixel256
				Putpixel64k
				Xorpixel
				Horizline
				Getpixel64k
				
Input：			register char page		需要换到的页面号

Output：		None
Return：		None
Others：		None
**********************************************************/
void Selectpage(register char page)
{
	/*REGS含义同上*/
	union REGS graph_regs;
	
	/*上一次的页面号,用于减少切换次数,是使用次数很多的重要变量*/
	static unsigned char old_page = 0;
	
	/*标志数，用于判断是否是第一次换页*/
	static int flag = 0;
	
	/*窗口页面控制功能号*/
	graph_regs.x.ax = 0x4f05;
	graph_regs.x.bx = 0;
	
	/*如果是第一次换页*/
	if (flag == 0)
	{
		old_page = page;
		graph_regs.x.dx = page;
		int86(0x10, &graph_regs, &graph_regs);
		flag++;
	}
	
	/*如果和上次页面号不同，则进行换页*/
	else if (page != old_page)
	{
		old_page = page;
		graph_regs.x.dx = page;
		int86(0x10, &graph_regs, &graph_regs);
	}
}

/**********************************************************
Function：		Putpixel256

Description：	画点函数，其他画图函数的基础，仅适用于0x105模式！

Calls：			Selectpage

Called By：		Putbmp256
				Line
				Circle
				
Input：			int x					像素横坐标，从左到右增加，0为最小值（屏幕参考系）
				int y					像素纵坐标，从上到下增加，0为最小值（屏幕参考系）
				unsigned char color		颜色数，共有256种

Output：		在屏幕上画指定颜色的点

Return：		None
Others：		None
**********************************************************/
void Putpixel256(int x, int y, unsigned char color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned char far * const video_buffer = (unsigned char far *)0xa0000000L;
	
	/*要切换的页面号*/
	unsigned char new_page;
	
	/*对应显存地址偏移量*/
	unsigned long int page;
	
	/*判断点是否在屏幕范围内，不在就退出*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		return;
	}
	
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 16;	/*64k个点一换页，除以64k的替代算法*/
	Selectpage(new_page);
	
	/*向显存写入颜色，对应点画出*/
	video_buffer[page] = color;	
}

/**********************************************************
Function：		Putpixel64k

Description：	画点函数，其他画图函数的基础，仅适用于0x117模式！

Calls：			Selectpage

Called By：		Putbmp64k
				MousePutBk
				MouseDraw
				
Input：			int x					像素横坐标，从左到右增加，0为最小值（屏幕参考系）
				int y					像素纵坐标，从上到下增加，0为最小值（屏幕参考系）
				unsigned int color		颜色数，共有64k种

Output：		在屏幕上画指定颜色的点

Return：		None
Others：		None
**********************************************************/
void Putpixel64k(int x, int y, unsigned int color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;
	
	/*要切换的页面号*/
	unsigned char new_page;
	
	/*对应显存地址偏移量*/
	unsigned long int page;
	
	/*判断点是否在屏幕范围内，不在就退出*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		return;
	}
	
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 15;	/*32k个点一换页，除以32k的替代算法*/
	Selectpage(new_page);
	
	/*向显存写入颜色，对应点画出*/
	video_buffer[page] = color;	
}

/**********************************************************
Function：		Putbmp256

Description：	8位非压缩bmp图定位显示函数。
				只支持8位非压缩bmp图，宽度像素最大允许为1024！
				其余bmp类型均不支持！
				仅在0x105模式下使用！
				为了简化，没有设置文件类型检测功能检测功能，请勿读入不合要求的文件！
				此函数适合在不换位面条件下读取大型图片。
				虽然能设置了读取颜色表功能，并能兼容实际使用颜色表数不足最大数的图片，
				但统一要求使用Windows默认颜色表，否则影响其他图片显示！

Calls：			Putpixel256

				fseek
				fread
				fclose
				outportb
				malloc
				free

Called By：		AutoSimulate
				HandOperate
				
Input：			int x		图片左上角的横坐标（屏幕参考系）
				int y		图片左上角的纵坐标（屏幕参考系）
				const char * path	bmp图片路径

Output：		屏幕上显示图片

Return：		0	显示成功
				-1	显示失败
				
Others：		None
**********************************************************/
int Readbmp256(int x, int y, const char * path)
{
	/*指向图片文件的文件指针*/
	FILE * fpbmp;
	
	/*bmp颜色表结构指针*/
	RGBQUAD * pclr, *clr;
	
	/*行像素缓存指针*/
	unsigned char * buffer;
	
	/*实际使用的颜色表中的颜色数*/
	unsigned long int clr_used;
	
	/*图片的宽度、高度、一行像素所占字节数（含补齐空字节）*/
	long int width, height, linebytes;
	
	/*循环变量*/
	int i, j;
	
	/*图片位深*/
	unsigned int bit;
	
	/*压缩类型数*/
	unsigned long int compression;
	
	/*打开文件*/
	if ((fpbmp = fopen(path, "rb")) == NULL)
	{
		return -1;
	}
	
	/*读取位深*/
	fseek(fpbmp, 28L, 0);
	fread(&bit, 2, 1, fpbmp);
	
	/*非8位图则退出*/
	if (bit != 8U)
	{
		return -1;
	}
	
	/*读取压缩类型*/
	fseek(fpbmp, 30L, 0);
	fread(&compression, 4, 1, fpbmp);
	
	/*采用压缩算法则退出*/
	if (compression != 0UL)
	{
		return -1;
	}
	
	/*读取宽度、高度*/
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);
	
	/*宽度超限则退出*/
	if (width > SCR_WIDTH)
	{
		return -1;
	}

	/*计算一行像素占字节数，包括补齐的空字节*/
	linebytes = width % 4;
	
	if(!linebytes)
	{
		linebytes = width;
	}
	else
	{
		linebytes = width + 4 - linebytes;
	}
	
	/*读取实际使用的颜色表中的颜色数*/
	fseek(fpbmp, 46L, 0);
	fread(&clr_used, 4, 1, fpbmp);
	
	/*若颜色数为0，则使用了2的bit次方种颜色*/
	if (clr_used == 0L)
	{
		clr_used = 1U << bit;
	}
	
	/*开辟颜色表动态储存空间*/
	if ((clr = (RGBQUAD *)malloc(4L * clr_used)) == 0)
	{
		return -1;
	}
	
	/*颜色表工作指针初始化*/
	pclr = clr;
	
	/*读取颜色表*/
	fseek(fpbmp, 54L, 0);
	
	if ((fread((unsigned char *)pclr, 4L * clr_used, 1, fpbmp)) != 1)
	{
		return -1;
	}
	
	/*按照颜色表设置颜色寄存器值*/
	for (i = 0; i < clr_used; i++, pclr++) 
	{
		outportb(0x3c8, i);				/*设置要改变的颜色号*/
		outportb(0x3c9, pclr->r >> 2);
		outportb(0x3c9, pclr->g >> 2);
		outportb(0x3c9, pclr->b >> 2);
	}
	
	free(clr);
	
	/*开辟行像素数据动态储存空间*/
	if ((buffer = (unsigned char *)malloc(linebytes)) == 0)
	{
		return -1;
	}
	
	/*行扫描形式读取图片数据并显示*/
	fseek(fpbmp, 54L + 4L * clr_used, 0);
	for (i = height - 1; i > -1; i--)
	{
		fread(buffer, linebytes, 1, fpbmp);	/*读取一行像素数据*/
		
		for (j = 0; j < width; j++)
		{
			Putpixel256(j + x, i + y, buffer[j]);
		}
	}
	
	free(buffer);	
	fclose(fpbmp);
	
	return 0;	
}

/*********************************************************
Function：		Readbmp64k

Description：	24位非压缩bmp图定位显示函数。
				只支持24位非压缩bmp图，宽度像素最大允许为1024！
				其余bmp类型均不支持！
				仅在0x117模式下使用！
				为了简化，没有设置文件类型检测功能检测功能，请勿读入不合要求的文件！

Calls：			Putpixel64k

				fseek
				fread
				fclose
				outportb
				malloc
				free

Called By：		AutoSimulate
				HandOperate
				Menu
				
Input：			int x		图片左上角的横坐标（屏幕参考系）
				int y		图片左上角的纵坐标（屏幕参考系）
				const char * path	bmp图片路径

Output：		屏幕上显示图片

Return：		0	显示成功
				-1	显示失败
				
Others：		None
**********************************************************/
int Readbmp64k(int x, int y, const char * path)
{
	/*指向图片文件的文件指针*/
	FILE * fpbmp;
	
	/*行像素缓存指针*/
	COLORS24 * buffer;
	
	/*图片的宽度、高度、一行像素所占字节数（含补齐空字节）*/
	long int width, height, linebytes;
	
	/*循环变量*/
	int i, j;
	
	/*图片位深*/
	unsigned int bit;
	
	/*压缩类型数*/
	unsigned long int compression;
	
	/*打开文件*/
	if ((fpbmp = fopen(path, "rb")) == NULL)
	{
		return -1;
	}
	
	/*读取位深*/
	fseek(fpbmp, 28L, 0);
	fread(&bit, 2, 1, fpbmp);
	
	/*非24位图则退出*/
	if (bit != 24U)
	{
		return -1;
	}
	
	/*读取压缩类型*/
	fseek(fpbmp, 30L, 0);
	fread(&compression, 4, 1, fpbmp);
	
	/*采用压缩算法则退出*/
	if (compression != 0UL)
	{
		return -1;
	}
	
	/*读取宽度、高度*/
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);
	
	/*宽度超限则退出*/
	if (width > SCR_WIDTH)
	{
		return -1;
	}

	/*计算一行像素占字节数，包括补齐的空字节*/
	linebytes = (3 * width) % 4;
	
	if(!linebytes)
	{
		linebytes = 3 * width;
	}
	else
	{
		linebytes = 3 * width + 4 - linebytes;
	}

	/*开辟行像素数据动态储存空间*/
	if ((buffer = (COLORS24 *)malloc(linebytes)) == 0)
	{
		return -1;
	}
	
	/*行扫描形式读取图片数据并显示*/
	fseek(fpbmp, 54L, 0);
	for (i = height - 1; i > -1; i--)
	{
		fread(buffer, linebytes, 1, fpbmp);	/*读取一行像素数据*/
		
		/*一行像素的数据处理和画出*/
		for (j = 0; j < width; j++)
		{
			/*0x117模式下，原图红绿蓝各8位分别近似为5位、6位、5位*/
			buffer[j].R >>= 3;
			buffer[j].G >>= 2;
			buffer[j].B >>= 3;
			Putpixel64k(j + x, i + y,
			((((unsigned int)buffer[j].R) << 11)
			| (((unsigned int)buffer[j].G) << 5)
			| ((unsigned int)buffer[j].B)));	/*计算最终颜色，红绿蓝从高位到低位排列*/
		}
	}
	
	free(buffer);	
	fclose(fpbmp);
	
	return 0;	
}

/**********************************************************
Function：		Xorpixel

Description：	按位异或画点函数

Calls：			Selectpage

Called By：		XorCarBmp
				
Input：			int x					像素横坐标，从左到右增加，0为最小值（屏幕参考系）
				int y					像素纵坐标，从上到下增加，0为最小值（屏幕参考系）
				unsigned char color		颜色数，共有256种

Output：		在屏幕上画异或点

Return：		None
Others：		None
**********************************************************/
void Xorpixel(int x, int y, unsigned char color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned char far * const video_buffer = (unsigned char far *)0xa0000000L;
	
	/*要切换的页面号*/
	unsigned char new_page;
	
	/*对应显存地址偏移量*/
	unsigned long int page;
	
	/*判断点是否在屏幕范围内，不在就退出*/
	if(x < 0 || x > (SCR_WIDTH - 1) || y < 0 || y > (SCR_HEIGHT - 1))
	{
		return;
	}
	
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 16;
	Selectpage(new_page);
	
	/*按位异或方式向显存写入颜色，对应点画出*/
	video_buffer[page] ^= color;	
}

/***8位显示模式下划线***/ 
void Line(int x1, int y1, int x2, int y2, unsigned char color)
{
	int i;
	if(x1==x2)                   //竖直直线
	{
		for(i=y1;i<=y2;i++)
			Putpixel256(x1,i,color);
	}
	if(y1==y1)                   //水平直线
	{
		for(i=x1;i<=x2;i++)
			Putpixel256(i,y1,color);
	}
}
/***24位显示模式下划线***/
void Line1(int x1, int y1, int x2, int y2, unsigned int color)
{
	int i;
	if(x1==x2)                   //竖直直线
	{
		for(i=y1;i<=y2;i++)
			Putpixel64k(x1,i,color);
	}
	if(y1==y1)                   //水平直线
	{
		for(i=x1;i<=x2;i++)
			Putpixel64k(i,y1,color);
	}
}

void Line2(int x1, int y1, int x2, int y2, unsigned int color)
{
	int	dx, dy;			/*直线x、y坐标差值*/
	int dx2, dy2;		/*加快运算速度的中间值*/
	int xinc, yinc;		/*判断想、y增加方向的符号值*/
	int d, dxy;			/*决策变量*/
	/*计算坐标差值和中间变量*/
	dx = abs(x2 - x1);
	dx2 = dx << 1;
	dy = abs(y2 - y1);
	dy2 = dy << 1;
	
	/*判断直线x坐标增加方向*/
	if (x2 > x1)
	{
		xinc = 1;
	}
	
	/*如果是竖直线*/
	else if (x2 == x1)
	{
		/*y坐标排序*/
		if (y1 > y2)
		{
			dx = y1;
			y1 = y2;
			y2 = dx;
		}
		
		/*画竖直线*/
		for (dx = y1; dx <= y2; dx++)
		{
			Putpixel64k(x1, dx, color);
		}
		
		return;
	}
	
	else
	{
		xinc = -1;
	}
	
	/*判断直线y坐标增加方向*/
	if (y2 > y1)
	{
		yinc = 1;
	}
	
	/*如果是水平线*/
	else if (y2 == y1)
	{
		Line1(x1, y1, x2, y1, color);		
		return;
	}
	
	else
	{
		yinc = -1;
	}
	
	/*******************************
	以下运用Bresenham算法生成直线。
	该算法是得到公认的成熟的快速算法。
	具体细节略去。
	*******************************/
	Putpixel64k(x1, y1, color);
	
	if (dx >= dy)
	{
		d = dy2 - dx;
		dxy = dy2 - dx2;
		
		while (dx--)
		{
			if (d <= 0)
			{
				d += dy2;
			}
			
			else
			{
				d += dxy;
				y1 += yinc;
			}
			
			x1 += xinc;
			Putpixel64k(x1, y1, color);
		}
	}
	
	else
	{
		d = dx2 - dy;
		dxy = dx2 - dy2;
		
		while (dy--)
		{
			if (d <= 0)
			{
				d += dx2;
			}
			
			else
			{
				d += dxy;
				x1 += xinc;
			}
			
			y1 += yinc;
			Putpixel64k(x1, y1, color);
		}
	}
}

/***24位显示模式下划粗直线***/
void Line3(int x1, int y1, int x2, int y2, int radius,unsigned int color)
{
	int i;
	int dx,dy;
	if(x1>x2)    //解决x,y大小顺序问题
	{
		dx=x1;
		x1=x2;
		x2=dx;
	}
	if(y1>y2)
	{
		dy=y1;
		y1=y2;
		y2=dy;
	}
	if(x1==x2)                   //竖直直线
	{
		for(i=y1;i<=y2;i++)
			Circlefill(x1, i, radius, color);
	}
	if(y1==y1)                   //水平直线
	{
		for(i=x1;i<=x2;i++)
			Circlefill(i, y1, radius, color);
	}
}

void Line_Thick(int x1, int y1, int x2, int y2, int radius,unsigned int color)
{
	int	dx, dy;			/*直线x、y坐标差值*/
	int dx2, dy2;		/*加快运算速度的中间值*/
	int xinc, yinc;		/*判断x、y增加方向的符号值*/
	int d, dxy;			/*决策变量*/
	
	/*计算坐标差值和中间变量*/
	dx = abs(x2 - x1);
	dx2 = dx << 1;
	dy = abs(y2 - y1);
	dy2 = dy << 1;
	
	/*判断直线x坐标增加方向*/
	if (x2 > x1)
	{
		xinc = 1;
	}
	
	/*如果是竖直线*/
	else if (x2 == x1)
	{
		/*y坐标排序*/
		if (y1 > y2)
		{
			dx = y1;
			y1 = y2;
			y2 = dx;
		}
		
		/*画竖直线*/
		for (dx = y1; dx <= y2; dx++)
		{
			Circlefill(x1, dx, radius, color);
		}
		
		return;
	}
	
	else
	{
		xinc = -1;
	}
	
	/*判断直线y坐标增加方向*/
	if (y2 > y1)
	{
		yinc = 1;
	}
	
	/*如果是水平线*/
	else if (y2 == y1)
	{
		Line3(x1, y1, x2, y1,radius, color);		
		return;
	}
	
	else
	{
		yinc = -1;
	}
	
	/*******************************
	以下运用Bresenham算法生成直线。
	该算法是得到公认的成熟的快速算法。
	具体细节略去。
	*******************************/
	Circlefill(x1, y1, radius, color);
	
	if (dx >= dy)
	{
		d = dy2 - dx;
		dxy = dy2 - dx2;
		
		while (dx--)
		{
			if (d <= 0)
			{
				d += dy2;
			}
			
			else
			{
				d += dxy;
				y1 += yinc;
			}
			
			x1 += xinc;
			Circlefill(x1, y1, radius, color);
		}
	}
	
	else
	{
		d = dx2 - dy;
		dxy = dx2 - dy2;
		
		while (dy--)
		{
			if (d <= 0)
			{
				d += dx2;
			}
			
			else
			{
				d += dxy;
				x1 += xinc;
			}
			
			y1 += yinc;
			Circlefill(x1, y1, radius, color);
		}
	}
}

/***8位显示模式下画矩形***/
void Bar(int x1, int y1, int x2, int y2, unsigned int color)
{
	int i,j;
	for(j=y1;j<=y2;j++)
	{
		Line(x1,j,x2,j,color);
	}
}
/***24位显示模式下画矩形***/
void bar1(int x1, int y1, int x2, int y2, unsigned int color)
{
	int i,j;
	for(j=y1;j<=y2;j++)
	{
		Line1(x1,j,x2,j,color);
	}
}


/***24位显示模式下画矩形(不填色)***/
void bar2(int x1,int y1,int x2,int y2,unsigned int color)
{
	Line1(x1,y1,x2,y1,color);
    Line1(x2,y1,x2,y2,color);
	Line1(x1,y1,x1,y2,color);
	Line1(x1,y2,x2,y2,color);
}

void Circle(int xc, int yc, int radius, unsigned int color)
{
	/*画圆圈的定位变量和决策变量*/
	int x, y, d;
	
	/*半径必须为正，否则退出*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	以下运用Bresenham算法生成圆圈。
	该算法是得到公认的成熟的快速算法。
	具体细节略去。
	************************************/
	y = radius;
	d = 3 - radius << 1;
	
	for (x = 0; x <= y; x++)
	{
		Putpixel64k(xc + x, yc + y, color);
		Putpixel64k(xc + x, yc - y, color);
		Putpixel64k(xc - x, yc - y, color);
		Putpixel64k(xc - x, yc + y, color);
		Putpixel64k(xc + y, yc + x, color);
		Putpixel64k(xc + y, yc - x, color);
		Putpixel64k(xc - y, yc - x, color);
		Putpixel64k(xc - y, yc + x, color);
		
		if (d < 0)
		{
			d += x * 4 + 6;
		}
		
		else
		{
			d += (x - y) * 4 + 10;
			y--;
		}
	}
}

void Circlefill(int xc, int yc, int radius, unsigned int color)
{
	/*画圆圈的定位变量和决策变量*/
	int x = 0,
		y = radius,
		dx = 3,
		dy = 2 - radius - radius,
		d = 1 - radius;
	
	/*半径必须为正，否则退出*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	以下运用Bresenham算法生成实心圆。
	该算法是得到公认的成熟的快速算法。
	具体细节略去。
	************************************/
	while (x <= y)
	{
		Line1(xc - x, yc - y, xc + x, yc-y, color);
        Line1(xc - y, yc - x, xc + y, yc-x, color);
        Line1(xc - y, yc + x, xc + y, yc+x, color);
        Line1(xc - x, yc + y, xc + x, yc+y, color);
        
        if (d < 0)
        {
            d += dx;
            dx += 2;
        }
        
        else
        {
            d += (dx + dy);
            dx += 2;
            dy += 2;
            y--;
		}

        x++;
	}
}

void CloseSVGA(void)        
{
    union REGS regs;
    regs.h.ah=0;
    regs.h.al=0x03;
    int86(0x10,&regs,&regs);     
}

/**********************************************************
Function:       SaveMenuBuffer

Description:    Saves a screen region to temporary BMP file for dropdown menu buffer

Calls:          

Called By:      Dropdown menu functions

Input:          int x1, y1      - Top-left coordinates
                int x2, y2      - Bottom-right coordinates

Output:         Creates BMP file in "list_temp" folder

Return:         int buffer_id   - ID of saved buffer (1-10)
                -1              - Error creating buffer
**********************************************************/
int SaveMenuBuffer(int x1, int y1, int x2, int y2)
{
    static int buffer_counter = 1;
    int i, j;
    int height = y2 - y1;
    int width = x2 - x1;
    int color;
	int imageSize = width * height * 3;
    char filename[50];
    FILE *fp;
	// Write BMP header (simplified)
	uint8_t header[54] = {
		0x42, 0x4D, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0,
		40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
    
    // Create directory if it doesn't exist
    mkdir("list_tmp");
    
	// Max menu_buffer: 10
    if(buffer_counter > 10) {
        buffer_counter = 1;
    }
    
    sprintf(filename, "list_tmp\\buf_%d.bmp", buffer_counter);
    
    // Similar to GenerateBMP but simplified for menu buffer
    fp = fopen(filename, "wb");
    if(fp == NULL) {
        return -1;
    }
    
    // Update header with actual dimensions
    *(int*)&header[18] = width;
    *(int*)&header[22] = height;
    *(int*)&header[34] = imageSize;
    *(int*)&header[2] = 54 + imageSize;
    
    fwrite(header, 1, 54, fp);
    
    // Write pixel data
    for(i = height-1; i >= 0; i--) {
        for(j = 0; j < width; j++) {
            color = Getpixel64k(x1 + j, y1 + i);
            fputc((color & 0x1F) << 3, fp);    // Blue
            fputc(((color >> 5) & 0x3F) << 2, fp); // Green
            fputc(((color >> 11) & 0x1F) << 3, fp); // Red
        }
    }
    
    fclose(fp);
    
    return buffer_counter++;
}

/**********************************************************
Function:       RestoreMenuBuffer

Description:    Restores screen region from temporary BMP file and deletes it

Calls:          

Called By:      Dropdown menu functions

Input:          int x1, y1      - Top-left coordinates
                int x2, y2      - Bottom-right coordinates
                int buffer_id   - ID of buffer to restore

Output:         Restores screen region and deletes temp file

Return:         None
**********************************************************/
void RestoreMenuBuffer(int x1, int y1, int x2, int y2, int buffer_id)
{
    char filename[50];
    FILE *fp;
    int i, j;
    int height = y2 - y1;
    int width = x2 - x1;
    uint8_t b, g, r;
    unsigned int color;
    
    sprintf(filename, "list_tmp\\buf_%d.bmp", buffer_id);
    
    fp = fopen(filename, "rb");
    if(fp == NULL) 
	{
        return;
    }
    
    // Skip BMP header
    fseek(fp, 54, SEEK_SET);
    
    // Read and restore pixels
    for(i = height - 1; i >= 0; i--) 
	{
        for(j = 0; j < width; j++) 
		{
            b = fgetc(fp);
            g = fgetc(fp);
            r = fgetc(fp);
            
            // Convert back to 16-bit color
            color = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
            Putpixel64k(x1 + j, y1 + i, color);
        }
    }
    
    fclose(fp);
    
    // Delete the temporary file
    remove(filename);
}