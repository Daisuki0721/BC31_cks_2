#ifndef _LGFUNC_H_
#define _LGFUNC_H_


#define U_LIST_INIT_SIZE 10 //���Ա�洢�ռ�ĳ�ʼ������
#define U_LISTINCEREMENT 1  //���Ա�洢�ռ�ķ�������

#define LEN 10
#define TEL_LEN 12
#define MAIL_LEN 30

typedef struct USER
{
	char name[LEN];			//�˻�
	char code[LEN];			//����
	int flag;				//�Ƿ�Ϊ��Ϣ�����û�

	int carhead;		//����ͷ����
	char carbody[10];	//��������

	char tel[TEL_LEN];		//�绰
	char mail[MAIL_LEN];		//����
	int ifin;				//�Ƿ�ΪУ����Ա

	int record_time;	//Υͣ����
} USER;				//�û��ṹ��

//��ʱע�͵�

// typedef struct ADMIN
// {
	

// }ADMIN;




/*******************************************************************/
typedef struct UserList
{
	struct USER * elem;    		//�洢�ռ��ֵ
	int length;  			//��ǰ����
	int listsize;  			//��ǰ����洢�ռ�����
} UserList;				//�û����Ա� 


/*����һ���ձ�*/
void InitUList(UserList *UL);

/*�����Ա�UL��ĩβ�����µ�Ԫ��e*/
void UListInsert(UserList *UL,struct USER e);

/*ɾ��Ԫ��*/
void UListDelete(int i);


/*�����Ա�L���ڣ��������Ա�*/
void DestroyUList(UserList *UL);	

/*����Ԫ��e�����Ա��е�λ��*/
int Userposition(UserList UL,USER e);

//��ʾ���
void show_gb(int x,int y);

//�õ���ʾ��Ϣ
void Getinfo(int x1,int y1,char *name,int num,int a1,int b1,int c1,int d1);

//�õ�����
void Getcode(int x1,int y1,char *code,int num,int a1,int b1,int c1,int d1);

/***�Ӵ����û����ݵ��ļ��������ȡ�����βζԱ�***/
int Check_info(struct UserList UL,char *name,char *code);

/*�����û���Ϣ*/
int save_user(USER temp);
/*��ȡ���е��û�*/
void ReadAllUser(UserList *UL);
/*��ȡ�û�����*/
int ReadUserNum(void);
/*�����û�*/
int UpdataUser(USER user);


#endif