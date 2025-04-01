#ifndef _ADRAW_H_
#define _ADRAW_H_

#define ALLBOARD 0
#define SIDEBOARD 1
#define MAINBOARD 2

/*�ڱ�Բ�Ǿ��ΰ�ť���Ǽ���Ϊ0������Ϊ1*/
int rounded_button(int x1, int y1, int x2, int y2, int r, int color, int state);
/*�ڱ�Բ�Ǿ��ΰ�ť(�����ʹ����֣�*/
void rounded_button_d(int x, int y, int xsize, int ysize, char * str, int r, int color);
/*�ڱ�Բ�Ǿ��ΰ�ť(�����ͣ������asc�ַ�*/
void rounded_button_asc(int x, int y, int xsize, int ysize, char * str, int r, int color);
/**************************************
 * ��ָ��λ�����һ������ͷ(ʹ��prthz����)
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
void put_carhead(int x, int y, int flag, int size, int color);
/*��ָ��λ������һ������ͷ��ť��x��y���ư�ťλ�ã�flagΪ����ͷ���ţ�size���ư�ť��С*/
void carhead_button(int x, int y, int flag, int size);
/*��ָ��λ������һ������ͷ����*/
void carhead_keyboard(int x, int y);
/*��������*/
void welcome_video(void);
/*������ҳ��*/
void clear_window(int flag);
/*��һ����ɫ�Ĺ�*/
void red_tick(int x, int y);
/*ѡ���û�������*/
void user_select_draw(int x,int y, int sidepage);
/*ѡ���¼������*/
void record_select_draw(int x, int y, int num);
/*������ť�л��������û���*/
void highlight_switch_user(int unum, int sidepage);
/*������ť�л��������ص㣩*/
void highlight_switch_area(int i, int sidepage);
/*��ָ��λ�����һ�����ڼ�(ʹ��puthz����)*/
/*flagΪ���ڼ����ţ�sizeΪ�ֺŴ�С����ѡ16��24��32��48��*/
void put_week(int x, int y, int flag, int size, int color);
/*��ָ��λ������һ�����ڼ���ť��x��y���ư�ťλ�ã�flagΪ���ڼ����ţ�size���ư�ť��С*/
void week_button(int x, int y, int flag, int size);
/*��ָ��λ������һ�����ڼ���*/
void week_keyboard(int x, int y);
/*ϵͳʱ����ʾ*/
void sys_time(int x, int y);
#endif
