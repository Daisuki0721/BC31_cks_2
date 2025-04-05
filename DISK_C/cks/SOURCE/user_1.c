#include <allfunc.h>

/*用户违停记录面板*/
void user_record_panel(int * page, int unum)
{
    int sidepage = 1;	//当前侧栏页码
    UserList UL = {NULL, 0, 0};          //用户线性表
    USER user = {0};	//用户
    InitUList(&UL);           //创建线性表
    ReadAllUser(&UL);         //获取所有用户
    user = UL.elem[unum];       //得到当前用户
    DestroyUList(&UL);        //销毁线性表

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    g_user_record_panel(sidepage, user);

    mouse_on(mouse);

    user_record_panel_ctrl(page, &sidepage, user);
}

/*用户邮箱面板控制函数*/
void user_record_panel_ctrl(int * page, int * sidepage, USER user)
{
    static int current_sidepage = 1;	//当前侧栏页码
    int rnum = 0;

    while(1)
    {
        if(current_sidepage != *sidepage)    //如果换页，重绘侧栏   
        {
            mouse_off(&mouse);
            g_user_record_panel(*sidepage, user);
            current_sidepage = *sidepage;
            mouse_on(mouse);
        }
        else
        {
            highlight_switch_record(user, rnum, *sidepage);   //高亮按钮切换
        }
        while(1)
        {
            mouse_show(&mouse);

            record_info_display_ctrl(user, &rnum, sidepage, page);  //记录信息显示/控制
            break;
        }
        if(!*page)     //如果选择退出，跳出循环
        {
            current_sidepage = 1;
            break;  
        }
    }
}

/*用户记录面板绘制函数*/
void g_user_record_panel(int sidepage, USER user)
{
    int i, pos, rnum;
    char str[20] = {0};
    RecList RL = {NULL, 0, 0};          //记录线性表

    ReadAllRec(user, &RL);         //获取所有记录
    pos = 7 * (sidepage - 1);		//计算控制区间

    clear_window(ALLBOARD);

    for(i=0, rnum = pos; (rnum < pos + 7) && (rnum < RL.length); rnum++, i++)       //控制翻页
    {
        sprintf(str, "record%d", rnum+1);
        rounded_button_asc(15, 150+i*75, 145, 60, str, 5, 65498);
    }
	if(!(sidepage == 1))
	{
		prt_hz16(20, 680, "上一页", 63519, "hzk\\hzk16");
	}
	if(pos + 7 < RL.length)
	{
		prt_hz16(100, 680, "下一页", 63519, "hzk\\hzk16");
	}
    prt_hz16(53, 720, "返回上级", 63519, "hzk\\hzk16");

    DestroyRList(&RL);      //销毁线性表
}

/*用户记录信息显示控制函数*/
void record_info_display_ctrl(USER user, int * rnum, int * sidepage, int * page)
{
    int i, k, esc = 0, flag = 0, pos = 0;
    RecList RL = {NULL, 0, 0};          //记录线性表

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    clear_window(MAINBOARD);
    if(user.record_id > 0)
    {
        record_display_user(200, 50, user, *rnum);   //打印记录内容
    }
    rounded_button_d(500, 10, 220, 35, "查看记录状态统计", 5, 34429);

    mouse_on(mouse);

    ReadAllRec(user, &RL);         //获取所有记录
    pos = 7 * (*sidepage - 1);		//计算控制区间

    while(1)
    {
        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);
            if(RL.length == 0)   //如果没有邮件
            {
                puthz(15, 150+2, "当前没有记录！", 24, 25, 0);
            }

            for(k = 0; (k < 7) && (k+(*sidepage-1)*7) < RL.length; k++)          //邮件选择按钮
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(15, 150+k*75, 160, 210+k*75))
                    {
                        *rnum = k + (*sidepage-1)*7;      //邮件编号
                        esc = 1;
                        delay(200);
                        break;
                    }
                    break;
                }
            }
            if(esc)                                 //如果点击返回，则退出循环
            {
                break;
            }
            if(flag)
            {
                flag = 0;
                continue;
            }

            if(mouse_in(500, 10, 590+220, 10+35))
            {
                mouse_trans(HAND);
                if(mouse_press(500, 10, 590+220, 10+35))
                {
                    RecState_list(500, 50, user);   //记录状态统计
                    delay(200);
                    break;
                }
                continue;
            }

            if((mouse_in(20, 680, 20+24*3, 680+24)) && (*sidepage > 1))  //控制翻页
            {
                mouse_trans(HAND);
                if(mouse_press(20, 680, 20+24*3, 680+24))
                {
                    (*sidepage)--;
                    esc = 1;
                    delay(200);
                    break;
                }
                continue;
            }

            if((mouse_in(100, 680, 100+24*3, 680+24)) && (*sidepage * 7 <  ReadRecNum(user)))  //控制翻页
            {
                mouse_trans(HAND);
                if(mouse_press(100, 680, 100+24*3, 680+24))
                {
                    (*sidepage)++;
                    esc = 1;
                    delay(200);
                    break;
                }
                continue;
            }            
            
            if(mouse_in(53, 720, 53+16*4, 720+16))      //如果点击返回主页
            {
                mouse_trans(HAND);
                if(mouse_press(53, 720, 53+16*4, 720+16))
                {
                    *page=0;
                    esc = 1;
                    *sidepage = 1;
                    delay(200);
                    break;
                }
                continue;
            }
            mouse_trans(CURSOR);
            delay(15);
        }
        if(esc)               //如果点击返回，则退出循环
        {
            mouse_off(&mouse);
            clear_window(MAINBOARD);
            DestroyRList(&RL);      //销毁线性表
            mouse_on(mouse);
            break;
        }
    }
}

/*用户记录信息显示函数*/
void record_display_user(int x, int y, USER user, int rnum)
{
    Record rec = {0};
    RecList RL = {NULL, 0, 0};          //记录线性表
    AREA AP[14] = {0};
    char str[24] = {0};
    char * week[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

    ReadAllRec(user, &RL);         //获取所有记录
    rec = RL.elem[rnum];           //获取记录
    DestroyRList(&RL);            //销毁线性表

    area_read(AP);          //读取地点信息

    bar1(x+10, y, x+10+800, y+400, 65533);   //绘制背景
    puthz(x+10, y, "记录信息", 32, 33, 0);
    puthz(x+10, y+10+34, "违停编号：", 32, 33, 0);
    puthz(x+10, y+10+2*34, "违停时间：", 32, 33, 0);
    puthz(x+10, y+10+3*34, "违停地点：", 32, 33, 0);
    puthz(x+10, y+10+4*34, "邮件阅读状态：", 32, 33, 0);
    puthz(x+10, y+10+5*34, "确认、申诉状态：", 32, 33, 0);
    puthz(x+10, y+10+6*34, "抓拍照片：", 32, 33, 0);
    sprintf(str, "%d", rnum+1);
    put_asc16_size(x+10+33*5, y+10+34, 2, 2, str, 0);
    sprintf(str, "%04d/%02d/%02d %s %02d:%02d:%02d",
            rec.year, rec.month, rec.day, week[rec.week], rec.hour, rec.minute, rec.second);
    put_asc16_size(x+10+33*5, y+10+34*2, 2, 2, str, 0);
    puthz(x+10+33*5, y+10+34*3, AP[rec.place].name, 32, 33, 0);
    if(rec.readif == 0)
    {
        puthz(x+10+33*7, y+10+34*4, "未读", 32, 33, 0);
    }
    else if(rec.readif == 1)
    {
        puthz(x+10+33*7, y+10+34*4, "已读", 32, 33, 0);
    }
    else if(rec.readif == 2)
    {
        puthz(x+10+33*7, y+10+34*4, "更新", 32, 33, 0);
    }
    if(rec.appeal_state == 0)
    {
        puthz(x+10+33*8, y+10+34*5, "未申诉", 32, 33, 0);
    }
    else if(rec.appeal_state == 1)
    {
        puthz(x+10+33*8, y+10+34*5, "已确认", 32, 33, 0);
    }
    else if(rec.appeal_state == 2)
    {
        puthz(x+10+33*8, y+10+34*5, "申诉中", 32, 33, 64384);
    }
    else if(rec.appeal_state == 3)
    {
        puthz(x+10+33*8, y+10+34*5, "申诉成功", 32, 33, 2016);
    }
    else if(rec.appeal_state == 4)
    {
        puthz(x+10+33*8, y+10+34*5, "申诉失败", 32, 33, 63488);
    }
    else if(rec.appeal_state == 5)
    {
        puthz(x+10+33*8, y+10+34*5, "申诉成功已确认", 32, 33, 0);
    }
    else if(rec.appeal_state == 6)
    {
        puthz(x+10+33*8, y+10+34*5, "申诉失败已确认", 32, 33, 0);
    }
    else if(rec.appeal_state == 7)
    {
        puthz(x+10+33*8, y+10+34*5, "撤销申诉", 32, 33, 0);
    }
}

/*违停状态统计下拉菜单*/
void RecState_list(int x, int y, USER user)
{
    int buffer_id;
    mouse_off(&mouse);

    buffer_id = SaveMenuBuffer(x-1, y-1, x+470+1, y+280+1);

    bar1(x, y, x+470, y+280, 33808);
    bar1(x+5, y+5, x+465, y+275, 65530);
            
    record_state_display(x+5, y+15, user, 0);   //显示记录状态

    mouse_on(mouse);

    while(1)
    {
        sys_time(200, 20);
        mouse_show(&mouse);

        if(mouse_press(0, 0, 1024, 768))   //如果再次点击，则退出
        {
            mouse_off(&mouse);
            RestoreMenuBuffer(x-1, y-1, x+470+1, y+280+1, buffer_id);   //恢复菜单
            mouse_on(mouse);
            ClearMenuBuffer();   //清除菜单缓存
            return;
        }

        mouse_trans(CURSOR);
        delay(15);
    }
}