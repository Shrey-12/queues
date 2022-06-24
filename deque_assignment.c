//Next, you need to implement a stretchable double ended queue using array. 
//First you need to declare a big array of size 100. First implement a double ended circular queue using first 10 spaces of the array. 
//Implement all the operations on that mentioned in the 1st part. Then whenever the double ended queue becomes full,
//increase the available size for the queue by 5 and make those spaces available for insertion at front and insertion at rear,
//i. e. you need to add the free space of size 5 at the middle of the already used space by the double ended queue. 
//Thus, this operation requires movement of some of the elements of the already existing double ended queue
//Similarly, while performing delete operations (both deleteF ront and deleteRear) you need to check the number of current elements in the double ended queue.
//If number of current elements are less than (current available space - 6), you need to decrease the available space for the double ended queue by 5 and adjust the double ended queue accordingly.
//Write functions stretchDeque() and reduceDeque() to implement stretch and reduce size operations.

#include<stdio.h>
#include<stdlib.h>

#include<string.h>
 
typedef struct dequeue{
    int* data;
    int rear,front;
    int size; //total size of the queue, beyond this the queue cannot be stretched
}dequeue;

int MAX=10; //keeps track of the size of queue
int count=0; //counts the number of elements present in the queue, excluding the empty spaces in between
 
 //initializes the array of size 100
void initialize(dequeue *P){
    P->size=100;
   P->data=(int*)calloc(P->size,sizeof(int));
    P->rear=-1;
    P->front=-1;}

//isEmpty and isFull conditions
int empty(dequeue *P){
    if(P->rear==-1)
        return(1);
    return(0);}

int full(dequeue *P){
    if((P->rear+1)%MAX==P->front)
        return(1);
    return(0);
}

//the free space of size 5 at the middle of the already used queue whenever the queue is full 
void stretchDeque(dequeue *P){
    int temp=MAX;
    MAX+=5;
int k=0,i;


    for(int i=temp/2;i<temp/2+5;i++){
        for(int j=temp-1+k;j>=i;j--){
         P->data[j+1]=P->data[j];
         //P->data[i+1]=0;
         }k++;
}

    //updates the front and rear pointers to the middle
    if(temp%2==1){
        P->rear=(temp/2);
        P->front=P->rear + 6;}
    else if(temp%2==0){
        P->rear=(temp/2)-1;
        P->front=P->rear + 6 ;
        
    }
}

//number of current elements are less than (current available space - 6)
//need to decrease the available space for the double ended queue by 5
void reduceDeque(dequeue* P){
    int temp=MAX;
    MAX-=5;
    int k=0,i;
    
    for( i=0;i<5;i++){
        for(int j=P->rear+3;j<temp-k;j++){
            P->data[j-1]=P->data[j];
        }k++;
    }
    
    
    //updates front and rear pointers
    
}

void enqueueR(dequeue *P,int x){
    if(empty(P)){
        P->rear=0;
        P->front=0;
            P->data[0]=x;}
    else{
        P->rear=(P->rear+1)%MAX;
        P->data[P->rear]=x;}
        count++;
}

void enqueueF(dequeue *P,int x){
    if(empty(P)){
        P->rear=0;
        P->front=0;
        P->data[0]=x;}
    else{
        P->front=(P->front-1+MAX)%MAX;
        P->data[P->front]=x;}
        count++;
}

int dequeueF(dequeue *P){
    int x;
      if(count<MAX-6)
      {
        reduceDeque(P);
        P->front=P->front-5;
          
      }
    x=P->data[P->front];
    if(P->rear==P->front) //delete the last element
        initialize(P);
    else
        P->front=(P->front+1)%MAX;
        count--;
    return(x);
}

int dequeueR(dequeue *P){
    int x;
     if(count<MAX-6)
     {
         reduceDeque(P);
         P->front=P->front-5;
        
     }
    x=P->data[P->rear];
    if(P->rear==P->front)
        initialize(P);
    else
        P->rear=(P->rear-1+MAX)%MAX;
        count--;
    return(x);
}

void print(dequeue *P){
    int i;
    i=P->front;
    while(i!=P->rear){
        printf("%d ",P->data[i]);
        i=(i+1)%MAX;
    }
     printf("%d ",P->data[P->rear]);
     printf("\n");
    int j=P->rear;
    printf("The 5 elements inserted in between after shifting are: ");
    while(j!=P->front){
         printf("%d ",P->data[j]);
         j++;

    }
}


void main(){
    int i,x,op,n;
    dequeue q;
    initialize(&q);
    do{
        printf("\n1.Create\n2.Insert(rear)\n3.Insert(front)\n4.Delete(rear)\n5.Delete(front)");
        printf("\n6.Print\n7.Exit\n\nEnter your choice:");
        scanf("%d",&op);
        switch(op){
            case 1: printf("\nEnter number of elements (less than 10, you may enter the rest using enqueue dequeue):");
            scanf("%d",&n);
            initialize(&q);
            if(n>MAX)
            {
                stretchDeque(&q);
            }
            printf("\nEnter the data:");
            for(i=0;i<n;i++){
                scanf("%d",&x);
                enqueueR(&q,x);}
            break;

            case 2: printf("\nEnter element to be inserted:");
            scanf("%d",&x);
            if(full(&q)){
                stretchDeque(&q);
            }
            enqueueR(&q,x);
                break;

            case 3: printf("\nEnter the element to be inserted:");
            if(full(&q)){
                stretchDeque(&q);
            }
            scanf("%d",&x);
            enqueueF(&q,x);
                break;

            case 4: 
                x=dequeueR(&q);
                printf("\nElement deleted is %d\n",x);
                break;

            case 5:
                x=dequeueF(&q);
                printf("\nElement deleted is %d\n",x);
                break;

            case 6: print(&q);
                break;

            default: break;
        }
    }while(op!=7);
}
 
 

 
