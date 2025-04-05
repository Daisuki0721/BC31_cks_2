#ifndef _ADMIN_4_
#define _ADMIN_4_

/*规则修改面板主控函数*/
void admin_rule_panel(int * page);

/*管理员用户管理面板控制*/
void admin_rule_panel_ctrl(int * sidepage, int * page);

/*绘制管理规则面板*/
void g_admin_rule_panel(int sidepage);

/*地点信息显示*/
void areainfo_display_ctrl(int * i,int * sidepage, int * page);

/*星期下拉菜单（在x2, y2的位置显示选择的星期）*/
int week_list(int x1, int y1, int x2, int y2);

#endif