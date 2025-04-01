#ifndef __welcome_H__
#define __welcome_H__

/*欢迎界面主控函数*/
void welcome(int * func);
/*welcome界面绘图总控函数*/
void g_welcome(void);
/*welcome界面按钮*/
void draw_login_bars(void);
/*清空welcome界面板*/
void clear_login_bar(void);
/*绘制用户登录界面*/
void draw_login_user(void);
/*绘制用户注册界面*/
void draw_register_user(void);
/*绘制管理员登录界面*/
void draw_login_admin(void);


#endif