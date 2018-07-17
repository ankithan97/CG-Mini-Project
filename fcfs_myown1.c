#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include<GL/glut.h>

typedef struct 
{
	//burst time,arrival time,process no
	int bt,at,pno,st,ct,wt,tt;
	char name;
}process;
process p[5];

void display();
void repeat();

int flag=0,exit_status=0,ip=0,done=0;
int z;
char a;
int numb;
int count=0,count1=0,temp;
int one=1,np=1,n=0,ind,att,btt,btotal=0,keypa=1,same[8];
float basic=36.0;

int counter=0;

//predefining the colours for each process
float col[5][3]={{.91,.80,.35},{.28,.21,.33},{0.6,.3,.5},{.3,1.0,0.73},{0.3,.75,.71}};

void delay()
{
	for(int i=0;i<35000;i++)
	for(int j=0;j<5000;j++);
}

void delay2()
{
	for(int i=0;i<35000;i++)
	for(int j=0;j<10000;j++);
}

void drawString(double x,double y,const char *string)
{
	const char *c;
	glRasterPos2f(x,y);
	for(c=string;*c!='\0';c++)
	    glutBitmapCharacter( GLUT_BITMAP_8_BY_13 , *c );
}

//p--string,n---length of string p,x and y are position of the string to be displayed
void strin(char p[],int n,GLint x,GLint y)
{
	glRasterPos2f(x,y);
	for(int i=0;i<n;i++)
	{
	    glutBitmapCharacter( GLUT_BITMAP_8_BY_13 , p[i] );
	}
}//prints string


void constr()
{
	int p=15,q=665;
	glColor3f(0,0.2,1);
	strin("Constraints On Input:",21,p,q);
	strin("_____________________",21,p,q-4);
	strin("1.Number of processes limited to 5.",35,p,q-(30*1));
	strin("2.All processes must arrive before 7sec and all the processes arrival must be continuous.",90,p,q-(30*2));
	strin("3.Two processes cannot have same Arrival Time.",46,p,q-(30*3));
	strin("4.Burst Time must be less than or equal to 5.",45,p,q-(30*4));
	glFlush();
}


void introPage()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	drawString(370.0,700.0,"PES INSTITUTE OF TECHNOLOGHY - BSC");
	glColor3f(0.7,0,1);
	drawString(320.0,650.0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	glColor3f(1,0.5,0);
	drawString(350.0,600.0,"A MINI PROJECT ON DISK SCHEDULING ALGORITHM-");
	glColor3f(1,0,0);
	drawString(380.0,550.0,"FCFS(First Come First Served)");
	glColor3f(1,1,0);
	drawString(100.0,400.0,"BY:");
	glColor3f(1,1,1);
	drawString(100.0,350.0,"B.RESHMA(1PE15CS192)");
	glColor3f(1,1,1);
	drawString(100.0,300.0,"ANKITHA.N(1PE15CS191)");
	glColor3f(1,1,0);
	drawString(800.0,400.0,"GUIDES:");
	glColor3f(1,1,1);
	drawString(800.0,350.0,"MS.EVLIN VIDYU LATHA");
	glColor3f(1,1,1);
	drawString(800.0,300.0,"MS.LAKSHMI NAGA PRASANNA");
	glColor3f(0,1,1);
	drawString(430.0,200.0,"RIGHT CLICK FOR THE MENU");
	glColor3f(1,1,1);

	//animation
	if(flag == 0) {
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_POLYGON);
			glVertex2f(counter*2+50,100);
			glVertex2f(counter*2+50,125);
			glVertex2f(counter*2+120,125);
			glVertex2f(counter*2+120,100);
		glEnd();
		counter++;
		if(counter>400)
			counter=0;
	}
	glutSwapBuffers();
	glutPostRedisplay();

}

void reshape(int w,int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	keypa=1;
}

void myinit()
{
	glClearColor(.07,.07,.07,0.0);
	glColor3f(0.0,0.87,.803);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0,1000,0,800);
	for(int i=0;i<=7;i++)
		same[i]=1;
	glMatrixMode(GL_PROJECTION);
}


void mouse(int bt,int st,int x,int y)
{
	//button,state
	if(bt==GLUT_LEFT_BUTTON && st==GLUT_DOWN)
		printf("\n%d\n%d",x,400-y);
}

void drawrec(int p,int q,int r, int s)
{
	glBegin(GL_POLYGON);
		glVertex2f(p,q);
		glVertex2f(p,s);
		glVertex2f(r,s);
		glVertex2f(r,q);
	glEnd();
}



//inserting arrival time , burst time and polygons in the table
void pro()
{
	int j;
	char a;
	for( j=0;j<n;j++)
	{
		a='0'+p[j].at;
		strin(&a,1,175,378-(25*(j+2)));
		a='0'+p[j].bt;
		strin(&a,1,265,378-(25*(j+2)));
	}

	//drawing the polygons in table
	for(int i=0;i<n;i++)
	{
		glColor3fv(col[i]);
		drawrec(355,378-(25*(i+1)),355+p[i].bt*36,400-(25*(i+1)));		
	}
	glFlush();
	delay2();
	delay2();
}


void s(int *a,int *b)
{
	int te;
	te=*a;
	*a=*b;
	*b=te;
}


void c(char *a,char *b)
{
	char te;
	te=*a;
	*a=*b;
	*b=te;
}


void swap(int x,int y)
{
	s(&p[x].at,&p[y].at);
	s(&p[x].bt,&p[y].bt);
	c(&p[x].name,&p[y].name);
	s(&p[x].pno,&p[y].pno);
}


void sort()
{
	int i,j;
	for(i=0;i<n;i++) 
	{
		for(j=0;j<n-1;j++) 
		{
			if(p[j].at>p[j+1].at)
			{
				swap(j,j+1);
			}
		}
	}
}


void setcst()
{
	for(int i=0;i<n;i++)
	{
		if(i==0)
		{
			p[i].ct=p[i].bt+p[i].at;
			p[i].st=p[i].at;
		}
		else if(p[i].at<p[i-1].ct)
		{
			p[i].ct=p[i].bt+p[i-1].ct;
			p[i].st=p[i-1].ct;
		}
		else
		{
			p[i].ct=p[i].at+p[i].bt;
			p[i].st=p[i].at;
		}
	}
}


void drawscale()
{
	int i,j;
	char a;
	glLineWidth(2.0);
	strin("Gantt Chart",11,30,158+40);
	strin("___________",11,30,156+40);
	//for the horizontal line and small vertical lines on the gantt chart
	glBegin(GL_LINES);
		glVertex2i(30,145);
		glVertex2i(931,145);
		for(i=1;i<=25;i++)
		{
			glVertex2f(30+basic*i,145);
			glVertex2f(30+basic*i,141);
		}
	glEnd();

	//for the numbers on the gantt chart
	for(i=0,j=0;i<=25;i++)
	{
		if(i<10)
		{
			a='0'+i;
			strin(&a,1,27+basic*i,147);
		}
		else if(i>9 && i<20)
		{
			j=1;
			a='0'+j;
			strin(&a,1,24+basic*i,147);
			a='0'+(i%10);
			strin(&a,1,32+basic*i,147);
		}
		else
		{
			j=2;
			a='0'+j;
			strin(&a,1,24+basic*i,147);
			a='0'+(i%10);
			strin(&a,1,32+basic*i,147);
		}
	}
	glFlush();
	glutSwapBuffers();
}


void arri(int po)
{

	//arrival of processes on the gantt chart
	for(int i=0;i<n;i++)
	{
		if(p[i].at<=p[po].ct)
		{
			glColor3fv(col[i]);
			strin("P",1,30+36*p[i].at-8,173);
			strin(&p[i].name,1,30+36*p[i].at,173);
			glBegin(GL_LINES);
			glVertex2i(30+36*p[i].at,170);
			glVertex2i(30+36*p[i].at,160);
			glVertex2i(30+36*p[i].at+2,163);
			glVertex2i(30+36*p[i].at,160);
			glVertex2i(30+36*p[i].at-2,163);
			glVertex2i(30+36*p[i].at,160);
			glEnd();
		}
	}
	glFlush();
	glColor3f(0.0,0.87,.803);
}

//print number
void prinum(int x,int y,float num)
{
	int r=(int)num,q=(((int)(num*10))%10),p=(((int)(num*100))%10);
	char a;
	a='0'+r;
	strin(&a,1,x,y);
	strin(".",1,x+8,y);
	a='0'+q;
	strin(&a,1,x+16,y);
	a='0'+p;
	strin(&a,1,x+24,y);
	glFlush();
}

//computations
void avg()
{
	
	float awt,atat;
	float ata=0,wt=0;
	float cum=0,swt=0,stt=0;

	//p[0].wt=p[0].at;
	p[0].wt=0;
    	p[0].tt = p[0].bt;
	
	// calculate waiting time and turnaround time
	for(int i=1; i<n; i++) 
	{
		for(int k=0; k<i; k++) 
		{	
			cum = cum + p[k].bt;
		}
	//p[i].waiting_time = p[i-1].burst_time + p[i-1].waiting_time - p[i].arrival_time;
		p[i].wt = cum - p[i].at;
		p[i].tt = p[i].wt + p[i].bt;
		cum=0;
    	}

	// calculate sum of waiting time and sum of turnaround time
	for(int i=0; i<n; i++)
	 {
	       swt += p[i].wt;
	       stt += p[i].tt;
	 }

	awt=(float)swt/n;
	atat=(float)stt/n;
	printf("the average waiting time is %2f \n",awt);
	printf("the average turn around time is %2f \n",atat);
	glColor3f(0,0,0);	
	strin("Average Wait Time =",19,30,70);
	strin("Average Turn Around Time =",26,30,45);
	prinum(185,70,awt);
	prinum(245,45,atat);
	glFlush();
	glutSwapBuffers();
}

void gchart()
{
	int i;
	float me;
	//sort();
	drawscale();
	basic=34;


	//displaying the polygons in the gantt chart
	for(i=0;i<n;i++)
	{
		glColor3fv(col[i]);
		drawrec(30+p[i].st*36,100,30+p[i].ct*36,130);
		glLineWidth(2.0);
		glColor3fv(col[i]);
		me=(30+p[i].st*36+30+p[i].ct*36)/2;
		strin("P",1,me-8,88);
		strin(&p[i].name,1,me,88);
		arri(i);
		glFlush();
		glutSwapBuffers();
		delay2();
	}

	glLineWidth(1.0);
	glColor3f(1,.84,.0);
	avg();
}

void table()
{
	int p,q,r,s,i;
	char a;
	keypa=0;
	glColor3f(0,.84,.0);
	p=30;
	q=375-(25*(1+n));
	s=375;
	r=330;
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(p,q);
		glVertex2i(p,s);
		glVertex2i(r,s);
		glVertex2i(r,q);
	glEnd();
	glBegin(GL_LINES);
		glVertex2i(130,s);
		glVertex2i(130,q);
		glVertex2i(233,s);
		glVertex2i(233,q);
		glVertex2i(p,350);
		glVertex2i(r,350);
	glEnd();
	strin("Process",7,55,355);
	strin("Arrival time",12,135,355);
	strin("Burst time",10,240,355);
	for( i=1;i<=n;i++)
	{
		strin("P",1,75,378-(25*(i+1)));
		a='0'+i;
		strin(&a,1,83,378-(25*(i+1)));
	}
	
	pro();
	glFlush();
	glutSwapBuffers();
	glLineWidth(1.0);
	glColor3f(0.0,0.0,0.0);
	gchart();
}

void setname()
{
	for(int i=0;i<n;i++)
	{
		p[i].name='0'+i+1;
		p[i].pno=i+1;
	}
}

void example()
{
	p[0].at=0;
	p[1].at=2;
	p[2].at=1;
	p[3].at=3;
	p[4].at=4;

	p[0].bt=3;
	p[1].bt=4;
	p[2].bt=5;
	p[3].bt=1;
	p[4].bt=3;
	n=5;
	setname();
	setcst();
	table();
	//glutSwapBuffers();	
}

void input1()
{
	ip=1;
	strin("ENTER THE NUMBER OF PROCESSES:",30,15,520);
	glFlush();
}

void input2()
{
	ip=2;
	strin("ENTER THE ARRIVAL TIMES OF PROCESSES:",37,15,500);
	glFlush();	
}

void input3()
{
	ip=3;
	strin("ENTER THE BURST TIMES OF PROCESSES:",35,15,500);
	glFlush();
}

void staticInput()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1,1,1,0);
	constr();
	example();	
}


void input()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1,1,1,0);
	constr();
	input1();
	glutSwapBuffers();
	
	
}

void dynamicInput()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1,1,1,0);
	constr();
	glFlush();
	setname();
	setcst();
	table();
	glFlush();
	
}



void menu(int id)
{
	switch(id)
	{
		case 1: flag=1;
			display();
			break;
		case 2: flag=2;
			display();
			break;
		case 3: exit(0);
			break;
			
	}
	glutPostRedisplay();

}

void display()
{
	if(exit_status == 1)
	{
		exit(0);
	}
	
	if(flag==0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		introPage();
		glFlush();
		
		
	}
	if(flag==1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1,1,1,0);
		glFlush();
		staticInput();
		glFlush();
		glutSwapBuffers();
		
	}
	if(flag==2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1,1,1,0);
		glColor3f(0,0,0);
		input();
	}
	
}


void myKey(unsigned char key,int x,int y)
{
	if((key == 'e' || key == 'E') && (flag == 1 || flag == 2))
	{
		exit_status=1;
		display();
		return;
	}

	char ch;
	if(ip==1)
	{
		a=key;
		numb=a-'0';
		n=numb;
		strin(&a,1,300,520);
		glFlush();
		glutSwapBuffers();
		delay();
		printf("%d\n",n);

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1,1,1,0);
		constr();
		glFlush();
		input2();
		glutSwapBuffers();			
	}
	
	if(ip==2)
	{
		if(count>=0 && count<=n)
		{
			if(count == 0)
				count++;
			else 
			{
				a=key;
				numb=a-'0';
				temp=numb;
				strin(&a,1,350,(500-10*(count-1)));
				p[count-1].at=temp;
				glFlush();
				glutSwapBuffers();
				delay();
				printf("%d\n",p[count-1].at);
				count++;
			}

			if(count == n+1) 
			{
				done=1;
			}
			
		}
		if(done == 1)
		{
			delay();
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1,1,1,0);
			constr();
			done=0;
			glFlush();
			input3();
			glutSwapBuffers();		
		}
		
	}

	
	if(ip==3)
	{
		if(count1>=0 && count1<=n)
		{
			if(count1 == 0)
				count1++;
			else 
			{
				a=key;
				numb=a-'0';
				temp=numb;
				strin(&a,1,350,(500-10*(count1-1)));
				p[count1-1].bt=temp;
				glFlush();
				glutSwapBuffers();
				delay();
				printf("%d\n",p[count1-1].bt);
				count1++;
			}

			if(count1 == n+1) 
			{
				done=1;
			}
			
		}
		if(done == 1)
		{
			delay();
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(1,1,1,0);
			constr();
			glFlush();
			done=0;
			dynamicInput();
		}
	}
	
}


int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("CG PROJECT----FCFS");
	myinit();
	int z=glutCreateMenu(menu);
	glutAddMenuEntry("STATIC INPUT",1);
	glutAddMenuEntry("DYNAMIC INPUT",2);
	glutAddMenuEntry("EXIT",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	/*call back functions*/
	glutDisplayFunc(display);
	glutKeyboardFunc(myKey);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}



