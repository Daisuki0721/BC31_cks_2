#ifndef _ADMIN_UI_
#define _ADMIN_UI_

/*管理交互界面主控函数*/
void admin_interface(int * func);
/*管理员主控面板*/
void admin_main_panel(int * page);
/*管理界面退出*/
void admin_exit(int * page, int * func);
/*管理交互界面绘制*/
void g_admin_interface(void);
/*绘制管理主控面板*/
void g_admin_main_panel(void);
/*管理退出动画界面*/
void g_admin_exit_video(void);
/*所有用户申诉记录修正*/
void admin_appeal_rec_fix(void);
/*绘制所有用户统计申诉红点*/
void appeal_all_confirm(int x, int y);

#endif