#include "allfunc.h"

/*初始化用户信息*/
void user_init(void)
{
    int i; 
    int unum = INIT_UNUM;
    FILE * fp;
    USER temp = {0};    //用户结构体
    char * name[INIT_UNUM] = 
    {
        "user1", "user2", "user3", "user4", "user5", "user6", "user7", "user8", "user9", "user10",
        "user11", "user12", "user13"/*, "user14", "user15", "user16", "user17", "user18", "user19", "user20", 
        "user21", "user22", "user23", "user24", "user25", "user26", "user27", "user28", "user29", "user30",
        "user31", "user32", "user33", "user34", "user35"*/
    };
    srand((unsigned)time(NULL));

    if((fp = fopen("userinfo.dat", "wb")) == NULL)
    {
        CloseSVGA();
        printf("Can't open file!");
        delay(5000);
        exit(1);
    }
    rewind(fp);

    fwrite(&unum, sizeof(int), 1, fp);
    fwrite(&unum, sizeof(int), 1, fp);
    delay(25);
    for(i=0; i<INIT_UNUM; i++)
    {
        user_register_rand(name[i], &temp);
        fwrite(&temp, sizeof(USER), 1, fp);
        delay(25);
    }
    fclose(fp);
}

/*用户注册器*/
void user_register_rand(char * name, USER * temp)
{
    FILE * fp;
    char path[40];
    int length = 0, listsize = R_LIST_INIT_SIZE;
    temp->flag = 1;
    strcpy(temp->name, name);
    strcpy(temp->code, "123456");
    temp->carhead = rand() % 32 + 1;
    user_carbody_rand(temp->carbody);
    temp->ifin = rand() % 2;
    temp->record_time = 0;
    user_tel_rand(temp->tel);
    user_email_rand(temp->mail);
    sprintf(path, "record\\%s.r", temp->name);
    if((fp = fopen(path, "wb+"))==NULL)
    {
        CloseSVGA();
        printf("Can't create record file!");
        delay(5000);
        exit(1);
    }
    else
    {
        rewind(fp);
        fwrite(&length, sizeof(int), 1, fp);
        fwrite(&listsize, sizeof(int), 1, fp);
        fclose(fp);
        delay(10);
    }
}

/*随机数/大写字母映射函数*/
char rand_to_char(int num)
{
    if(num < 10 && num >= 0)
    {
        return num + '0';
    }
    else if(num >= 10 && num < 36)
    {
        return num - 10 + 'A';
    }
    else
    {
        return 0;
    }
}

/*随机数/大小写字母映射函数*/
char rand_to_char2(int num)
{
    if(num < 10 && num >= 0)
    {
        return num + '0';
    }
    else if(num >= 10 && num < 36)
    {
            return num - 10 + 'A';
    }
    else if(num >= 36 && num < 62)
    {
        return num - 36 + 'a';
    }
    else
    {
        return 0;
    }
}

/*随机生成五位长(70%概率)/六位长（30%概率）车牌*/
void user_carbody_rand(char * carbody)
{
    int i, len, flag;
    flag = rand() % 10;
    if(flag < 3)
    {
        len = 6;
    }
    else
    {
        len = 5;
    }

    for(i=0; i<len; i++)
    {
        carbody[i] = rand_to_char(rand() % 36);
    }
    carbody[i] = '\0';
}

/*随机生成11位电话号码（130-139开头或180-189开头）*/
void user_tel_rand(char * tel)
{
    int i;
    tel[0] = '1';
    tel[1] = '3' + rand() % 2 * 5;
    tel[2] = '0' + rand() % 10;
    for(i=3; i<11; i++)
    {
        tel[i] = '0' + rand() % 10;
    }
    tel[i] = '\0';
}

/*随机生成邮箱(10-15位长)，以@qq.com, @163.com, @126.com, @gmail.com, @hotmail.com, @sina.com, @sohu.com, @yahoo.com.cn, @msn.com, @tom.com 其中之一结尾*/
void user_email_rand(char * email)
{
    int i, len, flag;
    char * tail[10] = {"@qq.com", "@163.com", "@126.com", "@gmail.com", "@hotmail.com", "@sina.com", "@sohu.com", "@yahoo.com.cn", "@msn.com", "@tom.com"};
    for(i=0; i<MAIL_LEN; i++)
    {
        email[i] = '\0';
    }
    len = rand() % 6 + 10;
    for(i=0; i<len; i++)
    {
        email[i] = rand_to_char2(rand() % 62);
    }
    email[i] = '\0';
    strcat(email, tail[rand() % 10]);
}
