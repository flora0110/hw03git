#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MALLOC(p,s)\
    if(!((p)=malloc(s))){\
        fprintf(stderr,"Insufficient memory");\
        exit(EXIT_FAILURE);\
    }
void find(char*,int);
long long check(char*,int);
char mose[26][5]={{'.','-'},{'-','.','.','.'},{'-','.','-','.'},{'-','.','.'},{'.'},\
    {'.','.','-','.'},{'-','-','.'},{'.','.','.','.'},{'.','.'},{'.','-','-','-'},\
    {'-','.','-'},{'.','-','.','.'},{'-','-'},{'-','.'},{'-','-','-'},\
    {'.','-','-','.'},{'-','-','.','-'},{'.','-','.'},{'.','.','.'},{'-'},\
    {'.','.','-'},{'.','.','.','-'},{'.','-','-'},{'-','.','.','-'},{'-','.','-','-'},{'-','-','.','.'}};
typedef struct node* nodepointer;
typedef struct node{
    int data;
    nodepointer dot;
    nodepointer dash;
}node;
nodepointer root;
void trans(char* word){
    int i,j;
    nodepointer temp=root;
    for(i=0;i<strlen(word);i++){
        for(j=0;j<strlen(mose[word[i]-65]);j++){
            if(mose[word[i]-65][j]=='.'){
                if(temp->dot==NULL){
                    nodepointer new;
                    MALLOC(new,sizeof(node));
                    new->dot=NULL;
                    new->dash=NULL;
                    new->data=0;
                    temp->dot=new;
                }
                temp=temp->dot;
            }
            else if(mose[word[i]-65][j]=='-'){
                if(temp->dash==NULL){
                    nodepointer new;
                    MALLOC(new,sizeof(node));
                    new->dot=NULL;
                    new->dash=NULL;
                    new->data=0;
                    temp->dash=new;
                }
                temp=temp->dash;
            }
        }
    }
    temp->data++;
}
int *step;
long long *arrive;
void find(char* code,int now){
    nodepointer temp=root;
    int orinow=now;
    do{
        if(code[now]=='.'){
            temp=temp->dot;
            now++;
        }
        else if(code[now]=='-'){
            temp=temp->dash;
            now++;
        }
        if(!temp){
            break;
        }
        if(temp->data!=0){
            arrive[orinow]+=(temp->data)*check(code,now);
        }
    }while(now<strlen(code));
    return;
}

long long check(char* code,int now){
    int i,j,t;
    if(now==strlen(code)){
        return 1;
    }
    if(step[now]==0){
        return arrive[now];
    }
    else{
        find(code,now);
    }
    step[now]=0;
    return arrive[now];
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test4.txt","r");
    wptr=fopen("output2-3.txt","w");
    if(rptr==NULL|| wptr==NULL){
        printf("open error\n");
        return 0;
    }

    int n;
    int i,j;
    root=(nodepointer)malloc(sizeof(node));
    root->data=0;
    root->dot=NULL;
    root->dash=NULL;
    char *code=(char*)malloc(100001*sizeof(char));
    fscanf(rptr,"%[-.]\n",code);
    fscanf(rptr,"%d\n",&n);
    int coden=strlen(code);
    step=(int*)malloc(coden*sizeof(int));
    arrive=(long long*)malloc(coden*sizeof(long long));
    for(i=0;i<coden;i++){
        arrive[i]=0;
    }
    for(i=0;i<coden;i++){
        step[i]=1;
    }
    char *word=(char*)malloc(21*sizeof(char));
    for(i=0;i<n;i++){
        fscanf(rptr,"%[A-Z]\n",word);
        trans(word);
    }
    check(code,0);
    printf("output: %lld\n",arrive[0]);
    fprintf(wptr,"output: %lld\n",arrive[0]);

    free(code);
    free(word);
    free(step);
    free(arrive);
    fclose(rptr);
    fclose(wptr);
}
