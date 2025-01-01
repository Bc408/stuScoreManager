#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>

#define N 30 //�趨ϵͳ�ڹ����ѧ����������Ϊ30���������޸�
char key[11]="1145141919"; //�趨����Ա���룬�������޸�

typedef struct {
  char name[11]; //GB2312������һ�������ַ�ռ2�ֽڣ����ֳ�������Ϊ5����
  char id[11]; //�֧�ֳ�10λ��ѧ��
  float c;
  float theory;
  float data;
  float math;
} stu;

typedef struct {
  char name[11];
  float score;
} rank;

//���û�������ַ���Чʱ
void def() {
  printf("\n\n\t\t\t%37s\n","��Ч���룬������Ϸ��Ĺ��ܱ��~");
  getch();
}

//�����˵����棬չʾ��ѡ����û�����
void uniMenu() {
  system("cls");
  printf(
    "\t\t\t **********   ѧ���ɼ�����ϵͳ  ***********\n\n"
    "\t\t\t|==========================================|\n"
    "\t\t\t|*************1.  ����ѧ��  ***************|\n"
    "\t\t\t|*************2.  ���ǽ�ʦ  ***************|\n"
    "\t\t\t|*************0.  �˳�ϵͳ  ***************|\n"
    "\t\t\t|==========================================|\n"
    "\t\t\t|******************************************|\n"
    "\n\t\t\t             ������������ǣ�"
  );
}

//���ײ˵����棬չʾ���п�ʹ�õĹ���
void proMenu() {
  system("cls");
  printf(
    "\t\t\t **********   ѧ���ɼ�����ϵͳ  ***********\n\n"
    "\t\t\t|==========================================|\n"
    "\t\t\t|*************1.  ¼����Ϣ  ***************|\n"
    "\t\t\t|*************2.  ��ѯ�ɼ�  ***************|\n"
    "\t\t\t|*************3.  �޸���Ϣ  ***************|\n"
    "\t\t\t|*************4.  ���ѧ��  ***************|\n"
    "\t\t\t|*************5.  ɾ��ѧ��  ***************|\n"
    "\t\t\t|*************6.  ��ʾ�ɼ�  ***************|\n"
    "\t\t\t|*************7.    ͳ��    ***************|\n"
    "\t\t\t|*************8.    ����    ***************|\n"
    "\t\t\t|*************0.    �˳�    ***************|\n"
    "\t\t\t|==========================================|\n"
    "\t\t\t|******************************************|\n"
    "\n\t\t\t               ��ѡ���ܣ�"
  );
}

//����¼�������Ϣ
void inputAll() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","ab"))==NULL) {
    printf("�޷��������ļ���\n");
    exit(0);
  }
  stu info;
  printf("������ѧ����Ϣ��\n");
  for (int i=0;i<N;i++) { //ȷ��¼����Ϣ������������
    printf("����������������End�Խ���¼�룩��");
    scanf("%10s",info.name);
    if (!strcmp(info.name,"End")||!strcmp(info.name,"end")) {
      printf("��Ϣ¼�����~\n");
      break;
    }
    printf("������ѧ�ţ�");
    scanf("%10s",info.id);
    printf("������c���Գɼ���");
    scanf("%f",&info.c);
    printf("���������ԭ��ɼ���");
    scanf("%f",&info.theory);
    printf("���������ݿ�ɼ���");
    scanf("%f",&info.data);
    printf("��������ɢ��ѧ�ɼ���");
    scanf("%f",&info.math);
    fwrite(&info,sizeof(stu),1,fp); //���ɼ���Ϣд���ļ�
    printf("��ǰ��Ϣ¼��ɹ���\n");
    if (i==N-1) {
      printf("��¼��ѧ�������Ѵ�ϵͳ���ޣ����Զ�����¼�룡");
      break;
    }
    getch();
    system("cls");
  }
  fclose(fp);
  getch();
}

//��������ѧ�ŵķ�ʽ��ѯ�ɼ�����ʾ��һ��ƥ�����Ϣ
void searchInfo() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("�޷��������ļ���\n");
    exit(0);
  }
  char chosen;
  while (1) {
    printf("��ѡ���ѯ��ʽ��\n");
    printf("1.����  2.ѧ��");
    chosen=getch();
    if (chosen!='1'&&chosen!='2') {
      def();
      system("cls");
    } else break;
  }
  stu info;
  char target[11];
  if (chosen=='1') printf("\n��������Ҫ��ѯ��ѧ������: ");
  else printf("\n��������Ҫ��ѯ��ѧ��ѧ��: ");
  scanf("%10s",target);
  while (fread(&info,sizeof(stu),1,fp)) { //���ļ��ж�ȡ�ɼ���Ϣ
    char pickOne[11]=""; //ʹpickOne��Ϊֻ��'\0'���ַ���
    strcpy(pickOne,chosen=='1'? info.name:info.id);
    if (!strcmp(pickOne,target)) {
      printf("ѧ������Ϣ����:\n");
      printf(
        "������%s\nѧ�ţ�%s\nC���Գɼ���%.2f\n����ԭ��ɼ���%.2f\n���ݿ�ɼ���%.2f\n��ɢ��ѧ�ɼ���%.2f\n",
        info.name,info.id,info.c,info.theory,info.data,info.math
      );
      break;
    }
  }
  if (feof(fp)) printf("ѧ�������ڣ�����ʧ��!");
  fclose(fp);
  getch();
}

//�Ȳ�ѯѧ����Ϣ���޸ĵ�һ��ƥ�����Ϣ������ʾ�޸�ǰ��Ľ��
void modifyInfo() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb+"))==NULL) {
    printf("�޷��������ļ���\n");
    exit(0);
  }
  char chosen;
  while (1) {
    printf("��ѡ����Ϣ������ʽ��\n");
    printf("1.����  2.ѧ��");
    chosen=getch();
    if (chosen!='1'&&chosen!='2') {
      def();
      system("cls");
    } else break;
  }
  stu info;
  char target[11];
  if (chosen=='1') printf("\n������Ҫ�޸���Ϣ��ѧ������: ");
  else printf("\n������Ҫ�޸���Ϣ��ѧ��ѧ��: ");
  scanf("%10s",target);
  int isFound=0;
  while (fread(&info,sizeof(stu),1,fp)) {
    char pickOne[11]="";
    strcpy(pickOne,chosen=='1'? info.name:info.id);
    if (!strcmp(pickOne,target)) {
      isFound++;
      printf("�޸�ǰ��ѧ����Ϣ��\n");
      printf("%10s %10s %10s %10s %10s %10s\n","����","ѧ��","C����","����ԭ��","���ݿ�","��ɢ��ѧ");
      printf("%10s %10s %10.2f %10.2f %10.2f %10.2f\n",info.name,info.id,info.c,info.theory,info.data,info.math);
      while (1) {
        printf("��ѡ����Ҫ�޸ĵ���Ϣ��\n");
        char choice;
        printf("1.����  2.ѧ��  3.C���Գɼ�  4.����ԭ��ɼ�  5.���ݿ�ɼ�  6.��ɢ��ѧ�ɼ�  0.�˳�\n");
        choice=getch();
        if (choice=='0') break;
        switch (choice) {
          case '1':
            printf("�������޸�Ϊ��");
            scanf("%10s",info.name);
            break;
          case '2':
            printf("��ѧ���޸�Ϊ��");
            scanf("%10s",info.id);
            break;
          case '3':
            printf("��c���Գɼ��޸�Ϊ��");
            scanf("%f",&info.c);
            break;
          case '4':
            printf("������ԭ��ɼ��޸�Ϊ��");
            scanf("%f",&info.theory);
            break;
          case '5':
            printf("�����ݿ�ɼ��޸�Ϊ��");
            scanf("%f",&info.data);
            break;
          case '6':
            printf("����ɢ��ѧ�ɼ��޸�Ϊ��");
            scanf("%f",&info.math);
            break;
          default:
            def();
            break;
        }
      }
      printf("\n�޸ĺ��ѧ������Ϣ���£�");
      printf("\n%10s %10s %6s %6s %6s %6s\n","����","ѧ��","C����","����ԭ��","���ݿ�","��ɢ��ѧ");
      printf("%10s %10s %6.2f %6.2f %6.2f %6.2f\n",info.name,info.id,info.c,info.theory,info.data,info.math);
      fseek(fp,-(int)sizeof(stu),1); //���ű�ʾ���ˣ�1��ʾ�ļ���ǰλ��
      fwrite(&info,sizeof(stu),1,fp); //������д�룬ͬʱ��֮ǰ��Ҫ�޸ĵĸ��ǵ�
      printf("�޸ĳɹ�~");
      break;
    }
  }
  if (!isFound) printf("\nѧ�������ڣ��޸�ʧ��!");
  fclose(fp);
  getch();
}

//����ѧ���ĵĸ���ɼ��������뵽ָ����������ָ����λ������Ϊ�գ�������ӵ�ȫ�ļ������һ��
void insertInfo() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("�޷��������ļ���\n");
    exit(0);
  }
  stu info,infos[N];
  int len=0;
  for (;fread(&infos[len],sizeof(stu),1,fp);len++) {}
  fclose(fp);
  if (len>=N) {
    printf("ѧ�������Ѵ����ޣ��޷����ѧ����Ϣ��\n");
    exit(0);
  }
  printf("������Ҫ��ӵ�ѧ��������");
  scanf("%10s",info.name);
  printf("������ѧ�ţ�");
  scanf("%10s",info.id);
  printf("������c���Գɼ���");
  scanf("%f",&info.c);
  printf("���������ԭ��ɼ���");
  scanf("%f",&info.theory);
  printf("���������ݿ�ɼ���");
  scanf("%f",&info.data);
  printf("��������ɢ��ѧ�ɼ���");
  scanf("%f",&info.math);
  int line=1;
  printf("������Ҫ���뵽��������");
  while (1) {
    scanf("%d",&line);
    if (line>=1&&line<=N) break;
    else printf("\n��ȷ��������Ϊ���Ҳ�����30���ٴ����룺");
  }
  if (line<=len) {
    printf("\n���������ݲ�������%d��\n",line);
    for (int i=len-1;i>=line-1;i--) infos[i+1]=infos[i];
    infos[line-1]=info;                     
    len++; //����һ���ռ䣬�������һ��ѧ��������
    if ((fp=fopen("student.dat","wb"))==NULL) {
      printf("�޷��������ļ���\n");
      exit(0);
    }
    for (int i=0;i<len;i++) fwrite(&infos[i],sizeof(stu),1,fp);
  } else {
    printf("\n��%d��Ϊ�գ������������������ĩ��\n",line);
    if ((fp=fopen("student.dat","ab"))==NULL) {
      printf("�޷��������ļ���\n");
      exit(0);
    }
    fwrite(&info,sizeof(stu),1,fp);
  }
  printf("��Ϣ��ӳɹ�~");
  fclose(fp);
  getch();
}

//�Ȳ�ѯѧ����Ϣ��ɾ�����һ��ƥ�����Ϣ
void deleteInfo() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb+"))==NULL) {
    printf("�޷��������ļ���\n");
    exit(0);
  }
  char chosen;
  while (1) {
    printf("��ѡ����Ϣ������ʽ��\n");
    printf("1.����  2.ѧ��");
    chosen=getch();
    if (chosen!='1'&&chosen!='2') {
      def();
      system("cls");
    } else break;
  }
  stu infos[N];
  char target[11];
  if (chosen=='1') printf("\n������Ҫɾ����Ϣ��ѧ������: ");
  else printf("\n������Ҫɾ����Ϣ��ѧ��ѧ��: ");
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
      printf("�޷��������ļ���\n");
      exit(0);
    }
    for (int i=0;i<len-1;i++) {
      if (i==isFound) continue; //д���ļ�ʱ����Ŀ����Ϣ��ʵ��ɾ��Ч��
      fwrite(&infos[i],sizeof(stu),1,fp);
    }
    printf("ɾ���ɹ�~");
    fclose(fp);
  } else printf("ѧ�������ڣ�ɾ��ʧ��!\n");
  getch();
}

//��ӡ����ѧ���ɼ���
void printAll() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("�޷��������ļ���\n");
    exit(0);
  }
  stu info;
  printf("%10s %10s %10s %10s %10s %10s\n","����","ѧ��","C����","����ԭ��","���ݿ�","��ɢ��ѧ");
  while (fread(&info,sizeof(stu),1,fp)) {
    printf("%10s %10s %10.2f %10.2f %10.2f %10.2f\n",info.name,info.id,info.c,info.theory,info.data,info.math);
  }
  fclose(fp);
  getch();
}

//�������4����Ŀ�ɼ�����߷֡���ͷֺ�ƽ����
void threeValues() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("�޷��������ļ���\n");
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
  printf("�ܳɼ�������\n");
  printf("%9s %18s %17s %10s\n","��Ŀ","��߷�","��ͷ�","ƽ����");
  char subjects[4][11]={"c���ԣ�","����ԭ��","���ݿ⣺","��ɢ��ѧ��"}; 
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

//ͳ���ܳɼ����������ε�ѧ������
void cntByScore() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("�޷��������ļ���\n");
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
    "���㣨360�ּ����ϣ���%d\n"
    "���ã�320�� - 359�֣���%d\n"
    "�еȣ�280�� - 319�֣���%d\n"
    "����240�� - 279�֣���%d\n"
    "������240�����£���%d\n",
    a,b,c,d,e
  );
  getch();
}

//�����ܳɼ��Ľ������ѧ���ɼ�����
void rankSum() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("�޷��������ļ���\n");
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
  //����ѡ������
  int maxp=0;
  for (int i=0;i<len;i++) {
    maxp=i;
    for (int j=i+1;j<len;j++) {
      if (ran[j].score>ran[maxp].score) maxp=j;
    }
    printf("��%d�� %10s %10.2f\n",i+1,ran[maxp].name,ran[maxp].score);
    float temp=ran[maxp].score;
    ran[maxp].score=ran[i].score;
    ran[i].score=temp;
  }
  getch();
}

//���ո�����Ŀ�ɼ��Ľ����������Ŀѧ���ɼ�����
void rankSubjects() {
  system("cls");
  FILE *fp;
  if ((fp=fopen("student.dat","rb"))==NULL) {
    printf("�޷��������ļ���\n");
    exit(0);
  }
  stu temp;
  rank ran[4][N];
  char subjects[4][19]={"c���Գɼ�������","����ԭ��ɼ�������","���ݿ�ɼ�������","��ɢ��ѧ�ɼ�������"};
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
  //����ð�ݷ�����
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
      printf("��%d�� %10s %10.2f\n",j+1,ran[i][j].name,ran[i][j].score);
    }
  }
  getch();
}

//չʾ��ִ��ͳ�ƹ��ܵ�С�˵�
void statistic() {
  char chosen;
  while (1) {
    system("cls");
    printf(
      "1.��ѯ����Ŀ��߷֡���ͷֺ�ƽ����\n"
      "2.ͳ���ܳɼ����������ε�ѧ������\n"
      "3.�����ܳɼ��Ľ������ѧ���ɼ�����\n"
      "4.���ո�����Ŀ�ɼ��Ľ����������Ŀѧ���ɼ�����\n"
      "0.�˳�"
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

//����������ϵͳ
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

//ִ�н��ײ˵�������ѡ��Ĺ���
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

//��������˵�
int main() {
  char uniChoice;
  while (1) {
    uniMenu();
    uniChoice=getch();
    if (uniChoice=='0') break;
    switch (uniChoice) {
      case '1': //��ѧ�����ʹ��ϵͳ
        searchInfo();
        break;
      case '2': //�Խ�ʦ���ʹ��ϵͳ
        system("cls");
        char password[11];
        printf("���������Ա���룺");
        scanf("%10s",password);
        if (!strcmp(password,key)) {
          proMode();
        } else {
          printf("�������\n");
          getch();
        }
        break;
      default:
        def();
        break;
    }
  }
  printf("\n\n\t\t\t%29s\n","��лʹ�ã��ټ���");
}
