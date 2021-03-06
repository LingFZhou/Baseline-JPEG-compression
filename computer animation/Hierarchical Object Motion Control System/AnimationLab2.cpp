#include "stdafx.h"
#include <iostream>
using namespace std;
// glut
#include <GL/glut.h>
// standard
#include <assert.h>
#include <math.h>
#define pi 3.14159265358979



//================================
// global variables
//================================
// screen size
int g_screenWidth  = 0;
int g_screenHeight = 0;
// animation speed
float speed;
//choose spline type
int splinetype;
static GLfloat M[16]={0};
static GLfloat M2[16]={0};
static GLfloat M1[16]={0};
// t parameter
GLfloat t = 0;
GLfloat CatmullRomMatrix[16]={-0.5f,1.0f,-0.5f,0,1.5f,-2.5f,0,1.0f,-1.5f,2.0f,0.5f,0,0.5f,-0.5f,0,0};
GLfloat BSplineMatrix[16]={-1.0f/6.0f,0.5f,-0.5f,1.0f/6.0f,0.5f,-1.0f,0,4.0f/6.0f,-0.5f,0.5f,0.5f,1.0f/6.0f,1.0f/6.0f,0,0,0};
// 3 parameters for Orientations and 3 for position given by euler angle
//GLfloat EulerAngle[5][6]={{0,0,0,-8,0,-20},{0,180,0,8,0,-20},{0,50,0,8,0,-5},{0,90,0,-8,0,-5},{0,80,0,-8,0,-15}};
// 4 parameters for Orientations and 3 for position given by quaternion
GLfloat Quaternion[5][7]={{1,0,0,0,-10,0,-25},{1,0,0,0,10,0,-25},{1,0,0,0,10,0,-5},{1,0,0,0,-10,0,-5},{1,0,0,0,-10,0,-15}};
GLfloat TransformMatrix[16] = {0};
GLfloat Q[7] = {0};
// # of current point 
int PointNumber = 0;
// point number
int PNumber = 6;

//================================
// comput Q=T��M��G
//================================
GLfloat ComputeQ(GLfloat T[4],GLfloat M[16],GLfloat G[4]) { 
	return	(T[0]*M[0]+T[1]*M[1]+T[2]*M[2]+T[3]*M[3])*G[0]+
			(T[0]*M[4]+T[1]*M[5]+T[2]*M[6]+T[3]*M[7])*G[1]+
			(T[0]*M[8]+T[1]*M[9]+T[2]*M[10]+T[3]*M[11])*G[2]+
			(T[0]*M[12]+T[1]*M[13]+T[2]*M[14]+T[3]*M[15])*G[3];
}

//================================
// make 4*4 matrix multiplication
//================================
void MultiMatrix(GLfloat Result[16],GLfloat M1[16],GLfloat M2[16]){ 
	GLfloat Matrix1[16];
	GLfloat Matrix2[16];
	for (int i=0;i<16;i++){
		Matrix1[i]=M1[i];
	}
	for (int i=0;i<16;i++){
		Matrix2[i]=M2[i];
	}
	Result[0]=Matrix1[0]*Matrix2[0]+Matrix1[4]*Matrix2[1]+Matrix1[8]*Matrix2[2]+Matrix1[12]*Matrix2[3];
	Result[1]=Matrix1[1]*Matrix2[0]+Matrix1[5]*Matrix2[1]+Matrix1[9]*Matrix2[2]+Matrix1[13]*Matrix2[3];
	Result[2]=Matrix1[2]*Matrix2[0]+Matrix1[6]*Matrix2[1]+Matrix1[10]*Matrix2[2]+Matrix1[14]*Matrix2[3];
	Result[3]=Matrix1[3]*Matrix2[0]+Matrix1[7]*Matrix2[1]+Matrix1[11]*Matrix2[2]+Matrix1[15]*Matrix2[3];
	Result[4]=Matrix1[0]*Matrix2[4]+Matrix1[4]*Matrix2[5]+Matrix1[8]*Matrix2[6]+Matrix1[12]*Matrix2[7];
	Result[5]=Matrix1[1]*Matrix2[4]+Matrix1[5]*Matrix2[5]+Matrix1[9]*Matrix2[6]+Matrix1[13]*Matrix2[7];
	Result[6]=Matrix1[2]*Matrix2[4]+Matrix1[6]*Matrix2[5]+Matrix1[10]*Matrix2[6]+Matrix1[14]*Matrix2[7];
	Result[7]=Matrix1[3]*Matrix2[4]+Matrix1[7]*Matrix2[5]+Matrix1[11]*Matrix2[6]+Matrix1[15]*Matrix2[7];
	Result[8]=Matrix1[0]*Matrix2[8]+Matrix1[4]*Matrix2[9]+Matrix1[8]*Matrix2[10]+Matrix1[12]*Matrix2[11];
	Result[9]=Matrix1[1]*Matrix2[8]+Matrix1[5]*Matrix2[9]+Matrix1[9]*Matrix2[10]+Matrix1[13]*Matrix2[11];
	Result[10]=Matrix1[2]*Matrix2[8]+Matrix1[6]*Matrix2[9]+Matrix1[10]*Matrix2[10]+Matrix1[14]*Matrix2[11];
	Result[11]=Matrix1[3]*Matrix2[8]+Matrix1[7]*Matrix2[9]+Matrix1[11]*Matrix2[10]+Matrix1[15]*Matrix2[11];
	Result[12]=Matrix1[0]*Matrix2[12]+Matrix1[4]*Matrix2[13]+Matrix1[8]*Matrix2[14]+Matrix1[12]*Matrix2[15];
	Result[13]=Matrix1[1]*Matrix2[12]+Matrix1[5]*Matrix2[13]+Matrix1[9]*Matrix2[14]+Matrix1[13]*Matrix2[15];
	Result[14]=Matrix1[2]*Matrix2[12]+Matrix1[6]*Matrix2[13]+Matrix1[10]*Matrix2[14]+Matrix1[14]*Matrix2[15];
	Result[15]=Matrix1[3]*Matrix2[12]+Matrix1[7]*Matrix2[13]+Matrix1[11]*Matrix2[14]+Matrix1[15]*Matrix2[15];
}

//================================
// Quaternion interpolation
//================================
// MatrixType can be CatmullRomMatrix or BSplineMatrix
void Interpolation (GLfloat MatrixType[16],GLfloat Object[5][7],GLfloat Q[7]){    
	GLfloat T[4]={t*t*t,t*t,t,1};
	for (int i=0; i<7 ; i++){
		GLfloat G[4] = {Object[PointNumber][i],Object[(PointNumber+1)%PNumber][i],Object[(PointNumber+2)%PNumber][i],Object[(PointNumber+3)%PNumber][i]};
		Q[i] = ComputeQ(T,MatrixType,G);
	}
	 
}

//================================
// nomalise the quanternion q, divide by |q|
//================================
void Normalize(GLfloat ParameterArray[7]){ 
	GLfloat w=ParameterArray[0];
	GLfloat x=ParameterArray[1];
	GLfloat y=ParameterArray[2];
	GLfloat z=ParameterArray[3];
	GLfloat q = w*w + x*x + y*y + z*z;
	if (q!=0 && (fabs(q-1.0f)>0.01f)){
		GLfloat m = sqrt(q);
		ParameterArray[0] /= m;
		ParameterArray[1] /= m;
		ParameterArray[2] /= m;
		ParameterArray[3] /= m;
	}
}  

//================================
// Quaternion corresponding transform matrix, rotation of w around vector (x,y,z)
//================================
void getMatrix (GLfloat ParameterArray[7],GLfloat Matrix[16]){
	GLfloat w=ParameterArray[0];
	GLfloat x=ParameterArray[1];
	GLfloat y=ParameterArray[2];
	GLfloat z=ParameterArray[3];
	Matrix[0]=1.0f-2.0f*(y*y+z*z);
	Matrix[1]=2.0f*(x*y+w*z);
	Matrix[2]=2.0f*(x*z-w*y);
	Matrix[3]=0.0f;
	Matrix[4]=2.0f*(x*y-w*z);
	Matrix[5]=1.0f-2.0f*(x*x+z*z);
	Matrix[6]=2.0f*(y*z+w*x);
	Matrix[7]=0.0f;
	Matrix[8]=2.0f*(x*z+w*y);
	Matrix[9]=2.0f*(y*z-w*x);
	Matrix[10]=1-2.0f*(x*x+y*y);
	Matrix[11]=0.0f;
	Matrix[12]=ParameterArray[4];
	Matrix[13]=ParameterArray[5];
	Matrix[14]=ParameterArray[6];
	Matrix[15]=1.0f;
}


/*
//================================
// transform euler angle to quaternion 
//================================
void EulerToQuaternion (GLfloat ParameterArray[7]){    
	GLfloat a=(ParameterArray[0]/180)*pi;
	GLfloat b=(ParameterArray[1]/180)*pi;
	GLfloat c=(ParameterArray[2]/180)*pi;
	GLfloat cosa=cos(a/2.0f);
	GLfloat sina=sin(a/2.0f);
	GLfloat cosb=cos(b/2.0f);
	GLfloat sinb=sin(b/2.0f);
	GLfloat cosc=cos(c/2.0f);
	GLfloat sinc=sin(c/2.0f);
	ParameterArray[6]=ParameterArray[5];
	ParameterArray[5]=ParameterArray[4];
	ParameterArray[4]=ParameterArray[3];
	ParameterArray[0]=cosa*cosb*cosc+sina*sinb*sinc;
	ParameterArray[1]=sina*cosb*cosc-cosa*sinb*sinc;
	ParameterArray[2]=cosa*sinb*cosc+sina*cosb*sinc;
	ParameterArray[3]=cosa*sinb*sinc+sina*sinb*cosc;
}

//================================
// EulerAngle interpolation
//================================
// MatrixType can be CatmullRomMatrix or BSplineMatrix
void Interpolation (GLfloat MatrixType[16],GLfloat Object[5][6],GLfloat Q[7]){    
	GLfloat T[4]={t*t*t,t*t,t,1};
	for(int i=0; i<6 ; i++){
		GLfloat G[4] = {Object[PointNumber][i],Object[(PointNumber+1)%PNumber][i],Object[(PointNumber+2)%PNumber][i],Object[(PointNumber+3)%PNumber][i]};
		Q[i] = ComputeQ(T,MatrixType,G);
	}
	EulerToQuaternion(Q); 
}
*/


//================================
// Using forward kinematic to transform two legs and two arms and head coordinate to torso coordinate
//================================
void LeftLeg(){    //transform left leg
	GLfloat MT[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-3.0f,0,1}; //translate matrix
	GLfloat angle = (sin(4*pi*t-pi/2)*pi)/12; //the angle of the swing
	GLfloat MR[16]={cos(angle),sin(angle),0,0,-sin(angle),cos(angle),0,0,0,0,1,0,0,0,0,1}; //Rotation matrix, by z axis
	GLfloat MT1[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0.3f,1}; // translate matrix
	MultiMatrix(M1,M,MR);
	MultiMatrix(M1,M1,MT);
	MultiMatrix(M1,M1,MT1);
}

void RightLeg(){	//transform right leg
	GLfloat MT[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-3.0f,0,1}; //translate matrix
	GLfloat angle = (sin(4*pi*t-pi/2)*pi)/12; //the angle of the swing
	GLfloat MR[16]={cos(-angle),sin(-angle),0,0,-sin(-angle),cos(-angle),0,0,0,0,1,0,0,0,0,1}; //Rotation matrix, by z axis
	GLfloat MT1[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,-0.3f,1}; // translate matrix
	MultiMatrix(M2,M,MR);
	MultiMatrix(M2,M2,MT);
	MultiMatrix(M2,M2,MT1);
}

void LeftArm(){    	//transform left arm
	GLfloat MT[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-0.4f,0,1}; //translate matrix
	GLfloat angle = (sin(4*pi*t-pi/2)*pi)/8; //the angle of the swing
	GLfloat MR[16]={cos(-angle),sin(-angle),0,0,-sin(-angle),cos(-angle),0,0,0,0,1,0,0,0,0,1}; //Rotation matrix, by z axis
	GLfloat MT1[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,1.2f,1}; // translate matrix
	MultiMatrix(M1,M,MR);
	MultiMatrix(M1,M1,MT);
	MultiMatrix(M1,M1,MT1);
}

void RightArm(){	//transform right arm
	GLfloat MT[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,-0.4f,0,1}; //translate matrix
	GLfloat angle = (sin(4*pi*(t)-pi/2)*pi)/8; //the angle of the swing
	GLfloat MR[16]={cos(angle),sin(angle),0,0,-sin(angle),cos(angle),0,0,0,0,1,0,0,0,0,1}; //Rotation matrix, by z axis
	GLfloat MT1[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,-1.2f,1}; //translate matrix
	MultiMatrix(M2,M,MR);
	MultiMatrix(M2,M2,MT);
	MultiMatrix(M2,M2,MT1);
}

void Head(){    	//transform head
	GLfloat MT[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,2.0f,0,1}; //translate matrix
	//GLfloat s = (sin(4*pi*(t)-pi/2)*pi)/8; //the angle of the swing
	//GLfloat MR[16]={cos(s),sin(s),0,0,-sin(s),cos(s),0,0,0,0,1,0,0,0,0,1}; //Rotation matrix, by z axis
	//GLfloat MT1[16]={1,0,0,0,0,1,0,0,0,0,1,0,5.0f,0,0,1}; // translate matrix
	//MultiMatrix(M,MR,M1);
	//MultiMatrix(M,MT,M1);
	MultiMatrix(M1,M,MT);
}

//================================
// Display torso,legs,arms and head
//================================
void DisplayTorso(){ //Display the Torso
	//if(splinetype == 1) Interpolation(CatmullRomMatrix,Quaternion,Q);
	//if(splinetype == 2) Interpolation(BSplineMatrix,Quaternion,Q);
	Interpolation(BSplineMatrix,Quaternion,Q);
	Normalize(Q);
	getMatrix(Q,M);
	glLoadMatrixf(M);
	glScalef(1.5,3,1.5);
	glutSolidCube(1.0);
}

void DisplayLeftLeg(){ //Display the left leg
	LeftLeg();
	glLoadMatrixf(M1);
	glScalef(0.5f,3.0f,0.5f);
	glutSolidCube(1.0);
}   

void DisplayRightLeg(){ //Display the right leg
	RightLeg();
	glLoadMatrixf(M2);
	glScalef(0.5f,3.0f,0.5f);
	glutSolidCube(1.0);
}

void DisplayLeftArm(){ //Display the left arm
	LeftArm();
	glLoadMatrixf(M1);
	glScalef(0.5f,3.0f,0.5f);
	glutSolidCube(1.0);
}   

void DisplayRightArm(){ //Display the right arm
	RightArm();
	glLoadMatrixf(M2);
	glScalef(0.5f,3.0f,0.5f);
	glutSolidCube(1.0);
}

void DisplayHead(){ //Display the head
	Head();
	glLoadMatrixf(M1);
	glScalef(0.7,0.7,0.7);
	glutSolidSphere(1.0,1000,1000);
}

//================================
// init
//================================
void init( void ) {
	// init something before main loop...
}

//================================
// render
//================================
void render( void ) {
	// clear buffer
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClearDepth (1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	// render state
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// light source attributes
	GLfloat LightAmbient[]	= { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat LightDiffuse[]	= { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat LightSpecular[]	= { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat LightPosition[] = { 5.0f, 5.0f, 5.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT , LightAmbient );
	glLightfv(GL_LIGHT0, GL_DIFFUSE , LightDiffuse );
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	// surface material attributes
	GLfloat material_Ka[]	= { 0.11f, 0.06f, 0.11f, 1.0f };
	GLfloat material_Kd[]	= { 0.43f, 0.47f, 0.54f, 1.0f };
	GLfloat material_Ks[]	= { 0.33f, 0.33f, 0.52f, 1.0f };
	GLfloat material_Ke[]	= { 0.1f , 0.0f , 0.1f , 1.0f };
	GLfloat material_Se		= 10;

	glMaterialfv(GL_FRONT, GL_AMBIENT	, material_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE	, material_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR	, material_Ks);
	glMaterialfv(GL_FRONT, GL_EMISSION	, material_Ke);
	glMaterialf (GL_FRONT, GL_SHININESS	, material_Se);

	// modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();


	// render objects
	DisplayTorso();
	DisplayHead();
	DisplayLeftLeg();
	DisplayRightLeg();
	DisplayLeftArm();
	DisplayRightArm();

	

	// disable lighting
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	// swap back and front buffers
	glutSwapBuffers();
}

//================================
// keyboard input
//================================
void keyboard( unsigned char key, int x, int y ) {
}

//================================
// reshape : update viewport and projection matrix when the window is resized
//================================
void reshape( int w, int h ) {
	// screen size
	g_screenWidth  = w;
	g_screenHeight = h;	
	
	// viewport
	glViewport( 0, 0, (GLsizei)w, (GLsizei)h );

	// projection matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(90.0, (GLfloat)w/(GLfloat)h, 1.0, 3000.0);
}


//================================
// timer 
//================================
void timer( int value ) {	

	// render
	glutPostRedisplay();

	// map t parameter to time to achieve speed control
	t=t+speed;
	if(t>=1){
		t=0;
		if(PointNumber<PNumber-1){
			PointNumber++;
		}
		else{
			PointNumber=0;
		}
	}
	// 16 ms per frame ( about 60 frames per second )
	glutTimerFunc( 16, timer, 0 );
}

//================================
// main
//================================
int main( int argc, char** argv ) {
	cout<< "Please enter spline type, 1 for CatmullRom, 2 for B Spline" << endl;
	cin >> splinetype;
	cout << "Please enter speed (0-0.02 preferred)"<<endl;
	cin >> speed;
	// create opengL window
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH );
	glutInitWindowSize(1000, 800 ); 
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( "Lab2" );

	// init
	init();
	
	// set callback functions
	glutDisplayFunc( render );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutTimerFunc( 16, timer, 0 );
	
	// main loop
	glutMainLoop();

	return 0;
}