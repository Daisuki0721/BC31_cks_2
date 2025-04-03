#ifndef _MAIL_C_
#define _MAIL_C_

/* 根据recfunc.h中的record结构的次数来确定发送第几封邮件
 * 根据结构体中的readif参数来判定是否已读*/

/*打印邮件内容（0为没有邮件）*/
void mail_print(int x, int y, USER user, int i);
 /*记录时间处理为邮件格式*/
void mail_format_time(Record rec, char * time);
/*检测是否有邮件*/
void mail_new_confirm(USER user, int x, int y);


#endif