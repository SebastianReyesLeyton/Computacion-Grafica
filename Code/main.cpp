//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "Clases/Malla.h"
#include "Clases/ConstructorMalla.h"
#include "Clases/MallaTextura.h"
#include <FreeImage.h>
#include <math.h>
#include <vector>

//-----------------------------------------------------------------------------
#define NUM_OBJECTS 4
#define NUM_TEXTURES 1
#define RO 0.005
#define DELTA 0.05
#define BETTA 0.1

class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader, *shader1;
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp, rot;        // flag if counting up or down.
   ConstructorMalla constructor;
   Malla* mallas[NUM_OBJECTS];
   BOOLEAN statusAxes[6];
   GLfloat movXZ[2], rotY;
   std::vector< std::vector<GLfloat> > positions;
   GLuint textid;

public:
	myWindow(){}

    void initialize_textures(void) {
        int w, h;
        GLubyte* data = 0;

        //dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage

        glGenTextures(1, &textid);
        glBindTexture(GL_TEXTURE_2D, textid);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("mallas/bola.jpg", 0),
            "mallas/bola.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

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

    void movementControl() {

        if (statusAxes[0]) movXZ[0] = movXZ[0] - DELTA;    // Se mueve hacia la izquierda
        if (statusAxes[1]) movXZ[0] = movXZ[0] + DELTA;    // Se mueve a la derecha
        if (statusAxes[2]) rotY = ((rotY - BETTA) < 0) ? 360 : rotY - BETTA;
        if (statusAxes[3]) rotY = ((rotY + BETTA) > 360) ? BETTA : rotY + BETTA;
        if (statusAxes[4]) movXZ[1] = movXZ[1] - DELTA;    // Se mueve hacia adelante
        if (statusAxes[5]) movXZ[1] = movXZ[1] + DELTA;    // Se mueve hacia atras
    }

	virtual void OnRender(void) {
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
        //timer010 = 0.09; //for screenshot!
        glPushMatrix();
        movementControl();

        BOOLEAN result = false;
        for (int i = 0; i < 6; i++) {
            if (!result) result = statusAxes[i];
        }
        glTranslatef(0.0f, 0.0f, -4.0f);
        glTranslatef(movXZ[0], 0.0f, movXZ[1]);
        glRotatef(rotY, 0.0, 1.0, 0.0);

        if (bUp) {
            if (rot) {
                positions[3][3] = -90.0f;
                positions[3][4] = 0.0f;
                positions[3][5] = 1.0f;
                positions[3][6] = 0.0f;
                rot = false;
            }
            positions[3][0] -= RO;
        }
        else {
            if (!rot) {
                positions[3][3] = 90.0f;
                positions[3][4] = 0.0f;
                positions[3][5] = 1.0f;
                positions[3][6] = 0.0f;
                rot = true;
            }
            positions[3][0] += RO;
        }

        if (shader) shader->begin();

        glPushMatrix();
            glTranslatef(0.0f, -0.5f, 0.0f);
            glScalef(1.0, 0.01, 1.0);
            glutSolidCube(20);
        glPopMatrix();
        
        if (shader) shader->end();
        
        if (shader1) shader1->begin();

        // Renderizacion
        for (int i = 0; i < NUM_OBJECTS; i++) {
            glPushMatrix();
            mallas[i]->transformaciones(positions[i]);
            mallas[i]->dibujarMalla();
            glPopMatrix();
        }
      
        // Fin de la Renderizacion

        if (shader1) shader1->end();
        glutSwapBuffers();
        glPopMatrix();

        UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
    virtual void OnInit() {

        glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        // Inicializacion de objetos

        char* nombres[NUM_OBJECTS] = {"trapiche", "casa principal", "perro", "caballo"};
        //char* nombres[NUM_OBJECTS] = { "trapiche" };
     
        positions = {};

        // Trapiche
        std::vector< GLfloat > transformation = {8.0f, 0.30f, 0.3f, -90.0f, 0.0f, 1.0f, 0.0f, 2.0f, 2.0f, 2.0f };
        positions.push_back(transformation);
        
        // Casa Pricipal
        transformation = { -6.0f, 0.9f, 0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 4.0f, 4.0f, 4.0f };
        positions.push_back(transformation);

        // Perro
        transformation = { -4.0f, -0.27f, 0.0f, -90.0f, 1.0f, 0.0f, 0.0f, 0.18f, 0.18f, 0.18f };
        positions.push_back(transformation);

        // Caballo
        transformation = { 8.0f, -0.15f, 2.5f, -90.0f, 0.0f, 1.0f, 0.0f, 0.4f, 0.4f, 0.4f };
        positions.push_back(transformation);
        
        constructor = ConstructorMalla();
        for (int i = 0; i < NUM_OBJECTS; i++) {
            mallas[i] = NULL;
        }

        for (int i = 0; i < NUM_OBJECTS; i++) {
            constructor.crearMalla(nombres[i]);
            mallas[i] = constructor.obtenerMalla();
            mallas[i]->abrirMalla();
        }

        // Fin de la Inicializacion de objetos
       
		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
            std::cout << "Error Loading, compiling or linking shader\n";
        else
        {
            ProgramObject = shader->GetProgramObject();
        }

        shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
        if (shader1 == 0)
            std::cout << "Error Loading, compiling or linking shader1\n";
        else
        {
            ProgramObject = shader1->GetProgramObject();
        }

        // Inizialización de las variables
        time0 = clock();
        timer010 = 0.0f;
        bUp = true;
        rot = false;

        for (int i = 0; i < 6; i++) {
            statusAxes[i] = false;
        }

        movXZ[0] = 0;
        movXZ[1] = 0;
        rotY = 0;
        // Fin de la Inicializacion de las variables
        initialize_textures();
        
        DemoLight();
	}

	virtual void OnResize(int w, int h) {

      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       gluLookAt(0.0f, 0.0f, 0.0f,
           0.0, 0.0, -1.0,
           0.0f, 1.0f, 0.0f);
    }

	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) {           // 0x1b = ESC
			this->Close();            // Close Window!
		}

        switch (cAscii) {
            case 'w': statusAxes[5] = true;
                      break;
            case 's': statusAxes[4] = true;
                      break;
            case 'd': statusAxes[0] = true;
                      break;
            case 'a': statusAxes[1] = true;
                      break;
            case 'e': statusAxes[2] = true;
                      break;
            case 'q': statusAxes[3] = true;
                      break;
        }

	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      if (cAscii == 's')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();

      switch (cAscii) {
      case 'w': statusAxes[5] = false;
                break;
      case 's': statusAxes[4] = false;
                break;
      case 'd': statusAxes[0] = false;
                break;
      case 'a': statusAxes[1] = false;
                break;
      case 'e': statusAxes[2] = false;
                break;
      case 'q': statusAxes[3] = false;
                break;
      }
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     /*
     // Light model parameters:
     // -------------------------------------------
     
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

     // -------------------------------------------
     // Material parameters:

     GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 20.0f;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
     */
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

