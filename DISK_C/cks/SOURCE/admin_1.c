#include <allfunc.h>

/*管理员查看摄像头面板*/
void admin_monitor_panel(int * page)
{
    int sidepage = 1;

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    g_admin_monitor_panel(sidepage);

    mouse_on(mouse);

    admin_monitor_panel_ctrl(&sidepage, page);

}

/*摄像头界面侧栏控制*/
void admin_monitor_panel_ctrl(int * sidepage, int * page)
{
    static int current_sidepage = 1;
    int i = 0, flag = 0, num = -1;
    while(1)
    {
        if(current_sidepage != *sidepage)    //如果换页，重绘侧栏
        {
            mouse_off(&mouse);
            mouse_trans(CURSOR);
            g_admin_monitor_panel(*sidepage);
            current_sidepage = *sidepage;
            mouse_on(mouse);
        }
        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);
            for(i=0; i<7; i++)
            {
                if(mouse_in(15, 150+i*75, 160, 210+i*75))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(15, 150, 160, 210+i*75))
                    {
                        monitor_display(i+(*sidepage-1)*7, *sidepage);
                        num = i+(*sidepage-1)*7;      //摄像头编号
                        delay(200);
                        break;
                    }
                    break;
                }
            }
            if(mouse_in(500, 15, 620, 45))
            {
                mouse_trans(HAND);
                if(mouse_press(500, 15, 620, 45))
                {
                    if(num == -1)
                    {
                        puthz(640, 15, "请先选择摄像头！", 24, 25, 0);
                        delay(2000);
                        bar1(640, 15, 640+200, 15+25, 65533);
                    }
                    else
                    {
                        CreateRec_monitor(num);
                    }
                }
                continue;
            }
            if(flag)
            {
                flag = 0;
                continue;
            }
            if(mouse_in(20, 680, 20+24*3, 680+24) && (*sidepage != 1))  //控制翻页
            {
                mouse_trans(HAND);
                if(mouse_press(20, 680, 20+24*3, 680+24))
                {
                    (*sidepage)--;
                    delay(200);
                    break;
                }
                continue;
            }
            if(mouse_in(100, 680, 100+24*3, 680+24) && (*sidepage !=2))
            {
                mouse_trans(HAND);
                if(mouse_press(100, 680, 100+24*3, 680+24))
                {
                    (*sidepage)++;
                    delay(200);
                    break;
                }
                continue;
            }            
            if(mouse_in(53, 720, 53+16*4, 720+16))
            {
                mouse_trans(HAND);
                if(mouse_press(53, 720, 53+16*4, 720+16))
                {
                    *page=0;
                    delay(200);
                    break;
                }
                continue;
            }
            mouse_trans(CURSOR);
            delay(15);
        }
        if(!*page)     //如果选择退出，跳出循环
        {
            current_sidepage = 1;
            break;  
        }
    }
}

/*绘制管理摄像头面板*/
void g_admin_monitor_panel(int sidepage)
{
    int i;
    AREA AP[14];
    area_read(AP);          //读取地点信息
    clear_window(ALLBOARD);
    rounded_button_d(500, 15, 120, 30, "生成记录", 5, 34429);
    for(i=0; i<7; i++)
    {
        rounded_button_d(15, 150+i*75, 145, 60, AP[i+(sidepage-1)*7].name, 5, 65498);
    }

    if(!(sidepage == 1))
        prt_hz16(20, 680, "上一页", 63519, "hzk\\hzk16");
    else if(!(sidepage == 2))
        prt_hz16(100, 680, "下一页", 63519, "hzk\\hzk16");
    prt_hz16(53, 720, "返回上级", 63519, "hzk\\hzk16");
}

/*摄像头信息显示*/
void monitor_display(int i, int sidepage)
{
    int j;      //计数循环
    static int last = 0;    //上一次点击的按钮
    static int lastsidepage = 1;    //上一次的页面
    static char * week[7] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
    AREA AP[14];
    char temp[3];
    area_read(AP);          //读取地点信息

    mouse_off(&mouse);
    mouse_trans(CURSOR);

    clear_window(MAINBOARD);

    rounded_button_d(500, 15, 120, 30, "生成记录", 5, 34429);
    if(lastsidepage == sidepage)        //如果不换页，重绘深色按钮
    {
        rounded_button_d(15, 150+(last%7)*75, 145, 60, AP[last].name, 5, 65498);
    }
    else
    {
        lastsidepage = sidepage;
    }
    last = i;
    
    rounded_button_d(15, 150+(i%7)*75, 145, 60, AP[i].name, 5, 65504);

    Readbmp64k(186, 50, AP[i].path);

    if(!AP[i].allnp)
    {
        puthz(186, 530, "是否为全路段禁停：是", 16, 17, 0);
    }
    else
    {
        puthz(186, 530, "是否为全路段禁停：否", 16, 17, 0);
        puthz(186, 555, "违停时间段　　起始时间　　终止时间", 16, 17, 0);
        for(j=0; j<7; j++)
        {
            puthz(186+17, 580 + j*25, week[j], 16, 17, 0);
            prt_time(297, 580 + j*25, AP[i].timest[j]);
            prt_time(400, 580 + j*25, 86400);
        }
    }

    mouse_on(mouse);
}


/*选择用户并生成违停记录*/
void CreateRec_monitor(int num)
{
    int sidepage = 1;

    mouse_off(&mouse);

    user_select_draw(550, 520, sidepage);

    mouse_on(mouse);

    user_select_ctrl(550, 520, num, &sidepage);
}

/*选择用户面板控制*/
void user_select_ctrl(int x, int y, int num, int * sidepage)
{
	int pos, unum, i, j, last;
	UserList UL = {NULL, 0, 0};          //线性表
    USER temp = {0};
    static int current_sidepage = 1;
    int  flag = 0, esc = 0;
	InitUList(&UL);           //创建线性表
	ReadAllUser(&UL);         //获取所有用户

	pos = 12 * (*sidepage - 1);		//计算控制区间
    last = UL.length / 12 + 1;		//计算总页数

    while(1)
    {
        if(current_sidepage != *sidepage)    //如果换页，重绘侧栏
        {
            mouse_off(&mouse);
            mouse_trans(CURSOR);
            user_select_draw(550, 520, *sidepage);
            current_sidepage = *sidepage;
            mouse_on(mouse);
            pos = 12 * (*sidepage - 1);       //重新计算控制区间
        }
        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);

            for(unum = pos; (unum < pos + 12) && (unum < UL.length); unum++)
            {
                j = (unum % 12) % 4;
                i = (unum % 12) / 4;
                if(mouse_in(x+8+i*150, y+10+j*37, x+8+i*150+144, y+10+j*37+30))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(x+8+i*150, y+10+j*37, x+8+i*150+144, y+10+j*37+30))
                    {        
                        temp = UL.elem[unum];
                        bar1(x+8, y+158, x+452, y+158+30, 65530);
                        puthz(x+8, y+164, "当前选择用户：", 16, 17, 0);
                        prt_asc16(x+128, y+164, temp.name, 0);
                    }
                    continue;;
                }
            }
            if(flag)
            {
                flag = 0;
                continue;
            }

            if((*sidepage > 1) && (UL.length > 12))  //控制翻页
            {
                if(mouse_in(x+50, y+200, x+130, y+230))
                {
                    mouse_trans(HAND);
                    if(mouse_press(x+50, y+200, x+130, y+230))
                    {
                        (*sidepage)--;
                    }
                    break;
                }
            }
            if(*sidepage < last)
            {
                if(mouse_in(x+150, y+200, x+230, y+230))
                {
                    mouse_trans(HAND);
                    if(mouse_press(x+150, y+200, x+230, y+230))
                    {
                        (*sidepage)++;
                    }
                    break;
                }
            }

            if(mouse_in(x+250, y+200, x+250+80, y+200+30))  //如果点击返回
            {
                mouse_trans(HAND);
                if(mouse_press(x+250, y+200, x+250+80, y+200+30))
                {
                    esc = 1;
                    delay(200);
                    break;
                }
                continue;
            }
            if(mouse_in(x+350, y+200, x+350+80, y+200+30))  //如果点击确定
            {
                mouse_trans(HAND);
                if(mouse_press(x+350, y+200, x+350+80, y+200+30))
                {
                    if(temp.name[0] == '\0')
                    {
                        bar1(x+8, y+158, x+452, y+158+30, 65530);
                        puthz(x+8, y+164, "请先选择用户！", 16, 17, 0);
                        break;
                    }
                    CreateRec(temp, num, 12);
                    bar1(x+8, y+158, x+452, y+158+30, 65530);
                    puthz(x+8, y+164, "记录保存成功！", 16, 17, 0);
                    esc = 1;
                    delay(2500);
                    break;
                }
                continue;
            }
            mouse_trans(CURSOR);
            delay(15);
        }
        if(esc)     //如果选择退出，跳出循环
        {
            mouse_off(&mouse);
            bar1(x, y, x+460, y+240, 65533);
            bar1(640, 15, 640+380, 15+25, 65533);
            mouse_on(mouse);
            current_sidepage = 1;
            break;  
        }
    }

	DestroyUList(&UL);        //销毁线性表
}

