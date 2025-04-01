#ifndef _RECFUNC_H_
#define _RECFUNC_H_
#include <time.h>

#define R_LIST_INIT_SIZE 10 //线性表存储空间的初始分配量
#define R_LISTINCEREMENT 1  //线性表存储空间的分配增量

#define LEN 10

typedef struct Record{
    /*记录时间*/
    int year;
    int month;
    int day;
    int week;

    int hour;
    int minute;
    int second;

    /*记录地点*/
    int place;

    /*抓拍路径*/
    char RecGraph[80];

    /*第几次记录*/
    int position;

    /*是否已读*/
    int readif;
} Record;

typedef struct RecList
{
	struct Record * elem;    //存储空间基值
	int length;             //当前长度
	int listsize;           //当前分配存储空间容量
} RecList;               //用户线性表 

/*生成一条记录*/
int CreateRec(USER temp, int place, int maxlen);

/*保存记录信息*/
int SaveRec(USER temp, Record rec, int maxlen);

/*读取记录信息*/
void ReadAllRec(USER temp, RecList * RL);

/*读取当前用户记录数*/
int ReadRecNum(USER temp);

/*更新记录信息*/
int UpdataRec(USER temp, Record rec);

/*建立一个空表*/
void InitRList(RecList * RL);

/*在线性表UL的末尾插入新的元素e*/
void RListInsert(RecList * RL, Record r);

/*删除元素*/
void RListDelete(RecList * L, int i);

/*若线性表L存在，销毁线性表*/
void DestroyRList(RecList * RL);

#endif