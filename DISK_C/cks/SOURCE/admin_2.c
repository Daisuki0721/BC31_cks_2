#include <allfunc.h>

/*����ԱΥͣ�������*/
void admin_record_panel(int * page)
{
    static int sidepage = 1;

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    g_admin_record_panel(sidepage);   

    mouse_on(mouse);
    
    admin_record_panel_ctrl(&sidepage, page);     
}

/*����ԱΥͣ����������*/
void admin_record_panel_ctrl(int * sidepage, int * page)
{
    static int current_sidepage = 1;
    int i = 0, flag = 0, num = 0, esc = 0;
    int last_user_num = 0;
    USER last_user = {0}, now_user = {0};	//��һ���û��͵�ǰ�û�

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
            last_user_num = highlight_switch_user(num, *sidepage, &last_user, &now_user);   //������ť�л�
            appeal_new_confirm(now_user, 155, 150+(num%7)*75+5);            //���ߺ��(��ǰ�û�)
            appeal_new_confirm(last_user, 155, 150+(last_user_num%7)*75+5);   //���ߺ��(��һ���û�)
        } 

        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);

            record_select_ctrl(560, 5, &num, sidepage, page);   //��¼ѡ�����
            break;
        }
        if(!*page)     //���ѡ���˳�������ѭ��
        {
            current_sidepage = 1;
            break;  
        }
    }
}

/*���ƹ����¼���*/
void g_admin_record_panel(int sidepage)
{
    int i, pos, unum;
    UserList UL = {NULL, 0, 0};          //�û����Ա�
    InitUList(&UL);           //�������Ա�
    ReadAllUser(&UL);         //��ȡ�����û�
    pos = 7 * (sidepage - 1);		//�����������

    clear_window(ALLBOARD);
    for(i=0, unum = pos; (unum < pos + 7) && (unum < UL.length); unum++, i++)       //���Ʒ�ҳ
    {
        rounded_button_asc(15, 150+i*75, 145, 60, UL.elem[unum].name, 5, 65498);
        appeal_new_confirm(UL.elem[unum], 155, 150+i*75+5);   //���ߺ��
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

    DestroyUList(&UL);
}

/*�û���Ϣ��ʾ(�����)*/
void userinfo_display_short(int unum)
{
    char str[3];
    USER temp = {0};
    UserList UL = {NULL, 0, 0};          //�û����Ա�
    InitUList(&UL);           //�������Ա�
    ReadAllUser(&UL);         //��ȡ�����û�
    temp = UL.elem[unum];
    DestroyUList(&UL);          //�������Ա�
    
    mouse_off(&mouse);

    prt_hz16(200, 50, "�û���Ϣ", 63519, "hzk\\hzk16");
    prt_hz16(200+4*16, 76, "�û�����", 63519, "hzk\\hzk16");
    prt_asc16(330, 76, temp.name, 0);
    prt_hz16(200+4*16, 102, "����ͷ��", 63519, "hzk\\hzk16");
    put_carhead(330, 102, temp.carhead, 16, 0);
    prt_asc16(330+18, 102, temp.carbody, 0);
    prt_hz16(200, 128, "�Ƿ�ΪУ����Ա��", 63519, "hzk\\hzk16");
    if(temp.ifin)
    {
        prt_hz16(330, 128, "��", 0, "hzk\\hzk16");
    }
    else
    {
        prt_hz16(330, 128, "��", 0, "hzk\\hzk16");
    }
    prt_hz16(200+16, 154, "Υͣ��¼������", 63519, "hzk\\hzk16");
    itoa(temp.record_times, str, 10);
    prt_asc16(330, 154, str, 0);
    prt_hz16(200+3*16, 180, "���ߴ�����", 63519, "hzk\\hzk16");
    itoa(temp.appeal_times, str, 10);
    prt_asc16(330, 180, str, 0);
}

/*��¼��Ϣ��ʾ��32���֣���puthz������*/
void record_display_admin(int x, int y, Record rec)
{
    AREA AP[14] = {0};
    char str[24] = {0};
    char * week[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    area_read(AP);          //��ȡ�ص���Ϣ

    bar1(x+10, y, x+10+800, y+180, 65533);   //���Ʊ���
    puthz(x+10, y, "��¼��Ϣ", 32, 33, 0);
    puthz(x+10, y+10+34, "Υͣʱ�䣺", 32, 33, 0);
    puthz(x+10, y+10+2*34, "Υͣ�ص㣺", 32, 33, 0);
    puthz(x+10, y+10+3*34, "�û��Ķ�״̬��", 32, 33, 0);
    puthz(x+10, y+10+4*34, "ȷ�ϡ�����״̬��", 32, 33, 0);
    sprintf(str, "%04d/%02d/%02d %s %02d:%02d:%02d",
            rec.year, rec.month, rec.day, week[rec.week], rec.hour, rec.minute, rec.second);
    put_asc16_size(x+10+33*5, y+10+34, 2, 2, str, 0);
    puthz(x+10+33*5, y+10+34*2, AP[rec.place].name, 32, 33, 0);
    if(rec.readif == 0)
    {
        puthz(x+10+33*7, y+10+34*3, "δ��", 32, 33, 0);
    }
    else if(rec.readif == 1)
    {
        puthz(x+10+33*7, y+10+34*3, "�Ѷ�", 32, 33, 0);
    }
    else if(rec.readif == 2)
    {
        puthz(x+10+33*7, y+10+34*3, "����", 32, 33, 0);
    }
    if(rec.appeal_state == 0)
    {
        puthz(x+10+33*8, y+10+34*4, "δ����", 32, 33, 0);
    }
    else if(rec.appeal_state == 1)
    {
        puthz(x+10+33*8, y+10+34*4, "��ȷ��", 32, 33, 0);
    }
    else if(rec.appeal_state == 2)
    {
        puthz(x+10+33*8, y+10+34*4, "������", 32, 33, 64384);
    }
    else if(rec.appeal_state == 3)
    {
        puthz(x+10+33*8, y+10+34*4, "���߳ɹ�", 32, 33, 2016);
    }
    else if(rec.appeal_state == 4)
    {
        puthz(x+10+33*8, y+10+34*4, "����ʧ��", 32, 33, 63488);
    }
    else if(rec.appeal_state == 5)
    {
        puthz(x+10+33*8, y+10+34*4, "���߳ɹ���ȷ��", 32, 33, 0);
    }
    else if(rec.appeal_state == 6)
    {
        puthz(x+10+33*8, y+10+34*4, "����ʧ����ȷ��", 32, 33, 0);
    }
    else if(rec.appeal_state == 7)
    {
        puthz(x+10+33*8, y+10+34*4, "��������", 32, 33, 0);
    }
}

/*��¼�������*/
void record_select_ctrl(int x, int y, int * num, int * sidepage, int * page)
{
    int pos, rnum, i, j, k, rlistlen;
    int  flag = 0, flag2 = 0, esc = 0, rnum_select = -1;
    char str[3];
	USER user = {0};
	Record temp = {0};
	UserList UL = {NULL, 0, 0};          //�û����Ա�
	RecList RL = {NULL, 0, 0};          //��¼���Ա�

	InitUList(&UL);           //�������Ա�
	ReadAllUser(&UL);         //��ȡ�����û�
	user = UL.elem[*num];
	DestroyUList(&UL);        //�������Ա�

	ReadAllRec(user, &RL);       //��ȡ���м�¼
    rlistlen = RL.length;		//��ȡ��¼����

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    record_select_draw(560, 5, *num);  //���Ƽ�¼ѡ�����

    mouse_on(mouse);

    while(1)
    {
        userinfo_display_short(*num);   //��ʾ�û���Ϣ
        if(rlistlen == 0)   //���û�м�¼
        {
            bar1(x+8, y+158, x+452, y+158+30, 65530);
            puthz(x+8, y+164, "��ǰ�û�û�м�¼��", 16, 17, 0);
        }

        record_state_display(210, 500, user, 1);   //��ʾ��¼״̬

        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);
            if(rlistlen > 0)   //����м�¼
            {
                for(rnum = 0; rnum < rlistlen; rnum++)      //ѡ���¼
                {
                    j = (rnum % 12) % 4;
                    i = (rnum % 12) / 4;
                    if(mouse_in(x+8+i*150, y+10+j*37, x+8+i*150+144, y+10+j*37+30))
                    {
                        mouse_trans(HAND);
                        flag = 1;
                        if(mouse_press(x+8+i*150, y+10+j*37, x+8+i*150+144, y+10+j*37+30))
                        {
                            temp = RL.elem[rnum];
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            puthz(x+8, y+164, "��ǰѡ���¼��", 16, 17, 0);
                            sprintf(str, "%d", rnum+1);
                            prt_asc16(x+128, y+164, str, 0);
                            record_display_admin(210, 300, temp);   //��ʾ��¼��Ϣ
                            rnum_select = rnum;   //��¼ѡ��ļ�¼���
                            break;
                        }
                        continue;
                    }
                }
                if(flag)
                {
                    flag = 0;
                    continue;
                }

                if(mouse_in(x+135, y+200, x+135+110, y+200+30))     //�����û����߲˵�
                {
                    mouse_trans(HAND);
                    if(mouse_press(x+135, y+200, x+135+110, y+200+30))
                    {
                        if(temp.id == 0)   //���û��ѡ���¼
                        {
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            puthz(x+8, y+164, "����ѡ���¼��", 16, 17, 0);
                            delay(2000);
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                        }
                        else
                        {
                            temp = RL.elem[rnum_select];   //��ȡ��ǰ��¼
                            esc = appeal_deal_list(x+135, y+243, &user, rnum_select);   //��������
                            if(esc)
                            {
                                break;
                            }
                        }
                    }
                    continue;
                }

                if(mouse_in(x+260, y+200, x+260+80, y+200+30))  //������ɾ��
                {
                    mouse_trans(HAND);
                    if(mouse_press(x+260, y+200, x+260+80, y+200+30))
                    {
                        if(temp.id == 0)   //���û��ѡ���¼
                        {
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            puthz(x+8, y+164, "����ѡ���¼��", 16, 17, 0);
                            delay(2000);
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                        }
                        else
                        {
                            mouse_off(&mouse);
                            // sprintf(str, "%d", rnum_select);
                            // prt_asc16(x+8, y+164, str, 63488);
                            // getch();
                            RListDelete(user, rnum_select);
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            puthz(x+8, y+164, "ɾ����¼�ɹ���", 16, 17, 0);
                            delay(2000);
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            mouse_on(mouse);
                            esc = 1;
                        }
                    }
                    continue;
                }

                if(mouse_in(x+360, y+200, x+360+80, y+200+30))  //������ˢ��
                {
                    mouse_trans(HAND);
                    if(mouse_press(x+360, y+200, x+360+80, y+200+30))
                    {
                        if(temp.record_time == 0)   //���û��ѡ���¼
                        {
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                            puthz(x+8, y+164, "����ѡ���¼��", 16, 17, 0);
                            delay(2000);
                            bar1(x+8, y+158, x+452, y+158+30, 65530);
                        }
                        else
                        {
                            record_display_admin(210, 300, temp);   //��ʾ��¼��Ϣ
                        }
                    }
                    continue;
                }
            }


            
            if(mouse_in(x+10, y+200, x+10+110, y+200+30))  //������������ҳ
            {
                mouse_trans(HAND);
                if(mouse_press(x+10, y+200, x+10+110, y+200+30))
                {
                    *page = 0;
                    esc = 1;
                    delay(200);
                    break;
                }
                continue;
            }

            for(k=0; k<7; k++)                      //�����û���ť
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag2 = 1;
                    if(mouse_press(15, 150, 160, 210+k*75))
                    {
                        *num = k + (*sidepage-1)*7;      //�û����
                        esc = 1;
                        delay(200);
                        break;
                    }
                    break;
                }
            }
            if(esc)                                 //���������أ����˳�ѭ��
            {
                break;
            }
            if(flag2)
            {
                flag2 = 0;
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

            if(mouse_in(53, 720, 53+16*4, 720+16))      //������������ҳ
            {
                mouse_trans(HAND);
                if(mouse_press(53, 720, 53+16*4, 720+16))
                {
                    *page=0;
                    sidepage = 1;
                    esc = 1;
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
            DestroyRList(&RL);        //�������Ա�
            break;
        }
    }    
}

/*�û���¼״̬��ӡ*/
void record_state_display(int x, int y, USER user, int ifadmin)
{
    char str[3];
    RecState recstate = {0};

    RecStateCount(user, &recstate);   //��ȡ��¼״̬ͳ��

    if(ifadmin)   //����ǹ���Ա
    {
        puthz(x+10, y, "��ǰ�û���¼״̬ͳ��", 32, 33, 0);
    }
    else
    {
        puthz(x+10, y, "����Υͣ��¼״̬ͳ��", 32, 33, 0);
    }
    
    puthz(x+10, y+10+34, "δ�����¼����", 32, 33, 0);
    puthz(x+10, y+10+2*34, "��ȷ�ϼ�¼����", 32, 33, 0);
    puthz(x+10, y+10+3*34, "�����м�¼����", 32, 33, 0);
    puthz(x+10, y+10+4*34, "���߳ɹ���¼����", 32, 33, 0);
    puthz(x+10, y+10+5*34, "����ʧ�ܼ�¼����", 32, 33, 0);
    puthz(x+10, y+10+6*34, "�������߼�¼����", 32, 33, 0);
    itoa(recstate.not_appeal, str, 10);
    put_asc16_size(x+10+33*7, y+10+34*1, 2, 2, str, 0);
    itoa(recstate.confirmed,str ,10);
    put_asc16_size(x+10+33*7,y +10 +34*2 ,2 ,2 ,str ,0 );
    itoa(recstate.appealed,str ,10);
    put_asc16_size(x +10 +33*7,y +10 +34*3 ,2 ,2 ,str ,0 );
    itoa(recstate.appealed_success,str ,10);
    put_asc16_size(x +10 +33*8,y +10 +34*4 ,2 ,2 ,str ,0 );
    itoa(recstate.appealed_fail,str ,10);
    put_asc16_size(x +10 +33*8,y +10 +34*5 ,2 ,2 ,str ,0 );
    itoa(recstate.appealed_cancel,str ,10);
    put_asc16_size(x +10 +33*8,y +10 +34*6 ,2 ,2 ,str ,0 );
}

/*�����û����ߺ��*/
void appeal_new_confirm(USER user, int x, int y)
{
    int i;
    char temp[3] = {0};

    if(user.appeal_times <= 0)   //���û������
    {
        return;       //ֱ�ӷ���  
    }

    if(user.appeal_times < 10)
    {
        Circlefill(x, y, 10, 63488);
        sprintf(temp, "%d", user.appeal_times);
        prt_asc16(x-3, y-8, temp, 65535);
    }
    else if(user.appeal_times >= 10)
    {
        Circlefill(x, y, 10, 63488);
        sprintf(temp, "%d", user.appeal_times);
        prt_asc16(x-8, y-8, temp, 65535);
    }
}

/*�û����ߴ��������˵���0Ϊδ�ɹ�����1Ϊ�ɹ�����*/
int appeal_deal_list(int x, int y, USER * user, int rec_num)
{
    int buffer_id;
    Record rec = {0};
    RecList RL = {NULL, 0, 0};          //��¼���Ա�
    ReadAllRec(*user, &RL);   //��ȡ���м�¼
    rec = RL.elem[rec_num];   //��ȡ��ǰ��¼
    DestroyRList(&RL);        //�������Ա�

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    buffer_id = SaveMenuBuffer(x-1, y-1, x+140+1, y+175+1);

    bar1(x, y, x+140, y+175, 33808);   //���Ʊ���
    bar1(x+5, y+5, x+135, y+170, 65530);   

    puthz(x+7, y+7, "���ߴ���", 24, 25, 0);   //���Ʊ���
    if(rec.appeal_state == 2)
    {
        rounded_button_d(x+15, y+35, 110, 30, "���߳ɹ�", 3, 65498);   //���߳ɹ�
        rounded_button_d(x+15, y+75, 110, 30, "����ʧ��", 3, 65498);   //����ʧ��
    }
    else
    {
        rounded_button_d(x+15, y+35, 110, 30, "���߳ɹ�", 3, 33808);   //���߳ɹ�
        rounded_button_d(x+15, y+75, 110, 30, "����ʧ��", 3, 33808);   //����ʧ��
    }
    
    mouse_on(mouse);

    while(1)
    {
        sys_time(200, 20);
        mouse_show(&mouse);
        
        if(mouse_in(x+15, y+35, x+15+110, y+35+30))
        {
            mouse_trans(HAND);
            if(mouse_press(x+15, y+35, x+15+110, y+35+30))
            {
                if(rec.appeal_state == 2)   //�����������
                {
                    rec.appeal_state = 3;   //���߳ɹ�
                    rec.readif = 2;        //����
                    UpdataRec(*user, rec, rec_num);   //���¼�¼
                    (*user).appeal_times--;   //�������ߴ���
                    UpdataUser(*user);      //�����û���Ϣ
                    bar1(x+15, y+115, x+15+110, y+115+16, 65530);
                    puthz(x+15, y+115, "���û����߳ɹ���", 16, 16, 0);
                    delay(2000);
                    return 1;
                }
                else
                {
                    bar1(x+15, y+115, x+15+110, y+115+16, 65530);
                    puthz(x+15, y+115, "���û�δ���ߣ�", 16, 16, 63488);
                }
            }
            continue;
        }

        if(mouse_in(x+15, y+75, x+15+110, y+75+30))
        {
            mouse_trans(HAND);
            if(mouse_press(x+15, y+75, x+15+110, y+75+30))
            {
                if(rec.appeal_state == 2)   //�����������
                {
                    rec.appeal_state = 4;   //����ʧ��
                    rec.readif = 2;        //����
                    UpdataRec(*user, rec, rec_num);   //���¼�¼
                    bar1(x+15, y+115, x+15+110, y+115+16, 65530);
                    puthz(x+15, y+115, "���û�����ʧ�ܣ�", 16, 16, 0);
                    delay(2000);
                    return 1;
                }
                else
                {
                    bar1(x+15, y+115, x+15+110, y+115+16, 65530);
                    puthz(x+15, y+115, "���û�δ���ߣ�", 16, 16, 63488);
                }
            }
            continue;
        }

        if(mouse_press(0, 0, 1024, 768) && !mouse_in(x, y, x+140, y+175))   //�������˵��⣬���˳�
        {
            mouse_off(&mouse);
            RestoreMenuBuffer(x-1, y-1, x+140+1, y+175+1, buffer_id);   //�ָ��˵�
            mouse_on(mouse);
            ClearMenuBuffer();   //����˵�����
            return 0;
        }
        mouse_trans(CURSOR);
        delay(15);
    }
}