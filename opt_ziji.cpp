#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
#define N  12              //随机生成的页地址流的长度 
#define B   3              //分配给当前进程的内存块数 
#define P   5              //进程的页面数
int isInBuf(int buf[], int x, int *p) 
//返回某个数x有没有在缓冲Buf[]中，若在，返回其位置，否则返回－1,*p为缺页次数
{   int i, j = -1; 
for (i = 0; i < B; i++) //依次在内存块（3个）中检查list【i】是否存在
{ 
	if(buf[i] == x) 
	{ 
		j = i; 
		break; 
	} 
	else if (buf[i] == -1) 
	{ //有空闲内存块（在装入最初的几个页面时）
		(*p)++;//absence增加一
		buf[i] = x;//将x赋值给buf【i】
		j = i;														//j的作用？？
		break; 
	} 
} 


if(j==-1) 
(*p)++;	//等到3个内存块全部检查完后还是没有x的值，则absence也加1	
return j; 
} 
int oldopt(int i, int buf[ ], int list[ ], int f[ ])
{//功能：返回下次使用距离现在最久的页面位置
	int k, h, j=0, max=-1;
	for (k = 0; k < B; k++) //两层循环，一个for是负责行，即查内存块中的buf[]，有三个，B
	{
        for (h = i; h < N; h++) //从第i个开始找起，向后查。负责列，遍历list[i]后面的所有值
			if (buf[k] == list[h])//buf【】这列中有三个值
				// 判断物理块中的页面是否与未来页面相等
			{
				f[k] = h; //如果找到，则记录h（即list的序号），这个h就是下次使用距离这次的时间
				break;
			}
			if(h==N)
				f[k] = N;//f记录内存中页面下次使用的时间，依次记录buf[]的数的h（什么时候被用到）
    }
	
    //寻找下次使用距离现在最久的页面
    for (k = 0; k < B; k++) 
    {
        if (max < f[k]) 
        {
            max = f[k];
            j = k;//认为第k个是距离现在最久的页面，循环三次决定最终的k
        }
    }
    return j;
}

int main() 
{ 
    int list[N]; //程序的访页地址流
    int change[N]; //记录每次被替换出去的页
    int buf[B],f[B],i,j,k; 
    //buf是分配给进程的内存块，f记录内存中页面下次使用的时间
    int result[B][N]; //置换的详细过程
    int old; //指向将要换出去的页
    int absent; //缺页次数
    srand((int)time(NULL));  //初始化随机数种子
    printf("\n The Random List:\n"); 
    for (i = 0; i < N; i++)
    {//产生随机页面访问序列 
		list[i] = rand() % P+1;  
		printf("%3d", list[i]); 
    } 
    printf("\n----------------------------------------------------------------\n");
	
	
	
	
	
    //OPT置换算法 
    printf("\nOPT:\n");
    absent=0;		
    for(i = 0; i < B; i++) 
        buf[i] = f[i] = -1;  
    for(i = 0; i < N; i++)//检查十二次
    { 
        j=isInBuf(buf, list[i],&absent); //检查list【i】是否在buf里面
        if(j== -1) //j==-1,则需置换页面
		{ 
            old=oldopt(i, buf, list, f);//*******************使用置换算法
            
            
			change[i]=buf[old];//被置换出来的数赋值给change[i],i为当前的list数组的序号
			buf[old] = list[i]; //将list[i](将要换进的数)的值赋值给buf[old]（被置换出来的数，将被覆盖）
		} 
		else 
			change[i]=-1; //设置chang[i]的值为-1，等下-1的值都用三个空格代替
		
        //保存当前内存页面情况
        for(k=0;k<B;k++)   //置数，置给最终的矩阵，最终的结果（对每列进行赋值）
			result[k][i]=buf[k];//i代表第i（i共12次）列（即从矩阵的k行，i列开始赋值）//更新buf[]页面（一列）
		/**********可以加一行输出*************/
    }
	
    //输出置换详细过程
    printf("the result is:\n");
    for(i=0;i<B;i++)//变换行
    {
        for(j=0;j<N;j++)//变换列
			printf("%3d",result[i][j]);//一行一行，逐个输出
		printf("\n");
    }
	
	
	
    //输出每次被置换出去的页
    printf("\nthe page is changed:\n");
    for(i=0;i<N;i++)
    {
        if(change[i]== -1)//如果没有如果没有发生置换，则输出3个空格 
            printf("   ");	
        else
            printf("%3d",change[i]);//否则输出置换出去的数 
    }
	
    //显示缺页次数及缺页率 
    printf("\nabsent:%d\n",absent); 
    printf("the absent vote is:%f\n",(float)absent/N);
}
