#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct date
{
    int d,m,y;
};
struct student
{
    int test;
    int num;
    int nob;
    char name[30];
    int pun;//1 pun***0 not pun
    struct date doh;
};
struct writer
{
    char name_w[30];
};
struct book
{
    int test;
    int isbn;
    char adres[30];
    int now;
    struct writer w[5];
    char sector[30];
    int nob;
    int no_borrow;
};
struct borrow
{
    struct book b;
    struct student s;
    struct date dob;
    struct date doc;
    int test;
};
void deleate_b(char *name);
void deleat_s(char *name);
struct book search_b (char *name);
struct student search_s(char *name);
void add_borrow(struct student s,struct book b);
void open_s(struct student s);
void open_b(struct book b);
void add_b(char *name);
void display ();
void display_one_book(struct book b);
void display_one_book(struct book b)
{
    int i;
    printf("%7s  \t  %3d  \t",b.adres,b.isbn);
    printf("         %8s  \t  %3d  \t",b.sector,b.nob);
    for(i=0; i<b.now; i++)
    {
        printf("\t%8s  \n\t\t\t\t\t\t\t",b.w[i].name_w);
    }
    printf("\n");
}
int test_date(struct date b)
{
    if(b.y>1900&&b.y<2030)
    {
        if(b.m>=1&&b.m<=12)
            if(b.m==2)
            {
                if(b.d>=1&&b.d<=28)
                    return 0;
            }

            else if(b.d>=1&&b.d<=30)
                return 0;
            else
                return 1;
    }
    else
        return 1;
}
void deleate_b(char *name)
{
    FILE *f,*ft;
    f=fopen("file1.bin","rb");
    ft=fopen("temp.bin","wb");
    if(f==NULL||ft==NULL)
    {
        printf("error12\n");
        exit(-1);
    }
    struct book test;
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        if(strcmp(name,test.adres)==0)
        {
            continue;
        }
        else
            fwrite(&test,sizeof(test),1,ft);
    }
    fclose(f);
    fclose(ft);
    f=fopen("file1.bin","wb");
    ft=fopen("temp.bin","rb");
    while((fread(&test,sizeof(test),1,ft))!=NULL)
    {
        fwrite(&test,sizeof(test),1,f);
    }
    fclose(f);
    fclose(ft);
}
void deleat_s(char *name)
{
    FILE *f=fopen("file2.bin","rb");
    FILE *ft=fopen("temp1.bin","wb");
    if (f==NULL||ft==NULL)
    {
        printf("error13\n");
        exit(-1);
    }
    struct student test;
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        if (strcmp(name,test.name)==0)
            continue;
        else
            fwrite(&test,sizeof(test),1,ft);
    }
    fclose(f);
    fclose(ft);
    f=fopen("file2.bin","wb");
    ft=fopen("temp1.bin","rb");
    while((fread(&test,sizeof(test),1,ft))!=NULL)
    {
        fwrite(&test,sizeof(test),1,f);
    }
    fclose(f);
    fclose(ft);
}
struct book search_b (char *name)
{
    FILE *f=fopen("file1.bin","rb");
    if(f==NULL)
    {
        printf("error7\n");
        exit(-1);
    }
    struct book test;
    while(fread(&test,sizeof(test),1,f)!=NULL)
    {
        if((strcmp(name,test.adres))==0)
        {
            test.test=1;
            fclose(f);
            return test;
        }
    }
    fclose(f);
    test.test=0;
    test.nob=0;
    return test;
}
int search_s_n(int n)
{
    FILE *f=fopen("file2.bin","rb");
    if(f==NULL)
    {
        printf("error6\n");
        exit(-1);
    }
    struct student test;
    while (fread(&test,sizeof(test),1,f)!=NULL)
    {
        if(test.num==n)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
struct student search_s(char *name)
{
    FILE *f=fopen("file2.bin","rb");
    if(f==NULL)
    {
        printf("error6\n");
        exit(-1);
    }
    struct student test;
    while (fread(&test,sizeof(test),1,f)!=NULL)
    {
        if(strcmp(test.name,name)==0)
        {
            fclose(f);
            test.test=1;
            return test;
        }
    }
    fclose(f);
    test.test=0;
    test.pun=0;
    test.nob=0;
    return test;
}
void open_borrow( struct borrow b)
{
    FILE *f=fopen("file3.bin","ab");
    if(f==NULL)
    {
        printf("error 15");
        exit(-1);
    }
    fwrite(&b,sizeof(b),1,f);
    fclose(f);
}
void add_borrow(struct student s,struct book b)
{
    if(b.nob==0)
    {
        printf("\n***There are no copies of this book in the library so the borrowing process will not be completed***\n");
        return;
    }
    s.nob=s.nob+1;
    if(s.nob>3)
    {
        printf("\n***This student borrowed three books so the borrowing process will not be completed***\n");
        return;
    }
    struct borrow borrow;
    b.nob=b.nob-1;
    b.no_borrow=b.no_borrow+1;
    borrow.b=b;
    if(b.nob==0)
    {
        printf("***This book is over***\n");
        deleate_b(b.adres);
        open_b(b);
    }
    else
    {
        deleate_b(b.adres);
        open_b(b);
    }
    borrow.s=s;
    deleat_s(s.name);
    open_s(s);
error1:
    printf("Enter the book's borrowing date like day/month/year : ");
    scanf("%d/%d/%d",&borrow.dob.d,&borrow.dob.m,&borrow.dob.y);
    while(test_date(borrow.dob))
    {
        printf("\n***you entered wrong date***\n\n");
        goto error1;
    }
    if(s.pun==1)
    {
        struct date test;
        test=s.doh;
        test.m=test.m+1;
        if(test.m>12)
        {
            test.y=test.y+1;
            test.m=1;
        }
        if(compare_date(test,borrow.dob)==1)
        {
            printf("\n***This student is being punished for borrowing on this date***\n");
            return;
        }
    }
error:
    printf("Enter the date when the book should be returned like day/month/year : ");
    scanf("%d/%d/%d",&borrow.doc.d,&borrow.doc.m,&borrow.doc.y);
    if(test_date(borrow.doc))
    {
        printf("\n***You entered wrong date***\n\n");
        goto error;
    }
    if(compare_date(borrow.dob,borrow.doc)==1)
    {
        printf("\n***You entered the wrong date***\n\n");
        goto error;
    }
    open_borrow(borrow);
    printf("\n***The borrowing process was successfully completed***\n");
    return;
}
void open_s(struct  student s)
{
    FILE *f=fopen("file2.bin","ab");
    if (f==NULL)
    {
        printf("error5\n");
        exit(-1);
    }
    fwrite(&s,sizeof(s),1,f);
    fclose(f);
}
void open_b(struct book b)
{
    FILE *f1=fopen("file1.bin","ab");
    if(f1==NULL)
    {
        printf("error4\n");
        exit(-1);
    }
    fwrite(&b,sizeof(b),1,f1);
    fclose(f1);
}
void add_b(char *name)
{
    struct book b;
    int choise;
    b.test=0;//not found ::::
    b=search_b(name);
    if(b.test==0) //book not exist
    {
        strcpy(b.adres,name);
        printf("Enter the number of book (isbn) : ");
        scanf("%d",&b.isbn);
        while(b.isbn<=0)
        {
            printf("***Please you must enter a positive number ==> ");
            scanf("%d",&b.isbn);
        }
        while(search_b_n(b.isbn)==1)
                {
                    printf("***This (isbn) is reserved\n***Please enter a new number ==> ");
                    scanf("%d",&b.isbn);
                }
        printf("Enter the number of writers : ");
        int i;
        scanf("%d",&b.now);
        while(1>b.now||b.now>5)
        {
            printf("***Enter number between 1 and 5 ==> ");
            scanf("%d",&b.now);
        }
        for(i=0; i<b.now; i++)
        {
            printf("Enter the name of writer(%d) : ",i+1);
            fflush(stdin);
            gets(b.w[i].name_w);
        }
        printf("Enter the name of section : ");
        fflush(stdin);
        gets(b.sector);
        printf("Enter the number of copies of this book : ");
        scanf("%d",&b.nob);
        while(b.nob<=0)
        {
            printf("***Please you must enter a positive number ==> ");
            scanf("%d",&b.nob);
        }
        b.no_borrow=0;
        open_b(b);
        return ;
    }
    else
    {
        int test;
        printf("\n***This book is exist in the library***\n\n");
        error:
        printf("press(1)...To enter the number of copies you want to add from this book to the library\n");
        printf("press(2)...To return to main menu\nWhat is your choice ==> ");
        scanf("%d",&choise);
        if(choise==1)
        {
            printf("Enter the number of copies you want to add : ");
            scanf("%d",&test);
            while(test<=0)
            {
                printf("***Please you must enter a positive number ==> ");
                scanf("%d",&test);
            }
            b.nob=b.nob+test;
            deleate_b(b.adres);
            open_b(b);
        }
        else if(choise==2)
            return ;
        else
        {
            printf("\n*** Enter a number 1 or 2 ***\n\n");
            goto error;
        }
    }
}
void display()
{
    struct book test;
    int i;
    FILE *f=fopen("file1.bin","rb");
    if(f==NULL)
    {
        printf("error 10\n");
        exit(-1);
    }
    printf("   name  \t  isbn  \t  section  \t  noc  \t          writers  \n");
    printf("***********************************************************************************\n");
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        if(test.nob==0)
            continue;
        printf("%7s  \t  %3d  \t",test.adres,test.isbn);
        printf("         %8s  \t  %3d  \t",test.sector,test.nob);
        for(i=0; i<test.now; i++)
        {
            printf("\t%8s  \n\t\t\t\t\t\t\t",test.w[i].name_w);
        }
        printf("\n");
    }
    fclose(f);
}
void search_w(char *name_w)
{
    int test1=0,i,q=0;
    FILE *f=fopen("file1.bin","rb");
    if(f==NULL)
    {
        printf("error12");
        exit(-1);
    }
    struct book test;
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        for (i=0; i<test.now; i++)
            if((strcmp(name_w,test.w[i].name_w))==0)
            {
                if(q==0)
                {
                    printf("***********************************************************************************\n");
                    printf("   name  \t  isbn  \t  section  \t  noc  \t         writers  \n");
                    printf("***********************************************************************************\n");
                    q=1;
                }
                display_one_book(test);
                test1=1;
            }
    }
    if(test1==0)
    {
        printf("***********************************************************************************\n");
        printf("\n***There is no book for this writer***\n");
    }
    fclose(f);
}
int compare_date (struct date a,struct date b)
{
    if(a.y==b.y&&a.m==b.m&&a.d==b.d)
        return 0;
    if(a.y==b.y)
        if(a.m>b.m)
            return 1;
        else if(a.m<b.m)
            return -1;
        else if(a.m==b.m)
            if(a.d>b.d)
                return 1;
            else
                return -1;
    if(a.y>b.y)
        return 1;
    else
        return -1;

}
struct borrow search_borrow(char *name_s,char *name_b)
{
    FILE *f=fopen("file3.bin","rb");
    if(f==NULL)
    {
        printf("erorr14\n");
        exit(-1);
    }
    struct borrow test;
    test.test=0;
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        if(strcmp(name_s,test.s.name)==0&&strcmp(name_b,test.b.adres)==0)
        {
            fclose(f);
            test.test=1;
            return test;
        }
    }
    fclose(f);
    test.test=0;//not found
    return test;
}
int search_re(char *name)
{
    FILE *f=fopen("temp4.bin","rb");
    if(f==NULL)
    {
        printf("error\n");
        exit (-1);
    }
    struct book test;
    while(fread(&test,sizeof(test),1,f)!=NULL)
    {
        if(strcmp(test.adres,name)==0)
        {
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return 1;
}
void open_re(struct book b)
{
    FILE *f=fopen("temp4.bin","ab");
    if(f==NULL)
    {
        printf("eroor19\n");
        exit(-1);
    }
    fwrite(&b,sizeof(b),1,f);
    fclose(f);
}
void re_back (struct borrow b)
{
    b.b.nob=b.b.nob+1;
    b.s.nob=b.s.nob-1;
    deleate_b(b.b.adres);
    open_b(b.b);
    struct date test;
error:
    printf("Enter the date that this book was returned like day/month/years : ");
    scanf("%d/%d/%d",&test.d,&test.m,&test.y);
    while(test_date(test))
    {
        printf("\n**you entered wrong date**\n\n");
        goto error;
    }
    while(compare_date(b.dob,test)==1)
    {
        printf("\n***You entered  wrong date***\n\n");
        goto error;
    }
    if((compare_date(b.doc,test))==-1)
    {
        b.s.pun=1;
        b.s.doh=test;
        deleat_s(b.s.name);
        open_s(b.s);
        if(search_re(b.b.adres))// 0 found //1 not found
            open_re(b.b);
    }
    else
    {
        deleat_s(b.s.name);
        open_s(b.s);
    }
    deleate_borrow(b);
}
void deleate_borrow(struct borrow b)
{
    FILE *f,*ft;
    f=fopen("file3.bin","rb");
    ft=fopen("temp2.bin","wb");
    if(f==NULL||ft==NULL)
    {
        printf("error12\n");
        exit(-1);
    }
    struct borrow test;
    while((fread(&test,sizeof(test),1,f))!=NULL)
    {
        if(strcmp(b.b.adres,test.b.adres)==0)
        {
            continue;
        }
        else
            fwrite(&test,sizeof(test),1,ft);
    }
    fclose(f);
    fclose(ft);
    f=fopen("file3.bin","wb");
    ft=fopen("temp2.bin","rb");
    while((fread(&test,sizeof(test),1,ft))!=NULL)
    {
        fwrite(&test,sizeof(test),1,f);
    }
    fclose(f);
    fclose(ft);
}
void search_s_b(char *name_s)
{
    FILE *f=fopen("file3.bin","rb");
    if(f==NULL)
    {
        printf("error16");
        exit(-1);
    }
    struct borrow borow;
    int test=0;
    int i=1,q=0;
    while((fread(&borow,sizeof(borow),1,f))!=NULL)
    {
        if(strcmp(name_s,borow.s.name)==0)
        {
            if(q==0)
            {
                printf("****************\nList of books : \n****************\n");
                q=1;
            }
            printf("\tBook number(%d) : %s\n",i++,borow.b.adres);
            test=1;
        }
    }
    if(test==0)
    {
        printf("***********************************************************************************");
        printf("\n\n***This student does not borrowed any book***\n");
    }
}
void display_borrow(struct borrow b)
{
    printf("%s    \t  %s        \t     %d/%d/%d              %d/%d/%d\n",b.b.adres,b.s.name,b.dob.d,b.dob.m,b.dob.y,b.doc.d,b.doc.m,b.doc.y);
}
void sort_by_array(struct borrow test[],int n)
{
    if(n==1)
        return;
    int i;
    for(i=0; i<n; i++)
    {
        if(compare_date(test[i].dob,test[i+1].dob)==-1)
        {
            struct borrow temp;
            temp=test[i];
            test[i]=test[i+1];
            test[i+1]=temp;
        }
    }
    return sort_by_array(test,n-1);
}
void sort_by_ne_borrow(struct book test[],int n)
{
    if(n==1)
        return;
    int i;
    for(i=0; i<n; i++)
    {
        if(test[i].no_borrow<test[i+1].no_borrow)
        {
            struct book temp;
            temp=test[i];
            test[i]=test[i+1];
            test[i+1]=temp;
        }
    }
    return sort_by_ne_borrow(test,n-1);
}
void sort_by_date(int x)
{
    int n=0;
    struct borrow finals[120];
    struct borrow test;
    FILE *f=fopen("file3.bin","rb");
    if(f==NULL)
    {
        printf("error 18\n");
        exit(-1);
    }
    while(fread(&test,sizeof(test),1,f)!=NULL)
    {
        finals[n]=test;
        n++;
    }
    fclose(f);
    sort_by_array(finals,n);
    int i;
    printf("\n***********************************************************************************\n");
    printf("book name  \t  student     \t  date of borrowing      date of re-borrowing\n");
    printf("***********************************************************************************\n");
    for (i=0; i<n; i++)
    {
        if(finals[i].dob.m==x)
            display_borrow(finals[i]);
    }
}
void display_re(struct book test)
{
    int i;
    printf("%8s  \t  %3d  \t",test.adres,test.isbn);
    printf("     %10s    \t",test.sector,test.nob);
    printf("%d",test.no_borrow);
    for(i=0; i<test.now; i++)
    {
        printf("\t      %8s  \n\t\t\t\t\t\t",test.w[i].name_w);
    }
    printf("\n");
}
void sort_by_noborrow()
{
    FILE *f=fopen("file1.bin","rb");
    if(f==NULL)
    {
        printf("erorr19\n");
        exit(-1);
    }
    int i=0;
    struct book test,finals[120];
    while(fread(&test,sizeof(test),1,f)!=NULL)
    {
        finals[i]=test;
        i++;
    }
    fclose(f);
    int j;
    sort_by_ne_borrow(finals,i);
    printf("   name  \t  isbn  \t  sector  \tnob            writers  \n");
    printf("***********************************************************************************\n");
    for(j=0; j<i; j++)
    {if(finals[j].no_borrow==0)
    continue;
    else
        display_re(finals[j]);
    }
}
void dsiplay_book_should_back(struct book b)
{
    int i;
    printf("%8s  \t  %3d  \t",b.adres,b.isbn);
    printf("     %10s  \t  %3d  \t",b.sector,b.nob);
    for(i=0; i<b.now; i++)
    {
        printf("\t %8s   \n\t\t\t\t\t\t\t",b.w[i].name_w);
    }
    printf("\n");
}
void display_s()
{
    struct student test;
    FILE *f=fopen("file2.bin","rb");
    if(f==NULL)
        printf("ERROR 3\n");
    /*if(fread(&test,sizeof(test),1,f)==NULL)
    {
        printf("file is empty\n");
        return;
    }*/
    printf("id\tname\n");
    printf("............\n");
    while(fread(&test,sizeof(test),1,f)!=NULL)
    {
        printf("%d\t%s",test.num,test.name);
        printf("\n");
    }
    fclose(f);
}
void display_borrowoo()
{
    FILE *f=fopen("file3.bin","rb");
    if(f==NULL)
        printf("\ncant open file\n");
    struct borrow b;
    printf("book name  \t  student     \t  date of borrowing      date of re-borrowing\n");
    printf("***********************************************************************************\n");
    while(fread(&b,sizeof(b),1,f)!=NULL)
        printf("%s    \t  %s        \t     %d/%d/%d              %d/%d/%d\n",b.b.adres,b.s.name,b.dob.d,b.dob.m,b.dob.y,b.doc.d,b.doc.m,b.doc.y);

fclose(f);
}
int search_b_n(int n)
{
    FILE *f=fopen("file1.bin","rb");
    if(f==NULL)
    {
        printf("error61\n");
        exit(-1);
    }
    struct book test;
    while (fread(&test,sizeof(test),1,f)!=NULL)
    {
        if(test.isbn==n)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
int main()
{
    /*FILE *f=fopen("file1.bin","wb");
    fclose(f);
    FILE *f1=fopen("file2.bin","wb");
    fclose(f1);
    FILE *f2=fopen("file3.bin","wb");
    fclose(f2);
    FILE *f3=fopen("temp4.bin","wb");
    fclose(f3);*/
    int choise;
    while (choise!=11)
    {
        printf("\n***********************************************************************************\n");
        printf ("Please choose number from 1 to 11\n");
        printf("***********************************************************************************\n");
        printf("(1)..Add a new book to the library\n");
        printf("(2)..Add borrowed information\n");
        printf("(3)..Re book\n");
        printf("(4)..Display books information in the library\n");
        printf("(5)..Search for a book by title\n");
        printf("(6)..Display all books for a specific author\n");
        printf("(7)..Display the books borrowed by a specific student and still with him\n");
        printf("(8)..Display borrowings within a specified month sorted by date\n");
        printf("(9)..Display books borrowed by the most borrowed sorted by date\n");
        printf("(10)..Display the books to be returned and not returned by the specified date\n");
        printf("(11)..EXIT\n");
        printf("***********************************************************************************\n");
        printf("Enter your choice ==>");
        scanf("%d",&choise);
        printf("***********************************************************************************\n");
        switch(choise)
        {
        case 1:
        {
            char name[30];
            printf("Enter the name of the book : ");
            fflush(stdin);
            gets(name);
            add_b(name);
            break;
        }
        case 2:
        {
            char name_b[30];
            char name_s[30];
            printf("Enter the name of book : ");
            fflush(stdin);
            gets(name_b);
            struct book b;
            b.test=0;
            b=search_b(name_b);
            if(b.test==0)
            {
                printf("***********************************************************************************\n");
                printf("\n***This book does not exist so the borrowing process will not be completed***\n");
                break;
            }
            printf("Enter the name of the student : ");
            fflush(stdin);
            gets(name_s);
            struct student s;
            s.test=0;
            s=search_s(name_s);
            if(s.test==0)
            {
                strcpy(s.name,name_s);
                printf("Enter (id) of the student : ");
                scanf("%d",&s.num);
                while(s.num<=0)
                {
                    printf("***pleas enter a positive number***\n");
                    scanf("%d",&s.num);
                }
                while(search_s_n(s.num)==1)
                {
                    printf("***This (id) is reserved\n***Please enter a new number ==> ");
                    scanf("%d",&s.num);
                }
                s.pun=0;
                s.nob=0;
                open_s(s);
            }
            struct borrow test;
            test.test=0;
            test=search_borrow(s.name,b.adres);
            if(test.test==0)
                add_borrow(s,b);
            else
            {
                printf("\n***This student borrowed this book***\nso the borrowing process will not be completed\n");
                break ;
            }
            break;
        }
        case 3:
        {
            char name_s[30],name_b[30];
            printf("Enter the name of the book : ");
            fflush(stdin);
            gets(name_b);
            printf("Enter the name of the student : ");
            fflush(stdin);
            gets(name_s);
            struct borrow borow;
            borow=search_borrow(name_s,name_b);
            if(borow.test==0)
            {
                printf("\n***The information entered is wrong***\n");
                break;
            }
            re_back(borow);
            break;
        }
        case 4:
        {
            FILE *f=fopen("file1.bin","rb");
            struct book test;
            if((fread(&test,sizeof(test),1,f))==NULL)
            {
                printf("\n***The library is empty***\n");
                fclose(f);
            }
            else
                display();
            break;
        }
        case 5:
        {
            char name_b[30];
            printf("Enter the name of the book you want to search for : ");
            fflush(stdin);
            gets(name_b);
            struct book test;
            test.test=0;
            test=search_b(name_b);
            if(test.test==0)
            {
                printf("***********************************************************************************\n");
                printf("\n***This book does not exist***\n");
                break;
            }
            else
            {
                printf("***********************************************************************************\n");
                printf("   name  \t  isbn  \t  section  \t  noc  \t          writers  \n");
                printf("***********************************************************************************\n");
                display_one_book(test);
                break;
            }
        }
        case 6:
        {
            char name_w[30];
            printf("Enter the name of the writer : ");
            fflush(stdin);
            gets(name_w);
            search_w(name_w);
            break;
        }
        case 7:
        {
            char name_s[30];
            printf("Enter the name of the student : ");
            fflush(stdin);
            gets(name_s);
            search_s_b(name_s);
            break;
        }
        case 8:
        {
            int n;
            printf("Enter the number of the month for which you want to display his borrowings process : ");
            scanf("%d",&n);
            while(n<=0)
            {
                printf("***Please you must enter a positive number ==> ");
                scanf("%d",&n);
            }
            sort_by_date(n);
            break;
        }
        case 9:
        {
            sort_by_noborrow();
            break;
        }
        case 10:
        {
            FILE *f3=fopen("temp4.bin","rb");
            if(f3==NULL)
            {
                printf("error20\n");
                exit(-1);
            }
            struct book test;
            int x=0;
            while(fread(&test,sizeof(test),1,f3)!=NULL)
            {
                if(x==0)
                {
                    printf("   name  \t  isbn  \t  sector  \t  nob  \t            writers  \n");
                    printf("***********************************************************************************\n");
                }
                x=1;
                dsiplay_book_should_back(test);
            }
            fclose(f3);
            break;
        }
        case 11:
            return 0;
        case 12:
             display_s();
             break;
        case 13:
             display_borrowoo();
             break;
        default:
        {
            printf("\n===========>Please enter number from 1 to 11<===========\n");
            break;
        }
        }
    }
}
