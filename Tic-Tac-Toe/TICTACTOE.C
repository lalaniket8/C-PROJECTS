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
int a[9],chance=1;
union REGS in,out;

int checkarray(void);
int check(void);
void restart(void);

void main()
{
int i,gd=DETECT,gm,button,x,y;
char ch;
clrscr();

initgraph(&gd,&gm,"");
in.x.ax=1;
int86(0X33,&in,&out);

line(100,50,100,200);
line(150,50,150,200);
line(50,100,200,100);
line(50,150,200,150);

while(!check() && !checkarray() && !kbhit())
{
in.x.ax=3;
int86(0X33,&in,&out);
button=out.x.bx;x=out.x.cx;y=out.x.dx;
settextstyle(DEFAULT_FONT,0,2);
	if(button==1 && x>50 && x<100)
	{
		if(y>50 && y<100)
		       {
		       if((chance%2)==1)
		       {outtextxy(70,70,"X");
		       a[0]=1;sound(500);
		       delay(200);
		       nosound();}
		       else
		       {outtextxy(70,70,"O");
		       a[0]=2;sound(700);
		       delay(200);
		       nosound();}
		       chance++;
		       }
		if(y>100 && y<150)                //70120
		       {
		       if((chance%2)==1)
		       {outtextxy(70,120,"X");
		       a[1]=1;
		       sound(500);
		       delay(200);
		       nosound();}
		       else
		       {outtextxy(70,120,"O");
		       a[1]=2;
		       sound(700);
		       delay(200);
		       nosound();}
		       chance++;
		       }
		if(y>150 && y<200)                    //70170
			{
		       if((chance%2)==1)
		       {outtextxy(70,170,"X");
		       a[2]=1;
		       sound(500);
		       delay(200);
		       nosound();}
		       else
		       {outtextxy(70,170,"O");
		       a[2]=2;
		       sound(700);
		       delay(200);
		       nosound();}
		       chance++;
		       }
	}
	if(button==1 && x>100 && x<150)
	{
		if(y>50 && y<100)
			{
		       if((chance%2)==1)
		       {outtextxy(120,70,"X");
		       a[3]=1;
		       sound(500);
		       delay(200);
		       nosound();}
		       else
		       {outtextxy(120,70,"O");
		       a[3]=2;
		       sound(700);
		       delay(200);
		       nosound();}
		       chance++;
		       }
		if(y>100 && y<150)
			{
		       if((chance%2)==1)
		       {outtextxy(120,120,"X");
		       a[4]=1;
		       sound(500);
		       delay(200);
		       nosound();}
		       else
		       {outtextxy(120,120,"O");
		       a[4]=2;
		       sound(700);
		       delay(200);
		       nosound();}
		       chance++;
		       }
		if(y>150 && y<200)
			{
		       if((chance%2)==1)
		       {outtextxy(120,170,"X");
		       a[5]=1;
		       sound(500);
		       delay(200);
		       nosound();}
		       else
		       {outtextxy(120,170,"O");
		       a[5]=2;
		      sound(700);
		       delay(200);
		       nosound();}
		       chance++;
		       }
	}
	if(button==1 && x>150 && x<200)
	{
		if(y>50 && y<100)
			{
		       if((chance%2)==1)
		      { outtextxy(170,70,"X");
		      a[6]=1;
		      sound(500);
		       delay(200);
		       nosound();}
		       else
		      { outtextxy(170,70,"O");
		      a[6]=2;
		      sound(700);
		       delay(200);
		       nosound();}
		       chance++;
		       }
		if(y>100 && y<150)
			{
		       if((chance%2)==1)
		       {outtextxy(170,120,"X");
		       a[7]=1;
		      sound(500);
		       delay(200);
		       nosound();}
		       else
		       {outtextxy(170,120,"O");
		       a[7]=2;
		       sound(700);
		       delay(200);
		       nosound();}
		       chance++;
		       }
		if(y>150 && y<200)
			{
		       if((chance%2)==1)
		       {outtextxy(170,170,"X");
		       a[8]=1;
		      sound(500);
		       delay(200);
		       nosound();}
		       else
		       {outtextxy(170,170,"O");
		       a[8]=2;
		      sound(700);
		       delay(200);
		       nosound();}
		       chance++;
		       }
	}
settextstyle(DEFAULT_FONT,0,1);
}
printf("\nGame over \npress y to play again, any other key to exit");
/*delay(400);                                    // game over sound
sound(1700);delay(200);nosound();//delay(50);
sound(1500);delay(200);nosound();//delay(50);
//sound(800);delay(250);nosound();delay(50);
//sound(600);delay(250);nosound();delay(50);
sound(1700);delay(200);nosound();  */
ch=getch();
if(ch=='y' || ch=='Y')
restart();
else
closegraph();
}

int checkarray()
{
int i;
for(i=0;i<9;i++)
{
if(a[i]==0)
return 0;
}
return 1;
}

int check()
{
if(a[0]==a[1] && a[1]==a[2] && a[0]!=0)
{
	if(a[0]==1)
	{
	printf("Player 1 wins!!!");
	line(76,76,76,176);
	return 1;
	}
	if(a[0]==2)
	{
	printf("Player 2 wins!!!");
	line(76,76,76,176);
	return 1;
	}
}
else if(a[0]==a[3] && a[3]==a[6] && a[0]!=0)
{
	if(a[0]==1)
	{
	printf("Player 1 wins!!!");
	line(76,76,176,76);
	return 1;
	}
	if(a[0]==2)
	{
	printf("Player 2 wins!!!");
	line(76,76,176,76);
	return 1;
	}
}
else if(a[3]==a[4] && a[4]==a[5] && a[3]!=0)
{      	if(a[3]==1)
	{
	printf("Player 1 wins!!!");
	line(126,76,126,176);
	return 1;
	}
	if(a[3]==2)
	{
	printf("Player 2 wins!!!");
	line(126,76,126,176);
	return 1;
	}
}
else if(a[6]==a[7] && a[7]==a[8] && a[6]!=0)
{
	if(a[6]==1)
	{
	printf("Player 1 wins!!!");
	line(176,76,176,176);
	return 1;
	}
	if(a[6]==2)
	{
	printf("Player 2 wins!!!");
	line(176,76,176,176);
	return 1;
	}
}
else if(a[1]==a[4] && a[4]==a[7] && a[1]!=0)
{
	if(a[1]==1)
	{
	printf("Player 1 wins!!!");
	line(76,126,176,126);
	return 1;
	}
	if(a[1]==2)
	{
	printf("Player 2 wins!!!");
	line(76,126,176,126);
	return 1;
	}
}
else if(a[2]==a[5] && a[5]==a[8] && a[2]!=0)
{
	if(a[2]==1)
	{
	printf("Player 1 wins!!!");
	line(76,176,176,176);
	return 1;
	}
	if(a[2]==2)
	{
	printf("Player 2 wins!!!");
	line(76,176,176,176);
	return 1;
	}
}
else if(a[0]==a[4] && a[4]==a[8] && a[0]!=0)
{
	if(a[0]==1 && a[4]==1 && a[8]==1)
	{
	printf("Player 1 wins!!!");
	line(76,76,176,176);
	delay(100);
	return 1;
	}
	if(a[0]==2 && a[4]==2 && a[8]==2)
	{
	printf("Player 2 wins!!!");
	line(76,76,176,176);
	return 1;
	}
}
else if(a[2]==a[4] && a[4]==a[6] && a[2]!=0)
{
	if(a[2]==1)
	{
	printf("Player 1 wins!!!");
	line(76,176,176,76);
	return 1;
	}
	if(a[2]==2)
	{
	printf("Player 2 wins!!!");
	line(76,176,176,76);
	return 1;
	}
}
else
return 0;
}
void restart()
{
int i;
for(i=0;i<9;i++)
a[i]=0;
chance=1;
main();
}
