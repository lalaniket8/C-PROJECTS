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
#include<dos.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>

int check=0,lives=5,number,button,xcoord,ycoord,score=0;
FILE *fp;
int getno();
void parity(void);
void writefile(int,int,int);
void displayhighscore(void);
void updatefile(void);
void reset(void);
void resetclick(void);

union REGS in,out;

void main()
{

int gd=DETECT,gm,i,space=0;
char string[10],livestring[10]={2},stringscore[10];
time_t a,b;
clrscr();

initgraph(&gd,&gm,"");
in.x.ax=1;
int86(0X33,&in,&out);
while(!kbhit())
{
cleardevice();
rectangle(220,180,280,240);
outtextxy(234,210,"EVEN");
rectangle(220+93,180,280+93,240);
outtextxy(333,210,"ODD");
outtextxy(380,10,"LIVES:");
for(i=0;i<lives;i++)
{
outtextxy(430+space,10,livestring);
space+=11;
}
space=0;
outtextxy(490,390,"MADE BY-ANIKET LAL");
outtextxy(500,11,"SCORE:");
itoa(score,stringscore,10);
outtextxy(560,11,stringscore);
outtextxy(10,280,"Hit any key to exit");
outtextxy(10,100,"Click the respective boxes");
outtextxy(10,110,"for the appearing numbers");
outtextxy(10,10,"PARITY");

number=getno();
itoa(number,string,10);
outtextxy(getmaxx()/2-30,150,string);
a=time(NULL);
b=time(NULL);
while(difftime(b,a)<=1)
{
b=time(NULL);
parity();
}
if(lives==0)
break;
}
if(lives==0)
{
outtextxy(250,300,"GAME OVER");
outtextxy(240,310,"YOUR SCORE: ");
outtextxy(330,310,stringscore);
updatefile();
displayhighscore();
rectangle(500,280,590,305);
outtextxy(505,285,"click to");
outtextxy(505,295,"reset");
while(!kbhit())
{
resetclick();
}
}

getch();
closegraph();

}

int getno()
{
int no,i;
randomize();
for(i=0;i<=check;i++)
no=random(101);
check++;

if(no>=2)
return no;
else
{
no=getno();
return no;
}
}

void parity()
{
in.x.ax=3;
int86(0X33,&in,&out);
button=out.x.bx;
xcoord=out.x.cx;
ycoord=out.x.dx;

if(number%2==0 && button==1 && xcoord>=220 && xcoord<=280 && ycoord>=180 && ycoord<=240)
{
score+=100;
//setbkcolor(BLUE);
sound(900);
delay(150);
nosound();
}
else if(number%2==0 && button==1 && xcoord>=220+93 && xcoord<=280+93 && ycoord>=180 && ycoord<=240)
{
lives--;
//setbkcolor(RED);
sound(500);
delay(150);
nosound();

}
else if(number%2==1 && button==1 && xcoord>=220+93 && xcoord<=280+93 && ycoord>=180 && ycoord<=240)
{
score+=100;
//setbkcolor(BLUE);
sound(900);
delay(150);
nosound();

}
else if(number%2==1 && button==1 && xcoord>=220 && xcoord<=280 && ycoord>=180 && ycoord<=240)
{
//setbkcolor(RED);
lives--;
sound(500);
delay(150);
nosound();

}

else
setbkcolor(BLACK);
}

void updatefile()
{
int sc1=0,sc2=0,sc3=0;
fp=fopen("parityhs.txt","r");
if(fp==NULL)
writefile(sc1,sc2,sc3);
fscanf(fp,"%d%d%d",&sc1,&sc2,&sc3);
fclose(fp);
if(score>sc1)
{
sc3=sc2;sc2=sc1;sc1=score;
outtextxy(250,320,"!!HIGH SCORE!!");
outtextxy(220,330,"CONGRATS!1 1st POSITION!!");
}
else if(score>sc2)
{
sc3=sc2;sc2=score;
outtextxy(250,320,"!!HIGH SCORE!!");
outtextxy(220,330,"CONGRATS!1 2nd POSITION!!");
}
else if(score>sc3)
{
sc3=score;
outtextxy(250,320,"!!HIGH SCORE!!");
outtextxy(220,330,"CONGRATS!1 3rd POSITION!!");
}
else
{;}
writefile(sc1,sc2,sc3);
}

void writefile(int sc1,int sc2,int sc3)
{
FILE *fp2;
fp2=fopen("parityhs.txt","w");
fprintf(fp2,"%d\n%d\n%d\n",sc1,sc2,sc3);
fp=fp2;
fclose(fp2);
}

void displayhighscore()
{
int sc1,sc2,sc3;
char score1s[5],score2s[5],score3s[5];
fp=fopen("parityhs.txt","r");
fscanf(fp,"%d%d%d",&sc1,&sc2,&sc3);
fclose(fp);

itoa(sc1,score1s,10);
itoa(sc2,score2s,10);
itoa(sc3,score3s,10);

outtextxy(500,200,"HIGH SCORES:");
outtextxy(500,210,"1)");
outtextxy(515,210,score1s);
outtextxy(500,220,"2)");
outtextxy(515,220,score2s);
outtextxy(500,230,"3)");
outtextxy(515,230,score3s);
}

void reset()
{
FILE *fpr;
fpr=fopen("parityhs.txt","w");
fprintf(fpr,"%d\n%d\n%d\n",0,0,0);
fclose(fpr);
}

void resetclick()
{
in.x.ax=3;
int86(0X33,&in,&out);
button=out.x.bx;
xcoord=out.x.cx;
ycoord=out.x.dx;
if(button==1 && xcoord>=500 && xcoord<=590 && ycoord>=280 && ycoord<=305)
{
reset();
cleardevice();
rectangle(220,180,280,240);
outtextxy(234,210,"EVEN");
rectangle(220+93,180,280+93,240);
outtextxy(333,210,"ODD");
outtextxy(380,10,"LIVES:");
outtextxy(380,10,"LIVES:");
outtextxy(500,11,"SCORE:");
outtextxy(10,280,"Hit any key to exit");
outtextxy(10,100,"Click the respective boxes");
outtextxy(10,110,"for the appearing numbers");
outtextxy(10,10,"PARITY");

displayhighscore();
sound(600);
delay(150);
nosound();
sound(1000);
delay(150);
nosound();
}
}