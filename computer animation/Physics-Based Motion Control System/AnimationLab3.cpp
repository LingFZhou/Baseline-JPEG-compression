#include "stdafx.h"

// standard
#include <assert.h>
#include <math.h>

// glut
#include <GL/glut.h>

//================================
// global variables
//================================
// screen size
int g_screenWidth  = 0;
int g_screenHeight = 0;
// Number of balls
int BallNum = 8;
// old velocity of the balls
GLfloat OldVel[8][3] = {{0.1f,0,0},{-0.2f,0,0},{-0.1f,0,0.1f},{0.1f,0,0},{0,0,0},{0,0,-0.2f},{-0.1f,0,0},{-0.1f,0,0.1f}};
// new velocity of the balls
GLfloat NewVel[8][3];
// old position of the balls
GLfloat OldPos[8][3];
// new position of the balls
GLfloat NewPos[8][3];
// matrix of each ball
GLfloat BallMatrix[8][16];
// Geometric data for the balls
GLfloat BM[16] = {0};
// gravity
GLfloat gravity[3] = {0,-2.0f,0};
// dt
GLfloat dt = 0.02f;
// coefficient of restitution
GLfloat res = 0.4f;
// initial position of each ball
GLfloat Position[10][3]={{2.0f,5.5f,1.5f},{2.0f,8.5f,1.5f},{2.3f,7.0f,1.6f},{4.0f,5.0f,2.5f},{4.8f,7.0f,2.5f},{1.0f,7.0f,2.0f},{0.5f,3.2f,1.8f},{3.0f,4.6f,1.8f}};
// mass of balls
GLfloat Mass[10] = {1.2f,1.3f,1.0f,1.0f,0.8f,1.2f,1.4f,1.2f,1.0f,1.0f};

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
			OldPos[i][j]=BallMatrix[i][12+j];
		}
		BallMatrix[i][15]=1.0f;
	}
}

//================================
// Display the floor
//================================
void DisplayFloor(){
	glBegin(GL_LINES);
	for (GLfloat x = -150; x < 150;x+=0.1f)
	        {glVertex3f(x, 0, -100); glVertex3f(x, 0,  100);}         
	for (GLfloat z = -150; z < 100;z+=0.1f)
	        {glVertex3f(-150, 0, z); glVertex3f( 100, 0, z);}          
    glEnd();
}

//================================
// Calculate distance between two balls for collision detect
//================================
GLfloat CalDistance(GLfloat B1[3],GLfloat B2[3]){
	return sqrt((B1[0]-B2[0])*(B1[0]-B2[0])+(B1[1]-B2[1])*(B1[1]-B2[1])+(B1[2]-B2[2])*(B1[2]-B2[2]));
}

//================================
// Normalise a vector
//================================
void Normalise(GLfloat V[3]){ 
	GLfloat s = V[0]*V[0]+V[1]*V[1]+V[2]*V[2];
	if (s!=0 && (fabs(s-1.0f)>0.00001f)){
		V[1] /= sqrt(s);
		V[2] /= sqrt(s);
		V[0] /= sqrt(s);
	}
} 

//================================
// Calculate dot product of two vectors to find projection of one direction
//================================
GLfloat Dot(GLfloat V1[3],GLfloat V2[3]){
	return V1[0]*V2[0]+V1[1]*V2[1]+V1[2]*V2[2];
}

//================================
// Detect whether two balls have collision, the method is retrived from http://nehe.gamedev.net/tutorial/collision_detection/17005/
//================================
void DetectCollision(int n){
	for (int i=n+1;i<BallNum;i++){ // handle the probable collision between ball n and other balls
		if (CalDistance(OldPos[n],OldPos[i])<1.01){ // if the Distance between ball n and ball i is less than the diameter, then collision occours
			GLfloat X_Axis[3];
			GLfloat U1_X[3], U1_Y[3];
			GLfloat U2_X[3], U2_Y[3];
			for(int j=0;j<3;j++){
				X_Axis[j]=OldPos[i][j]-OldPos[n][j]; // find X_Axis
			}
			Normalise(X_Axis);
			GLfloat a=Dot(X_Axis,OldVel[n]);// find projection
			for(int j=0;j<3;j++){ 
				U1_X[j]=a*X_Axis[j];// find projected vector for ball n
				U1_Y[j]=OldVel[n][j]-U1_X[j];
			}
			// do the same as above
			for(int j=0;j<3;j++){
				X_Axis[j]=OldPos[n][j]-OldPos[i][j];// find X_Axis
			}
			Normalise(X_Axis);
			GLfloat b=Dot(X_Axis,OldVel[i]);// find projection
			for(int j=0;j<3;j++){
				U2_X[j]=b*X_Axis[j];// find projected vector for ball i
				U2_Y[j]=OldVel[i][j]-U2_X[j];
			}
			// find new velocity
			GLfloat V1_X[3], V2_X[3];
			GLfloat V1_Y[3], V2_Y[3];
			for(int j=0;j<3;j++){
				V1_X[j]=(U1_X[j]*Mass[n]+U2_X[j]*Mass[i]-(U1_X[j]-U2_X[j])*Mass[i])/(Mass[n]+Mass[i]); 
				V2_X[j]=(U1_X[j]*Mass[n]+U2_X[j]*Mass[i]-(U2_X[j]-U1_X[j])*Mass[i])/(Mass[n]+Mass[i]);
				V1_Y[j]=U1_Y[j];
				V2_Y[j]=U2_Y[j];
				OldVel[n][j]=V1_X[j]+U1_Y[j];// new velocity for ball n
				OldVel[i][j]=V2_X[j]+U2_Y[j];// new velocity for ball i
			}
		}
	}
}

//================================
// The movement of ball n
//================================
void BallMovement(int n){
	if(OldPos[n][1]<0.5){ // floor collision detection
		OldVel[n][1]=-res*OldVel[n][1];
		OldVel[n][0]=OldVel[n][0];
		OldVel[n][2]=OldVel[n][2];
		OldPos[n][1]=0.5;
	}
	DetectCollision(n); // collsion with other balls
	for (int i=0;i<3;i++){
		NewVel[n][i]=OldVel[n][i]+gravity[i]*dt;
		OldVel[n][i]=NewVel[n][i];
		NewPos[n][i]=OldPos[n][i]+NewVel[n][i]*dt;
		OldPos[n][i]=NewPos[n][i];
		BallMatrix[n][12+i]=NewPos[n][i];			
	}
	
}

//================================
// Display the animation
//================================
void Display(){  
	for (int i=0;i<BallNum;i++){
		glPushMatrix();
		BallMovement(i); // Movement of ball i
		for (int j=0;j<16;j++){
			BM[j]=BallMatrix[i][j];// matrix of ball i
		}
		glMultMatrixf(BM);
		glutSolidSphere(0.5,20,20);
		glPopMatrix();
	}
}


//================================
// update
//================================
void update( void ) {
	// do something before rendering...
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
	gluLookAt (0, 8.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	DisplayFloor();
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
	gluPerspective(70.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);

}


//================================
// timer : triggered every 16ms ( about 60 frames per second )
//================================
void timer( int value ) {	
	update();
	
	// render
	glutPostRedisplay();

	// reset timer
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
	glutInitWindowSize( 1000, 600 ); 
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow("Lab3");

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