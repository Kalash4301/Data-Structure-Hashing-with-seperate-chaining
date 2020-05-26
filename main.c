#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>
struct node
{
    int grno;
    char name[15] ;
    char address[15];
    struct node *next;
};
struct node * A[100];

int dele();
void displayl();
void init(int n);
void create();
int Search();
int update(int gr);



typedef union uwb {
    unsigned w;
    unsigned char b[4];
} WBunion;
typedef unsigned Digest[4];



unsigned f0( unsigned abcd[] ){
    return ( abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);}

unsigned f1( unsigned abcd[] ){
    return ( abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);}

unsigned f2( unsigned abcd[] ){
    return  abcd[1] ^ abcd[2] ^ abcd[3];}

unsigned f3( unsigned abcd[] ){
    return abcd[2] ^ (abcd[1] |~ abcd[3]);}

typedef unsigned (*DgstFctn)(unsigned a[]);

unsigned *calcKs( unsigned *k)
{
    double s, pwr;
    int i;

    pwr = pow( 2, 32);
    for (i=0; i<64; i++) {
        s = fabs(sin(1+i));
        k[i] = (unsigned)( s * pwr );
    }
    return k;
}

// ROtate v Left by amt bits
unsigned rol( unsigned v, short amt )
{
    unsigned  msk1 = (1<<amt) -1;
    return ((v>>(32-amt)) & msk1) | ((v<<amt) & ~msk1);
}

unsigned *md5( const char *msg, int mlen)
{
    static Digest h0 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };

    static DgstFctn ff[] = { &f0, &f1, &f2, &f3 };
    static short M[] = { 1, 5, 3, 7 };
    static short O[] = { 0, 1, 5, 0 };
    static short rot0[] = { 7,12,17,22};
    static short rot1[] = { 5, 9,14,20};
    static short rot2[] = { 4,11,16,23};
    static short rot3[] = { 6,10,15,21};
    static short *rots[] = {rot0, rot1, rot2, rot3 };
    static unsigned kspace[64];
    static unsigned *k;

    static Digest h;
    Digest abcd;
    DgstFctn fctn;
    short m, o, g;
    unsigned f;
    short *rotn;
    union {
        unsigned w[16];
        char     b[64];
    }mm;
    int os = 0;
    int grp, grps, q, p;
    unsigned char *msg2;

    if (k==NULL) k= calcKs(kspace);

    for (q=0; q<4; q++) h[q] = h0[q];   // initialize

    {
        grps  = 1 + (mlen+8)/64;
        msg2 = malloc( 64*grps);
        memcpy( msg2, msg, mlen);
        msg2[mlen] = (unsigned char)0x80;
        q = mlen + 1;
        while (q < 64*grps){ msg2[q] = 0; q++ ; }
        {

            WBunion u;
            u.w = 8*mlen;

            q -= 8;
            memcpy(msg2+q, &u.w, 4 );
        }
    }

    for (grp=0; grp<grps; grp++)
    {
        memcpy( mm.b, msg2+os, 64);
        for(q=0;q<4;q++) abcd[q] = h[q];
        for (p = 0; p<4; p++) {
            fctn = ff[p];
            rotn = rots[p];
            m = M[p]; o= O[p];
            for (q=0; q<16; q++) {
                g = (m*q + o) % 16;
                f = abcd[1] + rol( abcd[0]+ fctn(abcd) + k[q+16*p] + mm.w[g], rotn[q%4]);

                abcd[0] = abcd[3];
                abcd[3] = abcd[2];
                abcd[2] = abcd[1];
                abcd[1] = f;
            }
        }
        for (p=0; p<4; p++)
            h[p] += abcd[p];
        os += 64;
    }

    if( msg2 )
        free( msg2 );

    return h;
}




void init(int n)
{
    int i,h;
   for(i=0;i<n;i++)
    A[i]=NULL;

}
void create()
{
    char ch='y';
    int gr,h;
    char nam[15],add[15];
    struct node *newnode,*p;

    do{
        printf("\nEnter Gr no : ");
        scanf("%d",&gr);

        printf("\nEnter Name  : ");
        scanf("%s",nam);

        printf("\nEnter Address : ");
        scanf("%s",add);



        newnode=(struct node*)malloc(sizeof(struct node));
        newnode->grno=gr;
        strcpy(newnode->name,nam);
        strcpy(newnode->address,add);

        newnode->next=NULL;
        h=gr%100;
        p=A[h];
        if(p==NULL)
          {A[h]=newnode;}
        else
        {
            while(p->next!=NULL)
                p=p->next;
            p->next=newnode;
        }





        printf("\nWant to enter another node(y/n)\n");

        ch=getche();

        printf("\t");
        }while(ch=='y'||ch=='Y');



}



int Search()
{
    int hashvalue,gr;


           printf("\nEnter gr no of record to be searched : ");
            struct node *ptr;
            scanf("%d",&gr);
            hashvalue=gr%100;
            ptr=A[hashvalue];

            while(ptr!=NULL && ptr->grno!=gr)
            {
              ptr=ptr->next;
            }
            if(ptr==NULL)
            {printf("\nRECORD NOT PRESENT \n");
              return ;}

             printf("\n\tName  \tAddress\n");
            printf("\t%s \t%s",ptr->name,ptr->address);

    return ;


}
int update(int gr)
{
    int hashvalue=gr%100;
    char nam[15],add[15];
    struct node *ptr;
     ptr=(struct node*)malloc(sizeof(struct node));
    ptr=A[hashvalue];

    while(ptr!=NULL && ptr->grno!=gr)
    {
      ptr=ptr->next;
    }
    if(ptr==NULL)
    { printf("\nRECORD NOT PRESENT \n");
      return ;
    }



        printf("\nUpdate Name  : ");
        scanf("%s",nam);

        printf("\nUpdate Address : ");
        scanf("%s",add);





        strcpy(ptr->name,nam);
         strcpy(ptr->address,add);

      printf("\nUPDATED SUCCESSFULLY\n");



}

int dele() {
     printf("\nEnter gr no  ");
    int n;
    scanf("%d",&n);
    struct node *head,*p,*prev,*q,*s=NULL;

    int    hashvalue=n%100;
     p=A[hashvalue];
     head=A[hashvalue];
     if(A[hashvalue]==NULL)
       {printf("DATA NOT PRESENT");
         return;}

     if(A[hashvalue]->grno==n)
        {  if(A[hashvalue]->next==NULL)
                {       free(head);

                        A[hashvalue]=NULL;
                        printf("\nDELETED\n");
                      return ;

                }

       p=A[hashvalue];
        A[hashvalue]=p->next;
        free(p);
        printf("\nDELETED\n");
        return ;
    }

        prev=A[hashvalue];




    while(prev!=NULL && prev->grno!=n)
    {

       s=prev;
       prev=prev->next;

    }



     if(prev==NULL)
    {
      printf("\nRECORD NOT PRESENT \n");
      return ;
    }
    s->next=prev->next;
    printf("\nDELETED\n");


return;


}

void displayl()
  {
	 int v;
	struct node *adj;
	adj=(struct node*)malloc(sizeof(struct node));

	 for(v=0;v<100;v++)
	 {

		 adj=A[v];
		 if(adj!=NULL)
         {


            while(adj!=NULL)
             {
                 printf("%d  \t%s   \t%s ",adj->grno,adj->name,adj->address);
                 adj=adj->next;
                  printf("\n");
             }
         }

	 }

  }
int main()
{   int n=0,key;
    int j,k;
    int i=0,p=0;
    char kk[15];
    int s=0;
    WBunion u;
    const char *msg;
    unsigned *d ;
    char pass1[16]="",pass2[16]="System",pass[16]="",database[32];
    struct node *ptr;


    printf("PROJECT NAME :PASSWORD VERIFICATION  AND STUDENT RECORD MANAGEMENT SYSTEM USING HASHING ");
    printf("\n\n\t\t====================================");
    printf("\n\t\t\t  STUDENT  DATABASE  \t");
    printf("\n\t\t====================================\n");

    aa:
    printf("\nEnter  password  to login :  ");
    scanf("%s",pass1);


      /*char ch=0;
      while(ch!=13)
      {
          ch=getch();
          pass1[p]=ch;
          p++;
           printf("*");
      }
      pass1[p]='\0';
      printf("\n");*/









    msg = pass1;
       d = md5(msg, strlen(msg));
    printf("\nHash Value of Password :\t");
    for (j=0;j<4; j++){
            u.w = d[j];
            for (k=0;k<4;k++) {
              printf("%02x",u.b[k]);}
              }

    printf("\n");
     if(strcmp(pass1,pass2)==0)
      {    printf("\nHash Value of Password stored in database :\t");
          for (j=0;j<4; j++){
          u.w = d[j];
          for (k=0;k<4;k++) {
          printf("%02x",u.b[k]);}}
          printf("\n\nMatched...\n");

           printf("\n.......................\n");
          printf("\nLogged in Successfully\n");
          msg = pass2;
          d = md5(msg, strlen(msg));

          goto abc;

      }
      else
      {    printf("\nWrong Password \n");
            msg = pass2;
           d = md5(msg, strlen(msg));
           printf("\nHash Value of Password  stored in database :\t");
           for (j=0;j<4; j++){
           u.w = d[j];
           for (k=0;k<4;k++) {
           printf("%02x",u.b[k]);}
                            }
           printf("\nNOT MATCHED ...\n");
           printf(" \n1.TRY AGAIN \n2.EXIT\t :");
           int k;
           scanf("%d",&k);
           if(k==1)
             goto aa;
           else
              exit(0);

       }




    clrscr();

   abc:
    printf("  \n\nInsert Records\n");
    init(100);
    create(100);
    do{   printf("\n\t\t====================================\n");
          printf("\n\tMenu :\n");
        printf("\n\t1.Insert\n\t2.Search\n\t3.Delete\n\t4.Display(all)\n\t5.Update\n\t6.Exit\n\t\tEnter your choice :  ");
        scanf("%d",&key);
        switch(key){
        case 1:{ create();
                break;
                }
        case 2:{
                  Search();
                    break;
                }
        case 3:{
                  dele();
                    break;
               }
        case 4:{  printf("\nList of all records\n");
                  printf("\nGr.no  \tName  \tAddress\n");
                 displayl();
                   break;
               }
        case 5:{  printf("\nEnter Gr.no of record to be updated : ");
                  scanf("%d",&n);
                  update(n);
                    break;
                }

                }
    }while(key!=6);


    return 0;


}


