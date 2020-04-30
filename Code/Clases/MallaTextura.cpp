#include "MallaTextura.h"
MallaTextura::MallaTextura() {
	textura = new Textura();
	std::cout << "Se ha creado un objeto tipo Malla con textura" << std::endl;
}

void MallaTextura::dibujarMalla() {
	std::cout << "Se ha dibujado una malla con textura" << std::endl;
	glBindTexture(GL_TEXTURE_2D, textura->textid);
	glmDraw(objmodel_ptr, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE );
}

MallaTextura::~MallaTextura() {
	std::cout << "Se ha destruido un objeto tipo malla con textura." << std::endl;
}