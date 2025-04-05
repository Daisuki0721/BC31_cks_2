#include <allfunc.h>

/*管理交互界面主控函数*/
void admin_interface(int * func)
{
    int page=0;

    admin_appeal_rec_fix();      //修正所有用户申诉记录

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    g_admin_interface();

    mouse_on(mouse);

    while(1)
    {
        switch(page)
        {
            case 0:
            {
                admin_main_panel(&page);     //管理员主控面板
                break;
            }
            case 1:
            {
                admin_monitor_panel(&page);      //管理员查看摄像头面板
                break;
            }
            case 2:
            {
                admin_record_panel(&page);      //管理员违停处理面板
                break;
            }
            case 3:
            {
                admin_user_panel(&page);        //管理员用户管理面板
                break;
            }
            case 4:
            {
                admin_rule_panel(&page);
                break;
            }
            case 5:
            {
                admin_exit(&page, func);       //管理退出
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

/*管理员主控面板*/
void admin_main_panel(int * page)
{
    mouse_off(&mouse);
    g_admin_main_panel();        //绘制管理员主控面板
    mouse_on(mouse);

    /*管理员主控面板选择*/
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
        if(mouse_in(15, 225, 160, 285))
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
        if(mouse_in(15, 300, 160, 360))
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
        if(mouse_in(15, 375, 160, 435))
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
        if(mouse_in(15, 450, 160, 510))
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
        mouse_trans(CURSOR);
        delay(15);
    }
}

/*管理界面退出*/
void admin_exit(int * page, int * func)
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

/*管理交互界面绘制*/
void g_admin_interface(void)
{
    bar1(0, 0, 1024, 768, 34429);
    Line_Thick(180, 0, 180, 768, 1, 0);
    Line_Thick(0, 120, 180, 120, 1, 0);
    bar1(182, 0, 1024, 768, 65533);
    Readbmp64k(0, 0, "bmp\\hust1.bmp");
}

/*所有用户申诉记录修正*/
void admin_appeal_rec_fix(void)
{
    int i;
    UserList UL = {NULL, 0, 0};          //用户线性表

    ReadAllUser(&UL);         //获取所有用户
    for(i = 0; i < UL.length; i++)
    {
        RecListRecordFix(UL.elem[i]);   //修正用户违停记录
        RecListAppealFix(UL.elem[i]);   //修正用户申诉记录
    }
}

/*绘制管理主控面板*/
void g_admin_main_panel(void)
{
    int i;
    char * proj[5] = {"摄像头", "记录与申诉", "用户管理", "规则修改", "退出"};
    clear_window(ALLBOARD);
    for(i=0;i<5;i++)
    {
        rounded_button_d(15, 150+i*75, 145, 60, proj[i], 5, 65498);
    }
    appeal_all_confirm(155, 230);   //绘制申诉红点
    puthz(602-101, 324, "尊敬的管理员", 32, 34, 0);
    puthz(602-254, 364, "欢迎使用校园机动车违停管理系统", 32, 34, 0);
    puthz(602-228, 404, "请在左侧选择需要办理的业务", 32, 34, 0);
}

/*管理退出动画界面*/
void g_admin_exit_video(void)
{
    bar1(0, 0, 1024, 768, 34429);
    Readbmp64k(423, 250, "bmp\\hust2.bmp");
    puthz(70, 400, "感谢您使用　校园机动车违停管理系统", 48, 52, 0);
    puthz(278, 460, "祝您生活愉快，再见！", 48 ,52, 0);
    puthz(600, 600, "点击任意键继续……", 32, 34, 33808);
    getch(); 
}

/*绘制所有用户统计申诉红点*/
void appeal_all_confirm(int x, int y)
{
    int i;
    int flag = 0, count = 0;
    char temp[3] = {0};
    UserList UL = {NULL, 0, 0};          //用户线性表
    ReadAllUser(&UL);         //获取所有用户

    for(i = 0; i < UL.length; i++)
    {
        count += UL.elem[i].appeal_times;   //获取所有用户的申诉次数
    }
    
    if(count > 0)
    {
        flag = 1;
    }
    else
    {
        DestroyUList(&UL);         
        return;                     //如果没有申诉记录，则直接返回
    }


    if(flag && count < 10)
    {
        Circlefill(x, y, 10, 63488);
        sprintf(temp, "%d", count);
        prt_asc16(x-3, y-8, temp, 65535);
    }
    else if(flag && count >= 10 && count < 100)
    {
        Circlefill(x, y, 10, 63488);
        sprintf(temp, "%d", count);
        prt_asc16(x-8, y-8, temp, 65535);
    }
    else if(flag && count >= 100)
    {
        Circlefill(x, y, 12, 63488);
        prt_asc16(x-11, y-8, "99+", 65535);
    }

    DestroyUList(&UL);         //销毁用户线性表
}