 /*Prácticas de Informática Gráfica

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

=======================================================

	 modelo.h
*/

/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel ();

/**
 * 	Funcion que cambia el modo
 **/
void setModo(int M);

/**
 * 	Funcion que cambia la iluminacion
 **/
void modificaIluminacion();

/**
 * Gira grúa completa a la izquierda
 * 
 */
void giroTotalIzquierda();

/**
 * Gira grúa completa a la derecha
 * 
 */
void giroTotalDerecha();

/**
 * Gira el brazo a la izquierda
 * 
 */
void giroBrazoIzquierda();

/**
 * Gira brazo a la derecha
 * 
 */

void giroBrazoDerecha();


/**
 * Baja el gancho, solo hasta que llegue a la base de la grúa
 * 
 */
void bajaGancho();

/**
 * Sube el gancho, hasta la altura del brazo de la grúa
 * 
 */
void subeGancho();

/**
 * Sube y baja el gancho. Cuando baje y llegue a la base de la grúa, comienza a subir hasta la altura del brazo
 * 
 */
void bajaSubeGancho();

/**
 * Anima la figura al completo
 * 
 */
void Animacion();

/**
 * Aumenta la rapidez del giro de la grúa completa
 * 
 */
void gruaRapida();

/**
 * Disminuye la rapidez del giro de la grúa completa
 * 
 */
void gruaLenta();

/**
 * Aumenta la rapidez del giro del brazo de la grúa
 * 
 */
void brazoRapido();

/**
 * Disminuye la rapidez del giro del brazo de la grúa 
 * 
 */
void brazoLento();

/**
 * Aumenta la rapidez de subida y bajada del gancho
 * 
 */
void ganchoRapido();

/**
 * Aumenta la rapidez de subida y bajada del gancho
 * 
 */
void ganchoLento();



class Objeto3D 
{ 
public: 

virtual void draw( ) = 0; // Dibuja el objeto
} ; 

