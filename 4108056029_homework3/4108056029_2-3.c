#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
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
    int data;//���h�ֳ�r�������K�X�O�o�ӲզX
    nodepointer dot;//���V�{�b���զX�[�@���I���զX
    nodepointer dash;
}node;
nodepointer root;//�r���
void trans(char* word){//���r�[���
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
    temp->data++;//�O�o�ӲզX����r�[�@
}
int *step;//�O�_�����L
long long *arrive;//�{�b��o���I�ɫ᭱�|�����զX
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
        if(temp->data!=0){//���r�夺���r�Mcode prefix
            arrive[orinow]+=(temp->data)*check(code,now);//�{�b�̭��I���զX�Ʋ{�b+���᪺
        }
    }while(now<strlen(code));
}

long long check(char* code,int now){//��զX��
    if(now==strlen(code)){//��̫�@�ӤF
        return 1;
    }
    if(step[now]==0){
        return arrive[now];//���L�F�A�w�g���D
    }
    else{
        find(code,now);//�h��ݬݦr�夺�O�_���ŦX���A�w���D�b�o���I���զX��(arrive[now])
    }
    step[now]=0;//�аO���L
    return arrive[now];
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test.txt","r");//test--------------test.txt
    wptr=fopen("output.txt","w");
    if(rptr==NULL|| wptr==NULL){
        printf("open error\n");
        return 0;
    }
    clock_t start,end; // �x�s�ɶ��Ϊ��ܼ�
    start = clock(); // �p��}�l�ɶ�
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

    step=(int*)malloc(coden*sizeof(int));//(����)�O�_�����L
    arrive=(long long*)malloc(coden*sizeof(long long));//(����)�{�b��o���I�ɫ᭱�|�����զX
    for(i=0;i<coden;i++){
        arrive[i]=0;//��l��
    }
    for(i=0;i<coden;i++){
        step[i]=1;//��l��(�����L=1)
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
    end=clock();
    double diff = end - start;
    printf("\n %f ms",diff);
    printf(" %f sec",diff/CLOCKS_PER_SEC );
}
