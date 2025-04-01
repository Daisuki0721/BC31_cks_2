#include <allfunc.h>

/* 用户信息面板 */
void user_info_panel(int* page, int unum)
{
    mouse_off(&mouse);
    mouse_trans(CURSOR);

    g_user_info_panel(unum);

    mouse_on(mouse);

    user_info_panel_ctrl(page);
}

/* 绘制用户信息面板 */
void g_user_info_panel(int unum)
{
    char record_time_str[10];

    char str[3];
    USER temp = { 0 };
    UserList UL = { NULL, 0, 0 };          // 用户线性表
    InitUList(&UL);           // 创建线性表
    ReadAllUser(&UL);         // 获取所有用户
    temp = UL.elem[unum];
    DestroyUList(&UL);          // 销毁线性表

    mouse_off(&mouse);

    clear_window(ALLBOARD);

    // 绘制用户信息
    puthz(200, 50, "用户信息", 32, 34, 0); // 标题
    puthz(200, 125, "用户名：", 24, 26, 0); // 用户名
    prt_asc16(330, 130, temp.name, 0);
    puthz(200, 175, "车牌号：", 24, 26, 0); // 车牌号
    put_carhead(320, 175, temp.carhead, 24, 0);
    prt_asc16(330 + 18, 180, temp.carbody, 0);
    puthz(200, 225, "是否为校内人员：", 24, 26, 0); // 是否为校内人员
    if (temp.ifin)
    {
        puthz(330 + 100, 225, "是", 24, 26, 0); 
    }
    else
    {
        puthz(330 + 100, 225, "否", 24, 26, 0); 
    }
    puthz(200, 275, "违停次数：", 24, 26, 0);
    itoa(temp.record_time, str, 10);
    prt_asc16(330, 280, str, 0);

    // 绘制返回按钮
    rounded_button_d(15, 150 + 7 * 75, 145, 60, "返回", 5, 65498);
}

/* 用户信息面板控制 */
void user_info_panel_ctrl(int* page)
{
    while (1)
    {
        mouse_show(&mouse);

        if (mouse_in(15, 675, 160, 735))  // 返回按钮
        {
            mouse_trans(HAND);
            if (mouse_press(15, 675, 160, 735))
            {
                *page = 0;  // 返回主界面
                delay(200);
                break;
            }
            continue;
        }
        mouse_trans(CURSOR);
        delay(15);
    }
}