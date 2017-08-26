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
void randomizeboard(int,int);
void initproxboard();
int m[11][11],mines,counter=0,flagno=0,firstgo=0;
int instructions=1;
int proxboard[11][11];
int color[11][11];
void opencell(int,int);
int selrow=0,selcol=0,n=4,bx=150,by=100,t=20,cellsclosed;
int bombstatus=0;
int flag[11][11];
void initvar();
void drawflag(int,int);
void board();
void main()
{
int i,j,gd=DETECT,gm;
char c;
clrscr();
initvar();
initgraph(&gd,&gm,"");

while(1)
{
cleardevice();
board();

if(cellsclosed==mines || bombstatus==1)
break;

while(kbhit()==0)
{}
c=getch();
if(c=='a' || c=='A')
{
selcol--;
if(selcol<0)
selcol=0;
sound(600);delay(90);nosound();
}
if(c=='D' || c=='d')
{
selcol++;
if(selcol>n-1)
selcol=n-1;
sound(600);delay(90);nosound();
}
if(c=='S' || c=='s')
{
selrow++;
if(selrow>n-1)
selrow=n-1;
sound(600);delay(90);nosound();
}
if(c=='W' || c=='w')
{
selrow--;
if(selrow<0)
selrow=0;
sound(600);delay(90);nosound();
}
if(c=='i' || c=='I')
{
if(instructions==0)
instructions=1;
else
instructions=0;
}
if(c=='p' || c=='P')
{
if(color[selrow][selcol]==0)
	{
	if(flag[selrow][selcol]==1)
		{flag[selrow][selcol]=0;flagno--;}
	else
		{flag[selrow][selcol]=1;flagno++;}
	}
sound(1200);delay(90);nosound();
}
if(c=='o' || c=='O')
{
if(firstgo==0)
{
randomizeboard(selrow,selcol);
initproxboard();
firstgo++;
}
opencell(selrow,selcol);
sound(1000);delay(45);nosound();
sound(500);delay(45);nosound();

}
if(c=='q' || c=='Q')
{sound(500);delay(150);nosound();
sound(300);delay(150);nosound();
sound(500);delay(150);nosound();
sound(300);delay(150);nosound();
exit(0);
}
delay(100);



}
if(bombstatus==1)
{
delay(100);
outtextxy(180,350,"BOOOM!!! You Lose...");
for(i=0;i<n;i++)
for(j=0;j<n;j++)
{
if(m[i][j]==1){
setcolor(GREEN);setfillstyle(1,2);
circle(j*t+bx+10,i*t+by+10,4);
floodfill(j*t+bx+10,i*t+by+10,GREEN);
setfillstyle(9,0);setcolor(WHITE);  }
}
for(i=600;i>=0;i-=3)
{sound(i);delay(5);nosound();
}
}
else
{delay(100);
outtextxy(180,350,"Congrats!!! You won!!!");
for(i=600;i<=1000;i+=3)
{sound(i);delay(3);nosound();
}
for(i=850;i<=1250;i+=3)
{sound(i);delay(3);nosound();
}
for(i=1100;i<=1500;i+=3)
{sound(i);delay(3);nosound();
}

}
getch();
closegraph();
}
void randomizeboard(int first_x,int first_y)
{
int i,j,r=-1;
do
{
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	m[i][j]=0;
	r++;counter=0;
	while(counter<mines)
		{
		for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			{
			if(m[i][j]!=1 && counter<mines && random(100)==r)
			{m[i][j]=1;counter++;}
			}
		}
}while(m[first_x][first_y]!=0);
}

void initproxboard()
{
int i,j,k_i,k_j;
for(i=0;i<n;i++)
for(j=0;j<n;j++)
{
if(m[i][j]==1)
	{
	for(k_i=-1;k_i<=1;k_i++)
	for(k_j=-1;k_j<=1;k_j++)
	proxboard[i+k_i][j+k_j]+=1;
	}
}

for(i=0;i<n;i++)
for(j=0;j<n;j++)
if(m[i][j]==1)
proxboard[i][j]=-1;
}

void board()
{
int i,j,k,l,selx,sely,c=0;
char number[2],minestring1[2],minestring2[2];
for(i=by;i<=(n*t)+by;i+=t)     //horizontal lines(|| to x axis by constant)
line(bx,i,bx+(n*t),i);
for(i=bx;i<=(n*t)+bx;i+=t)     //vertical lines(|| to y axis bx constant)
line(i,by,i,by+(n*t));

for(i=by,k=0;i<(n*t)+by,k<n;i+=t,k++)     //horizontal lines(|| to x axis by constant)
for(j=bx,l=0;j<(n*t)+bx,l<n;j+=t,l++)     //vertical lines(|| to y axis bx constant)
{
if(color[k][l]==0)
{setfillstyle(9,4);floodfill(j+5,i+5,WHITE);c++;}
if(color[k][l]==1)
{
setfillstyle(9,0);floodfill(j+5,i+5,WHITE);
if(proxboard[k][l]>0)
{
itoa(proxboard[k][l],number,10);
outtextxy(l*t+bx+5,k*t+by+5,number);
}
if(proxboard[k][l]==-1)
bombstatus=1;
}
if(k==selrow && l==selcol)
{selx=selcol*t+bx,sely=selrow*t+by;
setcolor(BLUE);
rectangle(selx+1,sely+1,selx+19,sely+19);
rectangle(selx+2,sely+2,selx+18,sely+18);
setcolor(WHITE);
}

}

for(i=0;i<n;i++)
for(j=0;j<n;j++)
{if(flag[i][j]==1)
drawflag(j,i);}
cellsclosed=c;
settextstyle(0,0,2);
outtextxy(200,50,"MINESWEEPER");
itoa(mines,minestring1,10);
settextstyle(0,0,1);
outtextxy(450,100,"Total mines: ");
outtextxy(550,100,minestring1);
itoa(mines-flagno,minestring2,10);
outtextxy(450,120,"Flags: ");
outtextxy(550,120,minestring2);

outtextxy(450,140,"CONTROLS:");
outtextxy(450,150,"w-move up");
outtextxy(450,160,"a-move left");
outtextxy(450,170,"d-move right");
outtextxy(450,180,"s-move down");
outtextxy(450,190,"p-place/remove flag");
outtextxy(450,200,"o-open cell");
outtextxy(450,210,"i-view instructions");
outtextxy(450,220,"q-quit game");
if(instructions==1)
{
outtextxy(100,380,"INSTRUCTIONS:");
outtextxy(100,390,"Board contains certain no. of mines");
outtextxy(100,400,"Find them by opening one cell at a time");
outtextxy(100,410,"Numbers tell you how many mines surround that particular cell");
outtextxy(100,420,"Each cell can contain only one mine");
outtextxy(100,430,"Use flags to help you mark them");
outtextxy(100,440,"You will lose if you open a cell with a mine...it will explode");
outtextxy(100,450,"Dont worry, the first cell you open won't explode...");
}
}

void drawflag(int fpx,int fpy)
{
int i,j,fx=fpx*t+10+bx,fy=fpy*t+10+by;
putpixel(fx,fy,13);
for(i=0;i<=4;i++)
for(j=-i;j<=i;j++)
putpixel(fx+j,fy+i,14);
}
void initvar()
{
printf("Enter size of board(1 to 10)\n");
scanf("%d",&n);
mines=((3*n*n)/8+1)/2;
cellsclosed=n*n;
}
void opencell(int x,int y)
{
if((x>=0 && x<n) && (y>=0 && y<n) && color[x][y]==0)
{color[x][y]=1;
if(proxboard[x][y]==0)
{
opencell(x,y-1);
opencell(x,y+1);
opencell(x+1,y);
opencell(x-1,y);
opencell(x+1,y-1);
opencell(x+1,y+1);
opencell(x-1,y+1);
opencell(x-1,y-1);
}
}
}