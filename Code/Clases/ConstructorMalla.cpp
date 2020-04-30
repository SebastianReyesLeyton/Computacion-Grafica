#include "ConstructorMalla.h"

ConstructorMalla::ConstructorMalla() {
	name = "";
	malla = NULL;
}

ConstructorMalla::ConstructorMalla(char* name) {
	this->name = name;
	crearMalla();
}

Malla* ConstructorMalla::obtenerMalla() {
	return malla;
}

void ConstructorMalla::crearMalla() {
	if (!strcmp(name, ""))
		std::cout << "No se va a crear ningun objeto" << std::endl;
	else {
		if (!strcmp(name, "trapiche")) malla = new Trapiche();
		else if (!strcmp(name, "casa principal")) malla = new CasaPrincipal();
		else if (!strcmp(name, "perro")) malla = new Perro();
		else if (!strcmp(name, "caballo")) malla = new Caballo();
	}
}

void ConstructorMalla::crearMalla(char* name) {
	this->name = name;
	crearMalla();
}