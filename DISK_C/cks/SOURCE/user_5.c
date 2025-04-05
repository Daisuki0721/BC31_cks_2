#include <allfunc.h>

/*用户邮箱面板*/
void user_mail_panel(int * page, int unum)
{
    int sidepage = 1;	//当前侧栏页码
    UserList UL = {NULL, 0, 0};          //用户线性表
    USER user = {0};	//用户
    InitUList(&UL);           //创建线性表
    ReadAllUser(&UL);         //获取所有用户
    user = UL.elem[unum];       //得到当前用户
    DestroyUList(&UL);        //销毁线性表

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    g_user_mail_panel(sidepage, user);

    mouse_on(mouse);

    user_mail_panel_ctrl(page, &sidepage, user);
}

/*用户邮箱面板控制函数*/
void user_mail_panel_ctrl(int * page, int * sidepage, USER user)
{
    static int current_sidepage = 1;	//当前侧栏页码
    int rnum = 0;
    RecList RL = {NULL, 0, 0};          //记录线性表
    Record rec = {0};	//记录

    while(1)
    {
        ReadAllRec(user, &RL);         //获取所有记录
        rec = RL.elem[rnum];
        DestroyRList(&RL);       
    
        if(rec.readif != 1)       //如果不为已读，设置为已读
        {
            rec.readif = 1;
            UpdataRec(user, rec, rnum);	//更新记录
        }

        if(current_sidepage != *sidepage)    //如果换页，重绘侧栏   
        {
            mouse_off(&mouse);
            g_user_mail_panel(*sidepage, user);
            current_sidepage = *sidepage;
            mouse_on(mouse);
        }
        else
        {
            highlight_switch_mail(user, rnum, *sidepage);   //高亮按钮切换
        }
        while(1)
        {
            mouse_show(&mouse);

            mail_info_display_ctrl(user, &rnum, sidepage, page);  //邮件信息显示/控制
            break;
        }
        if(!*page)     //如果选择退出，跳出循环
        {
            current_sidepage = 1;
            break;  
        }
    }
}

/*用户邮箱面板绘制函数*/
void g_user_mail_panel(int sidepage, USER user)
{
    int i, pos, rnum;
    char str[20] = {0};
    RecList RL = {NULL, 0, 0};          //记录线性表

    ReadAllRec(user, &RL);         //获取所有记录
    pos = 7 * (sidepage - 1);		//计算控制区间

    clear_window(ALLBOARD);

    for(i=0, rnum = pos; (rnum < pos + 7) && (rnum < RL.length); rnum++, i++)       //控制翻页
    {
        sprintf(str, "mail%d", rnum+1);
        rounded_button_asc(15, 150+i*75, 145, 60, str, 5, 65498);
        if(RL.elem[rnum].readif == 0)
        {
            puthz(126, 150+i*75+2, "未读", 16, 16, 63488);
        }
        else if(RL.elem[rnum].readif == 1)
        {
            puthz(126, 150+i*75+2, "已读", 16, 16, 33808);
        }
        else if(RL.elem[rnum].readif == 2)
        {
            puthz(126, 150+i*75+2, "更新", 16, 16, 33808);
        }
    }
	if(!(sidepage == 1))
	{
		prt_hz16(20, 680, "上一页", 63519, "hzk\\hzk16");
	}
	if(pos + 7 < RL.length)
	{
		prt_hz16(100, 680, "下一页", 63519, "hzk\\hzk16");
	}
    prt_hz16(53, 720, "返回上级", 63519, "hzk\\hzk16");

    DestroyRList(&RL);      //销毁线性表
}

/*用户邮箱信息显示控制函数*/
void mail_info_display_ctrl(USER user, int * rec, int * sidepage, int * page)
{
    int i, k, esc = 0, flag = 0, pos = 0;
    RecList RL = {NULL, 0, 0};          //记录线性

    mouse_off(&mouse);
    mouse_trans(CURSOR);
    delay(100);

    clear_window(MAINBOARD);
    mail_print(200, 50, user, *rec+1);   //打印邮件内容
    if(user.record_id > 0)
    {
        rounded_button_d(800, 600, 145, 45, "查看抓拍", 5, 65498);    //查看抓拍按钮
    }

    mouse_on(mouse);

    ReadAllRec(user, &RL);         //获取所有记录
    pos = 7 * (*sidepage - 1);		//计算控制区间

    while(1)
    {
        while(1)
        {
            sys_time(200, 20);
            mouse_show(&mouse);
            if(RL.length == 0)   //如果没有邮件
            {
                puthz(15, 150+2, "当前没有邮件！", 24, 25, 0);
            }
            for(k = 0; (k < 7) && (k+(*sidepage-1)*7) < RL.length; k++)          //邮件选择按钮
            {
                if(mouse_in(15, 150+k*75, 160, 210+k*75))
                {
                    mouse_trans(HAND);
                    flag = 1;
                    if(mouse_press(15, 150+k*75, 160, 210+k*75))
                    {
                        *rec = k + (*sidepage-1)*7;      //邮件编号
                        esc = 1;
                        delay(200);
                        break;
                    }
                    break;
                }
            }
            if(esc)                                 //如果点击返回，则退出循环
            {
                break;
            }
            if(flag)
            {
                flag = 0;
                continue;
            }

            if(mouse_in(800, 600, 800+145, 600+45))
            {
                mouse_trans(HAND);
                if(mouse_press(800, 600, 800+145, 600+45))
                {
                    
                    
                    delay(200);
                    break;
                }
            }

            if((mouse_in(20, 680, 20+24*3, 680+24)) && (*sidepage > 1))  //控制翻页
            {
                mouse_trans(HAND);
                if(mouse_press(20, 680, 20+24*3, 680+24))
                {
                    (*sidepage)--;
                    esc = 1;
                    delay(200);
                    break;
                }
                continue;
            }
            if((mouse_in(100, 680, 100+24*3, 680+24)) && (*sidepage * 7 <  ReadRecNum(user)))  //控制翻页
            {
                mouse_trans(HAND);
                if(mouse_press(100, 680, 100+24*3, 680+24))
                {
                    (*sidepage)++;
                    esc = 1;
                    delay(200);
                    break;
                }
                continue;
            }            
            if(mouse_in(53, 720, 53+16*4, 720+16))
            {
                mouse_trans(HAND);
                if(mouse_press(53, 720, 53+16*4, 720+16))
                {
                    *page=0;
                    esc = 1;
                    *sidepage = 1;
                    delay(200);
                    break;
                }
                continue;
            }
            mouse_trans(CURSOR);
            delay(15);
        }
        if(esc)               //如果点击返回，则退出循环
        {
            mouse_off(&mouse);
            clear_window(MAINBOARD);
            DestroyRList(&RL);      //销毁线性表
            mouse_on(mouse);
            break;
        }
    }
}