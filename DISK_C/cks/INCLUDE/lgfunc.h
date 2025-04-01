#ifndef _LGFUNC_H_
#define _LGFUNC_H_


#define U_LIST_INIT_SIZE 10 //线性表存储空间的初始分配量
#define U_LISTINCEREMENT 1  //线性表存储空间的分配增量

#define LEN 10
#define TEL_LEN 12
#define MAIL_LEN 30

typedef struct USER
{
	char name[LEN];			//账户
	char code[LEN];			//密码
	int flag;				//是否为信息完善用户

	int carhead;		//车牌头代码
	char carbody[10];	//车牌主体

	char tel[TEL_LEN];		//电话
	char mail[MAIL_LEN];		//邮箱
	int ifin;				//是否为校内人员

	int record_time;	//违停次数
} USER;				//用户结构体

//暂时注释掉

// typedef struct ADMIN
// {
	

// }ADMIN;




/*******************************************************************/
typedef struct UserList
{
	struct USER * elem;    		//存储空间基值
	int length;  			//当前长度
	int listsize;  			//当前分配存储空间容量
} UserList;				//用户线性表 


/*建立一个空表*/
void InitUList(UserList *UL);

/*在线性表UL的末尾插入新的元素e*/
void UListInsert(UserList *UL,struct USER e);

/*删除元素*/
void UListDelete(int i);


/*若线性表L存在，销毁线性表*/
void DestroyUList(UserList *UL);	

/*返回元素e在线性表中的位置*/
int Userposition(UserList UL,USER e);

//显示光标
void show_gb(int x,int y);

//得到显示信息
void Getinfo(int x1,int y1,char *name,int num,int a1,int b1,int c1,int d1);

//得到密码
void Getcode(int x1,int y1,char *code,int num,int a1,int b1,int c1,int d1);

/***从存有用户数据的文件中逐个读取并与形参对比***/
int Check_info(struct UserList UL,char *name,char *code);

/*保存用户信息*/
int save_user(USER temp);
/*读取所有的用户*/
void ReadAllUser(UserList *UL);
/*读取用户数量*/
int ReadUserNum(void);
/*更新用户*/
int UpdataUser(USER user);


#endif