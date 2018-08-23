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


/** judge 函数判断输入的用户名和密码是否正确
 *   返回值：
 *	-1表示不正确
 *	0表示为管理员用户
 *	1表示为默认用户
 * 	>1表示为普通用户
 **/
int judge(char username[20],char password[20]) {
	char rightName[20],rightPassword[20];
	FILE *nameFile=fopen("administrator.txt","r");
	int userNumber;
	if(strcmp(username,"administrator")==0) {
		if(strcmp(password,"123456")==0) {
			printf("正在登录.......\n");
			Sleep(1000);
			printf("登录成功!\n");
			Sleep(1000);
			return 0;//管理员
		}
	} else {
		for(userNumber=1; fscanf(nameFile,"%s %s\n",rightName,rightPassword)!=EOF; userNumber++) {
			if(strcmp(username,rightName)==0)
				if(strcmp(password,rightPassword)==0) {
					printf("正在登录.......\n");
					Sleep(1000);
					printf("登录成功!\n");
					Sleep(1000);
					return userNumber;//普通用户
				}
		}
		printf("密码错误或用户名不存在!\n");
		return -1;//错误
	}
}




/** login_in 函数为登录函数
 *  参数 time 表示输入密码错误的次数
 *	错误达到3次时强制退出程序
 *	函数返回值为 judge函数的返回值
 **/
int login_in() {
	int time=0,judgeFlag=0;
	char enter_name[20],password[20];

	printf("          <默认的用户名为 user0,密码是 12345>          \n");
	while(time<=3) {
		if(time==3) {
			printf("你已经输入错误3次!强制退出程序!");
			Sleep(1000);
			exit(0);
		}

		printf("请输入用户名:\n");
		scanf("%s",&enter_name);
		int i=0;

		printf("请输入你的密码:\n");
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




/** judgeData 函数用于判断输入数据是否合理 
 *	合理返回1
 *  不合理返回-1
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



/** recording 函数用于输入需要记录的信息
 *	按照提示的格式输入和存储信息
 *  由于是添加信息所以是在原数据的末尾进行添加
 *	函数不改变已有数据
 *	可以进行连续输入
 *
 **/
int recording(int userNumber) {
	int type,number,enterFlag;
	Day day;
	char detail[500];

// 通过管理员文件对应的列表获取对应用户的存储文件名称
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

	FILE *userFile=fopen(name,"a+");//a+表示在原文件的末尾写入内容
	printf("请按照以下格式输入账目信息:\n");
	printf("	[时间(年.月.日.时.分)+类型(1/0 表示 收入/支出)+数额+明细]\n");
	while(1) {

		scanf("%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail);
		if(judgeData(day,type,number)!=1) {
			printf("输入信息不合法!信息录入失败!\n");
			return -1;
		}

		fprintf(userFile,"%d.%d.%d.%d.%d  %d %d %s\n",day.year,day.mon,day.day,day.hour,day.min,type,number,detail);
		printf("信息录入成功!是否继续输入? <1/0>\n");
		scanf("%d",&enterFlag);
		if(enterFlag!=1)
			break;
	}
	fclose(nameFile);
	fclose(userFile);

	return 1;
}


/**  seach 函数用于查找相关内容
 *	 输入需要查找的内容
 *	 查找成功则返回信息的详细内容
 *	 否则返回失败信息
 *
 **/
int seach(int userNumber) {

// 通过管理员文件对应的列表获取对应用户的存储文件名称
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
	//输入需要查找的内容
	printf("请按照以下格式输入需要查找的账目信息\n");
	printf("	[时间(年.月.日.时.分)]\n");
	scanf("%d.%d.%d.%d.%d",&seachDay.year,&seachDay.mon,&seachDay.day,&seachDay.hour,&seachDay.min);

	if(judgeData(seachDay)!=1) {
		printf("输入信息不合法!信息录入失败!\n");
		return -1;
	}
	char Type='-';
	FILE *userFile=fopen(name,"r");//r表示在原文的基础上读内容
	while(fscanf(userFile,"%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail)!=EOF) {
		if(day.min==seachDay.min && day.hour==seachDay.hour && day.day==seachDay.day && day.mon==seachDay.mon && day.year==seachDay.year) {
			if(type==1)
				Type='+';
			printf("搜索结果:%d.%d.%d.%d.%d %c%d %s\n",day.year,day.mon,day.day,day.hour,day.min,Type,number,detail);
			return 1;
		}

	}
	fclose(nameFile);
	fclose(userFile);

	printf("无法找到账目信息！\n");
	return -1;

}



/**  rewrite 函数负责修改原有信息
 *	  用户需要输入之前已记录的信息作为查找条件
 *	  再输入修改后的内容作为修改条件
 *	  如果查找失败则不会进行修改
 *
 **/
int rewrite(int userNumber) {

// 通过管理员文件对应的列表获取对应用户的存储文件名称
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

	//输入修改后的内容
	printf("请按照以下格式输入需要修改的账目信息吧\n");
	printf("	[时间(年.月.日.时.分)+类型(1/0 表示 收入/支出)+数额]\n");
	scanf("%d.%d.%d.%d.%d %d %d",&needDay.year,&needDay.mon,&needDay.day,&needDay.hour,&needDay.min,&needType,&needNumber);
	if(judgeData(needDay,needType,needNumber)!=1) {
		printf("输入信息不合法!信息录入失败!\n");
		return -1;
	}

	//输入修改后的内容
	printf("请按照以下格式输入修改后的账目信息\n");
	printf("	[时间(年.月.日.时.分)+类型(1/0 表示 收入/支出)+数额+明细]\n");
	scanf("%d.%d.%d.%d.%d %d %d %s",&newDay.year,&newDay.mon,&newDay.day,&newDay.hour,&newDay.min,&newType,&newNumber,&newDetail);
	if(judgeData(newDay,newType,newNumber)!=1) {
		printf("输入信息不合法!信息录入失败!\n");
		return -1;
	}

	//把原来的文件中除了要替换的行以外直接拷贝到临时文件中 ，替换行直接输入
	FILE *userFile=fopen(name,"r");//r+表示在原文的基础上读内容
	FILE *temp=fopen("temp.txt","w+");
	int flag=0;
	while(fscanf(userFile,"%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail)!=EOF) {
		if(day.min==needDay.min&&day.hour==needDay.hour&&needType==type&&needNumber==number&&day.day==needDay.day&&day.mon==needDay.mon&&day.year==needDay.year) {
			//替换需要修改的那一行
			flag=1;
			fprintf(temp,"%d.%d.%d.%d.%d %d %d %s\n",newDay.year,newDay.mon,newDay.day,newDay.hour,newDay.min,newType,newNumber,newDetail);
		} else {
			//其他行直接复制
			fprintf(temp,"%d.%d.%d.%d.%d %d %d %s\n",day.year,day.mon,day.day,day.hour,day.min,type,number,detail);
		}

	}
	fclose(userFile);
	fclose(temp);

	if(flag==0) {
		printf("找不到对应账目信息!\n");
		return -1;
	}

	//最后再把临时文件拷贝回原文件
	FILE *uFile=fopen(name,"w+");//w+表示重新写新内容
	FILE *tFile=fopen("temp.txt","r");
	while(fscanf(tFile,"%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail)!=EOF) {
		fprintf(uFile,"%d.%d.%d.%d.%d %d %d %s\n",day.year,day.mon,day.day,day.hour,day.min,type,number,detail);
	}
	fclose(uFile);
	fclose(tFile);

}



/**  delet 函数负删除原有信息
 *	  用户需要输入之前已记录的信息作为查找条件
 *	  如果成功找到信息则删除并返回操作成功提示
 *    失败则不会删除信息
 **/
int delet(int userNumber) {

// 通过管理员文件对应的列表获取对应用户的存储文件名称
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

	//输入修改后的内容
	printf("请按照以下格式输入需要删除的账目信息\n");
	printf("	[时间(年.月.日.时.分)+类型(1/0 表示 收入/支出)+数额]\n");
	scanf("%d.%d.%d.%d.%d %d %d",&needDay.year,&needDay.mon,&needDay.day,&needDay.hour,&needDay.min,&needType,&needNumber);
	if(judgeData(needDay,needType,needNumber)!=1) {
		printf("输入信息不合法!信息录入失败!\n");
		return -1;
	}

	FILE *userFile=fopen(name,"r");//r表示在原文的基础上读内容
	FILE *temp=fopen("temp.txt","w+");
	while(fscanf(userFile,"%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail)!=EOF) {
		if(day.min==needDay.min&&day.hour==needDay.hour&&needType==type&&needNumber==number&&day.day==needDay.day&&day.mon==needDay.mon&&day.year==needDay.year) {
			//删除行
			printf("成功删除!\n");
			flag=1;
		} else
			fprintf(temp,"%d.%d.%d.%d.%d %d %d %s\n",day.year,day.mon,day.day,day.hour,day.min,type,number,detail);//其他行直接复制
	}

	fclose(userFile);
	fclose(temp);

	if(flag==0) {
		printf("没有找到对应数据，删除失败\n");
		return -1;
	}

	//最后再把临时文件拷贝回原文件
	FILE *uFile=fopen(name,"w+");//w+表示重新写新内容
	FILE *tFile=fopen("temp.txt","r");
	while(fscanf(tFile,"%d.%d.%d.%d.%d %d %d %s",&day.year,&day.mon,&day.day,&day.hour,&day.min,&type,&number,&detail)!=EOF) {
		fprintf(uFile,"%d.%d.%d.%d.%d %d %d %s\n",day.year,day.mon,day.day,day.hour,day.min,type,number,detail);
	}
	fclose(uFile);
	fclose(tFile);
	return 1;
}



/**  quit 函数用于退出程序
 *
 **/
void quit() {
	system("cls");
	printf("感谢您的使用!\n");
	Sleep(2000);
	exit(0);
}



/**  addUser 函数只提供管理员使用
 *	  用于添加用户
 *
 **/
int addUser() {

	printf("请按照以下格式输入你所要添加的用户名和密码:\n");
	printf("<用户名 密码>\n");
	char username[20],password[20];
	scanf("%s %s",username,password);
	FILE *nameFile=fopen("administrator.txt","a+");
	fprintf(nameFile,"%s %s\n",username,password);
	fclose(nameFile);
}


/**  displayUser 函数用于显示可以使用的用户
 *		函数会返回可以使用的用户的用户名和密码
 *
 **/
int displayUser() {
	char username[20],password[20];
	FILE *nameFile=fopen("administrator.txt","r");
	while(fscanf(nameFile,"%s %s",username,password)!=EOF) {
		printf("用户名%s 密码%s\n",username,password);
	}
	fclose(nameFile);
}


/**  deleteUser 函数只提供管理员使用
 *	 用于删除已经存在的用户
 *
 **/
int deleteUser() {
	printf("请按照以下格式输入你所要删除的用户名和密码:\n");
	printf("<用户名 密码>\n");
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
		printf("用户名或者密码不正确，删除失败!\n");
		return -1;
	}

	FILE *nFile=fopen("administrator.txt","w+");
	FILE *tFile=fopen("tempFile.txt","r");
	while(fscanf(tFile,"%s %s",un,pw)!=EOF) {
		fprintf(nFile,"%s %s\n",un,pw);
	}
	fclose(nFile);
	fclose(tFile);
	//删除对应的用户文件
	const char str[] = ".txt";
	int len = strlen(username);
	for(int i=0; i<strlen(str); i++) {
		username[len+i] = str[i];
	}
	username[len+strlen(str)]=0;
	remove(username);

	return 1;
}

/**  displayData 函数用于显示已经记录的信息
 *		显示所有信息后会统计收入和支出并计算总和
 *
 **/
int displayData(int userNumber) {
// 通过管理员文件对应的列表获取对应用户的存储文件名称
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
	printf("目前的总花费为: %d元,其中收入 %d元,支出 %d元  \n",inSum-outSum,inSum,outSum);
}



/**  display 函数负责管理界面
 *   在登录成功之后会刷新界面
 *	 分为普通用户界面和管理员界面
 *	 用户可以在不同的界面根据提示进行不同操作
 *
 **/
void display() {
	printf("------------欢迎使用简单记账本小程序!----------\n");
	int userNumber=login_in();

	//登录成功
	system("cls");
	int flag;//用户输入的操作数
	if(userNumber==1||userNumber==2) { //普通用户和默认用户
		printf("欢迎您来到操作界面!\n");
		
		int time=0;
		while(1) {
			printf(" ______________________________________________ \n");
			printf("|**********选择您需要的操作(选择序号)**********|\n");
			printf("|       1.写入账目信息   2.修改账目信息        |\n");
			printf("|       3.删除账目信息   4.搜索账目信息        |\n");
			printf("|       5.显示账户数据   6.退出                |\n");
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
					printf("------操作指令错误！请重新输入------\n");
					break;
			}
			if(time%5==0&&time!=0)
				system("cls");
		}
	} else if(userNumber==0) { //管理员用户
		printf("管理员用户登录成功!欢迎使用!\n");
		int time=0;
		while(1) {		
			printf(" ______________________________________________ \n");
			printf("|*********选择您需要的操作(选择序号)***********|\n");
			printf("|         1.添加用户       2.删除用户          |\n");
			printf("|         3.显示用户列表   4.退出              |\n");
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
					printf("------操作指令错误！请重新输入------\n")	;
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
