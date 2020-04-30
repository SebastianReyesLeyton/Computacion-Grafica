#pragma once
#include "Textura.h"
#include <iostream>
#include <string>
#include <vector>

class Malla {
	
	public:
		Malla();
		GLMmodel* objmodel_ptr;
		char* name;
		virtual void dibujarMalla();
		virtual void transformaciones(std::vector< GLfloat > transformation);
		void abrirMalla();
		~Malla();
};