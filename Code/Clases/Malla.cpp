#include "Malla.h"
Malla::Malla() {
	objmodel_ptr = NULL;
	name = "./mallas";
	std::cout << "Se ha creado un objeto tipo Malla" << std::endl;
}

void Malla::dibujarMalla() {
	glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL );
}

void Malla::transformaciones(std::vector< GLfloat > transformation) {
	glTranslatef(transformation[0], transformation[1], transformation[2]);
	glRotatef(transformation[3], transformation[4], transformation[5], transformation[6]);
	glScalef(transformation[7], transformation[8], transformation[9]);
}

void Malla::abrirMalla() {
	objmodel_ptr = NULL;
	if (!objmodel_ptr) {
		objmodel_ptr = glmReadOBJ(name);
		if (!objmodel_ptr)
			exit(0);

		glmUnitize(objmodel_ptr);
		glmFacetNormals(objmodel_ptr);
		glmVertexNormals(objmodel_ptr, 90.0);
	}
}

Malla::~Malla() {
	std::cout << "Se ha destruido un objeto tipo malla." << std::endl;
}