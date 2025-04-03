#ifndef _USER_INTERFACE_
#define _USER_INTERFACE_
#include <lgfunc.h>

/*用户交互界面总控函数*/
void user_interface(int unum, int * func);
/*用户主控制面板*/
void user_main_panel(int * page, USER user);
/*用户登出*/
void user_exit(int * page, int * func);
/*用户交互界面绘制*/
void g_user_interface(void);
/*绘制用户主控面板*/
void g_user_main_panel(void);
/*用户退出动画界面*/
void g_user_exit_video(void);
/*用户信息完善函数*/
void userinfo_complete(USER user, int * page);

#endif