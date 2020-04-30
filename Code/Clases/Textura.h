#pragma once
#include "./glsl.h"
#include "../glm/glm.h"
#include "FreeImage.h"
#include <iostream>

class Textura{
	
	public:
		Textura();
		char *name;
		GLuint textid;
		void initialize_texture();
		~Textura();
};