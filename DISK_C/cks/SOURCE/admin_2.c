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
            highlight_switch_user(num, *sidepage);   //������ť�л�
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
}

/*��¼��Ϣ��ʾ��32���֣���puthz������*/
void record_display(int x, int y, Record rec)
{
    AREA AP[14] = {0};
    char str[24] = {0};
    char * week[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    area_read(AP);          //��ȡ�ص���Ϣ

    bar1(x+10, y, x+10+800, y+400, 65533);   //���Ʊ���
    puthz(x+10, y, "��¼��Ϣ", 32, 33, 0);
    puthz(x+10, y+10+34, "Υͣʱ�䣺", 32, 33, 0);
    puthz(x+10, y+10+2*34, "Υͣ�ص㣺", 32, 33, 0);
    puthz(x+10, y+10+3*34, "�û��Ķ�״̬��", 32, 33, 0);
    puthz(x+10, y+10+4*34, "����״̬��", 32, 33, 0);
    sprintf(str, "%04d/%02d/%02d %s %02d:%02d:%02d",
            rec.year, rec.month, rec.day, week[rec.week], rec.hour, rec.minute, rec.second);
    put_asc16_size(x+10+33*5, y+10+34, 2, 2, str, 0);
    puthz(x+10+33*5, y+10+34*2, AP[rec.place].name, 32, 33, 0);
    if(rec.readif == 0)
    {
        puthz(x+10+33*7, y+10+34*3, "δ��", 32, 33, 0);
    }
    else
    {
        puthz(x+10+33*7, y+10+34*3, "�Ѷ�", 32, 33, 0);
    }
    if(rec.appeal_state == 0)
    {
        puthz(x+10+33*7, y+10+34*4, "δ����", 32, 33, 0);
    }
    else if(rec.appeal_state == 1)
    {
        puthz(x+10+33*7, y+10+34*4, "������", 32, 33, 0);
    }
    else if(rec.appeal_state == 2)
    {
        puthz(x+10+33*7, y+10+34*4, "���߳ɹ�", 32, 33, 0);
    }
    else if(rec.appeal_state == 3)
    {
        puthz(x+10+33*7, y+10+34*4, "����ʧ��", 32, 33, 0);
    }
}

/*��¼�������*/
void record_select_ctrl(int x, int y, int * num, int * sidepage, int * page)
{
    int pos, rnum, rnum_select, i, j, k, rlistlen;
    int  flag = 0, flag2 = 0, esc = 0;
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
                if(mouse_in(x+250, y+200, x+250+80, y+200+30))  //������ɾ��
                {
                    mouse_trans(HAND);
                    if(mouse_press(x+250, y+200, x+250+80, y+200+30))
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
                if(mouse_in(x+350, y+200, x+350+80, y+200+30))  //������ȷ��
                {
                    mouse_trans(HAND);
                    if(mouse_press(x+350, y+200, x+350+80, y+200+30))
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
                            record_display(210, 300, temp);   //��ʾ��¼��Ϣ
                        }
                    }
                    continue;
                }
            }


            
            if(mouse_in(x+50, y+200, x+50+150, y+200+30))  //������������ҳ
            {
                mouse_trans(HAND);
                if(mouse_press(x+50, y+200, x+50+80, y+200+30))
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