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
	temp.record_time++;		//��¼��1
	rec.position = temp.record_time;
	rec.readif = 0;		//δ��
	/*����ץ����Ƭ·��*/
	sprintf(p, "bmp\\RecGraph\\%s%d.bmp", temp.name, temp.record_time);
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
	if(UpdataUser(temp) == -1)		//�����û���Ϣ
	{
		fclose(fp);
		DestroyRList(&RL);
		return -1;
	}
	if(RL.length <= maxlen)			//��ഢ��maxlen����¼
	{
	    RListInsert(&RL, rec);		//����¼��Ϣ�������Ա�
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
int UpdataRec(USER temp, Record rec)
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
	if(rec.position<=0 || rec.position > RL.listsize)		//�������λ�ò��Ϸ�
	{
		fclose(fp);
		DestroyRList(&RL);
		return 0;
	}
	else
	{
		RL.elem[rec.position]=rec;		//�������Ա����û���Ϣ 
		fseek(fp, 0, SEEK_SET);
		fwrite(&RL.length, sizeof(int), 1, fp);			//�����Ա�������Ϣд���ļ�
		fwrite(&RL.listsize, sizeof(int), 1, fp);
		fwrite(RL.elem, sizeof(USER), RL.length, fp);
		fclose(fp);
		DestroyUList(&RL);			//�������Ա�
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
	newbase->position = RL->length + 1;		//��¼������ǩ
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
����˵�������Ա��ַ��Ҫɾ����Ԫ��λ�ã�����ɾ��Ԫ�صĴ洢�ռ��ַ
����ֵ���� 
****************************/
void RListDelete(RecList * L, int i)
{
	Record * p = NULL;
	Record * q = NULL;
	if((i<0) || (i >= L->length)) 	//i��λ�ò��Ϸ� 
	{
		CloseSVGA();
		printf("ListDelete Wrong!");
		getch();
		exit(1);
	}
	p = L->elem+i;  			//pΪ��ɾ��Ԫ��λ��
	q = L->elem+L->length-1;  	//��βԪ�ص�λ��
	for(p++; p<=q; p++)  		//��ɾ��Ԫ��֮���Ԫ������
	{
		p->position-=1;
		*(p-1) = *p;
	}
	L->length--;  		//����1
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