#include<cmath>
#include<ctime>
#include<cstdlib>
#include"opencv.hpp"
struct  chromosome
{
	double fitness;//适应度
	int gene[8];//基因序列
	int decimal;//十进制数字，具体用来转换二进制
	double pselect;//染色体选择概率
	double ap;//累计概率
};

void BinToDec(int *a,int &b);
void DecToBin(const int a ,int *b);
void InitializePopulation(chromosome *a, int size);
void GetFitness(chromosome *a,double* histogram,int *statistic,int size);
void FucSelect(chromosome *a,int size);
void FucCross(chromosome *a,int size,double pcross);
void FucVariation(chromosome *a,int size,double pvariation);
void FucReproduct(chromosome *a,chromosome* b,double *histogram,int *statistic,int size,double &best ,int &yuzhi);
