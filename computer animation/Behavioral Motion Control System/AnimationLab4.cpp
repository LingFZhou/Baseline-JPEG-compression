#include "stdafx.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

//================================
// global variables
//================================
// screen size
int g_screenWidth  = 0;
int g_screenHeight = 0;

// t parameter
GLfloat t=0; 
// Number of balls
int BallNum=8;
// velocities of boids
GLfloat BoidVel[8][3]={0};
// positions of boids
GLfloat BoidPos[8][3]={0};
// matrix of each ball
GLfloat BallMatrix[8][16]={0};
// matrix of lead teapot
GLfloat TeapotMatrix[16]={0};
// Geometric data for the balls
GLfloat BM[16]={0};
// initial position of each ball
GLfloat Position[8][3]={{2.0f,5.5f,1.5f},{2.0f,8.5f,1.5f},{2.3f,7.0f,1.6f},{4.0f,5.0f,2.5f},{4.8f,7.0f,2.5f},{1.0f,7.0f,2.0f},{0.5f,3.2f,1.8f},{3.0f,4.6f,1.8f}};
// B Spline matrix
GLfloat BSplineMatrix[16]={-1.0f/6.0f,0.5f,-0.5f,1.0f/6.0f,0.5f,-1.0f,0,4.0f/6.0f,-0.5f,0.5f,0.5f,1.0f/6.0f,1.0f/6.0f,0,0,0};
// # of current point
int PointNumber = 0;
// point number
int PNumber = 5;
// The matrix to get Q=T，M，G
GLfloat Q[7] = {0};
// 4 parameters for Orientations and 3 for position given by quaternion
GLfloat Quaternion[5][7]={{1,0,0,0,-10,0,-25},{0,0,1,0,10,0,-25},{1,0,0,0,10,0,-5},{1,0,0,0,-10,0,-5},{1,0,0,0,-10,0,-15}};
// velocities after four apply four rules to affect behaviours
GLfloat R1Vel[3]={0};
GLfloat R2Vel[3]={0};
GLfloat R3Vel[3]={0};
GLfloat R4Vel[3]={0};


//================================
// comput Q=T，M，G
//================================
GLfloat ComputeQ(GLfloat T[4],GLfloat M[16],GLfloat G[4]) { 
	return	(T[0]*M[0]+T[1]*M[1]+T[2]*M[2]+T[3]*M[3])*G[0]+
			(T[0]*M[4]+T[1]*M[5]+T[2]*M[6]+T[3]*M[7])*G[1]+
			(T[0]*M[8]+T[1]*M[9]+T[2]*M[10]+T[3]*M[11])*G[2]+
			(T[0]*M[12]+T[1]*M[13]+T[2]*M[14]+T[3]*M[15])*G[3];
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

//================================
// Quaternion interpolation
//================================
// MatrixType is BSplineMatrix in this lab
void Interpolation (GLfloat MatrixType[16],GLfloat Object[5][7],GLfloat Q[7]){    
	GLfloat T[4]={t*t*t,t*t,t,1};
	for (int i=0; i<7 ; i++){
		GLfloat G[4] = {Object[PointNumber][i],Object[(PointNumber+1)%PNumber][i],Object[(PointNumber+2)%PNumber][i],Object[(PointNumber+3)%PNumber][i]};
		Q[i] = ComputeQ(T,MatrixType,G);
	}
	Normalize(Q);
	getMatrix(Q,TeapotMatrix);
	 
}

//================================
// Calculate distance between two balls
//================================
GLfloat CalDistance(GLfloat B1[3],GLfloat B2[3]){
	return sqrt((B1[0]-B2[0])*(B1[0]-B2[0])+(B1[1]-B2[1])*(B1[1]-B2[1])+(B1[2]-B2[2])*(B1[2]-B2[2]));
}

//================================
// Collision avoidance rule. Establish minimum required separation distance
//================================
void CARule(int N){
	for (int i=0; i<BallNum;i++){
		if (i!=N){
			if (CalDistance(BoidPos[N],BoidPos[i])<4.5f){
				for (int j=0;j<3;j++){
					R1Vel[j]=(R1Vel[j]-(BoidPos[i][j]-BoidPos[N][j]))/2000;
				}
			}
		}
	}
}

//================================
// Velocity matching rule. Boids try to match velocity with nearby boids
//================================
void VMRule(int N){
	GLfloat avg[3]={0};
	for (int i=0; i<BallNum; i++){
		avg[0]+=BoidVel[i][0];
		avg[1]+=BoidVel[i][1];
		avg[2]+=BoidVel[i][2];
	}
	// compute the average velocity of nearby boids
	avg[0]=(avg[0]-BoidVel[N][0])/(BallNum-1);
	avg[1]=(avg[1]-BoidVel[N][1])/(BallNum-1);
	avg[2]=(avg[1]-BoidVel[N][2])/(BallNum-1);
	// set the velocity toward the average velocity of nearby boids
	for (int i=0;i<3;i++){
		R2Vel[i]=(avg[i]-BoidVel[N][i])/2000;
	}
}

//================================
// Flock centering rule. Boids try to move towards the centre of mass of nearby boids
//================================
void FCRule(int N){
	GLfloat center[3]={0};
	for (int i=0; i<BallNum; i++){
		center[0]+=BallMatrix[i][12];
		center[1]+=BallMatrix[i][13];
		center[2]+=BallMatrix[i][14];
	}
	// compute the centre of mass of nearby boids
	center[0]=(center[0]-BallMatrix[N][12])/(BallNum-1);
	center[1]=(center[1]-BallMatrix[N][13])/(BallNum-1);
	center[2]=(center[1]-BallMatrix[N][14])/(BallNum-1);
	// set the velocity toward the center
	for (int i=0;i<3;i++){
		R3Vel[i]=(center[i]-BallMatrix[N][12+i])/5000;
	}
	
}

//================================
// Leader following rule. Boids try to follow the leading teapot
//================================
void LFRule(int N){
	for (int i=0; i<3;i++){
		R4Vel[i]=(TeapotMatrix[12+i]-BallMatrix[N][12+i])/3000;
	}
}

//================================
// Movement of the boids, apply the four rules to the boids.
//================================
void BoidsMovement(){
	GLfloat V1[3]={0};
	GLfloat V2[3]={0};
	GLfloat V3[3]={0};
	GLfloat V4[3]={0};
	for (int i=0;i<BallNum;i++){
		CARule(i);// apply collision avoidance rule
		for(int j=0;j<3;j++){
			V1[j]=R1Vel[j];
		}
		VMRule(i);// apply velocity matching rule
		for(int j=0;j<3;j++){
			V2[j]=R2Vel[j];
		}
		FCRule(i);// apply flock centering rule
		for(int j=0;j<3;j++){
			V3[j]=R3Vel[j];
		}
		LFRule(i);// apply leader following rule
		for(int j=0;j<3;j++){
			V4[j]=R4Vel[j];
		}
		// compute the finally velocity and position of the boids
		for(int j=0;j<3;j++){
			BoidVel[i][j]=BoidVel[i][j]+V1[j]+V2[j]+V3[j]+V4[j];
			BoidPos[i][j]=BoidPos[i][j]+BoidVel[i][j]*0.05;
			BallMatrix[i][12+j]=BoidPos[i][j];
		}
	}

}
//================================
// Display the ball N
//================================
void DisplayBall (int N){  
	glPushMatrix();
	for (int i=0;i<16;i++){
		BM[i]=BallMatrix[N][i];
	}
	glMultMatrixf(BM);
	glutSolidSphere(0.5,15,15);
	glPopMatrix();

}

//================================
// Display the leading teapot, same as in lab 1
//================================
void DisplayTeapot (){
	glPushMatrix();
	Interpolation(BSplineMatrix,Quaternion,Q);
	glMultMatrixf(TeapotMatrix);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidTeapot(1.0);
	glPopMatrix();
}

//================================
// Display the animation
//================================
void Display(){
	DisplayTeapot ();
	BoidsMovement();
	for (int i=0;i<BallNum;i++){
		DisplayBall (i);
	}	
}

//================================
// init
//================================
void init( void ) {
	for (int i=0;i<BallNum;i++){
		BallMatrix[i][0]=1.0f;
		BallMatrix[i][5]=1.0f;		
		BallMatrix[i][10]=1.0f;
		for (int j=0;j<3;j++){
			BallMatrix[i][12+j]=Position[i][j];
			BoidPos[i][j]=BallMatrix[i][12+j];
		}
		BallMatrix[i][15]=1.0f;
	}
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
	gluLookAt (0, 10.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// render objects
	Display();
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
	gluPerspective(90.0, (GLfloat)w/(GLfloat)h, 1.0, 2000.0);
}


//================================
// timer 
//================================
void timer( int value ) {	

	// render
	glutPostRedisplay();

	// map t parameter to time to achieve speed control
	t=t+0.002;
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
	// create opengL window
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH );
	glutInitWindowSize(1000, 800 ); 
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( "Lab4" );

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