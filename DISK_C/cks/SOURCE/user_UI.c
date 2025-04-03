#include <allfunc.h>

/*用户交互界面总控函数*/
void user_interface(int unum, int * func)
{
    int page=0;

    struct USER user = {"\0", "\0", 0, 0, "\0", "\0", "\0", 0, 0};	//用户
	UserList UL = {NULL, 0, 0};          //线性表
	InitUList(&UL);           //创建线性表
	ReadAllUser(&UL);         //获取所有用户  
	user = UL.elem[unum];       //得到当前用户
	DestroyUList(&UL);        //销毁线性表

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    g_user_interface();

    mouse_on(mouse);

    if(!user.flag)
    {
        userinfo_complete(user, &page);        //完善用户信息
    }

    while(1)
    {
        switch(page)
        {
            case 0:
            {
                user_main_panel(&page, user);     //用户主控面板
                break;
            }
            case 1:
            {
                user_record_panel(&page);      //用户违停记录面板
                break;
            }
            case 2:
            {
                user_dispose_panel(&page);      //用户违停处理面板
                break;
            }
            case 3:
            {
                user_range_panel(&page);        //用户停车范围查询面板
                break;
            }
            case 4:
            {
                user_notice_panel(&page);       //用户车主须知面板
                break;
            }
            case 5:
            {
                user_mail_panel(&page, unum);         //用户邮箱面板
                break;
            }
            case 6:
            {
                user_info_panel(&page, unum);         //用户信息面板
                break;
            }
            case 7:
            {
                user_FAQ_panel(&page);          //用户常见问题面板
                break;
            }
            case 8:
            {
                user_exit(&page, &func);         //用户登出（注意这个地方func是一个指针！）
                break;
            }
            default:
            {
                break;
            } 
        }
        if(page < 0)        //如果选择了退出，则退出循环
        {
            *func = 0;
            break;
        }
    }
}

/*用户主控制面板*/
void user_main_panel(int * page, USER user)
{
    mouse_off(&mouse);
    g_user_main_panel();        //绘制用户主控面板
    mail_new_confirm(user, 155, 455);        //检查是否有新邮件
    mouse_on(mouse);

    /*用户主控面板选择*/
    while(1)
    {
        mouse_show(&mouse);

        if(mouse_in(15, 150, 160, 210))
        {
            mouse_trans(HAND);
            if(mouse_press(15, 150, 160, 210))
            {
                *page=1;
                delay(200);
                break;
            }
            continue;
        }
        else if(mouse_in(15, 225, 160, 285))
        {
            mouse_trans(HAND);
            if(mouse_press(15, 225, 160, 285))
            {
                *page=2;
                delay(200);
                break;
            }
            continue;
        }
        else if(mouse_in(15, 300, 160, 360))
        {
            mouse_trans(HAND);
            if(mouse_press(15, 300, 160, 360))
            {
                *page=3;
                delay(200);
                break;
            }
            continue;
        }
        else if(mouse_in(15, 375, 160, 435))
        {
            mouse_trans(HAND);
            if(mouse_press(15, 375, 160, 435))
            {
                *page=4;
                delay(200);
                break;
            }
            continue;
        }
        else if(mouse_in(15, 450, 160, 510))
        {
            mouse_trans(HAND);
            if(mouse_press(15, 450, 160, 510))
            {
                *page=5;
                delay(200);
                break;
            }
            continue;
        }
        else if(mouse_in(15, 525, 160, 585))
        {
            mouse_trans(HAND);
            if(mouse_press(15, 525, 160, 585))
            {
                *page=6;
                delay(200);
                break;
            }
            continue;
        }
        else if(mouse_in(15, 600, 160, 660))
        {
            mouse_trans(HAND);
            if(mouse_press(15, 600, 160, 660))
            {
                *page=7;
                delay(200);
                break;
            }
            continue;
        }
        else if(mouse_in(15, 675, 160, 735))
        {
            mouse_trans(HAND);
            if(mouse_press(15, 675, 160, 735))
            {
                *page=8;
                delay(200);
                break;
            }
            continue;
        }
        mouse_trans(CURSOR);
        delay(15);
    }
}

/*用户登出*/
void user_exit(int * page, int * func)
{
    mouse_off(&mouse);
    mouse_trans(CURSOR);

    /*绘制登出框*/
    clear_window(MAINBOARD);                            //清除主板
    bar1(602-205, 384-125, 602+205, 384+125, 33808);
    bar1(602-200, 384-120, 602+200, 384+120, 65530);
    puthz(435, 310, "确定要返回主界面吗？", 32, 35, 0);
    rounded_button_d(432, 400, 150, 60, "取消", 3, 65498);
    rounded_button_d(622, 400, 150, 60, "确定", 3, 65498);

    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);
        if(mouse_in(432, 400, 582, 492))
        {
            mouse_trans(HAND);
            if(mouse_press(432, 400, 582, 492))
            {
                *page=0;
                delay(200);
                break;
            }
            continue;
        }
        else if(mouse_in(622, 400, 772, 460))
        {
            mouse_trans(HAND);
            if(mouse_press(622, 400, 772, 460))
            {
                g_user_exit_video();      //用户登出动画
                *page=-1;
                delay(200);
                break;
            }
            continue;
        }
        mouse_trans(CURSOR);
        delay(15);
    }
}

/*用户交互界面绘制*/
void g_user_interface(void)
{
    char str[20];
    bar1(0, 0, 1024, 768, 34429);
    Line_Thick(180, 0, 180, 768, 1, 0);
    Line_Thick(0, 120, 180, 120, 1, 0);
    bar1(182, 0, 1024, 768, 65533);
    Readbmp64k(0, 0, "bmp\\hust1.bmp");
}

/*绘制用户主控面板*/
void g_user_main_panel(void)
{
    int i;
    char * proj[8]={"违停记录", "违停处理", "范围查询", "车主须知",
        "邮箱", "个人信息", "常见问题", "退出登录"};
    clear_window(ALLBOARD);
    for(i=0; i<8; i++)
    {
        rounded_button_d(15, 150+i*75, 145, 60, proj[i], 5, 65498);
    }
    puthz(602-84, 324, "尊敬的用户", 32, 34, 0);
    puthz(602-254, 364, "欢迎使用校园机动车违停管理系统", 32, 34, 0);
    puthz(602-228, 404, "请在左侧选择需要办理的业务", 32, 34, 0);
}

/*用户退出动画界面*/
void g_user_exit_video(void)
{
    bar1(0, 0, 1024, 768, 34429);
    Readbmp64k(423, 250, "bmp\\hust2.bmp");
    puthz(70, 400, "感谢您使用　校园机动车违停管理系统", 48, 52, 0);
    puthz(278, 460, "祝您生活愉快，再见！", 48 ,52, 0);
    puthz(600, 600, "点击任意键继续……", 32, 34, 33808);
    getch();
}

/*用户信息完善函数*/
void userinfo_complete(USER user, int * page)
{
    int carbodyflag = 1, telflag = 1, mailflag = 1, i = 0, j = 0, flag = 0;
    char * pt = NULL;

    mouse_off(&mouse);
    mouse_trans(CURSOR);

    /*绘制完善信息窗口*/
    bar1(602-205, 384-205, 602+205, 384+165, 33808);
    bar1(602-200, 384-200, 602+200, 384+160, 65530);
    puthz(435, 200, "请完善您的用户信息：", 24, 26, 0);
    puthz(430, 250, "车牌号：", 24, 26, 0);
    bar2(530, 245, 570, 285, 0);
    bar2(575, 245, 770, 285, 0);
    puthz(451, 300, "电话：", 24, 26, 0);
    bar2(530, 295, 770, 335, 0);
    puthz(451, 350, "邮箱：", 24, 26, 0);
    bar2(530, 345, 770, 385, 0);
    puthz(451, 400, "是否为校内人员", 24, 24, 0);
    bar2(625, 402, 645, 422, 0);
    carhead_keyboard(397, 555);     //放置输入键盘

    rounded_button_d(432, 470, 150, 60, "取消", 3, 65498);
    rounded_button_d(622, 470, 150, 60, "确定", 3, 65498);

    mouse_on(mouse);

    while(1)
    {
        carbodyflag = 1; 
        telflag = 1;
        mailflag = 1;
        mouse_show(&mouse);
        if(mouse_in(575, 245, 770, 285))    //车牌输入框
        {
            mouse_trans(TEXT);
            if(mouse_press(575, 245, 770, 285))
            {
                mouse_off(&mouse);
                bar1(576, 246, 769, 284, 65530);
                strcpy(user.carbody, "\0");
                Getinfo(578, 248, user.carbody, 6, 576, 246, 769, 284);
                strupr(user.carbody);       //将车牌转换为大写
                mouse_on(mouse);
            }
            continue;
        }
        else if(mouse_in(530, 295, 770, 335))   //电话输入框
        {
            mouse_trans(TEXT);
            if(mouse_press(530, 295, 770, 335))
            {
                mouse_off(&mouse);
                bar1(531, 296, 769, 334, 65530);
                strcpy(user.tel, "\0");
                Getinfo(533, 298, user.tel, 11, 531, 246, 769, 284);
                mouse_on(mouse);
            }
            continue;
        }
        else if(mouse_in(530, 345, 770, 385))    //邮箱输入框
        {
            mouse_trans(TEXT);
            if(mouse_press(530, 345, 770, 385))
            {
                mouse_off(&mouse);
                bar1(531, 346, 769, 384, 65530);
                strcpy(user.mail, "\0");
                Getinfo(533, 348, user.mail, MAIL_LEN, 531, 246, 769, 284);
                mouse_on(mouse);
            }
            continue;
        }
        else if(mouse_in(625, 402, 645, 422))       //是否为校内人员
        {
            mouse_trans(HAND);
            if(mouse_press(625, 402, 645, 422))
            {
                if(user.ifin == 0)
                {
                    mouse_off(&mouse);
                    bar1(622, 399, 648, 425, 65530);
                    bar2(625, 402, 645, 422, 0);
                    red_tick(625, 402);
                    user.ifin=1;
                    mouse_on(mouse);
                    delay(400);
                }
                else if(user.ifin==1)
                {
                    mouse_off(&mouse);
                    bar1(622, 399, 648, 425, 65530);
                    bar2(625, 402, 645, 422, 0);
                    user.ifin=0;
                    mouse_on(mouse);
                    delay(400);
                }
            }

        }            
        else if(mouse_in(622, 470, 772, 530))     //确定按钮
        {
            mouse_trans(HAND);
            if(mouse_press(622, 470, 772, 530))
            {
                if(user.carhead>0)      //如果选择了车牌头
                {
                    if(strlen(user.carbody)>0)      //如果车牌号不为空
                    {
                        for(i=0; i<strlen(user.carbody); i++)
                        {
                            if(!((user.carbody[i]>='0'&&user.carbody[i]<='9') || (user.carbody[i]>='A'&&user.carbody[i]<='Z')))
                            {
                                carbodyflag = 0;
                                break;
                            }
                        }
                        if(!(strlen(user.carbody)==5||strlen(user.carbody)==6))
                        {
                            carbodyflag = 0;
                        }
                        if(carbodyflag)             //如果车牌号格式正确
                        {
                            if(strlen(user.mail)>0)       //如果电话不为空
                            {
                                for(i=0; i<strlen(user.tel); i++)
                                {
                                    if(!(user.tel[i]>='0'&&user.tel[i]<='9'))
                                    {
                                        telflag = 0;
                                        break;
                                    }
                                }
                                if(!(strlen(user.tel) == 11))
                                {
                                    telflag = 0;
                                        break;
                                }
                                if(telflag)        //如果电话格式正确
                                {
                                    if(strlen(user.mail)>0)     //如果邮箱不为空
                                    {
                                        if(!(pt = strchr(user.mail, '@')))
                                        {
                                            mailflag = 0;
                                        }
                                        if(!(strstr(pt, ".com")))
                                        {
                                            mailflag = 0;
                                        }
                                        if(mailflag)        //如果邮箱格式正确
                                        {
                                            user.flag=1;        //保存并退出循环
                                            UpdataUser(user);
                                            *page = 0;
                                            break;
                                        }
                                        else
                                        {
                                            prt_hz24(602, 440, "邮箱格式不正确！",63488, "HZK\\Hzk24h");
                                            delay(1500);
                                            bar1(602, 440, 794, 466, 65530);
                                        }
                                    }
                                    else
                                    {
                                        prt_hz24(622, 440, "邮箱为空！",63488, "HZK\\Hzk24h");
                                        delay(1500);
                                        bar1(622, 440, 772, 466, 65530);
                                    }
                                }
                                else
                                {
                                    prt_hz24(602, 440, "电话格式不正确！",63488, "HZK\\Hzk24h");
                                    delay(1500);
                                    bar1(602, 440, 794, 466, 65530);
                                }
                            }
                            else
                            {
                                prt_hz24(622, 440, "电话为空！",63488, "HZK\\Hzk24h");
                                delay(1500);
                                bar1(622, 440, 772, 466, 65530);
                            }
                        }
                        else
                        {
                            prt_hz24(578, 440, "车牌号格式不正确！",63488, "HZK\\Hzk24h");
                            delay(1500);
                            bar1(578, 440, 794, 466, 65530);
                        }
                    }
                    else
                    {
                        prt_hz24(622, 440, "车牌号为空！",63488, "HZK\\Hzk24h");
                        delay(1500);
                        bar1(622, 440, 772, 466, 65530);
                    }
                }
            } 
            continue;
        }
        else if(mouse_in(432, 470, 582, 530))       //取消按钮
        {
            mouse_trans(HAND);
            if(mouse_press(432, 470, 582, 530))
            {
                *page = -1;
                break;
            }
            continue;
        }
        for(i=0; i<4; i++)                    //车牌头键盘
        {
            for(j=0; j<8; j++)
            {
                if(mouse_in(410+j*48, 572+i*48, 450+j*48, 612+i*48))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(410+j*48, 572+i*48, 450+j*48, 612+i*48))
                    {
                        user.carhead = j+i*8+1;
                        bar1(531, 246, 569, 284, 65530);
                        put_carhead(538, 253, user.carhead, 24, 0);
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
        mouse_trans(CURSOR);
        delay(15);
    }
}