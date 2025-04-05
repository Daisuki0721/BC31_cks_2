#include <allfunc.h>

/*�û��������������*/
void user_dispose_panel(int * page, int unum)
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

    g_user_dispose_panel(sidepage, user);

    mouse_on(mouse);

    user_record_dispose_ctrl(page, &sidepage, user);
}

/*�û����������������ƺ���*/
void user_record_dispose_ctrl(int * page, int * sidepage, USER user)
{
    int rnum = 0, pnum = 0;	        //��¼���

    while(1)
    {
        mouse_off(&mouse);
        g_user_dispose_panel(*sidepage, user);
        mouse_on(mouse);
        highlight_switch_appeal(user, pnum, *sidepage);   //������ť�л�

        while(1)
        {
            mouse_show(&mouse);

            appeal_info_display_ctrl(user, &pnum, &rnum, sidepage, page);  //��¼��Ϣ��ʾ/����
            break;
        }
        if(!*page)     //���ѡ���˳�������ѭ��
        {
            break;  
        }
    }
}

/*�û����������������ƺ���*/
void g_user_dispose_panel(int sidepage, USER user)
{
    int i, pos, rnum;
    char str[20] = {0};
    RecList APL = {NULL, 0, 0};          //��¼���Ա�

    RecListToAppealList(user, &APL);         //��ȡ�������߼�¼
    pos = 7 * (sidepage - 1);		//�����������

    clear_window(ALLBOARD);

    for(i=0, rnum = pos; (rnum < pos + 7) && (rnum < APL.length); rnum++, i++)       //���Ʒ�ҳ
    {
        sprintf(str, "appeal%d", rnum+1);
        rounded_button_asc(15, 150+i*75, 145, 60, str, 5, 65498);
        if(APL.elem[rnum].appeal_state == 0)
        {
            puthz(110, 150+i*75+2, "δ����", 16, 16, 63488);
        }
        else if(APL.elem[rnum].appeal_state == 2)
        {
            puthz(110, 150+i*75+2, "������", 16, 16, 63488);
        }
        else if(APL.elem[rnum].appeal_state == 3)
        {
            puthz(94, 150+i*75+2, "���߳ɹ�", 16, 16, 2016);
        }
        else if(APL.elem[rnum].appeal_state == 4)
        {
            puthz(94, 150+i*75+2, "����ʧ��", 16, 16, 63488);
        }
        else if(APL.elem[rnum].appeal_state == 7)
        {
            puthz(94, 150+i*75+2, "���߳���", 16, 16, 63488);
        }
    }
	if(!(sidepage == 1))
	{
		prt_hz16(20, 680, "��һҳ", 63519, "hzk\\hzk16");
	}
	if(pos + 7 < APL.length)
	{
		prt_hz16(100, 680, "��һҳ", 63519, "hzk\\hzk16");
	}
    prt_hz16(53, 720, "�����ϼ�", 63519, "hzk\\hzk16");

    DestroyRList(&APL);      //�������Ա�
}

/*�û���¼��Ϣ��ʾ���ƺ���*/
void appeal_info_display_ctrl(USER user, int * pnum, int * rnum, int * sidepage, int * page)
{
    int i, k;
    int esc = 0, flag = 0, pos = 0, button1 = 0, button2 = 0;
    RecList APL = {NULL, 0, 0};          //�������Ա�

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    clear_window(MAINBOARD);
    if(user.appeal_times > 0)
    {
        appeal_display_user(200, 50, user, *pnum);   //��ӡ��¼����
    }

    RecListToAppealList(user, &APL);         //��ȡ�������߼�¼

    rounded_button_d(500, 10, 220, 35, "�鿴��¼״̬ͳ��", 5, 34429);
    if(APL.elem[*pnum].appeal_state == 0)
    {
        rounded_button_d(800, 200, 180, 35, "ȷ��", 5, 65530);
        rounded_button_d(800, 250, 180, 35, "��Ҫ����", 5, 65530);
        button1 = 1;
        button2 = 1;
    }
    else if(APL.elem[*pnum].appeal_state == 3 && APL.elem[*pnum].appeal_state == 4)
    {
        rounded_button_d(800, 200, 180, 35, "ȷ��", 5, 65530);
        button1 = 1;
    }
    else if(APL.elem[*pnum].appeal_state == 2)
    {
        rounded_button_d(800, 250, 180, 35, "��������", 5, 65530);
        button2 = 1;
    }
    else if(APL.elem[*pnum].appeal_state == 7)
    {
        rounded_button_d(800, 200, 180, 35, "ȷ��", 5, 65530);
        rounded_button_d(800, 250, 180, 35, "��������", 5, 65530);
        button1 = 1;
        button2 = 1;
    }

    mouse_on(mouse);

    pos = 7 * (*sidepage - 1);		    //�����������

    while(1)
    {
        if(APL.length == 0)   //���û���ʼ�
        {
            puthz(15, 150+2, "��ǰû����Ҫ", 24, 25, 0);
            puthz(15, 150+2+24, "����ļ�¼��", 24, 25, 0);
        }
        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);

            for(k = 0; (k < 7) && (k+(*sidepage-1)*7) < APL.length; k++)          //����ѡ��ť
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(15, 150+k*75, 160, 210+k*75))
                    {
                        *pnum = k + (*sidepage-1)*7;      //��ǰ�����ť��λ�ã�ͬʱҲ�����߱��
                        *rnum = APL.elem[*pnum].id - 1;     //������ԭ��¼���Ա��е�λ�ñ��
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

            if(mouse_in(500, 10, 590+220, 10+35))   //��¼״̬ͳ��
            {
                mouse_trans(HAND);
                if(mouse_press(500, 10, 590+220, 10+35))
                {
                    RecState_list(500, 50, user);   
                    delay(200);
                    break;
                }
                continue;
            }

            if(button1)     //�����ȷ�ϰ�ť
            {
                if(mouse_in(800, 200, 800+180, 200+35))
                {
                    mouse_trans(HAND);
                    if(mouse_press(800, 200, 800+180, 200+35))
                    {
                        if(APL.elem[*pnum].appeal_state == 0 
                            && APL.elem[*pnum].appeal_state == 7)   //δ���߻����߳���
                        {
                            APL.elem[*pnum].appeal_state = 1;   //��ȷ��  
                        }
                        else if(APL.elem[*pnum].appeal_state = 3)  //���߳ɹ�
                        {
                            APL.elem[*pnum].appeal_state = 5;   //���߳ɹ���ȷ��   
                        }
                        else if(APL.elem[*pnum].appeal_state == 4)  //����ʧ��
                        {
                            APL.elem[*pnum].appeal_state = 6;   //����ʧ����ȷ��  
                        }
                        UpdataRec(user, APL.elem[*pnum], APL.elem[*pnum].id-1); 
                        puthz(800, 172, "��ȷ�ϣ����������ϼ�", 24, 25, 0);
                        delay(2000);
                        *pnum = 0;   //����ѡ������
                        esc = 1;
                        delay(200);
                        break;
                    }
                    continue;
                }
            }

            if(button2)     //��������߲�����ť
            {
                if(mouse_in(800, 250, 800+180, 250+35))
                {
                    mouse_trans(HAND);
                    if(mouse_press(800, 250, 800+180, 250+35))
                    {
                        if(APL.elem[*pnum].appeal_state == 0)   //δ����
                        {
                            APL.elem[*pnum].appeal_state = 2;   //������
                            user.appeal_times++;   //���ߴ�����1
                            puthz(800, 172, "�����ߣ�", 24, 25, 0);
                            delay(2000);
                        }
                        else if(APL.elem[*pnum].appeal_state == 2)  //������
                        {
                            APL.elem[*pnum].appeal_state = 7;   //��������  
                            user.appeal_times--;   //���ߴ�����1
                            puthz(800, 172, "�ѳ������ߣ�", 24, 25, 0);
                            delay(2000);
                        }
                        else if(APL.elem[*pnum].appeal_state == 7)  //��������
                        {
                            APL.elem[*pnum].appeal_state = 2;   //��������  
                            user.appeal_times++;   //���ߴ�����1
                            puthz(800, 172, "���������ߣ�", 24, 25, 0);
                            delay(2000);
                        }
                        UpdataRec(user, APL.elem[*pnum], APL.elem[*pnum].id-1); 
                        UpdataUser(user);   //�����û���Ϣ
                        esc = 1;
                        delay(200);
                        break;
                    }
                    continue;
                }
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
            DestroyRList(&APL);      //�������Ա�
            mouse_on(mouse);
            break;
        }
    }
}

/*�û�������Ϣ��ʾ����*/
void appeal_display_user(int x, int y, USER user, int rnum)
{
    Record appeal = {0};
    RecList APL = {NULL, 0, 0};          //�������Ա�
    AREA AP[14] = {0};
    char str[24] = {0};
    char * week[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

    RecListToAppealList(user, &APL);         //��ȡ��������
    appeal = APL.elem[rnum];           //��ȡ����
    DestroyRList(&APL);            //�������Ա�

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
            appeal.year, appeal.month, appeal.day, week[appeal.week], appeal.hour, appeal.minute, appeal.second);
    put_asc16_size(x+10+33*5, y+10+34*2, 2, 2, str, 0);
    puthz(x+10+33*5, y+10+34*3, AP[appeal.place].name, 32, 33, 0);
    if(appeal.readif == 0)
    {
        puthz(x+10+33*7, y+10+34*4, "δ��", 32, 33, 0);
    }
    else if(appeal.readif == 1)
    {
        puthz(x+10+33*7, y+10+34*4, "�Ѷ�", 32, 33, 0);
    }
    else if(appeal.readif == 2)
    {
        puthz(x+10+33*7, y+10+34*4, "����", 32, 33, 0);
    }
    if(appeal.appeal_state == 0)
    {
        puthz(x+10+33*8, y+10+34*5, "δ����", 32, 33, 0);
    }
    else if(appeal.appeal_state == 2)
    {
        puthz(x+10+33*8, y+10+34*5, "������", 32, 33, 64384);
    }
    else if(appeal.appeal_state == 3)
    {
        puthz(x+10+33*8, y+10+34*5, "���߳ɹ�", 32, 33, 2016);
    }
    else if(appeal.appeal_state == 4)
    {
        puthz(x+10+33*8, y+10+34*5, "����ʧ��", 32, 33, 63488);
    }
    else if(appeal.appeal_state == 7)
    {
        puthz(x+10+33*8, y+10+34*5, "��������", 32, 33, 0);
    }
}

