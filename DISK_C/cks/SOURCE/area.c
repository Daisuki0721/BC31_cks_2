#include <allfunc.h>

/*初始化地点信息*/
void area_init(void)
{
    int i;
    AREA temp = {0};
    FILE * fp;

    if((fp = fopen("area.dat", "wb")) == NULL)
    {
        CloseSVGA();
        printf("Can't open file!");
        delay(5000);
        exit(1);
    }
    rewind(fp);

    temp.num = 1;
    strcpy(temp.name, "引力中心");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor1.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 2;
    strcpy(temp.name, "摄像头二");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor2.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 3;
    strcpy(temp.name, "摄像头三");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor3.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 4;
    strcpy(temp.name, "摄像头四");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor4.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 5;
    strcpy(temp.name, "摄像头五");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor5.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 6;
    strcpy(temp.name, "摄像头");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor6.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 7;
    strcpy(temp.name, "摄像头");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor7.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 8;
    strcpy(temp.name, "摄像头");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor8.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 9;
    strcpy(temp.name, "摄像头");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor9.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 10;
    strcpy(temp.name, "摄像头");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor10.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 11;
    strcpy(temp.name, "摄像头");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor11.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 12;
    strcpy(temp.name, "摄像头");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor12.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 13;
    strcpy(temp.name, "摄像头");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor13.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    temp.num = 14;
    strcpy(temp.name, "摄像头");
    temp.allnp = 1;
    for(i=0; i<7; i++)
    {
        temp.timest[i] = 0;
        temp.timeed[i] = 86400;
    }
    strcpy(temp.path, "bmp\\monitor\\monitor14.bmp");
    temp.carnum = 0;
    fwrite(&temp, sizeof(AREA), 1, fp);

    rewind(fp);
    fclose(fp);
}

/*读取地点信息*/
void area_read(AREA * AL)
{
    int i;
    FILE * fp;
    if((fp = fopen("area.dat", "rb")) == NULL)
    {
        CloseSVGA();
        printf("Cannot open file!");
        getch();
        exit(1);
    }
    // if((AL = (AREA *)malloc(14 * sizeof(AREA))) == NULL)
    // {
    //     CloseSVGA();
    //     printf("Not enough memory!");
    //     getch();
    //     exit(1);
    // }

    rewind(fp);

    for(i=0; i<14; i++)
    {
        fread(&AL[i], sizeof(AREA), 1, fp);
    }
    
    fclose(fp);
}

/*更新地点信息*/
void area_update(AREA temp, int i)
{
    FILE * fp;
    AREA AL[14];
    area_read(AL);
    if((fp = fopen("area.dat", "wb")) == NULL)
    {
        CloseSVGA();
        printf("Cannot open file!");
        getch();
        exit(1);
    }
    AL[i] = temp;
    rewind(fp);
    fwrite(AL, sizeof(AREA), 14, fp);
    fclose(fp);
}

/*保存地点信息*/
void area_save(AREA * AL)
{
    FILE * fp;
    if((fp = fopen("area.dat", "wb")) == NULL)
    {
        CloseSVGA();
        printf("Cannot open file!");
        getch();
        exit(1);
    }
    rewind(fp);
    fwrite(AL, sizeof(AREA), 14, fp);
    fclose(fp);
}

/*释放地点数组*/
void area_destory(AREA * AL)
{
    free(AL);
}

/*时间储存函数（将save中的时间存储在time中）
 *save为一个三个int类型数组，分别为小时，分钟，秒*/
void area_timesave(long * time, int * save)
{
    *time = save[0]*3600 + save[1]*60 + save[2];
}

/*时间解析函数（将time中的时间分解到save中）
 *save为一个三个int类型数组，分别为小时，分钟，秒*/
void area_timeread(long time, int * save)
{
    save[2] = time % 60;
    time /= 60;
    save[1] = time % 60;
    time /= 60;
    save[0] = time;
}

/*将非解析时间打印在指定位置*/
void prt_time(int x, int y, long time)
{
    int i;
    int save[3];
    char temp[9];
    area_timeread(time, save);

    sprintf(temp, "%02d:%02d:%02d", save[0], save[1], save[2]);
    prt_asc16(x, y, temp, 0);
}

