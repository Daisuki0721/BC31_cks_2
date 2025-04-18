#ifndef _RECFUNC_H_
#define _RECFUNC_H_
#include <time.h>

#define R_LIST_INIT_SIZE 10 //线性表存储空间的初始分配量
#define R_LISTINCEREMENT 1  //线性表存储空间的分配增量

#define LEN 10

/*记录结构体*/
typedef struct Record{
    int id;         //记录编号

    /*记录时间*/
    int year;
    int month;
    int day;
    int week;

    int hour;
    int minute;
    int second;

    int place;      //记录地点

    char RecGraph[80];      //抓拍路径

    int record_time;   //第几次违规

    int readif;     //是否已读 0：未读 1：已读 2：更新

    int appeal_state;   //申诉状态
    //0：未申诉 1：已确认 2：申诉中 3：申诉成功 4：申诉失败 5.申诉成功已确认 6.申诉失败已确认 7.撤销申诉
} Record;

/*记录状态统计结构体*/
typedef struct RecState
{
    int not_appeal;   //未申诉记录数
    int confirmed;      //已确认记录数
    int appealed;    //申诉中记录数
    int appealed_success;   //申诉成功记录数
    int appealed_fail;   //申诉失败记录数
    int appealed_cancel;   //已撤销申诉记录数
} RecState;

/************************************************************************** */
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
int UpdataRec(USER temp, Record rec, int rnum);

/*建立一个空表*/
void InitRList(RecList * RL);

/*在线性表UL的末尾插入新的元素e*/
void RListInsert(RecList * RL, Record r);

/*删除元素*/
void RListDelete(USER user, int i);

/*若线性表L存在，销毁线性表*/
void DestroyRList(RecList * RL);

/*用户记录状态统计*/
void RecStateCount(USER user, RecState * recstate);

/*记录线性表处理为申诉线性表*/
int RecListToAppealList(USER user, RecList * RL);

/*用户申诉记录修正函数*/
void RecListAppealFix(USER user);

/*整理用户违停记录次数*/
void RecListRecordFix(USER user);

#endif