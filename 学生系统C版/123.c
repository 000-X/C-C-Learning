#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define M 50
#define PAGESIZE 10 /*����ÿҳ��ʾ��ѧ����������*/
enum xb{boy=1,g};
#define A1 "a1.dat"/*��ȡ�ļ���ַ*/
#define A2 "a2.dat"

typedef struct node{
        int id;/*ѧ��*/
        char name[M];/*����*/
        int gender;/*�Ա�,����ö������*/
        char zye[M];/*רҵ*/ 
        char cla[M];/*�༶*/
        int math,eng,C,sum;/*��ѧ��Ӣ�c���ԣ��ܳɼ�*/
        int pm1,pm2;/*pm1�༶����*/
        char fang[M];/*�о�����*/
        char dao[M];/*��ʦ*/
        int sum1,lun;/*�γ��ۺϳɼ������ĳɼ�*/ 
        struct node *next;/*ָ����һ������*/ 
        }student;
int ID=0;
student *head1=NULL,*head2=NULL;/*head1�Ǳ�������*/
int people=0;
int change=0;

void addnode(student **headp,student *stu1)/*��������*/
{
	student *p=*headp;
	if(*headp==NULL){
		*headp=stu1;
	}
	else{
		p=*headp;
		while(p->next!=NULL) 
			p=p->next;
		p->next=stu1;
	}
}
void add1()/*���뱾����*/
{
	student *p;
	void addnode(student **headp,student *stu1);
	int x;
	printf("�����뱾������Ϣ����������Ϊ�գ��Ա�Ϊ�գ�רҵ��Ϊ�գ��༶��Ϊ��;\n");
	printf("ע���Ա����루1.���ԣ�2.Ů�ԣ�.\n");
	do{
		fflush(stdin);
		p=(student *)malloc(sizeof(student));
		scanf("%s%d%s%s",p->name,&p->gender ,p->zye,p->cla);
		ID++;
		p->id=ID;
		p->math=-1;
		p->eng=-1;
		p->C=-1;
		p->sum=-1;
		p->pm1=-1;
		p->pm2 =1;
		people++;
		p->next=NULL;
		addnode(&head1,p);
		printf("�Ƿ�������루0Ϊ������־��:");
		scanf("%d",&x);
	}while(x!=0);	
}
void add2()/*�����о���*/
{
	student *p;
	void addnode(student **headp,student *stu2);
	int x;
	printf("�����о�����Ϣ����������Ϊ�գ��Ա�Ϊ�գ�רҵ��Ϊ�գ��༶��Ϊ��\n");
	printf("				  �о�����Ϊ�գ���ʦ��Ϊ��.\n");
	printf("ע���Ա����루1.���ԣ�2.Ů�ԣ�.\n");
	do{
		fflush(stdin);
		p=(student *)malloc(sizeof(student));
		scanf("%s%d%s%s%s%s",p->name,&p->gender,p->zye,p->cla,p->fang,p->dao);
		ID++;
		p->id=ID;
		p->sum1=-1;
		p->lun=-1;
		p->sum =-1;
		p->pm1=-1;
		p->pm2 =-1;
		people++;
		p->next=NULL;
		addnode(&head2,p);
		printf("�Ƿ�������루0Ϊ������־��:");
		scanf("%d",&x);
	}while(x!=0);
}
void p1()/*���������ݴ洢���ļ�*/
{
	FILE *fp1,*fp2;
	int nodenumder=0;
	student *p1=NULL,*p2=NULL;
	p1=head1;
	p2=head2;
	if((fp1=fopen(A1,"wb"))==NULL)
	{
		printf("�޷��������ļ�!\n");
		return ;
	}
	printf("���ڴ洢���ݣ����Ե�......\n");
	while(p1!=NULL)
	{
		if(fwrite(p1,sizeof(student),1,fp1)==1)
			nodenumder++;
		else 
			printf("ѧ�ţ�%d ������%s �����ݱ���ʧ�ܣ�\n",p1->id,p1->name);
		p1=p1->next;
	}
	fclose(fp1);
	if((fp2=fopen(A2,"wb"))==NULL)
	{
		printf("�޷��������ļ�!");
		return ;
	}
	while(p2!=NULL)
	{
		if(fwrite(p2,sizeof(student),1,fp2)==1)
			nodenumder++;
		else
			printf("ѧ�ţ�%d ������%s �����ݱ���ʧ��\n",p2->id,p2->name);
		p2=p2->next;
	}
	fclose(fp2);
	printf("���ݱ����������������%d ��ѧ������!\n",nodenumder);
}
int p2()/*���ļ���ȡ��������*/
{
	FILE *fp1,*fp2;
	int flag=0,flag1=1;
	int nodenumder=0;
	student *p1,*p2;
	if((fp1=fopen(A1,"rb"))==NULL )
	{
		printf("�ļ��޷��򿪣�\n");
		flag1=0;
	}
	if((fp2=fopen(A2,"rb"))==NULL)
	{
		printf("�ļ��޷��򿪣�\n");
		flag=1;
	}
	if(flag1==0 && flag==1) return -1;
	printf("���ڶ�ȡ�ļ�����...\n");
	do{
		if(!feof(fp1)){
			p1=(student *)malloc(sizeof(student));
			if(fread(p1,sizeof(student),1,fp1)==1)
			{
				p1->next=NULL;
				if(ID<p1->id) ID=p1->id;
				addnode(&head1,p1);
				nodenumder++;
			}
		}
		if(!feof(fp2))
		{
			p2=(student *)malloc(sizeof(student));
			if(fread(p2,sizeof(student),1,fp2)==1)
			{
				p2->next=NULL;
				if(ID<p2->id) ID=p2->id;
				addnode(&head2,p2);
				nodenumder++;
			}
		}
		if(feof(fp1) && feof(fp2))
		{
			fclose(fp1);
			fclose(fp2);
			printf("��ȡ����������ȡ%d ��ѧ����Ϣ!\n",nodenumder);
			system("pause");
			return nodenumder;
		}
	}while(1);
}
int checkdata(student *p)/*������뺯��,,�ж��Ƿ�Ϊ��*/
{
	int flag=1,m,i=0;
	char k[M];
	strcpy(k,p->name);
	while(k[i]!='\0')
	{
		m=(int)k[i];
		if(m>=32 && m<=126)
			flag=0;
		i++;
	}
	strcpy(k,p->zye);
	while(k[i]!='\0')
	{
		m=(int)k[i];
		if(m>=32 && m<=126)
			flag=0;
		i++;
	}
	strcpy(k,p->cla);
	while(k[i]!='\0')
	{
		m=(int)k[i];
		if(m>=32 && m<=126)
			flag=0;
		i++;
	}
	strcpy(k,p->fang);
	while(k[i]!='\0')
	{
		m=(int)k[i];
		if(m>=32 && m<=126)
			flag=0;
		i++;
	}
	strcpy(k,p->dao);
	while(k[i]!='\0')
	{
		m=(int)k[i];
		if(m>=32 && m<=126)
			flag=0;
		i++;
	}
	if(flag==0) return flag;
	return flag;
}
void p3()/*�޸�ѧ��������Ϣ*/
{
	int id;
	student *p;
	fflush(stdin);
	printf("������Ҫ�޸ĵ�ѧ��ѧ�ţ�\n");
	scanf("%d",&id);
	p=head1;
	while(p!=NULL)
	{
		if(p->id==id)
		{
			printf("�޸�ǰ�����ݣ�%s,%d,%s,%s\n",p->name,p->gender,p->zye,p->cla);
			do{
				fflush(stdin);
				printf("�޸����ѣ�������Ϊ�գ��Ա�Ϊ�գ�רҵ��Ϊ�գ��༶��Ϊ�գ�\n");
				printf("�Ա����루1.����  2.Ů�ԣ�;\n");
				printf("�����������������Ա�ѡ�רҵ���༶��\n");
				scanf("%s%d%s%s",p->name,&p->gender,p->zye,p->cla);
			}while(checkdata(p)==0);
			change=1;
			printf("�޸ĳɹ���\n");
			printf("�޸ĺ�����Ϊ:%s,%d,%s,%s\n",p->name,p->gender,p->zye,p->cla);
			break;
		}
		p=p->next;
	}
	if(p==NULL)
	{
		p=head2;
		while(p!=NULL)
		{
			if(p->id=id)
			{
				printf("�޸�ǰ����:%s,%d,%s,%s,%s,%s\n",p->name,p->gender,p->zye,p->cla,p->fang,p->dao);
				do{
					fflush(stdin);
					printf("�޸����ѣ�������Ϊ�գ��Ա�Ϊ�գ�רҵ��Ϊ�գ��༶��Ϊ�գ�\n");
					printf("		  �о�����Ϊ�գ���ʦ��Ϊ�ա�\n");
					printf("�Ա����루1.����  2.Ů�ԣ�;\n");
					printf("�����������������Ա�ѡ�רҵ���༶���о����򣬵�ʦ��\n");
					scanf("%s%d%s%s%s%s",p->name,&p->gender,p->zye,p->cla,p->fang,p->dao);
				}while(checkdata(p)==0);
				change=1;
				printf("�޸ĳɹ�!\n");
				printf("�޸ĺ�����:%s,%d,%s,%s,%s,%s\n",p->name,p->gender,p->zye,p->cla,p->fang,p->dao);
				break;
			}
			p=p->next;
		}
	}
}
void benhead()/*��ʾѧ����������*/
{
	printf("%2s%10s%6s%20s%20s","ѧ��","����","�Ա�","רҵ","�༶");
	printf("%6s%6s%6s%6s%8s%8s","����","Ӣ��","C����","�ܳɼ�","������","У����");
}
void showonestudent(student *p)/*����ѧ����Ϣ*/
{
	printf("\n%4d%10s",p->id,p->name);
	switch(p->gender){
	case 1: printf(" ���� ");break;
	case 2: printf(" Ů�� ");break;
	}
	printf("%20s%20s",p->zye,p->cla);
	printf("%6d%6d%6d%6d%8d%8d",p->math,p->eng,p->C,p->sum,p->pm1,p->pm2);
}
void yanhead()/*�о�����������*/
{
	printf("%2s%10s%6s%20s%20s%20s%10s","ѧ��","����","�Ա�","רҵ","�༶","�о�����","��ʦ");
	printf("%6s%6s%6s%8s%8s","�ۺϳɼ�","���ĳɼ�","�ܳɼ�","������","У����");
}
void show1(student *p)/*�о���*/
{
	printf("\n%4d%10s",p->id,p->name);
	switch(p->gender){
	case 1: printf(" ���� ");break;
	case 2: printf(" Ů�� ");break;
	}
	printf("%20s%20s%20s%10s",p->zye,p->cla,p->fang,p->dao);
	printf("%6d%6d%6d%8d%8d",p->sum1,p->lun,p->sum,p->pm1,p->pm2);
}
void p4()/*����ѧ��ɾ��ѧ��*/
{
	student *p=head1,*q;
	student *m=head2,*n;
	int id; 
	printf("������Ҫɾ����ѧ��:");
	scanf("%d",&id);
	while(p!=NULL){
		if(p->id==id) break;
		q=p;
		p=p->next;
	}
	if(p==head1){
		head1=p->next;
		free(p); 
	}
	else if(p==NULL){
		printf("���Ҳ�����ѧ��!");
	}
	else{
		q->next=p->next;
		free(p);
		printf("ɾ����ϣ�\n"); 
	}
	if(p==NULL){
		while(m!=NULL){
			if(m->id==id) break;
			n=m;
			m=m->next;
		}
		if(m==head2){
			head2=m->next;
			free(m); 
		}
		else if(m==NULL){
			printf("���Ҳ�����ѧ��!");
		}
		else{
			n->next=m->next;
			free(m);
		} 
	}
}
void p5()/*����ѧ�Ų�ѯ��Ϣ*/
{
	void showonestudent(student *p);
	void show1(student *p);
	void benhead();
	void yanhead();
	int id,n=0;
	int flag=1;
	student *p;
	fflush(stdin);
	printf("������Ҫ��ѯ��Ϣ��ѧ��ѧ��:");
	scanf("%d",&id);
	if(id<=0) printf("�޸�ѧ����Ϣ\n");
	p=head1;
	while(p!=NULL)
	{
		if(p->id==id){
			n++;
			if(n==1){
				benhead();
				showonestudent(p);
			}
			else 
				showonestudent(p);
			printf("\n");
			flag=0;
			break;
		}
		p=p->next;
	}
	if(p==NULL)
	{
		p=head2;
		while(p!=NULL)
		{
			if(p->id==id){
				flag=0;
				n++;
				if(n==1){
					yanhead();
					show1(p);
				}
				else 
					show1(p);
				printf("\n");
				break;
			}
			p=p->next;
		}
	}
	if(flag!=0) printf("�޸�ѧ����Ϣ!");
}
void p6()/*ѧ���ɼ�����*/
{
	void math(student *p);
	void eng(student *p);
	void C(student *p);
	void sum1(student *p);
	void lun(student *p);
	int id,a,y=1;
	student *p;
	fflush(stdin);
	printf("������Ҫ�����ѧ���ɼ���ѧ�ţ�\n");
	scanf("%d",&id);
	while(y){
		p=head1;
		while(p!=NULL)
		{
			if(p->id==id)
			{
				fflush(stdin);
				printf("�������ѧ���Ǳ�������Ϣ\nѧ��: %d ����: %s \n",p->id,p->name);
				printf("ѡ����Ҫ�����ѧ��: 1- ��ѧ   2- Ӣ��  3- C����\n");
				scanf("%d",&a);
				switch(a){
				case 1: math(p);break;
				case 2: eng(p) ;break;
				case 3: C(p);break;
				}
			}
			p=p->next;
		}
		if(p==NULL)
		{
			p=head2;
			while(p!=NULL)
			{
				if(p->id==id)
				{
					fflush(stdin);
					printf("�������ѧ�����о�����Ϣ\nѧ��:%d ����:%s\n",p->id,p->name);
					printf("ѡ����Ҫ����ĳɼ�����: 1- �ۺϳɼ�   2- ���ĳɼ�\n");
					scanf("%d",&a);
					switch(a){
					case 1: sum1(p);break;
					case 2: lun(p);break;
					}
				}
				p=p->next;
			}
		}
		printf("�Ƿ���������ѧ���ɼ���0- ȡ��    1- ����\n");
		scanf("%d",&y);
	}
}
void math(student *p)
{
	int a;
	printf("�������ѧ������ѧ�ɼ�:");
	scanf("%d",&a);
	if(a>100 || a<0){
		printf("�ɼ��������!\n����������:");
		scanf("%d",&a);
	}
	p->math=a;
}
void eng(student *p)
{
	int a;
	printf("�������ѧ����Ӣ��ɼ�:");
	scanf("%d",&a);
	if(a>100 || a<0)
	{
		printf("�ɼ��������\n����������:");
		scanf("%d",&a);
	}
	p->eng=a;
}
void C(student *p)
{
	int a;
	printf("�������ѧ����C���Գɼ�:");
	scanf("%d",&a);
	if(a>100 || a<0)
	{
		printf("�ɼ��������\n����������:");
		scanf("%d",&a);
	}
	p->C=a;
}
void sum1(student *p)
{
	int a;
	printf("�������ѧ�����ۺϳɼ�:");
	scanf("%d",&a);
	if(a>100 || a<0)
	{
		printf("�ɼ��������\n����������:");
		scanf("%d",&a);
	}
	p->sum1=a;
}
void lun(student *p)
{
	int a;
	printf("�������ѧ�������ĳɼ�:");
	scanf("%d",&a);
	if(a>100 || a<0)
	{
		printf("�ɼ��������\n����������:");
		scanf("%d",&a);
	}
	p->lun=a;
}
void q1()/*�޸�ѧ���ɼ�*/
{
	int id,y=1,a;
	student *p;
	while(y)
	{
		fflush(stdin);
		printf("������Ҫ�޸ĵ�ѧ��ѧ��:");
		scanf("%d",&id);
		p=head1;
		while(p!=NULL)
		{
			if(p->id==id)
			{
				fflush(stdin);
				printf("�޸ĳɼ���ѧ�� ѧ�ţ�%d ����: %s\n",p->id,p->name);
				printf("�ɼ�����Ϊ ��ѧ: %d Ӣ��: %d C����: %d\n",p->math,p->eng,p->C);
				printf("**ȷ���Ƿ���Ҫ�޸�: 0- ȡ�� ** 1- ȷ��\n");
				scanf("%d",&a);
				if(a==1)
				{
					printf("����������ѧ���ɼ�,��ѧ��Ӣ��C�����ԣ�\n");
					scanf("%d%d%d",&p->math,&p->eng,&p->C);
				}
			}
			p=p->next;
		}
		if(p==NULL)
		{
			p=head2;
			while(p!=NULL)
			{
				if(p->id==id)
				{
					fflush(stdin);
					printf("�޸ĳɼ���ѧ����Ϣ ѧ��:%d ����:%s \n",p->id,p->name);
					printf("�ɼ�����Ϊ �ۺϳɼ�:%d ���ĳɼ�:%d \n",p->sum1,p->lun);
					printf("**ȷ���Ƿ���Ҫ�޸�: 0- ȡ�� ** 1- ȷ��\n");
					scanf("%d",&a);
					if(a==1)
					{
						printf("���������룬�ۺϳɼ������ĳɼ�:\n");
						scanf("%d%d",&p->sum1,&p->lun);
					}
				}
				p=p->next;
			}
		}
		printf("�Ƿ���Ҫ�޸ģ�0- ȡ�� **   1- ����\n");
		scanf("%d",&y);
	}
}
void q2()/*ɾ��ѧ���ɼ�*/
{
	int id,y=1,a;
	student *p;
	while(y)
	{
		fflush(stdin);
		printf("��������Ҫɾ����ѧ��ѧ��:");
		scanf("%d",&id);
		p=head1;
		while(p!=NULL)
		{
			if(p->id ==id)
			{
				printf("��Ҫɾ����ѧ�� ѧ��: %d ����: %s\n",p->id ,p->name );
				printf("**�Ƿ���Ҫɾ���ɼ�\n0- ȡ��   1- ��\n");
				scanf("%d",&a);
				if(a==1)
				{
					p->math =-1;
					p->eng =-1;
					p->C =-1;
				}
				break;
			}
			p=p->next ;
		}
		if(p==NULL)
		{
			p=head2;
			while(p!=NULL)
			{
				if(p->id =id)
				{
					printf("��Ҫɾ���ɼ���ѧ����Ϣ ѧ��: %d ����: %s \n",p->id ,p->name );
					printf("**�Ƿ���Ҫɾ���ɼ�\n0- ȡ��    1- ��\n");
					scanf("%d",&a);
					if(a==1)
					{
						p->sum1 =-1;
						p->lun =-1;
					}
					break;
				}
				p=p->next ;
			}
		}
		printf("�Ƿ���Ҫ����ɾ���ɼ�\n**0- ȡ��   1- ����\n");
		scanf("%d",&y);
	}
}
void q3()/*��ѧ�Ų�ѯ�ɼ�*/
{
	int id,y=1;
	student *p;
	while(y){
		fflush(stdin);
		printf("��������Ҫ��ѯ��ѧ��:");
		scanf("%d",&id);
		p=head1;
		while(p!=NULL)
		{
			if(p->id ==id)
			{
				printf("ѧ����Ϣ��\nѧ��: %d ����: %s",p->id ,p->name );
				printf("��ѧ: %d Ӣ��: %d C����: %d \n",p->math ,p->eng ,p->C );
				break;
			}
			p=p->next ;
		}
		if(p==NULL)
		{
			p=head2;
			while(p!=NULL)
			{
				if(p->id ==id )
				{
					printf("ѧ����Ϣ��\nѧ��:%d ����:%s ",p->id ,p->name );
					printf("�ۺ�:%d ����:%d \n",p->sum1 ,p->lun );
					break;
				}
				p=p->next ;
			}
		}
		printf("�Ƿ���Ҫ��ѯѧ����Ϣ\n**0- ȡ��   1- ��Ҫ\n");
		scanf("%d",&y);
	}
}
void q4()/*�����ܳɼ�*/
{	
	void q6();
	void school();
	student *p1,*p2;
	q6();
	school();
	p1=head1;
	p2=head2;
	while(p1!=NULL)
	{
		if((p1->math==-1)||(p1->eng==-1)||(p1->C ==-1))
			p1=p1->next ;
		else 
			p1->sum=p1->math +p1->eng+p1->C ;
		p1=p1->next ;
	}
	while(p2!=NULL)
	{
		if((p2->sum1 ==-1)||(p2->lun ==-1))
			p2=p2->next ;
		else 
			p2->sum =p2->sum1 +p2->lun ;
		p2=p2->next ;
	}
	printf("�������! ���Ե���ѯ�����鿴������Ϣ\n");
}
void q6()/*����༶����*/
{
	student *p1,*p2;
	int n;
	p1=head1;
	while(p1!=NULL)
	{
		n=1;
		p2=head1;
		while(p2!=NULL)
		{
			if(strcmp(p1->cla ,p2->cla )==0)
			{
				if(p1->sum <p2->sum ) n++;
			}
			p2=p2->next ;
		}
		p1->pm1 =n;
		p1=p1->next ;
	}
	if(p1==NULL)
	{
		p1=head2;
		while(p1!=NULL)
		{
			n=1;
			p2=head2;
			while(p2!=NULL)
			{
				if(strcmp(p1->cla ,p2->cla )==0)
				{
					if(p1->sum <p2->sum )
						n++;
				}
				p2=p2->next ;
			}
			p1->pm1 =n;
			p1=p1->next ;
		}
	}
}
void jiaohuan(student *p,student *q)/*�����������*/
{
	student temp,*pnext,*qnext;
	pnext=p->next ;
	qnext=q->next ;
	temp=*p;
	*p=*q;
	*q=temp;
	p->next =pnext;
	q->next =qnext;
}
void cla()/*ĳ������---������*/
{
	void a(char *classes);
	student *p,*q,*big;
	char classes[M];
	printf("��������Ҫ�鿴�İ༶:\n");
	scanf("%s",classes);
	for(p=head1;p!=NULL;p=p->next )
	{
		while(p!=NULL && strcmp(p->cla ,classes)!=0)
			p=p->next ;
		if(p==NULL) break;
		big=p;
		for(q=p->next ;q!=NULL;q=q->next )
		{
			while(q!=NULL && strcmp(q->cla,classes)!=0)
				q=q->next ;
			if(q==NULL) break;
			if(q->sum >big->sum ) big=q;
		}
		jiaohuan(p,big);
	}
	a(classes);
}
void a(char *classes)/*��ӡ�༶����*/
{
	void benhead();
	void showonestudent(student *p);
	student *p;
	p=head1;
	printf("��ʾ%s �༶������\n",classes);
	benhead();
	while(p!=NULL)
	{
		if(strcmp(p->cla,classes)==0)
			showonestudent(p);
		p=p->next ;
	}
	printf("\n");
}
void sch()/*ĳ������---�о���*/
{
	void jiaohuan(student *q,student *p);
	void a8(char *classes);
	student *p,*q,*big;
	char classes[M];
	printf("��������Ҫ�鿴�İ༶:\n");
	scanf("%s",classes);
	for(p=head2;p!=NULL;p=p->next )
	{
		while(p!=NULL && strcmp(p->cla ,classes)!=0)
			p=p->next ;
		if(p==NULL) break;
		big=p;
		for(q=p->next ;q!=NULL;q=q->next )
		{
			while(q!=NULL && strcmp(q->cla,classes)!=0)
				q=q->next ;
			if(q==NULL) break;
			if(q->sum >big->sum ) big=q;
		}
		jiaohuan(p,big);
	}
	a8(classes);
}
void a8(char *classes)/*��ӡ*/
{
	void yanhead();
	void show1(student *p);
	student *p;
	printf("��ʾ%s �༶������\n",classes);
	yanhead();
	p=head2;
	while(p!=NULL){
		if(strcmp(p->cla,classes)==0)
			show1(p);
		p=p->next ;
	}
}
void school()/*����ѧУ����*/
{
	student *p1,*p2;
	int n;
	p1=head1;
	while(p1!=NULL)
	{
		n=1;
		p2=head1;
		while(p2!=NULL)
		{
			if(p1->sum <p2->sum ) n++;
			p2=p2->next ;
		}
		if(p2==NULL){
			p2=head2;
			while(p2!=NULL){
				if(p1->sum <p2->sum ) n++;
				p2=p2->next;
			}
		}
		p1->pm2=n;
		p1=p1->next;
	}
	if(p1==NULL)
	{
		p1=head2;
		while(p1!=NULL)
		{
			n=1;
			p2=head2;
			while(p2!=NULL)
			{
				if(p1->sum <p2->sum ) n++;
				p2=p2->next ;
			}
			if(p2==NULL){
				p2=head1;
				while(p2!=NULL)
				{
				if(p1->sum <p2->sum ) n++;
				p2=p2->next ;
				}
			}
			p1->pm2 =n;
			p1=p1->next ;
		}
	}
}

void a1()/*����ѧ����Ϣ����---������*/
{
	student *p,*p1;
	void jiaohuan(student *p,student *q);
	void a3();
	p=head1;
	while(p!=NULL)
	{
		p1=p->next ;
		while(p1!=NULL)
		{
			if(p->sum <p1->sum)
				jiaohuan(p,p1);
			p1=p1->next ;
		}
		p=p->next ;
	}
	a3();
}
void a3()/*��ӡ������ѧ����Ϣ*/
{
	void benhead();
	void showonestudent(student *p);
	student *p;
	p=head1;
	printf("������������ѧ�����ܳɼ�����Ϊ��\n");
	benhead();
	while(p!=NULL)
	{
		showonestudent(p);
		p=p->next ;
	}
}
void a4()/*��ӡ�о�����Ϣ*/
{
	void yanhead();
	void show();
	student *p;
	p=head2;
	printf("�о���������ѧ�����ܳɼ�����Ϊ��\n");
	yanhead();
	while(p!=NULL)
	{
		show1(p);
		p=p->next ;
	}
}
void a6()/*��ӡ�о���������Ϣ*/
{
	student *p,*p1;
	void jiaohuan(student *p,student *q);
	void a4();
	p=head2;
	while(p!=NULL)
	{
		p1=p->next ;
		while(p1!=NULL)
		{
			if(p->sum <p1->sum)
				jiaohuan(p,p1);
			p1=p1->next ;
		}
		p=p->next ;
	}
	a4();
}
void getpage1(student *head,int page,int pagesize)/*��ҳ��ʾָ��ҳѧ������----������*/
{
	void benhead();
	void showonestudent(student *p);
	int nowi=0;
	int start=(page-1) *pagesize+1;
	int end=start +pagesize-1;
	student *p=head;
	benhead();
	while(p!=NULL)
	{
		nowi++;
		if(nowi>=start && nowi<=end)
			showonestudent(p);
		else if(nowi>end)
			break;
		p=p->next ;
	}
}
void getpage2(student *head,int page,int pagesize)/*��ҳ��ʾָ��ҳѧ������----�о���*/
{
	void yanhead();
	void show1(student *p);
	int nowi=0;
	int start=(page-1) *pagesize+1;
	int end=start +pagesize-1;
	student *p=head;
	yanhead();
	while(p!=NULL)
	{
		nowi++;
		if(nowi>=start && nowi<=end)
			show1(p);
		else if(nowi>end)
			break;
		p=p->next ;
	}
}
void showall()/*��ҳ��ʾָ��ҳѧ������---������*/
{
	void getpage1(student *head,int page,int pagesize);
	int menuitem;
	int page=1;
	int totalpage;
	int error;
	if(people==0)
	{
		printf("���������ѧ������!\n");
		return ;
	}
	if(people%PAGESIZE==0)
	{
		totalpage=people/PAGESIZE;
	}
	else {
		totalpage=people/PAGESIZE+1;
	}
	while(1)
	{
		fflush(stdin);
		if(people==0)
		{
			printf("��ǰ���κ�ѧ������\n");
			break;
		}
		printf("\n ��ǰ�Ǳ�������ҳ��%d ҳ�� �ܹ�%d ҳ\n",page,totalpage);
		printf("----------------------------------------------");
		printf("---------------------------------------------\n");
		getpage1(head1,page,PAGESIZE);/*������*/
		printf("\n---------------------------------------------");
		printf("----------------------------------------------\n");
		if(page==1 && totalpage==1)
		{
			break;
		}
		else if(page==1)
		{
			printf("��ҳ�˵�: 3- ��һҳ     4- βҳ   5- ����\n");
			printf("������˵���ţ�3-5��:");
			do{
				fflush(stdin);
				scanf("%d",&menuitem);
				switch(menuitem)
				{
				case 3: page++;error=0;break;
				case 4: page=totalpage;error=0;break;
				case 5: return ;
				default : error=1;
					printf("�˵���������������������˵����(3-5):");
					break;
				}
			}while(error);
		}
		else if(page==totalpage)
		{
			printf("��ҳ�˵�: 1- ��ҳ   2- ��һҳ   5- ����\n");
			printf("������˵����(1, 2, 5):");
			do{
				fflush(stdin);
				scanf("%d",&menuitem);
				switch(menuitem){
				case 1: page=1;error=0;break;
				case 2: page--;error=0;break;
				case 5: return;
				default: error=1;
					printf("�˵���������������������˵���ţ�1, 2, 5��:");
					break;
				}
			}while(error);
		}
		else {
			printf("��ҳ�˵�: 1- ��ҳ   2- ��һҳ   3- ��һҳ   4- βҳ   5- ����\n");
			printf("������˵���ţ�1-5��:");
			do{
				fflush(stdin);
				scanf("%d",&menuitem);
				switch(menuitem)
				{
				case 1: page=1;error=0;break;
				case 2: page--;error=0;break;
				case 3: page++;error=0;break;
				case 4: page=totalpage;break;
				case 5: return;
				default: error=1;
					printf("�˵���������������������˵����:");
					break;
				}
			}while(error);
		}
	}
}
void showall1()/*��ҳ��ʾָ��ҳѧ������---�о���*/
{
	void getpage2(student *head,int page,int pagesize);
	int menuitem;
	int page=1;
	int totalpage;
	int error;
	if(people==0)
	{
		printf("���������ѧ������!\n");
		return ;
	}
	if(people%PAGESIZE==0)
	{
		totalpage=people/PAGESIZE;
	}
	else {
		totalpage=people/PAGESIZE+1;
	}
	while(1)
	{
		fflush(stdin);
		if(people==0)
		{
			printf("��ǰ���κ�ѧ������\n");
			break;
		}
		printf("\n ��ǰ���о�����ҳ��%d ҳ�� �ܹ�%d ҳ\n",page,totalpage);
		printf("\n---------------------------------------------");
		printf("---------------------------------------------\n");
		getpage2(head2,page,PAGESIZE);
		printf("\n---------------------------------------------");
		printf("---------------------------------------------\n");
		if(page==1 && totalpage==1)
		{
			break;
		}
		else if(page==1)
		{
			printf("��ҳ�˵�: 3- ��һҳ     4- βҳ   5- ����\n");
			printf("������˵���ţ�3-5��:");
			do{
				fflush(stdin);
				scanf("%d",&menuitem);
				switch(menuitem)
				{
				case 3: page++;error=0;break;
				case 4: page=totalpage;error=0;break;
				case 5: return ;
				default : error=1;
					printf("�˵���������������������˵����(3-5):");
					break;
				}
			}while(error);
		}
		else if(page==totalpage)
		{
			printf("��ҳ�˵�: 1- ��ҳ   2- ��һҳ   5- ����\n");
			printf("������˵����(1, 2, 5):");
			do{
				fflush(stdin);
				scanf("%d",&menuitem);
				switch(menuitem){
				case 1: page=1;error=0;break;
				case 2: page--;error=0;break;
				case 5: return;
				default: error=1;
					printf("�˵���������������������˵���ţ�1, 2, 5��:");
					break;
				}
			}while(error);
		}
		else {
			printf("��ҳ�˵�: 1- ��ҳ   2- ��һҳ   3- ��һҳ   4- βҳ   5- ����\n");
			printf("������˵���ţ�1-5��:");
			do{
				fflush(stdin);
				scanf("%d",&menuitem);
				switch(menuitem)
				{
				case 1: page=1;error=0;break;
				case 2: page--;error=0;break;
				case 3: page++;error=0;break;
				case 4: page=totalpage;break;
				case 5: return;
				default: error=1;
					printf("�˵���������������������˵����:");
					break;
				}
			}while(error);
		}
	}
}
void a5()/*���༶��ʾѧ����Ϣ---������*/
{
	void benhead();
	void showonestudent(student *p);
	student *p;
	char classes[M];
	p=head1;
	printf("��������Ҫ��ʾ�İ༶:\n");
	scanf("%s",classes);
	benhead();
	while(p!=NULL)
	{
		if(strcmp(p->cla,classes)==0)
			showonestudent(p);
		p=p->next;
	}
	printf("\n");
}
void b1()/*���༶��ʾѧ����Ϣ---�о���*/
{
	void yanhead();
	void show1(student *p);
	student *p;
	char classes[M];
	p=head2;
	printf("��������Ҫ��ʾ�İ༶:\n");
	scanf("%s",classes);
	yanhead();
	while(p!=NULL)
	{
		if(strcmp(p->cla,classes)==0)
			show1(p);
		p=p->next;
	}
	printf("\n");
}
void b2()/*��ѧ�Ż�������ѯѧ��*/
{
	void showonestudent(student *p);
	void benhead();
	void yanhead();
	void show1(student *p);
	int a,id;
	char b[M];
	int flag=1;
	student *p1,*p2;
	p1=head1;
	p2=head2;
	fflush(stdin);
	printf("��ѡ���ѯ��ʽ��**0- ѧ�Ų�ѯ     1- ������ѯ\n");
	scanf("%d",&a);
	while(flag!=0){
		if(a==0)
		{
			fflush(stdin);
			printf("������ѧ����Ϣ:");
			scanf("%d",&id);
			while(p1!=NULL)
			{
				if(p1->id==id)
				{
					benhead();
					showonestudent(p1);
					break;
				}
				p1=p1->next;
			}
			if(p1==NULL)
			{
				while(p2!=NULL)
				{
					if(p2->id==id)
					{
						yanhead();
						show1(p2);
						break;
					}
					p2=p2->next;
				}
			}
			flag=0;
		}
		else if(a==1)
		{
			fflush(stdin);
			printf("��������Ҫ��ѯ��ѧ������:");
			scanf("%s",b);
			while(p1!=NULL)
			{
				if(strcmp(p1->name,b)==0)
				{
					benhead();
					showonestudent(p1);
					break;
				}	
				p1=p1->next;
			}
			if(p1==NULL)
			{
				while(p2!=NULL)
				{
					if(strcmp(p2->name,b)==0)
					{
						yanhead();
						show1(p2);
						break;
					}
					p2=p2->next;
				}
			}
			flag=0;
		}
		else {
			printf("ѡ�������������������:");
			scanf("%d",&a);
			flag=1;
		}
	}
}
void b3(char *classes)/*��ѯĳ����ĳ�ſγɼ�������ѧ����Ϣ---������*/
{
	void showonestudent(student *p);
	void benhead();
	student *p;
	int a,n=0;
	fflush(stdin);
	printf("��ѡ����Ҫ��ѯ�Ŀγ�:1- ��ѧ  2- Ӣ��  3- C����  0- �˳�\n");
	scanf("%d",&a);
	p=head1;
	while(p!=NULL)
	{
		if(strcmp(p->cla,classes)==0)
		{
			switch(a)
			{
			case 1: 
				if(p->math <60 && p->math !=-1)
				{
					n++;
					if(n==1){ 
						benhead();
						showonestudent(p);
					}
					else showonestudent(p);
				}
				break;
			case 2:
				if(p->eng<60 && p->eng !=-1)
				{
					n++;
					if(n==1){ 
						benhead();
						showonestudent(p);
					}
					else showonestudent(p);
				}
				break;
			case 3:
				if(p->C<60 && p->C!=-1)
				{
					n++;
					if(n==1){ 
						benhead();
						showonestudent(p);
					}
					else showonestudent(p);
				}
				break;
			default:
				printf("�γ̴����������!\n");
				break;
			}
		}
		p=p->next ;
	}
	if(n==0) printf("�ð༶����ؿγ�û�в������ѧ��\n");
}

void b4(char *classes)/*��ѯĳ����ĳ�ſγɼ�������ѧ����Ϣ---�о���*/
{
	void yanhead();
	void show1(student *p);
	student *p;
	int a,n=0;
	fflush(stdin);
	printf("��������Ҫ��ѯ�ĳɼ�: 1- �ۺϳɼ�  2- ���ĳɼ�  0- �˳�\n");
	scanf("%d",&a);
	if(a!=0)
	{
		p=head2;
		while(p!=NULL)
		{
			if(strcmp(p->cla,classes)==0)
			{
				switch(a){
				case 1:
					if(p->sum1<60 && p->sum1!=-1)
					{
						n++;
						if(n==1){
							yanhead();
							show1(p);
						}
						else show1(p);
					}
					break;
				case 2:
					if(p->lun<60 && p->lun!=-1)
					{
						n++;
						if(n==1){
							yanhead();
							show1(p);
						}
						else show1(p);
					}
					break;
				default:
					printf("ѡ���������!\n");
					break;
				}
			}
			p=p->next ;
		}
	}
	if(n==0) printf("�ð༶����ؿγ�û�в������ѧ��\n");
}

void h1()/*ͳ��ÿ�����ƽ���ɼ�---������*/
{
	student *p;
	char k[M][M];
	int i=0,a,b,c=0,n=0;
	int sum[M]={0},people[M]={0};
	p=head1;
	strcpy(k[0],p->cla);
	while(p!=NULL)
	{
		
		if(strcmp(p->cla,k[i])!=0 && strcmp(p->cla,k[n])!=0)
		{
			n=i;
			i++;
			strcpy(k[i],p->cla);
		}
		p=p->next;
	}
	b=i;
	printf("��ѡ����Ҫ��ѯ�Ŀγ̴���: 1- ��ѧ  2- Ӣ��  3- C����   0- �˳�\n");
	scanf("%d",&a);
	if(a<0 || a>4)
	{
		printf("�γ̴���ѡ���������������ѡ��:\n");
		scanf("%d",&a);
	}
	if(a!=0)
	{
		i=0;
		switch(a)
		{
		case 1: 
			while(c<=b)
			{
				p=head1;
				while(p!=NULL)
				{
					if(strcmp(p->cla,k[i])==0 && p->math!=-1)
					{
						sum[c]=sum[c]+p->math;
						people[c]=people[c]+1;
					}
					p=p->next;
				}
				i++;
				c++;
			}
			break;
		case 2:
			while(c<=b)
			{
				p=head1;
				while(p!=NULL)
				{
					if(strcmp(p->cla,k[i])==0 && p->eng!=-1)
					{
						sum[c]=sum[c]+p->eng;
						people[c]=people[c]+1;
					}
					p=p->next;
				}
				i++; c++;
			}
			break;
		case 3:
			while(c<=b)
			{
				p=head1;
				while(p!=NULL)
				{
					if(strcmp(p->cla,k[i])==0 && p->C!=-1)
					{
						sum[c]=sum[c]+p->C;
						people[c]=people[c]+1;
					}
					p=p->next;
				}
				i++; c++;
			}
			break;
		}
		printf("��Ҫ��ѯ�Ŀ�Ŀ�� ");
		switch(a){
		case 1: printf("��ѧ\n");break;
		case 2: printf("Ӣ��\n");break;
		case 3: printf("C����\n");break;
		}
		for(i=0,c=0;c<=b;i++,c++)
		{
			printf("%s ��ƽ���ɼ�Ϊ:%d \n",k[i],sum[c]/people[c]);
		}
	}
}
void h3()/*ͳ�ƿγ�ĳ��ƽ���ɼ�---�о���*/
{
	student *p;
	char k[M][M];
	int i=0,b=0,a,t=0;
	int m,sum[M]={0},people[M]={0};
	p=head2;
	strcpy(k[0],p->cla);
	while(p!=NULL)
	{
		if(strcmp(p->cla,k[i])!=0 && strcmp(p->cla,k[t])!=0)
		{
			t=i;
			i++;
			strcpy(k[i],p->cla);
		}
		p=p->next;
	}
	m=i;
	printf("��ѡ����Ҫ��ѯ�ĳɼ�����:1- �ۺϳɼ�   2- ���ĳɼ�   0- �˳�\n");
	scanf("%d",&a);
	if(a<0 || a>4){
		printf("ѡ�������������������:");
		scanf("%d",&a);
	}
	if(a!=0)
	{
		i=0;
		switch(a){
		case 1:
			while(b<=m)
			{
				p=head2;
				while(p!=NULL)
				{
					if(strcmp(p->cla,k[i])==0 && p->sum1!=-1)
					{
						sum[b]=sum[b]+p->sum1;
						people[b]=people[b]+1;
					}
					p=p->next;
				}
				b++; i++;
			}
			break;
		case 2:
			while(b<=m){
				p=head2;
				while(p!=NULL)
				{
					if(strcmp(p->cla,k[i])==0 && p->lun!=-1)
					{
						sum[b]=sum[b]+p->lun;
						people[b]=people[b]+1;
					}
					p=p->next;
				}
				b++; i++;
			}
			break;
		}
		printf("��Ҫ��ѯ����");
		switch(a){
		case 1: printf("�ۺϳɼ�:\n");break;
		case 2: printf("���ĳɼ�:\n");break;
		}
		for(i=0,b=0;b<=m;i++,b++)
		{
			printf("%s ���ƽ���ɼ�Ϊ %d\n",k[i],sum[b]/people[b]);
		}
	}
}
void h4(char *classes)/*ͳ��ĳ����ĳ�Ƴɼ��ȼ�����---������*/
{
	student *p;
	int a;
	int m1=0,m2=0,m3=0,m4=0,m5=0;
	int find=0;
	p=head1;
	while(p!=NULL)
	{
		if(strcmp(p->cla,classes)==0)
			find=1;
		p=p->next;
	}
	if(find==0) printf("��û�д˰༶����!\n");
	else{
		printf("��ѡ��γ̴���:1- ��ѧ   2- Ӣ��   3- C����   0- �˳�\n");
		scanf("%d",&a);
		if(a<0 || a>4)
		{
			printf("ѡ�������������������:");
			scanf("%d",&a);
		}
		if(a!=0)
		{
			p=head1;
			switch(a){
			case 1: 
				while(p!=NULL){
					if(strcmp(p->cla,classes)==0 && p->math!=-1)
					{
						if(p->math>=90) m1++;
						else if(p->math>=80) m2++;
						else if(p->math>=70) m3++;
						else if(p->math>=60) m4++;
						else m5++;
					}
					p=p->next;
				}
				break;
			case 2:
				while(p!=NULL){
					if(strcmp(p->cla,classes)==0 && p->eng!=-1)
					{
						if(p->eng>=90) m1++;
						else if(p->eng>=80) m2++;
						else if(p->eng>=70) m3++;
						else if(p->eng>=60) m4++;
						else m5++;
					}
					p=p->next;
				}
				break;
			case 3:
				while(p!=NULL){
					if(strcmp(p->cla,classes)==0 && p->C!=-1)
					{
						if(p->C >=90) m1++;
						else if(p->C >=80) m2++;
						else if(p->C >=70) m3++;
						else if(p->C >=60) m4++;
						else m5++;
					}
					p=p->next;
				}
				break;
			}
		switch(a){
		case 1:printf("%s ����ѧ�ȼ��ֲ����£�\n",classes);break;
		case 2:printf("%s ��Ӣ��ȼ��ֲ����£�\n",classes);break;
		case 3:printf("%s ��C���Եȼ��ֲ����£�\n",classes);break;
		}
		printf("��----%d ��\n",m1);
		printf("��----%d ��\n",m2);
		printf("��----%d ��\n",m3);
		printf("����----%d ��\n",m4);
		printf("������----%d ��\n",m5);
		}
	}
}
void h5(char *classes)/*ͳ��ĳ����ĳ�Ƴɼ��ȼ�����---�о���*/
{
	student *p;
	int a;
	int m1=0,m2=0,m3=0,m4=0,m5=0;
	int find=0;
	p=head2;
	while(p!=NULL)
	{
		if(strcmp(p->cla,classes)==0)
			find=1;
		p=p->next;
	}
	if(find==0) printf("��û�д˰༶����!\n");
	else{
		printf("��ѡ���ѯ�ɼ�����:1- �ۺϳɼ�   2- ���ĳɼ�   0- �˳�\n");
		scanf("%d",&a);
		if(a<0 || a>3)
		{
			printf("ѡ�������������������:");
			scanf("%d",&a);
		}
		if(a!=0)
		{
			p=head2;
			switch(a){
			case 1: 
				while(p!=NULL){
					if(strcmp(p->cla,classes)==0 && p->sum1!=-1)
					{
						if(p->sum1>=90) m1++;
						else if(p->sum1>=80) m2++;
						else if(p->sum1>=70) m3++;
						else if(p->sum1>=60) m4++;
						else m5++;
					}
					p=p->next;
				}
				break;
			case 2:
				while(p!=NULL){
					if(strcmp(p->cla,classes)==0 && p->lun!=-1)
					{
						if(p->lun>=90) m1++;
						else if(p->lun>=80) m2++;
						else if(p->lun>=70) m3++;
						else if(p->lun>=60) m4++;
						else m5++;
					}
					p=p->next;
				}
				break;
			}
		switch(a){
		case 1:printf("%s ���ۺϳɼ��ȼ��ֲ����£�\n",classes);break;
		case 2:printf("%s �����ĳɼ��ȼ��ֲ����£�\n",classes);break;
		}
		printf("��----%d ��\n",m1);
		printf("��----%d ��\n",m2);
		printf("��----%d ��\n",m3);
		printf("����----%d ��\n",m4);
		printf("������----%d ��\n",m5);
		}
	}
}
	
int main()
{
	void student1();
	void search();
	void sort();
	void statis();
	int menuitem;
	int a;
	people=p2();
	if(people==-1){
		printf("��ϵͳ�������ݣ�������洢����\n");
		printf("��ѡ��洢��Ϣ���1- ������   2- �о���\n");
		scanf("%d",&a);
		if(a==1) add1();
		else if(a==2) add2();
		p1();
	}
	while(1){
		do{
			fflush(stdin);
			printf("                    ���˵�\n");
			printf("========================================================\n");
			printf("|   1- ѧ������                       2- ��ѯ����      |\n");
			printf("|   3- �������                       4- ͳ�ƹ���      |\n");
			printf("|   5- ��    ��                                        |\n");
			printf("========================================================\n");
			printf("    ������˵����(1--5):");
			scanf("%d",&menuitem);
			if(menuitem>5 || menuitem<1)
				printf("�˵���������������������˵����(1--5):\n");
			else break;
		}while(1);
		switch(menuitem){
		case 1:student1();printf("\n");break;
		case 2:search();printf("\n");break;
		case 3:sort();printf("\n");break;
		case 4:statis();printf("\n");break;
		case 5:p1();printf("ллʹ��!\n\n");return 0;
		}
	}
}
void student1()/*ѧ������*/
{
	int menuitem;
	while(1){
		do{
			fflush(stdin);
			printf("              ѧ������˵�\n");
			printf("=========================================================\n");
			printf("| 1- ������������Ϣ¼��	2- �о���������Ϣ¼��		|\n");
			printf("| 3- ������Ϣ�޸�	4- ������Ϣɾ��			|\n");
			printf("| 5- ������Ϣ��ѯ	6- �ɼ�¼��			|\n");
			printf("| 7- �ɼ��޸�		8- �ɼ�ɾ��			|\n");
			printf("| 9- �ɼ���ѯ		10- �����ܳɼ�������		|\n");
			printf("|		11- �˳�				|\n");
			printf("=========================================================\n");
			printf("������˵����(1-11):");
			scanf("%d",&menuitem);
			if(menuitem>11 || menuitem<1)
				printf("�˵���������������������˵����(1-11):\n\n");
			else break;
		}while(1);
		if(menuitem<11 && menuitem>=1){
			switch(menuitem)
			{
			case 1:add1();printf("\n");break;
			case 2:add2();printf("\n");break;
			case 3:p3()	 ;printf("\n");break;
			case 4:p4()	 ;printf("\n");break;
			case 5:p5()  ;printf("\n");break;
			case 6:p6()  ;printf("\n");break;
			case 7:q1()	 ;printf("\n");break;
			case 8:q2()	 ;printf("\n");break;
			case 9:q3()  ;printf("\n");break;
			case 10:q4() ;printf("\n");break;
			}
		}
		else if(menuitem==11) break;
	}
}
void search()/*��ѯ����*/
{
	int menuitem;
	char classes[M];
	while(1){
		do{
			fflush(stdin);
			printf("			��ѯ�������\n");
			printf("=================================================================\n");
			printf("|  1- ��������ҳ��ʾȫ��ѧ��	2- ��������ʾĳ��ѧ����Ϣ 	| \n");
			printf("|  3- ��������ѧ�Ż�������ѯ	4- ��������ѯĳ���Ŀ��������Ϣ	|\n");
			printf("|  5- �о�����ҳ��ʾȫ��ѧ��	6- �о�����ʾĳ��ѧ����Ϣ	| \n");
			printf("|  7- �о�����ѧ�Ż�������ѯ	8- �о�����ѯĳ���Ŀ��������Ϣ	|\n");
			printf("|			9- �˳�					|\n");
			printf("=================================================================\n");
			printf("������˵����(1-9):");
			scanf("%d",&menuitem);
			if(menuitem>9 || menuitem<1)
				printf("�˵���������������������˵����(1-9):\n\n");
			else break;
		}while(1);
		if(menuitem<9 && menuitem>=1){
			switch(menuitem){
			case 1:showall();printf("\n");break;
			case 2:a5()		;printf("\n");break;
			case 3:b2()		;printf("\n");break;
			case 4:
				printf("��������Ҫ��ѯ�İ༶:\n");
				scanf("%s",classes);
				b3(classes);
				printf("\n");
				break;
			case 5:showall1();printf("\n");break;
			case 6:b1()		 ;printf("\n");break;
			case 7:b2()		 ;printf("\n");break;
			case 8:
				printf("��������Ҫ��ѯ�İ༶:\n");
				scanf("%s",classes);
				b4(classes);
				printf("\n");
				break;
			}
		}
		else if(menuitem==9) break;
	}
}
void sort()/*�������*/
{
	int menuitem;
	while(1){
		do{
			fflush(stdin);
			printf("                 �������˵�\n");
			printf("========================================================\n");
			printf("|   1- ����ѧ�����ܳɼ�����(����)(������);	       |\n");
			printf("|   2- ĳ���ఴ�ܳɼ�(����)(������);		       |\n");
			printf("|   3- ����ѧ�����ܳɼ�����(����)(�о���);	       |\n");
			printf("|   4- ĳ���ఴ�ܳɼ�����(����)(�о���);	       |\n");
			printf("|   5- ��    ��                                        |\n");
			printf("========================================================\n");
			printf("    ������˵����(1--5):");
			scanf("%d",&menuitem);
			if(menuitem>5 || menuitem<1)
				printf("�˵���������������������˵����(1--5):\n");  
			else break;
		}while(1);
		if(menuitem>=1 && menuitem<5){
			switch(menuitem){
			case 1:a1()   ;printf("\n");break;
			case 2:cla()  ;printf("\n");break;
			case 3:a6()   ;printf("\n");break;
			case 4:sch()  ;printf("\n");break;
			}
		}
		else if(menuitem==5) break;
	}
}
void statis()/*ͳ�ƹ���*/
{
	int menuitem;
	char classes[M];
	while(1){
		do{
			fflush(stdin);
			printf("          ͳ�ƹ���˵�\n");
			printf("=========================================================\n");
			printf("|   1- ͳ��ĳ�ſ�ÿ�����ƽ���ɼ�(������)		|\n");
			printf("|   2- ͳ��ĳ����ĳ�ſβ�ͬ�ȼ�����(������)		|\n");
			printf("|   3- ͳ��ĳ�ſ�ÿ�����ƽ���ɼ�(�о���)		|\n");
			printf("|   4- ͳ��ĳ����ĳ�ſβ�ͬ�ȼ�����(�о���)		|\n");
			printf("|   5- ��    ��                                         |\n");
			printf("=========================================================\n");
			printf("    ������˵����(1--5):");
			scanf("%d",&menuitem);
			if(menuitem>5 || menuitem<1)
				printf("�˵���������������������˵����(1--5):\n");
			else break;
		}while(1);
		if(menuitem!=5){
			switch(menuitem){
			case 1:h1()		   ;printf("\n");break;
			case 2:
				printf("��������Ҫ�鿴�İ༶:\n");
				scanf("%s",classes);
				h4(classes) ;
				printf("\n");
				break;
			case 3:h3()        ;printf("\n");break;
			case 4:
				printf("��������Ҫ�鿴�İ༶:\n");
				scanf("%s",classes);
				h5(classes) ;
				printf("\n");
				break;
			}
		}
		else if(menuitem==5) break;
	}
}



		




