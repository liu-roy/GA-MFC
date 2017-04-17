#include<cmath>
#include<ctime>
#include<cstdlib>
#include"opencv.hpp"
struct  chromosome
{
	double fitness;//��Ӧ��
	int gene[8];//��������
	int decimal;//ʮ�������֣���������ת��������
	double pselect;//Ⱦɫ��ѡ�����
	double ap;//�ۼƸ���
};

void BinToDec(int *a,int &b);
void DecToBin(const int a ,int *b);
void InitializePopulation(chromosome *a, int size);
void GetFitness(chromosome *a,double* histogram,int *statistic,int size);
void FucSelect(chromosome *a,int size);
void FucCross(chromosome *a,int size,double pcross);
void FucVariation(chromosome *a,int size,double pvariation);
void FucReproduct(chromosome *a,chromosome* b,double *histogram,int *statistic,int size,double &best ,int &yuzhi);
