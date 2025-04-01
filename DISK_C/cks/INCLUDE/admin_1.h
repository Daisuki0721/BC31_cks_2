#ifndef _ADMIN_1_
#define _ADMIN_1_

/*管理员查看摄像头面板*/
void admin_monitor_panel(int * page);
/*摄像头界面侧栏控制*/
void admin_monitor_panel_ctrl(int * sidepage, int * page);
/*绘制管理摄像头面板*/
void g_admin_monitor_panel(int sidepage);
/*摄像头信息显示*/
void monitor_display(int i, int sidepage);
/*选择用户并生成违停记录*/
void CreateRec_monitor(int num);
/*选择用户面板并生成违停记录控制*/
void user_select_ctrl(int x, int y, int num, int * sidepage);
#endif