#include <allfunc.h>

/*�û�ͣ����Χ��ѯ���*/
void user_range_panel(int * page)
{
    mouse_off(&mouse);
    mouse_trans(CURSOR);

    g_user_range_panel();

    mouse_on(mouse);

    user_range_panel_ctrl(page);
}

/*�����û�ͣ����Χ��ѯ���*/
void g_user_range_panel(void)
{

}

/*�û�ͣ����Χ��ѯ������*/
void user_range_panel_ctrl(int *page)
{
    while (1)
    {
        mouse_show(&mouse);

        if (mouse_in(15, 675, 160, 735))  // ���ذ�ť
        {
            mouse_trans(HAND);
            if (mouse_press(15, 675, 160, 735))
            {
                *page = 0;  // ����������
                delay(200);
                break;
            }
            continue;
        }
        mouse_trans(CURSOR);
        delay(15);
    }
}
