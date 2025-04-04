#ifndef _USER_2_
#define _USER_2_

/*用户处理与申诉面板*/
void user_dispose_panel(int * page, int unum);
/*用户处理与申诉面板控制函数*/
void user_record_dispose_ctrl(int * page, int * sidepage, USER user);
/*用户处理与申诉面板绘制函数*/
void g_user_dispose_panel(int sidepage, USER user);
/*用户记录信息显示控制函数*/
void appeal_info_display_ctrl(USER user, int * pnum, int * sidepage, int * page, int * rnum);
/*用户申诉信息显示函数*/
void appeal_display_user(int x, int y, USER user, int rnum);

#endif