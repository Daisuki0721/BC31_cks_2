#ifndef _USER_2_
#define _USER_2_

/*�û��������������*/
void user_dispose_panel(int * page, int unum);
/*�û����������������ƺ���*/
void user_record_dispose_ctrl(int * page, int * sidepage, USER user);
/*�û����������������ƺ���*/
void g_user_dispose_panel(int sidepage, USER user);
/*�û���¼��Ϣ��ʾ���ƺ���*/
void appeal_info_display_ctrl(USER user, int * pnum, int * sidepage, int * page, int * rnum);
/*�û�������Ϣ��ʾ����*/
void appeal_display_user(int x, int y, USER user, int rnum);

#endif