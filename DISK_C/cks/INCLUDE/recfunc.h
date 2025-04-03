#ifndef _RECFUNC_H_
#define _RECFUNC_H_
#include <time.h>

#define R_LIST_INIT_SIZE 10 //���Ա�洢�ռ�ĳ�ʼ������
#define R_LISTINCEREMENT 1  //���Ա�洢�ռ�ķ�������

#define LEN 10

typedef struct Record{
    /*��¼ʱ��*/
    int year;
    int month;
    int day;
    int week;

    int hour;
    int minute;
    int second;

    int place;      //��¼�ص�

    char RecGraph[80];      //ץ��·��

    int record_time;   //�ڼ���Υ��

    int readif;     //�Ƿ��Ѷ� 0��δ�� 1���Ѷ� 2������

    int appeal_state;   //����״̬
    //0��δ���� 1����ȷ�� 2�������� 3�����߳ɹ� 4������ʧ��
} Record;

typedef struct RecList
{
	struct Record * elem;    //�洢�ռ��ֵ
	int length;             //��ǰ����
	int listsize;           //��ǰ����洢�ռ�����
} RecList;               //�û����Ա� 

/*����һ����¼*/
int CreateRec(USER temp, int place, int maxlen);

/*�����¼��Ϣ*/
int SaveRec(USER temp, Record rec, int maxlen);

/*��ȡ��¼��Ϣ*/
void ReadAllRec(USER temp, RecList * RL);

/*��ȡ��ǰ�û���¼��*/
int ReadRecNum(USER temp);

/*���¼�¼��Ϣ*/
int UpdataRec(USER temp, Record rec, int rnum);

/*����һ���ձ�*/
void InitRList(RecList * RL);

/*�����Ա�UL��ĩβ�����µ�Ԫ��e*/
void RListInsert(RecList * RL, Record r);

/*ɾ��Ԫ��*/
void RListDelete(USER user, int i);

/*�����Ա�L���ڣ��������Ա�*/
void DestroyRList(RecList * RL);

#endif