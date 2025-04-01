#ifndef _ADMIN_3_
#define _ADMIN_3_

/*管理员用户管理面板*/
void admin_user_panel(int * page);

/*管理员用户管理面板控制*/
void admin_user_panel_ctrl(int * sidepage, int * page);

/*绘制管理用户面板*/
void g_admin_user_panel(int sidepage);

/*用户信息显示*/
void userinfo_display_ctrl(int * unum,int * sidepage, int *page);

/*车牌头下拉菜单(在x2, y2的位置显示选择的车牌)*/
int carhead_list(int x1, int y1, int x2, int y2);

#endif