#ifndef _MAIL_C_
#define _MAIL_C_

/* ����recfunc.h�е�record�ṹ�Ĵ�����ȷ�����͵ڼ����ʼ�
 * ���ݽṹ���е�readif�������ж��Ƿ��Ѷ�*/

/*��ӡ�ʼ����ݣ�0Ϊû���ʼ���*/
void mail_print(int x, int y, USER user, int i);
 /*��¼ʱ�䴦��Ϊ�ʼ���ʽ*/
void mail_format_time(Record rec, char * time);
/*����Ƿ����ʼ�*/
void mail_new_confirm(USER user, int x, int y);


#endif