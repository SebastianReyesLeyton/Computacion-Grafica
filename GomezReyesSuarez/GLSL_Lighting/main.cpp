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
#include "ClassTree.h"
#include "Door.h"
#include "./glm/glm.h"
#include "AbrirMalla.h"

//-----------------------------------------------------------------------------
#define NUM_TREE 10
#define SEGMENTS 8
#define DELTA 0.03
#define BETTA 0.5
#define NUM_MALLAS 5

/*
MALLAS:
0: Casa
1: Caballo
2: Trapiche
3: Acueducto
4: Perro

*/

class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   ClassTree Jardin[NUM_TREE];
   Door door;
   AbrirMalla* malla[NUM_MALLAS];
   int shoulder = 0;
   int angles[SEGMENTS];
   GLfloat movZ, movX;
   GLfloat rotY;
   BOOLEAN mZPositivo, mZNegativo, mX[2], rY[2];
public:
	myWindow(){}

    void ControlDeMovimiento() 
    {
        if (mZPositivo)
        {
            movZ -= DELTA;
        }
        
        if (mZNegativo)
        {
            movZ += DELTA;
        }

        if (mX[1])
        {
            movX += DELTA;
        }

        if (mX[0])
        {
            movX -= DELTA;
        }

        if (rY[0]) {
            rotY = (rotY - BETTA < 0) ? 360 : rotY - BETTA;
        }
        if (rY[1]) {
            rotY = ((rotY + BETTA) > 360) ? BETTA : rotY + BETTA;
        }
    }
	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!
      glPushMatrix();
      glTranslatef(-2,0,10);
      ControlDeMovimiento();
      glTranslatef(movX, 0.0f, movZ);
      glRotatef(rotY, 0.0f, 1.0f, 0.0f); // control rotacion mundo ( Q, E )
      glTranslatef(1, -0.25, 0); //control movimiento camara (W A S D)
      
      // dibujar casa
      malla[0]->DibujarMalla();

      // dibujar caballo
      glPushMatrix();
      glTranslatef(1, -0.25, 0);
      malla[1]->DibujarMalla();
      glPopMatrix();

      // dibujar trapiche
      glPushMatrix();
      glTranslatef(3, -0.15, 0.3);
      glRotatef(180, 0, 1, 0);
      malla[2]->DibujarMalla();
      glPopMatrix();

      //dibujar acueducto
      glPushMatrix();
      glTranslatef(2.47, -0.4, -0.17);
      glRotatef(180, 0, 1, 0);
      malla[3]->DibujarMalla();
      glPopMatrix();

      // dibujar perro
      glPushMatrix();
      glTranslatef(1.2, -0.28, 0);
      glRotatef(90, 0, 1,0);
      malla[4]->DibujarMalla();
      glPopMatrix();

      
     if (shader) shader->end();
      glutSwapBuffers();
      glPopMatrix();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		glClearColor(0.1f, 0.9f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

        malla[0] = new AbrirMalla("./mallas/casa/CasaPrincipalEscala.obj");
        malla[1] = new AbrirMalla("./mallas/caballo/caballoEscala.obj");
        malla[2] = new AbrirMalla("./mallas/trapiche/trapicheEscala3.obj");
        malla[3] = new AbrirMalla("./mallas/acueducto/acueductoEscala2.obj");
        malla[4] = new AbrirMalla("./mallas/perro/perroEscala2.obj");
        for (int i = 0; i < NUM_TREE; i++) {
            Jardin[i] = ClassTree();
        }

        angles[0] = 0;
        for (int i = 1; i < SEGMENTS; i++) {
            angles[i] = 20;
        }
       
		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;

      DemoLight();

      movZ = 0;
      movX = 0;
      rotY = 0;
      mZPositivo = false;
      mZNegativo = false;
      mX[0] = false;
      mX[1] = false;
      rY[0] = false;
      rY[1] = false;
	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f, 15.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f + movZ);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		}
        else if (cAscii == 'W') {
            angles[0] = (angles[0] + 5) % 360;
            shoulder = (shoulder + 5) % 360;
            glutPostRedisplay();
        }
        else if (cAscii == 'E') {
            angles[1] = (angles[1] + 5) % 360;
            glutPostRedisplay();
        }
        else if (cAscii == 'R') {
            angles[2] = (angles[2] + 5) % 360;
            glutPostRedisplay();
        }
        else if (cAscii == 'T') {
            angles[3] = (angles[3] + 5) % 360;
            glutPostRedisplay();
        }
        else if (cAscii == 'Y') {
            angles[4] = (angles[4] + 5) % 360;
            glutPostRedisplay();
        }
        else if (cAscii == 'U') {
            angles[5] = (angles[5] + 5) % 360;
            glutPostRedisplay();
        }
        else if (cAscii == 'I') {
            angles[6] = (angles[6] + 5) % 360;
            glutPostRedisplay();
        }
        else if (cAscii == 'O') {
            angles[7] = (angles[7] + 5) % 360;
            glutPostRedisplay();
        }

        switch (cAscii) {
        case 'w':
            mZNegativo = true;
            break;
        case 'd':
            mX[0] = true;
            break;
        case 'a':
            mX[1] = true;
            break;
        case 's':
            mZPositivo = true;
            break;
        case 'e':
            rY[1] = true;
            break;
        case 'q':
            rY[0] = true;
            break;
        }

        /*
        else if (cAscii == 'W') { // Para la que es en conjunto
            shoulder = (shoulder + 5) % 360;
            glutPostRedisplay();
        }
        */
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      if (cAscii == 'l')      // s: Shader
         shader->enable();
      else if (cAscii == 'L') // f: Fixed Function
         shader->disable();
      
      switch (cAscii) {
      case 'w':
          mZNegativo = false;
          break;
      case 'd':
          mX[0] = false;
          break;
      case 'a':
          mX[1] = false;
          break;
      case 's':
          mZPositivo = false;
          break;
      case 'e':
          rY[1] = false;
          break;
      case 'q':
          rY[0] = false;
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

