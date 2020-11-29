#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void find(char*,int);
long long check(char*,int);
char mose[26][5]={{'.','-'},{'-','.','.','.'},{'-','.','-','.'},{'-','.','.'},{'.'},\
    {'.','.','-','.'},{'-','-','.'},{'.','.','.','.'},{'.','.'},{'.','-','-','-'},\
    {'-','.','-'},{'.','-','.','.'},{'-','-'},{'-','.'},{'-','-','-'},\
    {'.','-','-','.'},{'-','-','.','-'},{'.','-','.'},{'.','.','.'},{'-'},\
    {'.','.','-'},{'.','.','.','-'},{'.','-','-'},{'-','.','.','-'},{'-','.','-','-'},{'-','-','.','.'}};
typedef struct stack* stackpointer;
typedef struct stack{
    char* data;
    stackpointer link;
}stack;
stackpointer top=NULL;
char* stackEmpty(){
    printf("stack is empty\n");
    return NULL;
}
void push(char* item){
    stackpointer temp;
    temp=(stackpointer)malloc(sizeof(stack));
    temp->data=item;
    temp->link=top;
    top=temp;
}
char* pop(){
    stackpointer temp=top;
    char* item;
    if(!temp){
        return stackEmpty();
    }
    item = temp->data;
    top=temp->link;
    free(temp);
    return item;
}

typedef struct node* nodepointer;
typedef struct node{
    int data;
    nodepointer dot;
    nodepointer dash;
}node;
nodepointer root;
char* trans(char* word){
    int i,j;
    int n=0;
    char *result=(char*)malloc(401*sizeof(char));
    for(i=0;i<strlen(word);i++){
        for(j=0;j<strlen(mose[word[i]-65]);j++){
            result[n++]=mose[word[i]-65][j];
            //printf("%c\n",result[n-1]);
        }
        result[n]='\0';
    }
    //printf("%d\n",strlen(result));
    nodepointer temp=root;
    for(i=0;i<strlen(result);i++){
        //printf("in for %c\n",result[i]);
        if(result[i]=='.'){
            //printf("inn\n" );
            if(temp->dot==NULL){
                nodepointer new=(node*)malloc(sizeof(node));
                new->dot=NULL;
                new->dash=NULL;
                new->data=-1;
                temp->dot=new;
                //printf("dot\n");
            }
            temp=temp->dot;
        }
        else if(result[i]=='-'){
            if(temp->dash==NULL){
                nodepointer new=(node*)malloc(sizeof(node));
                new->dot=NULL;
                new->dash=NULL;
                new->data=-1;
                temp->dash=new;
                //printf("dash\n");
            }
            temp=temp->dash;
        }
    }
    temp->data=n;
    //printf("result\n");
    //system("pause");
    return result;
}
long long sum=0;
int *step;
long long *arrive;
void find(char* code,int now){
    //printf("ffffffffffffffffffffffffffffffffff\n" );
    nodepointer temp=root;
    printf("in find now %d\n",now );
    int orinow=now;
    int i;
    for(i=now;i<strlen(code);i++){
        printf("%c",code[i] );
    }
    printf("\n");
    do{
        //printf("in do\n");
        printf("%c\n",code[now]);

        if(code[now]=='.'){
            temp=temp->dot;
            now++;
            //printf("dot\n");
        }
        else if(code[now]=='-'){
            temp=temp->dash;
            now++;
            //printf("dash\n");
        }
        if(!temp){
            break;
        }
        //printf("kkk\n");
        if(temp->data!=-1 && temp){
            //printf("222\n");
            printf("result %d\n",now);
            printf("before ++ing arrive[%d] = %lld\n",orinow,arrive[orinow]);
            arrive[orinow]+=check(code,now);
            printf("++ing arrive[%d] = %lld\n",orinow,arrive[orinow]);
        }
        //printf("333\n");
        printf("%d\n",now );
    }while(temp && now<strlen(code));
    printf("--------------over\n");
    //printf("ooooooooooooooooooooooooooooooofffffffffffffff\n" );
    return;
}

long long check(char* code,int now){//dicn是字典量
    //printf("now %d\n",now );
    //printf("cccccccccccccccccccccccccccccccccc\n");
    printf("in ckeck now %d\n",now);
    int i,j,t;
    if(now==strlen(code)){
        sum++;
        printf("---------------%d\n",sum );
        /*//test------------
        stackpointer temp=top;
        printf("ans\n");
        while(temp){
            printf("%d\n",strlen(temp->data) );
            for(i=0;i<strlen(temp->data);i++){
                printf("%c",temp->data[i]);
            }
            printf("\n");
            temp=temp->link;
        }
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        //test-----------*/
        return 1;
    }
    if(!step[now]){
        sum+=arrive[now];
        printf("--------------     %lld\n",sum);
        printf("add arrive[%d] (%lld) = %lld\n",now,arrive[now],sum );
        //printf("------------------------------------------------------\n");
        return arrive[now];
    }
    else{
        find(code,now);
    }
    /*for(i=0;i<dicn;i++){
        t=1;
        if(strlen(diction[i])>strlen(code)){
            t=0;
            continue;
        }
        for(j=0;j<strlen(diction[i]);j++){
            if(diction[i][j]!=code[now+j]){
                t=0;
                break;
            }
        }
        if(t){
            //test---
            //push(diction[i]);
            //----
            //printf("add diction: %d\n",i );
                //printf("before ++ing arrive[%d] = %lld\n",now,arrive[now]);
                arrive[now]+=check(code,diction,now+strlen(diction[i]),dicn);
                //printf("++ing arrive[%d] = %lld\n",now,arrive[now]);
            //test---
            //pop();
            //---
        }
    }*/
    step[now]=0;
    printf("arrive[%d] = %lld\n",now,arrive[now]);
    //printf("-----------------------------now-------------------------\n");
    return arrive[now];
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test2.txt","r");
    wptr=fopen("output2-3.txt","w");
    if(rptr==NULL|| wptr==NULL){
        printf("open error\n");
        return 0;
    }
    long long testlong=57330892800;
    printf("%lld\n",testlong );
    printf("%d\n",sizeof(testlong));
    int n;
    int i,j;
    root=(nodepointer)malloc(sizeof(node));
    root->data=-1;
    root->dot=NULL;
    root->dash=NULL;
    char *code=(char*)malloc(100001*sizeof(char));
    fscanf(rptr,"%[-.]\n",code);
    //test---------
    printf("strlen %d\n",strlen(code));
    for(i=0;i<strlen(code);i++){
        printf("%c",code[i] );
    }
    printf("\n");
    //test--------*/
    fscanf(rptr,"%d\n",&n);
    printf("n: %d\n",n );
    int coden=strlen(code);
    step=(int*)malloc(coden*sizeof(int));
    arrive=(long long*)malloc(coden*sizeof(long long));
    for(i=0;i<coden;i++){
        arrive[i]=0;
    }
    for(i=0;i<coden;i++){
        step[i]=1;
    }
    char **diction=(char**)malloc(n*sizeof(char*));
    char *word=(char*)malloc(21*sizeof(char));
    char *trcode=(char*)malloc(21*sizeof(char));
    for(i=0;i<n;i++){
        fscanf(rptr,"%[A-Z]\n",word);
        /*printf("-----word------\n");
        for(j=0;j<strlen(word);j++){
            printf("%c",word[j]);
        }
        printf("\n");
        printf("-----------------\n");*/
        trcode=trans(word);
        diction[i]=trcode;
        //test-----
        for(j=0;j<strlen(diction[i]);j++){
            printf("%c",diction[i][j]);
        }
        printf("\n");
        //test-----*/
    }
    printf("tran over\n");
    check(code,0);
    printf("outt\n");
    printf("output: %lld\n",arrive[0]);
}
