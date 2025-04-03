#include <allfunc.h>

/*规则修改面板主控函数*/
void admin_rule_panel(int * page)
{
    static int sidepage = 1;

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    g_admin_rule_panel(sidepage);

    mouse_on(mouse);

    admin_rule_panel_ctrl(&sidepage, page);
}

/*管理员规则管理面板控制*/
void admin_rule_panel_ctrl(int * sidepage, int * page)
{
    static int current_sidepage = 1;
    int anum = 0;

    while(1)
    {
        if(current_sidepage != *sidepage)    //如果换页，重绘侧栏
        {
            mouse_off(&mouse);
            g_admin_rule_panel(*sidepage);
            current_sidepage = *sidepage;
            mouse_on(mouse);
        }
        else
        {
            highlight_switch_area(anum, *sidepage);   //高亮按钮切换
        }
        while(1)
        {
            areainfo_display_ctrl(&anum, sidepage, page);  //地点信息显示
            break;
        }
        if(!*page)     //如果选择退出，跳出循环
        {
            current_sidepage = 1;
            break;  
        }
    }
}

/*绘制管理规则面板*/
void g_admin_rule_panel(int sidepage)
{
    int i;
    AREA AP[14];
    area_read(AP);          //读取地点信息
    clear_window(ALLBOARD);

    for(i=0; i<7; i++)
    {
        rounded_button_d(15, 150+i*75, 145, 60, AP[i+(sidepage-1)*7].name, 5, 65498);
    }
    //area_destory(AP);   //
    if(!(sidepage == 1))
        prt_hz16(20, 680, "上一页", 63519, "hzk\\hzk16");
    else if(!(sidepage == 2))
        prt_hz16(100, 680, "下一页", 63519, "hzk\\hzk16");
    prt_hz16(53, 720, "返回上级", 63519, "hzk\\hzk16");
}

/*地点信息显示/控制*/
void areainfo_display_ctrl(int * i, int * sidepage, int * page)
{
    int j, k;
    int time = -1, time1 = -1, time2 = -1, time3 = -1;
    int flag = 0, esc = 0, week_num = -1, ifstart = 1;
    AREA AP[14];
    AREA temp = {0};
    char str[30], str_time[3];
    char * week[7] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
    area_read(AP);          //读取地点信息

    mouse_off(&mouse);
    clear_window(MAINBOARD);

    sprintf(str, "路段名称：%s", AP[*i].name);
    puthz(200, 50, str, 32, 33, 0);
    if(!AP[*i].allnp)
    {
        puthz(200, 90, "是否为全路段禁停：是", 32, 33, 0);
    }
    else
    {
        puthz(200, 90, "是否为全路段禁停：否", 32, 33, 0);
        puthz(200, 130, "违停时间段　　起始时间　　终止时间", 24, 25, 0);
        for(k=0; k<7; k++)
        {
            puthz(225, 160 + k*25, week[k], 24, 25, 0);
            prt_time(383, 160 + k*25, AP[*i].timest[k]);
            prt_time(535, 160 + k*25, AP[*i].timeed[k]);
        }
    }
    bar1(200, 410, 1005, 755, 33808);   //绘制用户控件面板
    bar1(205, 415, 1000, 750, 65530); 
    puthz(215, 420, "管理地点信息面板", 32, 33, 0);   //管理用户信息面板
    puthz(215, 465, "违停时间修改：", 32, 33, 0);   //地点名称修改
    puthz(215, 505, "是否为全路段禁停：", 32, 33, 0);   //是否为全路段禁停
    bar2(215+32*7, 465, 215+32*7+96, 465+32, 0);   //违停时间段修改星期选择框
    bar2(547, 465, 547+24*4+8, 465+32, 0);  //起始/终止切换框（默认起始）
    puthz(547+4, 465+4, "起始时间", 24, 25, 0);   //起始时间
    bar2(667, 465, 667+40, 465+32, 0);          //时间输入框
    put_asc16_size(667+40, 465+4, 2, 2, ":", 0);   //时间输入框冒号
    bar2(727, 465, 727+40, 465+32, 0);          //时间输入框
    put_asc16_size(727+40, 465+4, 2, 2, ":", 0);   //时间输入框冒号
    bar2(787, 465, 787+40, 465+32, 0);          //时间输入框
    bar2(215+32*9, 511, 215+32*9+20, 511+20, 0);   //是否为全路段禁停勾选框
    if(!AP[*i].allnp)
    {
       red_tick(215+32*9, 511);   //是否为全路段禁停
    }

    puthz(220, 545, "每更新一次时间信息，请点击一次修改时间按钮！", 24, 25, 63488);   //更新时间信息按钮

    rounded_button_d(220, 700, 140, 40, "返回主页", 5, 65498);   //返回主页按钮
    rounded_button_d(550, 700, 140, 40, "禁停切换", 5, 65498);   //禁停切换按钮
    rounded_button_d(700, 700, 140, 40, "修改时间", 5, 65498);   //确认修改按钮
    rounded_button_d(850, 700, 140, 40, "初始化地点", 5, 65498);   //初始化地点按钮

    mouse_on(mouse);

    while(1)
    {
        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);


            for(k=0; k<7; k++)      //选择侧栏用户
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(15, 150, 160, 210+k*75))
                    {
                        *i = k + (*sidepage-1)*7;      //地点编号
                        esc = 1;
                        delay(200);
                        break;
                    }
                    break;
                }
            }
            if(esc)   //如果点击返回，则退出循环
            {
                break;
            }
            if(flag)
            {
                flag = 0;
                continue;
            }

            if(mouse_in(667, 465, 667+40, 465+32))  //获取小时
            {
                mouse_trans(HAND);
                if(mouse_press(667, 465, 667+40, 465+32))
                {
                    mouse_off(&mouse);
                    bar1(667+1, 465+1, 667+40-1, 465+32-1, 65530);   //清除输入框
                    strcpy(str_time, "\0\0\0");
                    Getinfo(667+3, 465+3, str_time, 2, 667+1, 465+1, 667+40-1, 465+32-1);   //获取输入时间
                    time1 = atoi(str_time);   //转换为整数
                    if(time1 < 0 || time1 > 24)
                    {
                        puthz(220, 660, "输入小时数不合法！", 32, 33, 63488);
                        delay(2000);
                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                        bar1(667+1, 465+1, 667+40-1, 465+32-1, 65530);          //清除时间输入框
                        time1 = -1;
                    }
                    mouse_on(mouse);
                    break;
                }
                continue;
            }
            else if(mouse_in(727, 465, 727+40, 465+32))      //获取分钟
            {
                mouse_trans(HAND);
                if(mouse_press(727, 465, 727+40, 465+32))
                {
                    mouse_off(&mouse);
                    bar1(727+1, 465+1, 727+40-1, 465+32-1, 65530);   //清除输入框
                    strcpy(str_time, "\0\0\0");
                    Getinfo(727+3, 465+3, str_time, 2, 727+1, 465+1, 727+40-1, 465+32-1);   //获取输入时间
                    time2 = atoi(str_time);   //转换为整数
                    if(time2 < 0 || time2 > 59)
                    {
                        puthz(220, 660, "输入分钟数不合法！", 32, 33, 63488);
                        delay(2000);
                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                        bar1(727+1, 465+1, 727+40-1, 465+32-1, 65530);          //清除时间输入框
                        time2 = -1;
                    }
                    mouse_on(mouse);
                    break;
                }
                continue;
            }
            else if(mouse_in(787, 465, 787+40, 465+32))     //获取秒钟
            {
                mouse_trans(HAND);
                if(mouse_press(787, 465, 787+40, 465+32))
                {
                    mouse_off(&mouse);
                    bar1(787+1, 465+1, 787+40-1, 465+32-1, 65530);   //清除输入框
                    strcpy(str_time, "\0\0\0");
                    Getinfo(787+3, 465+3, str_time, 2, 787+1, 465+1, 787+40-1, 465+32-1);   //获取输入时间
                    time3 = atoi(str_time);   //转换为整数
                    if(time3 < 0 || time3 > 59)
                    {
                        puthz(220, 660, "输入秒数不合法！", 32, 33, 63488);
                        delay(2000);
                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                        bar1(787+1, 465+1, 787+40-1, 465+32-1, 65530);          //清除时间输入框
                        time3 = -1;
                    }                        
                    mouse_on(mouse);
                    break;
                }
            }

            if(mouse_in(550, 700, 550+140, 700+40))     //禁停切换
            {
                mouse_trans(HAND);
                if(mouse_press(550, 700, 550+140, 700+40))
                {
                    mouse_off(&mouse);
                    if(AP[*i].allnp)
                    {
                        AP[*i].allnp = 0;
                        mouse_off(&mouse);
                        bar1(215+32*9-3, 511-3, 215+32*9+20+3, 511+20+3, 65530);   //清除勾选框
                        bar2(215+32*9, 511, 215+32*9+20, 511+20, 0);   //是否为全路段禁停勾选框
                        red_tick(215+32*9, 511);   //全路段禁停
                        area_save(AP);   //更新地点信息
                        delay(300);
                        mouse_on(mouse);
                        esc = 1;
                        break;
                    }
                    else
                    {
                        AP[*i].allnp = 1;
                        mouse_off(&mouse);
                        bar1(215+32*9-3, 511-3, 215+32*9+20+3, 511+20+3, 65530);   //清除勾选框
                        bar2(215+32*9, 511, 215+32*9+20, 511+20, 0);   //是否为全路段禁停勾选框
                        area_save(AP);   //更新地点信息
                        delay(300);
                        mouse_on(mouse);
                        esc = 1;
                        break;
                    }
                }
                continue;
            }

            if(mouse_in(547, 465, 547+24*4+8, 465+32))      //起始/终止切换框（默认起始）
            {
                mouse_trans(HAND);
                if(mouse_press(547, 465, 547+24*4+8, 465+32))
                {
                    if(ifstart)
                    {
                        ifstart = 0;
                        mouse_off(&mouse);
                        bar1(547+1, 465+1, 547+24*4+8-1, 465+32-1, 65530);   //起始/终止切换框（默认终止）
                        puthz(547+4, 465+4, "终止时间", 24, 25, 0);   //起始时间
                        delay(300);
                        mouse_on(mouse);
                    }
                    else
                    {
                        ifstart = 1;
                        mouse_off(&mouse);
                        bar1(547+1, 465+1, 547+24*4+8-1, 465+32-1, 65530);   //起始/终止切换框（默认起始）
                        puthz(547+4, 465+4, "起始时间", 24, 25, 0);   //起始时间
                        delay(300);
                        mouse_on(mouse);
                    }
                    break;
                }
                continue;
            }

            if(mouse_in(215+32*7, 465, 215+32*7+100, 465+32))       //选择星期
            {
                mouse_trans(HAND);
                if(mouse_press(215+32*7, 465, 215+32*7+100, 465+32))
                {
                    week_num = week_list(215+32*7, 465+34, 215+32*7, 465);
                }
                continue;
            }

            if(mouse_in(220, 700, 220+140, 700+40))     //返回主页
            {
                mouse_trans(HAND);
                if(mouse_press(220, 700, 220+140, 700+40))
                {
                    *page = 0;
                    esc = 1;
                    delay(200);
                    break;
                }
                continue;
            }
  
            if(mouse_in(700, 700, 700+140, 700+40))     //确认修改时间
            {
                mouse_trans(HAND);
                if(mouse_press(700, 700, 700+140, 700+40))
                {
                    if(!AP[*i].allnp)        //如果不为非禁停模式
                    {
                        mouse_off(&mouse);
                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                        puthz(220, 660, "请切换到非禁停模式以启用时间更改！", 32, 33, 63488);
                        delay(2000);
                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                        mouse_on(mouse);
                        break;
                    }
                    else
                    {
                        puthz(220, 660, "是否保存修改时间信息？", 32, 33, 0);
                        rounded_button_d(220+32*12, 660, 80, 32, "确定", 5, 65498);   //确定按钮
                        rounded_button_d(220+32*12+90, 660, 80, 32, "取消", 5, 65498);   //取消按钮 
                        while(1)
                        {
                            sys_time(200, 20);
                            mouse_show(&mouse);
                            if(mouse_in(220+32*12, 660, 220+32*12+80, 660+32))
                            {
                                mouse_trans(HAND);
                                if(mouse_press(220+32*12, 660, 220+32*12+80, 660+32))
                                {
                                    if(week_num < 0)   //如果没有选择星期，则提示
                                    {
                                        mouse_off(&mouse);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                        puthz(220, 660, "请选择星期！", 32, 33, 63488);
                                        delay(2000);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                        mouse_on(mouse);
                                        break;
                                    }
                                    else if(time1 < 0)
                                    {
                                        mouse_off(&mouse);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                        puthz(220, 660, "请输入正确的小时数！", 32, 33, 63488);
                                        delay(2000);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                        mouse_on(mouse);
                                        break;
                                    }
                                    else if(time2 < 0)
                                    {
                                        mouse_off(&mouse);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                        puthz(220, 660, "请输入正确的分钟数！", 32, 33, 63488);
                                        delay(2000);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                        mouse_on(mouse);
                                        break;
                                    }
                                    else if(time3 < 0)
                                    {
                                        mouse_off(&mouse);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                        puthz(220, 660, "请输入正确的秒数！", 32, 33, 63488);
                                        delay(2000);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                        mouse_on(mouse);
                                        break;
                                    }
                                    else
                                    {
                                        time = time1 * 3600 + time2 * 60 + time3;
                                        if(ifstart)
                                        {
                                            if(time < 0L)
                                            {
                                                mouse_off(&mouse);
                                                sprintf(str, "%s起始时间不能为空！", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                break;
                                            }
                                            else if(time > 86400L)
                                            {
                                                sprintf(str, "%s起始时间不能大于二十四小时！", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                break;
                                            }
                                            else if(time > AP[*i].timeed[week_num])
                                            {
                                                sprintf(str, "%s起始时间不能大于终止时间！", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                break;
                                            }
                                            else if(time == AP[*i].timeed[week_num])
                                            {
                                                sprintf(str, "%s起始时间不能等于终止时间！", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                break;
                                            }
                                            else 
                                            {
                                                AP[*i].timest[week_num] = time;   //更新起始时间
                                                area_save(AP);                  //更新地点信息
                                                mouse_off(&mouse);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                puthz(220, 660, "时间信息修改成功！", 32, 33, 0);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                mouse_on(mouse);
                                                esc = 1;
                                                break;
                                            }    
                                        }
                                        else
                                        {
                                            if(time < 0L)
                                            {
                                                sprintf(str, "%s终止时间不能为空！", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                break;
                                            }
                                            else if(AP[*i].timeed[week_num] > 86400L)
                                            {
                                                sprintf(str, "%s终止时间不能大于二十四小时！", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                break;
                                            }
                                            else if(AP[*i].timest[week_num] > time)
                                            {
                                                sprintf(str, "%s起始时间不能大于终止时间！", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                break;
                                            }
                                            else if(AP[*i].timest[week_num] == time)
                                            {
                                                sprintf(str, "%s起始时间不能等于终止时间！", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                break;
                                            }
                                            else 
                                            {
                                                AP[*i].timeed[week_num] = time;   //更新终止时间
                                                area_save(AP);                  //更新地点信息
                                                mouse_off(&mouse);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                puthz(220, 660, "时间信息修改成功！", 32, 33, 0);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                                mouse_on(mouse);
                                                esc = 1;
                                                break;
                                            }    
                                        }
                                    }
                                }
                                continue;
                            }
                            else if(mouse_in(220+32*12+90, 660, 220+32*12+90+80, 660+32))
                            {
                                mouse_trans(HAND);
                                if(mouse_press(220+32*12+90, 660, 220+32*12+90+80, 660+32))
                                {
                                    mouse_off(&mouse);
                                    bar1(220, 660-2, 220+700, 660+32+2, 65530);
                                    mouse_on(mouse);   //清除提示框
                                    break;
                                }
                                continue;
                            }
                            mouse_trans(CURSOR);
                            delay(15);
                        }
                    }
                } 
                continue;
            }

            if(mouse_in(850, 700, 850+140, 700+40))     //地点信息初始化
            {
                mouse_trans(HAND);
                if(mouse_press(850, 700, 850+140, 700+40))
                {
                    mouse_off(&mouse);
                    puthz(220, 660, "是否初始化该地点？", 32, 33, 63488);   //提示删除用户
                    rounded_button_d(220+32*9, 660, 80, 32, "确定", 5, 65498);   //确定按钮
                    rounded_button_d(220+32*9+90, 660, 80, 32, "取消", 5, 65498);   //取消按钮
                    mouse_on(mouse);
                    while(1)
                    {
                        sys_time(200, 20);
                        mouse_show(&mouse);
                        if(mouse_in(220+32*9, 660, 220+32*9+80, 660+32))
                        {
                            mouse_trans(HAND);
                            if(mouse_press(220+32*9, 660, 220+32*9+80, 660+32))
                            {
                                temp = AP[*i];   //初始化地点信息
                                temp.allnp = 1;
                                for(j=0; j<7; j++)
                                {
                                    temp.timest[j] = 28800L;
                                    temp.timeed[j] = 79200L;
                                }
                                area_update(temp, *i);   //更新地点信息
                                mouse_off(&mouse);
                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                puthz(220, 660, "地点信息初始化成功！", 32, 33, 0);
                                delay(2000);
                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //清除提示框
                                mouse_on(mouse);
                                esc = 1;
                                break;
                            }
                            continue;
                        }
                        else if(mouse_in(220+32*9+90, 660, 220+32*9+80+90, 660+32))
                        {
                            mouse_trans(HAND);
                            if(mouse_press(220+32*9+90, 660, 220+32*9+80+90, 660+32))
                            {
                                mouse_off(&mouse);
                                bar1(220, 660-2, 220+700, 660+32+2, 65530);     //清除提示框
                                mouse_on(mouse);
                                break;
                            }
                            continue;
                        }
                        mouse_trans(CURSOR);
                        delay(15);
                    }
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
            if(mouse_in(53, 720, 53+16*4, 720+16))      //返回主页
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
            mouse_on(mouse);
            break;
        }
    }
}



/*星期下拉菜单（在x2, y2的位置显示选择的星期）*/
int week_list(int x1, int y1, int x2, int y2)
{
    int buffer_id, i, j, flag;
    mouse_off(&mouse);
    bar1(x2+1, y2+1, x2+96-1, y2+32-1, 65530);   //清除输入框
    buffer_id = SaveMenuBuffer(x1-1, y1-1, x1+282+1, y1+210+1);
    week_keyboard(x1, y1);
    mouse_on(mouse);
    while(1)
    {
        sys_time(200, 20);
        mouse_show(&mouse);
        flag = 0;  
        for(i=0; i<4; i++)                    //车牌头键盘
        {
            for(j=0; j<2; j++)
            {
                if(mouse_in(x1+13+j*128, y1+17+i*48, x1+13+j*128+120, y1+17+i*48+40))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(x1+13+j*128, y1+17+i*48, x1+13+j*128+120, y1+17+i*48+40))
                    {
                        mouse_off(&mouse);
                        bar1(x2+1, y2+1, x2+96-1, y2+32-1, 65530);   //清除输入框
                        put_week(x2+4, y2+4, j+i*2+1, 24, 0);
                        RestoreMenuBuffer(x1-1, y1-1, x1+282+1, y1+210+1, buffer_id);   //恢复菜单
                        mouse_on(mouse);
                        return j+i*2+1;   //返回星期
                    }
                    break;
                }
            }
        }
        if(flag)
        {
            flag = 0;
            continue;
        }

        if(mouse_press(0, 0, 1024, 768) && !mouse_in(x1, y1, x1+282, y1+210))   //如果点击菜单外，则退出
        {
            mouse_off(&mouse);
            RestoreMenuBuffer(x1-1, y1-1, x1+282+1, y1+210+1, buffer_id);   //恢复菜单
            mouse_on(mouse);
            return 0;
        }
        mouse_trans(CURSOR);
        delay(15);
    }
}

