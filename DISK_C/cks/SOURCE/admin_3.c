#include <allfunc.h>

/*����Ա�û��������*/
void admin_user_panel(int * page)
{
    static int sidepage = 1;

    mouse_off(&mouse);  
    mouse_trans(CURSOR);
    delay(100);

    g_admin_user_panel(sidepage);

    mouse_on(mouse);

    admin_user_panel_ctrl(&sidepage, page);
}

/*����Ա�û�����������*/
void admin_user_panel_ctrl(int * sidepage, int * page)
{
    static int current_sidepage = 1;
    int unum = 0;

    while(1)
    {
        if(current_sidepage != *sidepage)    //�����ҳ���ػ����
        {
            mouse_off(&mouse);
            g_admin_record_panel(*sidepage);
            current_sidepage = *sidepage;
            mouse_on(mouse);
        }
        else
        {
            highlight_switch_user(unum, *sidepage);   //������ť�л�
        }
        while(1)
        {
            userinfo_display_ctrl(&unum, sidepage, page);  //�û���Ϣ��ʾ
            break;
        }
        if(!*page)     //���ѡ���˳�������ѭ��
        {
            current_sidepage = 1;
            break;  
        }
    }
}

/*���ƹ����û����*/
void g_admin_user_panel(int sidepage)
{
    int i, pos, unum;
    UserList UL = {NULL, 0, 0};          //�û����Ա�
    InitUList(&UL);           //�������Ա�
    ReadAllUser(&UL);         //��ȡ�����û�
    pos = 7 * (sidepage - 1);		//�����������

    clear_window(ALLBOARD);
    for(i=0, unum = pos; (unum < pos + 7) && (unum < UL.length); unum++, i++)
    {
        rounded_button_asc(15, 150+i*75, 145, 60, UL.elem[unum].name, 5, 65498);
    }
	if(!(sidepage == 1))
	{
		prt_hz16(20, 680, "��һҳ", 63519, "hzk\\hzk16");
	}
	if(pos + 7 < UL.length)
	{
		prt_hz16(100, 680, "��һҳ", 63519, "hzk\\hzk16");
	}
    prt_hz16(53, 720, "�����ϼ�", 63519, "hzk\\hzk16");
}

/*�û���Ϣ��ʾ/����*/
void userinfo_display_ctrl(int * unum,int * sidepage, int *page)
{
    int pos, rnum, k, i;
    int  flag = 0, esc = 0;
    int carbodyflag = 1, telflag = 1, mailflag = 1;
    char str[3];
    char * pt = NULL;
    USER temp = {0}, temp_codeonly = {0};
    UserList UL = {NULL, 0, 0};          //�û����Ա�
    InitUList(&UL);           //�������Ա�
    ReadAllUser(&UL);         //��ȡ�����û�
    temp = UL.elem[*unum];
    temp_codeonly = UL.elem[*unum];   //�������޸�����
    DestroyUList(&UL);          //�������Ա�
    mouse_off(&mouse);
    
    clear_window(MAINBOARD);     //������ҳ��

    puthz(200, 50, "�û���Ϣ", 32, 33, 0);
    puthz(200, 90, "�û�����", 32, 33, 0);
    put_asc16_size(200+24*5, 90, 2, 2, temp.name, 0);
    puthz(200, 130, "���룺", 32, 33, 0);
    put_asc16_size(200+24*4, 130, 2, 2, temp.code, 0);
    puthz(200, 170, "���ƺţ�", 32, 33, 0);
    put_carhead(200+24*5, 170, temp.carhead, 32, 0);
    put_asc16_size(200+24*7, 170, 2, 2, temp.carbody, 0);
    puthz(200, 210, "�绰��", 32, 33, 0);
    put_asc16_size(200+24*4, 210, 2, 2, temp.tel, 0);
    puthz(200, 250, "���䣺", 32, 33, 0);
    put_asc16_size(200+24*4, 250, 2, 2, temp.mail, 0);
    puthz(200, 290, "�Ƿ�ΪУ����Ա��", 32, 33, 0);
    if(temp.ifin)
    {
        puthz(200+24*11, 290, "��", 32, 33, 0);
    }
    else
    {
        puthz(200+24*11, 290, "��", 32, 33, 0);
    }
    puthz(200, 330, "Υͣ������", 32, 33, 0);
    itoa(temp.record_time, str, 10);
    put_asc16_size(200+24*7, 330, 2, 2, str, 0);
    puthz(200, 370, "��Ϣ�Ƿ����ƣ�", 32, 33, 0);
    if(temp.flag)
    {
        puthz(200+24*9, 370, "��", 32, 33, 0);
    }
    else
    {
        puthz(200+24*9, 370, "��", 32, 33, 0);
    }
    bar1(200, 410, 1005, 755, 33808);   //�����û��ؼ����
    bar1(205, 415, 1000, 750, 65530); 
    puthz(215, 420, "�����û���Ϣ���", 32, 33, 0);   //�����û���Ϣ���
    puthz(215, 465, "���ƺ��޸ģ�", 32, 33, 0);   //���ƺ��޸�
    puthz(215+32, 505, "�绰�޸ģ�", 32, 33, 0);   //�绰�޸�
    puthz(215+32, 545, "�����޸ģ�", 32, 33, 0);   //�����޸�
    puthz(215, 585, "�Ƿ�ΪУ����Ա��", 32, 33, 0);   //�Ƿ�ΪУ����Ա
    bar2(215+32*6, 465, 215+32*6+32, 465+32, 0);   //����ͷ�޸������
    bar2(215+32*6+40, 465, 215+32*6+300, 465+32, 0);   //���ƺ��޸������
    bar2(215+32*6, 505, 215+32*6+300, 505+32, 0);   //�绰�޸������
    bar2(215+32*6, 545, 215+32*6+300, 545+32, 0);   //�����޸������
    bar2(215+32*8, 591, 215+32*8+20, 591+20, 0);   //�Ƿ�ΪУ����Ա��ѡ��
    if(temp.ifin)
    {
       red_tick(215+32*8, 591);   //�Ƿ�ΪУ����Ա
    }
    rounded_button_d(220, 700, 140, 40, "������ҳ", 5, 65498);   //������ҳ��ť
    rounded_button_d(550, 700, 140, 40, "��ʼ������", 5, 65498);   //��ʼ�����밴ť
    rounded_button_d(700, 700, 140, 40, "ȷ���޸�", 5, 65498);   //ȷ���޸İ�ť
    rounded_button_d(850, 700, 140, 40, "ɾ���û�", 5, 65498);   //ɾ���û���ť

    while(1)
    {

        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);

            if(mouse_in(215+32*6, 465, 215+32*6+32, 465+32))
            {
                mouse_trans(HAND);
                if(mouse_press(215+32*6, 465, 215+32*6+32, 465+32))
                {
                    temp.carhead = carhead_list(215+32*6, 465+32+2, 215+32*6, 465);   //����ͷ�����˵�
                }
                continue;
            }

            if(mouse_in(215+32*6+40, 465, 215+32*6+300, 465+32))
            {
                mouse_trans(TEXT);
                if(mouse_press(215+32*6+40, 465, 215+32*6+300, 465+32))
                {
                    mouse_off(&mouse);
                    bar1(215+32*6+40+1, 465+1, 215+32*6+300-1, 465+32-1, 65530);   //��������
                    strcpy(temp.carbody, "\0");
                    Getinfo(215+32*6+40+3, 465+3, temp.carbody, 6, 215+32*6+40+1, 465+1, 215+32*6+300-1, 465+32-1);   //��ȡ���ƺ�
                    strupr(temp.carbody);       //������ת��Ϊ��д
                    mouse_on(mouse);
                }
                continue;
            }
            
            if(mouse_in(215+32*6, 505, 215+32*6+300, 505+32))   //�޸ĵ绰
            {
                mouse_trans(TEXT);
                if(mouse_press(215+32*6, 505, 215+32*6+300, 505+32))
                {
                    mouse_off(&mouse);
                    bar1(215+32*6+1, 505+1, 215+32*6+300-1, 505+32-1, 65530);   //��������
                    strcpy(temp.tel, "\0");
                    Getinfo(215+32*6+3, 505+3, temp.tel, 11, 215+32*6+1, 505+1, 215+32*6+300-1, 505+32-1);   //��ȡ�绰
                    mouse_on(mouse);
                }
                continue;
            }

            if(mouse_in(215+32*6, 545, 215+32*6+300, 545+32))
            {
                mouse_trans(TEXT);
                if(mouse_press(215+32*6, 545, 215+32*6+300, 545+32))
                {
                    mouse_off(&mouse);
                    bar1(215+32*6+1, 545+1, 215+32*6+300-1, 545+32-1, 65530);   //��������
                    strcpy(temp.mail, "\0");
                    Getinfo(215+32*6+3, 545+3, temp.mail, MAIL_LEN, 215+32*6+1, 545+1, 215+32*6+300-1, 545+32-1);   //��ȡ����
                    mouse_on(mouse);
                }
                continue;
            }

            if(mouse_in(215+32*8, 591, 215+32*8+20, 591+20))
            {
                mouse_trans(HAND);
                if(mouse_press(215+32*8, 591, 215+32*8+20, 591+20))
                {
                    if(temp.ifin == 0)
                    {
                        mouse_off(&mouse);
                        bar1(215+32*8-3, 591-3, 215+32*8+20+3, 591+20+3, 65530);   //��������
                        bar2(215+32*8, 591, 215+32*8+20, 591+20, 0);   //��������
                        red_tick(215+32*8, 591);                        //��ΪУ����Ա
                        temp.ifin = 1;
                        mouse_on(mouse);
                        delay(300);
                    }
                    else
                    {
                        mouse_off(&mouse);
                        bar1(215+32*8-3, 591-3, 215+32*8+20+3, 591+20+3, 65530);   //��������
                        bar2(215+32*8, 591, 215+32*8+20, 591+20, 0);   //��������
                        temp.ifin = 0;
                        mouse_on(mouse);
                        delay(300);
                    }
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
            if(mouse_in(550, 700, 550+140, 700+40))     //��ʼ������
            {
                mouse_trans(HAND);
                if(mouse_press(550, 700, 550+140, 700+40))
                {
                    puthz(220, 660, "�Ƿ�Ҫ��ʼ�����룿", 32, 33, 0);
                    rounded_button_d(220+32*9, 660, 80, 32, "ȷ��", 5, 65498);   //ȡ����ť
                    rounded_button_d(220+32*9+90, 660, 80, 32, "ȡ��", 5, 65498);   //ȷ����ť 
                    while(1)
                    {
                        sys_time(200, 20);
                        mouse_show(&mouse);
                        if(mouse_in(220+32*9, 660, 220+32*9+80, 660+32))
                        {
                            mouse_trans(HAND);
                            if(mouse_press(220+32*9, 660, 220+32*9+80, 660+32))
                            {
                                strcpy(temp_codeonly.code, "123456");   //��ʼ������
                                UpdataUser(temp_codeonly);   //�����û���Ϣ
                                mouse_off(&mouse);
                                bar1(220, 660-2, 220+500, 660+32+2, 65530);   //�����ʾ��
                                puthz(220, 660, "�����ʼ���ɹ���", 32, 33, 0);
                                delay(2000);
                                bar1(220, 660-2, 220+500, 660+32+2, 65530);   //�����ʾ��
                                mouse_on(mouse);
                                break;
                            }
                            continue;
                        }
                        else if(mouse_in(220+32*9+90, 660, 220+32*9+90+80, 660+32))
                        {
                            mouse_trans(HAND);
                            if(mouse_press(220+32*9+90, 660, 220+32*9+90+80, 660+32))
                            {
                                mouse_off(&mouse);
                                bar1(220, 660-2, 220+500, 660+32+2, 65530);   //�����ʾ��  //�����ʾ��
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

            if(mouse_in(700, 700, 700+140, 700+40))     //ȷ���޸�
            {
                mouse_trans(HAND);
                if(mouse_press(700, 700, 700+140, 700+40))
                {
                    if(temp.flag == 0)   //�����Ϣ������
                    {
                        puthz(220, 660, "���û���δ������Ϣ��", 32, 33, 0);
                        delay(2000);
                        bar1(220, 660-2, 220+500, 660+32+2, 65530);
                        break;
                    }
                    else
                    {
                        puthz(220, 660, "�Ƿ񱣴��޸���Ϣ��", 32, 33, 0);
                        rounded_button_d(220+32*9, 660, 80, 32, "ȷ��", 5, 65498);   //ȷ����ť
                        rounded_button_d(220+32*9+90, 660, 80, 32, "ȡ��", 5, 65498);   //ȡ����ť 
                        while(1)
                        {
                            sys_time(200, 20);
                            mouse_show(&mouse);
                            if(mouse_in(220+32*9, 660, 220+32*9+80, 660+32))
                            {
                                mouse_trans(HAND);
                                if(mouse_press(220+32*9, 660, 220+32*9+80, 660+32))
                                {
                                    if(temp.carhead>0)      //���ѡ���˳���ͷ
                                    {
                                        if(strlen(temp.carbody)>0)      //������ƺŲ�Ϊ��
                                        {
                                            for(i=0; i<strlen(temp.carbody); i++)
                                            {
                                                if(!((temp.carbody[i]>='0'&&temp.carbody[i]<='9') || (temp.carbody[i]>='A'&&temp.carbody[i]<='Z')))
                                                {
                                                    carbodyflag = 0;
                                                    break;
                                                }
                                            }
                                            if(!(strlen(temp.carbody)==5||strlen(temp.carbody)==6))
                                            {
                                                carbodyflag = 0;
                                            }
                                            if(carbodyflag)             //������ƺŸ�ʽ��ȷ
                                            {
                                                if(strlen(temp.mail)>0)       //����绰��Ϊ��
                                                {
                                                    for(i=0; i<strlen(temp.tel); i++)
                                                    {
                                                        if(!(temp.tel[i]>='0'&&temp.tel[i]<='9'))
                                                        {
                                                            telflag = 0;
                                                            break;
                                                        }
                                                    }
                                                    if(!(strlen(temp.tel) == 11))
                                                    {
                                                        telflag = 0;
                                                            break;
                                                    }
                                                    if(telflag)        //����绰��ʽ��ȷ
                                                    {
                                                        if(strlen(temp.mail)>0)     //������䲻Ϊ��
                                                        {
                                                            if(!(pt = strchr(temp.mail, '@')))
                                                            {
                                                                mailflag = 0;
                                                            }
                                                            if(!(strstr(pt, ".com")))
                                                            {
                                                                mailflag = 0;
                                                            }
                                                            if(mailflag)        //��������ʽ��ȷ
                                                            {
                                                                temp.flag=1;        //���沢�˳�ѭ��
                                                                mouse_off(&mouse);
                                                                UpdataUser(temp);
                                                                bar1(220, 660-2, 220+500, 660+32+2, 65530);     //�����ʾ��
                                                                puthz(220, 660, "�û���Ϣ�޸ĳɹ�", 32, 33, 0);
                                                                delay(2000);
                                                                bar1(220, 660-2, 220+500, 660+32+2, 65530);   //�����ʾ��
                                                                mouse_on(mouse);
                                                                esc = 1;
                                                                break;
                                                            }
                                                            else
                                                            {
                                                                prt_hz24(220, 635, "�����ʽ����ȷ��",63488, "HZK\\Hzk24h");
                                                                delay(1500);
                                                                bar1(220, 635, 220+300, 635+24, 65530);
                                                            }
                                                        }
                                                        else
                                                        {
                                                            prt_hz24(220, 635, "����Ϊ�գ�",63488, "HZK\\Hzk24h");
                                                            delay(1500);
                                                            bar1(220, 635, 220+300, 635+24, 65530);
                                                        }
                                                    }
                                                    else
                                                    {
                                                        prt_hz24(220, 635, "�绰��ʽ����ȷ��",63488, "HZK\\Hzk24h");
                                                        delay(1500);
                                                        bar1(220, 635, 220+300, 635+24, 65530);
                                                    }
                                                }
                                                else
                                                {
                                                    prt_hz24(220, 635, "�绰Ϊ�գ�",63488, "HZK\\Hzk24h");
                                                    delay(1500);
                                                    bar1(220, 635, 220+300, 635+24, 65530);
                                                }
                                            }
                                            else
                                            {
                                                prt_hz24(220, 635, "���ƺŸ�ʽ����ȷ��",63488, "HZK\\Hzk24h");
                                                delay(1500);
                                                bar1(220, 635, 220+300, 635+24, 65530);
                                            }
                                        }
                                        else
                                        {
                                            prt_hz24(220, 635, "���ƺ�Ϊ�գ�",63488, "HZK\\Hzk24h");
                                            delay(1500);
                                            bar1(220, 635, 220+300, 635+24, 65530);
                                        }
                                    }
                                }
                                continue;
                            }
                            else if(mouse_in(220+32*9+90, 660, 220+32*9+90+80, 660+32))
                            {
                                mouse_trans(HAND);
                                if(mouse_press(220+32*9+90, 660, 220+32*9+90+80, 660+32))
                                {
                                    mouse_off(&mouse);
                                    bar1(220, 660-2, 220+500, 660+32+2, 65530);
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

            if(mouse_in(850, 700, 850+140, 700+40))
            {
                mouse_trans(HAND);
                if(mouse_press(850, 700, 850+140, 700+40))
                {
                    mouse_off(&mouse);
                    puthz(220, 660, "�Ƿ�ɾ�����û���", 32, 33, 57355);   //��ʾɾ���û�
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
                                UListDelete(*unum);        //ɾ���û�
                                mouse_off(&mouse);
                                bar1(220, 660-2, 220+500, 660+32+2, 65530);   //�����ʾ��
                                puthz(220, 660, "ɾ���û��ɹ������������ϼ�����", 32, 33, 57355);
                                delay(2000);
                                *page = 0;   //�����ϼ�
                                esc = 1;
                                mouse_on(mouse);
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
                                bar1(220, 660-2, 220+500, 660+32+2, 65530);     //�����ʾ��
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

            for(k=0; k<7; k++)      //ѡ������û�
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(15, 150, 160, 210+k*75))
                    {
                        *unum = k + (*sidepage-1)*7;      //�û����
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
            if(mouse_in(53, 720, 53+16*4, 720+16))
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

/*����ͷ�����˵�(��x2, y2��λ����ʾѡ��ĳ���)*/
int carhead_list(int x1, int y1, int x2, int y2)
{
    int buffer_id, i, j, flag;
    mouse_off(&mouse);
    bar1(215+32*6+1, 465+1, 215+32*6+32-1, 465+32-1, 65530);   //��������
    buffer_id = SaveMenuBuffer(x1-1, y1-1, x1+410+1, y1+210+1);
    carhead_keyboard(x1, y1);
    mouse_on(mouse);
    while(1)
    {
        sys_time(200, 20);
        mouse_show(&mouse);
        flag = 0;  
        for(i=0; i<4; i++)                    //����ͷ����
        {
            for(j=0; j<8; j++)
            {
                if(mouse_in(x1+13+j*48, y1+17+i*48, x1+13+j*48+40, y1+i*48+40))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(x1+13+j*48, y1+17+i*48, x1+13+j*48+40, y1+i*48+40))
                    {
                        mouse_off(&mouse);
                        bar1(x2+1, y2+1, x2+32-1, y2+32-1, 65530);   //��������
                        put_carhead(x2+4, y2+4, j+i*8+1, 24, 0);
                        RestoreMenuBuffer(x1-1, y1-1, x1+410+1, y1+210+1, buffer_id);   //�ָ��˵�
                        mouse_on(mouse);
                        return j+i*8+1;   //���س���ͷ
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

        if(mouse_press(0, 0, 1024, 768) && !mouse_in(x1, y1, x1+410, y1+210))   //�������˵��⣬���˳�
        {
            mouse_off(&mouse);
            RestoreMenuBuffer(x1-1, y1-1, x1+410+1, y1+210+1, buffer_id);   //�ָ��˵�
            mouse_on(mouse);
            return 0;
        }
        mouse_trans(CURSOR);
        delay(15);
    }
}

