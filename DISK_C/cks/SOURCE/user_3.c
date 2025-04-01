#include <allfunc.h>

/*用户停车范围查询面板*/
void user_range_panel(int * page)
{
    mouse_off(&mouse);
    mouse_trans(CURSOR);

    g_user_range_panel();

    mouse_on(mouse);

    user_range_panel_ctrl(page);
}

/*绘制用户停车范围查询面板*/
void g_user_range_panel(void)
{

}

/*用户停车范围查询面板控制*/
void user_range_panel_ctrl(int *page)
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
