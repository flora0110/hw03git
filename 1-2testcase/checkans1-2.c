#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *ansptr;
    FILE *testptr;
    ansptr=fopen("output2.txt","r");
    testptr=fopen("output1-1.txt","r");
    if(ansptr==NULL || testptr==NULL){
        printf("ERROR\n");
        return 0;//
    }
    int ans,test;
    int testcount;
    while(fscanf(ansptr,"%d\n",&ans)!=EOF && fscanf(testptr,"%d: %d\n",&testcount,&test)!=EOF){
        //printf("%d : %d %d\n",testcount,ans,test);
        if(ans!=test){
            printf("%d : %d %d\n",testcount,ans,test);
        }
    }
    while(fscanf(ansptr,"%d\n",&ans)!=EOF || fscanf(testptr,"%d\n",&test)!=EOF){
        printf("??　%d %d\n",ans,test);
        /*if(ans!=test){
            printf("%d %d\n",ans,test);
        }*/
    }
}
