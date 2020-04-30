#include "Textura.h"
Textura::Textura() {
	name = "";
	std::cout << "Se ha creado un objeto tipo Malla con textura" << std::endl;
}

void Textura::initialize_texture() {
    int w, h;
    GLubyte* data = 0;

    //dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage
    std::cout << "Se va a cargar: " <<  name << "\n";
    glGenTextures(1, &textid);
    glBindTexture(GL_TEXTURE_2D, textid);
    glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Loading JPG file
    FIBITMAP* bitmap = FreeImage_Load(
        FreeImage_GetFileType(name, 0),
        name);  //*** Para Textura: esta es la ruta en donde se encuentra la textura

    FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
    std::cout << pImage << "\n";
    int nWidth = FreeImage_GetWidth(pImage);
    int nHeight = FreeImage_GetHeight(pImage);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
        0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

    FreeImage_Unload(pImage);
    //
    glEnable(GL_TEXTURE_2D);
}

Textura::~Textura() {
	std::cout << "Se ha destruido un objeto tipo malla con textura." << std::endl;
}