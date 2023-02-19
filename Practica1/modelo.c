/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: 

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"


/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void
initModel ()
{

}


class Ejes:Objeto3D { 

public: 
  float longitud = 30;

// Dibuja el objeto
  void draw( ){
    glDisable (GL_LIGHTING);
    glBegin (GL_LINES);{
      glColor3f (0, 1, 0);
      glVertex3f (0, 0, 0);
      glVertex3f (0, longitud, 0);

      glColor3f (1, 0, 0);
      glVertex3f (0, 0, 0);
      glVertex3f (longitud, 0, 0);

      glColor3f (0, 0, 1);
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, longitud);
    }
    glEnd ();
    glEnable (GL_LIGHTING);
  }
}; 

//Clase Cubo.
class Cubo:Objeto3D{
  
  private:
    float lado;
  
  public:
    Cubo(float lado){
      this -> lado = lado;
    }

    void draw(){
      float color[4]={0.8,0.0,1,1};
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color ); //Color morado

      /*
        GL_QUAD_STRIP para las caras transversales. Con esta función, no haría 
        falta repetir los vértices en cada cara, pues ya están definidos antes, 
        si se re-definen, se crearían aristas de más.
      */
      glBegin( GL_QUAD_STRIP );{ //Caras transversales

        //Vertical delantera
        glNormal3f( 0.0, 0.0, 1.0 );
        glVertex3f( lado, lado, lado );
        glVertex3f( 0, lado, lado );
        glVertex3f( lado, 0, lado );
        glVertex3f( 0, 0, lado );
        
        //Inferior
        glNormal3f( 0.0, -1.0, 0.0 ); 
        glVertex3f( lado, 0, 0 );
        glVertex3f( 0, 0, 0 );
        
        //Vertical hacia atras 
        glNormal3f( 0.0, 0.0, -1.0 ); 
        glVertex3f( lado, lado, 0 );
        glVertex3f( 0, lado, 0 );
        
        //Superior, horizontal 
        glNormal3f( 0.0, 1.0, 0.0 ); 
        glVertex3f( lado, lado, lado );
        glVertex3f( 0, lado, lado );
      }
      glEnd();

      /*
        GL_QUADS para los costados, aquí si es necesario especificar los vértices
        de cada cara, a pesar de que tengan vértices en común ya definidos 
        anteriormente.
      */
      glBegin( GL_QUADS );{ // Costados 
        glNormal3f( -1.0, 0.0, 0.0 );
        glVertex3f( lado, 0, 0 );
        glVertex3f( lado, lado, 0 );
        glVertex3f( lado, lado, lado );
        glVertex3f( lado, 0, lado );
        glNormal3f( 1.0, 0.0, 0.0 );
        glVertex3f( 0, 0, 0 );
        glVertex3f( 0, 0, lado );
        glVertex3f( 0, lado, lado );
        glVertex3f( 0, lado, 0 );
      } 
      glEnd();
    }   
};


//Clase Piramide.
class Piramide:Objeto3D{
  private:
    float lado;
    float altura;
    float B;
    float normalXZ, normalY;
    

  public:
    Piramide(float lado, float altura){
      this -> lado = lado;
      this -> altura = altura;

      //formula explicada en clase para el calculo de la normal.
      B = sqrt(pow(this->lado,2) + pow(this->altura,2));
      normalXZ = lado/B;
      normalY = altura/B;
    }

    void draw(){
      float color2[4] = {0.0, 1, 1, 0.0};
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2 ); //Color azul turquesa
      
      /*
        GL_TRIANGLES, por tanto hay que repetir todos los vértices, aunque sean
        comunes. La base inferior también la he hecho con triángulos, en concreto
        con 2. LAs caras deben darse en sentido antihorario
      */
      glBegin(GL_TRIANGLES);{
         
         //Vertical delantera
         glNormal3f( 0.0, normalY, normalXZ); 
         glVertex3f(lado/2, altura, lado/2);
         glVertex3f(0, 0, lado);
         glVertex3f(lado, 0, lado);
         
         //Vertical trasera
         glNormal3f(0.0, normalY, -normalXZ);
         glVertex3f(lado/2, altura, lado/2);
         glVertex3f(lado, 0, 0);
         glVertex3f(0, 0, 0); 
         
         //Costado derecho
         glNormal3f(normalXZ, normalY, 0.0);
         glVertex3f(lado/2, altura, lado/2);
         glVertex3f(lado, 0, lado);
         glVertex3f(lado, 0, 0);

         //Costado izquierdo
         glNormal3f(-normalXZ, normalY, 0.0);
         glVertex3f(lado/2, altura, lado/2);
         glVertex3f(0, 0, 0); 
         glVertex3f(0, 0, lado);

         //Inferior, construida con 2 triangulos       
         glNormal3f(0.0, -1.0, 0.0);
          
          //Primer triángulo base
          glVertex3f(0, 0, 0);
          glVertex3f(lado, 0, lado);
          glVertex3f(0, 0,lado);
          
          //Segundo triángulo base
          glVertex3f(0, 0, 0);
          glVertex3f(lado, 0, 0);
          glVertex3f(lado, 0, lado);
      }
      glEnd();
    }
};


//Clase Tetraedro.
class Tetraedro:Objeto3D{
  private:
    float lado;
    float altura;
    float B;
    float normalXZ, normalY;

  public:

    Tetraedro(float lado, float altura){
      this -> lado = lado;
      this -> altura = altura;

      //Calculamos la normal como en la pirámide.
      B = sqrt(pow(this->lado,2) + pow(this->altura,2));
      normalXZ = lado/B;
      normalY = altura/B;
    }

    void draw(){
      float color3[4] = {1, 1, 0.0, 0.0}; //Color amarillo
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3 );

      /*
      Lo he hecho también con GL_TRIANGLES. Caras en sentido antihorario.
      */
      glBegin(GL_TRIANGLES);{
        //Cara trasera
        glNormal3f(0.0, normalY, -normalXZ);
        glVertex3f(lado/2, altura, lado/2);
        glVertex3f(lado, 0, 0);
        glVertex3f(0, 0, 0);

        //Cara delantera izquierda
        glNormal3f(0.0, normalY, normalXZ);
        glVertex3f(lado/2, altura, lado/2);
        glVertex3f(0, 0, 0);
        glVertex3f(lado/2, 0, lado/2);

        //Cara delantera derecha
        glNormal3f(normalXZ, normalY, 0.0);
        glVertex3f(lado/2, altura, lado/2);
        glVertex3f(lado/2, 0, lado/2);
        glVertex3f(lado, 0, 0);

        //Cara debajo
        glNormal3f(0.0, -1, 0.0);
        glVertex3f(lado/2, 0, lado/2);
        glVertex3f(0, 0, 0);
        glVertex3f(lado, 0, 0);
        
      }
      glEnd();
  
    }

};

//Clase Prisma Rectangular     
class PrismaRectangular:Objeto3D{
  private:
    float lado;
    float altura;

  public:
    PrismaRectangular(float lado, float altura){
      this->lado = lado;
      this->altura = altura;
    }

    void draw(){
      float color4[4] = {1, 1, 1, 0.0};
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color4);

      //Lo he hecho con GL_QUADS, repito vértices. Sentido antihorario de las caras
      glBegin(GL_QUADS);{
        //Vertical delantera
        glNormal3f(0.0, 0.0, 1.0); 
        glVertex3f(lado, altura, lado);
        glVertex3f(0, altura, lado);
        glVertex3f(0, 0, lado);
        glVertex3f(lado, 0, lado);

        //Vertical trasera
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(0, altura, 0);
        glVertex3f(lado, altura, 0);
        glVertex3f(lado, 0, 0);
        glVertex3f(0, 0, 0);

        //Tapa debajo
        glNormal3f( 0.0, -1.0, 0.0);
        glVertex3f(0, 0, 0);
        glVertex3f(lado, 0, 0);
        glVertex3f(lado, 0, lado);
        glVertex3f(0, 0, lado);

        //Tapa de arriba
        glNormal3f( 0.0, 1.0, 0.0); 
        glVertex3f(lado, altura, 0);
        glVertex3f(0, altura, 0);
        glVertex3f(0, altura, lado);
        glVertex3f(lado, altura, lado);
     
        //Costado derecho
        glNormal3f( 1.0, 0.0, 0.0 );
        glVertex3f( lado, 0, 0 );
        glVertex3f( lado, altura, 0 );
        glVertex3f( lado, altura, lado );
        glVertex3f( lado, 0, lado );

        //Costado izquierdo
        glNormal3f( -1.0, 0.0, 0.0 );
        glVertex3f( 0, 0, 0 );
        glVertex3f( 0, 0, lado );
        glVertex3f( 0, altura, lado );
        glVertex3f( 0, altura, 0 );
        
      }
      glEnd();

    }

};

Ejes ejesCoordenadas;

//Creo los objetos de cada figura con sus correspondientes dimensiones.
Cubo cubo(4);
Piramide piramide(4,7);
Tetraedro tetraedro(5,7);
PrismaRectangular prisma(4,7);

int modo = GL_FILL;
bool iluminacion;

void setModo(int M){
  modo = M;
  glPolygonMode(GL_FRONT_AND_BACK, modo);
}

void modificaIluminacion(){
  if (iluminacion==1){
    iluminacion = 0;
    glDisable(GL_LIGHTING);
    glDisable (GL_LIGHT0);
  }

  else{
    iluminacion = 1;
    glEnable(GL_LIGHTING);
    glEnable (GL_LIGHT0);
  }
}

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
--
**/

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz
  float color[4] = {0.8, 0.0, 1, 1}; //Color cubo
  float color2[4] = {0.0, 1, 1, 0.0}; //Cubo Pirámide
  float color3[4] = {1, 1, 0.0, 0.0}; //Color Tetraedro
  float color4[4] = {1, 1, 1, 0.0}; //Color Prisma Rectangular
  
  glPushMatrix ();		// Apila la transformacion geometrica actual
  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer
  transformacionVisualizacion ();	// Carga transformacion de visualizacion
  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena
  ejesCoordenadas.draw();			// Dibuja los ejes
  
  //Cubo
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  glPointSize(17.0);
  cubo.draw();
  
  //Pirámide
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
  glTranslatef(5,0,0);
  piramide.draw();

  //Tetraedro
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
  glTranslatef(5,0,0);
  tetraedro.draw();
  
  //Prisma Rectangular
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color4);
  glTranslatef(6,0,0);
  prisma.draw();
  

  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)          
  glPopMatrix ();		// Desapila la transformacion geometrica
  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{
  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}
