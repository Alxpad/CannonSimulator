#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include "clasesCannon.h"
#include "stdlib.h"
#include<memory>

/*
Aplicación que simula un cañón. El usuario puede cargar el cañón con varios tipos de munición. Debe de realizar varios ajustes para preparar
el disparo, y el cañón disparará en orden FIFO las distintas municiones.
*/
static std::unique_ptr<bool> p_running{ std::make_unique<bool>(true) }; //Booleano que mantiene el programa en funcionamiento

int main(){
	const shared_ptr<Cannon> cannon2 = make_shared<Cannon>(2);
	const shared_ptr<Cannon> cannon1 = make_shared<Cannon>(1);
	const shared_ptr<Cannon> cannon3 = make_shared<Cannon>(3);
	const shared_ptr<Cannon_list> CannonList = make_shared<Cannon_list>(cannon1, cannon2, cannon3); // Lista de sistemas de punteros a los distintos cañones

	Menu menu;

	while(*menu.p_running.get() == true) {

		cout << "Iniciando sistemas del MegaCannon";
		for (int8_t i = 0; i < 3; i++)
		{
			Sleep(200);
			cout << ".";
		}
		//cout << "Pulse tecla para continuar" << endl;
		cin.get();
		menu.Mostrar(*CannonList);
		
		
	}
	cout << "...Fin de programa..." << "(" << * p_running << ")" << endl;
	cout << "Variable global running | valor: " << *p_running << " | direccion: " << p_running << endl;
	cout << "Puntero p_running -> " << &menu.p_running << endl;

	exit(0);
}