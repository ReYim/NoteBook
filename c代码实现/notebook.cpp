#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

struct Day {
	int year;
	int mon;
	int day;
	int hour;
	int min;
};


/** judge �����ж�������û����������Ƿ���ȷ
 *   ����ֵ��
 *	-1��ʾ����ȷ
 *	0��ʾΪ����Ա�û�
 *	1��ʾΪĬ���û�
 * 	>1��ʾΪ��ͨ�û�
 **/
int judge(char username[20],char password[20]) {
	char rightName[20],rightPassword[20];
	FILE *nameFile=fopen("administrator.txt","r");
	int userNumber;
	if(strcmp(username,"administrator")==0) {
		if(strcmp(password,"123456")==0) {
			printf("���ڵ�¼.......\n");
			Sleep(1000);
			printf("��¼�ɹ�!\n");
			Sleep(1000);
			return 0;//����Ա
		}
	} else {
		for(userNumber=1; fscanf(nameFile,"%s %s\n",rightName,rightPassword)!=EOF; userNumber++) {
			if(strcmp(username,rightName)==0)
				if(strcmp(password,rightPassword)==0) {
					printf("���ڵ�¼.......\n");
					Sleep(1000);
					printf("��¼�ɹ�!\n");
					Sleep(1000);
					return userNumber;//��ͨ�û�
				}
		}
		printf("���������û���������!\n");
		return -1;//����
	}
}




/** login_in ����Ϊ��¼����
 *  ���� time ��ʾ�����������Ĵ���
 *	����ﵽ3��ʱǿ���˳�����
 *	��������ֵΪ judge�����ķ���ֵ
 **/
int login_in() {
	int time=0,judgeFlag=0;
	char enter_name[20],password[20];

	printf("          <Ĭ�ϵ��û���Ϊ user0,������ 12345>          \n");
	while(time<=3) {
		if(time==3) {
			printf("���Ѿ��������3��!ǿ���˳�����!");
			Sleep(1000);
			exit(0);
		}

		printf("�������û���:\n");
		scanf("%s",&enter_name);
		int i=0;

		printf("�������������:\n");
		while(i<19&&(password[i]=getch())!='\r') {
			if(password[i]=='\b') {
				printf("\b \b");
				i--;
			} else {
				putchar('*');
				i++;
			}
		}
		password[i]='\0';
		//	printf("\nyour password is:%s;long:%d",password,strlen(password));
		printf("\n");
		getchar();

		judgeFlag=judge(enter_name,password);
		if(judgeFlag==-1)
			time++;
		else
			break;
	}
	return judgeFlag;
}




/** judgeData ���������ж����������Ƿ���� 
 *	������1
 *  ��������-1
 *
 **/
int judgeData(Day day) {
	if(day.mon>12||day.mon<=0||day.day>31||day.day<=0||day.hour<0||day.hour>23||day.min>60||day.min<=0||(day.year%2017)>18||(day.year%2017)<0)
		return -1;
	return 1;
}
int judgeData(Day day,int type, int number) {
	if(day.mon>12||day.mon<=0||day.day>31||day.day<=0||day.hour<0||day.hour>23||day.min>60||day.min<=0||day.year<2017||day.year>2018||(type!=0&&type!=1)||number<=0||number>100000)
		return -1;
	else
		return 1;
}



/** recording ��������������Ҫ��¼����Ϣ
 *	������ʾ�ĸ�ʽ����ʹ洢��Ϣ
 *  �����������Ϣ��������ԭ���ݵ�ĩβ�������
 *	�������ı���������
 *	���Խ�����������
 *
 **/
int recording(int userNumber) {
	int type,number,enterFlag;
	Day day;
	char detail[500];

// ͨ������Ա�ļ���Ӧ���б��ȡ��Ӧ�û��Ĵ洢�ļ�����
	char name[20],password[20];
	FILE *nameFile=fopen("administrator.txt","r");
	for(int i=1; i<=userNumber; i++) {
		fscanf(nameFile,"%s %s\n",name,password);
	}
	const char str[] = ".txt";
	int len = strlen(name);
	for(int i=0; i<strlen(str); i++) {
		name[len+i] = str[i];
	}
	name[len+strlen(str)]=0;

	FILE *userFile=fopen(name,"a+");//a+��ʾ��ԭ�ļ���ĩβд������
	printf("�밴�����¸�ʽ������Ŀ��Ϣ:\n");
	printf("	[ʱ��(��.��.��.ʱ.��)+����(1/0 ��ʾ ����/֧��)+����+��ϸ]\n");
	while(1) {

		scanf("%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail);
		if(judgeData(day,type,number)!=1) {
			printf("������Ϣ���Ϸ�!��Ϣ¼��ʧ��!\n");
			return -1;
		}

		fprintf(userFile,"%d.%d.%d.%d.%d  %d %d %s\n",day.year,day.mon,day.day,day.hour,day.min,type,number,detail);
		printf("��Ϣ¼��ɹ�!�Ƿ��������? <1/0>\n");
		scanf("%d",&enterFlag);
		if(enterFlag!=1)
			break;
	}
	fclose(nameFile);
	fclose(userFile);

	return 1;
}


/**  seach �������ڲ����������
 *	 ������Ҫ���ҵ�����
 *	 ���ҳɹ��򷵻���Ϣ����ϸ����
 *	 ���򷵻�ʧ����Ϣ
 *
 **/
int seach(int userNumber) {

// ͨ������Ա�ļ���Ӧ���б��ȡ��Ӧ�û��Ĵ洢�ļ�����
	char name[20];
	FILE *nameFile=fopen("administrator.txt","r");
	for(int i=1; i<=userNumber; i++) {
		fscanf(nameFile,"%s",name);
	}
	const char str[] = ".txt";
	int len = strlen(name);
	for(int i=0; i<strlen(str); i++) {
		name[len+i] = str[i];
	}
	name[len+strlen(str)]=0;

	int type,number,seachType,seachNumber;
	Day day,seachDay,theNew;
	char detail[500],newDetail[500];
	//������Ҫ���ҵ�����
	printf("�밴�����¸�ʽ������Ҫ���ҵ���Ŀ��Ϣ\n");
	printf("	[ʱ��(��.��.��.ʱ.��)]\n");
	scanf("%d.%d.%d.%d.%d",&seachDay.year,&seachDay.mon,&seachDay.day,&seachDay.hour,&seachDay.min);

	if(judgeData(seachDay)!=1) {
		printf("������Ϣ���Ϸ�!��Ϣ¼��ʧ��!\n");
		return -1;
	}
	char Type='-';
	FILE *userFile=fopen(name,"r");//r��ʾ��ԭ�ĵĻ����϶�����
	while(fscanf(userFile,"%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail)!=EOF) {
		if(day.min==seachDay.min && day.hour==seachDay.hour && day.day==seachDay.day && day.mon==seachDay.mon && day.year==seachDay.year) {
			if(type==1)
				Type='+';
			printf("�������:%d.%d.%d.%d.%d %c%d %s\n",day.year,day.mon,day.day,day.hour,day.min,Type,number,detail);
			return 1;
		}

	}
	fclose(nameFile);
	fclose(userFile);

	printf("�޷��ҵ���Ŀ��Ϣ��\n");
	return -1;

}



/**  rewrite ���������޸�ԭ����Ϣ
 *	  �û���Ҫ����֮ǰ�Ѽ�¼����Ϣ��Ϊ��������
 *	  �������޸ĺ��������Ϊ�޸�����
 *	  �������ʧ���򲻻�����޸�
 *
 **/
int rewrite(int userNumber) {

// ͨ������Ա�ļ���Ӧ���б��ȡ��Ӧ�û��Ĵ洢�ļ�����
	char name[20];
	FILE *nameFile=fopen("administrator.txt","r");
	for(int i=1; i<=userNumber; i++) {
		fscanf(nameFile,"%s",name);
	}
	const char str[] = ".txt";
	int len = strlen(name);
	for(int i=0; i<strlen(str); i++) {
		name[len+i] = str[i];
	}
	name[len+strlen(str)]=0;

	int type,number,newType,newNumber,needType,needNumber;
	Day day,needDay,newDay;
	char detail[500],newDetail[500];

	//�����޸ĺ������
	printf("�밴�����¸�ʽ������Ҫ�޸ĵ���Ŀ��Ϣ��\n");
	printf("	[ʱ��(��.��.��.ʱ.��)+����(1/0 ��ʾ ����/֧��)+����]\n");
	scanf("%d.%d.%d.%d.%d %d %d",&needDay.year,&needDay.mon,&needDay.day,&needDay.hour,&needDay.min,&needType,&needNumber);
	if(judgeData(needDay,needType,needNumber)!=1) {
		printf("������Ϣ���Ϸ�!��Ϣ¼��ʧ��!\n");
		return -1;
	}

	//�����޸ĺ������
	printf("�밴�����¸�ʽ�����޸ĺ����Ŀ��Ϣ\n");
	printf("	[ʱ��(��.��.��.ʱ.��)+����(1/0 ��ʾ ����/֧��)+����+��ϸ]\n");
	scanf("%d.%d.%d.%d.%d %d %d %s",&newDay.year,&newDay.mon,&newDay.day,&newDay.hour,&newDay.min,&newType,&newNumber,&newDetail);
	if(judgeData(newDay,newType,newNumber)!=1) {
		printf("������Ϣ���Ϸ�!��Ϣ¼��ʧ��!\n");
		return -1;
	}

	//��ԭ�����ļ��г���Ҫ�滻��������ֱ�ӿ�������ʱ�ļ��� ���滻��ֱ������
	FILE *userFile=fopen(name,"r");//r+��ʾ��ԭ�ĵĻ����϶�����
	FILE *temp=fopen("temp.txt","w+");
	int flag=0;
	while(fscanf(userFile,"%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail)!=EOF) {
		if(day.min==needDay.min&&day.hour==needDay.hour&&needType==type&&needNumber==number&&day.day==needDay.day&&day.mon==needDay.mon&&day.year==needDay.year) {
			//�滻��Ҫ�޸ĵ���һ��
			flag=1;
			fprintf(temp,"%d.%d.%d.%d.%d %d %d %s\n",newDay.year,newDay.mon,newDay.day,newDay.hour,newDay.min,newType,newNumber,newDetail);
		} else {
			//������ֱ�Ӹ���
			fprintf(temp,"%d.%d.%d.%d.%d %d %d %s\n",day.year,day.mon,day.day,day.hour,day.min,type,number,detail);
		}

	}
	fclose(userFile);
	fclose(temp);

	if(flag==0) {
		printf("�Ҳ�����Ӧ��Ŀ��Ϣ!\n");
		return -1;
	}

	//����ٰ���ʱ�ļ�������ԭ�ļ�
	FILE *uFile=fopen(name,"w+");//w+��ʾ����д������
	FILE *tFile=fopen("temp.txt","r");
	while(fscanf(tFile,"%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail)!=EOF) {
		fprintf(uFile,"%d.%d.%d.%d.%d %d %d %s\n",day.year,day.mon,day.day,day.hour,day.min,type,number,detail);
	}
	fclose(uFile);
	fclose(tFile);

}



/**  delet ������ɾ��ԭ����Ϣ
 *	  �û���Ҫ����֮ǰ�Ѽ�¼����Ϣ��Ϊ��������
 *	  ����ɹ��ҵ���Ϣ��ɾ�������ز����ɹ���ʾ
 *    ʧ���򲻻�ɾ����Ϣ
 **/
int delet(int userNumber) {

// ͨ������Ա�ļ���Ӧ���б��ȡ��Ӧ�û��Ĵ洢�ļ�����
	char name[20];
	FILE *nameFile=fopen("administrator.txt","r");
	for(int i=1; i<=userNumber; i++) {
		fscanf(nameFile,"%s",name);
	}
	const char str[] = ".txt";
	int len = strlen(name);
	for(int i=0; i<strlen(str); i++) {
		name[len+i] = str[i];
	}
	name[len+strlen(str)]=0;

	int flag=0;
	int type,number,newType,newNumber,needType,needNumber;
	Day day,needDay,newDay;
	char detail[500],newDetail[500];

	//�����޸ĺ������
	printf("�밴�����¸�ʽ������Ҫɾ������Ŀ��Ϣ\n");
	printf("	[ʱ��(��.��.��.ʱ.��)+����(1/0 ��ʾ ����/֧��)+����]\n");
	scanf("%d.%d.%d.%d.%d %d %d",&needDay.year,&needDay.mon,&needDay.day,&needDay.hour,&needDay.min,&needType,&needNumber);
	if(judgeData(needDay,needType,needNumber)!=1) {
		printf("������Ϣ���Ϸ�!��Ϣ¼��ʧ��!\n");
		return -1;
	}

	FILE *userFile=fopen(name,"r");//r��ʾ��ԭ�ĵĻ����϶�����
	FILE *temp=fopen("temp.txt","w+");
	while(fscanf(userFile,"%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail)!=EOF) {
		if(day.min==needDay.min&&day.hour==needDay.hour&&needType==type&&needNumber==number&&day.day==needDay.day&&day.mon==needDay.mon&&day.year==needDay.year) {
			//ɾ����
			printf("�ɹ�ɾ��!\n");
			flag=1;
		} else
			fprintf(temp,"%d.%d.%d.%d.%d %d %d %s\n",day.year,day.mon,day.day,day.hour,day.min,type,number,detail);//������ֱ�Ӹ���
	}

	fclose(userFile);
	fclose(temp);

	if(flag==0) {
		printf("û���ҵ���Ӧ���ݣ�ɾ��ʧ��\n");
		return -1;
	}

	//����ٰ���ʱ�ļ�������ԭ�ļ�
	FILE *uFile=fopen(name,"w+");//w+��ʾ����д������
	FILE *tFile=fopen("temp.txt","r");
	while(fscanf(tFile,"%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail)!=EOF) {
		fprintf(uFile,"%d.%d.%d.%d.%d %d %d %s\n",day.year,day.mon,day.day,day.hour,day.min,type,number,detail);
	}
	fclose(uFile);
	fclose(tFile);
	return 1;
}



/**  quit ���������˳�����
 *
 **/
void quit() {
	system("cls");
	printf("��л����ʹ��!\n");
	Sleep(2000);
	exit(0);
}



/**  addUser ����ֻ�ṩ����Աʹ��
 *	  ��������û�
 *
 **/
int addUser() {

	printf("�밴�����¸�ʽ��������Ҫ��ӵ��û���������:\n");
	printf("<�û��� ����>\n");
	char username[20],password[20];
	scanf("%s %s",username,password);
	FILE *nameFile=fopen("administrator.txt","a+");
	fprintf(nameFile,"%s %s\n",username,password);
	fclose(nameFile);
}


/**  displayUser ����������ʾ����ʹ�õ��û�
 *		�����᷵�ؿ���ʹ�õ��û����û���������
 *
 **/
int displayUser() {
	char username[20],password[20];
	FILE *nameFile=fopen("administrator.txt","r");
	while(fscanf(nameFile,"%s %s",username,password)!=EOF) {
		printf("�û���%s ����%s\n",username,password);
	}
	fclose(nameFile);
}


/**  deleteUser ����ֻ�ṩ����Աʹ��
 *	 ����ɾ���Ѿ����ڵ��û�
 *
 **/
int deleteUser() {
	printf("�밴�����¸�ʽ��������Ҫɾ�����û���������:\n");
	printf("<�û��� ����>\n");
	char username[20],password[20],un[20],pw[20];
	scanf("%s %s",username,password);

	int flag=0;
	FILE *nameFile=fopen("administrator.txt","a+");
	FILE *tempFile=fopen("tempFile.txt","w+");
	while(fscanf(nameFile,"%s %s",un,pw)!=EOF) {
		if(strcmp(un,username)==0&&strcmp(pw,password)==0) {
			flag=1;
			continue;
		}

		fprintf(tempFile,"%s %s\n",un,pw);
	}
	fclose(nameFile);
	fclose(tempFile);

	if(flag==0) {
		printf("�û����������벻��ȷ��ɾ��ʧ��!\n");
		return -1;
	}

	FILE *nFile=fopen("administrator.txt","w+");
	FILE *tFile=fopen("tempFile.txt","r");
	while(fscanf(tFile,"%s %s",un,pw)!=EOF) {
		fprintf(nFile,"%s %s\n",un,pw);
	}
	fclose(nFile);
	fclose(tFile);
	//ɾ����Ӧ���û��ļ�
	const char str[] = ".txt";
	int len = strlen(username);
	for(int i=0; i<strlen(str); i++) {
		username[len+i] = str[i];
	}
	username[len+strlen(str)]=0;
	remove(username);

	return 1;
}

/**  displayData ����������ʾ�Ѿ���¼����Ϣ
 *		��ʾ������Ϣ���ͳ�������֧���������ܺ�
 *
 **/
int displayData(int userNumber) {
// ͨ������Ա�ļ���Ӧ���б��ȡ��Ӧ�û��Ĵ洢�ļ�����
	char name[20];
	FILE *nameFile=fopen("administrator.txt","r");
	for(int i=1; i<=userNumber; i++) {
		fscanf(nameFile,"%s",name);
	}
	const char str[] = ".txt";
	int len = strlen(name);
	for(int i=0; i<strlen(str); i++) {
		name[len+i] = str[i];
	}
	name[len+strlen(str)]=0;

	int type,number;
	Day day;
	int inSum=0,outSum=0;
	char detail[500],theType='-';
	FILE *userFile=fopen(name,"r");
	while(fscanf(userFile,"%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail)!=EOF) {
		if(type==1) {
			theType='+';
			inSum+=number;
		}
		outSum+=number;
		printf("%d.%d.%d.%d.%d %c%d %s\n",day.year,day.mon,day.day,day.hour,day.min,theType,number,detail);
	}
	printf("Ŀǰ���ܻ���Ϊ: %dԪ,�������� %dԪ,֧�� %dԪ  \n",inSum-outSum,inSum,outSum);
}



/**  display ��������������
 *   �ڵ�¼�ɹ�֮���ˢ�½���
 *	 ��Ϊ��ͨ�û�����͹���Ա����
 *	 �û������ڲ�ͬ�Ľ��������ʾ���в�ͬ����
 *
 **/
void display() {
	printf("------------��ӭʹ�ü򵥼��˱�С����!----------\n");
	int userNumber=login_in();

	//��¼�ɹ�
	system("cls");
	int flag;//�û�����Ĳ�����
	if(userNumber==1||userNumber==2) { //��ͨ�û���Ĭ���û�
		printf("��ӭ��������������!\n");
		
		int time=0;
		while(1) {
			printf(" ______________________________________________ \n");
			printf("|**********ѡ������Ҫ�Ĳ���(ѡ�����)**********|\n");
			printf("|       1.д����Ŀ��Ϣ   2.�޸���Ŀ��Ϣ        |\n");
			printf("|       3.ɾ����Ŀ��Ϣ   4.������Ŀ��Ϣ        |\n");
			printf("|       5.��ʾ�˻�����   6.�˳�                |\n");
			printf("|______________________________________________|\n");
			scanf("%d",&flag);
			switch(flag) {
				case 1:
					recording(userNumber);
					time++;
					break;
				case 2:
					rewrite(userNumber);
					time++;
					break;
				case 3:
					delet(userNumber);
					time++;
					break;
				case 4:
					seach(userNumber);
					time++;
					break;
				case 5:
					displayData(userNumber);
					time++;
					break;
				case 6:
					quit();
					break;
				default:
					printf("------����ָ���������������------\n");
					break;
			}
			if(time%5==0&&time!=0)
				system("cls");
		}
	} else if(userNumber==0) { //����Ա�û�
		printf("����Ա�û���¼�ɹ�!��ӭʹ��!\n");
		int time=0;
		while(1) {		
			printf(" ______________________________________________ \n");
			printf("|*********ѡ������Ҫ�Ĳ���(ѡ�����)***********|\n");
			printf("|         1.����û�       2.ɾ���û�          |\n");
			printf("|         3.��ʾ�û��б�   4.�˳�              |\n");
			printf("|______________________________________________|\n");
			scanf("%d",&flag);
			switch(flag) {
				case 1:
					addUser();
					time++;
					break;
				case 2:
					deleteUser();
					time++;
					break;
				case 3:
					displayUser();
					time++;
					break;
				case 4:
					quit();
					break;
				default:
					printf("------����ָ���������������------\n")	;
					break;
			}
			if(time%3==0&&time!=0)
				system("cls");
		}
	}

}


int main() {

	display();
	return 0;
}
