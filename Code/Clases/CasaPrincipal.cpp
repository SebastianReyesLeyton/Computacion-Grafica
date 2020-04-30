#include "CasaPrincipal.h"

CasaPrincipal::CasaPrincipal() {
	name = "./mallas/arquitecturas/CasaPrincipalEscala.obj";
	std::cout << "Has creado una Casa Principal " << std::endl;
}

CasaPrincipal::~CasaPrincipal() {
	std::cout << "Has destruido una Casa Principal " << std::endl;
}