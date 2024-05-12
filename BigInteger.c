#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    int carry;
    struct node* next;
    struct node* prev;
};
struct BigInteger
{
    struct node* head;
    int length;
};
int len(struct BigInteger a)
{
    int i=0;
    while(a.head)
    {
        i++;
        a.head=a.head->next;
    }
    a.length=i;
    return i;
}
int compare(struct BigInteger a,struct BigInteger b)
{
        while(a.head && a.head->data==0)
        a.head=a.head->next;
        while(b.head && b.head->data==0)
        b.head=b.head->next;
        if(len(a)<len(b))
        return 0;
        if(len(a)>len(b))
        return 1;
        while(a.head!=NULL&&b.head!=NULL)
        {
           if(a.head->data < b.head->data)
           return 0;
           if(a.head->data > b.head->data)
           return 1;
           a.head=a.head->next;
            b.head=b.head->next;
        }
       
       
        return -1;
}
   
   

struct BigInteger initialize(char *s)
{
    struct BigInteger a,b,c;
    a.head=NULL;
    int i;
    for(i=0;s[i]!='\0';i++)
    {
        if(s[i]>='0' && s[i]<='9'){
        b.head=(struct node*)malloc(sizeof(struct node));
        b.head->data=(s[i]-48);
        b.head->carry=0;
        b.head->next=NULL;
        b.head->prev=NULL;
        if(a.head==NULL)
        {
            a.head=c.head=b.head;
        }
        else
        {
            c.head->next=b.head;
            b.head->prev=c.head;
            c.head=b.head;
        }
        }
    }
    a.length=i-1;
    return a;
}
struct node * reverse(struct node * c)
{
    struct node* pre=NULL,*temp=NULL;
    while(c)
    {
        temp=c->next;
        c->next=pre;
        c->prev=temp;
        pre=c;
        c=temp;
    }
   
    return pre;
}
void display(struct  BigInteger a)
{
    while(a.head)
    {
        printf("%d",a.head->data);
        a.head=a.head->next;
    }
    printf("\n");
}
struct BigInteger add(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger c;
    c.head=NULL;
    struct node *t,*nn;
    while(a.head->next)
     a.head=a.head->next;
    while(b.head->next)
     b.head=b.head->next;
    while(a.head!=NULL || b.head!=NULL)
    {
        nn=(struct node*)malloc(sizeof(struct node));
        nn->next=NULL;
        nn->prev=NULL;
        if(c.head==NULL)
        {
            nn->data=((a.head->data)+(b.head->data))%10;
            nn->carry=((a.head->data)+(b.head->data))/10;
            a.head=a.head->prev;
            b.head=b.head->prev;
            c.head=t=nn;
        }
        else
        {
            if(a.head==NULL)
            {
                nn->data=(0+(b.head->data)+(t->carry))%10;
                nn->carry=(0+(b.head->data)+(t->carry))/10;
                t->next=nn;
            nn->prev=t;
            t=nn;
            b.head=b.head->prev;
            }
            else if(b.head==NULL)
            {
                nn->data=((a.head->data)+0+(t->carry))%10;
                nn->carry=((a.head->data)+0+(t->carry))/10;
                t->next=nn;
            nn->prev=t;
            t=nn;
            a.head=a.head->prev;
            }
            else
            {
                nn->data=((a.head->data)+(b.head->data)+(t->carry))%10;
                nn->carry=((a.head->data)+(b.head->data)+(t->carry))/10;
            
            t->next=nn;
            nn->prev=t;
            t=nn;
            a.head=a.head->prev;
            b.head=b.head->prev;
            }
        }
    }
    if(t->carry!=0)
    {
        nn=(struct node*)malloc(sizeof(struct node));
        nn->data=t->carry;
        nn->carry=0;
        t->next=nn;
        nn->prev=t;
        nn->next=NULL;
    }
    c.head=reverse(c.head);
    return c;
}
struct BigInteger sub(struct BigInteger a,struct BigInteger b)
{ 
    struct BigInteger c;
    c.head=NULL;

   if((compare(a,b))==0){
   return c;
   }
    c.head=NULL;
    struct node *t,*nn;
    while(a.head->next)
     a.head=a.head->next;
    while(b.head->next)
     b.head=b.head->next;
     while(a.head!=NULL || b.head!=NULL)
     {
        nn=(struct node *)malloc(sizeof(struct node));
        nn->next=NULL;
        if(c.head==NULL)
        {
            if(a.head->data < b.head->data)
            {
                nn->data=(((a.head->data)+10)-(b.head->data));
                nn->carry=-1;
            }
             else if(a.head->data==b.head->data)
            {
                
                
                    nn->data=((a.head->data)-(b.head->data));
                    nn->carry=0; 
                
            }
            else
            {
                nn->data=((a.head->data)-(b.head->data));
                nn->carry=0;
            }
            c.head=t=nn;
            a.head=a.head->prev;
            b.head=b.head->prev;
        }
        else
        {
            if(b.head==NULL)
            {
                nn->data=((a.head->data)+(t->carry));
                nn->carry=0;
                a.head=a.head->prev;
                t->next=nn;
                nn->prev=t;
                t=nn;
            }
            else
            {
            if(a.head->data < b.head->data)
            {
                nn->data=((((a.head->data)+10)+(t->carry))-(b.head->data));
                nn->carry=-1;
            }
            else if(a.head->data==b.head->data)
            {
                if(t->carry==-1)
                {
                    nn->data=((((a.head->data)+10)+(t->carry))-(b.head->data));
                    nn->carry=-1;
                }
                else
                {
                    nn->data=((a.head->data)+(t->carry)-(b.head->data));
                nn->carry=0; 
                }
            }
            else
            {
                nn->data=((a.head->data)+(t->carry)-(b.head->data));
                nn->carry=0;
            }
            t->next=nn;
            nn->prev=t;
            t=nn;
            a.head=a.head->prev;
            b.head=b.head->prev;
        }
        }
     }
     c.head=reverse(c.head);
    return c;
} 
struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger c,e;
    struct node *temp=a.head;
    e=initialize("0");
    int i,p=-1;
    c.head=NULL;
    struct node *t,*q,*n=NULL;
    while(b.head->next)
     b.head=b.head->next;
     while(temp->next)
     temp=temp->next;
     struct node *itr=temp;;
    while(b.head)
    {
            n=NULL;
            temp=itr;
            while(temp)
            {
                if(n==NULL)
                {
                t=(struct node*)malloc(sizeof(struct node));
                t->data=((temp->data)*(b.head->data))%10;
                t->carry=((temp->data)*(b.head->data))/10;
                t->next=NULL;
                t->prev=NULL;
                n=q=t;
                }
                else
                {
                    t=(struct node*)malloc(sizeof(struct node));
                    t->data=((temp->data)*(b.head->data)+(q->carry))%10;
                    t->carry=((temp->data)*(b.head->data)+(q->carry))/10;
                    t->next=NULL;
                    q->next=t;
                    t->prev=q;
                    q=t;
                }
                temp=temp->prev;
            }
            p++;
            if(t->carry!=0)
                {
                t=(struct node*)malloc(sizeof(struct node));
                    t->data=((q->carry));
                    t->carry=0;
                    t->prev=q;
                    q->next=t;
                    t->next=NULL;
                 }
                 n=reverse(n);
                 for(i=0;i<p;i++)
            {
                temp=n;
                t=(struct node * )malloc(sizeof(struct node));
                t->data=0;
                while(temp->next)
                 temp=temp->next;
                temp->next=t;
                t->prev=temp;
                t->next=NULL;
            }
            c.head=n;
            e=add(c,e);
            c.head=n;
             b.head=b.head->prev;
    }
    return e;
}
struct BigInteger div1(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger c,d,e,f;
    int i=0,n;
     if(compare(a,b)==0)
    {
        c=initialize("0");
        return c;
    }
    c=initialize("0");
    d=initialize("1");
    f=initialize("1");
    if(compare(b,f)==-1)
    return a;
    while(1)
    {
        c=mul(b,d);
        e=sub(a,c);
            if((compare(b,e)==1))
            break;
        d=add(d,f);
    }
   return d;
}
struct BigInteger mod(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger c,d,e,f;
    int i=0,n;
     if(compare(a,b)==0)
    {
        c=initialize("0");
        return c;
    }
    c=initialize("0");
    d=initialize("1");
    f=initialize("1");
    if(compare(b,f)==-1)
    return a;
    while(1)
    {
        c=mul(b,d);
        e=sub(a,c);
            if((compare(b,e)==1))
            break;
        d=add(d,f);
    }
   return e;
}
int main()
{
    struct BigInteger a,b,c; 
    char s[1000],p[1000];
    int ch,co;
    do
    {
    fflush(stdin);
    printf("enter a value\n");
    fgets(s,1001,stdin);
    printf("enter another value\n");
    fgets(p,1001,stdin);
    a=initialize(s);
    b=initialize(p);
    printf("press 1 for addition\npress 2 for subtraction\npress 3 for multiplication\npress 4 for division\npress 5 for modulus\n");
    scanf("%d",&ch);
    switch(ch)
    {   
         
        case 1:
            c=add(a,b);
            display(c);
            break;
        case 2:
            c=sub(a,b);
            display(c);
            break;
        case 3:
            c=mul(a,b);
            display(c);
            break;
        case 4:
            c=div1(a,b);
            display(c);
            break;
        case 5:
            c=mod(a,b);
            display(c);
            break;
        default:
            printf("inavalid\n");
    }
    printf("press 1 to continue press any number to exit\n");
    scanf("%d",&co);
    } while (co==1);
    
}