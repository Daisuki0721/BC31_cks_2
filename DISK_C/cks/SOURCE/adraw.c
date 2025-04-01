#include <allfunc.h>

/*�ڱ�Բ�Ǿ��ΰ�ť���Ǽ���Ϊ0������Ϊ1�����ص�ǰ״̬*/
int rounded_button(int x1, int y1, int x2, int y2, int r , int color, int state)
{
	/*���ݲ�ͬ״̬������ɫ*/
	if(state==1)    color=34429;

	/*�����߿�*/
	Circlefill(x1+r, y1+r, r+2, 0x0000);
	Circlefill(x2-r, y1+r, r+2, 0x0000);
	Circlefill(x1+r, y2-r, r+2, 0x0000);
	Circlefill(x2-r, y2-r, r+2, 0x0000);
	Line_Thick(x1, y1+r+2, x1, y2-r-2, 2, 0x0000);
	Line_Thick(x2, y1+r+2, x2, y2-r-2, 2, 0X0000);
	Line_Thick(x1+r+2, y1, x2-r-2, y1, 2, 0X0000);
	Line_Thick(x1+r+2, y2, x2-r-2, y2, 2, 0X0000);
	/*�ڲ���ɫ*/
	Circlefill(x1+r, y1+r, r, color);
	Circlefill(x2-r, y1+r, r, color);
	Circlefill(x1+r, y2-r, r, color);
	Circlefill(x2-r, y2-r, r, color);
	bar1(x1+r, y1, x2-r, y2, color);
	bar1(x1, y1+r, x2, y2-r, color);

	return state;
}

/*�ڱ�Բ�Ǿ��ΰ�ť(�����ʹ����֣�*/
void rounded_button_d(int x, int y, int xsize, int ysize, char * str, int r, int color)
{
		/*���߿�*/
		Line_Thick(x+r, y-1, x+xsize-r, y-1, 1, 0);
		Line_Thick(x-1, y+r, x-1, y+ysize-r, 1, 0);
		Line_Thick(x+r, y+ysize+1, x+xsize-r, y+ysize+1, 1, 0);
		Line_Thick(x+xsize+1, y+r, x+xsize+1, y+ysize-r, 1, 0);
		Circlefill(x+r, y+r, r+2, 0);
		Circlefill(x+xsize-r, y+r, r+2, 0);
		Circlefill(x+r, y+ysize-r, r+2, 0);
		Circlefill(x+xsize-r, y+ysize-r, r+2, 0);
		/*�ڲ���ɫ*/
		Circlefill(x+r, y+r, r, color);
		Circlefill(x+xsize-r, y+r, r, color);
		Circlefill(x+r, y+ysize-r, r, color);
		Circlefill(x+xsize-r, y+ysize-r, r, color);
		bar1(x+r, y, x+xsize-r, y+ysize, color);
		bar1(x, y+r, x+xsize, y+ysize-r, color);
		/*�������*/
		puthz(x+(xsize-12*strlen(str)-(strlen(str)-1))/2, y+(ysize-24)/2, str, 24, 26, 0);
}

/*�ڱ�Բ�Ǿ��ΰ�ť(�����ͣ������asc�ַ�*/
void rounded_button_asc(int x, int y, int xsize, int ysize, char * str, int r, int color)
{
		/*���߿�*/
		Line_Thick(x+r, y-1, x+xsize-r, y-1, 1, 0);
		Line_Thick(x-1, y+r, x-1, y+ysize-r, 1, 0);
		Line_Thick(x+r, y+ysize+1, x+xsize-r, y+ysize+1, 1, 0);
		Line_Thick(x+xsize+1, y+r, x+xsize+1, y+ysize-r, 1, 0);
		Circlefill(x+r, y+r, r+2, 0);
		Circlefill(x+xsize-r, y+r, r+2, 0);
		Circlefill(x+r, y+ysize-r, r+2, 0);
		Circlefill(x+xsize-r, y+ysize-r, r+2, 0);
		/*�ڲ���ɫ*/
		Circlefill(x+r, y+r, r, color);
		Circlefill(x+xsize-r, y+r, r, color);
		Circlefill(x+r, y+ysize-r, r, color);
		Circlefill(x+xsize-r, y+ysize-r, r, color);
		bar1(x+r, y, x+xsize-r, y+ysize, color);
		bar1(x, y+r, x+xsize, y+ysize-r, color);
		/*����ַ�*/
		prt_asc16(x+(xsize-8*strlen(str))/2, y+(ysize-16)/2, str, 0);
}

/**************************************
 * ��ָ��λ�����һ������ͷ(ʹ��puthz����)
 * flagΪ����ͷ���ţ�sizeΪ�ֺŴ�С����ѡ16��24��32��48��
 * flag�����ο���
 * 1 ����    2����     3 ����    4 ����
 * 5 ����    6��³     7 ����    8 ����
 * 9 ��ԥ    10����    11����    12����
 * 13����    14����    15����    16����
 * 17����    18����    19����    20����
 * 21����    22����    23����    24����
 * 25����    26����    27����    28����
 * 29����    30����    31����    32����
***************************************/
void put_carhead(int x, int y, int flag, int size, int color)
{
	char * str[32] = {"��", "��", "��", "��", "��", "³", "��", "��",
					  "ԥ", "��", "��", "��", "��", "��", "��", "��",
					  "��", "��", "��", "��", "��", "��", "��", "��",
					  "��", "��", "��", "��", "��", "��", "��", "��"};
	
	puthz(x, y, str[flag-1], size, size, color);

}

/*��ָ��λ������һ������ͷ��ť��x��y���ư�ťλ�ã�flagΪ����ͷ���ţ�size���ư�ť��С*/
void carhead_button(int x, int y, int flag, int size)
{
	rounded_button(x, y, x+size, y+size, NULL, 59391, 4);
	put_carhead(x+(size-24)/2, y+(size-24)/2, flag, 24, 0);
	// if(mouse_in(x1, y1, x1+size1, y1+size1))
	// {
	// 	mouse_trans(HAND);
	// 	if(mouse_press(x1, y1, x1+size1, y1+size1))
	// 	{
	// 		bar1(x2, y2, x2+size2, y2+size2, color);
	// 		put_carhead(x2+(size2-24)/2, y2+(size2-24)/2, flag, 24, 0);
	// 	}
	// 	continue;
	// }
}

/*��ָ��λ������һ������ͷ����*/
void carhead_keyboard(int x, int y)
{
	int i, j, xp, yp;
	xp = x + 17;
	yp = y + 13;

	bar1(x, y, x+410, y+210, 33808);
    bar1(x+5, y+5, x+405, y+205, 65530);

	for(i=0; i<4; i++)
	{
		for(j=0; j<8; j++)
		{
			carhead_button(xp, yp, i*8+j+1, 40);
			xp += 48;
		}
		xp = x + 17;		//x�ص���ͷ�ĵ�һ��
		yp += 48;
	}
}

/*��������*/
void welcome_video(void)
{
	bar1(0, 0, 1024, 768, 65530);  //��������
	Readbmp64k(400, 250, "bmp\\hust1.bmp");	//ͼƬ����
	puthz(400, 400, "��ӭʹ��", 48, 50, 0);	//��Ϣ����
	puthz(230, 460, "У԰������Υͣ����ϵͳ", 48, 50, 0);
	puthz(600, 520, "��Ϣ���ڼ����С���", 24, 26, 0);
	puthz(600, 550, "����һ�ν�����ܼ���ʱ��ϳ��������ĵȴ���", 16, 16, 0);
	delay(1000);  //��ʱ1��
}

/*������ҳ��*/
void clear_window(int flag)
{
	if(flag==ALLBOARD)
	{
		bar1(0, 122, 178, 768, 34429);
		bar1(182, 0, 1024, 768, 65533);
	}
	else if(flag==SIDEBOARD)
	{
		bar1(0, 122, 178, 768, 34429);
	}
	else if(flag==MAINBOARD)
	{
		bar1(182, 0, 1024, 768, 65533);
	}
}

/*��һ����ɫ�Ĺ�*/
void red_tick(int x, int y)
{
	Line_Thick(x-2, y+12, x+6, y+20, 1, 63488);
	Line_Thick(x+6, y+20, x+22, y-2, 1, 63488);
}

/*ѡ���û���岢����Υͣ��¼�����*/
void user_select_draw(int x, int y, int sidepage)
{
	int pos, unum, i, j;
	UserList UL = {NULL, 0, 0};          //���Ա�
	InitUList(&UL);           //�������Ա�
	ReadAllUser(&UL);         //��ȡ�����û�

	bar1(x, y, x+460, y+240, 33808);
    bar1(x+5, y+5, x+455, y+235, 65530);

	pos = 12 * (sidepage - 1);		//�����ӡ����

	if(sidepage > 1)
	{
		rounded_button_d(x+50, y+200, 80, 30, "��һҳ", 3, 65498);
	}
	if(pos + 12 < UL.length)
	{
		rounded_button_d(x+150, y+200, 80, 30, "��һҳ", 3, 65498);
	}

	for(unum = pos; (unum < pos + 12) && (unum < UL.length); unum++)
	{
		j = (unum % 12) % 4;
		i = (unum % 12) / 4;
		rounded_button_asc(x+8+i*150, y+10+j*37, 144, 30, UL.elem[unum].name, 3, 59391);
	}
	
    rounded_button_d(x+250, y+200, 80, 30, "����", 3, 65498);
    rounded_button_d(x+350, y+200, 80, 30, "ȷ��", 3, 65498);

	puthz(660, 15, "��Ҫ�л�����ͷ�����ȵ�����أ�", 24, 25, 63488);

	DestroyUList(&UL);        //�������Ա�
}

/*ѡ���¼������*/
void record_select_draw(int x, int y, int num)
{
	int i, j, rnum, reclistlen;
	char str[9] = {0};
	USER temp = {0};
	Record record = {0};
	UserList UL = {NULL, 0, 0};          //�û����Ա�
	RecList RL = {NULL, 0, 0};          //��¼���Ա�
	InitUList(&UL);           //�������Ա�
	ReadAllUser(&UL);         //��ȡ�����û�
	temp = UL.elem[num];
	DestroyUList(&UL);        //�������Ա�

	reclistlen = ReadRecNum(temp);		//��ȡ��¼����

	bar1(x, y, x+460, y+240, 33808);
	bar1(x+5, y+5, x+455, y+235, 65530);
	for(rnum = 0; rnum < reclistlen; rnum++)
	{
		j = (rnum % 12) % 4;
		i = (rnum % 12) / 4;
		sprintf(str, "record%d", rnum+1);
		rounded_button_asc(x+8+i*150, y+10+j*37, 144, 30, str, 3, 59391);
	}

	rounded_button_d(x+50, y+200, 150, 30, "������ҳ", 3, 65498);
	if(reclistlen > 0)
	{
		rounded_button_d(x+250, y+200, 80, 30, "ɾ��", 3, 65498);
		rounded_button_d(x+350, y+200, 80, 30, "ȷ��", 3, 65498);
	}


	DestroyRList(&RL);        //�������Ա�
}

/*������ť�л�����(�û�)*/
void highlight_switch_user(int unum, int sidepage)
{
    static int last = 0;    //��һ�ε���İ�ť
    static int lastsidepage = 1;    //��һ�ε�ҳ��
    UserList UL = {NULL, 0, 0};          //�û����Ա�
    InitUList(&UL);           //�������Ա�
    ReadAllUser(&UL);         //��ȡ�����û�

	mouse_off(&mouse);

    if(lastsidepage == sidepage)        //�������ҳ���ػ���ɫ��ť
    {
        rounded_button_asc(15, 150+(last%7)*75, 145, 60, UL.elem[last].name, 5, 65498);
    }
    else
    {
        lastsidepage = sidepage;
    }
    last = unum;
    
	if(lastsidepage)
	{
		rounded_button_asc(15, 150+(unum%7)*75, 145, 60, UL.elem[unum].name, 5, 65504);
	}
    
	mouse_on(mouse);

    DestroyUList(&UL);        //�������Ա�
}

/*������ť�л��������ص㣩*/
void highlight_switch_area(int i, int sidepage)
{
	static int last = 0;    //��һ�ε���İ�ť
    static int lastsidepage = 1;    //��һ�ε�ҳ��
	AREA AP[14];
	area_read(AP);

	mouse_off(&mouse);

    if(lastsidepage == sidepage)        //�������ҳ���ػ���ɫ��ť
    {
        rounded_button_d(15, 150+(last%7)*75, 145, 60, AP[last].name, 5, 65498);
    }
    else
    {
        lastsidepage = sidepage;
    }
    last = i;
    
	if(lastsidepage)
	{
		rounded_button_d(15, 150+(i%7)*75, 145, 60, AP[i].name, 5, 65504);
	}
    
	mouse_on(mouse);
}

/*��ָ��λ�����һ�����ڼ�(ʹ��puthz����)*/
/*flagΪ���ڼ����ţ�sizeΪ�ֺŴ�С����ѡ16��24��32��48��*/
void put_week(int x, int y, int flag, int size, int color)
{
	char * str[7] = {"����һ", "���ڶ�", "������", "������", "������", "������", "������"};
	
	puthz(x, y, str[flag-1], size, size, color);

}

/*��ָ��λ������һ�����ڼ���ť��x��y���ư�ťλ�ã�flagΪ���ڼ����ţ�size���ư�ť��С*/
void week_button(int x, int y, int flag, int size)
{
	rounded_button(x, y, x+size*3, y+size, NULL, 59391, 4);
	put_week(x+(size-24)*3/2, y+(size-24)/2, flag, 24, 0);
}

/*��ָ��λ������һ�����ڼ���*/
void week_keyboard(int x, int y)
{
	int i, j, xp, yp;
	xp = x + 17;
	yp = y + 13;

	bar1(x, y, x+282, y+210, 33808);
    bar1(x+5, y+5, x+277, y+205, 65530);

	for(i=0; i<4; i++)
	{
		for(j=0; j<2; j++)
		{	
			if(i == 3 && j == 1)
			{
				break;		//ֻ���߸���ť
			}
			week_button(xp, yp, i*2+j+1, 40);
			xp += 128;
		}
		xp = x + 17;
		yp += 48;
	}
}


/*ϵͳʱ����ʾ*/
void sys_time(int x, int y)
{
    static int cursec = 0;
    static char * week[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    char str[80] = "\0";
    char temp[10] = "\0";
    time_t now = time(NULL);
	struct tm *local = localtime(&now);

    if(cursec != local->tm_sec)
    {
        cursec = local->tm_sec;
        sprintf(temp, "%04d", local->tm_year + 1900);
        strcat(str, temp);
        strcat(str, "/");
        sprintf(temp, "%02d", local->tm_mon + 1);
        strcat(str, temp);
        strcat(str, "/");
        sprintf(temp, "%02d", local->tm_mday);
        strcat(str, temp);
        strcat(str, " ");
        sprintf(temp, "%02d", local->tm_hour);
        strcat(str, temp);
        strcat(str, ":");
        sprintf(temp, "%02d", local->tm_min);
        strcat(str, temp);
        strcat(str, ":");
        sprintf(temp, "%02d", local->tm_sec);
        strcat(str, temp);
        strcat(str, " ");
        strcat(str, week[local->tm_wday]);

        mouse_off(&mouse);
        bar1(x, y, x+250, y+16, 65533);
        prt_asc16(x, y, str, 0);
        mouse_on(mouse);
    }
}