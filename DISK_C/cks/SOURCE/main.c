#include <allfunc.h>

void main()
{          
	int func=5;
    int unum=0;

    int i;
    char getbmp[100];

    FILE *fp=NULL;


    SetSVGA64k();                    //����SVGA��ͼ����  
    
    welcome_video();                 //��������

	if((fp=fopen("area.dat","rb"))==NULL)       //����ص��ļ������ڣ��½�����ʼ�� 
	{
		area_init();                        //��ʼ���ص���Ϣ
	}
	fclose(fp);

    fp=NULL;

    if((fp=fopen("userinfo.dat","rb"))==NULL)   //����û���Ϣ�ļ������ڣ��½�����ʼ�� .dat","rb"))==NULL)//���δ��ʼ��������Ϣ������г�ʼ�� 
	{
		user_init();                        //��ʼ���û���Ϣ
	}

	fclose(fp);

    /********************
    0:��ӭ����
    1:�û���¼
    2:�û�ע��
    3:�����¼
    4:�û�������
    5:����Ա������
    ********************/



//������������

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
	CloseSVGA();                //�ر�ͼ�ν��� 
}
