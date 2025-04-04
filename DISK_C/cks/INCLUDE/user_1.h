#ifndef _USER_1_
#define _USER_1_

/*用户违停记录面板*/
void user_record_panel(int * page, int unum);
/*用户邮箱面板控制函数*/
void user_record_panel_ctrl(int * page, int * sidepage, USER user);
/*用户邮箱面板绘制函数*/
void g_user_record_panel(int sidepage, USER user);
/*用户邮箱信息显示函数*/
void record_display_user(int x, int y, USER user, int rnum);
/*用户邮箱信息显示控制函数*/
void record_info_display_ctrl(USER user, int * rnum, int * sidepage, int * page);
/*违停状态统计下拉菜单*/
void RecState_list(int x, int y, USER user);

#endif