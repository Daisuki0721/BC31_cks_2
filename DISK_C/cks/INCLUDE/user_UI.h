#ifndef _USER_INTERFACE_
#define _USER_INTERFACE_
#include <lgfunc.h>

/*�û����������ܿغ���*/
void user_interface(int unum, int * func);
/*�û����������*/
void user_main_panel(int * page, USER user);
/*�û��ǳ�*/
void user_exit(int * page, int * func);
/*�û������������*/
void g_user_interface(void);
/*�����û��������*/
void g_user_main_panel(void);
/*�û��˳���������*/
void g_user_exit_video(void);
/*�û���Ϣ���ƺ���*/
void userinfo_complete(USER user, int * page);

#endif