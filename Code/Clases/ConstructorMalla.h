#pragma once
#include <iostream>
#include "Malla.h"
#include "Trapiche.h"
#include "CasaPrincipal.h"
#include "Perro.h"
#include "Caballo.h"

class ConstructorMalla {
	Malla* malla;
	char* name;
	public:
		ConstructorMalla();
		ConstructorMalla(char*);
		Malla* obtenerMalla();
		void crearMalla();
		void crearMalla(char*);
};