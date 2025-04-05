#include <allfunc.h>

/*�û��������*/
void user_mail_panel(int * page, int unum)
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

    g_user_mail_panel(sidepage, user);

    mouse_on(mouse);

    user_mail_panel_ctrl(page, &sidepage, user);
}

/*�û����������ƺ���*/
void user_mail_panel_ctrl(int * page, int * sidepage, USER user)
{
    static int current_sidepage = 1;	//��ǰ����ҳ��
    int rnum = 0;
    RecList RL = {NULL, 0, 0};          //��¼���Ա�
    Record rec = {0};	//��¼

    while(1)
    {
        ReadAllRec(user, &RL);         //��ȡ���м�¼
        rec = RL.elem[rnum];
        DestroyRList(&RL);       
    
        if(rec.readif != 1)       //�����Ϊ�Ѷ�������Ϊ�Ѷ�
        {
            rec.readif = 1;
            UpdataRec(user, rec, rnum);	//���¼�¼
        }

        if(current_sidepage != *sidepage)    //�����ҳ���ػ����   
        {
            mouse_off(&mouse);
            g_user_mail_panel(*sidepage, user);
            current_sidepage = *sidepage;
            mouse_on(mouse);
        }
        else
        {
            highlight_switch_mail(user, rnum, *sidepage);   //������ť�л�
        }
        while(1)
        {
            mouse_show(&mouse);

            mail_info_display_ctrl(user, &rnum, sidepage, page);  //�ʼ���Ϣ��ʾ/����
            break;
        }
        if(!*page)     //���ѡ���˳�������ѭ��
        {
            current_sidepage = 1;
            break;  
        }
    }
}

/*�û����������ƺ���*/
void g_user_mail_panel(int sidepage, USER user)
{
    int i, pos, rnum;
    char str[20] = {0};
    RecList RL = {NULL, 0, 0};          //��¼���Ա�

    ReadAllRec(user, &RL);         //��ȡ���м�¼
    pos = 7 * (sidepage - 1);		//�����������

    clear_window(ALLBOARD);

    for(i=0, rnum = pos; (rnum < pos + 7) && (rnum < RL.length); rnum++, i++)       //���Ʒ�ҳ
    {
        sprintf(str, "mail%d", rnum+1);
        rounded_button_asc(15, 150+i*75, 145, 60, str, 5, 65498);
        if(RL.elem[rnum].readif == 0)
        {
            puthz(126, 150+i*75+2, "δ��", 16, 16, 63488);
        }
        else if(RL.elem[rnum].readif == 1)
        {
            puthz(126, 150+i*75+2, "�Ѷ�", 16, 16, 33808);
        }
        else if(RL.elem[rnum].readif == 2)
        {
            puthz(126, 150+i*75+2, "����", 16, 16, 33808);
        }
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

/*�û�������Ϣ��ʾ���ƺ���*/
void mail_info_display_ctrl(USER user, int * rec, int * sidepage, int * page)
{
    int i, k, esc = 0, flag = 0, pos = 0;
    RecList RL = {NULL, 0, 0};          //��¼����

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    clear_window(MAINBOARD);
    mail_print(200, 50, user, *rec+1);   //��ӡ�ʼ�����
    if(user.record_id > 0)
    {
        rounded_button_d(800, 600, 145, 45, "�鿴ץ��", 5, 65498);    //�鿴ץ�İ�ť
    }

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
                puthz(15, 150+2, "��ǰû���ʼ���", 24, 25, 0);
            }
            for(k = 0; (k < 7) && (k+(*sidepage-1)*7) < RL.length; k++)          //�ʼ�ѡ��ť
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(15, 150+k*75, 160, 210+k*75))
                    {
                        *rec = k + (*sidepage-1)*7;      //�ʼ����
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

            if(mouse_in(800, 600, 800+145, 600+45))
            {
                mouse_trans(HAND);
                if(mouse_press(800, 600, 800+145, 600+45))
                {
                    
                    
                    delay(200);
                    break;
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
            DestroyRList(&RL);      //�������Ա�
            mouse_on(mouse);
            break;
        }
    }
}