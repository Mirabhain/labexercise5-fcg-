#include<Windows.h>
#include<GL/glut.h>
#include<iostream>
#include "imageloader.h"

//make it move
//add image 
using namespace std;
float _angle = 0.0f;

void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
	}
}

GLuint loadTexture(Image* image)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Set texture parameters here!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGB,
		image->width, image->height,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		image->pixels);

	return textureId;
}


//GLuint _textureId1;
//GLuint _textureId2;
//GLuint _textureId3;
//GLuint _textureId4;
//GLuint _textureId5;
//GLuint _textureId6;

GLuint _textureId[6];

void initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // Grey background to see your cube clearly


	for (int i = 0; i < 6; i++) {
		_textureId[i] = 0;
	}
Image* image1 = loadBMP("image2_v3.bmp");
	_textureId[0] = loadTexture(image1);
	delete image1;

	Image* image2 = loadBMP("image2_v3.bmp");
	_textureId[1] = loadTexture(image2);
	delete image2;

	Image* image3 = loadBMP("image3_v3.bmp");
	_textureId[2] = loadTexture(image3);
	delete image3;

	Image* image4 = loadBMP("image4_v3.bmp");
	_textureId[3] = loadTexture(image4);
	delete image4;

	Image* image5 = loadBMP("image5_v3.bmp");
	_textureId[4] = loadTexture(image5);
	delete image5;

	Image* image6 = loadBMP("image6_v3.bmp");
	_textureId[5] = loadTexture(image6);
	delete image6; 

	
}

void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void update(int value) {
	_angle += 1.0f;  // You can adjust speed here
	if (_angle > 360) {
		_angle -= 360;
	}
	glutPostRedisplay();  // Tell GLUT to redraw the scene
	glutTimerFunc(25, update, 0);  // Call again after 25 ms
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 1.0f, -6.0f);
	glRotatef(_angle, 1.0f, 1.0f, 0.0f);

	// Draw textured cube
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	

	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);

	// Front face

	glBindTexture(GL_TEXTURE_2D, _textureId[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	// Back face
	
		glBindTexture(GL_TEXTURE_2D, _textureId[0]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd();
	

	// Left face
	
		glBindTexture(GL_TEXTURE_2D, _textureId[2]);
		glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glEnd();
	

	// Right face
		glBindTexture(GL_TEXTURE_2D, _textureId[3]);
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	// Top face
	glBindTexture(GL_TEXTURE_2D, _textureId[4]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	// Bottom face
	glBindTexture(GL_TEXTURE_2D, _textureId[5]);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(600, 400);

    glutCreateWindow("Texture Mapping");
    initRendering();
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);


    glutMainLoop();
    return 0;
}
