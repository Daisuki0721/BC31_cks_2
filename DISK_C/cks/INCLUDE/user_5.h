#ifndef _USER_5_
#define _USER_5_

/*�û��������*/
void user_mail_panel(int * page, int unum);
/*�û����������ƺ���*/
void user_mail_panel_ctrl(int * page, int * sidepage, USER user);
/*�û����������ƺ���*/
void g_user_mail_panel(int sidepage, USER user);
/*�û�������Ϣ��ʾ���ƺ���*/
void mail_info_display_ctrl(USER user, int * rec, int * sidepage, int * page);

#endif