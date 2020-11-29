#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

char* trans(char* word){
    int i,j;
    int n=0;
    char *result=(char*)malloc(400*sizeof(char));
    for(i=0;i<strlen(word);i++){
        for(j=0;j<strlen(mose[word[i]-65]);j++){
            result[n++]=mose[word[i]-65][j];
        }
        result[n]='\0';
    }
    //printf("%d %d\n",strlen(result),n );
    /*for(i=0;i<n;i++){
        printf("%c",result[i] );
    }
    printf("\n");*/
    return result;
}
long long sum=0;
int *step;
long long *arrive;
long long check(char* code,char** diction,int now,int dicn){//dicn是字典量
    //printf("now %d\n",now );
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
    for(i=0;i<dicn;i++){
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
            if(step[now]==1){
                //printf("before ++ing arrive[%d] = %lld\n",now,arrive[now]);
                arrive[now]+=check(code,diction,now+strlen(diction[i]),dicn);
                //printf("++ing arrive[%d] = %lld\n",now,arrive[now]);
            }
            else{
                sum+=arrive[now];
                printf("--------------     %lld\n",sum );
                //printf("add arrive[%d] (%lld) = %lld\n",now,arrive[now],sum );
                return arrive[now];
            }
            //test---
            //pop();
            //---
        }
    }
    step[now]=0;
    //printf("arrive[%d] = %lld\n",now,arrive[now]);
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
    long long testlong=57330892800;
    printf("%lld\n",testlong );
    printf("%d\n",sizeof(testlong));
    int n;
    int i,j;
    char *code=(char*)malloc(100001*sizeof(char));
    fscanf(rptr,"%[-.]\n",code);
    //test---------
    printf("strlen %d\n",strlen(code));
    /*for(i=0;i<strlen(code);i++){
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
        /*//test-----
        for(j=0;j<strlen(diction[i]);j++){
            printf("%c",diction[i][j]);
        }
        printf("\n");
        //test-----*/
    }
    printf("tran over\n");
    check(code,diction,0,n);
    printf("output: %lld\n",sum );
}
