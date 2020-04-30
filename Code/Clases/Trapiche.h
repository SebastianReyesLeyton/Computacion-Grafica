#pragma once
#include "MallaTextura.h"
#include "Techo.h"

class Trapiche : public MallaTextura {
	public:
		Trapiche();
		Malla* techo;
		void transformaciones(std::vector< GLfloat > transformation);
};