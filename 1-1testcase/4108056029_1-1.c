#include<stdio.h>
#include<stdlib.h>
typedef struct Treenode* nodepointer;
int max(int a,int b){
    if(a>b){
        return a;
    }
    else return b;
}
typedef struct Treenode{
    int sum;
    int ls;
    int rs;
    int max;
    nodepointer left;
    nodepointer right;
}node;
node* build(int l,int r,int* arr){
    node* ptr=(node*)malloc(sizeof(node));
    //printf("%d %d\n",l,r);
    if(r==l){
        ptr->sum=arr[l];
        ptr->ls=arr[l];
        ptr->rs=arr[l];
        ptr->max=arr[l];
        //printf("sum:%d ls:%d rs:%d max:%d\n",ptr->sum ,ptr->ls,ptr->rs,ptr->max);
        return ptr;
    }
    else{
        int m=(l+r)/2;
        node* leftn=build(l,m,arr);
        node* rightn=build(m+1,r,arr);
        ptr->sum=leftn->sum+rightn->sum;
        ptr->ls=max(leftn->ls,leftn->sum+rightn->ls);
        ptr->rs=max(rightn->rs,rightn->sum+leftn->rs);
        ptr->max=max(max(rightn->max,leftn->max),leftn->rs+rightn->ls);
        ptr->left=leftn;
        ptr->right=rightn;
        //printf("sum:%d ls:%d rs:%d max:%d\n",ptr->sum ,ptr->ls,ptr->rs,ptr->max);
        return ptr;
    }
}
void modify(int x,int value,int l,int r,node* ptr){
    if(l==r){
        ptr->sum=value;
        ptr->ls=value;
        ptr->rs=value;
        ptr->max=value;
        //printf("find!!! sum:%d ls:%d rs:%d max:%d\n",ptr->sum ,ptr->ls,ptr->rs,ptr->max);
        return;
    }
    int m=(r+l)/2;
    if(x<=m){
        //printf("at left\n");
        modify(x,value,l,m,ptr->left);
    }
    else{
        //printf("at right\n");
        modify(x,value,m+1,r,ptr->right);
    }
    ptr->sum=ptr->left->sum+ptr->right->sum;
    ptr->ls=max(ptr->left->ls,ptr->left->sum+ptr->right->ls);
    ptr->rs=max(ptr->right->rs,ptr->right->sum+ptr->left->rs);
    ptr->max=max(max(ptr->right->max,ptr->left->max),ptr->left->rs+ptr->right->ls);
    //printf("sum:%d ls:%d rs:%d max:%d\n",ptr->sum ,ptr->ls,ptr->rs,ptr->max);
    return;
}
typedef struct imfor{
    int sum;
    int ls;
    int rs;
    int max;
}imfor;
imfor find(int a,int b,int l,int r,node* ptr){
    imfor im;//存a到b的imfor
    if(a==l && b==r){//符合就直接帶
        im.sum=ptr->sum;
        im.ls=ptr->ls;
        im.rs=ptr->rs;
        im.max=ptr->max;
        //printf("fix %d %d\n",a,b);
        //printf("sum:%d ls:%d rs:%d max:%d\n",ptr->sum ,ptr->ls,ptr->rs,ptr->max);
        return im;
    }
    int m=(l+r)/2;
    if(b<=m){//都在左邊
        //printf("all at left %d %d %d %d\n",a,b,l,r);
        im = find(a,b,l,m,ptr->left);
        //printf("in left %d %d\n",a,b);
        //printf("sum:%d ls:%d rs:%d max:%d\n",ptr->sum ,ptr->ls,ptr->rs,ptr->max);
        return im;
    }
    if(a>m){//都在右邊
        //printf("all at right %d %d %d %d\n",a,b,l,r);
        im = find(a,b,m+1,r,ptr->right);
        //printf("in right %d %d\n",a,b);
        //printf("sum:%d ls:%d rs:%d max:%d\n",ptr->sum ,ptr->ls,ptr->rs,ptr->max);
        return im;
    }
    else{
        //printf("middle %d %d %d %d\n",a,b,l,r );
        //printf("------to left------\n");
        imfor leftim=find(a,m,l,m,ptr->left);
        //printf("!! left sum:%d ls:%d rs:%d max:%d\n",leftim.sum ,leftim.ls,leftim.rs,leftim.max);
        //printf("------to right------\n");
        imfor rightim=find(m+1,b,m+1,r,ptr->right);
        //printf("!! right sum:%d ls:%d rs:%d max:%d\n",rightim.sum ,rightim.ls,rightim.rs,rightim.max);
        im.sum=leftim.sum+rightim.sum;
        im.ls=max(leftim.ls,leftim.sum+rightim.ls);
        im.rs=max(rightim.rs,rightim.sum+leftim.rs);
        im.max=max(max(rightim.max,leftim.max),leftim.rs+rightim.ls);
        //printf("%d %d\n",a,b);
        //printf("sum:%d ls:%d rs:%d max:%d\n",ptr->sum ,ptr->ls,ptr->rs,ptr->max);
        return im;
    }
}
int main(){
    FILE *rptr;
    FILE *wptr;
    rptr=fopen("test3.txt","r");
    wptr=fopen("output1-1.txt","w");
    if(rptr==NULL ||wptr==NULL){
        printf("open error\n");
        return 0;
    }
    int i,j;
    int t,n,m;
    fscanf(rptr,"%d\n",&t);
    printf("t: %d\n",t);
    node* root;
    int* arr;
    for(i=0;i<t;i++){
        fscanf(rptr,"%d\n",&n);
        printf("n: %d\n",n);
        arr=(int*)malloc((n+1)*sizeof(int));
        arr[0]=0;
        for(j=1;j<n;j++){
            fscanf(rptr,"%d ",&arr[j]);
        }
        fscanf(rptr,"%d\n",&arr[n]);
        //test-----------------------------
        /*printf("----test----\n");
        for(j=0;j<=n;j++){
            printf("%d \n",arr[j]);
        }
        printf("------------\n");
        //---------------------------------*/
        //int a[8]={1,2,3,4,5,6,7,8};
        root=build(1,n,arr);
        fscanf(rptr,"%d\n",&m);
        printf("m: %d\n",m);
        char c;
        int n1,n2;
        for(j=0;j<m;j++){
            fscanf(rptr,"%c ",&c);
            fscanf(rptr,"%d %d\n",&n1,&n2);
            if(c=='M'){
                //printf("\n\n%c %d %d\n",c,n1,n2);
                modify(n1,n2,1,n,root);
            }
            else if(c=='P'){
                //printf("\n\n%c %d %d\n",c,n1,n2);
                imfor ans=find(n1,n2,1,n,root);
                //printf("max %d\n",ans.max);
                fprintf(wptr,"%d\n",ans.max);
            }
        }

    }
}
