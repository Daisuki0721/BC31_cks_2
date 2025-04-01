#include <allfunc.h>

/*黑边圆角矩形按钮，非激活为0，激活为1，返回当前状态*/
int rounded_button(int x1, int y1, int x2, int y2, int r , int color, int state)
{
	/*根据不同状态设置颜色*/
	if(state==1)    color=34429;

	/*画出边框*/
	Circlefill(x1+r, y1+r, r+2, 0x0000);
	Circlefill(x2-r, y1+r, r+2, 0x0000);
	Circlefill(x1+r, y2-r, r+2, 0x0000);
	Circlefill(x2-r, y2-r, r+2, 0x0000);
	Line_Thick(x1, y1+r+2, x1, y2-r-2, 2, 0x0000);
	Line_Thick(x2, y1+r+2, x2, y2-r-2, 2, 0X0000);
	Line_Thick(x1+r+2, y1, x2-r-2, y1, 2, 0X0000);
	Line_Thick(x1+r+2, y2, x2-r-2, y2, 2, 0X0000);
	/*内部填色*/
	Circlefill(x1+r, y1+r, r, color);
	Circlefill(x2-r, y1+r, r, color);
	Circlefill(x1+r, y2-r, r, color);
	Circlefill(x2-r, y2-r, r, color);
	bar1(x1+r, y1, x2-r, y2, color);
	bar1(x1, y1+r, x2, y2-r, color);

	return state;
}

/*黑边圆角矩形按钮(增量型带汉字）*/
void rounded_button_d(int x, int y, int xsize, int ysize, char * str, int r, int color)
{
		/*画边框*/
		Line_Thick(x+r, y-1, x+xsize-r, y-1, 1, 0);
		Line_Thick(x-1, y+r, x-1, y+ysize-r, 1, 0);
		Line_Thick(x+r, y+ysize+1, x+xsize-r, y+ysize+1, 1, 0);
		Line_Thick(x+xsize+1, y+r, x+xsize+1, y+ysize-r, 1, 0);
		Circlefill(x+r, y+r, r+2, 0);
		Circlefill(x+xsize-r, y+r, r+2, 0);
		Circlefill(x+r, y+ysize-r, r+2, 0);
		Circlefill(x+xsize-r, y+ysize-r, r+2, 0);
		/*内部填色*/
		Circlefill(x+r, y+r, r, color);
		Circlefill(x+xsize-r, y+r, r, color);
		Circlefill(x+r, y+ysize-r, r, color);
		Circlefill(x+xsize-r, y+ysize-r, r, color);
		bar1(x+r, y, x+xsize-r, y+ysize, color);
		bar1(x, y+r, x+xsize, y+ysize-r, color);
		/*输出汉字*/
		puthz(x+(xsize-12*strlen(str)-(strlen(str)-1))/2, y+(ysize-24)/2, str, 24, 26, 0);
}

/*黑边圆角矩形按钮(增量型），输出asc字符*/
void rounded_button_asc(int x, int y, int xsize, int ysize, char * str, int r, int color)
{
		/*画边框*/
		Line_Thick(x+r, y-1, x+xsize-r, y-1, 1, 0);
		Line_Thick(x-1, y+r, x-1, y+ysize-r, 1, 0);
		Line_Thick(x+r, y+ysize+1, x+xsize-r, y+ysize+1, 1, 0);
		Line_Thick(x+xsize+1, y+r, x+xsize+1, y+ysize-r, 1, 0);
		Circlefill(x+r, y+r, r+2, 0);
		Circlefill(x+xsize-r, y+r, r+2, 0);
		Circlefill(x+r, y+ysize-r, r+2, 0);
		Circlefill(x+xsize-r, y+ysize-r, r+2, 0);
		/*内部填色*/
		Circlefill(x+r, y+r, r, color);
		Circlefill(x+xsize-r, y+r, r, color);
		Circlefill(x+r, y+ysize-r, r, color);
		Circlefill(x+xsize-r, y+ysize-r, r, color);
		bar1(x+r, y, x+xsize-r, y+ysize, color);
		bar1(x, y+r, x+xsize, y+ysize-r, color);
		/*输出字符*/
		prt_asc16(x+(xsize-8*strlen(str))/2, y+(ysize-16)/2, str, 0);
}

/**************************************
 * 在指定位置输出一个车牌头(使用puthz函数)
 * flag为车牌头代号，size为字号大小（可选16，24，32，48）
 * flag参数参考表：
 * 1 ：京    2：沪     3 ：浙    4 ：苏
 * 5 ：粤    6：鲁     7 ：晋    8 ：冀
 * 9 ：豫    10：川    11：渝    12：辽
 * 13：吉    14：黑    15：皖    16：鄂
 * 17：津    18：贵    19：云    20：桂
 * 21：琼    22：青    23：藏    24：蒙
 * 25：宁    26：甘    27：陕    28：闽
 * 29：赣    30：湘    31：港    32：澳
***************************************/
void put_carhead(int x, int y, int flag, int size, int color)
{
	char * str[32] = {"京", "沪", "浙", "苏", "粤", "鲁", "晋", "冀",
					  "豫", "川", "渝", "辽", "吉", "黑", "皖", "鄂",
					  "津", "贵", "云", "桂", "琼", "青", "藏", "蒙",
					  "宁", "甘", "陕", "闽", "赣", "湘", "港", "澳"};
	
	puthz(x, y, str[flag-1], size, size, color);

}

/*在指定位置生成一个车牌头按钮，x，y控制按钮位置，flag为车牌头代号，size控制按钮大小*/
void carhead_button(int x, int y, int flag, int size)
{
	rounded_button(x, y, x+size, y+size, NULL, 59391, 4);
	put_carhead(x+(size-24)/2, y+(size-24)/2, flag, 24, 0);
	// if(mouse_in(x1, y1, x1+size1, y1+size1))
	// {
	// 	mouse_trans(HAND);
	// 	if(mouse_press(x1, y1, x1+size1, y1+size1))
	// 	{
	// 		bar1(x2, y2, x2+size2, y2+size2, color);
	// 		put_carhead(x2+(size2-24)/2, y2+(size2-24)/2, flag, 24, 0);
	// 	}
	// 	continue;
	// }
}

/*在指定位置生成一个车牌头键盘*/
void carhead_keyboard(int x, int y)
{
	int i, j, xp, yp;
	xp = x + 17;
	yp = y + 13;

	bar1(x, y, x+410, y+210, 33808);
    bar1(x+5, y+5, x+405, y+205, 65530);

	for(i=0; i<4; i++)
	{
		for(j=0; j<8; j++)
		{
			carhead_button(xp, yp, i*8+j+1, 40);
			xp += 48;
		}
		xp = x + 17;		//x回到表头的第一列
		yp += 48;
	}
}

/*开机动画*/
void welcome_video(void)
{
	bar1(0, 0, 1024, 768, 65530);  //背景加载
	Readbmp64k(400, 250, "bmp\\hust1.bmp");	//图片加载
	puthz(400, 400, "欢迎使用", 48, 50, 0);	//信息加载
	puthz(230, 460, "校园机动车违停管理系统", 48, 50, 0);
	puthz(600, 520, "信息正在加载中……", 24, 26, 0);
	puthz(600, 550, "（第一次进入可能加载时间较长，请耐心等待）", 16, 16, 0);
	delay(1000);  //延时1秒
}

/*清理主页面*/
void clear_window(int flag)
{
	if(flag==ALLBOARD)
	{
		bar1(0, 122, 178, 768, 34429);
		bar1(182, 0, 1024, 768, 65533);
	}
	else if(flag==SIDEBOARD)
	{
		bar1(0, 122, 178, 768, 34429);
	}
	else if(flag==MAINBOARD)
	{
		bar1(182, 0, 1024, 768, 65533);
	}
}

/*画一个红色的勾*/
void red_tick(int x, int y)
{
	Line_Thick(x-2, y+12, x+6, y+20, 1, 63488);
	Line_Thick(x+6, y+20, x+22, y-2, 1, 63488);
}

/*选择用户面板并生成违停记录控面板*/
void user_select_draw(int x, int y, int sidepage)
{
	int pos, unum, i, j;
	UserList UL = {NULL, 0, 0};          //线性表
	InitUList(&UL);           //创建线性表
	ReadAllUser(&UL);         //获取所有用户

	bar1(x, y, x+460, y+240, 33808);
    bar1(x+5, y+5, x+455, y+235, 65530);

	pos = 12 * (sidepage - 1);		//计算打印区间

	if(sidepage > 1)
	{
		rounded_button_d(x+50, y+200, 80, 30, "上一页", 3, 65498);
	}
	if(pos + 12 < UL.length)
	{
		rounded_button_d(x+150, y+200, 80, 30, "下一页", 3, 65498);
	}

	for(unum = pos; (unum < pos + 12) && (unum < UL.length); unum++)
	{
		j = (unum % 12) % 4;
		i = (unum % 12) / 4;
		rounded_button_asc(x+8+i*150, y+10+j*37, 144, 30, UL.elem[unum].name, 3, 59391);
	}
	
    rounded_button_d(x+250, y+200, 80, 30, "返回", 3, 65498);
    rounded_button_d(x+350, y+200, 80, 30, "确定", 3, 65498);

	puthz(660, 15, "若要切换摄像头，请先点击返回！", 24, 25, 63488);

	DestroyUList(&UL);        //销毁线性表
}

/*选择记录面板绘制*/
void record_select_draw(int x, int y, int num)
{
	int i, j, rnum, reclistlen;
	char str[9] = {0};
	USER temp = {0};
	Record record = {0};
	UserList UL = {NULL, 0, 0};          //用户线性表
	RecList RL = {NULL, 0, 0};          //记录线性表
	InitUList(&UL);           //创建线性表
	ReadAllUser(&UL);         //获取所有用户
	temp = UL.elem[num];
	DestroyUList(&UL);        //销毁线性表

	reclistlen = ReadRecNum(temp);		//获取记录长度

	bar1(x, y, x+460, y+240, 33808);
	bar1(x+5, y+5, x+455, y+235, 65530);
	for(rnum = 0; rnum < reclistlen; rnum++)
	{
		j = (rnum % 12) % 4;
		i = (rnum % 12) / 4;
		sprintf(str, "record%d", rnum+1);
		rounded_button_asc(x+8+i*150, y+10+j*37, 144, 30, str, 3, 59391);
	}

	rounded_button_d(x+50, y+200, 150, 30, "返回主页", 3, 65498);
	if(reclistlen > 0)
	{
		rounded_button_d(x+250, y+200, 80, 30, "删除", 3, 65498);
		rounded_button_d(x+350, y+200, 80, 30, "确定", 3, 65498);
	}


	DestroyRList(&RL);        //销毁线性表
}

/*高亮按钮切换函数(用户)*/
void highlight_switch_user(int unum, int sidepage)
{
    static int last = 0;    //上一次点击的按钮
    static int lastsidepage = 1;    //上一次的页面
    UserList UL = {NULL, 0, 0};          //用户线性表
    InitUList(&UL);           //创建线性表
    ReadAllUser(&UL);         //获取所有用户

	mouse_off(&mouse);

    if(lastsidepage == sidepage)        //如果不换页，重绘深色按钮
    {
        rounded_button_asc(15, 150+(last%7)*75, 145, 60, UL.elem[last].name, 5, 65498);
    }
    else
    {
        lastsidepage = sidepage;
    }
    last = unum;
    
	if(lastsidepage)
	{
		rounded_button_asc(15, 150+(unum%7)*75, 145, 60, UL.elem[unum].name, 5, 65504);
	}
    
	mouse_on(mouse);

    DestroyUList(&UL);        //销毁线性表
}

/*高亮按钮切换函数（地点）*/
void highlight_switch_area(int i, int sidepage)
{
	static int last = 0;    //上一次点击的按钮
    static int lastsidepage = 1;    //上一次的页面
	AREA AP[14];
	area_read(AP);

	mouse_off(&mouse);

    if(lastsidepage == sidepage)        //如果不换页，重绘深色按钮
    {
        rounded_button_d(15, 150+(last%7)*75, 145, 60, AP[last].name, 5, 65498);
    }
    else
    {
        lastsidepage = sidepage;
    }
    last = i;
    
	if(lastsidepage)
	{
		rounded_button_d(15, 150+(i%7)*75, 145, 60, AP[i].name, 5, 65504);
	}
    
	mouse_on(mouse);
}

/*在指定位置输出一个星期几(使用puthz函数)*/
/*flag为星期几代号，size为字号大小（可选16，24，32，48）*/
void put_week(int x, int y, int flag, int size, int color)
{
	char * str[7] = {"星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日"};
	
	puthz(x, y, str[flag-1], size, size, color);

}

/*在指定位置生成一个星期几按钮，x，y控制按钮位置，flag为星期几代号，size控制按钮大小*/
void week_button(int x, int y, int flag, int size)
{
	rounded_button(x, y, x+size*3, y+size, NULL, 59391, 4);
	put_week(x+(size-24)*3/2, y+(size-24)/2, flag, 24, 0);
}

/*在指定位置生成一个星期键盘*/
void week_keyboard(int x, int y)
{
	int i, j, xp, yp;
	xp = x + 17;
	yp = y + 13;

	bar1(x, y, x+282, y+210, 33808);
    bar1(x+5, y+5, x+277, y+205, 65530);

	for(i=0; i<4; i++)
	{
		for(j=0; j<2; j++)
		{	
			if(i == 3 && j == 1)
			{
				break;		//只画七个按钮
			}
			week_button(xp, yp, i*2+j+1, 40);
			xp += 128;
		}
		xp = x + 17;
		yp += 48;
	}
}


/*系统时间显示*/
void sys_time(int x, int y)
{
    static int cursec = 0;
    static char * week[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    char str[80] = "\0";
    char temp[10] = "\0";
    time_t now = time(NULL);
	struct tm *local = localtime(&now);

    if(cursec != local->tm_sec)
    {
        cursec = local->tm_sec;
        sprintf(temp, "%04d", local->tm_year + 1900);
        strcat(str, temp);
        strcat(str, "/");
        sprintf(temp, "%02d", local->tm_mon + 1);
        strcat(str, temp);
        strcat(str, "/");
        sprintf(temp, "%02d", local->tm_mday);
        strcat(str, temp);
        strcat(str, " ");
        sprintf(temp, "%02d", local->tm_hour);
        strcat(str, temp);
        strcat(str, ":");
        sprintf(temp, "%02d", local->tm_min);
        strcat(str, temp);
        strcat(str, ":");
        sprintf(temp, "%02d", local->tm_sec);
        strcat(str, temp);
        strcat(str, " ");
        strcat(str, week[local->tm_wday]);

        mouse_off(&mouse);
        bar1(x, y, x+250, y+16, 65533);
        prt_asc16(x, y, str, 0);
        mouse_on(mouse);
    }
}