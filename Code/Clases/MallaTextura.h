#pragma once
#include "Malla.h"

class MallaTextura : public Malla {
	
	public:
		Textura* textura;
		MallaTextura();
		void dibujarMalla();
		~MallaTextura();
};