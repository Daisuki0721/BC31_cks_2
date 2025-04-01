#ifndef _AREA_H_
#define _AREA_H_

typedef struct AREA{
    int num;
    char name[13];
    int allnp;     //�Ƿ�ȫ·�ν�ͣ(1Ϊ��ͣ)
    /*��ֹʱ��*/
    long timest[7];   //Υͣ��ʼʱ��α��
    long timeed[7];   //Υͣ��ֹʱ��α��
    /*����ͷ·��*/
    char path[40];
    int carnum;
} AREA;


/*��ʼ���ص���Ϣ*/
void area_init(void);
/*��ȡ�ص���Ϣ*/
void area_read(AREA * AL);
/*���µص���Ϣ*/
void area_update(AREA temp, int i);
/*����ص���Ϣ*/
void area_save(AREA * AL);
/*ʱ�䴢�溯��*/
void area_timesave(long * time, int * save);
/*ʱ���������*/
void area_timeread(long time, int * save);
/*���ǽ���ʱ���ӡ��ָ��λ��*/
void prt_time(int x, int y, long time);
#endif