#include <allfunc.h>

/**********************
功能说明：生成一条记录
参数说明：用户结构体（用于读取账户名），记录地点信息，最大保存数
返回值说明:0：生成成功   -1：生成失败 
**********************/
int CreateRec(USER temp, int place, int maxlen)
{
	int flag;
	char p[80];
	Record rec;
	time_t now=time(NULL);
	struct tm *local = localtime(&now);
	/*记录时间信息*/
	rec.year = local->tm_year + 1900;
	rec.month = local->tm_mon;
	rec.day = local->tm_mday;
	rec.week = local->tm_wday;
	rec.hour = local->tm_hour;
	rec.minute = local->tm_min;
	rec.second = local->tm_sec;
	/*记录地点信息*/
	rec.place = place;
	/*记录抓拍照片路径*/
	temp.record_time++;		//记录加1
	rec.position = temp.record_time;
	rec.readif = 0;		//未读
	/*生成抓拍照片路径*/
	sprintf(p, "bmp\\RecGraph\\%s%d.bmp", temp.name, temp.record_time);
	strcpy(rec.RecGraph, p);
	/*生成抓拍照片*/
	//SaveBMP();		//等会再来写

	flag = SaveRec(temp, rec, maxlen);
	return flag;
}
	

/**********************
功能说明：保存记录信息函数 (最大保存maxlen条)
参数说明：用户结构体（用于读取账户名），记录结构体 ，最大保存数
返回值说明:0：保存成功   -1：保存失败 
**********************/
int SaveRec(USER temp, Record rec, int maxlen)
{
	RecList RL={0};
	FILE *fp=NULL;
    char path[80];
    sprintf(path, "record\\%s.r", temp.name);	//只设置了一位后缀名
	ReadAllRec(temp, &RL);
	if((fp=fopen(path, "rb+"))==NULL)		//首次使用时应创建文件
	{
		prt_hz24(400, 400, "无法打开文件！", 10, "HZK\\Hzk24h");
		delay(3000);
		exit(1);
	}
	if(UpdataUser(temp) == -1)		//更新用户信息
	{
		fclose(fp);
		DestroyRList(&RL);
		return -1;
	}
	if(RL.length <= maxlen)			//最多储存maxlen条记录
	{
	    RListInsert(&RL, rec);		//将记录信息插入线性表
	    fseek(fp, 0, SEEK_SET);
	    rewind(fp);
	    fwrite(&RL.length, sizeof(int), 1, fp);
	    fwrite(&RL.listsize, sizeof(int), 1, fp);
	    fwrite(RL.elem, sizeof(Record), RL.length, fp);
		DestroyUList(&RL);
	    fclose(fp);
		delay(500);
		return 0;
	}
	else
	{
		DestroyRList(&RL);
		fclose(fp);
		delay(500);		
		return -1;
	}
}


/*******************
功能说明：获取文件中的所有记录
参数说明：用户结构体（用于读取账户名），记录线性表地址 
返回值：无 
*******************/
void ReadAllRec(USER temp, RecList * RL)
{
	int length = 0;						//接收线性表长度 
	int listsize = R_LIST_INIT_SIZE;		//线性表初始长度 
	FILE *fp=NULL;
	char path[80];
	sprintf(path,"record\\%s.r", temp.name);
	if((fp=fopen(path, "rb+")) == NULL)			//检测文件打开是否正常
	{
		fp=fopen(path, "wb");
		rewind(fp);
		fwrite(&length, sizeof(int), 1, fp);
		fwrite(&listsize, sizeof(int), 1, fp);
	}								
    else
    {
       fseek(fp, 0, SEEK_SET);
	   fread(&length, sizeof(int), 1, fp);
	   fread(&listsize, sizeof(int), 1, fp);
	   RL->length = length;
	   RL->listsize = listsize;
	   if((RL->elem = (Record *)malloc(listsize * sizeof(Record)))==NULL)//构建用户线性表 
	   {
		    CloseSVGA();
		    printf("No enough memory!\n");
		    getch();
		    exit(-1);
	   } 
	  	fread(RL->elem, sizeof(Record),length, fp);		//读取文件的所有用户到线性表中 
    }
	fclose(fp);
}

/*******************
 * 功能说明：读取当前用户记录数
 * 参数说明：用户结构体（用于读取账户名），记录线性表地址
 * 返回值：记录数
 * *******************/
int ReadRecNum(USER temp)
{
	int length = 0;						//接收线性表长度 
	FILE *fp=NULL;
	char path[80];
	sprintf(path,"record\\%s.r", temp.name);
	if((fp=fopen(path, "rb+")) == NULL)			//检测文件打开是否正常
	{
		fp=fopen(path, "wb");
		rewind(fp);
		fwrite(&length, sizeof(int), 1, fp);
	}								
	else
	{
	   fseek(fp, 0, SEEK_SET);
	   fread(&length, sizeof(int), 1, fp);
	}
	fclose(fp);
	return length;			//返回用户数量 
}


/*******************
功能说明：更新记录信息 
参数说明：记录结构体 
返回值：1：更新成功）    0：更新失败 
*******************/
int UpdataRec(USER temp, Record rec)
{
	RecList RL = {0};				//记录线性表 
	FILE * fp = NULL;
	char path[80];
	ReadAllRec(temp, &RL);				//获取所有记录到线性表
	sprintf(path,"record\\%s.r", temp.name);
	if((fp=fopen(path, "rb+"))==NULL)
	{
		prt_hz24(400, 400, "无法打开文件！", 10, "HZK\\Hzk24h");
		delay(5000);
		exit(1);
	}
	if(rec.position<=0 || rec.position > RL.listsize)		//如果插入位置不合法
	{
		fclose(fp);
		DestroyRList(&RL);
		return 0;
	}
	else
	{
		RL.elem[rec.position]=rec;		//更新线性表中用户信息 
		fseek(fp, 0, SEEK_SET);
		fwrite(&RL.length, sizeof(int), 1, fp);			//将线性表的相关信息写入文件
		fwrite(&RL.listsize, sizeof(int), 1, fp);
		fwrite(RL.elem, sizeof(USER), RL.length, fp);
		fclose(fp);
		DestroyUList(&RL);			//销毁线性表
		return 1;
	}
}

/****************************
功能说明：建立一个线性表 
参数说明：线性表地址
返回值：  无  
****************************/
void InitRList(RecList * RL)  
{
	if((RL->elem=(Record *)malloc(R_LIST_INIT_SIZE * sizeof(Record))) == NULL)
	{
		CloseSVGA();
		printf("No enough memory!\n");
		exit(-1);
	}
	RL->length = 0;
	RL->listsize = R_LIST_INIT_SIZE;
}


/****************************
功能说明：在线性表L末尾插入元素 
参数说明：线性表地址，要插入的元素
返回值：  无  
****************************/
void RListInsert(RecList * RL, Record r) 
{
	Record * newbase = NULL;
	newbase->position = RL->length + 1;		//记录次数标签
	if(RL->length >= RL->listsize)
	{
		if((newbase = (Record *)realloc(RL->elem, (RL->listsize+R_LISTINCEREMENT) * sizeof(Record)))==NULL)
	    {
		    CloseSVGA();
		    printf("No enough memory!\n");
		    exit(-1);
	    }
		RL->elem = newbase;
		RL->listsize += R_LISTINCEREMENT;
	}
	*(RL->elem + (RL->length))=r;		//指针向后移动线性表当前长度
	RL->length++;
}



/****************************
功能说明：在线性表L中删除第i个元素，并用e返回其值
参数说明：线性表地址，要删除的元素位置，接收删除元素的存储空间地址
返回值：无 
****************************/
void RListDelete(RecList * L, int i)
{
	Record * p = NULL;
	Record * q = NULL;
	if((i<0) || (i >= L->length)) 	//i的位置不合法 
	{
		CloseSVGA();
		printf("ListDelete Wrong!");
		getch();
		exit(1);
	}
	p = L->elem+i;  			//p为被删除元素位置
	q = L->elem+L->length-1;  	//表尾元素的位置
	for(p++; p<=q; p++)  		//被删除元素之后的元素左移
	{
		p->position-=1;
		*(p-1) = *p;
	}
	L->length--;  		//表长减1
}


/****************************
功能说明：销毁线性表L
参数说明：线性表地址
返回值：无 
****************************/
void DestroyRList(RecList * RL)	
{
	free(RL->elem);
	RL->listsize=0;
	RL->length=0;
}