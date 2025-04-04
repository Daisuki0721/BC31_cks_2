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
	temp.record_times++;		//记录加1
	temp.record_id++;		//记录编号加1
	rec.record_time = temp.record_times;		//第几次违规
	rec.id = temp.record_id;	//记录编号
	rec.readif = 0;		//未读
	rec.appeal_state = 0;	//未申诉
	/*生成抓拍照片路径*/
	sprintf(p, "bmp\\RecGraph\\%s%d.bmp", temp.name, temp.record_times);
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
	if(RL.length <= maxlen)			//最多储存maxlen条记录
	{
	    RListInsert(&RL, rec);		//将记录信息插入线性表
		if(UpdataUser(temp) == -1)		//更新用户信息
		{
			fclose(fp);
			DestroyRList(&RL);
			return -1;
		}
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
int UpdataRec(USER temp, Record rec, int rnum)
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
	if(rnum<0 || rnum > RL.listsize)		//如果更新位置不合法
	{
		fclose(fp);
		DestroyRList(&RL);
		return 0;
	}
	else
	{
		RL.elem[rnum]=rec;		//更新线性表中用户信息 
		fseek(fp, 0, SEEK_SET);
		fwrite(&RL.length, sizeof(int), 1, fp);			//将线性表的相关信息写入文件
		fwrite(&RL.listsize, sizeof(int), 1, fp);
		fwrite(RL.elem, sizeof(Record), RL.length, fp);
		fclose(fp);
		DestroyRList(&RL);			//销毁线性表
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
	newbase->record_time = RL->length + 1;		//记录次数标签
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
参数说明：用户结构体（获取名称），要删除的元素位置
返回值：无 
****************************/
void RListDelete(USER user, int i)
{
	RecList RL = {0};
	char path[40];
	FILE * fp;
	Record * p = NULL;
	Record * q = NULL;
	Record temp = {0};
	ReadAllRec(user, &RL);
	sprintf(path, "record\\%s.r", user.name);
	if((i<0) || (i >= RL.length)) 	//i的位置不合法 
	{
		CloseSVGA();
		printf("ListDelete Wrong!");
		getch();
		exit(1);
	}
	temp = RL.elem[i];		//获取被删除元素
	p = RL.elem+i;  			//p为被删除元素位置
	q = RL.elem+RL.length-1;  	//表尾元素的位置
	for(p++; p<=q; p++)  		//被删除元素之后的元素左移
	{
		(*p).id--;		//记录编号减1
		(*p).record_time--;	//记录次数减1
		*(p-1) = *p;
	}
	RL.length--;  		//表长减1
	if((fp=fopen(path, "rb+"))==NULL)
	{
		prt_hz24(400, 400, "无法打开文件！", 10, "HZK\\Hzk24h");
		delay(5000);
		exit(1);
	}
	else
	{
		if(temp.appeal_state == 0 && temp.appeal_state == 1 && temp.appeal_state == 2 && temp.appeal_state == 4 &&temp.appeal_state == 6 && temp.appeal_state == 7)
		{
			user.record_times--;		//记录次数减1
		}
		user.record_id--;		//记录编号减1
		if(UpdataUser(user) == -1)		//更新用户信息
		{
			fclose(fp);
			DestroyRList(&RL);
			return -1;
		}
		rewind(fp);
		fwrite(&RL.length, sizeof(int), 1, fp);			//将线性表的相关信息写入文件
		fwrite(&RL.listsize, sizeof(int), 1, fp);
		fwrite(RL.elem, sizeof(Record), RL.length, fp);
		fclose(fp);
		DestroyRList(&RL);			//销毁线性表
		delay(50);
		return;
	}
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

/****************************
 * 功能说明：用户记录状态统计
 * 参数说明：用户结构体，记录状态结构体
 * 返回值：无
 * ****************************/
void RecStateCount(USER user, RecState * recstate)
{
	RecList RL = {0};
	int i;
	ReadAllRec(user, &RL);			//获取所有记录到线性表
	recstate->not_appeal = 0;		//未读记录数
	recstate->confirmed = 0;	//已确认记录数
	recstate->appealed = 0;		//申诉中记录数
	recstate->appealed_success = 0;	//申诉成功记录数
	recstate->appealed_fail = 0;	//申诉失败记录数
	recstate->appealed_cancel = 0;	//撤销申诉记录数
	for(i=0; i<RL.length; i++)
	{
		if(RL.elem[i].appeal_state == 0) recstate->not_appeal++;
		if(RL.elem[i].appeal_state == 1 
		&& RL.elem[i].appeal_state == 5
		&& RL.elem[i].appeal_state == 6) recstate->confirmed++;
		if(RL.elem[i].appeal_state == 2) recstate->appealed++;
		if(RL.elem[i].appeal_state == 3) recstate->appealed_success++;
		if(RL.elem[i].appeal_state == 4) recstate->appealed_fail++;
		if(RL.elem[i].appeal_state == 7) recstate->appealed_cancel++;
	}
	DestroyRList(&RL);			//销毁线性表
}

/****************************
 * 功能说明：记录线性表处理为申诉线性表
 * 参数说明：用户结构体，记录线性表地址
 * 返回值：	0: 没有记录 1: 有记录
 * ****************************/
int RecListToAppealList(USER user, RecList * RL)
{
	RecList RL_temp = {0};
	int i, j = 0;
	ReadAllRec(user, &RL_temp);			//获取所有记录到线性表
	if(RL_temp.length == 0) 
	{
		RL->length = 0;
		RL->listsize = RL_temp.listsize;
		return 0;		//如果没有记录，直接返回
	}
	for(i=0; i<RL_temp.length; i++)
	{
		if(RL_temp.elem[i].appeal_state == 0 || RL_temp.elem[i].appeal_state == 2 || RL_temp.elem[i].appeal_state == 3 || RL_temp.elem[i].appeal_state == 4 || RL_temp.elem[i].appeal_state == 7)
		{
			RListInsert(RL, RL_temp.elem[i]);	//将记录信息插入线性表
			j++;
		}
	}
	RL->length = j;
	RL->listsize = RL_temp.listsize;
	DestroyRList(&RL_temp);			//销毁线性表
	return 1;		//返回有记录
}