#include <allfunc.h>

/**********************
����˵��������һ����¼
����˵�����û��ṹ�壨���ڶ�ȡ�˻���������¼�ص���Ϣ����󱣴���
����ֵ˵��:0�����ɳɹ�   -1������ʧ�� 
**********************/
int CreateRec(USER temp, int place, int maxlen)
{
	int flag;
	char p[80];
	Record rec;
	time_t now=time(NULL);
	struct tm *local = localtime(&now);
	/*��¼ʱ����Ϣ*/
	rec.year = local->tm_year + 1900;
	rec.month = local->tm_mon;
	rec.day = local->tm_mday;
	rec.week = local->tm_wday;
	rec.hour = local->tm_hour;
	rec.minute = local->tm_min;
	rec.second = local->tm_sec;
	/*��¼�ص���Ϣ*/
	rec.place = place;
	/*��¼ץ����Ƭ·��*/
	temp.record_times++;		//��¼��1
	temp.record_id++;		//��¼��ż�1
	rec.record_time = temp.record_times;		//�ڼ���Υ��
	rec.id = temp.record_id;	//��¼���
	rec.readif = 0;		//δ��
	rec.appeal_state = 0;	//δ����
	/*����ץ����Ƭ·��*/
	sprintf(p, "bmp\\RecGraph\\%s%d.bmp", temp.name, temp.record_times);
	strcpy(rec.RecGraph, p);
	/*����ץ����Ƭ*/
	//SaveBMP();		//�Ȼ�����д

	flag = SaveRec(temp, rec, maxlen);
	return flag;
}
	

/**********************
����˵���������¼��Ϣ���� (��󱣴�maxlen��)
����˵�����û��ṹ�壨���ڶ�ȡ�˻���������¼�ṹ�� ����󱣴���
����ֵ˵��:0������ɹ�   -1������ʧ�� 
**********************/
int SaveRec(USER temp, Record rec, int maxlen)
{
	RecList RL={0};
	FILE *fp=NULL;
    char path[80];
    sprintf(path, "record\\%s.r", temp.name);	//ֻ������һλ��׺��
	ReadAllRec(temp, &RL);
	if((fp=fopen(path, "rb+"))==NULL)		//�״�ʹ��ʱӦ�����ļ�
	{
		prt_hz24(400, 400, "�޷����ļ���", 10, "HZK\\Hzk24h");
		delay(3000);
		exit(1);
	}
	if(RL.length <= maxlen)			//��ഢ��maxlen����¼
	{
	    RListInsert(&RL, rec);		//����¼��Ϣ�������Ա�
		if(UpdataUser(temp) == -1)		//�����û���Ϣ
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
����˵������ȡ�ļ��е����м�¼
����˵�����û��ṹ�壨���ڶ�ȡ�˻���������¼���Ա��ַ 
����ֵ���� 
*******************/
void ReadAllRec(USER temp, RecList * RL)
{
	int length = 0;						//�������Ա��� 
	int listsize = R_LIST_INIT_SIZE;		//���Ա��ʼ���� 
	FILE *fp=NULL;
	char path[80];
	sprintf(path,"record\\%s.r", temp.name);
	if((fp=fopen(path, "rb+")) == NULL)			//����ļ����Ƿ�����
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
	   if((RL->elem = (Record *)malloc(listsize * sizeof(Record)))==NULL)//�����û����Ա� 
	   {
		    CloseSVGA();
		    printf("No enough memory!\n");
		    getch();
		    exit(-1);
	   } 
	  	fread(RL->elem, sizeof(Record),length, fp);		//��ȡ�ļ��������û������Ա��� 
    }
	fclose(fp);
}

/*******************
 * ����˵������ȡ��ǰ�û���¼��
 * ����˵�����û��ṹ�壨���ڶ�ȡ�˻���������¼���Ա��ַ
 * ����ֵ����¼��
 * *******************/
int ReadRecNum(USER temp)
{
	int length = 0;						//�������Ա��� 
	FILE *fp=NULL;
	char path[80];
	sprintf(path,"record\\%s.r", temp.name);
	if((fp=fopen(path, "rb+")) == NULL)			//����ļ����Ƿ�����
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
	return length;			//�����û����� 
}


/*******************
����˵�������¼�¼��Ϣ 
����˵������¼�ṹ�� 
����ֵ��1�����³ɹ���    0������ʧ�� 
*******************/
int UpdataRec(USER temp, Record rec, int rnum)
{
	RecList RL = {0};				//��¼���Ա� 
	FILE * fp = NULL;
	char path[80];
	ReadAllRec(temp, &RL);				//��ȡ���м�¼�����Ա�
	sprintf(path,"record\\%s.r", temp.name);
	if((fp=fopen(path, "rb+"))==NULL)
	{
		prt_hz24(400, 400, "�޷����ļ���", 10, "HZK\\Hzk24h");
		delay(5000);
		exit(1);
	}
	if(rnum<0 || rnum > RL.listsize)		//�������λ�ò��Ϸ�
	{
		fclose(fp);
		DestroyRList(&RL);
		return 0;
	}
	else
	{
		RL.elem[rnum]=rec;		//�������Ա����û���Ϣ 
		fseek(fp, 0, SEEK_SET);
		fwrite(&RL.length, sizeof(int), 1, fp);			//�����Ա�������Ϣд���ļ�
		fwrite(&RL.listsize, sizeof(int), 1, fp);
		fwrite(RL.elem, sizeof(Record), RL.length, fp);
		fclose(fp);
		DestroyRList(&RL);			//�������Ա�
		return 1;
	}
}

/****************************
����˵��������һ�����Ա� 
����˵�������Ա��ַ
����ֵ��  ��  
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
����˵���������Ա�Lĩβ����Ԫ�� 
����˵�������Ա��ַ��Ҫ�����Ԫ��
����ֵ��  ��  
****************************/
void RListInsert(RecList * RL, Record r) 
{
	Record * newbase = NULL;
	newbase->record_time = RL->length + 1;		//��¼������ǩ
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
	*(RL->elem + (RL->length))=r;		//ָ������ƶ����Ա�ǰ����
	RL->length++;
}



/****************************
����˵���������Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
����˵�����û��ṹ�壨��ȡ���ƣ���Ҫɾ����Ԫ��λ��
����ֵ���� 
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
	if((i<0) || (i >= RL.length)) 	//i��λ�ò��Ϸ� 
	{
		CloseSVGA();
		printf("ListDelete Wrong!");
		getch();
		exit(1);
	}
	temp = RL.elem[i];		//��ȡ��ɾ��Ԫ��
	p = RL.elem+i;  			//pΪ��ɾ��Ԫ��λ��
	q = RL.elem+RL.length-1;  	//��βԪ�ص�λ��
	for(p++; p<=q; p++)  		//��ɾ��Ԫ��֮���Ԫ������
	{
		(*p).id--;		//��¼��ż�1
		(*p).record_time--;	//��¼������1
		*(p-1) = *p;
	}
	RL.length--;  		//����1
	if((fp=fopen(path, "rb+"))==NULL)
	{
		prt_hz24(400, 400, "�޷����ļ���", 10, "HZK\\Hzk24h");
		delay(5000);
		exit(1);
	}
	else
	{
		if(temp.appeal_state == 0 && temp.appeal_state == 1 && temp.appeal_state == 2 && temp.appeal_state == 4 &&temp.appeal_state == 6 && temp.appeal_state == 7)
		{
			user.record_times--;		//��¼������1
		}
		user.record_id--;		//��¼��ż�1
		if(UpdataUser(user) == -1)		//�����û���Ϣ
		{
			fclose(fp);
			DestroyRList(&RL);
			return -1;
		}
		rewind(fp);
		fwrite(&RL.length, sizeof(int), 1, fp);			//�����Ա�������Ϣд���ļ�
		fwrite(&RL.listsize, sizeof(int), 1, fp);
		fwrite(RL.elem, sizeof(Record), RL.length, fp);
		fclose(fp);
		DestroyRList(&RL);			//�������Ա�
		delay(50);
		return;
	}
}


/****************************
����˵�����������Ա�L
����˵�������Ա��ַ
����ֵ���� 
****************************/
void DestroyRList(RecList * RL)	
{
	free(RL->elem);
	RL->listsize=0;
	RL->length=0;
}

/****************************
 * ����˵�����û���¼״̬ͳ��
 * ����˵�����û��ṹ�壬��¼״̬�ṹ��
 * ����ֵ����
 * ****************************/
void RecStateCount(USER user, RecState * recstate)
{
	RecList RL = {0};
	int i;
	ReadAllRec(user, &RL);			//��ȡ���м�¼�����Ա�
	recstate->not_appeal = 0;		//δ����¼��
	recstate->confirmed = 0;	//��ȷ�ϼ�¼��
	recstate->appealed = 0;		//�����м�¼��
	recstate->appealed_success = 0;	//���߳ɹ���¼��
	recstate->appealed_fail = 0;	//����ʧ�ܼ�¼��
	recstate->appealed_cancel = 0;	//�������߼�¼��
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
	DestroyRList(&RL);			//�������Ա�
}

/****************************
 * ����˵������¼���Ա���Ϊ�������Ա�
 * ����˵�����û��ṹ�壬��¼���Ա��ַ
 * ����ֵ��	0: û�м�¼ 1: �м�¼
 * ****************************/
int RecListToAppealList(USER user, RecList * RL)
{
	RecList RL_temp = {0};
	int i, j = 0;
	ReadAllRec(user, &RL_temp);			//��ȡ���м�¼�����Ա�
	if(RL_temp.length == 0) 
	{
		RL->length = 0;
		RL->listsize = RL_temp.listsize;
		return 0;		//���û�м�¼��ֱ�ӷ���
	}
	for(i=0; i<RL_temp.length; i++)
	{
		if(RL_temp.elem[i].appeal_state == 0 || RL_temp.elem[i].appeal_state == 2 || RL_temp.elem[i].appeal_state == 3 || RL_temp.elem[i].appeal_state == 4 || RL_temp.elem[i].appeal_state == 7)
		{
			RListInsert(RL, RL_temp.elem[i]);	//����¼��Ϣ�������Ա�
			j++;
		}
	}
	RL->length = j;
	RL->listsize = RL_temp.listsize;
	DestroyRList(&RL_temp);			//�������Ա�
	return 1;		//�����м�¼
}