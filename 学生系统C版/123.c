#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define M 50
#define PAGESIZE 10 /*控制每页显示的学生数据条数*/
enum xb{boy=1,g};
#define A1 "a1.dat"/*读取文件地址*/
#define A2 "a2.dat"

typedef struct node{
        int id;/*学号*/
        char name[M];/*姓名*/
        int gender;/*性别,采用枚举类型*/
        char zye[M];/*专业*/ 
        char cla[M];/*班级*/
        int math,eng,C,sum;/*数学，英语，c语言，总成绩*/
        int pm1,pm2;/*pm1班级排名*/
        char fang[M];/*研究方向*/
        char dao[M];/*导师*/
        int sum1,lun;/*课程综合成绩，论文成绩*/ 
        struct node *next;/*指向下一个链表*/ 
        }student;
int ID=0;
student *head1=NULL,*head2=NULL;/*head1是本科生，*/
int people=0;
int change=0;

void addnode(student **headp,student *stu1)/*创建链表*/
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
void add1()/*输入本科生*/
{
	student *p;
	void addnode(student **headp,student *stu1);
	int x;
	printf("请输入本科生信息包括姓名不为空，性别不为空，专业不为空，班级不为空;\n");
	printf("注意性别输入（1.男性，2.女性）.\n");
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
		printf("是否继续输入（0为结束标志）:");
		scanf("%d",&x);
	}while(x!=0);	
}
void add2()/*输入研究生*/
{
	student *p;
	void addnode(student **headp,student *stu2);
	int x;
	printf("输入研究生信息包括姓名不为空，性别不为空，专业不为空，班级不为空\n");
	printf("				  研究方向不为空，导师不为空.\n");
	printf("注意性别输入（1.男性，2.女性）.\n");
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
		printf("是否继续输入（0为结束标志）:");
		scanf("%d",&x);
	}while(x!=0);
}
void p1()/*将链表数据存储到文件*/
{
	FILE *fp1,*fp2;
	int nodenumder=0;
	student *p1=NULL,*p2=NULL;
	p1=head1;
	p2=head2;
	if((fp1=fopen(A1,"wb"))==NULL)
	{
		printf("无法打开数据文件!\n");
		return ;
	}
	printf("正在存储数据，请稍等......\n");
	while(p1!=NULL)
	{
		if(fwrite(p1,sizeof(student),1,fp1)==1)
			nodenumder++;
		else 
			printf("学号：%d 姓名：%s 的数据保存失败！\n",p1->id,p1->name);
		p1=p1->next;
	}
	fclose(fp1);
	if((fp2=fopen(A2,"wb"))==NULL)
	{
		printf("无法打开数据文件!");
		return ;
	}
	while(p2!=NULL)
	{
		if(fwrite(p2,sizeof(student),1,fp2)==1)
			nodenumder++;
		else
			printf("学号：%d 姓名：%s 的数据保存失败\n",p2->id,p2->name);
		p2=p2->next;
	}
	fclose(fp2);
	printf("数据保存结束，共保存了%d 名学生数据!\n",nodenumder);
}
int p2()/*将文件读取到链表中*/
{
	FILE *fp1,*fp2;
	int flag=0,flag1=1;
	int nodenumder=0;
	student *p1,*p2;
	if((fp1=fopen(A1,"rb"))==NULL )
	{
		printf("文件无法打开！\n");
		flag1=0;
	}
	if((fp2=fopen(A2,"rb"))==NULL)
	{
		printf("文件无法打开！\n");
		flag=1;
	}
	if(flag1==0 && flag==1) return -1;
	printf("正在读取文件数据...\n");
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
			printf("读取结束，共读取%d 名学生信息!\n",nodenumder);
			system("pause");
			return nodenumder;
		}
	}while(1);
}
int checkdata(student *p)/*检查输入函数,,判断是否为空*/
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
void p3()/*修改学生基本信息*/
{
	int id;
	student *p;
	fflush(stdin);
	printf("请输入要修改的学生学号：\n");
	scanf("%d",&id);
	p=head1;
	while(p!=NULL)
	{
		if(p->id==id)
		{
			printf("修改前的数据：%s,%d,%s,%s\n",p->name,p->gender,p->zye,p->cla);
			do{
				fflush(stdin);
				printf("修改提醒：姓名不为空，性别不为空，专业不为空，班级不为空！\n");
				printf("性别输入（1.男性  2.女性）;\n");
				printf("请依次输入姓名，性别选项，专业，班级：\n");
				scanf("%s%d%s%s",p->name,&p->gender,p->zye,p->cla);
			}while(checkdata(p)==0);
			change=1;
			printf("修改成功！\n");
			printf("修改后数据为:%s,%d,%s,%s\n",p->name,p->gender,p->zye,p->cla);
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
				printf("修改前数据:%s,%d,%s,%s,%s,%s\n",p->name,p->gender,p->zye,p->cla,p->fang,p->dao);
				do{
					fflush(stdin);
					printf("修改提醒：姓名不为空，性别不为空，专业不为空，班级不为空！\n");
					printf("		  研究方向不为空，导师不为空。\n");
					printf("性别输入（1.男性  2.女性）;\n");
					printf("请依次输入姓名，性别选项，专业，班级，研究方向，导师：\n");
					scanf("%s%d%s%s%s%s",p->name,&p->gender,p->zye,p->cla,p->fang,p->dao);
				}while(checkdata(p)==0);
				change=1;
				printf("修改成功!\n");
				printf("修改后数据:%s,%d,%s,%s,%s,%s\n",p->name,p->gender,p->zye,p->cla,p->fang,p->dao);
				break;
			}
			p=p->next;
		}
	}
}
void benhead()/*显示学生类型属性*/
{
	printf("%2s%10s%6s%20s%20s","学号","姓名","性别","专业","班级");
	printf("%6s%6s%6s%6s%8s%8s","高数","英语","C语言","总成绩","班排名","校排名");
}
void showonestudent(student *p)/*输入学生信息*/
{
	printf("\n%4d%10s",p->id,p->name);
	switch(p->gender){
	case 1: printf(" 男生 ");break;
	case 2: printf(" 女生 ");break;
	}
	printf("%20s%20s",p->zye,p->cla);
	printf("%6d%6d%6d%6d%8d%8d",p->math,p->eng,p->C,p->sum,p->pm1,p->pm2);
}
void yanhead()/*研究生类型属性*/
{
	printf("%2s%10s%6s%20s%20s%20s%10s","学号","姓名","性别","专业","班级","研究方向","导师");
	printf("%6s%6s%6s%8s%8s","综合成绩","论文成绩","总成绩","班排名","校排名");
}
void show1(student *p)/*研究生*/
{
	printf("\n%4d%10s",p->id,p->name);
	switch(p->gender){
	case 1: printf(" 男生 ");break;
	case 2: printf(" 女生 ");break;
	}
	printf("%20s%20s%20s%10s",p->zye,p->cla,p->fang,p->dao);
	printf("%6d%6d%6d%8d%8d",p->sum1,p->lun,p->sum,p->pm1,p->pm2);
}
void p4()/*根据学号删除学生*/
{
	student *p=head1,*q;
	student *m=head2,*n;
	int id; 
	printf("请输入要删除的学号:");
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
		printf("查找不到该学生!");
	}
	else{
		q->next=p->next;
		free(p);
		printf("删除完毕！\n"); 
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
			printf("查找不到该学生!");
		}
		else{
			n->next=m->next;
			free(m);
		} 
	}
}
void p5()/*按照学号查询信息*/
{
	void showonestudent(student *p);
	void show1(student *p);
	void benhead();
	void yanhead();
	int id,n=0;
	int flag=1;
	student *p;
	fflush(stdin);
	printf("请输入要查询信息的学生学号:");
	scanf("%d",&id);
	if(id<=0) printf("无该学生信息\n");
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
	if(flag!=0) printf("无该学生信息!");
}
void p6()/*学生成绩输入*/
{
	void math(student *p);
	void eng(student *p);
	void C(student *p);
	void sum1(student *p);
	void lun(student *p);
	int id,a,y=1;
	student *p;
	fflush(stdin);
	printf("请输入要输入的学生成绩的学号：\n");
	scanf("%d",&id);
	while(y){
		p=head1;
		while(p!=NULL)
		{
			if(p->id==id)
			{
				fflush(stdin);
				printf("待输入的学生是本科生信息\n学号: %d 姓名: %s \n",p->id,p->name);
				printf("选择需要输入的学科: 1- 数学   2- 英语  3- C语言\n");
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
					printf("待输入的学生是研究生信息\n学号:%d 姓名:%s\n",p->id,p->name);
					printf("选择需要输入的成绩类型: 1- 综合成绩   2- 论文成绩\n");
					scanf("%d",&a);
					switch(a){
					case 1: sum1(p);break;
					case 2: lun(p);break;
					}
				}
				p=p->next;
			}
		}
		printf("是否继续输入该学生成绩：0- 取消    1- 继续\n");
		scanf("%d",&y);
	}
}
void math(student *p)
{
	int a;
	printf("请输入该学生的数学成绩:");
	scanf("%d",&a);
	if(a>100 || a<0){
		printf("成绩输入错误!\n请重新输入:");
		scanf("%d",&a);
	}
	p->math=a;
}
void eng(student *p)
{
	int a;
	printf("请输入该学生的英语成绩:");
	scanf("%d",&a);
	if(a>100 || a<0)
	{
		printf("成绩输入错误\n请重新输入:");
		scanf("%d",&a);
	}
	p->eng=a;
}
void C(student *p)
{
	int a;
	printf("请输入该学生的C语言成绩:");
	scanf("%d",&a);
	if(a>100 || a<0)
	{
		printf("成绩输入错误\n请重新输入:");
		scanf("%d",&a);
	}
	p->C=a;
}
void sum1(student *p)
{
	int a;
	printf("请输入该学生的综合成绩:");
	scanf("%d",&a);
	if(a>100 || a<0)
	{
		printf("成绩输入错误\n请重新输入:");
		scanf("%d",&a);
	}
	p->sum1=a;
}
void lun(student *p)
{
	int a;
	printf("请输入该学生的论文成绩:");
	scanf("%d",&a);
	if(a>100 || a<0)
	{
		printf("成绩输入错误\n请重新输入:");
		scanf("%d",&a);
	}
	p->lun=a;
}
void q1()/*修改学生成绩*/
{
	int id,y=1,a;
	student *p;
	while(y)
	{
		fflush(stdin);
		printf("请输入要修改的学生学号:");
		scanf("%d",&id);
		p=head1;
		while(p!=NULL)
		{
			if(p->id==id)
			{
				fflush(stdin);
				printf("修改成绩的学生 学号：%d 姓名: %s\n",p->id,p->name);
				printf("成绩数据为 数学: %d 英语: %d C语言: %d\n",p->math,p->eng,p->C);
				printf("**确认是否需要修改: 0- 取消 ** 1- 确认\n");
				scanf("%d",&a);
				if(a==1)
				{
					printf("请依次输入学生成绩,数学，英语C，语言：\n");
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
					printf("修改成绩的学生信息 学号:%d 姓名:%s \n",p->id,p->name);
					printf("成绩数据为 综合成绩:%d 论文成绩:%d \n",p->sum1,p->lun);
					printf("**确认是否需要修改: 0- 取消 ** 1- 确认\n");
					scanf("%d",&a);
					if(a==1)
					{
						printf("请依次输入，综合成绩，论文成绩:\n");
						scanf("%d%d",&p->sum1,&p->lun);
					}
				}
				p=p->next;
			}
		}
		printf("是否还需要修改：0- 取消 **   1- 继续\n");
		scanf("%d",&y);
	}
}
void q2()/*删除学生成绩*/
{
	int id,y=1,a;
	student *p;
	while(y)
	{
		fflush(stdin);
		printf("请输入需要删除的学生学号:");
		scanf("%d",&id);
		p=head1;
		while(p!=NULL)
		{
			if(p->id ==id)
			{
				printf("需要删除的学生 学号: %d 姓名: %s\n",p->id ,p->name );
				printf("**是否需要删除成绩\n0- 取消   1- 是\n");
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
					printf("需要删除成绩的学生信息 学号: %d 姓名: %s \n",p->id ,p->name );
					printf("**是否需要删除成绩\n0- 取消    1- 是\n");
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
		printf("是否需要继续删除成绩\n**0- 取消   1- 继续\n");
		scanf("%d",&y);
	}
}
void q3()/*按学号查询成绩*/
{
	int id,y=1;
	student *p;
	while(y){
		fflush(stdin);
		printf("请输入需要查询的学号:");
		scanf("%d",&id);
		p=head1;
		while(p!=NULL)
		{
			if(p->id ==id)
			{
				printf("学生信息：\n学号: %d 姓名: %s",p->id ,p->name );
				printf("数学: %d 英语: %d C语言: %d \n",p->math ,p->eng ,p->C );
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
					printf("学生信息：\n学号:%d 姓名:%s ",p->id ,p->name );
					printf("综合:%d 论文:%d \n",p->sum1 ,p->lun );
					break;
				}
				p=p->next ;
			}
		}
		printf("是否还需要查询学生信息\n**0- 取消   1- 需要\n");
		scanf("%d",&y);
	}
}
void q4()/*计算总成绩*/
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
	printf("计算完成! 可以到查询管理处查看排名信息\n");
}
void q6()/*计算班级排名*/
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
void jiaohuan(student *p,student *q)/*交换结点数据*/
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
void cla()/*某班排序---本科生*/
{
	void a(char *classes);
	student *p,*q,*big;
	char classes[M];
	printf("请输入需要查看的班级:\n");
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
void a(char *classes)/*打印班级数据*/
{
	void benhead();
	void showonestudent(student *p);
	student *p;
	p=head1;
	printf("显示%s 班级排名：\n",classes);
	benhead();
	while(p!=NULL)
	{
		if(strcmp(p->cla,classes)==0)
			showonestudent(p);
		p=p->next ;
	}
	printf("\n");
}
void sch()/*某班排序---研究生*/
{
	void jiaohuan(student *q,student *p);
	void a8(char *classes);
	student *p,*q,*big;
	char classes[M];
	printf("请输入需要查看的班级:\n");
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
void a8(char *classes)/*打印*/
{
	void yanhead();
	void show1(student *p);
	student *p;
	printf("显示%s 班级排名：\n",classes);
	yanhead();
	p=head2;
	while(p!=NULL){
		if(strcmp(p->cla,classes)==0)
			show1(p);
		p=p->next ;
	}
}
void school()/*计算学校排名*/
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

void a1()/*所有学生信息排序---本科生*/
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
void a3()/*打印本科生学生信息*/
{
	void benhead();
	void showonestudent(student *p);
	student *p;
	p=head1;
	printf("本科生的所有学生按总成绩排序为：\n");
	benhead();
	while(p!=NULL)
	{
		showonestudent(p);
		p=p->next ;
	}
}
void a4()/*打印研究生信息*/
{
	void yanhead();
	void show();
	student *p;
	p=head2;
	printf("研究生的所有学生按总成绩排序为：\n");
	yanhead();
	while(p!=NULL)
	{
		show1(p);
		p=p->next ;
	}
}
void a6()/*打印研究生所有信息*/
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
void getpage1(student *head,int page,int pagesize)/*分页显示指定页学生数据----本科生*/
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
void getpage2(student *head,int page,int pagesize)/*分页显示指定页学生数据----研究生*/
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
void showall()/*分页显示指定页学生数据---本科生*/
{
	void getpage1(student *head,int page,int pagesize);
	int menuitem;
	int page=1;
	int totalpage;
	int error;
	if(people==0)
	{
		printf("无相关类别的学生数据!\n");
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
			printf("当前无任何学生数据\n");
			break;
		}
		printf("\n 当前是本科生分页第%d 页， 总共%d 页\n",page,totalpage);
		printf("----------------------------------------------");
		printf("---------------------------------------------\n");
		getpage1(head1,page,PAGESIZE);/*本科生*/
		printf("\n---------------------------------------------");
		printf("----------------------------------------------\n");
		if(page==1 && totalpage==1)
		{
			break;
		}
		else if(page==1)
		{
			printf("分页菜单: 3- 下一页     4- 尾页   5- 返回\n");
			printf("请输入菜单编号（3-5）:");
			do{
				fflush(stdin);
				scanf("%d",&menuitem);
				switch(menuitem)
				{
				case 3: page++;error=0;break;
				case 4: page=totalpage;error=0;break;
				case 5: return ;
				default : error=1;
					printf("菜单编号输入错误，请重新输入菜单编号(3-5):");
					break;
				}
			}while(error);
		}
		else if(page==totalpage)
		{
			printf("分页菜单: 1- 首页   2- 上一页   5- 返回\n");
			printf("请输入菜单编号(1, 2, 5):");
			do{
				fflush(stdin);
				scanf("%d",&menuitem);
				switch(menuitem){
				case 1: page=1;error=0;break;
				case 2: page--;error=0;break;
				case 5: return;
				default: error=1;
					printf("菜单编号输入错误，请重新输入菜单编号（1, 2, 5）:");
					break;
				}
			}while(error);
		}
		else {
			printf("分页菜单: 1- 首页   2- 上一页   3- 下一页   4- 尾页   5- 返回\n");
			printf("请输入菜单编号（1-5）:");
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
					printf("菜单编号输入错误，请重新输入菜单编号:");
					break;
				}
			}while(error);
		}
	}
}
void showall1()/*分页显示指定页学生数据---研究生*/
{
	void getpage2(student *head,int page,int pagesize);
	int menuitem;
	int page=1;
	int totalpage;
	int error;
	if(people==0)
	{
		printf("无相关类别的学生数据!\n");
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
			printf("当前无任何学生数据\n");
			break;
		}
		printf("\n 当前是研究生分页第%d 页， 总共%d 页\n",page,totalpage);
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
			printf("分页菜单: 3- 下一页     4- 尾页   5- 返回\n");
			printf("请输入菜单编号（3-5）:");
			do{
				fflush(stdin);
				scanf("%d",&menuitem);
				switch(menuitem)
				{
				case 3: page++;error=0;break;
				case 4: page=totalpage;error=0;break;
				case 5: return ;
				default : error=1;
					printf("菜单编号输入错误，请重新输入菜单编号(3-5):");
					break;
				}
			}while(error);
		}
		else if(page==totalpage)
		{
			printf("分页菜单: 1- 首页   2- 上一页   5- 返回\n");
			printf("请输入菜单编号(1, 2, 5):");
			do{
				fflush(stdin);
				scanf("%d",&menuitem);
				switch(menuitem){
				case 1: page=1;error=0;break;
				case 2: page--;error=0;break;
				case 5: return;
				default: error=1;
					printf("菜单编号输入错误，请重新输入菜单编号（1, 2, 5）:");
					break;
				}
			}while(error);
		}
		else {
			printf("分页菜单: 1- 首页   2- 上一页   3- 下一页   4- 尾页   5- 返回\n");
			printf("请输入菜单编号（1-5）:");
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
					printf("菜单编号输入错误，请重新输入菜单编号:");
					break;
				}
			}while(error);
		}
	}
}
void a5()/*按班级显示学生信息---本科生*/
{
	void benhead();
	void showonestudent(student *p);
	student *p;
	char classes[M];
	p=head1;
	printf("请输入需要显示的班级:\n");
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
void b1()/*按班级显示学生信息---研究生*/
{
	void yanhead();
	void show1(student *p);
	student *p;
	char classes[M];
	p=head2;
	printf("请输入需要显示的班级:\n");
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
void b2()/*按学号或姓名查询学生*/
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
	printf("请选择查询方式：**0- 学号查询     1- 姓名查询\n");
	scanf("%d",&a);
	while(flag!=0){
		if(a==0)
		{
			fflush(stdin);
			printf("请输入学号信息:");
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
			printf("请输入需要查询的学生姓名:");
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
			printf("选项输入错误，请重新输入:");
			scanf("%d",&a);
			flag=1;
		}
	}
}
void b3(char *classes)/*查询某班中某门课成绩不及格学生信息---本科生*/
{
	void showonestudent(student *p);
	void benhead();
	student *p;
	int a,n=0;
	fflush(stdin);
	printf("请选择需要查询的课程:1- 数学  2- 英语  3- C语言  0- 退出\n");
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
				printf("课程代码输入错误!\n");
				break;
			}
		}
		p=p->next ;
	}
	if(n==0) printf("该班级的相关课程没有不及格的学生\n");
}

void b4(char *classes)/*查询某班中某门课成绩不及格学生信息---研究生*/
{
	void yanhead();
	void show1(student *p);
	student *p;
	int a,n=0;
	fflush(stdin);
	printf("请输入需要查询的成绩: 1- 综合成绩  2- 论文成绩  0- 退出\n");
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
					printf("选择输入错误!\n");
					break;
				}
			}
			p=p->next ;
		}
	}
	if(n==0) printf("该班级的相关课程没有不及格的学生\n");
}

void h1()/*统计每个班的平均成绩---本科生*/
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
	printf("请选择需要查询的课程代码: 1- 数学  2- 英语  3- C语言   0- 退出\n");
	scanf("%d",&a);
	if(a<0 || a>4)
	{
		printf("课程代码选择输入错误，请重新选择:\n");
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
		printf("需要查询的科目是 ");
		switch(a){
		case 1: printf("数学\n");break;
		case 2: printf("英语\n");break;
		case 3: printf("C语言\n");break;
		}
		for(i=0,c=0;c<=b;i++,c++)
		{
			printf("%s 的平均成绩为:%d \n",k[i],sum[c]/people[c]);
		}
	}
}
void h3()/*统计课程某班平均成绩---研究生*/
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
	printf("请选择需要查询的成绩类型:1- 综合成绩   2- 论文成绩   0- 退出\n");
	scanf("%d",&a);
	if(a<0 || a>4){
		printf("选择输入错误，请重新输入:");
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
		printf("需要查询的是");
		switch(a){
		case 1: printf("综合成绩:\n");break;
		case 2: printf("论文成绩:\n");break;
		}
		for(i=0,b=0;b<=m;i++,b++)
		{
			printf("%s 班的平均成绩为 %d\n",k[i],sum[b]/people[b]);
		}
	}
}
void h4(char *classes)/*统计某班中某科成绩等级人数---本科生*/
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
	if(find==0) printf("并没有此班级数据!\n");
	else{
		printf("请选择课程代码:1- 数学   2- 英语   3- C语言   0- 退出\n");
		scanf("%d",&a);
		if(a<0 || a>4)
		{
			printf("选项输入错误，请重新输入:");
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
		case 1:printf("%s 的数学等级分布如下：\n",classes);break;
		case 2:printf("%s 的英语等级分布如下：\n",classes);break;
		case 3:printf("%s 的C语言等级分布如下：\n",classes);break;
		}
		printf("优----%d 人\n",m1);
		printf("良----%d 人\n",m2);
		printf("中----%d 人\n",m3);
		printf("及格----%d 人\n",m4);
		printf("不及格----%d 人\n",m5);
		}
	}
}
void h5(char *classes)/*统计某班中某科成绩等级人数---研究生*/
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
	if(find==0) printf("并没有此班级数据!\n");
	else{
		printf("请选择查询成绩类型:1- 综合成绩   2- 论文成绩   0- 退出\n");
		scanf("%d",&a);
		if(a<0 || a>3)
		{
			printf("选项输入错误，请重新输入:");
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
		case 1:printf("%s 的综合成绩等级分布如下：\n",classes);break;
		case 2:printf("%s 的论文成绩等级分布如下：\n",classes);break;
		}
		printf("优----%d 人\n",m1);
		printf("良----%d 人\n",m2);
		printf("中----%d 人\n",m3);
		printf("及格----%d 人\n",m4);
		printf("不及格----%d 人\n",m5);
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
		printf("该系统暂无数据，请输入存储数据\n");
		printf("请选择存储信息类别：1- 本科生   2- 研究生\n");
		scanf("%d",&a);
		if(a==1) add1();
		else if(a==2) add2();
		p1();
	}
	while(1){
		do{
			fflush(stdin);
			printf("                    主菜单\n");
			printf("========================================================\n");
			printf("|   1- 学生管理                       2- 查询管理      |\n");
			printf("|   3- 排序管理                       4- 统计管理      |\n");
			printf("|   5- 退    出                                        |\n");
			printf("========================================================\n");
			printf("    请输入菜单编号(1--5):");
			scanf("%d",&menuitem);
			if(menuitem>5 || menuitem<1)
				printf("菜单编号输入错误，请重新输入菜单编号(1--5):\n");
			else break;
		}while(1);
		switch(menuitem){
		case 1:student1();printf("\n");break;
		case 2:search();printf("\n");break;
		case 3:sort();printf("\n");break;
		case 4:statis();printf("\n");break;
		case 5:p1();printf("谢谢使用!\n\n");return 0;
		}
	}
}
void student1()/*学生管理*/
{
	int menuitem;
	while(1){
		do{
			fflush(stdin);
			printf("              学生管理菜单\n");
			printf("=========================================================\n");
			printf("| 1- 本科生基本信息录入	2- 研究生基本信息录入		|\n");
			printf("| 3- 基本信息修改	4- 基本信息删除			|\n");
			printf("| 5- 基本信息查询	6- 成绩录入			|\n");
			printf("| 7- 成绩修改		8- 成绩删除			|\n");
			printf("| 9- 成绩查询		10- 计算总成绩、排名		|\n");
			printf("|		11- 退出				|\n");
			printf("=========================================================\n");
			printf("请输入菜单编号(1-11):");
			scanf("%d",&menuitem);
			if(menuitem>11 || menuitem<1)
				printf("菜单编号输入错误，请重新输入菜单编号(1-11):\n\n");
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
void search()/*查询管理*/
{
	int menuitem;
	char classes[M];
	while(1){
		do{
			fflush(stdin);
			printf("			查询管理界面\n");
			printf("=================================================================\n");
			printf("|  1- 本科生分页显示全部学生	2- 本科生显示某班学生信息 	| \n");
			printf("|  3- 本科生按学号或姓名查询	4- 本科生查询某班科目不及格信息	|\n");
			printf("|  5- 研究生分页显示全部学生	6- 研究生显示某班学生信息	| \n");
			printf("|  7- 研究生按学号或姓名查询	8- 研究生查询某班科目不及格信息	|\n");
			printf("|			9- 退出					|\n");
			printf("=================================================================\n");
			printf("请输入菜单编号(1-9):");
			scanf("%d",&menuitem);
			if(menuitem>9 || menuitem<1)
				printf("菜单编号输入错误，请重新输入菜单编号(1-9):\n\n");
			else break;
		}while(1);
		if(menuitem<9 && menuitem>=1){
			switch(menuitem){
			case 1:showall();printf("\n");break;
			case 2:a5()		;printf("\n");break;
			case 3:b2()		;printf("\n");break;
			case 4:
				printf("请输入需要查询的班级:\n");
				scanf("%s",classes);
				b3(classes);
				printf("\n");
				break;
			case 5:showall1();printf("\n");break;
			case 6:b1()		 ;printf("\n");break;
			case 7:b2()		 ;printf("\n");break;
			case 8:
				printf("请输入需要查询的班级:\n");
				scanf("%s",classes);
				b4(classes);
				printf("\n");
				break;
			}
		}
		else if(menuitem==9) break;
	}
}
void sort()/*排序管理*/
{
	int menuitem;
	while(1){
		do{
			fflush(stdin);
			printf("                 排序管理菜单\n");
			printf("========================================================\n");
			printf("|   1- 所有学生按总成绩排序(降序)(本科生);	       |\n");
			printf("|   2- 某个班按总成绩(降序)(本科生);		       |\n");
			printf("|   3- 所有学生按总成绩排序(降序)(研究生);	       |\n");
			printf("|   4- 某个班按总成绩排序(降序)(研究生);	       |\n");
			printf("|   5- 退    出                                        |\n");
			printf("========================================================\n");
			printf("    请输入菜单编号(1--5):");
			scanf("%d",&menuitem);
			if(menuitem>5 || menuitem<1)
				printf("菜单编号输入错误，请重新输入菜单编号(1--5):\n");  
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
void statis()/*统计管理*/
{
	int menuitem;
	char classes[M];
	while(1){
		do{
			fflush(stdin);
			printf("          统计管理菜单\n");
			printf("=========================================================\n");
			printf("|   1- 统计某门课每个班的平均成绩(本科生)		|\n");
			printf("|   2- 统计某个班某门课不同等级人数(本科生)		|\n");
			printf("|   3- 统计某门课每个班的平均成绩(研究生)		|\n");
			printf("|   4- 统计某个班某门课不同等级人数(研究生)		|\n");
			printf("|   5- 退    出                                         |\n");
			printf("=========================================================\n");
			printf("    请输入菜单编号(1--5):");
			scanf("%d",&menuitem);
			if(menuitem>5 || menuitem<1)
				printf("菜单编号输入错误，请重新输入菜单编号(1--5):\n");
			else break;
		}while(1);
		if(menuitem!=5){
			switch(menuitem){
			case 1:h1()		   ;printf("\n");break;
			case 2:
				printf("请输入需要查看的班级:\n");
				scanf("%s",classes);
				h4(classes) ;
				printf("\n");
				break;
			case 3:h3()        ;printf("\n");break;
			case 4:
				printf("请输入需要查看的班级:\n");
				scanf("%s",classes);
				h5(classes) ;
				printf("\n");
				break;
			}
		}
		else if(menuitem==5) break;
	}
}



		




