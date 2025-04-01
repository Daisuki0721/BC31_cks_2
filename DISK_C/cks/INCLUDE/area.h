#ifndef _AREA_H_
#define _AREA_H_

typedef struct AREA{
    int num;
    char name[13];
    int allnp;     //是否全路段禁停(1为禁停)
    /*起止时间*/
    long timest[7];   //违停起始时间段表格
    long timeed[7];   //违停终止时间段表格
    /*摄像头路径*/
    char path[40];
    int carnum;
} AREA;


/*初始化地点信息*/
void area_init(void);
/*读取地点信息*/
void area_read(AREA * AL);
/*更新地点信息*/
void area_update(AREA temp, int i);
/*保存地点信息*/
void area_save(AREA * AL);
/*时间储存函数*/
void area_timesave(long * time, int * save);
/*时间解析函数*/
void area_timeread(long time, int * save);
/*将非解析时间打印在指定位置*/
void prt_time(int x, int y, long time);
#endif