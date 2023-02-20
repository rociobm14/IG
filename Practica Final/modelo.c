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
#include "estructura.h"
#include "lector-jpg.h" 


/**	void initModel()

Inicializa el modelo y de las variables globales


**/
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

//**********************************************************************************/
/******************************PRÁCTICA 1*******************************************/
/***********************************************************************************/

//Clase para dibujar un cubo
class Cubo:Objeto3D{
  
  private:
    float lado;
 
  public:
    Cubo(float lado){
      this -> lado = lado;
    }

    void draw(){
     glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, texId);
      glBegin(GL_QUADS);{
         //Vertical delantera
        glNormal3f( 0.0, 0.0, 1.0 );
        glTexCoord2f(0.75,1);
        glVertex3f( lado, lado, lado );
        glTexCoord2f(0.5,1);
        glVertex3f( 0, lado, lado );
        glTexCoord2f(0.5,0.75);
        glVertex3f( 0, 0, lado );
        glTexCoord2f(0.75,0.75);
        glVertex3f(lado, 0, lado);

        //Tapa arriba
        glNormal3f( 0.0, 1.0, 0.0 );
        glTexCoord2f(0, 0.5);
        glVertex3f(lado, lado, 0);
        glTexCoord2f(0.25, 0.5);
        glVertex3f(0, lado, 0);
        glTexCoord2f(0.25, 0.75);
        glVertex3f(0, lado, lado);
        glTexCoord2f(0, 0.75);
        glVertex3f(lado, lado, lado);

        //Tapa abajo
        glNormal3f( 0.0, -1.0, 0.0 );
        glTexCoord2f(0.75, 0.75);
        glVertex3f(lado, 0, lado);
        glTexCoord2f(0.5, 0.75);
        glVertex3f(0, 0, lado);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0.75, 0.5);
        glVertex3f(lado, 0, 0);

        //Vertical trasera
        glNormal3f( 0.0, 0.0, -1.0 );
        glTexCoord2f(0.5, 0.25);
        glVertex3f(0, lado, 0);
        glTexCoord2f(0.75, 0.25);
        glVertex3f(lado, lado, 0);
        glTexCoord2f(0.75, 0.5);
        glVertex3f(lado, 0, 0);
        glTexCoord2f(0.5, 0.5);
        glVertex3f(0, 0, 0);
        
        //Costado izquierdo
        glNormal3f( -1.0, 0.0, 0.0 );
        glTexCoord2f(0.5,0.5);
        glVertex3f(0, lado, lado);
        glTexCoord2f(0.25, 0.5);
        glVertex3f(0, lado, 0);
        glTexCoord2f(0.25, 0.75);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0.5,0.75);
        glVertex3f(0, 0, lado);

        //Costado derecho
        glNormal3f( 1.0, 0.0, 0.0 );
        glTexCoord2f(1, 0.5);
        glVertex3f(lado, lado, 0);
        glTexCoord2f(1, 0.75);
        glVertex3f(lado, lado, lado);
        glTexCoord2f(0.75, 0.75);
        glVertex3f(lado, 0, lado);
        glTexCoord2f(0.75, 0.5);
        glVertex3f(lado, 0, 0);
      }
      glEnd();

      glDisable(GL_TEXTURE_2D);
      glEnable(GL_LIGHTING);
    }

    void cargaTextura(){
      glGenTextures(1, &texId);
      glBindTexture(GL_TEXTURE_2D, texId);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                  Textura("P4/dado.jpg"));
    }
};


//Clase para dibujar una pirámide
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
 
//INSTANCIAS PRÁCTICA 1
//Creo los objetos de cada figura con sus correspondientes dimensiones.
Cubo cubo(4);
Piramide piramide(4,7);
Tetraedro tetraedro(5,7);
PrismaRectangular prisma(4,7);


//inicializo en modo de representación de figuras rellenas
int modo = GL_FILL;

//función que cambia el relleno de las figuras a modo puntos, aristas o rellenas.
void setModo(int M){
  modo = M;
  glPolygonMode(GL_FRONT_AND_BACK, modo);
}

bool iluminacion;

//Función que modifica la iluminación de las figuras
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





//**********************************************************************************/
/******************************PRÁCTICA 2 y 4*******************************************/
/***********************************************************************************/

class MallaTriangulo : public Objeto3D{
 public:

    struct CoordenadasV{
      float x;
      float y;
      float z;
    };

    struct CoordenadasTex{
      float u;
      float v;
    };

    std::vector <float> vertices_ply; //lee los vértices del archivo
    std::vector <int> caras_ply; //lee las caras del archivo
    std::vector <CoordenadasV> vertices; //guarda los vértices leídos
    std::vector <CoordenadasV> carasTriang; //guarda las caras leídas
    std::vector <CoordenadasV> normalesVertices; //guarda las normales de cada vértice
    std::vector <CoordenadasV> normalesCaras; //guarda las normales de cada cara (formada cada una por 3 vertices)

    //para calcular la textura de la práctica 4
    bool hayTextura = false;
    std::vector <CoordenadasTex> uv; //guarda las coordenadas uv para la textura
    
    //Constructor por defecto para que la clase de Revolución pueda
    //heredar mallaTriangulo
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

       CoordenadasV caraAux;
      for(int i = 0; i < caras_ply.size(); i+=3){
        caraAux.x = caras_ply.at(i);
        caraAux.y = caras_ply.at(i+1);
        caraAux.z = caras_ply.at(i+2);
        carasTriang.push_back(caraAux);
      }

      CoordenadasV v;
      for (int i = 0; i < carasTriang.size(); i++){
        v = normalCara(vertices[carasTriang[i].x],
                       vertices[carasTriang[i].y],
                       vertices[carasTriang[i].z]);
        
        normalesCaras.push_back(v);
      }

      normalVertice();   
    }

    //Función que calcula la normal de una cara dados los 3 vértices de esa cara.
    CoordenadasV normalCara(CoordenadasV p0, CoordenadasV p1, CoordenadasV p2){
      
      CoordenadasV A,B,N;
      float modulo;

      A.x = p1.x - p0.x;
      A.y = p1.y - p0.y;
      A.z = p1.z - p0.z;

      B.x = p2.x - p0.x;
      B.y = p2.y - p0.y;
      B.z = p2.z - p0.z;


      N.x = A.y*B.z-A.z*B.y; 
      N.y = A.z*B.x-A.x*B.z; 
      N.z = A.x*B.y-A.y*B.x; 

      modulo = sqrt(pow(N.x, 2) + pow(N.y, 2) + pow(N.z, 2));

      if (modulo > 0){
        N.x = N.x/modulo; 
        N.y = N.y/modulo; 
        N.z = N.z/modulo; 
      }

      return N;
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
      for (int i = 0; i < carasTriang.size(); i++){

        normalesVertices[carasTriang[i].x].x += normalesCaras[i].x;
        normalesVertices[carasTriang[i].y].y += normalesCaras[i].y;
        normalesVertices[carasTriang[i].z].z += normalesCaras[i].z;

        normalesVertices[carasTriang[i+1].x].x += normalesCaras[i].x;
        normalesVertices[carasTriang[i+1].y].y += normalesCaras[i].y;
        normalesVertices[carasTriang[i+1].z].z += normalesCaras[i].z;

        normalesVertices[carasTriang[i+2].x].x += normalesCaras[i].x;
        normalesVertices[carasTriang[i+2].y].y += normalesCaras[i].y;
        normalesVertices[carasTriang[i+2].z].z += normalesCaras[i].z;                 
             
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
      
      //Si no hay textura
      if(!hayTextura){
        glShadeModel(GL_FLAT);
        glBegin(GL_TRIANGLES);{
        
        for (int i = 0; i < carasTriang.size(); i++){
          
          glNormal3f(normalesCaras[i].x,
                     normalesCaras[i].y, 
                     normalesCaras[i].z);

          glVertex3f(vertices[carasTriang[i].x].x,
                     vertices[carasTriang[i].x].y,
                     vertices[carasTriang[i].x].z);

          glVertex3f(vertices[carasTriang[i].y].x,
                     vertices[carasTriang[i].y].y,
                     vertices[carasTriang[i].y].z);

          glVertex3f(vertices[carasTriang[i].z].x,
                     vertices[carasTriang[i].z].y,
                     vertices[carasTriang[i].z].z);
        }
      }
      glEnd();

      }

      //Si hay textura
      else{
        glShadeModel(GL_FLAT);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texId);
        glBegin(GL_TRIANGLES);{
        
          for (int i = 0; i < carasTriang.size(); i++){
            
            glNormal3f(normalesCaras[i].x,
                      normalesCaras[i].y, 
                      normalesCaras[i].z);
            
            //del primer vertice de la cara i, saca su coordenada u y su coordenada v
            glTexCoord2f(uv[carasTriang[i].x].u, uv[carasTriang[i].x].v);
            glVertex3f(vertices[carasTriang[i].x].x,
                      vertices[carasTriang[i].x].y,
                      vertices[carasTriang[i].x].z);
            
            //del segundo vértice de la cara i, saca su coordenada u y su coordenada v
            glTexCoord2f(uv[carasTriang[i].y].u, uv[carasTriang[i].y].v);
            glVertex3f(vertices[carasTriang[i].y].x,
                      vertices[carasTriang[i].y].y,
                      vertices[carasTriang[i].y].z);

            //del tercer vértice de la cara i, saca su coordenada u y su coordenada v
            glTexCoord2f(uv[carasTriang[i].z].u, uv[carasTriang[i].z].v);
            glVertex3f(vertices[carasTriang[i].z].x,
                      vertices[carasTriang[i].z].y,
                      vertices[carasTriang[i].z].z);
          }
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);
      }
    }

    //draw para dibujar normales de vértices
    void drawVertices(){

      glShadeModel(GL_SMOOTH);
      glBegin(GL_TRIANGLES);{

        for (int i = 0; i < carasTriang.size(); i++){
          
          glNormal3f(normalesVertices[carasTriang[i].x].x,
                     normalesVertices[carasTriang[i].x].y,
                     normalesVertices[carasTriang[i].x].z);
          glVertex3f(vertices[carasTriang[i].x].x,
                     vertices[carasTriang[i].x].y,
                     vertices[carasTriang[i].x].z);
        
          glNormal3f(normalesVertices[carasTriang[i].y].x,
                     normalesVertices[carasTriang[i].y].y,
                     normalesVertices[carasTriang[i].y].z);
          glVertex3f(vertices[carasTriang[i].y].x,
                     vertices[carasTriang[i].y].y,
                     vertices[carasTriang[i].y].z);
        
          glNormal3f(normalesVertices[carasTriang[i].z].x,
                     normalesVertices[carasTriang[i].z].y,
                     normalesVertices[carasTriang[i].z].z);
          glVertex3f(vertices[carasTriang[i].z].x,
                     vertices[carasTriang[i].z].y,
                     vertices[carasTriang[i].z].z);
        }
      }
      glEnd();
    }
};


class MallaRevolucion : public MallaTriangulo{ //HEREDA A MALLA TRIÁNGULO

    int m; //size de los vértices sacados del perfil.
    int n; //numero de perfiles
    std::vector <float> distancias;
    float distancia_total;
    bool tapa, base;

    public:
    MallaRevolucion(const char *nombre_archivo, int n, bool tapa, bool base){ //n>3
      hayTextura = false;
      this->tapa = tapa;
      this->base = base;
      ply::read_vertices(nombre_archivo, vertices_ply);
      this->n = n;
      m = vertices_ply.size()/3;
      distancia_total = 0;
      distancias.push_back(0);
      for (int i=3; i<vertices_ply.size(); i+=3){
        float aux = sqrt(pow((vertices_ply[i+1] - vertices_ply[i-2]), 2) + 
                        pow((vertices_ply[i] - vertices_ply[i-3]), 2));
        distancia_total += aux;
        distancias.push_back(distancia_total);
      }

      //para las tapas
      float radio = 0;
      for (int i=0; i<vertices_ply.size(); i+=3){
        if(radio<vertices_ply[i]){
          radio = vertices_ply[i];
        }
      }
      
      CoordenadasV vert;
      for(int i = 0; i < vertices_ply.size(); i+=3){
        vert.x = vertices_ply[i];
        vert.y = vertices_ply[i+1];
        vert.z = vertices_ply[i+2];
        vertices.push_back(vert);

        //Calcula el vector uv según si es tapa, base o cuerpo de la lata.
        CoordenadasTex p;
        if(tapa){
          p.u = ((vertices_ply[i]+radio)/(2*radio))/2;
          p.v = (vertices_ply[i+2]+radio)/(2*radio);
        }

        else if(base){
          p.u = (((vertices_ply[i] + radio) /(2*radio)) / 2) + 0.5;
          p.v = (vertices_ply[i+2] + radio) /(2*radio);
        }

        else{
          p.u = 0;
          p.v = distancias[i/3] / distancia_total;

        }
      
        uv.push_back(p);
      }

      //Creo lista de vertices
      int tam= vertices.size();
      float angulo;
      CoordenadasV v;

      for (int i=0; i<=n; i++){
        angulo = (2*i* M_PI) / (n-1);
        for (int j=0; j<tam; j++){
          
          v.x = vertices[j].x * cos(angulo);
          v.y = vertices[j].y;
          v.z = vertices[j].x * sin(angulo);
          vertices.push_back(v);

          CoordenadasTex p;
          if(tapa){
             p.u=(((vertices[j].x*cos(angulo))+radio)/(2*radio))/2;
             p.v=(((vertices[j].x*sin(angulo)))+radio)/(2*radio);

          }

          else if(base){
            p.u=((((vertices[j].x*cos(angulo))+radio)/(2*radio))/2)+0.5;
            p.v=(((vertices[j].x*sin(angulo))+radio)/(2*radio));

          }

          else{
            p.u = ((angulo*180)/M_PI) / 360;
            p.v = uv[j].v;
          }
          
          uv.push_back(p);
        }
      }

      //Creo lista de caras_ply
      int k;
      for (int i=0; i<n; i++){
        for(int j=0; j<m-1; j++){
          k = i*m + j;
          caras_ply.push_back(k);
          caras_ply.push_back(k+m+1);
          caras_ply.push_back(k+m);

          caras_ply.push_back(k);
          caras_ply.push_back(k+1);
          caras_ply.push_back(k+m+1);
        }
      }

      CoordenadasV caraAux;
      for(int i = 0; i < caras_ply.size(); i+=3){
        caraAux.x = caras_ply.at(i);
        caraAux.y = caras_ply.at(i+1);
        caraAux.z = caras_ply.at(i+2);
        carasTriang.push_back(caraAux);
      }


      //Calculo normales cara
      for (int i = 0; i < carasTriang.size(); i++){
        CoordenadasV vert;
        vert = normalCara(vertices[carasTriang[i].x],
                          vertices[carasTriang[i].y],
                          vertices[carasTriang[i].z]);
        
        normalesCaras.push_back(vert);//SE HEREDA LA FUNCIÓN DE LA CLASE MALLA TRIÁNGULO
      }

    }
   
     
     void cargaTexturaRev(const char *nombre){
      unsigned char *imagen = Textura(nombre);
      hayTextura = true;
      glGenTextures(1, &texId);
      glBindTexture(GL_TEXTURE_2D, texId);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, 
                  imagen);
    }

};


Ejes ejesCoordenadasV;


//INSTANCIAS PRÁCTICA 2
MallaTriangulo figuraSmooth("plys_1/plys/beethoven.ply");
MallaTriangulo figuraFlat("plys_1/plys/big_dodge.ply");
MallaRevolucion objetoR("plys_1/plys/perfil.ply", 12, false, false);

//INSTANCIAS PRÁCTICA 4
Cubo dado(4);
MallaRevolucion lata1("P4/lata-pinf.ply", 12,false,true);
MallaRevolucion lata2("P4/lata-pcue.ply", 12,false,false);
MallaRevolucion lata3("P4/lata-psup.ply", 12,true, false);
MallaTriangulo beethoven("plys_1/plys/beethoven.ply");

//Función que dibuja los materiales pedidos
void Materiales(float *ambient, float *specular, float *diffuse, float shine){

  struct Material{
  float specular[4];
  float diffuse[4];
  float ambient[4];
  float brillo;
  };

  
  Material material;
  for (int i=0; i<4; i++){
    material.ambient[i] = ambient[i];
  }

for (int i=0; i<4; i++){
  material.diffuse[i] = diffuse[i];
}

for (int i=0; i<4; i++){
  material.specular[i] = specular[i];
}

material.brillo = shine;
glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
glMaterialf(GL_FRONT, GL_SHININESS, material.brillo);
  
}

//Primera fuente de luz
bool iluminacion1;

void Iluminacion1(){
  if (iluminacion1==1){
    iluminacion1 = 0;;
    glDisable (GL_LIGHT1);
  }

  else{
    iluminacion1 = 1;
    glEnable (GL_LIGHT1);
  }
}

//Segunda fuente de luz
bool iluminacion2;

void Iluminacion2(){
  if (iluminacion2==1){
    iluminacion2 = 0;;
    glDisable (GL_LIGHT2);
  }

  else{
    iluminacion2 = 1;
    glEnable (GL_LIGHT2);
  }
}


//**********************************************************************************/
/******************************PRÁCTICA 3******************************************/
/***********************************************************************************/


//FUNCIONES Y VARIABLES P3
int giro_total = 0;
int giro_brazo = 0;
int altura = 15;
bool animacion;
int contadorGrua = 1;
int contadorBrazo = 1;
int contadorGancho = 1;

void giroTotalIzquierda(){
  giro_total+=1;
  if(giro_total > 360)
    giro_total -= 360;
}

void giroTotalDerecha(){
  giro_total-=1;
  if(giro_total < 0){
    giro_total += 360;
  }
}

void giroBrazoIzquierda(){
  giro_brazo+=1;
  if(giro_brazo > 360)
    giro_brazo -= 360;
}

void giroBrazoDerecha(){
  giro_brazo-=1;
  if(giro_brazo < 0)
    giro_brazo += 360;
}

void bajaGancho(){
    altura-=1;
    if(altura < 0)
      altura = 0;
}

void subeGancho(){
  altura+=1;
  if(altura > 15)
    altura = 15;
}

int limite = 15;
void bajaSubeGancho(){
  if(limite == 15){
    altura -= 1;
    if(altura == 0)
      limite = 0;
  }

  else if(limite == 0){
    altura+=1;
    if(altura == 15)
      limite = 15;
  }

}

void Animacion(){
  if(animacion == 1)
    animacion = 0;
    
  else
    animacion = 1;
}

void gruaRapida(){
  contadorGrua++;
}

void gruaLenta(){
  contadorGrua--;
  if(contadorGrua < 0)
    contadorGrua = 0;
}

void brazoRapido(){
  contadorBrazo++;
}

void brazoLento(){
  contadorBrazo--;
  if (contadorBrazo < 0)
    contadorBrazo = 0;
}

void ganchoRapido(){
  contadorGancho++;
}

void ganchoLento(){
  contadorGancho--;
  if(contadorGancho < 0)
    contadorGancho = 0;
}




bool cambiado = false;

void setCambio(){
  cambiado = true;
}


void initModel()
{
  dado.cargaTextura();
  lata1.cargaTexturaRev("P4/tapas.jpg");
  lata2.cargaTexturaRev("P4/lata.jpg");
  lata3.cargaTexturaRev("P4/tapas.jpg");
}



/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.
--
**/

//FUNCIONES PARA CAMBIAR DE PRÁCTICA
int practica = 1;

void practica1(){
  practica = 1;
}

void practica2(){
  practica = 2;
}

void practica3(){
  practica = 3;
}

void practica4(){
  practica = 4;
}

void practica5(){
  practica = 5;
}

//colores para las figuras
float amarillo[4] = {1, 1, 0.0, 0.0};
float rojo[4] = {1, 0.0, 0.0, 0.0};
float gris[4] = {0.5, 0.5, 0.5};
float morado[4] = {0.8, 0.0, 1, 1}; //Color cubo
float turquesa[4] = {0.0, 1, 1, 0.0}; //Cubo Pirámide
float blanco[4] = {1, 1, 1, 0.0};
float verde[4] = {0.0, 1, 0.0, 0.0};


void dibujaP1(){
  //Cubo
  glPointSize(17.0);
  
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, morado);
  cubo.draw();
  
  //Pirámide
  glTranslatef(5,0,0);
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, turquesa);
  piramide.draw();

  //Tetraedro
  glTranslatef(5,0,0);
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);
  tetraedro.draw();
  
  //Prisma Rectangular
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blanco);
  glTranslatef(6,0,0);
  prisma.draw();

}

void dibujaP2(){
  glPointSize(2.0); //para que se vean más claramente los puntos de cada figura en el modo puntos

  ////Características de la figura de Revolución
  glPushMatrix();
  glScaled(3,3,3);
  glEnable(GL_NORMALIZE);
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, morado);
  objetoR.draw();
  glPopMatrix();
  
  //Características de la figura con normales de vértice y GL_SMOOTH
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, verde);
  glTranslatef(-9,0,0);
  figuraSmooth.drawVertices();
  
  //Características de la figura con normales de cara y GL_FLAT
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
  glTranslatef(21,0,0);
  figuraFlat.draw();

}

void dibujaP3(){


  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);
  //CREO LA TORRE GENERAL
  glRotatef(giro_total, 0, 1, 0);
  creaEstructura(0, 0, 0, 0, 15, 0, 1, 1, 15);
  
  //CREO EL BRAZO
  glRotatef(giro_brazo, 0, 1, 0);
  glTranslatef(-10.5,15,0);
  glPushMatrix();
  creaBrazo(0, 0, 0, 10, 0, 0, 1, 10);
  glTranslatef(10, 0, -0.5);
  Cubo cubo(1);
  cubo.draw();

  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rojo);
  //CREO EL OTRO BRAZO
  glTranslatef(0.5,1, 0.5);
  creaTorre(0, 0, 0, 0, 5, 0, 1, 1, 7);
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amarillo);
  glTranslatef(0.5, -0.5, 0);
  creaEstructura(0, 0, 0, 7, 0, 0, 1, 1, 7);
  glTranslatef(5.8, -1.5, 0);
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gris);
  caja(2.5, 1, 1);
  glPopMatrix();

  //CREO EL GANCHO
  glTranslatef(1, -15, 0);
  glPushMatrix();
  glTranslatef(0, altura, 0);
  creaGancho(0, 0, 0, 1);
  cilindro(0, 0, 0, 0, 15-altura, 0, 0.05);
  glPopMatrix();

}

void dibujaP4(){
  float bronze_ambient[4] ={ 0.2125f, 0.1275f, 0.054f, 1.0f };
  float bronze_diffuse[4]={ 0.714f, 0.4284f, 0.18144f, 1.0f };
  float bronze_specular[4] ={ 0.393548f, 0.271906f, 0.166721f, 1.0f };
  float bronze_shine = 25.6f;

  float turquoise_ambient[4] = { 0.1f, 0.18725f, 0.1745f, 0.8f };
  float turquoise_diffuse[4] = {0.396f, 0.74151f, 0.69102f, 0.8f };
  float turquoise_specular[4] ={0.297254f, 0.30829f, 0.306678f, 0.8f };
  float turquoise_shine = 12.8f;

  float ruby_ambient[4] ={ 0.1745f, 0.01175f, 0.01175f, 0.55f };
  float ruby_diffuse[4] ={0.61424f, 0.04136f, 0.04136f, 0.55f };
  float ruby_specular[4] ={0.727811f, 0.626959f, 0.626959f, 0.55f };
  float ruby_shine =76.8f ;

  static GLfloat morado[3] = {1.0, 0.0, 1.0};
  static GLfloat pos1[4] = {0.0, 20.0, 40.0, 1.0};
  static GLfloat verde[3] = {0.0, 1.0, 0.0};
  static GLfloat pos2[4] = {20.0, 0.0, 1.0, 40.0};

  glLightfv(GL_LIGHT1, GL_POSITION, pos1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, morado);

  glLightfv(GL_LIGHT2, GL_POSITION, pos2);
  glLightfv(GL_LIGHT2, GL_AMBIENT, verde);

  glPushMatrix();
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blanco);
  glScaled(4,4,4);
  glEnable(GL_NORMALIZE);
  glRotatef(180,0,1,0);
  lata1.draw();
  lata2.draw();
  lata3.draw();
  glPopMatrix();


  glTranslatef(-8,0,0);
  dado.draw();
  
  
  
  glPushAttrib(GL_LIGHTING);
  glTranslatef(12, 0, 0);
  Materiales(bronze_ambient, bronze_specular, bronze_diffuse, bronze_shine);
  beethoven.draw();
  glPopAttrib();
  
  glPushAttrib(GL_LIGHTING);
  glTranslatef(12, 0, 0);
  Materiales(turquoise_ambient, turquoise_diffuse, turquoise_specular, turquoise_shine);
  beethoven.draw();
  glPopAttrib();
  
  glPushAttrib(GL_LIGHTING);
  glTranslatef(12, 0, 0);
  Materiales(ruby_ambient, ruby_diffuse, ruby_specular, ruby_shine);
  beethoven.draw();
  glPopAttrib();

}

void dibujaP5(){
  dibujaP4();
  glTranslatef(12,0,0);

  glPushMatrix();
  glScaled(3,3,3);
  glEnable(GL_NORMALIZE);
  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, morado);
  objetoR.draw();
  glPopMatrix();

  glTranslatef(-30,0,0);
  dibujaP3();

}


void Dibuja (void)
{
 static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz
  
  
  glPushMatrix ();		// Apila la transformacion geometrica actual
  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el z-Buffer
  transformacionVisualizacion ();	// Carga transformacion de visualizacion
  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena
  ejesCoordenadasV.draw();			// Dibuja los ejes

  switch(practica){
    
    case 1:
      dibujaP1();
      break;
    
    case 2:
      dibujaP2();
      break;
    
    case 3:
      dibujaP3();
      break;
    
    case 4:
      dibujaP4();
      break;

    case 5:

      if(cambiado){
        cambiado =false;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        fijaProyeccion();
      }
      dibujaP5();
      break;

  }
  
  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)          
  glPopMatrix ();		// Desapila la transformacion geometrica
  glutSwapBuffers ();
}



/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{
  if(animacion == 1){
    for (int i=0; i<contadorGrua; i++)
      giroTotalIzquierda();

    for (int i=0; i<contadorBrazo; i++)
      giroBrazoIzquierda();

    for (int i=0; i<contadorGancho; i++)
      bajaSubeGancho();
  }


  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}





