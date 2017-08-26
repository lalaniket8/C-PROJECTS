/*
MIT License

Copyright (c) 2017 Aniket Ramkrishna Lal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include<stdio.h>
#include<conio.h>
#include<string.h>
int chk(char a[30]);
void update(long int,char,char t[30]);
void enteracc();
void transaction(char r[30]);
void createacc();
void main()
{
int i;
clrscr();
printf("WELCOME TO Virtual Banking System(VBS)\n");
printf("What do you want to do? \n");
printf("1) Enter your account\n2) Create your account\n3) EXIT");
printf("\nEnter respective no.(1,2,3)\n");
scanf("%d",&i);
switch(i)
{
case 1:enteracc();
break;
case 2:createacc();
break;
case 3:exit(0);
break;
default:printf("Invalid entry\n");
}
getch();
}



void enteracc()
{
r:
{
FILE *fp;
char usrnm[20],ext[5]={'.','t','x','t','\0'},pswd[20],pswd2[20];
int wtdn,match,io;
clrscr();
printf("Enter username: ");
scanf("%s",&usrnm);
printf("Enter password: ");
scanf("%s",&pswd);
printf("\n");
strcat(usrnm,ext);
fp=fopen(usrnm,"r");
if(fp==NULL)
{
printf("\nYour account does not exists. Please create one.\n");
printf("What do you want to do next \n1)Continue to main menu\n2)EXIT\n");
printf("Enter respective nos(1 or 2)\n");
scanf("%d",&wtdn);
switch(wtdn)
{
case 1:main();
break;
case 2:exit(0);
break;
default:printf("Invalid entry\n");
}}

fscanf(fp,"%s",&pswd2);
match=strcmp(pswd,pswd2);
if(match==0)
transaction(usrnm);
else
{
printf("\nIncorrect password\n");
printf("Press 1 to proceed and 2 to exit\n");
scanf("%d",&io);
if(io==1)
goto r;
else if(io==2)
exit(0);
else
printf("invalid entry\n");

}
fclose(fp);
}
}


void createacc()
{
x:
{FILE *fp;
char c,a[5]={'.','t','x','t','\0'},bal[2]={'b','\0'},usrnm[20],usrnm2[20],pswd[20];
char t[2]={'t','\0'};
int i,wtdn,chk1;
int rt;
long int initialvalue=0;
clrscr();
printf("CREATE YOUR ACCOUNT\n");
printf("Enter your username(only alphabets no spaces)\n");
scanf("%s",&usrnm);
strcpy(usrnm2,usrnm);
strcat(usrnm,a);

chk1=chk(usrnm);
if(chk1==1)
{
printf("\nUsername already exists.Please choose another\n");
printf("Enter 1 to proceed and 2 to EXIT\n");
scanf("%d",&rt);
if(rt==2)
exit(0);
goto x;
}
fp=fopen(usrnm,"w");            //creating account file
printf("Enter desired password(only alphabets no spaces)\n");
scanf("%s",&pswd);
fprintf(fp,"%s",pswd);
fclose(fp);

strcat(bal,usrnm);         //creating balance file
fp=fopen(bal,"w");
fprintf(fp,"%ld",initialvalue);
fclose(fp);

strcat(t,usrnm);      //creating transaction file
fp=fopen(t,"w");
fclose(fp);

printf("\nYour account is created.\nUsername:%s\nPassword:%s",usrnm2,pswd);
printf("\n\nWhat do you want to do next:\n1)Continue to main menu\n2)EXIT\n");
printf("Enter respective nos(1 or 2)\n");
scanf("%d",&wtdn);
switch(wtdn)
{
case 1:main();
break;
case 2:exit(0);
break;
default:printf("Invalid entry\n");
}
}
}

int chk(char usrnm[30])
{
FILE *fp;
fp=fopen(usrnm,"r");
if(fp!=NULL)
return(1); //file is present
else
return(0); //file is not present
}

void transaction(char r[30])
{
FILE *fp,*pb,*cp;
char b[20]={'b','\0'},t[20]={'t','\0'},k,newpw[30];
long int balance,amt;
int a;
clrscr();
strcat(b,r);
strcat(t,r);
clrscr();
fp=fopen(b,"r+");
printf("Login successful...\n\n");
fscanf(fp,"%ld",&balance);
printf("BALANCE: %ld\n",balance);
fclose(fp);
printf("\nWhat do you want to do? Enter respective no.:\n1) Deposit\n2) Withdraw\n3) View transactions \n4) Change Password \n5) EXIT\n");
scanf("%d",&a);
switch(a)
{
case 1:
{
fp=fopen(b,"w");
printf("Enter amount to be deposited\n");
scanf("%ld",&amt);
fprintf(fp,"%ld",amt+balance);
fclose(fp);
update(amt,'d',t);
printf("\nWhat do you want to do next:\n1)Continue to main menu\n2)Continue transaction\n3)EXIT\n");
printf("Enter respective nos(1 or 2)\n");
scanf("%d",&a);

if(a==1)
main();
else if(a==2)
transaction(r);
else if(a==3)
exit(0);
else
printf("Invalid Entry\n");
}
break;
case 2:
{
printf("Enter amount to be withdrawn\n");
scanf("%ld",&amt);
if(amt>balance)
{
printf("Not enough balance\n");
goto m;
}
else
fp=fopen(b,"w");
fprintf(fp,"%ld",balance-amt);
fclose(fp);
update(amt,'w',t);
m:
{
printf("\n\nWhat do you want to do next:\n1)Continue to main menu\n2)Continue transaction\n3)EXIT\n");
printf("Enter respective nos(1 or 2)\n");
scanf("%d",&a);

if(a==1)
main();
else if(a==2)
transaction(r);
else if(a==3)
exit(0);
else
printf("Invalid Entry\n");
}}
break;
case 3:
{
clrscr();
printf("Loading transaction...\n");
pb=fopen(t,"r");
k=getc(pb);
if(k==EOF)
printf("No transactions done with this account\n");
while(k!=EOF)
{
putchar(k);
k=getc(pb);
}
fclose(pb);
goto m;
}
break;
case 4:
{
printf("Enter new password\n");
scanf("%s",&newpw);
cp=fopen(r,"w");
fprintf(cp,"%s",newpw);
fclose(cp);
printf("\nYour password is successfully changed.\n");
goto m;
}
break;
case 5:exit(0);
break;
default:printf("Invalid entry\n");
}

}
void update(long int value,char type,char t[30])
{
FILE *fp;
char dep[15]={'d','e','p','o','s','i','t','e','d',':',' ','\0'};
char with[15]={'w','i','t','h','d','r','a','w','n',':',' ','\0'};
fp=fopen(t,"a");
if(type=='d')
{
fprintf(fp,"%s",dep);
fprintf(fp,"%ld",value);
fprintf(fp,"%c",'\n');
}
else if(type=='w')
{
fprintf(fp,"%s",with);
fprintf(fp,"%ld",value);
fprintf(fp,"%c",'\n');
}
else
printf("error in passing value to update");
fclose(fp);
}