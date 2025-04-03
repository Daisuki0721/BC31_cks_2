#include <allfunc.h>

/*�����޸�������غ���*/
void admin_rule_panel(int * page)
{
    static int sidepage = 1;

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    g_admin_rule_panel(sidepage);

    mouse_on(mouse);

    admin_rule_panel_ctrl(&sidepage, page);
}

/*����Ա�������������*/
void admin_rule_panel_ctrl(int * sidepage, int * page)
{
    static int current_sidepage = 1;
    int anum = 0;

    while(1)
    {
        if(current_sidepage != *sidepage)    //�����ҳ���ػ����
        {
            mouse_off(&mouse);
            g_admin_rule_panel(*sidepage);
            current_sidepage = *sidepage;
            mouse_on(mouse);
        }
        else
        {
            highlight_switch_area(anum, *sidepage);   //������ť�л�
        }
        while(1)
        {
            areainfo_display_ctrl(&anum, sidepage, page);  //�ص���Ϣ��ʾ
            break;
        }
        if(!*page)     //���ѡ���˳�������ѭ��
        {
            current_sidepage = 1;
            break;  
        }
    }
}

/*���ƹ���������*/
void g_admin_rule_panel(int sidepage)
{
    int i;
    AREA AP[14];
    area_read(AP);          //��ȡ�ص���Ϣ
    clear_window(ALLBOARD);

    for(i=0; i<7; i++)
    {
        rounded_button_d(15, 150+i*75, 145, 60, AP[i+(sidepage-1)*7].name, 5, 65498);
    }
    //area_destory(AP);   //
    if(!(sidepage == 1))
        prt_hz16(20, 680, "��һҳ", 63519, "hzk\\hzk16");
    else if(!(sidepage == 2))
        prt_hz16(100, 680, "��һҳ", 63519, "hzk\\hzk16");
    prt_hz16(53, 720, "�����ϼ�", 63519, "hzk\\hzk16");
}

/*�ص���Ϣ��ʾ/����*/
void areainfo_display_ctrl(int * i, int * sidepage, int * page)
{
    int j, k;
    int time = -1, time1 = -1, time2 = -1, time3 = -1;
    int flag = 0, esc = 0, week_num = -1, ifstart = 1;
    AREA AP[14];
    AREA temp = {0};
    char str[30], str_time[3];
    char * week[7] = {"������", "����һ", "���ڶ�", "������", "������", "������", "������"};
    area_read(AP);          //��ȡ�ص���Ϣ

    mouse_off(&mouse);
    clear_window(MAINBOARD);

    sprintf(str, "·�����ƣ�%s", AP[*i].name);
    puthz(200, 50, str, 32, 33, 0);
    if(!AP[*i].allnp)
    {
        puthz(200, 90, "�Ƿ�Ϊȫ·�ν�ͣ����", 32, 33, 0);
    }
    else
    {
        puthz(200, 90, "�Ƿ�Ϊȫ·�ν�ͣ����", 32, 33, 0);
        puthz(200, 130, "Υͣʱ��Ρ�����ʼʱ�䡡����ֹʱ��", 24, 25, 0);
        for(k=0; k<7; k++)
        {
            puthz(225, 160 + k*25, week[k], 24, 25, 0);
            prt_time(383, 160 + k*25, AP[*i].timest[k]);
            prt_time(535, 160 + k*25, AP[*i].timeed[k]);
        }
    }
    bar1(200, 410, 1005, 755, 33808);   //�����û��ؼ����
    bar1(205, 415, 1000, 750, 65530); 
    puthz(215, 420, "����ص���Ϣ���", 32, 33, 0);   //�����û���Ϣ���
    puthz(215, 465, "Υͣʱ���޸ģ�", 32, 33, 0);   //�ص������޸�
    puthz(215, 505, "�Ƿ�Ϊȫ·�ν�ͣ��", 32, 33, 0);   //�Ƿ�Ϊȫ·�ν�ͣ
    bar2(215+32*7, 465, 215+32*7+96, 465+32, 0);   //Υͣʱ����޸�����ѡ���
    bar2(547, 465, 547+24*4+8, 465+32, 0);  //��ʼ/��ֹ�л���Ĭ����ʼ��
    puthz(547+4, 465+4, "��ʼʱ��", 24, 25, 0);   //��ʼʱ��
    bar2(667, 465, 667+40, 465+32, 0);          //ʱ�������
    put_asc16_size(667+40, 465+4, 2, 2, ":", 0);   //ʱ�������ð��
    bar2(727, 465, 727+40, 465+32, 0);          //ʱ�������
    put_asc16_size(727+40, 465+4, 2, 2, ":", 0);   //ʱ�������ð��
    bar2(787, 465, 787+40, 465+32, 0);          //ʱ�������
    bar2(215+32*9, 511, 215+32*9+20, 511+20, 0);   //�Ƿ�Ϊȫ·�ν�ͣ��ѡ��
    if(!AP[*i].allnp)
    {
       red_tick(215+32*9, 511);   //�Ƿ�Ϊȫ·�ν�ͣ
    }

    puthz(220, 545, "ÿ����һ��ʱ����Ϣ������һ���޸�ʱ�䰴ť��", 24, 25, 63488);   //����ʱ����Ϣ��ť

    rounded_button_d(220, 700, 140, 40, "������ҳ", 5, 65498);   //������ҳ��ť
    rounded_button_d(550, 700, 140, 40, "��ͣ�л�", 5, 65498);   //��ͣ�л���ť
    rounded_button_d(700, 700, 140, 40, "�޸�ʱ��", 5, 65498);   //ȷ���޸İ�ť
    rounded_button_d(850, 700, 140, 40, "��ʼ���ص�", 5, 65498);   //��ʼ���ص㰴ť

    mouse_on(mouse);

    while(1)
    {
        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);


            for(k=0; k<7; k++)      //ѡ������û�
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(15, 150, 160, 210+k*75))
                    {
                        *i = k + (*sidepage-1)*7;      //�ص���
                        esc = 1;
                        delay(200);
                        break;
                    }
                    break;
                }
            }
            if(esc)   //���������أ����˳�ѭ��
            {
                break;
            }
            if(flag)
            {
                flag = 0;
                continue;
            }

            if(mouse_in(667, 465, 667+40, 465+32))  //��ȡСʱ
            {
                mouse_trans(HAND);
                if(mouse_press(667, 465, 667+40, 465+32))
                {
                    mouse_off(&mouse);
                    bar1(667+1, 465+1, 667+40-1, 465+32-1, 65530);   //��������
                    strcpy(str_time, "\0\0\0");
                    Getinfo(667+3, 465+3, str_time, 2, 667+1, 465+1, 667+40-1, 465+32-1);   //��ȡ����ʱ��
                    time1 = atoi(str_time);   //ת��Ϊ����
                    if(time1 < 0 || time1 > 24)
                    {
                        puthz(220, 660, "����Сʱ�����Ϸ���", 32, 33, 63488);
                        delay(2000);
                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                        bar1(667+1, 465+1, 667+40-1, 465+32-1, 65530);          //���ʱ�������
                        time1 = -1;
                    }
                    mouse_on(mouse);
                    break;
                }
                continue;
            }
            else if(mouse_in(727, 465, 727+40, 465+32))      //��ȡ����
            {
                mouse_trans(HAND);
                if(mouse_press(727, 465, 727+40, 465+32))
                {
                    mouse_off(&mouse);
                    bar1(727+1, 465+1, 727+40-1, 465+32-1, 65530);   //��������
                    strcpy(str_time, "\0\0\0");
                    Getinfo(727+3, 465+3, str_time, 2, 727+1, 465+1, 727+40-1, 465+32-1);   //��ȡ����ʱ��
                    time2 = atoi(str_time);   //ת��Ϊ����
                    if(time2 < 0 || time2 > 59)
                    {
                        puthz(220, 660, "������������Ϸ���", 32, 33, 63488);
                        delay(2000);
                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                        bar1(727+1, 465+1, 727+40-1, 465+32-1, 65530);          //���ʱ�������
                        time2 = -1;
                    }
                    mouse_on(mouse);
                    break;
                }
                continue;
            }
            else if(mouse_in(787, 465, 787+40, 465+32))     //��ȡ����
            {
                mouse_trans(HAND);
                if(mouse_press(787, 465, 787+40, 465+32))
                {
                    mouse_off(&mouse);
                    bar1(787+1, 465+1, 787+40-1, 465+32-1, 65530);   //��������
                    strcpy(str_time, "\0\0\0");
                    Getinfo(787+3, 465+3, str_time, 2, 787+1, 465+1, 787+40-1, 465+32-1);   //��ȡ����ʱ��
                    time3 = atoi(str_time);   //ת��Ϊ����
                    if(time3 < 0 || time3 > 59)
                    {
                        puthz(220, 660, "�����������Ϸ���", 32, 33, 63488);
                        delay(2000);
                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                        bar1(787+1, 465+1, 787+40-1, 465+32-1, 65530);          //���ʱ�������
                        time3 = -1;
                    }                        
                    mouse_on(mouse);
                    break;
                }
            }

            if(mouse_in(550, 700, 550+140, 700+40))     //��ͣ�л�
            {
                mouse_trans(HAND);
                if(mouse_press(550, 700, 550+140, 700+40))
                {
                    mouse_off(&mouse);
                    if(AP[*i].allnp)
                    {
                        AP[*i].allnp = 0;
                        mouse_off(&mouse);
                        bar1(215+32*9-3, 511-3, 215+32*9+20+3, 511+20+3, 65530);   //�����ѡ��
                        bar2(215+32*9, 511, 215+32*9+20, 511+20, 0);   //�Ƿ�Ϊȫ·�ν�ͣ��ѡ��
                        red_tick(215+32*9, 511);   //ȫ·�ν�ͣ
                        area_save(AP);   //���µص���Ϣ
                        delay(300);
                        mouse_on(mouse);
                        esc = 1;
                        break;
                    }
                    else
                    {
                        AP[*i].allnp = 1;
                        mouse_off(&mouse);
                        bar1(215+32*9-3, 511-3, 215+32*9+20+3, 511+20+3, 65530);   //�����ѡ��
                        bar2(215+32*9, 511, 215+32*9+20, 511+20, 0);   //�Ƿ�Ϊȫ·�ν�ͣ��ѡ��
                        area_save(AP);   //���µص���Ϣ
                        delay(300);
                        mouse_on(mouse);
                        esc = 1;
                        break;
                    }
                }
                continue;
            }

            if(mouse_in(547, 465, 547+24*4+8, 465+32))      //��ʼ/��ֹ�л���Ĭ����ʼ��
            {
                mouse_trans(HAND);
                if(mouse_press(547, 465, 547+24*4+8, 465+32))
                {
                    if(ifstart)
                    {
                        ifstart = 0;
                        mouse_off(&mouse);
                        bar1(547+1, 465+1, 547+24*4+8-1, 465+32-1, 65530);   //��ʼ/��ֹ�л���Ĭ����ֹ��
                        puthz(547+4, 465+4, "��ֹʱ��", 24, 25, 0);   //��ʼʱ��
                        delay(300);
                        mouse_on(mouse);
                    }
                    else
                    {
                        ifstart = 1;
                        mouse_off(&mouse);
                        bar1(547+1, 465+1, 547+24*4+8-1, 465+32-1, 65530);   //��ʼ/��ֹ�л���Ĭ����ʼ��
                        puthz(547+4, 465+4, "��ʼʱ��", 24, 25, 0);   //��ʼʱ��
                        delay(300);
                        mouse_on(mouse);
                    }
                    break;
                }
                continue;
            }

            if(mouse_in(215+32*7, 465, 215+32*7+100, 465+32))       //ѡ������
            {
                mouse_trans(HAND);
                if(mouse_press(215+32*7, 465, 215+32*7+100, 465+32))
                {
                    week_num = week_list(215+32*7, 465+34, 215+32*7, 465);
                }
                continue;
            }

            if(mouse_in(220, 700, 220+140, 700+40))     //������ҳ
            {
                mouse_trans(HAND);
                if(mouse_press(220, 700, 220+140, 700+40))
                {
                    *page = 0;
                    esc = 1;
                    delay(200);
                    break;
                }
                continue;
            }
  
            if(mouse_in(700, 700, 700+140, 700+40))     //ȷ���޸�ʱ��
            {
                mouse_trans(HAND);
                if(mouse_press(700, 700, 700+140, 700+40))
                {
                    if(!AP[*i].allnp)        //�����Ϊ�ǽ�ͣģʽ
                    {
                        mouse_off(&mouse);
                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                        puthz(220, 660, "���л����ǽ�ͣģʽ������ʱ����ģ�", 32, 33, 63488);
                        delay(2000);
                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                        mouse_on(mouse);
                        break;
                    }
                    else
                    {
                        puthz(220, 660, "�Ƿ񱣴��޸�ʱ����Ϣ��", 32, 33, 0);
                        rounded_button_d(220+32*12, 660, 80, 32, "ȷ��", 5, 65498);   //ȷ����ť
                        rounded_button_d(220+32*12+90, 660, 80, 32, "ȡ��", 5, 65498);   //ȡ����ť 
                        while(1)
                        {
                            sys_time(200, 20);
                            mouse_show(&mouse);
                            if(mouse_in(220+32*12, 660, 220+32*12+80, 660+32))
                            {
                                mouse_trans(HAND);
                                if(mouse_press(220+32*12, 660, 220+32*12+80, 660+32))
                                {
                                    if(week_num < 0)   //���û��ѡ�����ڣ�����ʾ
                                    {
                                        mouse_off(&mouse);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                        puthz(220, 660, "��ѡ�����ڣ�", 32, 33, 63488);
                                        delay(2000);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                        mouse_on(mouse);
                                        break;
                                    }
                                    else if(time1 < 0)
                                    {
                                        mouse_off(&mouse);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                        puthz(220, 660, "��������ȷ��Сʱ����", 32, 33, 63488);
                                        delay(2000);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                        mouse_on(mouse);
                                        break;
                                    }
                                    else if(time2 < 0)
                                    {
                                        mouse_off(&mouse);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                        puthz(220, 660, "��������ȷ�ķ�������", 32, 33, 63488);
                                        delay(2000);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                        mouse_on(mouse);
                                        break;
                                    }
                                    else if(time3 < 0)
                                    {
                                        mouse_off(&mouse);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                        puthz(220, 660, "��������ȷ��������", 32, 33, 63488);
                                        delay(2000);
                                        bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                        mouse_on(mouse);
                                        break;
                                    }
                                    else
                                    {
                                        time = time1 * 3600 + time2 * 60 + time3;
                                        if(ifstart)
                                        {
                                            if(time < 0L)
                                            {
                                                mouse_off(&mouse);
                                                sprintf(str, "%s��ʼʱ�䲻��Ϊ�գ�", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                break;
                                            }
                                            else if(time > 86400L)
                                            {
                                                sprintf(str, "%s��ʼʱ�䲻�ܴ��ڶ�ʮ��Сʱ��", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                break;
                                            }
                                            else if(time > AP[*i].timeed[week_num])
                                            {
                                                sprintf(str, "%s��ʼʱ�䲻�ܴ�����ֹʱ�䣡", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                break;
                                            }
                                            else if(time == AP[*i].timeed[week_num])
                                            {
                                                sprintf(str, "%s��ʼʱ�䲻�ܵ�����ֹʱ�䣡", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                break;
                                            }
                                            else 
                                            {
                                                AP[*i].timest[week_num] = time;   //������ʼʱ��
                                                area_save(AP);                  //���µص���Ϣ
                                                mouse_off(&mouse);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                puthz(220, 660, "ʱ����Ϣ�޸ĳɹ���", 32, 33, 0);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                mouse_on(mouse);
                                                esc = 1;
                                                break;
                                            }    
                                        }
                                        else
                                        {
                                            if(time < 0L)
                                            {
                                                sprintf(str, "%s��ֹʱ�䲻��Ϊ�գ�", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                break;
                                            }
                                            else if(AP[*i].timeed[week_num] > 86400L)
                                            {
                                                sprintf(str, "%s��ֹʱ�䲻�ܴ��ڶ�ʮ��Сʱ��", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                break;
                                            }
                                            else if(AP[*i].timest[week_num] > time)
                                            {
                                                sprintf(str, "%s��ʼʱ�䲻�ܴ�����ֹʱ�䣡", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                break;
                                            }
                                            else if(AP[*i].timest[week_num] == time)
                                            {
                                                sprintf(str, "%s��ʼʱ�䲻�ܵ�����ֹʱ�䣡", week[week_num]);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                puthz(220, 660, str, 32, 33, 63488);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                break;
                                            }
                                            else 
                                            {
                                                AP[*i].timeed[week_num] = time;   //������ֹʱ��
                                                area_save(AP);                  //���µص���Ϣ
                                                mouse_off(&mouse);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                puthz(220, 660, "ʱ����Ϣ�޸ĳɹ���", 32, 33, 0);
                                                delay(2000);
                                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                                mouse_on(mouse);
                                                esc = 1;
                                                break;
                                            }    
                                        }
                                    }
                                }
                                continue;
                            }
                            else if(mouse_in(220+32*12+90, 660, 220+32*12+90+80, 660+32))
                            {
                                mouse_trans(HAND);
                                if(mouse_press(220+32*12+90, 660, 220+32*12+90+80, 660+32))
                                {
                                    mouse_off(&mouse);
                                    bar1(220, 660-2, 220+700, 660+32+2, 65530);
                                    mouse_on(mouse);   //�����ʾ��
                                    break;
                                }
                                continue;
                            }
                            mouse_trans(CURSOR);
                            delay(15);
                        }
                    }
                } 
                continue;
            }

            if(mouse_in(850, 700, 850+140, 700+40))     //�ص���Ϣ��ʼ��
            {
                mouse_trans(HAND);
                if(mouse_press(850, 700, 850+140, 700+40))
                {
                    mouse_off(&mouse);
                    puthz(220, 660, "�Ƿ��ʼ���õص㣿", 32, 33, 63488);   //��ʾɾ���û�
                    rounded_button_d(220+32*9, 660, 80, 32, "ȷ��", 5, 65498);   //ȷ����ť
                    rounded_button_d(220+32*9+90, 660, 80, 32, "ȡ��", 5, 65498);   //ȡ����ť
                    mouse_on(mouse);
                    while(1)
                    {
                        sys_time(200, 20);
                        mouse_show(&mouse);
                        if(mouse_in(220+32*9, 660, 220+32*9+80, 660+32))
                        {
                            mouse_trans(HAND);
                            if(mouse_press(220+32*9, 660, 220+32*9+80, 660+32))
                            {
                                temp = AP[*i];   //��ʼ���ص���Ϣ
                                temp.allnp = 1;
                                for(j=0; j<7; j++)
                                {
                                    temp.timest[j] = 28800L;
                                    temp.timeed[j] = 79200L;
                                }
                                area_update(temp, *i);   //���µص���Ϣ
                                mouse_off(&mouse);
                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                puthz(220, 660, "�ص���Ϣ��ʼ���ɹ���", 32, 33, 0);
                                delay(2000);
                                bar1(220, 660-2, 220+700, 660+32+2, 65530);   //�����ʾ��
                                mouse_on(mouse);
                                esc = 1;
                                break;
                            }
                            continue;
                        }
                        else if(mouse_in(220+32*9+90, 660, 220+32*9+80+90, 660+32))
                        {
                            mouse_trans(HAND);
                            if(mouse_press(220+32*9+90, 660, 220+32*9+80+90, 660+32))
                            {
                                mouse_off(&mouse);
                                bar1(220, 660-2, 220+700, 660+32+2, 65530);     //�����ʾ��
                                mouse_on(mouse);
                                break;
                            }
                            continue;
                        }
                        mouse_trans(CURSOR);
                        delay(15);
                    }
                }
                continue;
            }

            if((mouse_in(20, 680, 20+24*3, 680+24)) && (*sidepage > 1))  //���Ʒ�ҳ
            {
                mouse_trans(HAND);
                if(mouse_press(20, 680, 20+24*3, 680+24))
                {
                    (*sidepage)--;
                    esc = 1;
                    delay(200);
                    break;
                }
                continue;
            }
            if((mouse_in(100, 680, 100+24*3, 680+24)) && (*sidepage * 7 <  ReadUserNum()))  //���Ʒ�ҳ
            {
                mouse_trans(HAND);
                if(mouse_press(100, 680, 100+24*3, 680+24))
                {
                    (*sidepage)++;
                    esc = 1;
                    delay(200);
                    break;
                }
                continue;
            }            
            if(mouse_in(53, 720, 53+16*4, 720+16))      //������ҳ
            {
                mouse_trans(HAND);
                if(mouse_press(53, 720, 53+16*4, 720+16))
                {
                    *page=0;
                    esc = 1;
                    *sidepage = 1;
                    delay(200);
                    break;
                }
                continue;
            }
            mouse_trans(CURSOR);
            delay(15);
        }
        if(esc)               //���������أ����˳�ѭ��
        {
            mouse_off(&mouse);
            clear_window(MAINBOARD);
            mouse_on(mouse);
            break;
        }
    }
}



/*���������˵�����x2, y2��λ����ʾѡ������ڣ�*/
int week_list(int x1, int y1, int x2, int y2)
{
    int buffer_id, i, j, flag;
    mouse_off(&mouse);
    bar1(x2+1, y2+1, x2+96-1, y2+32-1, 65530);   //��������
    buffer_id = SaveMenuBuffer(x1-1, y1-1, x1+282+1, y1+210+1);
    week_keyboard(x1, y1);
    mouse_on(mouse);
    while(1)
    {
        sys_time(200, 20);
        mouse_show(&mouse);
        flag = 0;  
        for(i=0; i<4; i++)                    //����ͷ����
        {
            for(j=0; j<2; j++)
            {
                if(mouse_in(x1+13+j*128, y1+17+i*48, x1+13+j*128+120, y1+17+i*48+40))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(x1+13+j*128, y1+17+i*48, x1+13+j*128+120, y1+17+i*48+40))
                    {
                        mouse_off(&mouse);
                        bar1(x2+1, y2+1, x2+96-1, y2+32-1, 65530);   //��������
                        put_week(x2+4, y2+4, j+i*2+1, 24, 0);
                        RestoreMenuBuffer(x1-1, y1-1, x1+282+1, y1+210+1, buffer_id);   //�ָ��˵�
                        mouse_on(mouse);
                        return j+i*2+1;   //��������
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

        if(mouse_press(0, 0, 1024, 768) && !mouse_in(x1, y1, x1+282, y1+210))   //�������˵��⣬���˳�
        {
            mouse_off(&mouse);
            RestoreMenuBuffer(x1-1, y1-1, x1+282+1, y1+210+1, buffer_id);   //�ָ��˵�
            mouse_on(mouse);
            return 0;
        }
        mouse_trans(CURSOR);
        delay(15);
    }
}

