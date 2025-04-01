#ifndef _CRT_USER_H_
#define _CRT_USER_H_

#define INIT_UNUM 13 //初始化用户数量

/*初始化用户信息*/
void user_init(void);

/*用户注册器*/
void user_register_rand(char * name, USER * temp);

/*随机数/大写字母映射函数*/
char rand_to_char(int num);

/*随机数/大小写字母映射函数*/
char rand_to_char2(int num);

/*随机生成五位长(70%概率)/六位长（30%概率）车牌*/
void user_carbody_rand(char * carbody);

/*随机生成电话号码*/
void user_tel_rand(char * tel);

/*随机生成邮箱*/
void user_email_rand(char * mail);

#endif