#ifndef _CRT_USER_H_
#define _CRT_USER_H_

#define INIT_UNUM 13 //��ʼ���û�����

/*��ʼ���û���Ϣ*/
void user_init(void);

/*�û�ע����*/
void user_register_rand(char * name, USER * temp);

/*�����/��д��ĸӳ�亯��*/
char rand_to_char(int num);

/*�����/��Сд��ĸӳ�亯��*/
char rand_to_char2(int num);

/*���������λ��(70%����)/��λ����30%���ʣ�����*/
void user_carbody_rand(char * carbody);

/*������ɵ绰����*/
void user_tel_rand(char * tel);

/*�����������*/
void user_email_rand(char * mail);

#endif