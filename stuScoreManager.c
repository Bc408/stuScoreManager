#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>

#define N 30 //设定系统内管理的学生人数上限为30，可自行修改
char key[11]="1145141919"; //设定管理员密码，可自行修改

typedef struct {
  char name[11]; //GB2312编码下一个中文字符占2字节，名字长度上限为5个字
  char id[11]; //最长支持长10位的学号
  float c;
  float theory;
  float data;
  float math;
} stu;

typedef struct {
  char name[11];
  float score;
} rank;

//当用户键入的字符无效时
void def() {
  printf("\n\n\t\t\t%37s\n","无效输入，请输入合法的功能编号~");
  getch();
}

//基础菜单界面，展示可选择的用户类型
void uniMenu() {
  system("cls");
  printf(
    "\t\t\t **********   学生成绩管理系统  ***********\n\n"
    "\t\t\t|==========================================|\n"
    "\t\t\t|*************1.  我是学生  ***************|\n"
    "\t\t\t|*************2.  我是教师  ***************|\n"
    "\t\t\t|*************0.  退出系统  ***************|\n"
    "\t\t\t|==========================================|\n"
    "\t\t\t|******************************************|\n"
    "\n\t\t\t             请问您的身份是："
  );
}

//进阶菜单界面，展示所有可使用的功能
void proMenu() {
  system("cls");
  printf(
    "\t\t\t **********   学生成绩管理系统  ***********\n\n"
    "\t\t\t|==========================================|\n"
    "\t\t\t|*************1.  录入信息  ***************|\n"
    "\t\t\t|*************2.  查询成绩  ***************|\n"
    "\t\t\t|*************3.  修改信息  ***************|\n"
    "\t\t\t|*************4.  添加学生  ***************|\n"
    "\t\t\t|*************5.  删除学生  ***************|\n"
    "\t\t\t|*************6.  显示成绩  ***************|\n"
    "\t\t\t|*************7.    统计    ***************|\n"
    "\t\t\t|*************8.    关于    ***************|\n"
    "\t\t\t|*************0.    退出    ***************|\n"
    "\t\t\t|==========================================|\n"
    "\t\t\t|******************************************|\n"
    "\n\t\t\t               请选择功能："
  );
}

//依序录入大量信息
void inputAll() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","ab"))==NULL) {
    printf("无法打开数据文件！\n");
    exit(0);
  }
  stu info;
  printf("请输入学生信息：\n");
  for (int i=0;i<N;i++) { //确保录入信息量不高于上限
    printf("请输入姓名（填入End以结束录入）：");
    scanf("%10s",info.name);
    if (!strcmp(info.name,"End")||!strcmp(info.name,"end")) {
      printf("信息录入结束~\n");
      break;
    }
    printf("请输入学号：");
    scanf("%10s",info.id);
    printf("请输入c语言成绩：");
    scanf("%f",&info.c);
    printf("请输入编译原理成绩：");
    scanf("%f",&info.theory);
    printf("请输入数据库成绩：");
    scanf("%f",&info.data);
    printf("请输入离散数学成绩：");
    scanf("%f",&info.math);
    fwrite(&info,sizeof(stu),1,fp); //将成绩信息写入文件
    printf("当前信息录入成功！\n");
    if (i==N-1) {
      printf("已录入学生数量已达系统上限，已自动结束录入！");
      break;
    }
    getch();
    system("cls");
  }
  fclose(fp);
  getch();
}

//按姓名或学号的方式查询成绩，显示第一组匹配的信息
void searchInfo() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("无法打开数据文件！\n");
    exit(0);
  }
  char chosen;
  while (1) {
    printf("请选择查询方式：\n");
    printf("1.姓名  2.学号");
    chosen=getch();
    if (chosen!='1'&&chosen!='2') {
      def();
      system("cls");
    } else break;
  }
  stu info;
  char target[11];
  if (chosen=='1') printf("\n请输入需要查询的学生姓名: ");
  else printf("\n请输入需要查询的学生学号: ");
  scanf("%10s",target);
  while (fread(&info,sizeof(stu),1,fp)) { //从文件中读取成绩信息
    char pickOne[11]=""; //使pickOne成为只有'\0'的字符串
    strcpy(pickOne,chosen=='1'? info.name:info.id);
    if (!strcmp(pickOne,target)) {
      printf("学生的信息如下:\n");
      printf(
        "姓名：%s\n学号：%s\nC语言成绩：%.2f\n编译原理成绩：%.2f\n数据库成绩：%.2f\n离散数学成绩：%.2f\n",
        info.name,info.id,info.c,info.theory,info.data,info.math
      );
      break;
    }
  }
  if (feof(fp)) printf("学生不存在，查找失败!");
  fclose(fp);
  getch();
}

//先查询学生信息，修改第一组匹配的信息，并显示修改前后的结果
void modifyInfo() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb+"))==NULL) {
    printf("无法打开数据文件！\n");
    exit(0);
  }
  char chosen;
  while (1) {
    printf("请选择信息检索方式：\n");
    printf("1.姓名  2.学号");
    chosen=getch();
    if (chosen!='1'&&chosen!='2') {
      def();
      system("cls");
    } else break;
  }
  stu info;
  char target[11];
  if (chosen=='1') printf("\n请输入要修改信息的学生姓名: ");
  else printf("\n请输入要修改信息的学生学号: ");
  scanf("%10s",target);
  int isFound=0;
  while (fread(&info,sizeof(stu),1,fp)) {
    char pickOne[11]="";
    strcpy(pickOne,chosen=='1'? info.name:info.id);
    if (!strcmp(pickOne,target)) {
      isFound++;
      printf("修改前的学生信息：\n");
      printf("%10s %10s %10s %10s %10s %10s\n","姓名","学号","C语言","编译原理","数据库","离散数学");
      printf("%10s %10s %10.2f %10.2f %10.2f %10.2f\n",info.name,info.id,info.c,info.theory,info.data,info.math);
      while (1) {
        printf("请选择您要修改的信息：\n");
        char choice;
        printf("1.姓名  2.学号  3.C语言成绩  4.编译原理成绩  5.数据库成绩  6.离散数学成绩  0.退出\n");
        choice=getch();
        if (choice=='0') break;
        switch (choice) {
          case '1':
            printf("将姓名修改为：");
            scanf("%10s",info.name);
            break;
          case '2':
            printf("将学号修改为：");
            scanf("%10s",info.id);
            break;
          case '3':
            printf("将c语言成绩修改为：");
            scanf("%f",&info.c);
            break;
          case '4':
            printf("将编译原理成绩修改为：");
            scanf("%f",&info.theory);
            break;
          case '5':
            printf("将数据库成绩修改为：");
            scanf("%f",&info.data);
            break;
          case '6':
            printf("将离散数学成绩修改为：");
            scanf("%f",&info.math);
            break;
          default:
            def();
            break;
        }
      }
      printf("\n修改后的学生的信息如下：");
      printf("\n%10s %10s %6s %6s %6s %6s\n","姓名","学号","C语言","编译原理","数据库","离散数学");
      printf("%10s %10s %6.2f %6.2f %6.2f %6.2f\n",info.name,info.id,info.c,info.theory,info.data,info.math);
      fseek(fp,-(int)sizeof(stu),1); //负号表示后退，1表示文件当前位置
      fwrite(&info,sizeof(stu),1,fp); //再重新写入，同时把之前的要修改的覆盖掉
      printf("修改成功~");
      break;
    }
  }
  if (!isFound) printf("\n学生不存在，修改失败!");
  fclose(fp);
  getch();
}

//输入学生的的各项成绩，并插入到指定行数，当指定的位置数据为空，将其添加到全文件的最后一行
void insertInfo() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("无法打开数据文件！\n");
    exit(0);
  }
  stu info,infos[N];
  int len=0;
  for (;fread(&infos[len],sizeof(stu),1,fp);len++) {}
  fclose(fp);
  if (len>=N) {
    printf("学生数量已达上限，无法添加学生信息！\n");
    exit(0);
  }
  printf("请输入要添加的学生姓名：");
  scanf("%10s",info.name);
  printf("请输入学号：");
  scanf("%10s",info.id);
  printf("请输入c语言成绩：");
  scanf("%f",&info.c);
  printf("请输入编译原理成绩：");
  scanf("%f",&info.theory);
  printf("请输入数据库成绩：");
  scanf("%f",&info.data);
  printf("请输入离散数学成绩：");
  scanf("%f",&info.math);
  int line=1;
  printf("请输入要插入到的行数：");
  while (1) {
    scanf("%d",&line);
    if (line>=1&&line<=N) break;
    else printf("\n请确保行数不为负且不大于30，再次输入：");
  }
  if (line<=len) {
    printf("\n即将把数据插入至第%d行\n",line);
    for (int i=len-1;i>=line-1;i--) infos[i+1]=infos[i];
    infos[line-1]=info;                     
    len++; //增加一个空间，否则会少一个学生的数据
    if ((fp=fopen("student.dat","wb"))==NULL) {
      printf("无法打开数据文件！\n");
      exit(0);
    }
    for (int i=0;i<len;i++) fwrite(&infos[i],sizeof(stu),1,fp);
  } else {
    printf("\n第%d行为空，即将把数据添加至最末行\n",line);
    if ((fp=fopen("student.dat","ab"))==NULL) {
      printf("无法打开数据文件！\n");
      exit(0);
    }
    fwrite(&info,sizeof(stu),1,fp);
  }
  printf("信息添加成功~");
  fclose(fp);
  getch();
}

//先查询学生信息，删除最后一个匹配的信息
void deleteInfo() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb+"))==NULL) {
    printf("无法打开数据文件！\n");
    exit(0);
  }
  char chosen;
  while (1) {
    printf("请选择信息检索方式：\n");
    printf("1.姓名  2.学号");
    chosen=getch();
    if (chosen!='1'&&chosen!='2') {
      def();
      system("cls");
    } else break;
  }
  stu infos[N];
  char target[11];
  if (chosen=='1') printf("\n请输入要删除信息的学生姓名: ");
  else printf("\n请输入要删除信息的学生学号: ");
  scanf("%10s",target);
  int len=0,isFound=-1;
  for (;fread(&infos[len],sizeof(stu),1,fp);len++) {
    char pickOne[11]="";
    strcpy(pickOne,chosen=='1'? infos[len].name:infos[len].id);
    if (!strcmp(pickOne,target)) isFound=len;
  }
  fclose(fp);
  if (isFound>=0) {  
    if ((fp=fopen("student.dat","wb"))==NULL) {
      printf("无法打开数据文件！\n");
      exit(0);
    }
    for (int i=0;i<len-1;i++) {
      if (i==isFound) continue; //写入文件时跳过目标信息，实现删除效果
      fwrite(&infos[i],sizeof(stu),1,fp);
    }
    printf("删除成功~");
    fclose(fp);
  } else printf("学生不存在，删除失败!\n");
  getch();
}

//打印所有学生成绩单
void printAll() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("无法打开数据文件！\n");
    exit(0);
  }
  stu info;
  printf("%10s %10s %10s %10s %10s %10s\n","姓名","学号","C语言","编译原理","数据库","离散数学");
  while (fread(&info,sizeof(stu),1,fp)) {
    printf("%10s %10s %10.2f %10.2f %10.2f %10.2f\n",info.name,info.id,info.c,info.theory,info.data,info.math);
  }
  fclose(fp);
  getch();
}

//依次输出4个科目成绩的最高分、最低分和平均分
void threeValues() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("无法打开数据文件！\n");
    exit(0);
  }
  stu infos[N];
  float scores[N][4];
  int len=0;
  for (;fread(&infos[len],sizeof(stu),1,fp);len++) {
    scores[len][0]=infos[len].c;
    scores[len][1]=infos[len].theory;
    scores[len][2]=infos[len].data;
    scores[len][3]=infos[len].math;
  }
  fclose(fp);
  printf("总成绩排名：\n");
  printf("%9s %18s %17s %10s\n","科目","最高分","最低分","平均分");
  char subjects[4][11]={"c语言：","编译原理：","数据库：","离散数学："}; 
  for (int i=0;i<4;i++) {
    float highest=0,lowest=0,sum=0;
    int hp=0,lp=0;
    for (int j=0;j<len;j++) {
      if (scores[j][i]>highest) {
        highest=scores[j][i];
        hp=j;
      }
      if (scores[j][i]<lowest) {
        lowest=scores[j][i];
        lp=j;
      }
      sum+=scores[j][i];
    }
    float average=sum/len;
    printf("%10s %10s %6.2f %10s %6.2f %10.2f\n",subjects[i],infos[hp].name,highest,infos[lp].name,lowest,average);
  }
  getch();
}

//统计总成绩各个分数段的学生数量
void cntByScore() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("无法打开数据文件！\n");
    exit(0);
  }
  stu info;
  float sum[N];
  int len=0;
  for (;fread(&info,sizeof(stu),1,fp);len++) {
    sum[len]=info.c+info.theory+info.data+info.math;
  }
  int a=0,b=0,c=0,d=0,e=0;
  for (int i=0;i<len;i++) {
    if (sum[i]>=360) a++;
    else {
      if (sum[i]>=320) b++;
      else {
        if (sum[i]>=280) c++;
        else {
          if (sum[i]>=240) d++;
          else e++;
        }
      }
    } 
  }
  printf(
    "优秀（360分及以上）：%d\n"
    "良好（320分 - 359分）：%d\n"
    "中等（280分 - 319分）：%d\n"
    "及格（240分 - 279分）：%d\n"
    "不及格（240分以下）：%d\n",
    a,b,c,d,e
  );
  getch();
}

//按照总成绩的降序输出学生成绩排名
void rankSum() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("无法打开数据文件！\n");
    exit(0);
  }
  stu temp;
  rank ran[N];
  int len=0;
  for (;fread(&temp,sizeof(stu),1,fp);len++) {
    ran[len].score=temp.c+temp.theory+temp.data+temp.math;
    ran[len].name[0]='\0';
    strcpy(ran[len].name,temp.name);
  }
  //运用选择法排序
  int maxp=0;
  for (int i=0;i<len;i++) {
    maxp=i;
    for (int j=i+1;j<len;j++) {
      if (ran[j].score>ran[maxp].score) maxp=j;
    }
    printf("第%d名 %10s %10.2f\n",i+1,ran[maxp].name,ran[maxp].score);
    float temp=ran[maxp].score;
    ran[maxp].score=ran[i].score;
    ran[i].score=temp;
  }
  getch();
}

//按照各个科目成绩的降序输出各科目学生成绩排名
void rankSubjects() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("无法打开数据文件！\n");
    exit(0);
  }
  stu temp;
  rank ran[4][N];
  char subjects[4][19]={"c语言成绩排名：","编译原理成绩排名：","数据库成绩排名：","离散数学成绩排名："};
  int len=0;
  for (;fread(&temp,sizeof(stu),1,fp);len++) {
    for (int i=0;i<4;i++) {
      ran[i][len].name[0]='\0';
      strcpy(ran[i][len].name,temp.name);
    }
    ran[0][len].score=temp.c;
    ran[1][len].score=temp.theory;
    ran[2][len].score=temp.data;
    ran[3][len].score=temp.math;
  }
  //运用冒泡法排序
  for (int i=0;i<4;i++) {
    printf("%18s\n",subjects[i]);
    for (int j=0;j<len-1;j++) {
      for (int k=len-1;k>j;k--) {
        if (ran[i][k-1].score<ran[i][k].score) {
          float temp=ran[i][k-1].score;
          ran[i][k-1].score=ran[i][k].score;
          ran[i][k].score=temp;
        }
      }
    }
    for (int j=0;j<len;j++) {
      printf("第%d名 %10s %10.2f\n",j+1,ran[i][j].name,ran[i][j].score);
    }
  }
  getch();
}

//展示并执行统计功能的小菜单
void statistic() {
  char chosen;
  while (1) {
    system("cls");
    printf(
      "1.查询各科目最高分、最低分和平均分\n"
      "2.统计总成绩各个分数段的学生数量\n"
      "3.按照总成绩的降序输出学生成绩排名\n"
      "4.按照各个科目成绩的降序输出各科目学生成绩排名\n"
      "0.退出"
    );
    chosen=getch();
    if (chosen=='0') return;
    switch (chosen) {
      case '1':
        threeValues();
        break;
      case '2':
        cntByScore();
        break;
      case '3':
        rankSum();
        break;
      case '4':
        rankSubjects();
        break;
      default:
        def();
        break;
    }
  }
}

//关于作者与系统
void about() {
  system("cls");
  printf(
    "+------------------------------------+\n"
    "| About stuScoreManager              |\n"
    "|                                    |\n"
    "| [stuScoreManager] Version 1.0.6    |\n"
    "|                                    |\n"
    "| Follow auther on social media:     |\n"
    "| [Github] @Bc408                    |\n"
    "|                                    |\n"
    "| Thank you for using stuScoreManage |\n"
    "+------------------------------------+\n"
  );
  getch();
}

//执行进阶菜单界面所选择的功能
void proMode() {
  char proChoice;
  while (1) {
    proMenu();
    proChoice=getch();
    if (proChoice=='0') return;
    switch (proChoice) {
      case '1':
        inputAll();
        break;
      case '2':
        searchInfo();
        break;
      case '3':
        modifyInfo();
        break;
      case '4':
        insertInfo();
        break;
      case '5':
        deleteInfo();
        break;
      case '6':
        printAll();
        break;
      case '7':
        statistic();
        break;
      case '8':
        about();
        break;
      default:
        def();
        break;
    }
  }
}

//进入基础菜单
int main() {
  char uniChoice;
  while (1) {
    uniMenu();
    uniChoice=getch();
    if (uniChoice=='0') break;
    switch (uniChoice) {
      case '1': //以学生身份使用系统
        searchInfo();
        break;
      case '2': //以教师身份使用系统
        system("cls");
        char password[11];
        printf("请输入管理员密码：");
        scanf("%10s",password);
        if (!strcmp(password,key)) {
          proMode();
        } else {
          printf("密码错误！\n");
          getch();
        }
        break;
      default:
        def();
        break;
    }
  }
  printf("\n\n\t\t\t%29s\n","感谢使用，再见！");
}
