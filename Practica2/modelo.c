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
 but WITHOUT ANy WARRANTy; without even the implied warranty of
 MERCHANTABILITy or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
#include "file_ply_stl.h"


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
    float normalxz, normaly;
    

  public:
    Piramide(float lado, float altura){
      this -> lado = lado;
      this -> altura = altura;

      //formula explicada en clase para el calculo de la normal.
      B = sqrt(pow(this->lado,2) + pow(this->altura,2));
      normalxz = lado/B;
      normaly = altura/B;
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
         glNormal3f( 0.0, normaly, normalxz); 
         glVertex3f(lado/2, altura, lado/2);
         glVertex3f(0, 0, lado);
         glVertex3f(lado, 0, lado);
         
         //Vertical trasera
         glNormal3f(0.0, normaly, -normalxz);
         glVertex3f(lado/2, altura, lado/2);
         glVertex3f(lado, 0, 0);
         glVertex3f(0, 0, 0); 
         
         //Costado derecho
         glNormal3f(normalxz, normaly, 0.0);
         glVertex3f(lado/2, altura, lado/2);
         glVertex3f(lado, 0, lado);
         glVertex3f(lado, 0, 0);

         //Costado izquierdo
         glNormal3f(-normalxz, normaly, 0.0);
         glVertex3f(lado/2, altura, lado/2);
         glVertex3f(0, 0, 0); 
         glVertex3f(0, 0, lado);

         //Inferior, construida con 2 caras_ply       
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
    float normalxz, normaly;

  public:

    Tetraedro(float lado, float altura){
      this -> lado = lado;
      this -> altura = altura;

      //Calculamos la normal como en la pirámide.
      B = sqrt(pow(this->lado,2) + pow(this->altura,2));
      normalxz = lado/B;
      normaly = altura/B;
    }

    void draw(){
      float color3[4] = {1, 1, 0.0, 0.0}; //Color amarillo
      glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3 );

      /*
      Lo he hecho también con GL_TRIANGLES. Caras en sentido antihorario.
      */
      glBegin(GL_TRIANGLES);{
        //Cara trasera
        glNormal3f(0.0, normaly, -normalxz);
        glVertex3f(lado/2, altura, lado/2);
        glVertex3f(lado, 0, 0);
        glVertex3f(0, 0, 0);

        //Cara delantera izquierda
        glNormal3f(0.0, normaly, normalxz);
        glVertex3f(lado/2, altura, lado/2);
        glVertex3f(0, 0, 0);
        glVertex3f(lado/2, 0, lado/2);

        //Cara delantera derecha
        glNormal3f(normalxz, normaly, 0.0);
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
 

class MallaTriangulo : public Objeto3D{
 public:
  
    struct CoordenadasV{
      float x;
      float y;
      float z;
    };

    std::vector <float> vertices_ply;
    std::vector <int> caras_ply;
    std::vector <CoordenadasV> vertices;
    std::vector <CoordenadasV> normalesVertices;
    std::vector <CoordenadasV> normalesCaras;

    MallaTriangulo(){

    }

    MallaTriangulo(const char *nombre_archivo ){
      ply::read(nombre_archivo, vertices_ply, caras_ply);
      
      CoordenadasV vert;
      for(int i = 0; i < vertices_ply.size(); i+=3){
        vert.x = vertices_ply[i];
        vert.y = vertices_ply[i+1];
        vert.z = vertices_ply[i+2];
        vertices.push_back(vert);
      }
      
      //Cada cara corresponde a 3 posiciones del vector de vértices
      CoordenadasV v;
      for (int i = 0; i < caras_ply.size(); i+=3){
        v = normalCara(vertices[caras_ply[i]],
                       vertices[caras_ply[i+1]],
                       vertices[caras_ply[i+2]]);
        
        normalesCaras.push_back(v);
      }

      normalVertice();   
    }

    //Función que calcula la normal de una cara dados 3 vértices
    CoordenadasV normalCara(CoordenadasV p0, CoordenadasV p1, CoordenadasV p2){
      
      CoordenadasV p0p1,p0p2,Normal;
      float modulo;

      p0p1.x = p1.x - p0.x;
      p0p1.y = p1.y - p0.y;
      p0p1.z = p1.z - p0.z;

      p0p2.x = p2.x - p0.x;
      p0p2.y = p2.y - p0.y;
      p0p2.z = p2.z - p0.z;


      Normal.x = (p0p1.y * p0p2.z) - (p0p1.z * p0p2.y); 
      Normal.y = -((p0p1.z * p0p2.x) - (p0p1.x * p0p2.z)); 
      Normal.z = (p0p1.x * p0p2.y) - (p0p1.y * p0p2.x); 

      modulo = sqrt(pow(Normal.x, 2) + pow(Normal.y, 2) + pow(Normal.z, 2));

      if (modulo > 0){
        Normal.x = Normal.x / modulo; 
        Normal.y = Normal.y / modulo; 
        Normal.z = Normal.z / modulo; 
      }

      return Normal;
    }

    //Función que calcula la normal de los vértices
    void normalVertice(){
      
      CoordenadasV vertex;
      for(int i = 0; i< vertices.size(); i++){
        vertex.x = 0;
        vertex.y = 0;
        vertex.z = 0;
        normalesVertices.push_back(vertex);
      }   
      
      //Para cada cara, sumar a cada de las componentes de sus vértices, la normal de dicha cara
      int contador = 0;
      for (int i = 0; i < caras_ply.size();i+=3){

        normalesVertices[caras_ply[i]].x += normalesCaras[contador].x;
        normalesVertices[caras_ply[i]].y += normalesCaras[contador].y;
        normalesVertices[caras_ply[i]].z += normalesCaras[contador].z;

        normalesVertices[caras_ply[i+1]].x += normalesCaras[contador].x;
        normalesVertices[caras_ply[i+1]].y += normalesCaras[contador].y;
        normalesVertices[caras_ply[i+1]].z += normalesCaras[contador].z;

        normalesVertices[caras_ply[i+2]].x += normalesCaras[contador].x;
        normalesVertices[caras_ply[i+2]].y += normalesCaras[contador].y;
        normalesVertices[caras_ply[i+2]].z += normalesCaras[contador].z;                 
          
        contador++;   
      }

      //Normalizamos el vector
      for (int i = 0; i < normalesVertices.size(); i++){

        float modulo = sqrt(pow(normalesVertices[i].x, 2) + pow(normalesVertices[i].y, 2) + pow(normalesVertices[i].z, 2));

        if (modulo > 0){
          normalesVertices[i].x = normalesVertices[i].x / modulo; 
          normalesVertices[i].y = normalesVertices[i].y / modulo; 
          normalesVertices[i].z = normalesVertices[i].z / modulo; 
        }
      } 
    }
    
    //draw para dibujar normales de caras
    void draw(){

      glShadeModel(GL_FLAT);
      glBegin(GL_TRIANGLES);{
        
        int contador = 0;
        for (int i = 0; i < caras_ply.size(); i+=3){
          
          glNormal3f(normalesCaras[contador].x,
                     normalesCaras[contador].y, 
                     normalesCaras[contador].z);

          glVertex3f(vertices[caras_ply[i]].x,
                     vertices[caras_ply[i]].y,
                     vertices[caras_ply[i]].z);

          glVertex3f(vertices[caras_ply[i+1]].x,
                     vertices[caras_ply[i+1]].y,
                     vertices[caras_ply[i+1]].z);

          glVertex3f(vertices[caras_ply[i+2]].x,
                     vertices[caras_ply[i+2]].y,
                     vertices[caras_ply[i+2]].z);
          contador++;
        }
      }
      glEnd();
    }

    //draw para dibujar normales de vértices
    void drawVertices(){

      glShadeModel(GL_SMOOTH);
      glBegin(GL_TRIANGLES);{

        int contador = 0;
        for (int i = 0; i < caras_ply.size(); i+=3){
          
          glNormal3f(normalesVertices[caras_ply[i]].x,
                     normalesVertices[caras_ply[i]].y,
                     normalesVertices[caras_ply[i]].z);
          glVertex3f(vertices[caras_ply[i]].x,
                     vertices[caras_ply[i]].y,
                     vertices[caras_ply[i]].z);
        
          glNormal3f(normalesVertices[caras_ply[i+1]].x,
                     normalesVertices[caras_ply[i+1]].y,
                     normalesVertices[caras_ply[i+1]].z);
          glVertex3f(vertices[caras_ply[i+1]].x,
                     vertices[caras_ply[i+1]].y,
                     vertices[caras_ply[i+1]].z);
        
          glNormal3f(normalesVertices[caras_ply[i+2]].x,
                     normalesVertices[caras_ply[i+2]].y,
                     normalesVertices[caras_ply[i+2]].z);
          glVertex3f(vertices[caras_ply[i+2]].x,
                     vertices[caras_ply[i+2]].y,
                     vertices[caras_ply[i+2]].z);
          
          contador+=3;
        }
      }
      glEnd();
    }
};


class MallaRevolucion : public MallaTriangulo{ //HEREDA A MALLA TRIÁNGULO

    int m; //size de los vértices sacados del perfil.

    public:
    MallaRevolucion(const char *nombre_archivo, int n){ //n>3
      
      ply::read_vertices(nombre_archivo, vertices_ply);
      
      CoordenadasV vert;
      for(int i = 0; i < vertices_ply.size(); i+=3){
        vert.x = vertices_ply[i]*3;
        vert.y = vertices_ply[i+1]*3;
        vert.z = vertices_ply[i+2]*3;
        vertices.push_back(vert);
      }

      //Creo lista de vertices
      m = vertices.size();
      float angulo;
      CoordenadasV v;

      for (int i=0; i<=n-1; i++){
        for (int j=0; j<=m-1; j++){
          angulo = 2*i* M_PI / (n-1);
          v.x = vertices[j].x * cos(angulo);
          v.y = vertices[j].y;
          v.z = vertices[j].x * sin(angulo);
          vertices.push_back(v);
        }
      }

      //Creo lista de caras_ply
      int k;
      caras_ply.clear();
      for (int i=0; i<=n-1; i++){
        for(int j=0; j<= m-2; j++){
          k = i*m + j;
          caras_ply.push_back(k);
          caras_ply.push_back(k+m+1);
          caras_ply.push_back(k+m);

          caras_ply.push_back(k);
          caras_ply.push_back(k+1);
          caras_ply.push_back(k+m+1);
        }
      }

      //Calculo normales cara
      for (int i = 0; i < caras_ply.size(); i+=3){
        CoordenadasV vert;
        vert = normalCara(vertices[caras_ply[i]],
                          vertices[caras_ply[i+1]],
                          vertices[caras_ply[i+2]]);
        
        normalesCaras.push_back(vert);//SE HEREDA LA FUNCIÓN DE LA CLASE MALLA TRIÁNGULO
      }    
    }
};

Ejes ejesCoordenadasV;

/* INSTANCIAS PRÁCTICA 1
//Creo los objetos de cada figura con sus correspondientes dimensiones.
Cubo cubo(4);
Piramide piramide(4,7);
Tetraedro tetraedro(5,7);
PrismaRectangular prisma(4,7);
*/

//INSTANCIAS PRÁCTICA 2
MallaTriangulo figuraSmooth("plys/beethoven.ply");
MallaTriangulo figuraFlat("plys/big_dodge.ply");
MallaRevolucion objetoR("plys/perfil.ply", 12);


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
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el z-Buffer
  transformacionVisualizacion ();	// Carga transformacion de visualizacion
  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena
  ejesCoordenadasV.draw();			// Dibuja los ejes
  
  //Cubo
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  glPointSize(17.0);
  /*
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
  */

  glPointSize(2.0); //para que se vean más claramente los puntos de cada figura en el modo puntos

  ////Características de la figura de Revolución
  float colorRevolucion[4] = {0.8, 0.0, 1, 1};
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
  objetoR.draw();
  
  //Características de la figura con normales de vértice y GL_SMOOTH
  float colorSmooth[4] = {0.0, 1, 0.0, 0.0};
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorSmooth);
  glTranslatef(-9,0,0);
  figuraSmooth.drawVertices();
  
  //Características de la figura con normales de cara y GL_FLAT
  float colorFlat[4] = {1, 0.0, 0.0, 0.0};
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorFlat);
  glTranslatef(21,0,0);
  figuraFlat.draw();
  
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
