#include <allfunc.h>

void main()
{          
	int func=5;
    int unum=0;

    int i;
    char getbmp[100];

    FILE *fp=NULL;


    SetSVGA64k();                    //启动SVGA画图界面  
    
    welcome_video();                 //开机动画

	if((fp=fopen("area.dat","rb"))==NULL)       //如果地点文件不存在，新建并初始化 
	{
		area_init();                        //初始化地点信息
	}
	fclose(fp);

    fp=NULL;

    if((fp=fopen("userinfo.dat","rb"))==NULL)   //如果用户信息文件不存在，新建并初始化 .dat","rb"))==NULL)//如果未初始化管理信息，则进行初始化 
	{
		user_init();                        //初始化用户信息
	}

	fclose(fp);

    /********************
    0:欢迎界面
    1:用户登录
    2:用户注册
    3:管理登录
    4:用户主界面
    5:管理员主界面
    ********************/



//开机启动画面

//    for(i=1;i<148;i++)
//     {
//         sprintf(getbmp,"bmp\\vdeio\\%d.bmp",i);
//         bmp_fast1(0,1000,getbmp);
//     }

    mouse_init();
    
	while(1)   
	{
        switch(func)
        {
            case 0:
            {
                welcome(&func);
                break;
            }
            case 1:
            {
                user_login(&func, &unum);
                break;
            }
            case 2:
            {
                rigister_login(&func, &unum);
                break;
            }
            case 3:
            {
                staff_login(&func);
                break;
            }
            case 4:
            {
                user_interface(unum, &func);
                break;
            }
            case 5:
            {
                admin_interface(&func);
                break;
            }
        }
	}
	CloseSVGA();                //关闭图形界面 
}
