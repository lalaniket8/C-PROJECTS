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
#include<dos.h>
#include<math.h>
int arrayline[10][4],arraycolor[10][3],arrayrect[10][4],arraycircle[10][4];
int i=0,j=0;
union REGS in,out;

void paint();
void canvas();
void main()
{
int leftpressed=0,point1check=0,gd=DETECT,gm,i=0,j=0;
clrscr();
printf("Paint in C\n\nEnter l - line\nEnter r - rectangle\nEnter c - circle\nEnter f - fill color\nEnter q - quit\n");
printf("Enter any key to continue");
getch();
initgraph(&gd,&gm,"");

in.x.ax=1;
int86(0X33,&in,&out);
paint();
getch();
closegraph();
}
void paint(char char1)
{

char ch;
int brush=0,midx,halfx,halfy,midy,radius,leftpressed=0,point1check=0,gd=DETECT,gm;
canvas();
if(char1=='l')
{
printf("line selected");delay(500);
while(!kbhit())
{
	cleardevice();
	in.x.ax=1;
	int86(0X33,&in,&out);
	in.x.ax=3;
	int86(0X33,&in,&out);

	if(out.x.bx==1)
	{
		leftpressed=1;
		if(point1check==0)
		{	arrayline[i][0]=out.x.cx;
			arrayline[i][1]=out.x.dx;
			point1check=1;
		}
		arrayline[i][2]=out.x.cx;
		arrayline[i][3]=out.x.dx;
		line(arrayline[i][0],arrayline[i][1],arrayline[i][2],arrayline[i][3]);
	}
	if(out.x.bx==0 && leftpressed==1)
	{
		i++;point1check=0;leftpressed=0;  // printf("i: %d",i);
	}
	canvas();
      /*	for(j=0;j<i;j++)
		line(array[j][0],array[j][1],array[j][2],array[j][3]); */
	delay(100);
}
}
if(char1=='c')
{
printf("circle selected");delay(500);
while(!kbhit())
{
	cleardevice();
	in.x.ax=1;
	int86(0X33,&in,&out);
	in.x.ax=3;
	int86(0X33,&in,&out);

	if(out.x.bx==1)
	{
		leftpressed=1;
		if(point1check==0)
		{	arraycircle[i][0]=out.x.cx;
			arraycircle[i][1]=out.x.dx;
			point1check=1;
		}
		arraycircle[i][2]=out.x.cx;
		arraycircle[i][3]=out.x.dx;
		line(arraycircle[i][0],arraycircle[i][1],arraycircle[i][2],arraycircle[i][3]);
	}
	if(out.x.bx==0 && leftpressed==1)
	{
		i++;point1check=0;leftpressed=0;
	}
	canvas();delay(100);

}
}
if(char1=='q')
{printf("quit");
delay(1000);exit(0);}
if(char1=='r')
{
printf("rect selected");delay(500);
	while(!kbhit())
	{

		cleardevice();
		in.x.ax=1;
		int86(0X33,&in,&out);
		in.x.ax=3;
		int86(0X33,&in,&out);

		if(out.x.bx==1)
		{
			leftpressed=1;
			if(point1check==0)
			{	arrayrect[i][0]=out.x.cx;
				arrayrect[i][1]=out.x.dx;
				point1check=1;
			}
			arrayrect[i][2]=out.x.cx;
			arrayrect[i][3]=out.x.dx;
			line(arrayrect[i][0],arrayrect[i][1],arrayrect[i][2],arrayrect[i][3]);
		}
		if(out.x.bx==0 && leftpressed==1)
		{
			i++;point1check=0;leftpressed=0;   //printf("i: %d",i);
		}
		canvas();
		delay(100);
	}
}
if(char1=='f')
{
printf("fill color");delay(500);
	while(!kbhit())
	{
		cleardevice();
		in.x.ax=1;
		int86(0X33,&in,&out);
		in.x.ax=3;
		int86(0X33,&in,&out);

			setcolor(RED);
		rectangle(10,10,20,20);
			setfillstyle(1,RED);
			floodfill(12,12,RED);
			setcolor(BLUE);
		rectangle(10,20,20,30);
			setfillstyle(1,BLUE);
			floodfill(11,21,BLUE);
			setcolor(YELLOW);
		rectangle(10,30,20,40);
			setfillstyle(1,YELLOW);
			floodfill(11,31,YELLOW);
			setcolor(WHITE);
		rectangle(10,40,20,50);
			setfillstyle(1,WHITE);
			floodfill(11,41,WHITE);
			setcolor(GREEN);
		rectangle(10,50,20,60);
			setfillstyle(1,GREEN);
			floodfill(11,51,GREEN);
			setcolor(getmaxcolor());

		if(out.x.bx==1)
		{       printf("%d %d ",out.x.cx,out.x.dx);
			if(out.x.cx>10 && out.x.cx<20 && out.x.dx>10 && out.x.dx<20)
			{
				brush=4;
			}
			else if(out.x.cx>10 && out.x.cx<20 && out.x.dx>20 && out.x.dx<30)
			{
				brush=1;
			}
			else if(out.x.cx>10 && out.x.cx<20 && out.x.dx>30 && out.x.dx<40)
			{
				brush=14;
			}
			else if(out.x.cx>10 && out.x.cx<20 && out.x.dx>40 && out.x.dx<50)
			{
			       brush=15;
			}
			else if(out.x.cx>10 && out.x.cx<20 && out.x.dx>50 && out.x.dx<60)
			{
				brush=2;
			}
			else
			{
			setfillstyle(1,brush);
			floodfill(out.x.cx,out.x.dx,WHITE);
			arraycolor[i][0]=out.x.cx;
			arraycolor[i][1]=out.x.dx;
			arraycolor[i][2]=brush;
			i++;
			}
		}
		if(out.x.bx==0 && leftpressed==1)
		{
			i++;point1check=0;leftpressed=0;
		}

		canvas();
		delay(300);

	}
}
ch=getch();
paint(ch);
}

void canvas()
{
int j,midx,halfx,halfy,midy,radius;
for(j=0;j<i;j++)
{
halfx=abs((arraycircle[j][0]-arraycircle[j][2])/2);     //x2-x1/2;
halfy=abs((arraycircle[j][1]-arraycircle[j][3])/2);     //y2-y1/2;
if(arraycircle[j][0]<arraycircle[j][2])
	midx=halfx+arraycircle[j][0];
else
	midx=halfx+arraycircle[j][2];
if(arraycircle[j][1]<arraycircle[j][3])
	midy=halfy+arraycircle[j][1];
else
	midy=halfy+arraycircle[j][3];

radius=sqrt(pow(arraycircle[j][0]-arraycircle[j][2],2)+pow(arraycircle[j][1]-arraycircle[j][3],2))/2;      //sqrt((x2-x1)^2+(y2-y1)^2);
circle(midx,midy,radius);
}
	for(j=0;j<i;j++)
		line(arrayline[j][0],arrayline[j][1],arrayline[j][2],arrayline[j][3]);


	for(j=0;j<i;j++)
		rectangle(arrayrect[j][0],arrayrect[j][1],arrayrect[j][2],arrayrect[j][3]);
	delay(50);for(j=0;j<i;j++)
	       {
	       setfillstyle(1,arraycolor[j][2]);
	       floodfill(arraycolor[j][0],arraycolor[j][1],WHITE);
	       }


}