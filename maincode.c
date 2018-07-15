/* this is using hash-tree to improve the effiency /* 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int zs[10] = {2,3,5,7,11,13,17,19,23,29};
double seed = 997;
double rrand() {
 double m = 34359738337.0;
 seed = fmod(3125.0*seed, m); 
 return seed / 34359738337.0;
}
//生成随机数种子

struct hashtree {
 char *fr;//前缀
 char **bh; 
 int ocp;//是否被占用
 int num;//后缀个数
 int sup;
 struct hashtree *a[30];//根节点的子树个数
}*rt;

int hash(char *a, int b) {
 int i,length = strlen(a);
 unsigned long long sum = 0;
 for(i = 0; i < length; i++) {
  sum = sum*6 + a[i];
 }
 return sum % b;
}

void insert(char *a, char *c, int level, struct hashtree *rt) {
 if(rt -> ocp == 0) { //如果没有被占用，则直接插入
  rt -> bh = (char**)malloc(16*sizeof(char*));
  memset(rt->bh,0,16*sizeof(char*));
  rt -> fr = (char*)malloc((strlen(a)+1));
  rt -> fr = a;
  rt -> num = 1;
  rt -> sup = 16;
  rt -> bh[0] = (char *)malloc((strlen(c)+1)*sizeof(char));
  rt -> bh[0] = c;
  rt -> ocp = 1;
  return;
 } else if(strcmp(rt -> fr, a) == 0) { //如果已经有前缀了，加入后缀且则次数+1
  if(rt -> num==rt -> sup)
  {
   rt -> sup *= 2;
   rt -> bh = (char**)realloc(rt -> bh, rt->sup*sizeof(char*)); 
  }
  rt -> bh[rt -> num] = (char*)malloc((strlen(c)+1)*sizeof(char));
  rt -> bh[rt -> num++] = c;
  return;
 } else { //否则就是找不到，用hash函数确定其所属，并分配内存空间后插入
  int size = hash(a,zs[level]);
  if(rt -> a[size] == NULL) {
   rt->a[size] = (struct hashtree*)malloc(sizeof(struct hashtree));
   memset(rt->a[size],0,sizeof(struct hashtree));
  }
  insert(a,c,level+1,rt->a[size]);
 }
}

char *search(char *e,int level,struct hashtree *rt) { //寻找后缀
 //assert(rt);
 int i = 0;
 if(strcmp(rt->fr,e) == 0) {
  if(rt -> num == 1)
   return rt -> bh[0];
  else if(rt -> num>1) {
   i = (int)(rrand()*(rt->num));
   return rt -> bh[i];
  }
 }
 int size = hash(e,zs[level]);
 return search(e, level + 1, rt -> a[size]);
}
char *in[2];
char *in1,*in2;
char *bh;
int main() {
 FILE *fp,*fq;
 int s,i = 0;
 scanf("%d",&s);
 fp=fopen("article.txt", "r");
 fq=fopen("markov.txt", "w");
 fscanf(fp,"%s %s" ,in1,in2);
 in[0] = in1;
 in[1] = in2;
 rt = (struct hashtree*)malloc(sizeof(struct hashtree));
 memset(rt,0,sizeof(struct hashtree));
 while(fscanf(fp, "%s", bh) == 1) {
  strcat(in1, " ");
  strcat(in1, in2);
  insert(in1, bh, 0, rt);
  in1 = in2;
  in2 = bh;
 }
 strcat(in1, " ");
 strcat(in1, in2);
 strcpy(bh, "(end)");
 insert(in1, bh, 0, rt);//输入结束,建立哈希树结束
 fprintf(fq,"%s %s " ,in[0],in[1]);
 strcpy(in1, in[0]);
 strcpy(in2, in[1]);
 for(i = 0; i < s; i++) {
  strcat(in1, " ");
  strcat(in1, in2);
  strcpy(bh, search(in1, 0, rt));
  if(strcmp(bh, "(end)") == 0)
   return 0;
  fprintf(fq, "%s ", bh);
  strcpy(in1, in2);
  strcpy(in2, bh);
 }//输出结束，生成marklov文本
 fclose(fp);
 fclose(fq);
 return 0;//程序结束
}
