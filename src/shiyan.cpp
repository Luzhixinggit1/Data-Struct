#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxsize 10000
typedef char sstring[maxsize];
using namespace std;
typedef struct WorldNode{
	char s[30];
	int line;   //行号
	int numWorld;    //第几个单词
	struct WorldNode *next;
}WorldNode,*World;


//创建文本文件
void CreatTxt()
{
	FILE *fp;
	if((fp=fopen("1.txt","w"))==NULL)
	{
		cout<<"文件夹打开失败！"<<endl;
		exit(0);
	}
	char c;
	c = getchar();
	while(c!='~')
	{
		fputc(c,fp);
		c = getchar();
	}
	fputc('~',fp);
	fclose(fp);
}


//建立单词链表
void CreatWorld(World &W)
{
	World p,q;
	FILE *fp;
	if((fp=fopen("1.txt","r"))==NULL)
	{
		cout<<"打开文件失败"<<endl;
		exit(0);
	}

	p = new WorldNode;
	W = q = p;
	char c;
	int Line = 1;
	int count = 1;
	int i = 0;
	c = fgetc(fp);
	while(c!=EOF&&c!='~')
	{
		if(c=='\n')
		{
			c = fgetc(fp);
			Line += 1;
			count = 1;
			continue;
		}
		while(c!=' '&&c!=','&&c!='.'&&c!='\n'&&c!=EOF&&c!='~')
		{
			p->s[i] = c;
			i++;
			c = fgetc(fp);
		}
		p->s[i]='\0';
		i = 0;
		p->line = Line;
		p->numWorld = count;
		if(c==' '||c==','||c=='.')
		{
			count+=1;
		}
		if(c == '\n')
		{
			count = 1;
			Line += 1;
		}
		if(c=='~')break;
		q = p;
		p = new WorldNode;
		q->next = p;
		c = fgetc(fp);

	}
	q->next = NULL;

}

void WorldTimes(World &W,char *S)
{
	cout<<"Hellfj我急"<<endl;
	int Times = 0;
	World P;
	P = W;
	while(P!=NULL)
	{
		if(strcmp(P->s,S)==0)
		{
			cout<<"nihao分打开"<<endl;
			Times+=1;
		}
		  P = P->next;

	}
	cout<<S<<"一共出现"<<Times<<"次"<<endl;
}

void WorldOption(World &W,char *S)
{
	int n = 0;
	World P = W;
	while(P!=NULL)
	{
		if(strcmp(P->s,S)==0)
		{
			n = 1;
			break;
		}
		P = P->next;
	}
	if(n)
		cout<<S<<"首次出现的位置第"<<P->line<<"行第"<<P->numWorld<<"个"<<endl;
}




int main()
{

	cout<<"请输入文本（以～结束）："<<endl;
	CreatTxt();
	cout<<"文本创建成功"<<endl;
	 
	char *s="is";
	World W;
	CreatWorld(W);  
	WorldTimes(W,s);
	WorldOption(W,s);
	

	return 0;

}
