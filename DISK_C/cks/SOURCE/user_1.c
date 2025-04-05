#include <allfunc.h>

/*�û�Υͣ��¼���*/
void user_record_panel(int * page, int unum)
{
    int sidepage = 1;	//��ǰ����ҳ��
    UserList UL = {NULL, 0, 0};          //�û����Ա�
    USER user = {0};	//�û�
    InitUList(&UL);           //�������Ա�
    ReadAllUser(&UL);         //��ȡ�����û�
    user = UL.elem[unum];       //�õ���ǰ�û�
    DestroyUList(&UL);        //�������Ա�

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    g_user_record_panel(sidepage, user);

    mouse_on(mouse);

    user_record_panel_ctrl(page, &sidepage, user);
}

/*�û����������ƺ���*/
void user_record_panel_ctrl(int * page, int * sidepage, USER user)
{
    static int current_sidepage = 1;	//��ǰ����ҳ��
    int rnum = 0;

    while(1)
    {
        if(current_sidepage != *sidepage)    //�����ҳ���ػ����   
        {
            mouse_off(&mouse);
            g_user_record_panel(*sidepage, user);
            current_sidepage = *sidepage;
            mouse_on(mouse);
        }
        else
        {
            highlight_switch_record(user, rnum, *sidepage);   //������ť�л�
        }
        while(1)
        {
            mouse_show(&mouse);

            record_info_display_ctrl(user, &rnum, sidepage, page);  //��¼��Ϣ��ʾ/����
            break;
        }
        if(!*page)     //���ѡ���˳�������ѭ��
        {
            current_sidepage = 1;
            break;  
        }
    }
}

/*�û���¼�����ƺ���*/
void g_user_record_panel(int sidepage, USER user)
{
    int i, pos, rnum;
    char str[20] = {0};
    RecList RL = {NULL, 0, 0};          //��¼���Ա�

    ReadAllRec(user, &RL);         //��ȡ���м�¼
    pos = 7 * (sidepage - 1);		//�����������

    clear_window(ALLBOARD);

    for(i=0, rnum = pos; (rnum < pos + 7) && (rnum < RL.length); rnum++, i++)       //���Ʒ�ҳ
    {
        sprintf(str, "record%d", rnum+1);
        rounded_button_asc(15, 150+i*75, 145, 60, str, 5, 65498);
    }
	if(!(sidepage == 1))
	{
		prt_hz16(20, 680, "��һҳ", 63519, "hzk\\hzk16");
	}
	if(pos + 7 < RL.length)
	{
		prt_hz16(100, 680, "��һҳ", 63519, "hzk\\hzk16");
	}
    prt_hz16(53, 720, "�����ϼ�", 63519, "hzk\\hzk16");

    DestroyRList(&RL);      //�������Ա�
}

/*�û���¼��Ϣ��ʾ���ƺ���*/
void record_info_display_ctrl(USER user, int * rnum, int * sidepage, int * page)
{
    int i, k, esc = 0, flag = 0, pos = 0;
    RecList RL = {NULL, 0, 0};          //��¼���Ա�

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    clear_window(MAINBOARD);
    if(user.record_id > 0)
    {
        record_display_user(200, 50, user, *rnum);   //��ӡ��¼����
    }
    rounded_button_d(500, 10, 220, 35, "�鿴��¼״̬ͳ��", 5, 34429);

    mouse_on(mouse);

    ReadAllRec(user, &RL);         //��ȡ���м�¼
    pos = 7 * (*sidepage - 1);		//�����������

    while(1)
    {
        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);
            if(RL.length == 0)   //���û���ʼ�
            {
                puthz(15, 150+2, "��ǰû�м�¼��", 24, 25, 0);
            }

            for(k = 0; (k < 7) && (k+(*sidepage-1)*7) < RL.length; k++)          //�ʼ�ѡ��ť
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(15, 150+k*75, 160, 210+k*75))
                    {
                        *rnum = k + (*sidepage-1)*7;      //�ʼ����
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
            if(flag)
            {
                flag = 0;
                continue;
            }

            if(mouse_in(500, 10, 590+220, 10+35))
            {
                mouse_trans(HAND);
                if(mouse_press(500, 10, 590+220, 10+35))
                {
                    RecState_list(500, 50, user);   //��¼״̬ͳ��
                    delay(200);
                    break;
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

            if((mouse_in(100, 680, 100+24*3, 680+24)) && (*sidepage * 7 <  ReadRecNum(user)))  //���Ʒ�ҳ
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
            DestroyRList(&RL);      //�������Ա�
            mouse_on(mouse);
            break;
        }
    }
}

/*�û���¼��Ϣ��ʾ����*/
void record_display_user(int x, int y, USER user, int rnum)
{
    Record rec = {0};
    RecList RL = {NULL, 0, 0};          //��¼���Ա�
    AREA AP[14] = {0};
    char str[24] = {0};
    char * week[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

    ReadAllRec(user, &RL);         //��ȡ���м�¼
    rec = RL.elem[rnum];           //��ȡ��¼
    DestroyRList(&RL);            //�������Ա�

    area_read(AP);          //��ȡ�ص���Ϣ

    bar1(x+10, y, x+10+800, y+400, 65533);   //���Ʊ���
    puthz(x+10, y, "��¼��Ϣ", 32, 33, 0);
    puthz(x+10, y+10+34, "Υͣ��ţ�", 32, 33, 0);
    puthz(x+10, y+10+2*34, "Υͣʱ�䣺", 32, 33, 0);
    puthz(x+10, y+10+3*34, "Υͣ�ص㣺", 32, 33, 0);
    puthz(x+10, y+10+4*34, "�ʼ��Ķ�״̬��", 32, 33, 0);
    puthz(x+10, y+10+5*34, "ȷ�ϡ�����״̬��", 32, 33, 0);
    puthz(x+10, y+10+6*34, "ץ����Ƭ��", 32, 33, 0);
    sprintf(str, "%d", rnum+1);
    put_asc16_size(x+10+33*5, y+10+34, 2, 2, str, 0);
    sprintf(str, "%04d/%02d/%02d %s %02d:%02d:%02d",
            rec.year, rec.month, rec.day, week[rec.week], rec.hour, rec.minute, rec.second);
    put_asc16_size(x+10+33*5, y+10+34*2, 2, 2, str, 0);
    puthz(x+10+33*5, y+10+34*3, AP[rec.place].name, 32, 33, 0);
    if(rec.readif == 0)
    {
        puthz(x+10+33*7, y+10+34*4, "δ��", 32, 33, 0);
    }
    else if(rec.readif == 1)
    {
        puthz(x+10+33*7, y+10+34*4, "�Ѷ�", 32, 33, 0);
    }
    else if(rec.readif == 2)
    {
        puthz(x+10+33*7, y+10+34*4, "����", 32, 33, 0);
    }
    if(rec.appeal_state == 0)
    {
        puthz(x+10+33*8, y+10+34*5, "δ����", 32, 33, 0);
    }
    else if(rec.appeal_state == 1)
    {
        puthz(x+10+33*8, y+10+34*5, "��ȷ��", 32, 33, 0);
    }
    else if(rec.appeal_state == 2)
    {
        puthz(x+10+33*8, y+10+34*5, "������", 32, 33, 64384);
    }
    else if(rec.appeal_state == 3)
    {
        puthz(x+10+33*8, y+10+34*5, "���߳ɹ�", 32, 33, 2016);
    }
    else if(rec.appeal_state == 4)
    {
        puthz(x+10+33*8, y+10+34*5, "����ʧ��", 32, 33, 63488);
    }
    else if(rec.appeal_state == 5)
    {
        puthz(x+10+33*8, y+10+34*5, "���߳ɹ���ȷ��", 32, 33, 0);
    }
    else if(rec.appeal_state == 6)
    {
        puthz(x+10+33*8, y+10+34*5, "����ʧ����ȷ��", 32, 33, 0);
    }
    else if(rec.appeal_state == 7)
    {
        puthz(x+10+33*8, y+10+34*5, "��������", 32, 33, 0);
    }
}

/*Υͣ״̬ͳ�������˵�*/
void RecState_list(int x, int y, USER user)
{
    int buffer_id;
    mouse_off(&mouse);

    buffer_id = SaveMenuBuffer(x-1, y-1, x+470+1, y+280+1);

    bar1(x, y, x+470, y+280, 33808);
    bar1(x+5, y+5, x+465, y+275, 65530);
            
    record_state_display(x+5, y+15, user, 0);   //��ʾ��¼״̬

    mouse_on(mouse);

    while(1)
    {
        sys_time(200, 20);
        mouse_show(&mouse);

        if(mouse_press(0, 0, 1024, 768))   //����ٴε�������˳�
        {
            mouse_off(&mouse);
            RestoreMenuBuffer(x-1, y-1, x+470+1, y+280+1, buffer_id);   //�ָ��˵�
            mouse_on(mouse);
            ClearMenuBuffer();   //����˵�����
            return;
        }

        mouse_trans(CURSOR);
        delay(15);
    }
}