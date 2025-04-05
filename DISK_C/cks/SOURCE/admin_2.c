#include <allfunc.h>

/*管理员违停处理面板*/
void admin_record_panel(int * page)
{
    static int sidepage = 1;

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    g_admin_record_panel(sidepage);   

    mouse_on(mouse);
    
    admin_record_panel_ctrl(&sidepage, page);     
}

/*管理员违停处理面板控制*/
void admin_record_panel_ctrl(int * sidepage, int * page)
{
    static int current_sidepage = 1;
    int i = 0, flag = 0, num = 0, esc = 0;
    int last_user_num = 0;
    USER last_user = {0}, now_user = {0};	//上一个用户和当前用户

    while(1)
    {
        if(current_sidepage != *sidepage)    //如果换页，重绘侧栏
        {
            mouse_off(&mouse);
            g_admin_record_panel(*sidepage);

            current_sidepage = *sidepage;
            mouse_on(mouse);
        } 
        else
        {
            last_user_num = highlight_switch_user(num, *sidepage, &last_user, &now_user);   //高亮按钮切换
            appeal_new_confirm(now_user, 155, 150+(num%7)*75+5);            //申诉红点(当前用户)
            appeal_new_confirm(last_user, 155, 150+(last_user_num%7)*75+5);   //申诉红点(上一个用户)
        } 

        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);

            record_select_ctrl(560, 5, &num, sidepage, page);   //记录选择面板
            break;
        }
        if(!*page)     //如果选择退出，跳出循环
        {
            current_sidepage = 1;
            break;  
        }
    }
}

/*绘制管理记录面板*/
void g_admin_record_panel(int sidepage)
{
    int i, pos, unum;
    UserList UL = {NULL, 0, 0};          //用户线性表
    InitUList(&UL);           //创建线性表
    ReadAllUser(&UL);         //获取所有用户
    pos = 7 * (sidepage - 1);		//计算控制区间

    clear_window(ALLBOARD);
    for(i=0, unum = pos; (unum < pos + 7) && (unum < UL.length); unum++, i++)       //控制翻页
    {
        rounded_button_asc(15, 150+i*75, 145, 60, UL.elem[unum].name, 5, 65498);
        appeal_new_confirm(UL.elem[unum], 155, 150+i*75+5);   //申诉红点
    }
	if(!(sidepage == 1))
	{
		prt_hz16(20, 680, "上一页", 63519, "hzk\\hzk16");
	}
	if(pos + 7 < UL.length)
	{
		prt_hz16(100, 680, "下一页", 63519, "hzk\\hzk16");
	}
    prt_hz16(53, 720, "返回上级", 63519, "hzk\\hzk16");

    DestroyUList(&UL);
}

/*用户信息显示(精简版)*/
void userinfo_display_short(int unum)
{
    char str[3];
    USER temp = {0};
    UserList UL = {NULL, 0, 0};          //用户线性表
    InitUList(&UL);           //创建线性表
    ReadAllUser(&UL);         //获取所有用户
    temp = UL.elem[unum];
    DestroyUList(&UL);          //销毁线性表
    
    mouse_off(&mouse);

    prt_hz16(200, 50, "用户信息", 63519, "hzk\\hzk16");
    prt_hz16(200+4*16, 76, "用户名：", 63519, "hzk\\hzk16");
    prt_asc16(330, 76, temp.name, 0);
    prt_hz16(200+4*16, 102, "车牌头：", 63519, "hzk\\hzk16");
    put_carhead(330, 102, temp.carhead, 16, 0);
    prt_asc16(330+18, 102, temp.carbody, 0);
    prt_hz16(200, 128, "是否为校内人员：", 63519, "hzk\\hzk16");
    if(temp.ifin)
    {
        prt_hz16(330, 128, "是", 0, "hzk\\hzk16");
    }
    else
    {
        prt_hz16(330, 128, "否", 0, "hzk\\hzk16");
    }
    prt_hz16(200+16, 154, "违停记录次数：", 63519, "hzk\\hzk16");
    itoa(temp.record_times, str, 10);
    prt_asc16(330, 154, str, 0);
    prt_hz16(200+3*16, 180, "申诉次数：", 63519, "hzk\\hzk16");
    itoa(temp.appeal_times, str, 10);
    prt_asc16(330, 180, str, 0);
}

/*记录信息显示（32号字，用puthz函数）*/
void record_display_admin(int x, int y, Record rec)
{
    AREA AP[14] = {0};
    char str[24] = {0};
    char * week[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    area_read(AP);          //读取地点信息

    bar1(x+10, y, x+10+800, y+180, 65533);   //绘制背景
    puthz(x+10, y, "记录信息", 32, 33, 0);
    puthz(x+10, y+10+34, "违停时间：", 32, 33, 0);
    puthz(x+10, y+10+2*34, "违停地点：", 32, 33, 0);
    puthz(x+10, y+10+3*34, "用户阅读状态：", 32, 33, 0);
    puthz(x+10, y+10+4*34, "确认、申诉状态：", 32, 33, 0);
    sprintf(str, "%04d/%02d/%02d %s %02d:%02d:%02d",
            rec.year, rec.month, rec.day, week[rec.week], rec.hour, rec.minute, rec.second);
    put_asc16_size(x+10+33*5, y+10+34, 2, 2, str, 0);
    puthz(x+10+33*5, y+10+34*2, AP[rec.place].name, 32, 33, 0);
    if(rec.readif == 0)
    {
        puthz(x+10+33*7, y+10+34*3, "未读", 32, 33, 0);
    }
    else if(rec.readif == 1)
    {
        puthz(x+10+33*7, y+10+34*3, "已读", 32, 33, 0);
    }
    else if(rec.readif == 2)
    {
        puthz(x+10+33*7, y+10+34*3, "更新", 32, 33, 0);
    }
    if(rec.appeal_state == 0)
    {
        puthz(x+10+33*8, y+10+34*4, "未申诉", 32, 33, 0);
    }
    else if(rec.appeal_state == 1)
    {
        puthz(x+10+33*8, y+10+34*4, "已确认", 32, 33, 0);
    }
    else if(rec.appeal_state == 2)
    {
        puthz(x+10+33*8, y+10+34*4, "申诉中", 32, 33, 64384);
    }
    else if(rec.appeal_state == 3)
    {
        puthz(x+10+33*8, y+10+34*4, "申诉成功", 32, 33, 2016);
    }
    else if(rec.appeal_state == 4)
    {
        puthz(x+10+33*8, y+10+34*4, "申诉失败", 32, 33, 63488);
    }
    else if(rec.appeal_state == 5)
    {
        puthz(x+10+33*8, y+10+34*4, "申诉成功已确认", 32, 33, 0);
    }
    else if(rec.appeal_state == 6)
    {
        puthz(x+10+33*8, y+10+34*4, "申诉失败已确认", 32, 33, 0);
    }
    else if(rec.appeal_state == 7)
    {
        puthz(x+10+33*8, y+10+34*4, "撤销申诉", 32, 33, 0);
    }
}

/*记录控制面板*/
void record_select_ctrl(int x, int y, int * num, int * sidepage, int * page)
{
    int pos, rnum, i, j, k, rlistlen;
    int  flag = 0, flag2 = 0, esc = 0, rnum_select = -1;
    char str[3];
	USER user = {0};
	Record temp = {0};
	UserList UL = {NULL, 0, 0};          //用户线性表
	RecList RL = {NULL, 0, 0};          //记录线性表

	InitUList(&UL);           //创建线性表
	ReadAllUser(&UL);         //获取所有用户
	user = UL.elem[*num];
	DestroyUList(&UL);        //销毁线性表

	ReadAllRec(user, &RL);       //获取所有记录
    rlistlen = RL.length;		//获取记录长度

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    record_select_draw(560, 5, *num);  //绘制记录选择面板

    mouse_on(mouse);

    while(1)
    {
        userinfo_display_short(*num);   //显示用户信息
        if(rlistlen == 0)   //如果没有记录
        {
            bar1(x+8, y+158, x+452, y+158+30, 65530);
            puthz(x+8, y+164, "当前用户没有记录！", 16, 17, 0);
        }

        record_state_display(210, 500, user, 1);   //显示记录状态

        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);
            if(rlistlen > 0)   //如果有记录
            {
                for(rnum = 0; rnum < rlistlen; rnum++)      //选择记录
                {
                    j = (rnum % 12) % 4;
                    i = (rnum % 12) / 4;
                    if(mouse_in(x+8+i*150, y+10+j*37, x+8+i*150+144, y+10+j*37+30))
                    {
                        mouse_trans(HAND);
                        flag = 1;
                        if(mouse_press(x+8+i*150, y+10+j*37, x+8+i*150+144, y+10+j*37+30))
                        {
                            temp = RL.elem[rnum];
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            puthz(x+8, y+164, "当前选择记录：", 16, 17, 0);
                            sprintf(str, "%d", rnum+1);
                            prt_asc16(x+128, y+164, str, 0);
                            record_display_admin(210, 300, temp);   //显示记录信息
                            rnum_select = rnum;   //记录选择的记录编号
                            break;
                        }
                        continue;
                    }
                }
                if(flag)
                {
                    flag = 0;
                    continue;
                }

                if(mouse_in(x+135, y+200, x+135+110, y+200+30))     //处理用户申诉菜单
                {
                    mouse_trans(HAND);
                    if(mouse_press(x+135, y+200, x+135+110, y+200+30))
                    {
                        if(temp.id == 0)   //如果没有选择记录
                        {
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            puthz(x+8, y+164, "请先选择记录！", 16, 17, 0);
                            delay(2000);
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                        }
                        else
                        {
                            temp = RL.elem[rnum_select];   //获取当前记录
                            esc = appeal_deal_list(x+135, y+243, &user, rnum_select);   //处理申诉
                            if(esc)
                            {
                                break;
                            }
                        }
                    }
                    continue;
                }

                if(mouse_in(x+260, y+200, x+260+80, y+200+30))  //如果点击删除
                {
                    mouse_trans(HAND);
                    if(mouse_press(x+260, y+200, x+260+80, y+200+30))
                    {
                        if(temp.id == 0)   //如果没有选择记录
                        {
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            puthz(x+8, y+164, "请先选择记录！", 16, 17, 0);
                            delay(2000);
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                        }
                        else
                        {
                            mouse_off(&mouse);
                            // sprintf(str, "%d", rnum_select);
                            // prt_asc16(x+8, y+164, str, 63488);
                            // getch();
                            RListDelete(user, rnum_select);
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            puthz(x+8, y+164, "删除记录成功！", 16, 17, 0);
                            delay(2000);
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            mouse_on(mouse);
                            esc = 1;
                        }
                    }
                    continue;
                }

                if(mouse_in(x+360, y+200, x+360+80, y+200+30))  //如果点击刷新
                {
                    mouse_trans(HAND);
                    if(mouse_press(x+360, y+200, x+360+80, y+200+30))
                    {
                        if(temp.record_time == 0)   //如果没有选择记录
                        {
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            puthz(x+8, y+164, "请先选择记录！", 16, 17, 0);
                            delay(2000);
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                        }
                        else
                        {
                            record_display_admin(210, 300, temp);   //显示记录信息
                        }
                    }
                    continue;
                }
            }


            
            if(mouse_in(x+10, y+200, x+10+110, y+200+30))  //如果点击返回主页
            {
                mouse_trans(HAND);
                if(mouse_press(x+10, y+200, x+10+110, y+200+30))
                {
                    *page = 0;
                    esc = 1;
                    delay(200);
                    break;
                }
                continue;
            }

            for(k=0; k<7; k++)                      //绘制用户按钮
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag2 = 1;
                    if(mouse_press(15, 150, 160, 210+k*75))
                    {
                        *num = k + (*sidepage-1)*7;      //用户编号
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
            if(flag2)
            {
                flag2 = 0;
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

            if((mouse_in(100, 680, 100+24*3, 680+24)) && (*sidepage * 7 <  ReadUserNum()))  //控制翻页
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
                    sidepage = 1;
                    esc = 1;
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
            mouse_on(mouse);
            DestroyRList(&RL);        //销毁线性表
            break;
        }
    }    
}

/*用户记录状态打印*/
void record_state_display(int x, int y, USER user, int ifadmin)
{
    char str[3];
    RecState recstate = {0};

    RecStateCount(user, &recstate);   //获取记录状态统计

    if(ifadmin)   //如果是管理员
    {
        puthz(x+10, y, "当前用户记录状态统计", 32, 33, 0);
    }
    else
    {
        puthz(x+10, y, "您的违停记录状态统计", 32, 33, 0);
    }
    
    puthz(x+10, y+10+34, "未处理记录数：", 32, 33, 0);
    puthz(x+10, y+10+2*34, "已确认记录数：", 32, 33, 0);
    puthz(x+10, y+10+3*34, "申诉中记录数：", 32, 33, 0);
    puthz(x+10, y+10+4*34, "申诉成功记录数：", 32, 33, 0);
    puthz(x+10, y+10+5*34, "申诉失败记录数：", 32, 33, 0);
    puthz(x+10, y+10+6*34, "撤销申诉记录数：", 32, 33, 0);
    itoa(recstate.not_appeal, str, 10);
    put_asc16_size(x+10+33*7, y+10+34*1, 2, 2, str, 0);
    itoa(recstate.confirmed,str ,10);
    put_asc16_size(x+10+33*7,y +10 +34*2 ,2 ,2 ,str ,0 );
    itoa(recstate.appealed,str ,10);
    put_asc16_size(x +10 +33*7,y +10 +34*3 ,2 ,2 ,str ,0 );
    itoa(recstate.appealed_success,str ,10);
    put_asc16_size(x +10 +33*8,y +10 +34*4 ,2 ,2 ,str ,0 );
    itoa(recstate.appealed_fail,str ,10);
    put_asc16_size(x +10 +33*8,y +10 +34*5 ,2 ,2 ,str ,0 );
    itoa(recstate.appealed_cancel,str ,10);
    put_asc16_size(x +10 +33*8,y +10 +34*6 ,2 ,2 ,str ,0 );
}

/*绘制用户申诉红点*/
void appeal_new_confirm(USER user, int x, int y)
{
    int i;
    char temp[3] = {0};

    if(user.appeal_times <= 0)   //如果没有申诉
    {
        return;       //直接返回  
    }

    if(user.appeal_times < 10)
    {
        Circlefill(x, y, 10, 63488);
        sprintf(temp, "%d", user.appeal_times);
        prt_asc16(x-3, y-8, temp, 65535);
    }
    else if(user.appeal_times >= 10)
    {
        Circlefill(x, y, 10, 63488);
        sprintf(temp, "%d", user.appeal_times);
        prt_asc16(x-8, y-8, temp, 65535);
    }
}

/*用户申诉处理下拉菜单（0为未成功处理，1为成功处理）*/
int appeal_deal_list(int x, int y, USER * user, int rec_num)
{
    int buffer_id;
    Record rec = {0};
    RecList RL = {NULL, 0, 0};          //记录线性表
    ReadAllRec(*user, &RL);   //获取所有记录
    rec = RL.elem[rec_num];   //获取当前记录
    DestroyRList(&RL);        //销毁线性表

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    buffer_id = SaveMenuBuffer(x-1, y-1, x+140+1, y+175+1);

    bar1(x, y, x+140, y+175, 33808);   //绘制背景
    bar1(x+5, y+5, x+135, y+170, 65530);   

    puthz(x+7, y+7, "申诉处理", 24, 25, 0);   //绘制标题
    if(rec.appeal_state == 2)
    {
        rounded_button_d(x+15, y+35, 110, 30, "申诉成功", 3, 65498);   //申诉成功
        rounded_button_d(x+15, y+75, 110, 30, "申诉失败", 3, 65498);   //申诉失败
    }
    else
    {
        rounded_button_d(x+15, y+35, 110, 30, "申诉成功", 3, 33808);   //申诉成功
        rounded_button_d(x+15, y+75, 110, 30, "申诉失败", 3, 33808);   //申诉失败
    }
    
    mouse_on(mouse);

    while(1)
    {
        sys_time(200, 20);
        mouse_show(&mouse);
        
        if(mouse_in(x+15, y+35, x+15+110, y+35+30))
        {
            mouse_trans(HAND);
            if(mouse_press(x+15, y+35, x+15+110, y+35+30))
            {
                if(rec.appeal_state == 2)   //如果是申诉中
                {
                    rec.appeal_state = 3;   //申诉成功
                    rec.readif = 2;        //更新
                    UpdataRec(*user, rec, rec_num);   //更新记录
                    (*user).appeal_times--;   //减少申诉次数
                    UpdataUser(*user);      //更新用户信息
                    bar1(x+15, y+115, x+15+110, y+115+16, 65530);
                    puthz(x+15, y+115, "该用户申诉成功！", 16, 16, 0);
                    delay(2000);
                    return 1;
                }
                else
                {
                    bar1(x+15, y+115, x+15+110, y+115+16, 65530);
                    puthz(x+15, y+115, "该用户未申诉！", 16, 16, 63488);
                }
            }
            continue;
        }

        if(mouse_in(x+15, y+75, x+15+110, y+75+30))
        {
            mouse_trans(HAND);
            if(mouse_press(x+15, y+75, x+15+110, y+75+30))
            {
                if(rec.appeal_state == 2)   //如果是申诉中
                {
                    rec.appeal_state = 4;   //申诉失败
                    rec.readif = 2;        //更新
                    UpdataRec(*user, rec, rec_num);   //更新记录
                    bar1(x+15, y+115, x+15+110, y+115+16, 65530);
                    puthz(x+15, y+115, "该用户申诉失败！", 16, 16, 0);
                    delay(2000);
                    return 1;
                }
                else
                {
                    bar1(x+15, y+115, x+15+110, y+115+16, 65530);
                    puthz(x+15, y+115, "该用户未申诉！", 16, 16, 63488);
                }
            }
            continue;
        }

        if(mouse_press(0, 0, 1024, 768) && !mouse_in(x, y, x+140, y+175))   //如果点击菜单外，则退出
        {
            mouse_off(&mouse);
            RestoreMenuBuffer(x-1, y-1, x+140+1, y+175+1, buffer_id);   //恢复菜单
            mouse_on(mouse);
            ClearMenuBuffer();   //清除菜单缓存
            return 0;
        }
        mouse_trans(CURSOR);
        delay(15);
    }
}