#ifndef _ADMIN_1_
#define _ADMIN_1_

/*����Ա�鿴����ͷ���*/
void admin_monitor_panel(int * page);
/*����ͷ�����������*/
void admin_monitor_panel_ctrl(int * sidepage, int * page);
/*���ƹ�������ͷ���*/
void g_admin_monitor_panel(int sidepage);
/*����ͷ��Ϣ��ʾ*/
void monitor_display(int i, int sidepage);
/*ѡ���û�������Υͣ��¼*/
void CreateRec_monitor(int num);
/*ѡ���û���岢����Υͣ��¼����*/
void user_select_ctrl(int x, int y, int num, int * sidepage);
#endif