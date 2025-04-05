#include <allfunc.h>

/*用户处理与申诉面板*/
void user_dispose_panel(int * page, int unum)
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

    g_user_dispose_panel(sidepage, user);

    mouse_on(mouse);

    user_record_dispose_ctrl(page, &sidepage, user);
}

/*用户处理与申诉面板控制函数*/
void user_record_dispose_ctrl(int * page, int * sidepage, USER user)
{
    int rnum = 0, pnum = 0;	        //记录编号

    while(1)
    {
        mouse_off(&mouse);
        g_user_dispose_panel(*sidepage, user);
        mouse_on(mouse);
        highlight_switch_appeal(user, pnum, *sidepage);   //高亮按钮切换

        while(1)
        {
            mouse_show(&mouse);

            appeal_info_display_ctrl(user, &pnum, &rnum, sidepage, page);  //记录信息显示/控制
            break;
        }
        if(!*page)     //如果选择退出，跳出循环
        {
            break;  
        }
    }
}

/*用户处理与申诉面板绘制函数*/
void g_user_dispose_panel(int sidepage, USER user)
{
    int i, pos, rnum;
    char str[20] = {0};
    RecList APL = {NULL, 0, 0};          //记录线性表

    RecListToAppealList(user, &APL);         //获取所有申诉记录
    pos = 7 * (sidepage - 1);		//计算控制区间

    clear_window(ALLBOARD);

    for(i=0, rnum = pos; (rnum < pos + 7) && (rnum < APL.length); rnum++, i++)       //控制翻页
    {
        sprintf(str, "appeal%d", rnum+1);
        rounded_button_asc(15, 150+i*75, 145, 60, str, 5, 65498);
        if(APL.elem[rnum].appeal_state == 0)
        {
            puthz(110, 150+i*75+2, "未处理", 16, 16, 63488);
        }
        else if(APL.elem[rnum].appeal_state == 2)
        {
            puthz(110, 150+i*75+2, "申诉中", 16, 16, 63488);
        }
        else if(APL.elem[rnum].appeal_state == 3)
        {
            puthz(94, 150+i*75+2, "申诉成功", 16, 16, 2016);
        }
        else if(APL.elem[rnum].appeal_state == 4)
        {
            puthz(94, 150+i*75+2, "申诉失败", 16, 16, 63488);
        }
        else if(APL.elem[rnum].appeal_state == 7)
        {
            puthz(94, 150+i*75+2, "申诉撤销", 16, 16, 63488);
        }
    }
	if(!(sidepage == 1))
	{
		prt_hz16(20, 680, "上一页", 63519, "hzk\\hzk16");
	}
	if(pos + 7 < APL.length)
	{
		prt_hz16(100, 680, "下一页", 63519, "hzk\\hzk16");
	}
    prt_hz16(53, 720, "返回上级", 63519, "hzk\\hzk16");

    DestroyRList(&APL);      //销毁线性表
}

/*用户记录信息显示控制函数*/
void appeal_info_display_ctrl(USER user, int * pnum, int * rnum, int * sidepage, int * page)
{
    int i, k;
    int esc = 0, flag = 0, pos = 0, button1 = 0, button2 = 0;
    RecList APL = {NULL, 0, 0};          //申诉线性表

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    clear_window(MAINBOARD);
    if(user.appeal_times > 0)
    {
        appeal_display_user(200, 50, user, *pnum);   //打印记录内容
    }

    RecListToAppealList(user, &APL);         //获取所有申诉记录

    rounded_button_d(500, 10, 220, 35, "查看记录状态统计", 5, 34429);
    if(APL.elem[*pnum].appeal_state == 0)
    {
        rounded_button_d(800, 200, 180, 35, "确认", 5, 65530);
        rounded_button_d(800, 250, 180, 35, "我要申诉", 5, 65530);
        button1 = 1;
        button2 = 1;
    }
    else if(APL.elem[*pnum].appeal_state == 3 && APL.elem[*pnum].appeal_state == 4)
    {
        rounded_button_d(800, 200, 180, 35, "确认", 5, 65530);
        button1 = 1;
    }
    else if(APL.elem[*pnum].appeal_state == 2)
    {
        rounded_button_d(800, 250, 180, 35, "撤销申诉", 5, 65530);
        button2 = 1;
    }
    else if(APL.elem[*pnum].appeal_state == 7)
    {
        rounded_button_d(800, 200, 180, 35, "确认", 5, 65530);
        rounded_button_d(800, 250, 180, 35, "重新申诉", 5, 65530);
        button1 = 1;
        button2 = 1;
    }

    mouse_on(mouse);

    pos = 7 * (*sidepage - 1);		    //计算控制区间

    while(1)
    {
        if(APL.length == 0)   //如果没有邮件
        {
            puthz(15, 150+2, "当前没有需要", 24, 25, 0);
            puthz(15, 150+2+24, "处理的记录！", 24, 25, 0);
        }
        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);

            for(k = 0; (k < 7) && (k+(*sidepage-1)*7) < APL.length; k++)          //申诉选择按钮
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(15, 150+k*75, 160, 210+k*75))
                    {
                        *pnum = k + (*sidepage-1)*7;      //当前点击按钮的位置，同时也是申诉编号
                        *rnum = APL.elem[*pnum].id - 1;     //申诉在原记录线性表中的位置编号
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

            if(mouse_in(500, 10, 590+220, 10+35))   //记录状态统计
            {
                mouse_trans(HAND);
                if(mouse_press(500, 10, 590+220, 10+35))
                {
                    RecState_list(500, 50, user);   
                    delay(200);
                    break;
                }
                continue;
            }

            if(button1)     //如果有确认按钮
            {
                if(mouse_in(800, 200, 800+180, 200+35))
                {
                    mouse_trans(HAND);
                    if(mouse_press(800, 200, 800+180, 200+35))
                    {
                        if(APL.elem[*pnum].appeal_state == 0 
                            && APL.elem[*pnum].appeal_state == 7)   //未申诉或申诉撤销
                        {
                            APL.elem[*pnum].appeal_state = 1;   //已确认  
                        }
                        else if(APL.elem[*pnum].appeal_state = 3)  //申诉成功
                        {
                            APL.elem[*pnum].appeal_state = 5;   //申诉成功已确认   
                        }
                        else if(APL.elem[*pnum].appeal_state == 4)  //申诉失败
                        {
                            APL.elem[*pnum].appeal_state = 6;   //申诉失败已确认  
                        }
                        UpdataRec(user, APL.elem[*pnum], APL.elem[*pnum].id-1); 
                        puthz(800, 172, "已确认！即将返回上级", 24, 25, 0);
                        delay(2000);
                        *pnum = 0;   //重新选择申诉
                        esc = 1;
                        delay(200);
                        break;
                    }
                    continue;
                }
            }

            if(button2)     //如果有申诉操作按钮
            {
                if(mouse_in(800, 250, 800+180, 250+35))
                {
                    mouse_trans(HAND);
                    if(mouse_press(800, 250, 800+180, 250+35))
                    {
                        if(APL.elem[*pnum].appeal_state == 0)   //未申诉
                        {
                            APL.elem[*pnum].appeal_state = 2;   //申诉中
                            user.appeal_times++;   //申诉次数加1
                            puthz(800, 172, "已申诉！", 24, 25, 0);
                            delay(2000);
                        }
                        else if(APL.elem[*pnum].appeal_state == 2)  //申诉中
                        {
                            APL.elem[*pnum].appeal_state = 7;   //撤销申诉  
                            user.appeal_times--;   //申诉次数减1
                            puthz(800, 172, "已撤销申诉！", 24, 25, 0);
                            delay(2000);
                        }
                        else if(APL.elem[*pnum].appeal_state == 7)  //撤销申诉
                        {
                            APL.elem[*pnum].appeal_state = 2;   //重新申诉  
                            user.appeal_times++;   //申诉次数加1
                            puthz(800, 172, "已重新申诉！", 24, 25, 0);
                            delay(2000);
                        }
                        UpdataRec(user, APL.elem[*pnum], APL.elem[*pnum].id-1); 
                        UpdataUser(user);   //更新用户信息
                        esc = 1;
                        delay(200);
                        break;
                    }
                    continue;
                }
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
            DestroyRList(&APL);      //销毁线性表
            mouse_on(mouse);
            break;
        }
    }
}

/*用户申诉信息显示函数*/
void appeal_display_user(int x, int y, USER user, int rnum)
{
    Record appeal = {0};
    RecList APL = {NULL, 0, 0};          //申诉线性表
    AREA AP[14] = {0};
    char str[24] = {0};
    char * week[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

    RecListToAppealList(user, &APL);         //获取所有申诉
    appeal = APL.elem[rnum];           //获取申诉
    DestroyRList(&APL);            //销毁线性表

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
            appeal.year, appeal.month, appeal.day, week[appeal.week], appeal.hour, appeal.minute, appeal.second);
    put_asc16_size(x+10+33*5, y+10+34*2, 2, 2, str, 0);
    puthz(x+10+33*5, y+10+34*3, AP[appeal.place].name, 32, 33, 0);
    if(appeal.readif == 0)
    {
        puthz(x+10+33*7, y+10+34*4, "未读", 32, 33, 0);
    }
    else if(appeal.readif == 1)
    {
        puthz(x+10+33*7, y+10+34*4, "已读", 32, 33, 0);
    }
    else if(appeal.readif == 2)
    {
        puthz(x+10+33*7, y+10+34*4, "更新", 32, 33, 0);
    }
    if(appeal.appeal_state == 0)
    {
        puthz(x+10+33*8, y+10+34*5, "未申诉", 32, 33, 0);
    }
    else if(appeal.appeal_state == 2)
    {
        puthz(x+10+33*8, y+10+34*5, "申诉中", 32, 33, 64384);
    }
    else if(appeal.appeal_state == 3)
    {
        puthz(x+10+33*8, y+10+34*5, "申诉成功", 32, 33, 2016);
    }
    else if(appeal.appeal_state == 4)
    {
        puthz(x+10+33*8, y+10+34*5, "申诉失败", 32, 33, 63488);
    }
    else if(appeal.appeal_state == 7)
    {
        puthz(x+10+33*8, y+10+34*5, "撤销申诉", 32, 33, 0);
    }
}

