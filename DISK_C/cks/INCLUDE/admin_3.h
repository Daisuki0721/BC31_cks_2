#ifndef _ADMIN_3_
#define _ADMIN_3_

/*����Ա�û��������*/
void admin_user_panel(int * page);

/*����Ա�û�����������*/
void admin_user_panel_ctrl(int * sidepage, int * page);

/*���ƹ����û����*/
void g_admin_user_panel(int sidepage);

/*�û���Ϣ��ʾ*/
void userinfo_display_ctrl(int * unum,int * sidepage, int *page);

/*����ͷ�����˵�(��x2, y2��λ����ʾѡ��ĳ���)*/
int carhead_list(int x1, int y1, int x2, int y2);

#endif