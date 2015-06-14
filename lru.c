#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N  12              //������ɵ�ҳ��ַ���ĳ��� 
#define B   3             //�������ǰ���̵��ڴ���� 
#define P   5       //���̵�ҳ����
int isInBuf(int buf[], int x, int *p)
 //����ĳ����x��û���ڻ���Buf[]�У����ڣ�������λ�ã����򷵻أ�1,*pΪȱҳ����
{ 
    int i, j = -1; 
    for (i = 0; i < B; i++) 
    { 
      if(buf[i] == x) 
          { 
              j = i; 
              break; 
          } 
          else if (buf[i] == -1) 
          { 
         //�п����ڴ�飨��װ������ļ���ҳ��ʱ��
              (*p)++;
              buf[i] = x; 
              j = i; 
              break; 
          } 
    } 
       if(j==-1) 
              (*p)++;
       return j; 
} 

int oldlru(int f[ ]) 
{ //���ܣ� ����������δʹ��ҳ���λ��
    int i, j = 0, max = -1; 
    for (i = 0; i < B; i++) 
    { 
            if(f[i] > max) 
            {
                    max = f[i];
                    j = i;
            } 
            f[i]++; 
    } 
    return j; 
} 

int main() 
{ 
    int list[N]; //����ķ�ҳ��ַ��
    int change[N]; //��¼ÿ�α��滻��ȥ��ҳ
    int buf[B], f[B], i, j,k; 
    //buf�Ƿ�������̵��ڴ�飬f��¼�ڴ���ҳ����δ������
    int result[B][N]; //�û�����ϸ����
    int old; //ָ��Ҫ����ȥ��ҳ
    int absent; //ȱҳ����
    srand((int)time(NULL));  //��ʼ����������� 
    printf("\n The Random List:\n"); 
    for (i = 0; i < N; i++)
    {//�������ҳ��������� 
        list[i] = rand() % P+1;  
        printf("%3d", list[i]); 
    }
    printf("\n---------------------------------------------------\n");
    // LRU�û��㷨 
    printf("\nLRU:\n"); 
    absent = 0; 
    for(i = 0; i < B; i++) 
        buf[i] = f[i] = -1; 
    for(i = 0; i < N; i++) 
    { 
        j = isInBuf(buf, list[i],&absent); 
        old = oldlru(f); 
        if(j== -1) //���û�ҳ��
    	{ 
            change[i]=buf[old]; 
            buf[old] = list[i]; 
            f[old] = 0;      
        } 
        else //�����û�ҳ��
        { 
            f[j]=0; 
            change[i]=-1; 
    	}
 
        //���浱ǰ�ڴ�ҳ�����
        for(k=0;k<B; k++)   
                result[k][i]=buf[k];
    } 
    //����û���ϸ����
    printf("the result is:\n");
    for(i=0;i<B;i++)
    {
        for(j=0;j<N;j++)
        printf("%3d",result[i][j]);
        printf("\n");
    }
    //���ÿ�α��û���ȥ��ҳ
    printf("\nthe page is changed:\n");
    for(i=0;i<N;i++)
    {
    if(change[i]== -1)
        printf("   "); 
    else
        printf("%3d",change[i]);
    }

    //��ʾȱҳ������ȱҳ�� 
    printf("\nabsent:%d\n",absent); 
    printf("the absent vote is:%f\n",(float)absent/N);
}
