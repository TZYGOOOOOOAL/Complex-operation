#include <stdio.h>
#include<math.h>
#include<stdlib.h>
float R,I,M,J;		//实部，虚部，模值，幅角

#define PI 3.1415926

void zhijiao(void);				//直角坐标系下运算
void zhijiao_to_ji(void);		//直角坐标系转极坐标
void ji(void);					//极坐标系下运算
void ji_to_zhijiao(void);		//极坐标系转直角

main()
{   
	int mode;	//模式
	while(1)	//死循环一直输入
	{
		R=0,I=0,M=0,J=0;	//清零
		printf("\n输入:1直角坐标运算,2极坐标,3直角坐标转极坐标,4极坐标转直角,5清屏  ");
		scanf("%d",&mode);	//输入选择的模式
		switch(mode)
		{
			case 1:zhijiao();		break;
			case 2:ji();			break;
			case 3:zhijiao_to_ji();	break;
			case 4:ji_to_zhijiao();	break;
			case 5:system("cls");	break;
		}
	}
}
void zhijiao()										//计算直角坐标系下复数运算
{
    float R1,I1,R2,I2;
	char suan;
    printf("请输入：(数字或运算符之间以空格分隔)\n");
	scanf("%f%f %c%f%f",&R1,&I1,&suan,&R2,&I2);		//%c前加空格防止空格赋值给suan
    
	switch(suan)									
	{
		case '+':
		R=R1+R2;
		I=I1+I2;
		break;

		case '-':
		R=R1-R2;
		I=I1-I2;
		break;

		case '*':
		R=R1*R2-I1*I2;
		I=R1*I2+R2*I1;
		break;

		case '/':
		R=(R1*R2+I1*I2)/(R2*R2+I2*I2);
		I=(R2*I1-R1*I2)/(R2*R2+I2*I2);
		break;
	}
	//复数虚部添加正负号,同时实部(或虚部)为0情况省略实部(或虚部)
	if(fabs(R-0)<1e-6&&!(fabs(I-0)<1e-6))
		printf("(%f%+fi) %c (%f%+fi)=%fi\n",R1,I1,suan,R2,I2,I);
	if(fabs(I-0)<1e-6&&!(fabs(R-0)<1e-6))
		printf("(%f%+fi) %c (%f%+fi)=%f\n",R1,I1,suan,R2,I2,R);
	if(fabs(R-0)<1e-6&&(fabs(I-0)<1e-6))
		printf("(%f%+fi) %c (%f%+fi)=0\n",R1,I1,suan,R2,I2);
	if(!(fabs(R-0)<1e-6)&&!(fabs(I-0)<1e-6))
		printf("(%f%+fi) %c (%f%+fi)=%f%+fi\n",R1,I1,suan,R2,I2,R,I);
}


void zhijiao_to_ji()     //直角坐标系复数转化为极坐标
{
	printf("请输入实部和虚部：(以空格分隔)\n");
	scanf("%f%f",&R,&I);
	M=sqrt(R*R+I*I);		//模值
	J=180/PI*atan2(I,R);	//幅角计算选择atan2()函数,保证结果分布于4象限内
	printf("\n %f%+fi=%f(%f)\n",R,I,M,J);

}
	
void ji()
{
	float M1,M2,J1,J2,t1,t2;
	char suan;
    printf("请输入：(模或角度或运算符之间以空格分隔)\n");
	scanf("%f%f %c%f%f",&M1,&J1,&suan,&M2,&J2);
	t1=J1,t2=J2;
	J1=J1*PI/180;
	J2=J2*PI/180;

	//极坐标加减法可利用余弦定理
	switch(suan)
	{
		case '+':
		M=sqrt(M1*M1+M2*M2+2*M1*M2*cos(J1-J2));
		J=atan2((M1*sin(J1)+M2*sin(J2)),(M1*cos(J1)+M2*cos(J2)));
		break;

		case '-':
		M=sqrt(M1*M1+M2*M2-2*M1*M2*cos(J1-J2));
		J=atan2((M1*sin(J1)-M2*sin(J2)),(M1*cos(J1)-M2*cos(J2)));
		break;

		case '*':
		M=M1*M2;
		J=J1+J2;
		break;

		case '/':
		M=M1/M2;
		J=J1-J2;
		break;
	}
	J=180/PI*J;
	J1=t1,J2=t2;     //J,J1,J2以度数输出

	printf("%f(%f) %c %f(%f)=%f(%f)\n",M1,J1,suan,M2,J2,M,J);

	J=J*PI/180;
	ji_to_zhijiao();
	if(fabs(R-0)<1e-6&&!(fabs(I-0)<1e-6))
		printf(" =%fi\n",I);
	if(fabs(I-0)<1e-6&&!(fabs(R-0)<1e-6))
		printf(" =%f\n",R);
	if(fabs(R-0)<1e-6&&(fabs(I-0)<1e-6))
		printf(" =0\n");
	if(!(fabs(R-0)<1e-6)&&!(fabs(I-0)<1e-6))
		printf(" =%f%+fi\n",R,I);

}

void ji_to_zhijiao()
{   
	float t;
	printf("请输入模和角度：(以空格分隔)\n");
	scanf("%f%f",&M,&J);

	t=J*PI/180;	//转为弧度
	R=M*cos(t);
	I=M*sin(t);

	if(fabs(R-0)<1e-6&&!(fabs(I-0)<1e-6))
		printf(" %f(%f)=%fi\n",M,J,I);
	if(fabs(I-0)<1e-6&&!(fabs(R-0)<1e-6))
		printf(" %f(%f)=%f\n",M,J,R);
	if(fabs(R-0)<1e-6&&(fabs(I-0)<1e-6))
		printf(" %f(%f)=0\n",M,J);
	if(!(fabs(R-0)<1e-6)&&!(fabs(I-0)<1e-6))
		printf(" %f(%f)=%f%+fi\n",M,J,R,I);
}


