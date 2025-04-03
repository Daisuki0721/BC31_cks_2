#include <allfunc.h>

/*�û����������ܿغ���*/
void user_interface(int unum, int * func)
{
    int page=0;

    struct USER user = {"\0", "\0", 0, 0, "\0", "\0", "\0", 0, 0};	//�û�
	UserList UL = {NULL, 0, 0};          //���Ա�
	InitUList(&UL);           //�������Ա�
	ReadAllUser(&UL);         //��ȡ�����û�  
	user = UL.elem[unum];       //�õ���ǰ�û�
	DestroyUList(&UL);        //�������Ա�

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    g_user_interface();

    mouse_on(mouse);

    if(!user.flag)
    {
        userinfo_complete(user, &page);        //�����û���Ϣ
    }

    while(1)
    {
        switch(page)
        {
            case 0:
            {
                user_main_panel(&page, user);     //�û��������
                break;
            }
            case 1:
            {
                user_record_panel(&page);      //�û�Υͣ��¼���
                break;
            }
            case 2:
            {
                user_dispose_panel(&page);      //�û�Υͣ�������
                break;
            }
            case 3:
            {
                user_range_panel(&page);        //�û�ͣ����Χ��ѯ���
                break;
            }
            case 4:
            {
                user_notice_panel(&page);       //�û�������֪���
                break;
            }
            case 5:
            {
                user_mail_panel(&page, unum);         //�û��������
                break;
            }
            case 6:
            {
                user_info_panel(&page, unum);         //�û���Ϣ���
                break;
            }
            case 7:
            {
                user_FAQ_panel(&page);          //�û������������
                break;
            }
            case 8:
            {
                user_exit(&page, &func);         //�û��ǳ���ע������ط�func��һ��ָ�룡��
                break;
            }
            default:
            {
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

/*�û����������*/
void user_main_panel(int * page, USER user)
{
    mouse_off(&mouse);
    g_user_main_panel();        //�����û��������
    mail_new_confirm(user, 155, 455);        //����Ƿ������ʼ�
    mouse_on(mouse);

    /*�û��������ѡ��*/
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

/*�û��ǳ�*/
void user_exit(int * page, int * func)
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

/*�û������������*/
void g_user_interface(void)
{
    char str[20];
    bar1(0, 0, 1024, 768, 34429);
    Line_Thick(180, 0, 180, 768, 1, 0);
    Line_Thick(0, 120, 180, 120, 1, 0);
    bar1(182, 0, 1024, 768, 65533);
    Readbmp64k(0, 0, "bmp\\hust1.bmp");
}

/*�����û��������*/
void g_user_main_panel(void)
{
    int i;
    char * proj[8]={"Υͣ��¼", "Υͣ����", "��Χ��ѯ", "������֪",
        "����", "������Ϣ", "��������", "�˳���¼"};
    clear_window(ALLBOARD);
    for(i=0; i<8; i++)
    {
        rounded_button_d(15, 150+i*75, 145, 60, proj[i], 5, 65498);
    }
    puthz(602-84, 324, "�𾴵��û�", 32, 34, 0);
    puthz(602-254, 364, "��ӭʹ��У԰������Υͣ����ϵͳ", 32, 34, 0);
    puthz(602-228, 404, "�������ѡ����Ҫ�����ҵ��", 32, 34, 0);
}

/*�û��˳���������*/
void g_user_exit_video(void)
{
    bar1(0, 0, 1024, 768, 34429);
    Readbmp64k(423, 250, "bmp\\hust2.bmp");
    puthz(70, 400, "��л��ʹ�á�У԰������Υͣ����ϵͳ", 48, 52, 0);
    puthz(278, 460, "ף��������죬�ټ���", 48 ,52, 0);
    puthz(600, 600, "����������������", 32, 34, 33808);
    getch();
}

/*�û���Ϣ���ƺ���*/
void userinfo_complete(USER user, int * page)
{
    int carbodyflag = 1, telflag = 1, mailflag = 1, i = 0, j = 0, flag = 0;
    char * pt = NULL;

    mouse_off(&mouse);
    mouse_trans(CURSOR);

    /*����������Ϣ����*/
    bar1(602-205, 384-205, 602+205, 384+165, 33808);
    bar1(602-200, 384-200, 602+200, 384+160, 65530);
    puthz(435, 200, "�����������û���Ϣ��", 24, 26, 0);
    puthz(430, 250, "���ƺţ�", 24, 26, 0);
    bar2(530, 245, 570, 285, 0);
    bar2(575, 245, 770, 285, 0);
    puthz(451, 300, "�绰��", 24, 26, 0);
    bar2(530, 295, 770, 335, 0);
    puthz(451, 350, "���䣺", 24, 26, 0);
    bar2(530, 345, 770, 385, 0);
    puthz(451, 400, "�Ƿ�ΪУ����Ա", 24, 24, 0);
    bar2(625, 402, 645, 422, 0);
    carhead_keyboard(397, 555);     //�����������

    rounded_button_d(432, 470, 150, 60, "ȡ��", 3, 65498);
    rounded_button_d(622, 470, 150, 60, "ȷ��", 3, 65498);

    mouse_on(mouse);

    while(1)
    {
        carbodyflag = 1; 
        telflag = 1;
        mailflag = 1;
        mouse_show(&mouse);
        if(mouse_in(575, 245, 770, 285))    //���������
        {
            mouse_trans(TEXT);
            if(mouse_press(575, 245, 770, 285))
            {
                mouse_off(&mouse);
                bar1(576, 246, 769, 284, 65530);
                strcpy(user.carbody, "\0");
                Getinfo(578, 248, user.carbody, 6, 576, 246, 769, 284);
                strupr(user.carbody);       //������ת��Ϊ��д
                mouse_on(mouse);
            }
            continue;
        }
        else if(mouse_in(530, 295, 770, 335))   //�绰�����
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
        else if(mouse_in(530, 345, 770, 385))    //���������
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
        else if(mouse_in(625, 402, 645, 422))       //�Ƿ�ΪУ����Ա
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
        else if(mouse_in(622, 470, 772, 530))     //ȷ����ť
        {
            mouse_trans(HAND);
            if(mouse_press(622, 470, 772, 530))
            {
                if(user.carhead>0)      //���ѡ���˳���ͷ
                {
                    if(strlen(user.carbody)>0)      //������ƺŲ�Ϊ��
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
                        if(carbodyflag)             //������ƺŸ�ʽ��ȷ
                        {
                            if(strlen(user.mail)>0)       //����绰��Ϊ��
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
                                if(telflag)        //����绰��ʽ��ȷ
                                {
                                    if(strlen(user.mail)>0)     //������䲻Ϊ��
                                    {
                                        if(!(pt = strchr(user.mail, '@')))
                                        {
                                            mailflag = 0;
                                        }
                                        if(!(strstr(pt, ".com")))
                                        {
                                            mailflag = 0;
                                        }
                                        if(mailflag)        //��������ʽ��ȷ
                                        {
                                            user.flag=1;        //���沢�˳�ѭ��
                                            UpdataUser(user);
                                            *page = 0;
                                            break;
                                        }
                                        else
                                        {
                                            prt_hz24(602, 440, "�����ʽ����ȷ��",63488, "HZK\\Hzk24h");
                                            delay(1500);
                                            bar1(602, 440, 794, 466, 65530);
                                        }
                                    }
                                    else
                                    {
                                        prt_hz24(622, 440, "����Ϊ�գ�",63488, "HZK\\Hzk24h");
                                        delay(1500);
                                        bar1(622, 440, 772, 466, 65530);
                                    }
                                }
                                else
                                {
                                    prt_hz24(602, 440, "�绰��ʽ����ȷ��",63488, "HZK\\Hzk24h");
                                    delay(1500);
                                    bar1(602, 440, 794, 466, 65530);
                                }
                            }
                            else
                            {
                                prt_hz24(622, 440, "�绰Ϊ�գ�",63488, "HZK\\Hzk24h");
                                delay(1500);
                                bar1(622, 440, 772, 466, 65530);
                            }
                        }
                        else
                        {
                            prt_hz24(578, 440, "���ƺŸ�ʽ����ȷ��",63488, "HZK\\Hzk24h");
                            delay(1500);
                            bar1(578, 440, 794, 466, 65530);
                        }
                    }
                    else
                    {
                        prt_hz24(622, 440, "���ƺ�Ϊ�գ�",63488, "HZK\\Hzk24h");
                        delay(1500);
                        bar1(622, 440, 772, 466, 65530);
                    }
                }
            } 
            continue;
        }
        else if(mouse_in(432, 470, 582, 530))       //ȡ����ť
        {
            mouse_trans(HAND);
            if(mouse_press(432, 470, 582, 530))
            {
                *page = -1;
                break;
            }
            continue;
        }
        for(i=0; i<4; i++)                    //����ͷ����
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