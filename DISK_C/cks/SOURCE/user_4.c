#include <allfunc.h>

/* 用户须知面板 */
void user_notice_panel(int* page) 
{
    mouse_off(&mouse);
    mouse_trans(CURSOR);

    g_user_notice_panel();

    mouse_on(mouse);

    user_notice_panel_ctrl(page);
}

/*绘制用户须知面板*/
void g_user_notice_panel(void)
{
    clear_window(ALLBOARD);

    // 绘制侧栏
    bar1(0, 122, 178, 768, 34429);
    Line_Thick(180, 0, 180, 768, 1, 0);

    // 绘制车主须知内容
    puthz(200, 50, "车主须知", 32, 34, 0);
    puthz(200, 125, "一、请遵守校园内停车规定，不得在禁停区域停车。", 24, 26, 0);
    puthz(200, 160, "二、违停将被记录并通知车主。", 24, 26, 0);
    puthz(200, 195, "三、请保持车牌清晰可见，以便识别。", 24, 26, 0);
    puthz(200, 230, "四、如有疑问，请联系校园管理部门。", 24, 26, 0);

    // 绘制返回按钮
    rounded_button_d(15, 150 + 7 * 75, 145, 60, "返回", 5, 65498);
}

/*用户须知面板控制*/
void  user_notice_panel_ctrl(int* page)
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