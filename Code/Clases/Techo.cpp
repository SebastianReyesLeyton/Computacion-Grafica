#include "Techo.h"

Techo::Techo() {
	std::cout << "Se ha creador un techo: " << name << std::endl;
	textura->name = "./mallas/texture/tejado.jpg";
	textura->initialize_texture();
	name = "./mallas/arquitecturas/techo.obj";
}