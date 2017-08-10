/*
PROJECT NAME: VARIABLE PERSPECTIVE
AUTHOR: ANIKET RAMKRISHNA LAL
YEAR: 2015

Variable Perspective is a program that renders a 2D projection of a 3D object on your screen.
The object can be rotated around the Y (Veritcal) axis by movement of the mouse. 

The program has hard coded coordinates for each point.
You can make changes to read from a file or accept from user during runtime.
*/

#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<math.h>

/* 
Horizontal axis - X axis
Vertical axis - Y axis
axis normal to the screen - Z axis
*/

void line3d(float,float,float,float,float,float);
void initialize(int);
void function(int,int);
void assignvalues();
void callfunction();

//required data members for mouse control 
union REGS in,out;
int mousex,mousey,choice=0;

float screendist=400; //screen depth
float delgama,delalpha; // deltaGama , deltaAlpha
float ox=320,oy=240,oz=240;

struct points
{
float x,y,z; //cartesian coordinates for a point
float alpha,beta,gama; // angle between the line joining origin and the point to each of the axis 
float r; //r is length of the line
};

/* 
as mouse is moved, 
the members of the struct points change value with respect to the x coordinate of the mouse,
hence creating an effect of the object rotating with movement of the mouse.
*/

struct points p[20]; //array of 20 points

void main()
{
int k,i,dstatus=0,gd=DETECT,gm,p=0;
char c,stringx[5],stringy[5];
clrscr();
while(1)
{
printf("Enter your choice:\n0) Rotating X-below xyline\n1) self inverting pyramid\n2) 3D rotating X below xy line\n3) 3D rotating cuboid\n");//4) 3D rotating cuboid above xy line");
printf("\n\nEnter -1 to exit");
scanf("%d",&p);
if(p==-1)
exit(0);
else
choice=p;
in.x.ax=3;
assignvalues();

for(k=0;k<20;k++)
{initialize(k);}


initgraph(&gd,&gm,""); 
while(1)
{
while(!kbhit())
{
cleardevice(); //clears screen
callfunction(); //calculates points coordinates according to the position of the mouse

if(dstatus==1) // display x,y axes
{
line(320,0,320,480);
line(0,240,640,240);
}

int86(0X33,&in,&out);
mousex=out.x.cx-ox; //get x coordinate of mouse position
mousey=out.x.dx-oy; //get y coordinate of mouse position

itoa(mousex,stringx,10); //parse integer mousex to string stringx
itoa(mousey,stringy,10); //parse integer mousey to string stringy

//display stringx and stringy ,i.e. the current mouse position coordinates
outtextxy(5,10,"X:");
outtextxy(65,10,"Y:");
outtextxy(20,10,stringx);
outtextxy(85,10,stringy);
outtextxy(10,20,"Press d to view axes(x & y)");
outtextxy(10,30,"Press q to quit");

circle(out.x.cx,out.x.dx,5);//circle at mouse position

if(out.x.bx==1) //if left mouse button is pressed, 
circle(out.x.cx,out.x.dx,10); //double circle at mouse position
dstatus=0;
delay(50);
}

c=getch(); //input char 'd' for displaying axes 
if(c=='d' || c=='D')
{dstatus=1;}

if(c=='q' || c=='Q') //press q to quit
break;
}

}
getch();
closegraph();
}

void initialize(int p1) // initializes points - calculates value of alpha, beta, gama and r from x,y,z
{
float a;
p[p1].r=sqrt((p[p1].x*p[p1].x)+(p[p1].y*p[p1].y)+(p[p1].z*p[p1].z));
a=sqrt((p[p1].x*p[p1].x)+(p[p1].z*p[p1].z));

if(p[p1].x<0)
a=a*-1;

if(a==0)
{p[p1].alpha=0;}
else
{p[p1].alpha=asin(p[p1].z/a);}

}

void function(int p1,int p2)
{
int w=1;
float px,py,pz,pr,palpha,pbeta,pgama,prxz;
float qx,qy,qz,qr,qalpha,qbeta,qgama,qrxz;

px=p[p1].x;py=p[p1].y;pz=p[p1].z;pr=p[p1].r;palpha=p[p1].alpha;
prxz=sqrt((pr*pr)-(py*py));

qx=p[p2].x;qy=p[p2].y;qz=p[p2].z;qr=p[p2].r;qalpha=p[p2].alpha;
qrxz=sqrt((qr*qr)-(qy*qy));

delalpha=(0.0349065*0.5*mousex);
delgama=(0.0349065*0.5*mousey);

if(px<0)
w=-1;
else
w=1;
px=w*prxz*cos(palpha+delalpha);
if(pz<0)
w=-1;
else
w=1;
pz=w*prxz*sin(palpha+delalpha);

if(qx<0)
w=-1;
else
w=1;
qx=w*qrxz*cos(qalpha+delalpha);
if(qz<0)
w=-1;
else
w=1;
qz=w*qrxz*sin(qalpha+delalpha);

line3d(qx+ox,qy+oy,qz+oz,px+ox,py+oy,pz+oz);
}
 /*
 graphics.h library only displays the 4th quadrant of the graph on the screen.
 Therefore, the origin is at the top left corner of the screen.
 To bring the contents of the graph to the center of the screen, we need to transpose it to the "screen's center". 
 line3d() function does this task
 	it accepts x,y,z coordinates of 2 points,
	calculates the 2d projection coordinates of the line,
	plot them with respect to shifted origin 
 */
void line3d(float px,float py,float pz,float qx,float qy,float qz) 
{
float q1x=((100*(qx-ox))/(qz+100))+ox;
float q1y=((100*(qy-oy))/(qz+100))+oy;
float p1x=((100*(px-ox))/(pz+100))+ox;
float p1y=((100*(py-oy))/(pz+100))+oy;

line(p1x,p1y,q1x,q1y);

}


void assignvalues() //assign x, y, z coordinates to points with respect to the choice made 
{

if(choice==0)
{
p[0].x=100;p[0].y=100;p[0].z=80;  //rotating X-below xyline
p[1].x=100;p[1].y=200;p[1].z=80;
p[2].x=200;p[2].y=100;p[2].z=80;
p[3].x=200;p[3].y=200;p[3].z=80;
}
if(choice==1)
{
p[0].x=100;p[0].y=100;p[0].z=50;        //self inverting pyramid
p[1].x=-100;p[1].y=100;p[1].z=50;
p[2].x=100;p[2].y=100;p[2].z=-50;
p[3].x=-100;p[3].y=100;p[3].z=-50;
p[4].x=1;p[4].y=-200;p[4].z=1;
}
if(choice==2)
{
p[0].x=100;p[0].y=100;p[0].z=50;     //3D rotating X below xy line
p[1].x=100;p[1].y=200;p[1].z=50;
p[2].x=200;p[2].y=100;p[2].z=50;
p[3].x=200;p[3].y=200;p[3].z=50;
p[4].x=100;p[4].y=100;p[4].z=100;
p[5].x=100;p[5].y=200;p[5].z=100;
p[6].x=200;p[6].y=100;p[6].z=100;
p[7].x=200;p[7].y=200;p[7].z=100;
}
if(choice==3)
{
p[0].x=100;p[0].y=100;p[0].z=50;   //3D rotating cuboid
p[1].x=100;p[1].y=200;p[1].z=50;
p[2].x=200;p[2].y=100;p[2].z=50;
p[3].x=200;p[3].y=200;p[3].z=50;
p[4].x=100;p[4].y=100;p[4].z=100;
p[5].x=100;p[5].y=200;p[5].z=100;
p[6].x=200;p[6].y=100;p[6].z=100;
p[7].x=200;p[7].y=200;p[7].z=100;
}
if(choice==4)
{
p[0].x=100;p[0].y=100-300;p[0].z=50;   //3D rotating cuboid above xy line
p[1].x=100;p[1].y=200-300;p[1].z=50;
p[2].x=200;p[2].y=100-300;p[2].z=50;
p[3].x=200;p[3].y=200-300;p[3].z=50;
p[4].x=100;p[4].y=100-300;p[4].z=100;
p[5].x=100;p[5].y=200-300;p[5].z=100;
p[6].x=200;p[6].y=100-300;p[6].z=100;
p[7].x=200;p[7].y=200-300;p[7].z=100;
}
}

void callfunction() //this function creates a line between points with respect to the choice made to create a particular structure
{
if(choice==0)
{
function(0,2);   //rotating X below xyline
function(2,1);
function(1,3);
function(3,0);
}
if(choice==1)
{
function(0,1);   // self inverting PYRAMID
function(3,2);
function(1,3);
function(2,0);
function(4,0);
function(4,1);
function(4,2);
function(4,3);
}
if(choice==2)        //3D rotating X below xy line
{
function(0,1);
function(1,2);
function(2,3);
function(3,0);
function(4,5);
function(5,6);
function(6,7);
function(7,4);
function(0,4);
function(1,5);
function(2,6);
function(3,7);
}
if(choice==3)        //3D rotating cuboid
{
function(0,1);
function(1,3);
function(3,2);
function(2,0);
function(4,5);
function(5,7);
function(7,6);
function(6,4);
function(0,4);
function(1,5);
function(2,6);
function(3,7);
}
if(choice==4)        //3D rotating cuboid above xy line
{
function(0,1);
function(1,3);
function(3,2);
function(2,0);
function(4,5);
function(5,7);
function(7,6);
function(6,4);
function(0,4);
function(1,5);
function(2,6);
function(3,7);
}
}