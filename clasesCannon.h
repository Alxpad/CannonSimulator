#pragma once
using namespace std;
#include<memory>
#include<string>

enum TiposMunicion {
	LASER,
	EXPLOSIVA,
	GAUSS,
	SEGUIDORA,
	HUMO
};

class stats
{
public:
	int temp{ 20 }; //Temperatura del cañón
	float position{ 0 }; //Ángulo del cañón phi=0 -->0º
	bool ready{ false }; // Estado del cannon
	int nDisparos{ 0 }; // Munición en el cargador

	~stats() = default;
};


class Cannon
{
private:
	int cargadorMax{ 5 };
public:

	

	stats Statscannon;
	Cannon(int NID);
	int ID;
	int Ndisparos_realizados;
	bool debugMode;
	vector <TiposMunicion>cargador; ///CARGADOR POR DEFECTO EMPIEZA VACIO.
	void Recargar(const TiposMunicion tipo);
	void SustituirMunicion(const int index, TiposMunicion nuevaMuni);
	void Preparar();
	void Disparar();
	string LeerCargador(const vector<TiposMunicion> check_cargador);
	~Cannon();
};


class Cannon_list
{
public:
	vector<shared_ptr<Cannon>> sistemas;
	shared_ptr<int> sistSelect; //El puntero de selección de cannon se inicializa como 'nullptr'. 
	Cannon_list(shared_ptr<Cannon> can1, shared_ptr<Cannon> can2, shared_ptr<Cannon> can3);
	~Cannon_list();
	//void anadirCan();
	//void quitarCan(Cannon *can);
	
};

class Menu_recarga {
	void mostrar(Cannon_list canList);
	void recargar();
};

class Menu
{
public:
	unique_ptr<bool> p_running { make_unique<bool>(true) }; //Booleano que mantiene el programa en funcionamiento
	Menu_recarga menuRecarga;
	void Activar(Cannon can);
	void Update_list(Cannon_list& canList, vector<shared_ptr<Cannon>>& vect);
	void ListadoSistemasActivos(const Cannon_list canList, int n);
	void Mostrar(Cannon_list canList);
	void Opcion(Cannon_list& can, string n);
	void Opcion(Cannon_list can, char c, bool& run);
	
};


