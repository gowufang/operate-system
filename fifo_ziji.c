#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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



int main() 
{ 
    int list[N]; //����ķ�ҳ��ַ��
    int change[N]; //��¼ÿ�α��滻��ȥ��ҳ
    int buf[B], f[B], i, j,k; 
    //buf�Ƿ�������̵��ڴ�飬f��¼�ڴ���ҳ����δ������
    int result[B][N]; //�û�����ϸ����
    int old; //ָ��Ҫ����ȥ��ҳ
    int absent; //ȱҳ����
	int w=1;
	int changes=0;
    srand((int)time(NULL));  //��ʼ����������� 
    printf("\n The Random List:\n"); 
    for (i = 0; i < N; i++)
    {//�������ҳ��������� 
        list[i] = rand() % P+1;  
        printf("%3d", list[i]); 
    }
    printf("\n---------------------------------------------------\n");
    // FIFO�û��㷨 
    printf("\nFIFO:\n"); 
	printf("the result is:\n");
    absent = 0; 
    for(i = 0; i < B; i++) 
        buf[i] = f[i] = -1; 
    for(i = 0; i < N; i++) 
    { 
        j = isInBuf(buf, list[i],&absent); 
        //old = oldlru(f); 
        if(j== -1) //���û�ҳ��
		{ 
           	changes++;
			old=(changes-1)%B;                                                                                                                                       
			change[i]=buf[old]; 
            buf[old] = list[i]; 
			//old++;
			// f[old] = 0;      
        } 
        else //�����û�ҳ��
        { 
            f[j]=0; 
            change[i]=-1; 
		}
		printf("��%d��ҳ��:",w++);
        //���浱ǰ�ڴ�ҳ�����
        for(k=0;k<B; k++)   
		{
			result[k][i]=buf[k];
			
			printf("%4d",result[k][i]);//ÿ���û���ͽ�����ҳ�����	
			//Sleep(500);//buf[]�е������������
		}
		
		printf("\n");
	} 
	
	printf("\n\n%d��ҳ�����ţ�\n",N);
	for (i = 1; i <= N; i++)//ҳ�����
    {
        printf("%3d", i); 
    }
	//���ÿ�α��û���ȥ��ҳ
    printf("\nthe page is changed:\n");
	
	printf("\n");
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
