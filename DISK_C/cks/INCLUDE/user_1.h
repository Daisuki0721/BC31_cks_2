#ifndef _USER_1_
#define _USER_1_

/*�û�Υͣ��¼���*/
void user_record_panel(int * page, int unum);
/*�û����������ƺ���*/
void user_record_panel_ctrl(int * page, int * sidepage, USER user);
/*�û����������ƺ���*/
void g_user_record_panel(int sidepage, USER user);
/*�û�������Ϣ��ʾ����*/
void record_display_user(int x, int y, USER user, int rnum);
/*�û�������Ϣ��ʾ���ƺ���*/
void record_info_display_ctrl(USER user, int * rnum, int * sidepage, int * page);
/*Υͣ״̬ͳ�������˵�*/
void RecState_list(int x, int y, USER user);

#endif