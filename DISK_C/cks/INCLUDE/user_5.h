#ifndef _USER_5_
#define _USER_5_

/*用户邮箱面板*/
void user_mail_panel(int * page, int unum);
/*用户邮箱面板控制函数*/
void user_mail_panel_ctrl(int * page, int * sidepage, USER user);
/*用户邮箱面板绘制函数*/
void g_user_mail_panel(int sidepage, USER user);
/*用户邮箱信息显示控制函数*/
void mail_info_display_ctrl(USER user, int * rec, int * sidepage, int * page);

#endif