#include <allfunc.h>

/*管理员用户管理面板*/
void admin_user_panel(int * page)
{
    static int sidepage = 1;

    mouse_off(&mouse);  
    mouse_trans(CURSOR);
    delay(100);

    g_admin_user_panel(sidepage);

    mouse_on(mouse);

    admin_user_panel_ctrl(&sidepage, page);
}

/*管理员用户管理面板控制*/
void admin_user_panel_ctrl(int * sidepage, int * page)
{
    static int current_sidepage = 1;
    int unum = 0;

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
            highlight_switch_user(unum, *sidepage);   //高亮按钮切换
        }
        while(1)
        {
            userinfo_display_ctrl(&unum, sidepage, page);  //用户信息显示
            break;
        }
        if(!*page)     //如果选择退出，跳出循环
        {
            current_sidepage = 1;
            break;  
        }
    }
}

/*绘制管理用户面板*/
void g_admin_user_panel(int sidepage)
{
    int i, pos, unum;
    UserList UL = {NULL, 0, 0};          //用户线性表
    InitUList(&UL);           //创建线性表
    ReadAllUser(&UL);         //获取所有用户
    pos = 7 * (sidepage - 1);		//计算控制区间

    clear_window(ALLBOARD);
    for(i=0, unum = pos; (unum < pos + 7) && (unum < UL.length); unum++, i++)
    {
        rounded_button_asc(15, 150+i*75, 145, 60, UL.elem[unum].name, 5, 65498);
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
}

/*用户信息显示/控制*/
void userinfo_display_ctrl(int * unum,int * sidepage, int *page)
{
    int pos, rnum, k, i;
    int  flag = 0, esc = 0;
    int carbodyflag = 1, telflag = 1, mailflag = 1;
    char str[3];
    char * pt = NULL;
    USER temp = {0}, temp_codeonly = {0};
    UserList UL = {NULL, 0, 0};          //用户线性表
    InitUList(&UL);           //创建线性表
    ReadAllUser(&UL);         //获取所有用户
    temp = UL.elem[*unum];
    temp_codeonly = UL.elem[*unum];   //仅用于修改密码
    DestroyUList(&UL);          //销毁线性表
    mouse_off(&mouse);
    
    clear_window(MAINBOARD);     //清理主页面

    puthz(200, 50, "用户信息", 32, 33, 0);
    puthz(200, 90, "用户名：", 32, 33, 0);
    put_asc16_size(200+24*5, 90, 2, 2, temp.name, 0);
    puthz(200, 130, "密码：", 32, 33, 0);
    put_asc16_size(200+24*4, 130, 2, 2, temp.code, 0);
    puthz(200, 170, "车牌号：", 32, 33, 0);
    put_carhead(200+24*5, 170, temp.carhead, 32, 0);
    put_asc16_size(200+24*7, 170, 2, 2, temp.carbody, 0);
    puthz(200, 210, "电话：", 32, 33, 0);
    put_asc16_size(200+24*4, 210, 2, 2, temp.tel, 0);
    puthz(200, 250, "邮箱：", 32, 33, 0);
    put_asc16_size(200+24*4, 250, 2, 2, temp.mail, 0);
    puthz(200, 290, "是否为校内人员：", 32, 33, 0);
    if(temp.ifin)
    {
        puthz(200+24*11, 290, "是", 32, 33, 0);
    }
    else
    {
        puthz(200+24*11, 290, "否", 32, 33, 0);
    }
    puthz(200, 330, "违停次数：", 32, 33, 0);
    itoa(temp.record_time, str, 10);
    put_asc16_size(200+24*7, 330, 2, 2, str, 0);
    puthz(200, 370, "信息是否完善：", 32, 33, 0);
    if(temp.flag)
    {
        puthz(200+24*9, 370, "是", 32, 33, 0);
    }
    else
    {
        puthz(200+24*9, 370, "否", 32, 33, 0);
    }
    bar1(200, 410, 1005, 755, 33808);   //绘制用户控件面板
    bar1(205, 415, 1000, 750, 65530); 
    puthz(215, 420, "管理用户信息面板", 32, 33, 0);   //管理用户信息面板
    puthz(215, 465, "车牌号修改：", 32, 33, 0);   //车牌号修改
    puthz(215+32, 505, "电话修改：", 32, 33, 0);   //电话修改
    puthz(215+32, 545, "邮箱修改：", 32, 33, 0);   //邮箱修改
    puthz(215, 585, "是否为校内人员：", 32, 33, 0);   //是否为校内人员
    bar2(215+32*6, 465, 215+32*6+32, 465+32, 0);   //车牌头修改输入框
    bar2(215+32*6+40, 465, 215+32*6+300, 465+32, 0);   //车牌号修改输入框
    bar2(215+32*6, 505, 215+32*6+300, 505+32, 0);   //电话修改输入框
    bar2(215+32*6, 545, 215+32*6+300, 545+32, 0);   //邮箱修改输入框
    bar2(215+32*8, 591, 215+32*8+20, 591+20, 0);   //是否为校内人员勾选框
    if(temp.ifin)
    {
       red_tick(215+32*8, 591);   //是否为校内人员
    }
    rounded_button_d(220, 700, 140, 40, "返回主页", 5, 65498);   //返回主页按钮
    rounded_button_d(550, 700, 140, 40, "初始化密码", 5, 65498);   //初始化密码按钮
    rounded_button_d(700, 700, 140, 40, "确认修改", 5, 65498);   //确认修改按钮
    rounded_button_d(850, 700, 140, 40, "删除用户", 5, 65498);   //删除用户按钮

    while(1)
    {

        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);

            if(mouse_in(215+32*6, 465, 215+32*6+32, 465+32))
            {
                mouse_trans(HAND);
                if(mouse_press(215+32*6, 465, 215+32*6+32, 465+32))
                {
                    temp.carhead = carhead_list(215+32*6, 465+32+2, 215+32*6, 465);   //车牌头下拉菜单
                }
                continue;
            }

            if(mouse_in(215+32*6+40, 465, 215+32*6+300, 465+32))
            {
                mouse_trans(TEXT);
                if(mouse_press(215+32*6+40, 465, 215+32*6+300, 465+32))
                {
                    mouse_off(&mouse);
                    bar1(215+32*6+40+1, 465+1, 215+32*6+300-1, 465+32-1, 65530);   //清除输入框
                    strcpy(temp.carbody, "\0");
                    Getinfo(215+32*6+40+3, 465+3, temp.carbody, 6, 215+32*6+40+1, 465+1, 215+32*6+300-1, 465+32-1);   //获取车牌号
                    strupr(temp.carbody);       //将车牌转换为大写
                    mouse_on(mouse);
                }
                continue;
            }
            
            if(mouse_in(215+32*6, 505, 215+32*6+300, 505+32))   //修改电话
            {
                mouse_trans(TEXT);
                if(mouse_press(215+32*6, 505, 215+32*6+300, 505+32))
                {
                    mouse_off(&mouse);
                    bar1(215+32*6+1, 505+1, 215+32*6+300-1, 505+32-1, 65530);   //清除输入框
                    strcpy(temp.tel, "\0");
                    Getinfo(215+32*6+3, 505+3, temp.tel, 11, 215+32*6+1, 505+1, 215+32*6+300-1, 505+32-1);   //获取电话
                    mouse_on(mouse);
                }
                continue;
            }

            if(mouse_in(215+32*6, 545, 215+32*6+300, 545+32))
            {
                mouse_trans(TEXT);
                if(mouse_press(215+32*6, 545, 215+32*6+300, 545+32))
                {
                    mouse_off(&mouse);
                    bar1(215+32*6+1, 545+1, 215+32*6+300-1, 545+32-1, 65530);   //清除输入框
                    strcpy(temp.mail, "\0");
                    Getinfo(215+32*6+3, 545+3, temp.mail, MAIL_LEN, 215+32*6+1, 545+1, 215+32*6+300-1, 545+32-1);   //获取邮箱
                    mouse_on(mouse);
                }
                continue;
            }

            if(mouse_in(215+32*8, 591, 215+32*8+20, 591+20))
            {
                mouse_trans(HAND);
                if(mouse_press(215+32*8, 591, 215+32*8+20, 591+20))
                {
                    if(temp.ifin == 0)
                    {
                        mouse_off(&mouse);
                        bar1(215+32*8-3, 591-3, 215+32*8+20+3, 591+20+3, 65530);   //清除输入框
                        bar2(215+32*8, 591, 215+32*8+20, 591+20, 0);   //清除输入框
                        red_tick(215+32*8, 591);                        //改为校内人员
                        temp.ifin = 1;
                        mouse_on(mouse);
                        delay(300);
                    }
                    else
                    {
                        mouse_off(&mouse);
                        bar1(215+32*8-3, 591-3, 215+32*8+20+3, 591+20+3, 65530);   //清除输入框
                        bar2(215+32*8, 591, 215+32*8+20, 591+20, 0);   //清除输入框
                        temp.ifin = 0;
                        mouse_on(mouse);
                        delay(300);
                    }
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
            if(mouse_in(550, 700, 550+140, 700+40))     //初始化密码
            {
                mouse_trans(HAND);
                if(mouse_press(550, 700, 550+140, 700+40))
                {
                    puthz(220, 660, "是否要初始化密码？", 32, 33, 0);
                    rounded_button_d(220+32*9, 660, 80, 32, "确定", 5, 65498);   //取消按钮
                    rounded_button_d(220+32*9+90, 660, 80, 32, "取消", 5, 65498);   //确定按钮 
                    while(1)
                    {
                        sys_time(200, 20);
                        mouse_show(&mouse);
                        if(mouse_in(220+32*9, 660, 220+32*9+80, 660+32))
                        {
                            mouse_trans(HAND);
                            if(mouse_press(220+32*9, 660, 220+32*9+80, 660+32))
                            {
                                strcpy(temp_codeonly.code, "123456");   //初始化密码
                                UpdataUser(temp_codeonly);   //更新用户信息
                                mouse_off(&mouse);
                                bar1(220, 660-2, 220+500, 660+32+2, 65530);   //清除提示框
                                puthz(220, 660, "密码初始化成功！", 32, 33, 0);
                                delay(2000);
                                bar1(220, 660-2, 220+500, 660+32+2, 65530);   //清除提示框
                                mouse_on(mouse);
                                break;
                            }
                            continue;
                        }
                        else if(mouse_in(220+32*9+90, 660, 220+32*9+90+80, 660+32))
                        {
                            mouse_trans(HAND);
                            if(mouse_press(220+32*9+90, 660, 220+32*9+90+80, 660+32))
                            {
                                mouse_off(&mouse);
                                bar1(220, 660-2, 220+500, 660+32+2, 65530);   //清除提示框  //清除提示框
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

            if(mouse_in(700, 700, 700+140, 700+40))     //确认修改
            {
                mouse_trans(HAND);
                if(mouse_press(700, 700, 700+140, 700+40))
                {
                    if(temp.flag == 0)   //如果信息不完善
                    {
                        puthz(220, 660, "该用户还未完善信息！", 32, 33, 0);
                        delay(2000);
                        bar1(220, 660-2, 220+500, 660+32+2, 65530);
                        break;
                    }
                    else
                    {
                        puthz(220, 660, "是否保存修改信息？", 32, 33, 0);
                        rounded_button_d(220+32*9, 660, 80, 32, "确定", 5, 65498);   //确定按钮
                        rounded_button_d(220+32*9+90, 660, 80, 32, "取消", 5, 65498);   //取消按钮 
                        while(1)
                        {
                            sys_time(200, 20);
                            mouse_show(&mouse);
                            if(mouse_in(220+32*9, 660, 220+32*9+80, 660+32))
                            {
                                mouse_trans(HAND);
                                if(mouse_press(220+32*9, 660, 220+32*9+80, 660+32))
                                {
                                    if(temp.carhead>0)      //如果选择了车牌头
                                    {
                                        if(strlen(temp.carbody)>0)      //如果车牌号不为空
                                        {
                                            for(i=0; i<strlen(temp.carbody); i++)
                                            {
                                                if(!((temp.carbody[i]>='0'&&temp.carbody[i]<='9') || (temp.carbody[i]>='A'&&temp.carbody[i]<='Z')))
                                                {
                                                    carbodyflag = 0;
                                                    break;
                                                }
                                            }
                                            if(!(strlen(temp.carbody)==5||strlen(temp.carbody)==6))
                                            {
                                                carbodyflag = 0;
                                            }
                                            if(carbodyflag)             //如果车牌号格式正确
                                            {
                                                if(strlen(temp.mail)>0)       //如果电话不为空
                                                {
                                                    for(i=0; i<strlen(temp.tel); i++)
                                                    {
                                                        if(!(temp.tel[i]>='0'&&temp.tel[i]<='9'))
                                                        {
                                                            telflag = 0;
                                                            break;
                                                        }
                                                    }
                                                    if(!(strlen(temp.tel) == 11))
                                                    {
                                                        telflag = 0;
                                                            break;
                                                    }
                                                    if(telflag)        //如果电话格式正确
                                                    {
                                                        if(strlen(temp.mail)>0)     //如果邮箱不为空
                                                        {
                                                            if(!(pt = strchr(temp.mail, '@')))
                                                            {
                                                                mailflag = 0;
                                                            }
                                                            if(!(strstr(pt, ".com")))
                                                            {
                                                                mailflag = 0;
                                                            }
                                                            if(mailflag)        //如果邮箱格式正确
                                                            {
                                                                temp.flag=1;        //保存并退出循环
                                                                mouse_off(&mouse);
                                                                UpdataUser(temp);
                                                                bar1(220, 660-2, 220+500, 660+32+2, 65530);     //清除提示框
                                                                puthz(220, 660, "用户信息修改成功", 32, 33, 0);
                                                                delay(2000);
                                                                bar1(220, 660-2, 220+500, 660+32+2, 65530);   //清除提示框
                                                                mouse_on(mouse);
                                                                esc = 1;
                                                                break;
                                                            }
                                                            else
                                                            {
                                                                prt_hz24(220, 635, "邮箱格式不正确！",63488, "HZK\\Hzk24h");
                                                                delay(1500);
                                                                bar1(220, 635, 220+300, 635+24, 65530);
                                                            }
                                                        }
                                                        else
                                                        {
                                                            prt_hz24(220, 635, "邮箱为空！",63488, "HZK\\Hzk24h");
                                                            delay(1500);
                                                            bar1(220, 635, 220+300, 635+24, 65530);
                                                        }
                                                    }
                                                    else
                                                    {
                                                        prt_hz24(220, 635, "电话格式不正确！",63488, "HZK\\Hzk24h");
                                                        delay(1500);
                                                        bar1(220, 635, 220+300, 635+24, 65530);
                                                    }
                                                }
                                                else
                                                {
                                                    prt_hz24(220, 635, "电话为空！",63488, "HZK\\Hzk24h");
                                                    delay(1500);
                                                    bar1(220, 635, 220+300, 635+24, 65530);
                                                }
                                            }
                                            else
                                            {
                                                prt_hz24(220, 635, "车牌号格式不正确！",63488, "HZK\\Hzk24h");
                                                delay(1500);
                                                bar1(220, 635, 220+300, 635+24, 65530);
                                            }
                                        }
                                        else
                                        {
                                            prt_hz24(220, 635, "车牌号为空！",63488, "HZK\\Hzk24h");
                                            delay(1500);
                                            bar1(220, 635, 220+300, 635+24, 65530);
                                        }
                                    }
                                }
                                continue;
                            }
                            else if(mouse_in(220+32*9+90, 660, 220+32*9+90+80, 660+32))
                            {
                                mouse_trans(HAND);
                                if(mouse_press(220+32*9+90, 660, 220+32*9+90+80, 660+32))
                                {
                                    mouse_off(&mouse);
                                    bar1(220, 660-2, 220+500, 660+32+2, 65530);
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

            if(mouse_in(850, 700, 850+140, 700+40))
            {
                mouse_trans(HAND);
                if(mouse_press(850, 700, 850+140, 700+40))
                {
                    mouse_off(&mouse);
                    puthz(220, 660, "是否删除该用户？", 32, 33, 57355);   //提示删除用户
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
                                UListDelete(*unum);        //删除用户
                                mouse_off(&mouse);
                                bar1(220, 660-2, 220+500, 660+32+2, 65530);   //清除提示框
                                puthz(220, 660, "删除用户成功！即将返回上级……", 32, 33, 57355);
                                delay(2000);
                                *page = 0;   //返回上级
                                esc = 1;
                                mouse_on(mouse);
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
                                bar1(220, 660-2, 220+500, 660+32+2, 65530);     //清除提示框
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

            for(k=0; k<7; k++)      //选择侧栏用户
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(15, 150, 160, 210+k*75))
                    {
                        *unum = k + (*sidepage-1)*7;      //用户编号
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
            if(mouse_in(53, 720, 53+16*4, 720+16))
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

/*车牌头下拉菜单(在x2, y2的位置显示选择的车牌)*/
int carhead_list(int x1, int y1, int x2, int y2)
{
    int buffer_id, i, j, flag;
    mouse_off(&mouse);
    bar1(215+32*6+1, 465+1, 215+32*6+32-1, 465+32-1, 65530);   //清除输入框
    buffer_id = SaveMenuBuffer(x1-1, y1-1, x1+410+1, y1+210+1);
    carhead_keyboard(x1, y1);
    mouse_on(mouse);
    while(1)
    {
        sys_time(200, 20);
        mouse_show(&mouse);
        flag = 0;  
        for(i=0; i<4; i++)                    //车牌头键盘
        {
            for(j=0; j<8; j++)
            {
                if(mouse_in(x1+13+j*48, y1+17+i*48, x1+13+j*48+40, y1+i*48+40))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(x1+13+j*48, y1+17+i*48, x1+13+j*48+40, y1+i*48+40))
                    {
                        mouse_off(&mouse);
                        bar1(x2+1, y2+1, x2+32-1, y2+32-1, 65530);   //清除输入框
                        put_carhead(x2+4, y2+4, j+i*8+1, 24, 0);
                        RestoreMenuBuffer(x1-1, y1-1, x1+410+1, y1+210+1, buffer_id);   //恢复菜单
                        mouse_on(mouse);
                        return j+i*8+1;   //返回车牌头
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

        if(mouse_press(0, 0, 1024, 768) && !mouse_in(x1, y1, x1+410, y1+210))   //如果点击菜单外，则退出
        {
            mouse_off(&mouse);
            RestoreMenuBuffer(x1-1, y1-1, x1+410+1, y1+210+1, buffer_id);   //恢复菜单
            mouse_on(mouse);
            return 0;
        }
        mouse_trans(CURSOR);
        delay(15);
    }
}

