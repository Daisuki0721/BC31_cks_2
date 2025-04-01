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



#endif