#include <allfunc.h>

/* �û���֪��� */
void user_notice_panel(int* page) 
{
    mouse_off(&mouse);
    mouse_trans(CURSOR);

    g_user_notice_panel();

    mouse_on(mouse);

    user_notice_panel_ctrl(page);
}

/*�����û���֪���*/
void g_user_notice_panel(void)
{
    clear_window(ALLBOARD);

    // ���Ʋ���
    bar1(0, 122, 178, 768, 34429);
    Line_Thick(180, 0, 180, 768, 1, 0);

    // ���Ƴ�����֪����
    puthz(200, 50, "������֪", 32, 34, 0);
    puthz(200, 125, "һ��������У԰��ͣ���涨�������ڽ�ͣ����ͣ����", 24, 26, 0);
    puthz(200, 160, "����Υͣ������¼��֪ͨ������", 24, 26, 0);
    puthz(200, 195, "�����뱣�ֳ��������ɼ����Ա�ʶ��", 24, 26, 0);
    puthz(200, 230, "�ġ��������ʣ�����ϵУ԰�����š�", 24, 26, 0);

    // ���Ʒ��ذ�ť
    rounded_button_d(15, 150 + 7 * 75, 145, 60, "����", 5, 65498);
}

/*�û���֪������*/
void  user_notice_panel_ctrl(int* page)
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