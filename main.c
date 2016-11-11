

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <math.h>
#include "SOIL.h"
#pragma comment( lib, "DevIL.lib" )
#pragma comment( lib, "ILU.lib" )
#define PNG_DEBUG 3
#define PI 3.14

#define BLUE 1
#define RED 2
#define CYAN 3
#define GREEN 4
#define PINK 5
#define BLACK 6
#define YELLOW 7

#define PENCIL 1
#define TRIANGLE 2
#define RECTANGLE 3
#define LINE 4
#define CIRCLE 5

#define SAVE 1
#define OPEN 2


#define ww 1600 // Window's size
#define wh 810
#define GL_GLEXT_PROTOTYPES

# define GLAPI extern
# define GLAPIENTRY
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
int x,y;
int WIDTH=ww, HEIGHT=wh;
int width,height;
//GLuint texture[1];
int leftButtonState = 0;
int fill = 0;
//int x=0,y=0;
int click=0;
int  toolMenu, mainMenu, colorMenu,chosen, fileMenu;
float color[3]={0.0,0.0,0.0};
float holdColor[3]={0.0,0.0,0.0};
int menuStatus=0; // 0- OFF, 1- ON
void drawArea()
{
    glDisable(GL_TEXTURE_2D);
    /*MENU DRAWS*/
    glColor3f(0.329,0.329,0.329);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(50,0);
    glVertex2f(50,wh);
    glVertex2f(0,wh);
    glEnd();
    glFlush();
    glutSwapBuffers();

glColor3f(0,0,0);
glLineWidth(7);
glBegin(GL_LINES);

glVertex2i(53, 0);
glVertex2i(53, wh);
glEnd();
glFlush();
glLineWidth(5);
drawButton(0,wh-500,25,wh-475,0,0,0);//BLACK
drawButton(25,wh-500,50,wh-475,0,0,1);//BLUE
drawButton(0,wh-475,25,wh-450,1,0,0);//RED
drawButton(25,wh-475,50,wh-450,0,1,0);//GREEN
drawButton(0,wh-450,25,wh-425,0,1,1);//CYAN
drawButton(25,wh-450,50,wh-425,1,0,1);//PURPLE
drawButton(0,wh-425,25,wh-400,1,1,1);//WHITE
drawButton(25,wh-425,50,wh-400,1,1,0);//YELLOW
int i=0;
int xBut=0,yBut=25;
for(;i<6;i++) //TOOL MENU BUTTONS
{
    glColor3f(0.5,1.0,0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(xBut,wh-yBut);
    glVertex2f(xBut+50,wh-yBut);
    glVertex2f(xBut+50,wh-(yBut+25));
    glVertex2f(xBut,wh-(yBut+25));
    glEnd();
    glFlush();
    glutSwapBuffers();
    yBut+=35;

}
/*CIRCLE*/
if(fill == 1)
{
    int i;
	int triangleAmount = 50;
	GLfloat radius = 8.0f;
	GLfloat x = 24.0f;
	GLfloat y = wh-142.0f;
	GLfloat twicePi = 2.0f * PI;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color[0],color[1],color[2]);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
	glFlush;
	glutSwapBuffers();
}
else
{
       float ii;
      glBegin(GL_LINE_LOOP);
      glColor3f(color[0],color[1],color[2]);
    for (ii = 0; ii < 75; ii++)   {
        float theta = 2.0f * 3.1415926f * ii / 75.0;//get the current angle
        float cx = 8.0f * cosf(theta);//calculate the x component
        float cy = 8.0f * sinf(theta);//calculate the y component
        glVertex2f(cx + 24.0f, cy + wh-142.0f);//output vertex

}
    glEnd();
	glFlush;
	glutSwapBuffers();
}

drawTriangle(24,wh-30,15,wh-45,35,wh-45);
drawRectangle(15,wh-65,35,wh-80);
drawLine(15,wh-100,35,wh-115); /*PENCIL*/
drawLine(5,wh-170,25,wh-170);/*PENCIL*/
drawLine(5,wh-185,25,wh-185);/*PENCIL*/
drawLine(5,wh-170,5,wh-185);/*PENCIL*/
drawLine(25,wh-170,25,wh-185);/*PENCIL*/
drawLine(25,wh-169,40,wh-177);/*PENCIL*/
drawLine(25,wh-186,40,wh-177);/*PENCIL*/
holdColor[0]=color[0];holdColor[1]=color[1];holdColor[2]=color[2];
color[0]=0;color[1]=0;color[2]=0;
drawLine(20,wh-205,20,wh-220);/*FILL*/
drawLine(20,wh-205,30,wh-205);/*FILL*/
drawLine(20,wh-210,27,wh-210);/*FILL*/
color[0]=holdColor[0];color[1]=holdColor[1];color[2]=holdColor[2];


/*END OF MENU DRAWS*/
}
/*
###### TOOLS #####
*/

/*void drawBitmapText(char *string,int x,int y,float z)
{
		char *c;
	glRasterPos2i(x, y);

	for (c=string; *c != ' '; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}*/
int xPos1, yPos1, xPos2, yPos2,xPos3,yPos3;
void drawLine(int x1, int y1, int x2, int y2)
{
//glClear(GL_COLOR_BUFFER_BIT);
//glLineWidth(5.0);
glColor3f(color[0],color[1],color[2]);
glBegin(GL_LINES);
glVertex2i(x1, y1);
glVertex2i(x2, y2);
glEnd();
glFlush();
}
void pencil(int x1,int y1,int x2, int y2)
{
    glColor3f(color[0], color[1], color[2]);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glVertex2f(x1,y2);
    glEnd();
    glFlush();
    glutSwapBuffers();
}
void drawRectangle(int x1,int y1,int x2, int y2)
{
    glColor3f(color[0], color[1], color[2]);
    if(fill == 0)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glVertex2f(x1,y2);
    glEnd();
    glFlush();
    glutSwapBuffers();
}

void drawTriangle(int x1,int y1,int x2,int y2,int x3,int y3){

    glColor3f(color[0], color[1], color[2]);
if(fill == 0)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
else
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glBegin(GL_TRIANGLES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
	glEnd();
	glFlush;
	glutSwapBuffers();
}
void drawCircle(GLfloat x, GLfloat y, GLfloat r){
    if(fill == 0)
    {
        float ii;
      glBegin(GL_LINE_LOOP);
      glColor3f(color[0],color[1],color[2]);
    for (ii = 0; ii < 75; ii++)   {
        float theta = 2.0f * 3.1415926f * ii / 75.0;//get the current angle
        float cx = r * cosf(theta);//calculate the x component
        float cy = r * sinf(theta);//calculate the y component
        glVertex2f(cx + x, cy + y);//output vertex
    }
    //glEnd();
    }

    if(fill == 1)
    {
 int i;
	int triangleAmount = 50;
	/*GLfloat radius = 8.0f; radius*/
	GLfloat twicePi = 2.0f * PI;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color[0],color[1],color[2]);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (r* cos(i *  twicePi / triangleAmount)),
			    y + (r * sin(i * twicePi / triangleAmount))
			);
		}
    }
	glEnd();
	glFlush;
	glutSwapBuffers();
}
/*
###### END OF TOOLS ######
*/
/*
######  MENUS   ######
*/
void processMenuStatus(int status, int x, int y) {

	if (status == GLUT_MENU_IN_USE)
		menuStatus = 1;
	else
		menuStatus = 0;
}
void processMainMenu(int option) {

}



void processFileMenu(int option){
    char *fileName=malloc(sizeof(char)*32);
    switch(option){
    case SAVE: printf("SAVE FILE");printf("Enter file name to save as: ");
    scanf("%s",fileName);save_file(fileName);break;
    case OPEN: printf("OPEN FILE");printf("Enter file name to load: ");
    scanf("%s",fileName);display_image(fileName);break;
        }

}

void createMenu() {


	fileMenu=glutCreateMenu(processFileMenu);

	glutAddMenuEntry("Save",SAVE);
	glutAddMenuEntry("Open",OPEN);

    mainMenu = glutCreateMenu(processMainMenu);


    glutAddSubMenu("File",fileMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMenuStatusFunc(processMenuStatus);

}
/*
######  END OF MENUS   ######
*/
/*
#####   MOUSE   ######
*/
void mouse(int button,int state,int x,int y)
{
printf("\n\n x=%d y=%d",x,y);

if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN && chosen == LINE && x>50)
{
switch(click)
{
case 0:
xPos1 = x;
yPos1 = (wh-y);
click = 1;
break;
case 1:
xPos2 = x;
yPos2 = (wh-y);
drawLine(xPos1,yPos1,xPos2,yPos2);
click = 0;
break;
}
}
/*TRIANGLE*/
if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && chosen== TRIANGLE && x>50)
{
   switch(click)
   {
   case 0:
    xPos1=x;
    yPos1=(wh-y);
    click =1;
    break;
   case 1:
    xPos2=x;
    yPos2=(wh-y);
    click=2;
    break;
   case 2:
    xPos3=x;
    yPos3=(wh-y);
    drawTriangle(xPos1,yPos1,xPos2,yPos2,xPos3,yPos3);
    click=0;
    break;
   }
}
/*CIRCLE*/
if(button == GLUT_LEFT_BUTTON && state== GLUT_DOWN && chosen == CIRCLE && x>50)
{
     int radius=0;
    switch(click){
case 0:
    xPos1=x;
    yPos1=wh-y;
    click++;
    break;
case 1:
    xPos2=x;
    yPos2=wh-y;
    radius = sqrt(pow((double)(xPos1-xPos2),2)+pow((double)(yPos1-yPos2),2));
    drawCircle(xPos1,yPos1,radius);
    click=0;
    break;
    }

}
/*RECTANGLE*/
if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && chosen == RECTANGLE  && x>50)
{
    switch(click)
    {
    case 0:
        xPos1=x;
        yPos1=wh-y;
        click++;
        break;
    case 1:
        xPos2=x;
        yPos2=wh-y;
        drawRectangle(xPos1,yPos1,xPos2,yPos2);
        click= 0;
        break;
    }
}
/*PENCIL*/
if(button == GLUT_LEFT_BUTTON)
{
if(state == GLUT_DOWN)
    leftButtonState = 1;
    else
        leftButtonState = 0;
}
/*TOOL LIST*/
if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && x>0 && x<50 && y>25 && y<50)
{
    chosen = TRIANGLE;
    click = 0;
}
if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && x>0 && x<50 && y>60 && y<85)
{
    chosen = RECTANGLE;
    click = 0;
}
if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && x>0 && x<50 && y>95 && y<120)
{
    chosen = LINE;
    click = 0;
}
if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && x>0 && x<50 && y>130 && y<155)
{
    chosen = CIRCLE;
    click = 0;
}
if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && x>0 && x<50 && y>165 && y<190)
{
    chosen = PENCIL;
    click=0;
}
/*END OF TOOL LIST*/
if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && x>0 && x<50 && y>200 && y<225)
{
    if(fill == 1)
        fill = 0;
    else
        fill = 1;
}
/*COLOR LIST*/

if(button == GLUT_LEFT_BUTTON && state==GLUT_UP && x>0 && x<25 && y<500 && y>475)//BLUE
{
    color[0]=0;
    color[1]=0;
    color[2]=0;
}
 if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>0 && x<25 && y<475 && y>450)//RED
{
    color[0]=1;
    color[1]=0;
    color[2]=0;
}
 if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>0 && x<25 && y<450 && y>425)//CYAN
{
    color[0]=0;
    color[1]=1;
    color[2]=1;
}
 if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>0 && x<25 && y<425 && y>400)//WHITE
{
    color[0]=1;
    color[1]=1;
    color[2]=1;
}

 if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>25 && x<50 && y<425 && y>400)//YELLOW
{
    color[0]=1;
    color[1]=1;
    color[2]=0;
}
 if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>25 && x<50 && y<450 && y>425)//PURPLE
{
    color[0]=1;
    color[1]=0;
    color[2]=1;
}
 if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>25 && x<50 && y<475 && y>450)//GREEN
{
    color[0]=0;
    color[1]=1;
    color[2]=0;
}
 if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>25 && x<50 && y<500 && y>475) //BLUE
{
    color[0]=0;
    color[1]=0;
    color[2]=1;
}

/*END OF COLOR LIST*/
}

void motionFunc(int mousex,int mousey)
{
   if(leftButtonState==1 && chosen == PENCIL && mousex > 50)//PENCIL
    {
    int xpos=mousex;
	int ypos=wh-mousey;
	pencil(xpos,ypos,xpos+3,ypos+3);//PENCIL
	//printf("RUNS\n\n");
	glutSwapBuffers();
	glFlush();
    }

}
void keyboard(unsigned char key, int x, int y)
{
    int state = glutGetModifiers();
if((key == 'n' || key == 'N' ) && GLUT_ACTIVE_ALT==state)/*CLEAR SCREEN*/
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glClearColor(1,1,1,1);
	glutSwapBuffers();
	glutPostRedisplay();
	drawArea();
	}
else if(key == 'P' || key == 'p')/*PENCIL SHORTCUT*/
{
    printf("PRESSED P\n");
  chosen = PENCIL;
  glutPostRedisplay();

}else if(key == 't' || key == 'T')/*TRIANGLE SHORTCUT*/
{
    printf("PRESSED T\n");
    chosen=TRIANGLE;
    glutPostRedisplay();

}
else if(key == 'l' || key == 'L')/*LINE SHORTCUT*/
{
    printf("PRESSED L\n");
    chosen=LINE;
    glutPostRedisplay();
}
else if(key == 'r' || key == 'R')/*RECTANGLE SHORTCUT*/
{

    printf("PRESSED R\n");
    chosen=RECTANGLE;
    glutPostRedisplay();
}
else if(key == 'c' || key == 'C')/*CIRCLE SHORTCUT*/
{
    printf("PRESSED C\n");
    chosen=CIRCLE;
    glutPostRedisplay();
}
else if(key == ' ')
{
    printf("PRESSED SPACE\n");
    click = 0;
}

else if( key == 'f' || key== 'F')
{
    if(fill == 0)
    {
        fill = 1;
        printf("FILL\n");
        drawArea();
;    }
    else
    {
        fill = 0;
        printf("DON'T FILL\n");
drawArea();
    }
}
}
/* SAVE */
void save_file(char* file_name)
{
    /*SETS MENU'S COLORS AS BACKGROUND'S COLOR*/
    glColor3f(1,1,1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(56,0);
    glVertex2f(56,wh);
    glVertex2f(0,wh);
    glEnd();
    glFlush();
    glutSwapBuffers();
    ILuint imageID = ilGenImage();
    ilBindImage(imageID);
    ilutGLScreen();
    ilEnable(IL_FILE_OVERWRITE);
    ilSaveImage(file_name);
    ilDeleteImage(imageID);
    printf("File saved to: %s\n", file_name);
    drawArea();
    }



/* Load an image using DevIL and return the devIL handle (-1 if failure) */
GLuint loadIm(char *file_name)
{
   glEnable(GL_TEXTURE_2D);

    GLuint texture_id;
    glGenTextures(1, &texture_id);
width,height;

    glBindTexture(GL_TEXTURE_2D, texture_id);

    unsigned char *image = SOIL_load_image(file_name, &width, &height, 0, SOIL_LOAD_RGBA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);


    printf("Width: %d \n Height: %d\n",width,height);
    printf("Texture ID: %d\n",texture_id);
    printf("Data: %p",image);

    SOIL_free_image_data(image);

    if (texture_id == -1) {
        return -1;
    }

    return texture_id;

}
void display_image(char* file_name)
{
    GLuint texture_id=loadIm(file_name);
glClear(GL_COLOR_BUFFER_BIT);
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture_id);
glLoadIdentity();
glColor3f(1, 1, 1);
glFrontFace(GL_CCW);
glCullFace(GL_FRONT);
glBindTexture(GL_TEXTURE_2D, texture_id);
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_QUADS);
glTexCoord2f(0,1); glVertex2f(0,    0.0);
glTexCoord2f(0,0); glVertex2f(0,  wh);
glTexCoord2f(1,0); glVertex2f(ww,wh);
glTexCoord2f(1,1); glVertex2f(ww, 0.0);
glEnd();
glFlush();
glutSwapBuffers();
drawArea();

}

void reshape()
{

}

void myinit()
{
glViewport(0,0,ww,wh);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);
glMatrixMode(GL_MODELVIEW);
}

void drawButton(int x1,int y1,int x2,int y2,int r,int g,int b)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glVertex2f(x1,y2);
    glEnd();
    glFlush();
    glutSwapBuffers();
}

//glutPostRedisplay();

int main(int argc, char** argv){
glutInit(&argc,argv);
printf("glut has been initialized\n");
ilInit();
ilutRenderer(ILUT_OPENGL);
printf("DevIL has been initialized\n");
glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
glutInitWindowPosition(0,0);
glutInitWindowSize(ww,wh);
glutCreateWindow("Best Graphic Editor Ever");
glLineWidth(3.5);
glClearColor(1,1,1,1); // BACKGROUND COLOR
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glutDisplayFunc(drawArea);
myinit();
/*CALLBACK*/
glutReshapeFunc(reshape);
glutMouseFunc(mouse);
glutMotionFunc(motionFunc);
glutKeyboardFunc(keyboard);
createMenu();
glutMainLoop();
return 1;
}
