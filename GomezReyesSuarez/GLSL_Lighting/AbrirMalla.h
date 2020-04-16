#pragma once
#include "./glm/glm.h"
#include <iostream>

class AbrirMalla {

	public:
		GLMmodel* objmodel_ptr;
		AbrirMalla(char *);
		void DibujarMalla();
		~AbrirMalla();
};

