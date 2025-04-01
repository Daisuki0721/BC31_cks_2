#include <allfunc.h>

/*�������������غ���*/
void admin_interface(int * func)
{
    int page=0;

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
                admin_main_panel(&page);     //����Ա�������
                break;
            }
            case 1:
            {
                admin_monitor_panel(&page);      //����Ա�鿴����ͷ���
                break;
            }
            case 2:
            {
                admin_record_panel(&page);      //����ԱΥͣ�������
                break;
            }
            case 3:
            {
                admin_user_panel(&page);        //����Ա�û��������
                break;
            }
            case 4:
            {
                admin_rule_panel(&page);
                break;
            }
            case 5:
            {
                admin_exit(&page, func);       //�����˳�
                break;
            }
        }
        if(page < 0)        //���ѡ�����˳������˳�ѭ��
        {
            *func = 0;
            break;
        }
    }
}

/*����Ա�������*/
void admin_main_panel(int * page)
{
    mouse_off(&mouse);
    g_admin_main_panel();        //���ƹ���Ա�������
    mouse_on(mouse);

    /*����Ա�������ѡ��*/
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

/*��������˳�*/
void admin_exit(int * page, int * func)
{
    mouse_off(&mouse);
    mouse_trans(CURSOR);

    /*���Ƶǳ���*/
    clear_window(MAINBOARD);                            //�������
    bar1(602-205, 384-125, 602+205, 384+125, 33808);
    bar1(602-200, 384-120, 602+200, 384+120, 65530);
    puthz(435, 310, "ȷ��Ҫ������������", 32, 35, 0);
    rounded_button_d(432, 400, 150, 60, "ȡ��", 3, 65498);
    rounded_button_d(622, 400, 150, 60, "ȷ��", 3, 65498);

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
                g_user_exit_video();      //�û��ǳ�����
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

/*�������������*/
void g_admin_interface(void)
{
    bar1(0, 0, 1024, 768, 34429);
    Line_Thick(180, 0, 180, 768, 1, 0);
    Line_Thick(0, 120, 180, 120, 1, 0);
    bar1(182, 0, 1024, 768, 65533);
    Readbmp64k(0, 0, "bmp\\hust1.bmp");
}

/*���ƹ����������*/
void g_admin_main_panel(void)
{
    int i;
    char * proj[5] = {"����ͷ", "��¼����", "�û�����", "�����޸�", "�˳�"};
    clear_window(ALLBOARD);
    for(i=0;i<5;i++)
    {
        rounded_button_d(15, 150+i*75, 145, 60, proj[i], 5, 65498);
    }
    puthz(602-101, 324, "�𾴵Ĺ���Ա", 32, 34, 0);
    puthz(602-254, 364, "��ӭʹ��У԰������Υͣ����ϵͳ", 32, 34, 0);
    puthz(602-228, 404, "�������ѡ����Ҫ�����ҵ��", 32, 34, 0);
}

/*�����˳���������*/
void g_admin_exit_video(void)
{
    bar1(0, 0, 1024, 768, 34429);
    Readbmp64k(423, 250, "bmp\\hust2.bmp");
    puthz(70, 400, "��л��ʹ�á�У԰������Υͣ����ϵͳ", 48, 52, 0);
    puthz(278, 460, "ף��������죬�ټ���", 48 ,52, 0);
    puthz(600, 600, "����������������", 32, 34, 33808);
    getch(); 
}

