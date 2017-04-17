#include"stdafx.h"
#include"GA.h"

void DecToBin(const int a ,int *b)
{
	int i=7;
	int c=a;
	for(i=0;i<=7;i++)
		b[i]=0;
	i=i-1;
	while(c!=0)
	{
		b[i]=c%2;
		c/=2;
		i--;
		
	}
}
void BinToDec(int *a,int &b)
{
	b=0;
	for(int i=7;i>=0;i--)
		b=b+a[i]*(int)pow(double(2),(double)(7-i));
}

void InitializePopulation(chromosome *a, int size)
{
	srand((unsigned)time(NULL));
	int i=0;
	for(i=0;i<size;i++)
	{	
		a[i].decimal=rand()%256;
		//int c=a[i].decimal;
		DecToBin(a[i].decimal,a[i].gene);
		
		
	}
}

void GetFitness(chromosome *a,double *histogram,int *statistic,int size)
{
	for(int i=0;i<size;i++)
	{
		double pback=0;//背景概率
		double pfront=0;//目标概率
		double bave=0;//背景均值
		double fave=0;//目标均值
		double allave=0;//图像整体均值
		int j;
		for(j=0;j<a[i].decimal;j++)
		{
			pback+=histogram[j];
		}
		for(j=0;j<a[i].decimal;j++)
		{
			if (abs(pback-0)<0.0001)
			{
				pback=0;bave=0;
				break;
			}
			bave+=(j*histogram[j])/pback;
		}
		for(j=a[i].decimal;j<=255;j++)
		{
			pfront+=histogram[j];
		}
		for(j=a[i].decimal;j<=255;j++)
		{
			if (abs(pfront-0)<0.0001)
			{
				pfront=0;fave=0;
				break;
			}
			fave+=(j*histogram[j])/pfront;
		}
		double c=pfront+pback;
		allave=pfront*fave+pback*bave;
		a[i].fitness=pback*(bave-allave)*(bave-allave)+pfront*(fave-allave)*(fave-allave);
	}
}
void FucSelect(chromosome *a,int size)//a为初试种群;
{
	chromosome *b=new chromosome[size];
	double sumfitness=0;
	for(int i=0;i<size;i++)
	{
		sumfitness+=a[i].fitness;
	}
	for(int i=0;i<size;i++)//选择概率计算
	{
		a[i].pselect=a[i].fitness/sumfitness;
	}
	for(int i=1;i<size;i++)
	{
		a[0].ap=a[0].pselect;
		a[i].ap=a[i-1].ap+a[i].pselect;
	}
	srand((unsigned)time(NULL));//轮盘赌选择
	int k=0;
	for(int i=0;i<size;i++)
	{
		double r=rand()*1.0/RAND_MAX;
		for(int j=0;j<size;j++)
		{
			if(r<a[j].ap)
			{
				b[k++]=a[j];
				break;
			}
		}
	}
	for(int i=0;i<size;i++)
			a[i]=b[i];
	delete []b;

}

void FucCross(chromosome *a,int size,double pcross)
{
	srand((unsigned)time(NULL));
	for(int i=0;i<=size/2;i++)
	{
		int r=rand()%3+2;//交叉位数
		double r2=rand()*1.0/RAND_MAX;
		if(r2>pcross)
			continue;
		int temp[8]={0};
		if(2==r)
		{
			int j=rand()%6; //交叉点
			temp[j]=a[i].gene[j];
			temp[j+1]=a[i].gene[j+1];
			a[i].gene[j]=a[size-1-i].gene[j];
			a[i].gene[j+1]=a[size-1-i].gene[j+1];
			a[size-1-i].gene[j]=temp[j];
			a[size-1-i].gene[j+1]=temp[j+1];
		}
		else if(3==r)
		{
			int j=rand()%5;
			temp[j]=a[i].gene[j];
			temp[j+1]=a[i].gene[j+1];
			temp[j+2]=a[i].gene[j+2];
			a[i].gene[j]=a[size-1-i].gene[j];
			a[i].gene[j+1]=a[size-1-i].gene[j+1];
			a[i].gene[j+2]=a[size-1-i].gene[j+2];
			a[size-1-i].gene[j]=temp[j];
			a[size-1-i].gene[j+1]=temp[j+1];
			a[size-1-i].gene[j+2]=temp[j+2];
		}
		else 
		{
			int j=rand()%4;
			temp[j]=a[i].gene[j];
			temp[j+1]=a[i].gene[j+1];
			temp[j+2]=a[i].gene[j+2];
			temp[j+3]=a[i].gene[j+3];
			a[i].gene[j]=a[size-1-i].gene[j];
			a[i].gene[j+1]=a[size-1-i].gene[j+1];
			a[i].gene[j+2]=a[size-1-i].gene[j+2];
			a[i].gene[j+3]=a[size-1-i].gene[j+3];
			a[size-1-i].gene[j]=temp[j];
			a[size-1-i].gene[j+1]=temp[j+1];
			a[size-1-i].gene[j+2]=temp[j+2];
			a[size-1-i].gene[j+3]=temp[j+3];
		}
	}
}
void FucVariation(chromosome *a,int size,double pvariation)
{
	srand((unsigned)time(NULL));
	for(int i=0;i<size;i++)
	{	
		double r2=rand()*1.0/RAND_MAX;
		int ibit=rand()%8;
		if (r2<pvariation)
		{
			if(a[i].gene[ibit]==1)
				a[i].gene[ibit]=0;
			else
				a[i].gene[ibit]=1;

		}
	}
	for(int i=0;i<size;i++)
	{
		BinToDec(a[i].gene,a[i].decimal);
	}

}
void FucReproduct(chromosome *a,chromosome *b,double *histogram,int *statistic,int size,double &best,int &yuzhi)
{
	GetFitness(a,histogram,statistic,size);
	double maxa=0;double maxb=0;
	int ayuzhi=0;int byuzhi=0;
	for(int i=0;i<size;i++)
	{	
		if(a[i].fitness>maxa)
		{
			maxa=a[i].fitness;
			ayuzhi=a[i].decimal;
		}

	}
	for(int i=0;i<size;i++)
	{	
		if(b[i].fitness>maxb)
		{
			maxb=b[i].fitness;
			byuzhi=b[i].decimal;
		}

	}
	if(maxa<maxb)
	{
		best=maxb;
		yuzhi=byuzhi;
		for(int i=0;i<size;i++)
			a[i]=b[i];
	}
	else 
	{
			best=maxa;
			yuzhi=ayuzhi;
			for(int i=0;i<size;i++)//保存最新的a
				b[i]=a[i];
	}
}

