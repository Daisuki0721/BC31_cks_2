#ifndef _ADMIN_4_
#define _ADMIN_4_

/*�����޸�������غ���*/
void admin_rule_panel(int * page);

/*����Ա�û�����������*/
void admin_rule_panel_ctrl(int * sidepage, int * page);

/*���ƹ���������*/
void g_admin_rule_panel(int sidepage);

/*�ص���Ϣ��ʾ*/
void areainfo_display_ctrl(int * i,int * sidepage, int * page);

/*���������˵�����x2, y2��λ����ʾѡ������ڣ�*/
int week_list(int x1, int y1, int x2, int y2);

#endif