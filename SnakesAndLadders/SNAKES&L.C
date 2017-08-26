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
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
void playerred();
void movered();
void moveblue();
void playerblue();
void animatedice();
void displaydice(int);
void dynamicdice();
void board();
void animateladder(int coords[],char);
void ladder(int,int coords[]);
void snake(int,int coords[]);
void animatesnake(int coords[],char);

int rx=62,ry=425,rpos=1;
int bx=75,by=425,bpos=1;
char pattern[8]={0x00, 0x70, 0x20, 0x27, 0x25, 0x27, 0x04, 0x04};
int lad1[10]={310,315,325,315,358,420,343,420,310,315};
int lad2[10]={100-5,109,100+15-5,109,100+15-5,345,100-5,345,100-5,109};
int lad3[10]={340,230,340+15,230,391+15,306,391,306,340,230};
int lad4[10]={304,69,304+15,69,222+15,269,222,269,304,69};
int lad5[10]={185,66,185+15,66,224+15,149,224,149,185,66};
int lad6[10]={500,300,515,300,515,360,500,360,500,300};

int snake1[8]={146+10,421+10,183,268,183+15,268,146+10,421+10};
int snake2[8]={184+10,346,144,70,144+15,70,184+10,346};
int snake3[8]={426,221,385,69,385+15,69,426,221};
int snake4[8]={260,420+3,305,195,305+15,195,260,420+3};
int snake5[8]={141+10,387,64,188,64+15,188,141+10,387};
int snake6[8]={500+14,440,500,380,515,380,500+14,440};
union REGS in,out;

void main()
{
int no,gd=DETECT,gm;
char ch;
clrscr();
initgraph(&gd,&gm,"");
in.x.ax=1;
int86(0X33,&in,&out);
randomize();
getfillpattern(pattern);
pattern[0]+=1;pattern[1]+=1;pattern[2]+=1;pattern[3]+=0;
pattern[4]+=1;pattern[5]+=1;pattern[6]+=1;pattern[7]+=1;
setfillpattern(pattern,CYAN);



board();
while(1)
{
playred:;
setcolor(RED);
outtextxy(520,200,"PLAY RED");    setcolor(getmaxcolor());
ch=getch();
setcolor(getmaxcolor());
if(ch=='q' || ch=='Q')
exit(0);
no=random(6)+1;

animatedice();
displaydice(no);
sound(600);delay(100);nosound();
delay(1000);
if(no>(100-rpos))
{
outtextxy(200,40,"SORRY, TOO CLOSE");
goto playblue;
}
movered(no);
if(rpos==100)
break;

if(no==6)
	goto playred;
if(rpos==8)
	{animateladder(lad1,'r');rpos=34;ry-=120;rx-=40;}
if(rpos==22)
	{animateladder(lad2,'r');rpos=82;ry-=240;rx-=0;}
if(rpos==32)
	{animateladder(lad3,'r');rpos=53;ry-=80;rx-=40;}
if(rpos==45)
	{animateladder(lad4,'r');rpos=94;ry-=200;rx+=80;}
if(rpos==76)
	{animateladder(lad5,'r');rpos=97;ry-=80;rx-=40;}

if(rpos==44)
	{animatesnake(snake1,'r');rpos=3;ry+=160;rx-=40;}
if(rpos==98)
	{animatesnake(snake2,'r');rpos=24;ry+=280;rx+=40;}
if(rpos==92)
	{animatesnake(snake3,'r');rpos=51;ry+=160;rx+=40;}
if(rpos==67)
	{animatesnake(snake4,'r');rpos=6;ry+=240;rx-=40;}
if(rpos==61)
	{animatesnake(snake5,'r');rpos=18;ry+=200;rx+=80;}

playblue:;
setcolor(BLUE);
outtextxy(520,200,"PLAY BLUE");  setcolor(getmaxcolor());
ch=getch();
if(ch=='q' || ch=='Q')
exit(0);
no=random(6)+1;
animatedice();
displaydice(no);
sound(600);delay(100);nosound();
delay(1000);
if(no>(100-bpos))
{
outtextxy(200,40,"SORRY, TOO CLOSE");
goto playred;
}
moveblue(no);
if(bpos==100)
break;

if(no==6)
	goto playblue;
if(bpos==8)
	{animateladder(lad1,'b');bpos=34;by-=120;bx-=40;}
if(bpos==22)
	{animateladder(lad2,'b');bpos=82;by-=240;bx-=0;}
if(bpos==32)
	{animateladder(lad3,'b');bpos=53;by-=80;bx-=40;}
if(bpos==45)
	{animateladder(lad4,'b');bpos=94;by-=200;bx-=80;}
if(bpos==76)
	{animateladder(lad5,'b');bpos=97;by-=80;bx-=40;}
if(bpos==44)
	{animatesnake(snake1,'b');bpos=3;by+=160;bx-=40;}
if(bpos==98)
	{animatesnake(snake2,'b');bpos=25;by+=280;bx+=80;}
if(bpos==92)
	{animatesnake(snake3,'b');bpos=51;by+=160;bx+=40;}
if(bpos==67)
	{animatesnake(snake4,'b');bpos=6;by+=240;bx-=40;}
if(bpos==61)
	{animatesnake(snake5,'b');bpos=18;by+=300;bx+=80;}

}

if(rpos>=100)
	outtextxy(200,40,"CONGRATULATION!!! PLAYER RED WINS!!!");
if(bpos>=100)
	outtextxy(200,40,"CONGRATULATION!!! PLAYER BLUE WINS!!!");
delay(1000);
getch();
closegraph();
}

void board()
{
int i,j,count=1;
char string[5];

outtextxy(200,20,"SNAKES AND LADDERS");
outtextxy(480,60,"Hit any key to roll ");
outtextxy(480,70,"and 'Q' to QUIT");
for(i=50;i<=450;i+=40)
{
line(i,50,i,450);
line(50,i,450,i);
}
for(j=440;j>=50;j-=80)
{for(i=70-5;i<=460-5;i+=40)
{
itoa(count,string,10);
outtextxy(i,j,string);
count++;
}
count+=10;}
count=11;
for(j=400;j>=10;j-=80)
{for(i=430-5;i>=40-5;i-=40)
{
itoa(count,string,10);
outtextxy(i,j,string);
count++;
}count+=10;
}

ladder(5,lad1);
ladder(5,lad2);
ladder(5,lad3);
ladder(5,lad4);
ladder(5,lad5);
ladder(5,lad6);
snake(4,snake1);
snake(4,snake2);
snake(4,snake3);
snake(4,snake4);
snake(4,snake5);
snake(4,snake6);
outtextxy(500+25,300+20,"- LADDER");
outtextxy(500+25,380+20,"- SNAKE");
}

void playerred()
{
int i;
setcolor(RED);
for(i=0;i<=5;i++)
circle(rx,ry,i);
setcolor(getmaxcolor());
}
void playerblue()
{
int i;
setcolor(BLUE);
for(i=0;i<=5;i++)
circle(bx,by,i);
setcolor(getmaxcolor());
}
void movered(int no)
{
int i;
for(i=0;i<no;i++)
{
cleardevice();
board();displaydice(no);
	if((rpos%10==0 ) && rpos<91 && rpos>1)
	ry-=40;
	else if(rpos/10==0 || rpos/10==2 || rpos/10==4 || rpos/10==6 || rpos/10==8)
	rx+=40;
	else
	rx-=40;
rpos++;
playerred();
playerblue();
delay(300);
}
}
void moveblue(int no)
{
int i;
for(i=0;i<no;i++)
{
cleardevice();
board();displaydice(no);
	if((bpos%10==0 ) && bpos<91 && bpos>1)
	by-=40;
	else if(bpos/10==0 || bpos/10==2 || bpos/10==4 || bpos/10==6 || bpos/10==8)
	bx+=40;
	else
	bx-=40;
bpos++;
playerblue();playerred();
delay(300);
}
}
void dynamicdice()
{

cleardevice();
board();playerred();playerblue();
rectangle(520,100,580,160);
delay(60);
cleardevice();
board();playerred();playerblue();
rectangle(522,100,582,160);
delay(50);
cleardevice();
board();playerred();playerblue();
rectangle(520,100,580,160);
delay(50);
cleardevice();
board();playerred();playerblue();
rectangle(518,100,578,160);
delay(50);
}
void displaydice(int no)
{
rectangle(520,100,580,160);
if(no==1)
	{
	circle(230+320,130,5);
	}
if(no==2)
	{
	circle(220+320,130,5);
	circle(240+320,130,5);
	}
if(no==3)
	{
	circle(215+320,130,5);
	circle(230+320,130,5);
	circle(245+320,130,5);
	}
if(no==4)
{
	circle(220+320,120,5);
	circle(220+320,140,5);
	circle(240+320,120,5);
	circle(240+320,140,5);
	}
if(no==5)
	{
	circle(217+320,117,5);
	circle(217+320,143,5);
	circle(243+320,117,5);
	circle(243+320,143,5);
	circle(230+320,130,5);
	}
if(no==6)
	{
	circle(215+320,120,5);
	circle(215+320,140,5);
	circle(230+320,120,5);
	circle(230+320,140,5);
	circle(245+320,120,5);
	circle(245+320,140,5);
	}
delay(40);
}
void animatedice()
{
dynamicdice();displaydice(3);
dynamicdice();displaydice(1);
//dynamicdice();displaydice(6);
//dynamicdice();displaydice(4);
//dynamicdice();displaydice(2);
dynamicdice();displaydice(5);
cleardevice();
board();playerred();playerblue();
}

void ladder(int n,int coords[])
{
setcolor(LIGHTBLUE);
drawpoly(n,coords);
line(coords[0]+3,coords[1],coords[6]+3,coords[7]);
line(coords[2]-3,coords[3],coords[4]-3,coords[5]);
setfillpattern(pattern,LIGHTBLUE);
setfillstyle(12,LIGHTBLUE);
floodfill(coords[0]+7,coords[1]+2,LIGHTBLUE);
setcolor(getmaxcolor());
}
void animateladder(int coords[],char ch)
{
int deltax=coords[0]-coords[6],deltay=coords[7]-coords[1];
int steps=deltay/8;
float inc=deltax/steps;
float spx=coords[6]+7,spy=coords[7]-3;//printf("delta x %d\ndelta y %d\nsteps %d\n inc %d",deltax,deltay,steps,inc);

sound(550);delay(250);nosound();

for(;spy>coords[1];spy-=8)
{
int i;
cleardevice();
board();
if(ch=='r')
{
setcolor(BLUE);
	for(i=0;i<=5;i++)
	circle(bx,by,i);
	setcolor(getmaxcolor());
ladder(5,coords);
	setcolor(RED);
	for(i=0;i<=5;i++)
	circle(spx,spy,i);
	setcolor(getmaxcolor());
	delay(250);
}
if(ch=='b')
{
setcolor(RED);
	for(i=0;i<=5;i++)
	circle(rx,ry,i);
	setcolor(getmaxcolor());
ladder(5,coords);
	setcolor(BLUE);
	for(i=0;i<=5;i++)
	circle(spx,spy,i);
	setcolor(getmaxcolor());
delay(100);
}
spx+=inc;
}}

void snake(int n,int coords[])
{
int i;int coordscopy[8];
for(i=0;i<8;i++)
{coordscopy[i]=coords[i];}
coordscopy[0]-=7;coordscopy[6]-=7;
setcolor(LIGHTGREEN);
drawpoly(4,coordscopy);
setcolor(getmaxcolor());
setfillstyle(11,LIGHTGREEN);
floodfill(coords[2]+7,coords[3]+2,LIGHTGREEN);
}
void animatesnake(int coords[],char ch)
{
int deltax=coords[4]-coords[0],deltay=coords[5]-coords[1];
int steps=deltay/8;
int incx=deltax/steps;
int spx=coords[2]+8,spy=coords[3]+3;//printf("delta x %d\ndelta y %d\nsteps %d\n inc %d",deltax,deltay,steps,inc);
sound(550);delay(250);nosound();

for(;spy<coords[1];spy+=8)
{
int i;
cleardevice();
board();
if(ch=='r')
{
setcolor(BLUE);
	for(i=0;i<=5;i++)
	circle(bx,by,i);
	setcolor(getmaxcolor());
snake(4,coords);
	setcolor(RED);
	for(i=0;i<=5;i++)
	circle(spx,spy,i);
	setcolor(getmaxcolor());
delay(150);
}
if(ch=='b')
{
setcolor(RED);
	for(i=0;i<=5;i++)
	circle(rx,ry,i);
	setcolor(getmaxcolor());
snake(4,coords);
	setcolor(BLUE);
	for(i=0;i<=5;i++)
	circle(spx,spy,i);
	setcolor(getmaxcolor());
delay(100);
}
spx+=incx;
}

}
