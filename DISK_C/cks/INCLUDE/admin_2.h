#ifndef _ADMIN_2_
#define _ADMIN_2_

/*����ԱΥͣ�������*/
void admin_record_panel(int * page);
/*����ԱΥͣ����������*/
void admin_record_panel_ctrl(int * sidepage, int * page);
/*���ƹ����¼���*/
void g_admin_record_panel(int sidepage);
/*�û���Ϣ��ʾ������棩*/
void userinfo_display_short(int unum);
/*��¼�������*/
void record_select_ctrl(int x, int y, int * num, int * sidepage, int * page);

#endif