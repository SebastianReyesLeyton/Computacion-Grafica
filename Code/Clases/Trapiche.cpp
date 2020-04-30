#include "Trapiche.h"

Trapiche::Trapiche() {
	techo = new Techo();
	std::cout << "Se ha creador un trapiche: " << name << std::endl;
	textura->name = "./mallas/texture/madera.jpg";
	textura->initialize_texture();
	name = "./mallas/arquitecturas/trapiche.obj";

	techo->abrirMalla();
}

void Trapiche::transformaciones(std::vector< GLfloat > transformation) {
	glTranslatef(transformation[0], transformation[1], transformation[2]);
	glRotatef(transformation[3], transformation[4], transformation[5], transformation[6]);
	glScalef(transformation[7], transformation[8], transformation[9]);

	std::vector< GLfloat > transformation1 = { 0.0f, 0.32f, 0.0f, 0.0f, 0.0f, 0.0f , 0.0f, 1.1, 1.1, 1.1 };
	glPushMatrix();
	techo->transformaciones(transformation1);
	techo->dibujarMalla();
	glPopMatrix();
}
