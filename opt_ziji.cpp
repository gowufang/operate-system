#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
#define N  12              //������ɵ�ҳ��ַ���ĳ��� 
#define B   3              //�������ǰ���̵��ڴ���� 
#define P   5              //���̵�ҳ����
int isInBuf(int buf[], int x, int *p) 
//����ĳ����x��û���ڻ���Buf[]�У����ڣ�������λ�ã����򷵻أ�1,*pΪȱҳ����
{   int i, j = -1; 
for (i = 0; i < B; i++) //�������ڴ�飨3�����м��list��i���Ƿ����
{ 
	if(buf[i] == x) 
	{ 
		j = i; 
		break; 
	} 
	else if (buf[i] == -1) 
	{ //�п����ڴ�飨��װ������ļ���ҳ��ʱ��
		(*p)++;//absence����һ
		buf[i] = x;//��x��ֵ��buf��i��
		j = i;														//j�����ã���
		break; 
	} 
} 


if(j==-1) 
(*p)++;	//�ȵ�3���ڴ��ȫ����������û��x��ֵ����absenceҲ��1	
return j; 
} 
int oldopt(int i, int buf[ ], int list[ ], int f[ ])
{//���ܣ������´�ʹ�þ���������õ�ҳ��λ��
	int k, h, j=0, max=-1;
	for (k = 0; k < B; k++) //����ѭ����һ��for�Ǹ����У������ڴ���е�buf[]����������B
	{
        for (h = i; h < N; h++) //�ӵ�i����ʼ�������顣�����У�����list[i]���������ֵ
			if (buf[k] == list[h])//buf����������������ֵ
				// �ж�������е�ҳ���Ƿ���δ��ҳ�����
			{
				f[k] = h; //����ҵ������¼h����list����ţ������h�����´�ʹ�þ�����ε�ʱ��
				break;
			}
			if(h==N)
				f[k] = N;//f��¼�ڴ���ҳ���´�ʹ�õ�ʱ�䣬���μ�¼buf[]������h��ʲôʱ���õ���
    }
	
    //Ѱ���´�ʹ�þ���������õ�ҳ��
    for (k = 0; k < B; k++) 
    {
        if (max < f[k]) 
        {
            max = f[k];
            j = k;//��Ϊ��k���Ǿ���������õ�ҳ�棬ѭ�����ξ������յ�k
        }
    }
    return j;
}

int main() 
{ 
    int list[N]; //����ķ�ҳ��ַ��
    int change[N]; //��¼ÿ�α��滻��ȥ��ҳ
    int buf[B],f[B],i,j,k; 
    //buf�Ƿ�������̵��ڴ�飬f��¼�ڴ���ҳ���´�ʹ�õ�ʱ��
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
    printf("\n----------------------------------------------------------------\n");
	
	
	
	
	
    //OPT�û��㷨 
    printf("\nOPT:\n");
    absent=0;		
    for(i = 0; i < B; i++) 
        buf[i] = f[i] = -1;  
    for(i = 0; i < N; i++)//���ʮ����
    { 
        j=isInBuf(buf, list[i],&absent); //���list��i���Ƿ���buf����
        if(j== -1) //j==-1,�����û�ҳ��
		{ 
            old=oldopt(i, buf, list, f);//*******************ʹ���û��㷨
            
            
			change[i]=buf[old];//���û�����������ֵ��change[i],iΪ��ǰ��list��������
			buf[old] = list[i]; //��list[i](��Ҫ��������)��ֵ��ֵ��buf[old]�����û������������������ǣ�
		} 
		else 
			change[i]=-1; //����chang[i]��ֵΪ-1������-1��ֵ���������ո����
		
        //���浱ǰ�ڴ�ҳ�����
        for(k=0;k<B;k++)   //�������ø����յľ������յĽ������ÿ�н��и�ֵ��
			result[k][i]=buf[k];//i�����i��i��12�Σ��У����Ӿ����k�У�i�п�ʼ��ֵ��//����buf[]ҳ�棨һ�У�
		/**********���Լ�һ�����*************/
    }
	
    //����û���ϸ����
    printf("the result is:\n");
    for(i=0;i<B;i++)//�任��
    {
        for(j=0;j<N;j++)//�任��
			printf("%3d",result[i][j]);//һ��һ�У�������
		printf("\n");
    }
	
	
	
    //���ÿ�α��û���ȥ��ҳ
    printf("\nthe page is changed:\n");
    for(i=0;i<N;i++)
    {
        if(change[i]== -1)//���û�����û�з����û��������3���ո� 
            printf("   ");	
        else
            printf("%3d",change[i]);//��������û���ȥ���� 
    }
	
    //��ʾȱҳ������ȱҳ�� 
    printf("\nabsent:%d\n",absent); 
    printf("the absent vote is:%f\n",(float)absent/N);
}
