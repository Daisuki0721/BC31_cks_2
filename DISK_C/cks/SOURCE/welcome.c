#include <allfunc.h>

void welcome(int * func)
{

    mouse_off(&mouse);
	delay(100);

    g_welcome();        //绘图总控函数

    mouse_on(mouse);

    while(1)
    {
        mouse_show(&mouse);

        if(mouse_in(SCRMID_W-160, SCRMID_H+130, SCRMID_W+160, SCRMID_H+190))         //移动到按钮上，做出响应
        {
            mouse_trans(HAND);
            if(mouse_press(SCRMID_W-160, SCRMID_H+130, SCRMID_W+160, SCRMID_H+190))      //点击进入登录选项页（func=1）
            {
                *func=1;
                break;
            }
            continue;
        }
        else if(mouse_in(SCRMID_W-160, SCRMID_H+210, SCRMID_W+160, SCRMID_H+270))
        {
            mouse_trans(HAND);
            if(mouse_press(SCRMID_W-160, SCRMID_H+210, SCRMID_W+160, SCRMID_H+270))      //点击进入注册选项页（func=2）
            {
                *func=2;
                break;
            }
            continue;
        }
        else if(mouse_in(SCRMID_W-160, SCRMID_H+290, SCRMID_W+160, SCRMID_H+350))        //点击进入管理登录选项页（func=3）
        {
            mouse_trans(HAND);
            if(mouse_press(SCRMID_W-160, SCRMID_H+290, SCRMID_W+160, SCRMID_H+350))
            {
                *func=3;
                break;
            }
            continue;
        }
        else
        {
            mouse_trans(CURSOR);
            delay(15);
        }
    }
}

/*welcome界面绘图总控函数*/
void g_welcome(void)
{
    Readbmp64k(0, 0, "bmp\\cover.bmp");                                     //背景图
    prt_hz16_size(235, 100, 6, 20,"校园机动车", 65504, "HZK\\HZK16s");          //系统标题
    prt_hz16_size(170, 250, 6, 20,"违停管理系统", 65504, "HZK\\HZK16s");
    draw_login_bars();                                                   //按钮框及按钮
}

/*welcome界面按钮板+按钮*/
void draw_login_bars(void)
{
    bar1(SCRMID_W-205, SCRMID_H+105, SCRMID_W+205, SCRMID_H+375, 65513);
    bar1(SCRMID_W-200, SCRMID_H+110, SCRMID_W+200, SCRMID_H+370, 65498);
    rounded_button(SCRMID_W-160, SCRMID_H+130, SCRMID_W+160, SCRMID_H+190, 6, 46651, 0);
    rounded_button(SCRMID_W-160, SCRMID_H+210, SCRMID_W+160, SCRMID_H+270, 6, 46651, 0);
    rounded_button(SCRMID_W-160, SCRMID_H+290, SCRMID_W+160, SCRMID_H+350, 6, 46651, 0);
    puthz(SCRMID_W-80, SCRMID_H+140,"用户登录",32,40,0);
    puthz(SCRMID_W-80, SCRMID_H+220,"用户注册",32,40,0);
    puthz(SCRMID_W-100, SCRMID_H+300,"管理员登录",32,40,0);
}

/*清空welcome界面板*/
void clear_login_bar(void)
{
    bar1(SCRMID_W-205, SCRMID_H+105, SCRMID_W+205, SCRMID_H+375, 65513);
    bar1(SCRMID_W-200, SCRMID_H+110, SCRMID_W+200, SCRMID_H+370, 65498);
}

/*绘制用户登录界面*/
void draw_login_user(void)
{
    puthz(327, 544, "用户名：", 24, 26, 0);
    bar2(422, 538, 672, 573, 0);
    puthz(353, 604, "密码：", 24, 26, 0);
    bar2(422, 598, 672, 633, 0);
    rounded_button(352, 688, 502, 738, 6, 46651, 0);
    puthz(392, 698, "登录", 24 ,30, 0);
    rounded_button(522, 688, 672, 738, 6, 46651, 0);
    puthz(532, 698, "返回主界面", 24, 26, 0);
    puthz(512, 638, "没有账号？", 16, 18, 0);
    puthz(612, 638, "点我注册", 16, 18, 31);
}

/*绘制用户注册界面*/
void draw_register_user(void)
{
    puthz(327, 514, "用户名：", 24, 26, 0);
    bar2(422, 508, 672, 543, 0);
    puthz(353, 564, "密码：", 24, 26, 0);
    bar2(422, 558, 672, 593, 0);
    puthz(313, 614, "确认密码：", 24, 24, 0);
    bar2(422, 608, 672, 643, 0);
    
    rounded_button(352, 688, 502, 738, 6, 46651, 0);
    puthz(374, 698, "立即注册", 24,26, 0);
    rounded_button(522, 688, 672, 738, 6, 46651, 0);
    puthz(532, 698, "返回主界面", 24, 26, 0);
}

/*绘制管理员登录界面*/
void draw_login_admin(void)
{
    puthz(327, 544,"管理名：", 24, 26, 0);
    bar2(422, 538, 672, 573, 0);
    puthz(353, 604, "密码：", 24, 26, 0);
    bar2(422, 598, 672, 633, 0);
    rounded_button(352, 688, 502, 738, 6, 46651, 0);
    puthz(374, 698, "管理登录", 24 ,26, 0);
    rounded_button(522, 688, 672, 738, 6, 46651, 0);
    puthz(532, 698, "返回主界面", 24, 26, 0);
}