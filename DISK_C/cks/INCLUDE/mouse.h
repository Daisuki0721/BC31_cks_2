#ifndef MOUSE_H
#define MOUSE_H


/*���״̬�궨��*/
#define CURSOR 0
#define HAND 1
#define TEXT 2

/***���ṹ***/
typedef struct mouse                                                   
{
	int x;			//��������
	int y;			//���������
	int key;		//��ť��״̬��0,1λ�ֱ��ʾ���Ҽ�����λΪ1��ʾ���£�0��ʾ�ɿ�
	int state;		//�����״��0��ʾָ����״��1��ʾ��ָ��״��2��ʾ�ı�������״
} MOUSE;                  //���ṹ


 
/***����ʼ��***/
void mouse_init(void);
/***��긴λ***/
void MouseInit(void);
/***��귶Χ***/
void MouseRange(int x1, int y1, int x2, int y2);
/***�õ���갴��״̬(�������������)***/
int MouseBut(MOUSE * mouse);
/***�õ����λ�úͰ���״̬***/
int MouseGet(MOUSE *mouse);
//int MouseMove(MOUSE *mouse);
void MouseSpeed(int x, int y);

void SetMouseSen(int x,int y);
/***�������***/
void mouse_off(MOUSE *mouse);
/***�����������λ��***/
void MouseSet(int x,int y);
//void MouseSet1(int x,int y);
/***64k�����***/
void mouse_on(MOUSE mouse);
/***64k�����ʾ***/
void mouse_show(MOUSE *mouse);
/***�����̬ת��***/
void mouse_trans(int state);
/***�ж�����Ƿ���ָ�������ڲ�***/
int mouse_in(int x1, int y1, int x2, int y2);
/***�ж������ĳһλ�õİ�ѹ״̬***/
int mouse_press(int x1, int y1, int x2, int y2);
/***�õ�ĳһ�����ɫֵ***/
unsigned int Getpixel64k(int x, int y);

#endif
