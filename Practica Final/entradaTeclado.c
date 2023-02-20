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
modulo entradaTeclado.c
	Gestion de eventos de teclado
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"


/** 

Imprime en la consola las instrucciones del programa

**/
void printHelp ()
{

  printf ("\n\n     Prácticas de Informática Gráfica	Curso 2022-2023");
  printf ("\n\n Dpto. Lenguajes y Sistemas Informaticos");
  printf ("\n E.T.S.I. Informatica		Univ. de Granada ");
  printf ("\n");
  printf ("\n Opciones: \n\n");
  printf ("h, H: Imprime informacion de ayuda \n");
  printf ("PgUp, PgDn: avanza y retrocede la cámara \n\n");
  printf ("+,-: avanza y retrocede la cámara \n\n");
  printf ("Teclas de movimiento de cursor: giran la camara\n");
  // Anyade la informacion de las opciones que introduzcas aqui !!       

  printf ("\n Escape: Salir");
  printf ("\n\n\n");
}




/* @teclado ---------------------------------------------------------------- */

/** 		void letra (unsigned char k, int x, int y)

Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
El codigo k es el ascii de la letra

Para anyadir nuevas ordenes de teclado coloca el correspondiente case.

Parametros de entrada:

k: codigo del caracter pulsado

x:

y:

**/

//float rotxCamara = 30, rotyCamara = 45;
//float dCamara = 10;

float rotxCamara = 0;
float rotyCamara = 0;
float cx = 0, cy = 0, cz = 25;

bool orto = false;
bool cambio = false;

void setPosCamara(float rx, float ry){
  rotxCamara = rx;
  rotyCamara = ry;
}


void letra (unsigned char k, int x, int y)
{

  switch (k)
    {
    case 'h':
    case 'H':
      printHelp ();		// H y h imprimen ayuda
      break;

    case '+':			// acerca la cámara
      cz -= 5.0;
      break;

    case '-':			// aleja la cámara
      cz += 5.0;
      break;
      
    case 'p':
    case 'P': // representa las figuras según sus vértices
      setModo(GL_POINT);
      break;
   
    case 'r': 
    case 'R': // representa las figuras según sus aristas
      setModo(GL_LINE);
      break;
    
    case 'f':
    case 'F': // representa las figuras rellenas
      setModo(GL_FILL);
      break;
    
    case 'i':
    case 'I': // activa o desactiva la iluminación
      modificaIluminacion();
      break;
    
    case 'C': //Gira la grúa al completo hacia la izquierda
      giroTotalIzquierda();
      break;
    case 'c': //Gira la grúa al completo hacia la derecha
      giroTotalDerecha();
      break;
    
    case 'B': 
      giroBrazoIzquierda(); //Gira el brazo hacia la izquierda
      break;
    case 'b':
      giroBrazoDerecha(); //Gira el brazo hacia la derecha
      break;
    
    case 'M':
      bajaGancho(); //Baja el gancho
      break;
    case 'm':
      subeGancho(); //Sube el gancho
      break;
    
    case 'x':
    case 'X': //Anima la figura
      Animacion();
      break;

    case 'G': //La grúa gira al completo más rápido
      gruaRapida();
      break;
    case 'g': //La grúa gira al completo más lento
      gruaLenta();
      break;

    case 'K': //El brazo gira más rápido
      brazoRapido();
      break;
    case 'k': //El brazo gira más lento
      brazoLento();
      break;

    case 'L': //El gancho sube y baja más rápido
      ganchoRapido();
      break;
    case 'l': //El gancho sube y baja más lento
      ganchoLento();
      break;
    
    case '1':
      practica1(); //Dibuja la práctica 1
      break;

    case '2':
      practica2(); //Dibuja la práctica 2
      break;

    case '3':
      practica3(); //Dibuja la práctica 3
      break;

    case '4':
      practica4(); //Dibuja la práctica 4
      break;

    case '5':
      practica5(); //Dibuja la práctica 5
      break;

    case '9':
      Iluminacion1(); //Activa o desactiva la primera luz
      break;

    case '0':
      Iluminacion2(); //Activa o desactiva la segunda luz
      break;

    case 'w': //Aleja la cámara poco a poco
    case 'W':
      cz -= 0.5;
      break;

    case 'A': //Mueve la cámara a la izquierda poco a poco
    case 'a':
      cx += 0.5;
      break;

    case 's': //Acerca la cámara poco a poco
    case 'S':
      cz += 0.5;
      break;

    case 'd': //Mueve la cámara a la derecha poco a poco
    case 'D':
      cx -= 0.5;
      break;
 
    case 27:			// Escape  Terminar
      exit (0);
    default:
      return;
    }
  setCamara (rotxCamara, rotyCamara, cx, cz, orto);
  glutPostRedisplay ();		// Algunas de las opciones cambian paramentros
}				// de la camara. Es necesario actualziar la imagen

/**		void especial(int k, int x, int y)s
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes

Parametros de entrada:

k: codigo del caracter pulsado (definido en glut mediante constantes).

x:

y:

**/
void especial (int k, int x, int y)
{

  switch (k)
    {
    case GLUT_KEY_UP:
      rotxCamara += 5.0;	// Cursor arriba + rotacion x
      if (rotxCamara > 360)
	rotxCamara -= 360;
      break;
    case GLUT_KEY_DOWN:
      rotxCamara -= 5.0;
      if (rotxCamara < 0)
	rotxCamara += 360;
      break;
    case GLUT_KEY_LEFT:
      rotyCamara += 5.0;
      if (rotyCamara > 360)
	rotyCamara -= 360;
      break;
    case GLUT_KEY_RIGHT:
      rotyCamara -= 5.0;
      if (rotyCamara < 0)
	rotyCamara += 360;
      break;
    case GLUT_KEY_PAGE_DOWN:	// acerca la cámara
      cz -= 5.0;
      break;
    case GLUT_KEY_PAGE_UP:	// aleja la cámara
      cz += 5.0;
      break;
    case GLUT_KEY_F1:
      rotxCamara = 90, rotyCamara = 0; //planta
      cx = 0; cz = 25;
      if (orto==true)
        cambio = true;
      orto = false;
      break;
    case GLUT_KEY_F2:
      rotxCamara = 0, rotyCamara = -90; //alzado
      cx = 0; cz = 25;
      if (orto == true)
        cambio = true;
      orto = false;
      break;
    case GLUT_KEY_F3:
      rotxCamara = 0, rotyCamara = 0; //perfil
      cx = 0; cz = 25;
      if (orto == false)
        cambio = true;
      orto = true;
      break;
    default:
      return;
    }
  setCamara (rotxCamara, rotyCamara, cx, cz, orto);
  if (cambio){
    cambio = false;
    setCambio();
  }
  glutPostRedisplay ();		// Actualiza la imagen (ver proc. letra)
}
