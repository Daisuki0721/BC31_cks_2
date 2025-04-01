#include <allfunc.h>

void welcome(int * func)
{

    mouse_off(&mouse);
	delay(100);

    g_welcome();        //��ͼ�ܿغ���

    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);

        if(mouse_in(SCRMID_W-160, SCRMID_H+130, SCRMID_W+160, SCRMID_H+190))         //�ƶ�����ť�ϣ�������Ӧ
        {
            mouse_trans(HAND);
            if(mouse_press(SCRMID_W-160, SCRMID_H+130, SCRMID_W+160, SCRMID_H+190))      //��������¼ѡ��ҳ��func=1��
            {
                *func=1;
                break;
            }
            continue;
        }
        else if(mouse_in(SCRMID_W-160, SCRMID_H+210, SCRMID_W+160, SCRMID_H+270))
        {
            mouse_trans(HAND);
            if(mouse_press(SCRMID_W-160, SCRMID_H+210, SCRMID_W+160, SCRMID_H+270))      //�������ע��ѡ��ҳ��func=2��
            {
                *func=2;
                break;
            }
            continue;
        }
        else if(mouse_in(SCRMID_W-160, SCRMID_H+290, SCRMID_W+160, SCRMID_H+350))        //�����������¼ѡ��ҳ��func=3��
        {
            mouse_trans(HAND);
            if(mouse_press(SCRMID_W-160, SCRMID_H+290, SCRMID_W+160, SCRMID_H+350))
            {
                *func=3;
                break;
            }
            continue;
        }
        else
        {
            mouse_trans(CURSOR);
            delay(15);
        }
    }
}

/*welcome�����ͼ�ܿغ���*/
void g_welcome(void)
{
    Readbmp64k(0, 0, "bmp\\cover.bmp");                                     //����ͼ
    prt_hz16_size(235, 100, 6, 20,"У԰������", 65504, "HZK\\HZK16s");          //ϵͳ����
    prt_hz16_size(170, 250, 6, 20,"Υͣ����ϵͳ", 65504, "HZK\\HZK16s");
    draw_login_bars();                                                   //��ť�򼰰�ť
}

/*welcome���水ť��+��ť*/
void draw_login_bars(void)
{
    bar1(SCRMID_W-205, SCRMID_H+105, SCRMID_W+205, SCRMID_H+375, 65513);
    bar1(SCRMID_W-200, SCRMID_H+110, SCRMID_W+200, SCRMID_H+370, 65498);
    rounded_button(SCRMID_W-160, SCRMID_H+130, SCRMID_W+160, SCRMID_H+190, 6, 46651, 0);
    rounded_button(SCRMID_W-160, SCRMID_H+210, SCRMID_W+160, SCRMID_H+270, 6, 46651, 0);
    rounded_button(SCRMID_W-160, SCRMID_H+290, SCRMID_W+160, SCRMID_H+350, 6, 46651, 0);
    puthz(SCRMID_W-80, SCRMID_H+140,"�û���¼",32,40,0);
    puthz(SCRMID_W-80, SCRMID_H+220,"�û�ע��",32,40,0);
    puthz(SCRMID_W-100, SCRMID_H+300,"����Ա��¼",32,40,0);
}

/*���welcome�����*/
void clear_login_bar(void)
{
    bar1(SCRMID_W-205, SCRMID_H+105, SCRMID_W+205, SCRMID_H+375, 65513);
    bar1(SCRMID_W-200, SCRMID_H+110, SCRMID_W+200, SCRMID_H+370, 65498);
}

/*�����û���¼����*/
void draw_login_user(void)
{
    puthz(327, 544, "�û�����", 24, 26, 0);
    bar2(422, 538, 672, 573, 0);
    puthz(353, 604, "���룺", 24, 26, 0);
    bar2(422, 598, 672, 633, 0);
    rounded_button(352, 688, 502, 738, 6, 46651, 0);
    puthz(392, 698, "��¼", 24 ,30, 0);
    rounded_button(522, 688, 672, 738, 6, 46651, 0);
    puthz(532, 698, "����������", 24, 26, 0);
    puthz(512, 638, "û���˺ţ�", 16, 18, 0);
    puthz(612, 638, "����ע��", 16, 18, 31);
}

/*�����û�ע�����*/
void draw_register_user(void)
{
    puthz(327, 514, "�û�����", 24, 26, 0);
    bar2(422, 508, 672, 543, 0);
    puthz(353, 564, "���룺", 24, 26, 0);
    bar2(422, 558, 672, 593, 0);
    puthz(313, 614, "ȷ�����룺", 24, 24, 0);
    bar2(422, 608, 672, 643, 0);
    
    rounded_button(352, 688, 502, 738, 6, 46651, 0);
    puthz(374, 698, "����ע��", 24,26, 0);
    rounded_button(522, 688, 672, 738, 6, 46651, 0);
    puthz(532, 698, "����������", 24, 26, 0);
}

/*���ƹ���Ա��¼����*/
void draw_login_admin(void)
{
    puthz(327, 544,"��������", 24, 26, 0);
    bar2(422, 538, 672, 573, 0);
    puthz(353, 604, "���룺", 24, 26, 0);
    bar2(422, 598, 672, 633, 0);
    rounded_button(352, 688, 502, 738, 6, 46651, 0);
    puthz(374, 698, "�����¼", 24 ,26, 0);
    rounded_button(522, 688, 672, 738, 6, 46651, 0);
    puthz(532, 698, "����������", 24, 26, 0);
}