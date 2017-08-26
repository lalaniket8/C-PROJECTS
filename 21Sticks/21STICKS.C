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
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
int random_no();
int comp(int);
int user(int);
int count=12;

void main()
{
int gd=DETECT,gm;
int i,sticks=21,ch,f;
clrscr();
//initgraph(&gd,&gm,"");

//in.x.ax=1;
//int86(0X33,&in,&out);
printf("There are 21 sticks.\nWe will pick them turn by turn,\nthe one who is left with one stick looses\nYou can pick 1,2,3, or 4 sticks only\n");
printf("Do you want to go first?(enter 1 for yes and 0 for no)");
scanf("%d",&f);
//rectangle(100,100,100+60,100+40);rectangle(200,100,200+60,100+40);

//cleardevice();

if(f==0)
{
printf("\nI am going first...\n");
while(1)
{
sticks=comp(sticks);
printf("\nsticks left: %d",sticks);
ch=1;
if(sticks<=1)
break;
sticks=user(sticks);
printf("\nsticks left: %d",sticks);
ch=0;
if(sticks<=1)
break;
}
}
else if(f==1)
{
printf("okay...you go first...\n");
while(1)
{
sticks=user(sticks);
printf("\nsticks left: %d",sticks);
ch=0;
if(sticks<=1)
break;
sticks=comp(sticks);
printf("\nsticks left: %d",sticks);
ch=1;
if(sticks<=1)
break;
}
}
else
{
printf("\nYou had to enter 1 or 0...please restart now...\n");
}
if(sticks==1 && ch==1)
printf("\nI win!!! Looser....\n");
else if(sticks==1 && ch==0)
printf("\nCongrats!!! You won this game!!!!\n");
else
printf("\nYou could have easily won the game....some people just cant \nunderstand rules....");
printf("counts:%d",count);

getch();
//closegraph();
}

int random_no()
{
int i,x;
for(i=0;i<=count;i++)
x=random(3)+1;
count++;
return(x);
}

int user(int sticks)
{
int a;
printf("\nEnter no. of sticks you want to pick...\n");
scanf("%d",&a);
while(a>4 || a<1)
{
printf("No.of stciks can be 1,2,3 or 4 only\nEnter again\n");
scanf("%d",&a);
}
return(sticks-a);
}
int r;
int comp(int sticks)
{
if(sticks<21 && sticks>16)
r=sticks-16;
else if(sticks>11 && sticks<16)
r=sticks-11;
else if(sticks>6 && sticks<11)
r=sticks-6;
else if(sticks>1 && sticks<6)
r=sticks-1;
else
r=random_no();
printf("  I pick up %d \n",r);
return(sticks-r);
}