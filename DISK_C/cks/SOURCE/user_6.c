#include <allfunc.h>

/* �û���Ϣ��� */
void user_info_panel(int* page, int unum)
{
    mouse_off(&mouse);
    mouse_trans(CURSOR);

    g_user_info_panel(unum);

    mouse_on(mouse);

    user_info_panel_ctrl(page);
}

/* �����û���Ϣ��� */
void g_user_info_panel(int unum)
{
    char record_time_str[10];

    char str[3];
    USER temp = { 0 };
    UserList UL = { NULL, 0, 0 };          // �û����Ա�
    InitUList(&UL);           // �������Ա�
    ReadAllUser(&UL);         // ��ȡ�����û�
    temp = UL.elem[unum];
    DestroyUList(&UL);          // �������Ա�

    mouse_off(&mouse);

    clear_window(ALLBOARD);

    // �����û���Ϣ
    puthz(200, 50, "�û���Ϣ", 32, 34, 0); // ����
    puthz(200, 125, "�û�����", 24, 26, 0); // �û���
    prt_asc16(330, 130, temp.name, 0);
    puthz(200, 175, "���ƺţ�", 24, 26, 0); // ���ƺ�
    put_carhead(320, 175, temp.carhead, 24, 0);
    prt_asc16(330 + 18, 180, temp.carbody, 0);
    puthz(200, 225, "�Ƿ�ΪУ����Ա��", 24, 26, 0); // �Ƿ�ΪУ����Ա
    if (temp.ifin)
    {
        puthz(330 + 100, 225, "��", 24, 26, 0); 
    }
    else
    {
        puthz(330 + 100, 225, "��", 24, 26, 0); 
    }
    puthz(200, 275, "Υͣ������", 24, 26, 0);
    itoa(temp.record_time, str, 10);
    prt_asc16(330, 280, str, 0);

    // ���Ʒ��ذ�ť
    rounded_button_d(15, 150 + 7 * 75, 145, 60, "����", 5, 65498);
}

/* �û���Ϣ������ */
void user_info_panel_ctrl(int* page)
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