#include <glew.h> // glew.h must be included before gl.h/glu.h/freeglut.h
#include <freeglut.h>
#include <cstdio>
#include <cstdlib>

#define MENU_TIMER_START 1
#define MENU_TIMER_STOP 2
#define MENU_EXIT 3

const GLfloat tri_v1[3] = {-0.5f, -0.4f, 0.0f};
const GLfloat tri_v2[3] = { 0.5f, -0.4f, 0.0f};
const GLfloat tri_v3[3] = { 0.0f,  0.6f, 0.0f};

GLUquadricObj *quadratic;
int timer_cnt = 0;
bool timer_enabled = true;
unsigned int timer_speed = 16;

// Print OpenGL context related information.
void dumpInfo(void)
{
    printf("Vendor: %s\n", glGetString (GL_VENDOR));
    printf("Renderer: %s\n", glGetString (GL_RENDERER));
    printf("Version: %s\n", glGetString (GL_VERSION));
    printf("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
}


void Panda_Torso()
{

	glColor3ub(255,255,255);
	glScalef(1.0,1.1,0.9);

	glutSolidSphere(0.2,50,50);
	glColor3f(0,0,0);
	GLUquadric* neck;
	neck=gluNewQuadric();
	glTranslatef(0,0.2,0);
	glRotatef(90,1,0,0);
	gluCylinder(neck, 0.14, 0.18, 0.1, 30, 30);
	/*glColor3ub(0,0,0);
	glTranslatef(0.4,0,0);
	glRotatef(90,1,0,0);
	glutSolidCone(0.1,0.1,50,50);*/

}
void Panda_Head()
{

	glColor3ub(255,255,255);
	glScalef(1.1,1,1);
	glTranslatef(0,0.3,0);
	glutSolidSphere(0.25,50,50);

	glColor3f(0,0,0);
	glTranslatef(-0.18,0.17,0);
	glutSolidTorus(0.07,0.05,50,50);
	glTranslatef(0.36,0,0);
	glutSolidTorus(0.07,0.05,50,50);
	//glRotatef(45,0,1,1);
	//gluCylinder(obj, 5, 5, 10, 30, 30);

	//gluQuadricNormals(ear, GLU_SMOOTH);
	//gluCylinder(ear, 1.0, 1.0, 0.4, 10, 16);
}
void Panda_Upper_Hand()
{
	glColor3ub(0,0,0);
	glutSolidSphere(0.09,50,50);
	GLUquadric* upperArm;
	upperArm=gluNewQuadric();
	glTranslatef(-0.02,-0.05,0);
	glRotatef(90,1,-0.3,0);
	gluCylinder(upperArm, 0.05, 0.05, 0.18, 30, 30);

}
void Panda_Lower_Hand()
{
	glColor3ub(0,0,0);
	GLUquadric* lowerArm;
	lowerArm=gluNewQuadric();
	//glRotatef(90,1,-0.3,0);
	gluCylinder(lowerArm, 0.07, 0.065, 0.15, 30, 30);
	glColor3ub(0,0,0);
	glTranslatef(-0.005,0,0.19);
	glutSolidSphere(0.09,50,50);
}
void Panda_Upper_Leg()
{
	GLUquadric* upperLeg;
	upperLeg=gluNewQuadric();
	glRotatef(90,1,-0.2,0);
	gluCylinder(upperLeg, 0.07, 0.07, 0.3, 30, 30);
}
void Panda_Lower_Leg()
{
	GLUquadric* lowerLeg;
	lowerLeg=gluNewQuadric();
	//glRotatef(90,1,-0.3,0);
	gluCylinder(lowerLeg, 0.1, 0.1, 0.2, 30, 30);
}
void Panda_Left_Sole()
{
	GLUquadric* sole;
	sole=gluNewQuadric();
	glRotatef(90,-1,0.2,0);
	glScalef(1,0.8,1);
	gluCylinder(sole, 0.1, 0.1, 0.2, 30, 30);
	glTranslatef(0,-0.05,0.1);
	glScalef(1,0.6,1);
	glutSolidCube(0.2);
	glScalef(1,1.8,0.96);
	glTranslatef(0,0.05,0.08);
	glutSolidSphere(0.1,50,50);
	glTranslatef(0,0,-0.002);
	glRotatef(90,1,0,0);
	gluCylinder(sole,0.102,0.102,0.105,30,30);
	glRotatef(90,1,0,0);
	glScalef(1,0.98,1);
	glTranslatef(0,0.01,0.182);
	gluDisk(sole,0,0.1,30,30);
}
void Panda_Right_Sole()
{
	GLUquadric* sole;
	sole=gluNewQuadric();
	glRotatef(90,-1,0.2,0);
	glScalef(1,0.8,1);
	gluCylinder(sole, 0.1, 0.1, 0.2, 30, 30);
	glTranslatef(0,-0.05,0.1);
	glScalef(1,0.6,1);
	glutSolidCube(0.2);
	glScalef(1,1.8,0.96);
	glTranslatef(0,0.05,-0.08);
	glutSolidSphere(0.1,50,50);
	glTranslatef(0,0,-0.002);
	glRotatef(90,1,0,0);
	gluCylinder(sole,0.102,0.102,0.105,30,30);
	glRotatef(90,1,0,0);
	glScalef(1,0.98,1);
	glTranslatef(0,0.01,-0.182);
	glRotatef(180,0,0,0);
	gluDisk(sole,0,0.1,30,30);
}
void Panda_Wing()
{
	glColor3ub(255,0,85);
	GLUquadric* sole;
	sole=gluNewQuadric();
	glRotatef(90,0,1,0);
	glTranslatef(0.1,0.15,-0.6);
	glScalef(0.4,1,1);
	glRotatef(10,1,0,0);
	gluCylinder(sole, 0.15, 0.08, 0.5, 30, 30);
	gluCylinder(sole, 0.15, 0, 0.5, 30, 30);
}
void Render_Panda()
{
	//TORSO
	glPushMatrix();
		glTranslatef(0,-0.05,0);
		Panda_Torso();
	glPopMatrix();
	//HEAD&EARS
	glPushMatrix();
		glTranslatef(0,0.05,0);
		Panda_Head();
	glPopMatrix();
	//LEFT HAND
	glPushMatrix();
		glTranslatef(-0.22,0.085,0);
		Panda_Upper_Hand();
		glTranslatef(-0.0065,0,0.085);
		Panda_Lower_Hand();
	glPopMatrix();
	//RIGHT HAND
	glPushMatrix();
		glTranslatef(0.22,0.085,0);
		glRotatef(180,0,1,0);
		Panda_Upper_Hand();
		glTranslatef(-0.0065,0,0.085);
		Panda_Lower_Hand();
	glPopMatrix();
	//LEFT LEG
	glPushMatrix();
		glTranslatef(-0.1,-0.18,0);
		Panda_Upper_Leg();
		glTranslatef(-0.007,0,0.15);
		Panda_Lower_Leg();
		glTranslatef(-0.02,-0.1,0.22);
		Panda_Left_Sole();
	glPopMatrix();
	//RIGHT LEG
	glPushMatrix();
		glRotatef(180,0,1,0);
		glTranslatef(-0.1,-0.18,0);
		Panda_Upper_Leg();
		glTranslatef(-0.007,-0.01,0.15);
		Panda_Lower_Leg();
		glTranslatef(-0.02,-0.09,0.22);
		Panda_Right_Sole();
	glPopMatrix();
	//LEFT WING
	glPushMatrix();
		Panda_Wing();
	glPopMatrix();
	//RIGHT WING
	glPushMatrix();
		Panda_Wing();
	glPopMatrix();

}
// GLUT callback. Called to draw the scene.
void My_Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*glBegin(GL_TRIANGLES);
	{
		glColor3ub(timer_cnt, 0, 255 - timer_cnt);
		glVertex3fv(tri_v1);
		glColor3ub(255, timer_cnt, 255 - timer_cnt);
		glVertex3fv(tri_v2);
		glColor3ub(255 - timer_cnt, 0, timer_cnt);
		glVertex3fv(tri_v3);
	}
	glEnd();*/
	glPushMatrix();
	glTranslatef(0,0,1);
	glRotatef(timer_cnt,0,1,0);
	//printf("%d\n",timer_cnt);
	Render_Panda();
	glPopMatrix();

	glutSwapBuffers();
}

void My_Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	float viewportAspect = (float)width / (float)height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);

	GLfloat light_ambient[]  = { 0.5, 0.5, 0.5, 1.0};
	GLfloat light_diffuse[]  = { 0.3, 0.3, 0.3, 1.0};
	GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1.0};
	GLfloat light_position[] = { -8, 15, 15,0};  //光源的位置

	glEnable(GL_LIGHTING);                                 //開燈

	   // 設定發光體的光源的特性
	glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);      //環境光(Ambient Light)
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);      //散射光(Diffuse Light)
	glLightfv( GL_LIGHT0, GL_SPECULAR,light_specular);     //反射光(Specular Light)
   
	glLightfv( GL_LIGHT0, GL_POSITION,light_position);     //光的座標

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST); 


	//定義物體材質特性的數值
	GLfloat mat_ambient[]={0.2,0.2,0.2,1.0}; 
	GLfloat mat_diffuse[]={0.8,0.8,0.8,1.0}; 
	GLfloat mat_specular[]={ 1.0,1.0,1.0,1.0}; 
	GLfloat mat_shininess[]={80.0};


	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient); 
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse); 
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular); 
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);


	gluOrtho2D(-1 * viewportAspect, 1 * viewportAspect, -1, 1);
	//gluPerspective( 100, viewportAspect, 1.0, 500.0);   //透視投影
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void My_Timer(int val)
{
	timer_cnt++;
	timer_cnt%=360;
	glutPostRedisplay();
	if(timer_enabled)
	{
		glutTimerFunc(timer_speed, My_Timer, val);
	}
}

void My_Mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{
		printf("Mouse %d is pressed at (%d, %d)\n", button, x, y);
	}
	else if(state == GLUT_UP)
	{
		printf("Mouse %d is released at (%d, %d)\n", button, x, y);
	}
}

void My_Keyboard(unsigned char key, int x, int y)
{
	printf("Key %c is pressed at (%d, %d)\n", key, x, y);
}

void My_SpecialKeys(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_F1:
		printf("F1 is pressed at (%d, %d)\n", x, y);
		break;
	case GLUT_KEY_PAGE_UP:
		printf("Page up is pressed at (%d, %d)\n", x, y);
		break;
	case GLUT_KEY_LEFT:
		printf("Left arrow is pressed at (%d, %d)\n", x, y);
		break;
	default:
		printf("Other special key is pressed at (%d, %d)\n", x, y);
		break;
	}
}

void My_Menu(int id)
{
	switch(id)
	{
	case MENU_TIMER_START:
		if(!timer_enabled)
		{
			timer_enabled = true;
			glutTimerFunc(timer_speed, My_Timer, 0);
		}
		break;
	case MENU_TIMER_STOP:
		timer_enabled = false;
		break;
	case MENU_EXIT:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char *argv[])
{
	// Initialize GLUT and GLEW, then create a window.
	////////////////////
	glutInit(&argc, argv);
	glewInit();
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Robot Panda"); // You cannot use OpenGL functions before this line; The OpenGL context must be created first by glutCreateWindow()!
	dumpInfo();
	////////////////////
	
	// Initialize OpenGL states.
	////////////////////////
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	////////////////////////

	// Create a menu and bind it to mouse right button.
	////////////////////////////
	int menu_main = glutCreateMenu(My_Menu);
	int menu_timer = glutCreateMenu(My_Menu);

	glutSetMenu(menu_main);
	glutAddSubMenu("Timer", menu_timer);
	glutAddMenuEntry("Exit", MENU_EXIT);

	glutSetMenu(menu_timer);
	glutAddMenuEntry("Start", MENU_TIMER_START);
	glutAddMenuEntry("Stop", MENU_TIMER_STOP);

	glutSetMenu(menu_main);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	////////////////////////////

	// Register GLUT callback functions.
	///////////////////////////////
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape);
	glutMouseFunc(My_Mouse);
	glutKeyboardFunc(My_Keyboard);
	glutSpecialFunc(My_SpecialKeys);
	glutTimerFunc(timer_speed, My_Timer, 0); 
	///////////////////////////////

	// Enter main event loop.
	//////////////
	glutMainLoop();
	//////////////
	return 0;
}