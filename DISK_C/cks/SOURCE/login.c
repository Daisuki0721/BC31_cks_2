#include <allfunc.h>

/*�û���¼*/
void user_login(int * func,int * unum)
{
    char name[LEN]="\0";
	char code[LEN]="\0";
    int i=-5;

    UserList UL={0};		//��ʼ���û����Ա�
	InitUList(&UL);
	ReadAllUser(&UL);

    mouse_off(&mouse);
	mouse_trans(CURSOR);

	/*�����û���¼����*/
    clear_login_bar();
    draw_login_user();

    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);
        
		if(mouse_in(422, 538, 672, 573)==1)				//����Ƶ��˺ſ���
		{
			mouse_trans(TEXT);
			if(mouse_press(422, 538, 672, 573)==1)				//����˺ſ� 
			{
				mouse_off(&mouse);
				strcpy(name,"\0");
				bar1(423, 539, 671, 572, 65498);
				Getinfo(425, 541, name, LEN, 423, 539, 671, 572);		//�õ��˺� 
				mouse_on(mouse);
			}
			continue;
		} 
		else if(mouse_in(422, 598, 672, 633)==1)				//����Ƶ��������
		{
			mouse_trans(TEXT);
			if(mouse_press(422, 598, 672, 633)==1)				//�������� 
			{
				mouse_off(&mouse);
				strcpy(code,"\0");
				bar1(423, 599, 671, 632, 65498);
				Getcode(425, 601, code, LEN, 423, 599, 671, 632);		//�õ����� 
				mouse_on(mouse);
			}
			continue;
		} 
        else if(mouse_in(352, 688, 502, 738)==1)		
        {
			mouse_trans(HAND);
			if(mouse_press(352, 688, 502, 738)==1)		//�����¼
			{
				i=Check_info(UL,name,code);
        	    if(i>=0)
				{
					*unum=i;
					DestroyUList(&UL);
					*func=4;      						//����������
           	     break;
				}
				if(i==-2)								//����������� 
				{
					prt_hz24(374, 658, "�������", 63488, "HZK\\Hzk24h");
			   		delay(3000);
					bar1(362, 658, 512, 682, 65498);
				}
				if(i==-3)								//�û������� 
				{
					prt_hz24(362, 658, "�û������ڣ�", 63488, "HZK\\Hzk24h");
				    delay(3000);
					bar1(362, 658, 512, 682, 65498);
				} 
       		}
			continue;
		}
		else if(mouse_in(612, 638, 708, 662)==1)
		{
			mouse_trans(HAND);
			if(mouse_press(612, 638, 708, 662)==1)		//���ע��
			{
				*func=2;
           		break;
			}
			continue;
		}
		else if(mouse_in(522, 688, 672, 738)==1)
		{
			mouse_trans(HAND);
			if(mouse_press(522, 688, 672, 738)==1)		//�������������
			{
				*func=0;
           		break;
			}
			continue;
		}
		mouse_trans(CURSOR);
    }
}

/*���û�ע��*/
void rigister_login(int * func,int * unum)
{
	struct USER temp={"\0", "\0", 0, 0, "\0", "\0", "\0", 0, 0, 0};	//�洢��Ϣ���û��ṹ�� 
	UserList UL={0};		//��ʼ���û����Ա�
	char judge[LEN]="\0";				//�����жϵ����� 

    mouse_off(&mouse);
	mouse_trans(CURSOR);

	/*�����û�ע�����*/
    clear_login_bar();
    draw_register_user();

    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);
        
        if(mouse_in(422, 508, 672, 543))
		{
			mouse_trans(TEXT);
			if(mouse_press(422, 508, 672, 543))   //�����˺�
			{
				mouse_off(&mouse);
				bar1(423, 509, 671, 542, 65498);
				strcpy(temp.name, "\0");
				Getinfo(425, 511, temp.name, LEN, 423, 509, 671, 542);
				mouse_on(mouse);
			}
			continue;
		}
		else if(mouse_in(422, 558, 672, 593))
		{
			mouse_trans(TEXT);
			if(mouse_press(422, 558, 672, 593))    //��������
			{
				mouse_off(&mouse);
				bar1(423, 559, 671, 592, 65498);
				strcpy(temp.code,"\0");
				Getcode(425, 561, temp.code, LEN, 423, 559, 671, 592);
				mouse_on(mouse);
			}
			continue;
		}
		else if(mouse_in(422, 608, 672, 643))
		{
			mouse_trans(TEXT);
			if(mouse_press(422, 608, 672, 643))    //�ٴ���������
			{
				mouse_off(&mouse);
				bar1(423, 609, 671, 642, 65498);
				strcpy(judge,"\0");
				Getcode(425, 611, judge, LEN, 423, 609, 671, 642);
				mouse_on(mouse);
			}
			continue;
		}
		else if(mouse_in(352, 688, 502, 738))		//����Ƶ�ȷ�ϼ���
		{
			mouse_trans(HAND);
			if(mouse_press(352, 688, 502, 738))     //���ȷ�ϼ�
			{
				if(strcmp(temp.name,"\0")!=0)		//�û�����Ϊ�� 
				{
					if(strcmp(temp.code,"\0")!=0)		//���벻Ϊ�� 
					{
						if(!strcmp(temp.code,judge))		//����������ͬ 
				        {
					    	if(save_user(temp)==0)
       	            		{
								InitUList(&UL);
								ReadAllUser(&UL);
								*unum = Userposition(UL, temp);
								DestroyUList(&UL);
       	                		*func=4;
				        		break;
                     		}
                      		else
                      		{
                        		prt_hz24(374, 658, "�û����ѱ�ע�ᣡ", 63488, "HZK\\Hzk24h");
                        		delay(1500);
				        		bar1(362, 658, 560, 682, 65498);
                      		}
			        	}
			        	else
			        	{
				    		prt_hz24(374, 658, "�������벻��ͬ��", 63488, "HZK\\Hzk24h");
				      		delay(1500);
				      		bar1(362, 658, 560, 682, 65498);
			        	}  
					}
					else
					{
						prt_hz24(374, 658, "����Ϊ�գ�",63488, "HZK\\Hzk24h");
					    delay(1500);
					    bar1(362, 658, 560, 682, 65498);
					}	
				}
				else
				{
					prt_hz24(374, 658, "�û���Ϊ�գ�",63488,"HZK\\Hzk24h");
					delay(1500);
					bar1(362, 658, 560, 682, 65498);
				}	
			}
			continue;
		}
		else if(mouse_in(522, 688, 672, 738)==1)
		{
			mouse_trans(HAND);
			if(mouse_press(522, 688, 672, 738)==1)
			{
				*func=0;
				break;
			}
			continue;
		}
		mouse_trans(CURSOR);
    }
}

/*������Ա��¼*/
void staff_login(int *func)
{

	char name[LEN]="\0";
	char code[LEN]="\0";


    mouse_off(&mouse);

    clear_login_bar();
    draw_login_admin();

    mouse_on(mouse);
    while(1)
    {
        mouse_show(&mouse);
		if(mouse_in(422, 538, 672, 573)==1)				//����Ƶ��˺ſ���
		{
			mouse_trans(TEXT);
			if(mouse_press(422, 538, 672, 573)==1)				//����˺ſ� 
			{
				mouse_off(&mouse);
				strcpy(name,"\0");
				bar1(423, 539, 671, 572, 65498);
				Getinfo(425, 541, name, LEN, 423, 539, 671, 572);		//�õ��˺� 
				mouse_on(mouse);
			}
			continue;
		} 
		else if(mouse_in(422, 598, 672, 633)==1)				//����Ƶ��������
		{
			mouse_trans(TEXT);
			if(mouse_press(422, 598, 672, 633)==1)				//�������� 
			{
				mouse_off(&mouse);
				strcpy(code,"\0");
				bar1(423, 599, 671, 632, 65498);
				Getcode(425, 601, code, LEN, 423, 599, 671, 632);		//�õ����� 
				mouse_on(mouse);
			}
			continue;
		} 
		else if(mouse_in(352, 688, 502, 738)==1)		//�����¼
		{
			mouse_trans(HAND);
			if(mouse_press(352, 688, 502, 738)==1)
			{
				if(strcmp("ciallo",name)==0&&strcmp("11450721",code)==0)
				{
					*func=5;
					break;
				}
				else
				{
					prt_hz24(362, 658, "��¼��Ϣ����", 63488, "HZK\\Hzk24h");
				    delay(3000);
					bar1(362, 658, 536, 682, 65498);
				}
			}
			continue;
		}
		else if(mouse_in(522, 688, 672, 738)==1)
		{
			mouse_trans(HAND);
			if(mouse_press(522, 688, 672, 738)==1)		//�������������
			{
				*func=0;
           		break;
			}
			continue;
		}
		mouse_trans(CURSOR);
    }
}
