#ifndef _ADMIN_2_
#define _ADMIN_2_

/*管理员违停处理面板*/
void admin_record_panel(int * page);
/*管理员违停处理面板控制*/
void admin_record_panel_ctrl(int * sidepage, int * page);
/*绘制管理记录面板*/
void g_admin_record_panel(int sidepage);
/*用户信息显示（精简版）*/
void userinfo_display_short(int unum);
/*记录控制面板*/
void record_select_ctrl(int x, int y, int * num, int * sidepage, int * page);

#endif