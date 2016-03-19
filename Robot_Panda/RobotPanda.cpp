#include <glew.h> // glew.h must be included before gl.h/glu.h/freeglut.h
#include <freeglut.h>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <wingdi.h>
#include <math.h>

#define MENU_TIMER_START 1
#define MENU_TIMER_STOP 2
#define MENU_EXIT 3
#define MENU_ANIMATION_FLY 4
#define MENU_ANIMATION_DANCE 5
#define MENU_CENTER 6
#define GL_PI 3.141592654 

const GLfloat tri_v1[3] = {-0.5f, -0.4f, 0.0f};
const GLfloat tri_v2[3] = { 0.5f, -0.4f, 0.0f};
const GLfloat tri_v3[3] = { 0.0f,  0.6f, 0.0f};

GLUquadricObj *quadratic;
int timer_cnt = 0;
double fly_cnt=0;
double dance_cnt=0;
double move_cnt=0;
bool timer_enabled = true;
bool fly_animation = false;
bool fly_enabled = false;
unsigned int timer_speed = 16;
int left_right_rotate=0;
int up_down_rotate=0;
bool left_hand_upper_ani=0;
bool right_hand_upper_ani=0;
bool stop_up=0;
bool stop_down=0;
bool button_pressed=0;
bool delay=0;
bool dance_animation = false;
bool dance_enabled = false;
double left_right_position=0;
double up_down_position=0;
// Print OpenGL context related information.
void dumpInfo(void)
{
    printf("Vendor: %s\n", glGetString (GL_VENDOR));
    printf("Renderer: %s\n", glGetString (GL_RENDERER));
    printf("Version: %s\n", glGetString (GL_VERSION));
    printf("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
}
void Init_All()
{
	//left_right_rotate=0;
	//up_down_rotate=0;
	left_hand_upper_ani=0;
	right_hand_upper_ani=0;
	stop_up=0;
	stop_down=0;
	button_pressed=0;
	timer_cnt = 0;
	fly_cnt=0;
	timer_enabled = true;
	fly_animation = false;
	fly_enabled = false;
	delay=0;
	dance_animation = false;
	dance_enabled = false;
	dance_cnt=0;
	move_cnt=0;
}
int Press_The_Button_Lower(bool flag,int deg,int dir)
{
	if(!flag) return 0;
	else if(stop_down) {
		glRotatef(dir*deg,0,1,0);
		return 1;
	}
	else{
		if(timer_cnt<deg){		
			glRotatef(dir*timer_cnt,0,1,0);
			return 0;
		}
		else{
			stop_down=1;
			timer_cnt=0;
			glRotatef(dir*deg,0,1,0);
			return 1;
		}
	}
}
int Press_The_Button_Upper(bool flag,int deg,int dir)
{
	if(!flag) return 0;
	else if(stop_up) {
		glRotatef(deg*dir,1,0,0);
		return 1;
	}
	else{
		if(timer_cnt<abs(deg)){
			glRotatef(timer_cnt*dir,1,0,0);
			return 0;
		}
		else{
			stop_up=1;
			glRotatef(deg*dir,1,0,0);
			timer_cnt=0;
			return 1;
		}
	}
}
void Raise_My_Hand(bool flag,int deg)
{
	if(!flag) return ;
	else if(stop_down) {
		glRotatef(deg,0,-1,0);
	}
	else{
		if(timer_cnt<abs(deg)){		
			glRotatef(timer_cnt,0,-1,0);
		}
		else{
			stop_down=1;
			timer_cnt=0;
			glRotatef(deg,0,-1,0);
		}
	}
}
void Panda_Button()
{
	glColor3f(0.9,0.9,0.9);
	GLUquadric* button;
	button=gluNewQuadric();
	if(button_pressed) glTranslatef(0,0,-0.01);
	gluCylinder(button, 0.1, 0.1, 0.05, 30, 30);
	glTranslatef(0,0,0.05);
	gluDisk(button,0,0.1,30,30);
	glBegin(GL_QUADS);
      glNormal3f(0,0,1);
         glTexCoord2f(0,1);glVertex3f(-0.07, 0.07,0.001);
         glTexCoord2f(0,0);glVertex3f(-0.07,-0.07,0.001);
         glTexCoord2f(1,0);glVertex3f( 0.07,-0.07,0.001);
         glTexCoord2f(1,1);glVertex3f( 0.07, 0.07,0.001);
	glEnd();
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


}
void Panda_Head()
{

	glColor3ub(255,255,255);
	glScalef(1.1,1,1);
	glTranslatef(0,0.3,0);
	glutSolidSphere(0.25,50,50);

	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(-0.18,0.17,0);
		glutSolidTorus(0.07,0.05,50,50);
		glTranslatef(0.36,0,0);
		glutSolidTorus(0.07,0.05,50,50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.12,0.03,0.2);
		glRotatef(30,-1,4,1);
		glScalef(1.5,2,0.7);
		glutSolidSphere(0.05,50,50);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-0.05,0.23);
		glutSolidSphere(0.02,50,50);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.12,0.03,0.2);
		glRotatef(30,-1,-4,-1);
		glScalef(1.5,2,0.7);
		glutSolidSphere(0.05,50,50);
	glPopMatrix();
	glPushMatrix();
		GLUquadric* mouth;
		mouth=gluNewQuadric();
		glTranslatef(-0.05,-0.07,0.08);
		glRotatef(90,0,1,0);
		gluCylinder(mouth, 0.15, 0.15, 0.1, 30, 30);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1,1,1);
		//GLUquadric* mouth;
		mouth=gluNewQuadric();
		glTranslatef(-0.042,-0.08,0.077);
		glRotatef(90,0,1,0);
		gluCylinder(mouth, 0.15, 0.15, 0.08, 30, 30);
	glPopMatrix();
	
	
}
void Panda_Upper_Hand(bool flag,int dir)
{
	
	glColor3ub(0,0,0);
	glutSolidSphere(0.09,50,50);
	bool f=Press_The_Button_Upper(flag,79,dir);	
	GLUquadric* upperArm;
	upperArm=gluNewQuadric();
	glTranslatef(-0.02,-0.05,0);
	
	glRotatef(90,1,-0.3,0);
			//glRotatef(270,0,0,1);
	//Press_The_Button_Upper(f,45,1);
	Press_The_Button_Lower(f,45,1);
	//if(fly_enabled) Raise_My_Hand(flag,45);
	gluCylinder(upperArm, 0.05, 0.05, 0.1, 30, 30);
	button_pressed=Press_The_Button_Lower(f,10,abs(dir));
	//if(fly_enabled) Raise_My_Hand(flag,45);

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
void Panda_Wing_Right()
{
	glColor3ub(255,0,85);
	GLUquadric* sole;
	sole=gluNewQuadric();
	glRotatef(90,0,1,0);
	glTranslatef(0.1,0.2,-0.6);
	glScalef(0.4,1,1);
	glRotatef(20,1,0,0);
	gluCylinder(sole, 0.15, 0.08, 0.5, 30, 30);
	glTranslatef(0,0,-0.3);
	gluCylinder(sole, 0, 0.15, 0.3, 30, 30);
}
void Panda_Wing_Left()
{
	glColor3ub(255,0,85);
	GLUquadric* sole;
	sole=gluNewQuadric();
	glRotatef(90,0,-1,0);
	glTranslatef(-0.1,0.2,-0.6);
	glScalef(0.4,1,1);
	glRotatef(20,1,0,0);
	gluCylinder(sole, 0.15, 0.08, 0.5, 30, 30);
	glTranslatef(0,0,-0.3);
	//glScalef(0.9,1,1);
	//glRotatef(45,-1,0,0);
	gluCylinder(sole, 0, 0.15, 0.3, 30, 30);
}
void Panda_Rocket()
{
	glColor3f(0,0,0);
	GLUquadric* rocket;
	rocket=gluNewQuadric();
	glPushMatrix();
		glTranslatef(0,0,-0.5);
		glRotatef(-90,1,0,0);
		gluCylinder(rocket, 0.1, 0.09, 0.05, 30, 30);
		glColor3f(1,1,1);
		glTranslatef(0,0,0.05);
		gluCylinder(rocket, 0.09, 0.08, 0.05, 30, 30);
		glColor3f(0,0,0);
		glTranslatef(0,0,0.05);
		gluCylinder(rocket, 0.08, 0.07, 0.05, 30, 30);
		glTranslatef(0,0,0.05);
		gluCylinder(rocket, 0.07, 0.045, 0.08, 30, 30);
		glTranslatef(0,0,0.08);
		gluCylinder(rocket, 0.045, 0.0, 0.1, 30, 30);
		//BEAM
		if(fly_enabled){
			glColor3ub(255,255,0);
			glTranslatef(0,0,-0.4);
			gluCylinder(rocket, fly_cnt, fly_cnt, 0.3, 30, 30);
		}
	glPopMatrix();
}
void Render_Panda()
{
	//TORSO
	glPushMatrix();
		glTranslatef(0,-0.05,0);
		Panda_Torso();
	glPopMatrix();
	//BUTTON
	glPushMatrix();
		glTranslatef(0,-0.05,0.14);
		//glRotatef(5,1,0,0);
		Panda_Button();
	glPopMatrix();
	//HEAD&EARS
	glPushMatrix();
		glTranslatef(0,0.05,0);
		if(dance_enabled) glRotatef(dance_cnt/2,0,0,-1);
		Panda_Head();
	glPopMatrix();
	//LEFT HAND
	glPushMatrix();
		glTranslatef(-0.22,0.085,0);
		
		Panda_Upper_Hand(left_hand_upper_ani,-1);
		glTranslatef(-0.0065,0,0.085);
		if(dance_enabled) glRotatef(dance_cnt,1,0,0);
		glPushMatrix();
			Panda_Lower_Hand();
		glPopMatrix();
	glPopMatrix();
	//RIGHT HAND
	glPushMatrix();
		glTranslatef(0.22,0.085,0);
		glRotatef(180,0,1,0);
		Panda_Upper_Hand(right_hand_upper_ani,1);
		glTranslatef(-0.0065,0,0.085);
		glPushMatrix();
			Panda_Lower_Hand();
		glPopMatrix();
		
	glPopMatrix();
	//LEFT LEG
	glPushMatrix();
		glTranslatef(-0.1,-0.18,0);
		Panda_Upper_Leg();
		glTranslatef(-0.007,0,0.15);
		if(dance_enabled) glRotatef(dance_cnt,0,0,-1);
		glPushMatrix();
			Panda_Lower_Leg();
			glPushMatrix();
				glTranslatef(-0.02,-0.1,0.22);			
				Panda_Left_Sole();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//RIGHT LEG
	glPushMatrix();
		glRotatef(180,0,1,0);
		glTranslatef(-0.1,-0.18,0);
		Panda_Upper_Leg();
		glTranslatef(-0.007,-0.01,0.15);
		if(dance_enabled) glRotatef(dance_cnt,0,0,1);
		glPushMatrix();
			Panda_Lower_Leg();
			glPushMatrix();
				glTranslatef(-0.02,-0.09,0.22);
				Panda_Right_Sole();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	//LEFT WING
	glPushMatrix();
		glTranslatef(-0.05,0,-0.05);
		Panda_Wing_Left();
	glPopMatrix();
	//RIGHT WING
	glPushMatrix();
		glTranslatef(0.05,0,-0.05);
		Panda_Wing_Right();
	glPopMatrix();
	//ROCKET
	glPushMatrix();
		glScalef(1,1.2,1);
		glTranslatef(-0.08,-0.14,0.3);
		Panda_Rocket();
		glTranslatef(0.16,0,0);
		Panda_Rocket();
	glPopMatrix();

}
// GLUT callback. Called to draw the scene.
void My_Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glTranslatef(0,0,1);
		glTranslatef(left_right_position,up_down_position,0);
		glRotatef(left_right_rotate,0,1,0);
		glRotatef(up_down_rotate,1,0,0);
		if(fly_enabled) glTranslatef(0,fly_cnt,0);
		if(fly_animation){
			left_hand_upper_ani=0;
			right_hand_upper_ani=1;
		}
		else if(dance_animation){
			left_hand_upper_ani=0;
			right_hand_upper_ani=1;
		}
		if(fly_animation&&button_pressed&&!delay){		
			timer_cnt=0;
			fly_cnt=0;
			delay=1;
		}
		else if(timer_cnt==20&&delay){
			fly_animation=0;
			timer_cnt=0;
			fly_cnt=0;
			fly_enabled=1;
			delay=0;
		}
		if(dance_animation&&button_pressed){
			dance_enabled=true;
			dance_animation=0;
			dance_cnt=0;
			timer_cnt=0;
			move_cnt=0;
		}
		if(dance_enabled){
			glTranslatef(move_cnt/100,0,0);
		}
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

	//Lighting and Matrials

	glEnable(GL_NORMALIZE);
	glEnable(GL_RESCALE_NORMAL);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);

	GLfloat light_ambient[]  = { 0.6, 0.6, 0.6, 1.0};
	GLfloat light_diffuse[]  = { 0.3, 0.3, 0.3, 1.0};
	GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1.0};
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
unsigned char *LoadBitmapFile(char *fileName, BITMAPINFO *bitmapInfo)
{
   FILE            *fp;
   BITMAPFILEHEADER   bitmapFileHeader;   // Bitmap file header
   unsigned char       *bitmapImage;      // Bitmap image data
   unsigned int      lInfoSize;         // Size of information
   unsigned int      lBitSize;         // Size of bitmap
   
   unsigned char change;
    int pixel;
    int p=0;
       
   fp = fopen(fileName, "rb");
   fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);         //讀取 bitmap header
   
   lInfoSize = bitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);   //Info的size
   fread(bitmapInfo, lInfoSize, 1, fp);
   
   
   lBitSize = bitmapInfo->bmiHeader.biSizeImage;                  //配置記憶體
   bitmapImage = new BYTE[lBitSize];
   fread(bitmapImage, 1, lBitSize, fp);                        //讀取影像檔
   
   fclose(fp);
   
   //此時傳回bitmapImage的話，顏色會是BGR順序，下面迴圈會改順序為RGB
   pixel = (bitmapInfo->bmiHeader.biWidth)*(bitmapInfo->bmiHeader.biHeight);

   for( int i=0 ; i<pixel ; i++, p+=3 )
   {
      //交換bitmapImage[p]和bitmapImage[p+2]的值
      change = bitmapImage[p];
      bitmapImage[p] = bitmapImage[p+2];
      bitmapImage[p+2]  = change;
   }
   
   return bitmapImage;
}
void texture(void)
{
   int width;
   int height;
   unsigned char *image;         //得到圖案，是能直接讓OpenGL使用的資料了
   BITMAPINFO bmpinfo;            //用來存放HEADER資訊
   
   image = LoadBitmapFile("flower.bmp", &bmpinfo);
   width = bmpinfo.bmiHeader.biWidth;
   height = bmpinfo.bmiHeader.biHeight;
   
   glTexImage2D(GL_TEXTURE_2D,0,3,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
   glEnable(GL_TEXTURE_2D);;
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glBindTexture(GL_TEXTURE_2D, image)
   
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
void My_Timer(int val)
{
	if(fly_animation||fly_enabled||dance_animation||dance_enabled) {
		timer_cnt++;
	}
	//timer_cnt%=360;
	
	if(timer_cnt%60<30) fly_cnt+=0.002;
	else fly_cnt-=0.002;

	if(timer_cnt%60<15||timer_cnt%60>44) dance_cnt+=0.5;
	else dance_cnt-=0.5;

	if(timer_cnt%600<150||timer_cnt%600>449) move_cnt+=0.5;
	else move_cnt-=0.5;
	//if(timer_cnt==62) timer_cnt=0;
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
	switch(key)
	{
	case 'a'://A
		left_right_position-=0.05;
		printf("A is pressed at (%d, %d)\n", x, y);
		break;
	case 'd'://D
		left_right_position+=0.05;
		printf("D is pressed at (%d, %d)\n", x, y);
		break;
	case 'w'://W
		up_down_position+=0.05;
		printf("W is pressed at (%d, %d)\n", x, y);
		break;
	case 's'://S
		up_down_position-=0.05;
		printf("S is pressed at (%d, %d)\n", x, y);
		break;
	}
}
void My_SpecialKeys(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_F1:
		printf("F1 is pressed at (%d, %d)\n", x, y);
		break;
	case GLUT_KEY_PAGE_UP:
		//if(timer_speed>5) timer_speed-=5;
		printf("Page up is pressed at (%d, %d)\n", x, y);
		//printf("Now timer speed: %d\n",timer_speed);
		break;
	case GLUT_KEY_PAGE_DOWN:
	//	timer_speed+=5;
		printf("Page Down is pressed at (%d, %d)\n", x, y);
	//	printf("Now timer speed: %d\n",timer_speed);
		break;
	case GLUT_KEY_LEFT:
		left_right_rotate-=5;
		printf("Left arrow is pressed at (%d, %d)\n", x, y);
		break;
	case GLUT_KEY_RIGHT:
		left_right_rotate+=5;
		printf("Right arrow is pressed at (%d, %d)\n", x, y);
		break;
	case GLUT_KEY_UP:
		up_down_rotate-=5;
		printf("Up arrow is pressed at (%d, %d)\n", x, y);
		break;
	case GLUT_KEY_DOWN:
		up_down_rotate+=5;
		printf("Down arrow is pressed at (%d, %d)\n", x, y);
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
		fly_enabled=false;
		if(!timer_enabled)
		{
			timer_enabled = true;
			glutTimerFunc(timer_speed, My_Timer, 0);
		}
		break;
	case MENU_TIMER_STOP:
		Init_All();
		break;
	case MENU_EXIT:
		exit(0);
		break;
	case MENU_ANIMATION_FLY:
		Init_All();
		fly_animation=true;
		//fly_enabled=true;
		if(!timer_enabled)
		{
			timer_enabled = true;
			glutTimerFunc(timer_speed, My_Timer, 0);
		}
		break;
	case MENU_ANIMATION_DANCE:
		Init_All();
		dance_animation=true;
		if(!timer_enabled)
		{
			timer_enabled = true;
			glutTimerFunc(timer_speed, My_Timer, 0);
		}
		break;
	case MENU_CENTER:
		left_right_position=0;
		up_down_position=0;
		left_right_rotate=0;
		up_down_rotate=0;
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
	int menu_animation = glutCreateMenu(My_Menu);

	glutSetMenu(menu_main);
	//glutAddSubMenu("Timer", menu_timer);
	glutAddMenuEntry("Center", MENU_CENTER);
	glutAddSubMenu("Animation", menu_animation);
	glutAddMenuEntry("Exit", MENU_EXIT);

	/*glutSetMenu(menu_timer);
	glutAddMenuEntry("Start", MENU_TIMER_START);
	glutAddMenuEntry("Stop", MENU_TIMER_STOP);*/

	glutSetMenu(menu_animation);
	glutAddMenuEntry("Fly", MENU_ANIMATION_FLY);
	glutAddMenuEntry("Dacne", MENU_ANIMATION_DANCE);
	glutAddMenuEntry("Stop", MENU_TIMER_STOP);

	glutSetMenu(menu_main);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	texture();
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