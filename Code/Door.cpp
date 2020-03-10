#include "Door.h"

Door::Door(){}

void Door::Draw(GLfloat x, GLfloat y, GLfloat z) {
	
	glPushMatrix();
		glTranslatef(x, y, z);
		
		// Draw Border
		glPushMatrix();
			
			// Door
			glPushMatrix();
				glScalef(0.5f, 1.0f, 0.05f);
				glutSolidCube(1.0);
			glPopMatrix();

			// First Scale
			glPushMatrix();
				glScalef(0.6f, 0.15f, 0.35f);
				glTranslatef(0.0, -3, 0.0);
				glutSolidCube(1.0);
			glPopMatrix();
			// Second Scale
			glPushMatrix();
				glScalef(0.6f, 0.1f, 0.5f);
				glTranslatef(0.0, -5, 0.0);
				glutSolidCube(1.0);
			glPopMatrix();

			// Right border
			glPushMatrix();
				glTranslatef(0.25f, 0.0, 0.0);
				glScalef(0.05f, 1.0f, 0.2f);
				glutSolidCube(1.0);
			glPopMatrix();

			// Left Border
			glPushMatrix();
				glTranslatef(-0.25f, 0.0, 0.0);
				glScalef(0.05f, 1.0f, 0.2f);
				glutSolidCube(1.0);
			glPopMatrix();

			// Top Border
			glPushMatrix();
				glTranslatef(0.0f, 0.5f, 0.0);
				glScalef(0.6f, 0.05f, 0.2f);
				glutSolidCube(1.0);
			glPopMatrix();

			// Perilla
			glPushMatrix();
				glTranslatef(0.0, 0.0, 0.1);
				glutSolidSphere(0.05, 20, 20);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}