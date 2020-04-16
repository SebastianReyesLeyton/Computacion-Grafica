#include "ClassTree.h"

ClassTree::ClassTree() {

}

void ClassTree::DrawTree(GLfloat x, GLfloat y, GLfloat z) {
	
	glPushMatrix();
		glTranslatef(x, y, z);

		// Este dibuja el tallo
		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glutSolidCylinder(0.2f, 0.8f, 20, 20);
		glPopMatrix();
		// Traslada el follaje y lo dibuja
		glPushMatrix();
			glTranslatef(0.0f, 0.4f, 0.0);
			glutSolidSphere(0.5, 20, 20);
		glPopMatrix();
	
	glPopMatrix();
}