#include <stdlib.h>
#include <vector>
#include "clasesCannon.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <time.h>

TiposMunicion to_enum(int n) {
	TiposMunicion out{LASER};
	
	switch (n) {
	case 0:
		out = LASER;
		break;


	case 1:
		out = EXPLOSIVA;
		break;

	case 2:
		out = GAUSS;
		break;

	case 3:
		out = SEGUIDORA;
		break;

	case 4:
		out = HUMO;
		break;

	}
	return out;
}

string LeerCargador(int index) {
	switch (index) {
	case 0:
		return "LASER";
		break;

	case 1:
		return "EXPLOSIVA";
		break;

	case 2:
		return "GAUSS";
		break;

	case 3:
		return "SEGUIDORA";
		break;

	case 4:
		return "HUMO";
		break;

	default:
		return "Error: municion desconocida";
	}
}

bool checkLength(const string &cadena) {
	return (cadena.length() > 1) ? true : false;
}

void Preparar(Cannon& can)
{
	string armed;
	can.Statscannon.ready = !(can.Statscannon.ready);
	if (can.Statscannon.ready == true)
	{
		armed = "armado";
	}
	else
	{
		armed = "desarmado";
	}
	cout << "Cannon " << to_string(can.ID) << " " << armed << endl << endl;
}


Cannon::Cannon(int NID)
{
	ID = NID;
	cout << "Detectado sistema N " << to_string(NID) << endl;

	//--------------------  Atributos del arma ----------------
	Ndisparos_realizados = 0;
	this->Statscannon.ready = false;
	vector <int>cargador{ 0 };
	debugMode = false;
}


void Cannon::Recargar(const TiposMunicion tipo)
{
	vector<TiposMunicion> munCargada{ tipo };
	vector<TiposMunicion>& objCargador = this->cargador;
	if (this->cargador.size() < this->cargadorMax) {
		objCargador.push_back(tipo);
		cout << "Municion cargada en sistema " << to_string(this->ID) << " : " << ::LeerCargador(tipo) << endl;

		for (TiposMunicion elem : objCargador) {
			cout << " --> " << ::LeerCargador(static_cast<int>(elem)) << endl;
		}
	}
	else {
		cout << endl << endl;
		for (TiposMunicion elem : objCargador) {
			cout << " --> " << ::LeerCargador(static_cast<int>(elem)) << endl;
		}
		cout << "Cargador lleno" << endl;
		cout  << endl << endl;
	}
}

	void Cannon::Preparar()
	{
		this->Statscannon.ready = !(this->Statscannon.ready);
		string armed;

		if (this->Statscannon.ready == true)
		{
			armed = "armado";
		}
		else
		{
			armed = "desarmado";
		}

		cout << "\nCannon " << to_string(this->ID) << " " << armed << endl << endl;
	}


	void Cannon::SustituirMunicion(const int index, TiposMunicion nuevaMuni) {
		cout << "Sustituyendo municion " << ::LeerCargador(this->cargador.at(index)) << " por " << ::LeerCargador(nuevaMuni)<< endl;
		auto cargador = &this->cargador;
		cargador->at(index) = nuevaMuni;
		//cargador.at(index) = nuevaMuni;

	}

	void Cannon::Disparar()
	{
		if (this->Statscannon.ready) {
			if (this->cargador.size() > 0) {
				cout << "Disparo inciado..." << endl;
				this->cargador.erase(cargador.begin());
				cout << "Sistema " << to_string(this->ID) << " disparado" << endl;
				cout << "Nuevo estado del cargador. " << endl;
				cout << "---------------------------" << endl;
				for (TiposMunicion elem : this->cargador) {
					cout << ::LeerCargador(elem) << endl;
				}
				
			}
			else {
				cout <<"Sistema descargado. Iniciar recarga" << endl;
				
			}
		}
		else {
			cout << "Sistema no preparado. Inicializar sistema" << endl;
			
		}
		system("pause");
	}

	string Cannon::LeerCargador(const vector<TiposMunicion> check_cargador)
	{
		if (check_cargador.empty()) {
			return "Cargador vacio";
		}
		else
		{
			for (TiposMunicion elem : check_cargador) {
				switch (static_cast<int>(elem)) {
				case TiposMunicion::HUMO:
					return "Humo";
					break;

				case TiposMunicion::EXPLOSIVA:
					return "Explosiva";
					break;

				case TiposMunicion::GAUSS:
					return "Gauss";
					break;

				case TiposMunicion::LASER:
					return "Laser";
					break;

				case TiposMunicion::SEGUIDORA:
					return "Seguidora";
					break;
				}
			}
			return "Error: municion desconocida";
		}
	}

	
	

Cannon::~Cannon()
{
	cout << "----------------------" << endl;
	cout << " Destruyendo cannon " << to_string(this->ID)<<endl;
	cout << "----------------------" << endl<<endl;
}
;


void Menu::Activar(Cannon can)
{
	cout << "Seleccione los sistemas a activar" << endl;


}

void Menu::Update_list(Cannon_list& canList, vector<shared_ptr<Cannon>>& vect) {	// Actualización de la lista de punteros shared de aquellos sistemas activados por el usuario
	for (shared_ptr<Cannon> sist : canList.sistemas)
	{
		if (sist.get()->Statscannon.ready == true) {
			vect.push_back(sist);
		}
	}
}

void Menu::ListadoSistemasActivos(const Cannon_list canList, int n) {
	system("cls");
	string menuActivo{};

	switch (n) {
	case 1:
		menuActivo = " activacion de ";
		break;

	case 2:
		menuActivo = " estadisticas de ";
		break;

	case 3:
		menuActivo = " recarga de ";
		break;

	case 4:
		menuActivo = " disparo de ";
		break;

	default:
		menuActivo = "ERROR EN DETECCION DE MENU ACTIVO";
	}

	cout << "Menu de" << menuActivo << "sistemas" << endl;
	cout << "---------------------------" << endl;
	
	string estado;
	char cargado{ ' ' } ;
	for (shared_ptr<Cannon> cannon : canList.sistemas) {
		if (cannon.get()->Statscannon.ready == false) {
			estado = "OFF";
		}
		else {
			estado = "ON";
			if (cannon.get()->cargador.size() > 0) {
				cargado = 'c';
			}
		}
		cout << "\tCannon " << "(" << cannon.get()->ID << ")" << " " << estado << endl;
	}
	cout << "Seleccione el sistema a manipular o pulse (S)alir" << endl;
	cout << endl << endl;
}

void Menu::Opcion(Cannon_list& can, string strn)
{

	//TODO: El vector sistActivos se debe actualizar cada vez que se arma un cañon.
	// Por tanto, debe de contener punteros hacia aquellos que estén activos.
	// Además, debe de poder actualizarse sobre la marcha.
	// Ojo, la modificación ha de ser por referencia, para que la actualización perdure.
	// Probar a inicializar el vector en el constructor
	vector <shared_ptr<Cannon>> sistActivos;
	if (::checkLength(strn)) {
		cout << "valor introducido incorrecto" << endl;
		cout << "Pulse otra tecla para continuar" << endl;
		system("pause");
	}
	else {
		int npre = strn[0];
		int n = npre - '0';
		if (n == 1) {						//------------------------------- Primera opción: Activar sistemas
			bool menuSistemas = true;
			while (menuSistemas) {
				Update_list(can, sistActivos);
				if (sistActivos.empty()) {
					cout << "Ningun sistema preparado." << endl;
					cout << "Seleccione los sistemas a armar:" << endl << endl;
				}

				bool done{ false };

				while (!done) {
					cout << "Menú de activacion de sistemas" << endl;
					cout << "------------------------------" << endl<<endl;
					ListadoSistemasActivos(can,n);
					string strOpt;
					cin >> strOpt;

					if (::checkLength(strOpt)) {
						cout << "Valor introducido incorrecto" << endl;
						system("pause");
						system("cls");
					}

					else {
						char opt = strOpt[0];
						if (isdigit(opt)) {
							int iopt = opt - '0';
							for (shared_ptr<Cannon>& cannon : can.sistemas) { // ------------>> Anotación importante: Se ha de iterar por referencia
								if (iopt == cannon.get()->ID) {
									cannon.get()->Preparar();
									done = !done;
									Update_list(can, sistActivos);
								}
							}
						}

						else if (opt == 's' || opt == 'S') {
							done = true;
							menuSistemas = !menuSistemas;
						}
						else {
							cout << "Introduzca valor valido" << endl;
							system("pause");
							system("cls");

						}
					}
				}
			}
			Update_list(can, sistActivos);
		}

		if (n == 2) {						
			//------------------------------- Segunda opción: Estadísticas del sistema
			// El cargador actúa como un elemento FIFO
			bool done{ false };
			while (!done) {
				cout << "Menú de estadisticas de sistemas" << endl;
				cout << "------------------------------" << endl << endl;
				ListadoSistemasActivos(can,n);
				Update_list(can, sistActivos);
				string opt_in;
				cin >> opt_in;
				cin.ignore();
				if (checkLength(opt_in)) {
					cout << "Valor introducido incorrecto" << endl;
					system("pause");
					system("cls");
				}
				else {
					string opt = opt_in;
					if (::checkLength(opt)) {
						cout << "Valor introducido incorrecto" << endl;
						system("pause");
						system("cls");
					}
					else {
						char opt = opt_in[0];
						if (isdigit(opt)) {
							int iopt = opt - '0';
							for (shared_ptr<Cannon>& cannon : can.sistemas) {
								if (iopt == cannon.get()->ID) {
									if (cannon.get()->Statscannon.ready) {
										cout << endl << endl;
										cout << "Estadisticas del sistema " << to_string(cannon.get()->ID) << endl;
										cout << "--------------------------------------------------" << endl << endl;
										cout << "Temperatura:  " << to_string(cannon.get()->Statscannon.temp) << endl;
										cout << "Posicion angular actual:  " << to_string(cannon.get()->Statscannon.position) << endl;
										cout << "Contenido del cargador: " << cannon.get()->cargador.size() << endl;
										cout << "----------------------------" << endl << endl;

										if (cannon.get()->cargador.size() == 0) {
											cout << "El cargador del sistema " << to_string(cannon.get()->ID) << " esta vacio" << endl << endl;
										}
										
										else {
											for (TiposMunicion elem : cannon.get()->cargador) {
												string out = LeerCargador(elem);
												cout << out << endl;
											}
										}
										system("pause");
									}
									else {
										cout << "Sistema desactivado. Activar antes para manipular el sistema" << endl;
										system("pause");
										system("cls");
									}
								}
							}
						}


						else if (opt == 's' || opt == 'S') {
							done = true;
						}
						else {
							cout << "Introduzca valor valido" << endl;
							cout <<"Pulse una tecla para continuar" <<endl;
							system("pause");
							system("cls");
						}
					}
				}
			}
		}

		if (n == 3) {						//------------------------------- Tercera opción: Operar cargador
			bool done{ false };
			bool menuRecarga{ true };
			ListadoSistemasActivos(can,n);
			while (!done) {
				{
					while (menuRecarga) {
						string strOpt{};
						cin >> strOpt;
						if (::checkLength(strOpt)) {
							cout << "Valor introducido invalido" << endl;
							system("pause");
							system("cls");
							ListadoSistemasActivos(can,n);
						}
						else {
							char opt = strOpt[0];
							if (!isdigit(opt)) {
								if (opt == 's' || opt == 'S') {
									menuRecarga == false;
									done = true;
								}
								else {
									cout << "Valor introducido invalido" << endl;
									system("pause");
									system("cls");
									ListadoSistemasActivos(can, n);
								}
							}
							else {
								int cannonSelect = opt - '0';
								for (shared_ptr<Cannon>& cannon : can.sistemas) {
									
										if (cannonSelect == cannon.get()->ID) {
											if (cannon.get()->Statscannon.ready == false) {
												cout << "Sistema desactivado. Activar antes de operar" << endl;
												system("pause");
												ListadoSistemasActivos(can,n);
											}
																						
											else {
											cout << "---------------------------" << endl;
											cout << "Contenido del cargador: sistema " << to_string(cannon.get()->ID) << endl;
											cout << "---------------------------" << endl;
											
											for (TiposMunicion elem : cannon.get()->cargador) {
												string out = cannon.get()->LeerCargador(cannon.get()->cargador);
												cout << out << endl;
											}

											cout << "Operaciones disponibles" << endl;
												cout << "1 -> Recargar" << endl;
												cout << "2 -> Sustituir municiones" << endl;
												cout << "S -> Salir" << endl;

												string str_opcion_recarga;
												cin >> str_opcion_recarga;
												cin.ignore();
												if (::checkLength(str_opcion_recarga)) {
													cout << "Valor introducido invalido" << endl;
													system("pause");
													system("cls");
													ListadoSistemasActivos(can, n);
												}
												else {
													char opcion_recarga = str_opcion_recarga[0];
													if (!isdigit(opcion_recarga)) {
														if (opcion_recarga == 's' || opcion_recarga == 'S') {
															menuRecarga == false;
														}
														else {
															cout << "Valor introducido invalido" << endl;
															system("pause");
															system("cls");
															ListadoSistemasActivos(can, n);
															}
													}
													else {
														int iopt = opcion_recarga - '0';
														if (iopt < 0 || iopt > 2) {
															cout << "Valor introducido invalido" << endl;
															system("pause");
															system("cls");
															ListadoSistemasActivos(can, n);
														}
														bool doneRecarga{ false };
														{
															while (!doneRecarga) {
																if (iopt == 1) {
																	cout << "Seleccione el tipo de municion a cargar" << endl;
																	cout << "1 -> LASER" << endl;
																	cout << "2 -> EXPLOSIVA" << endl;
																	cout << "3 -> GAUSS" << endl;
																	cout << "4 -> SEGUIDORA" << endl;
																	cout << "5 -> HUMO" << endl;
																	cout << "S -> Salir" << endl;
																	string str_municion;
																	cin >> str_municion;
																	cin.ignore();

																	if (::checkLength(str_municion)) {
																		cout << "Valor introducido invalido" << endl;
																		system("pause");
																		system("cls");
																		ListadoSistemasActivos(can, n);
																	}
																	else {
																		int municion = (int)str_municion[0];
																		if (isdigit(municion)) {

																			TiposMunicion out{};
																			cout << "Municion seleccionada: " << to_string(municion - '0') << endl;
																			int seleccion = (int)municion - (int)'0';

																			switch (seleccion) {
																			case 1:
																				out = LASER;
																				break;
																			case 2:
																				out = EXPLOSIVA;
																				break;
																			case 3:
																				out = GAUSS;
																				break;
																			case 4:
																				out = SEGUIDORA;
																				break;
																			case 5:
																				out = HUMO;
																				break;
																			default:
																				cout << "Tipo desconocido" << endl;
																				break;
																			}

																			if (seleccion > 0 && seleccion <= 5) {
																				for (shared_ptr<Cannon>& cannon : can.sistemas) {
																					if (cannon.get()->ID == cannonSelect)
																						cannon.get()->Recargar(out);
																					// Una vez termina la operación, vuelve al menú de recarga
																				}
																			}
																			else {
																				cout << "Introduzca un valor valido." << endl << endl;
																				system("pause");
																				system("cls");
																			}

																		}
																		else {
																			if (municion == 'S' || municion == 's') {
																				doneRecarga = true;
																				system("cls");
																				return;
																			}
																			else {
																				cout << "Valor introducido invalido" << endl;
																				system("pause");
																				system("cls");
																			}
																		}

																	}
																}

																else if (iopt == 2) {
																	cout << "Seleccione municion a sustituir del cargador: " << endl;
																	if (cannon.get()->cargador.size() > 0) {
																		int i = 0;
																		for (TiposMunicion elem : cannon.get()->cargador) {

																			cout << to_string(i) << " --> " << LeerCargador(elem) << endl;
																			i++;
																		}
																		cout << "Introduzca 'S' para salir" << endl;
																	}
																	else {
																		cout << "Cargador vacio... Recargue el sistema" << endl;
																	}
																	string str_selecc;
																	cin >> str_selecc;
																	cin.ignore();
																	if (::checkLength(str_selecc)) {
																		cout << "Valor introducido invalido" << endl;
																		system("pause");
																		system("cls");
																	}
																	else {
																		char selecc = str_selecc[0];
																		if (isalpha(selecc)) {
																			if (selecc == 's' || selecc == 'S') {
																				doneRecarga = true;
																				return;
																			}
																			else {
																				cout << "Valor introducido invalido" << endl;
																				system("pause");
																				system("cls");
																			}
																		}
																		else {
																			cout << "Seleccione municion nueva" << endl;
																			for (int i = 0; i < 5;i++)
																				cout << to_string(i) << "--> " << ::LeerCargador(i) << endl;

																			string str_nuevaMun{};
																			cin >> str_nuevaMun;
																			cin.ignore();
																			if (::checkLength(str_nuevaMun)) {
																				cout << "Valor introducido invalido" << endl;
																				system("pause");
																				system("cls");
																			}
																			else {
																				int nuevaMun = str_nuevaMun[0] - '0';
																				cout << "Municion seleccionada: " << ::LeerCargador(nuevaMun) << endl;
																				cout << "Sustituyendo..." << endl;
																				int intSelecc = selecc - '0';
																				cannon.get()->SustituirMunicion(intSelecc, ::to_enum(nuevaMun));
																				cout << "--------------" << endl;
																				cout << "Nueva disposicion" << endl;

																				for (TiposMunicion elem : cannon.get()->cargador) {
																					cout << LeerCargador(elem) << endl;
																				}

																				cout << "Pulse tecla para finalizar proceso" << endl;
																				system("pause");
																				system("cls");
																			}
																		}
																	}
																}
															}
														}
													}
												}

											}
										}
								}
							}
						}
					}
				}
			}
		}

		if (n == 4) {
			bool done{ false };
			while (!done) {
				ListadoSistemasActivos(can, n);
				Update_list(can, sistActivos);
				char opt;
				cin >> opt;
				cin.ignore();
				if (isdigit(opt)) {
					int iopt = opt - '0';
					for (shared_ptr<Cannon>& cannon : can.sistemas) {
						if (iopt == cannon.get()->ID) {
							cannon.get()->Disparar();
						}
					}
				}
				else {
					if (opt == 's' || opt == 'S') {
						done = true;
						system("pause");
						system("cls");
					}
				}
			}
		}
	}
};


void Menu::Opcion(Cannon_list can,char c, bool &run) 
// Función sobrecargada con caracteres, si el carácter es e o E, la variable run cambia de estado
// Nota: "run" debe cambiar por referencia
{
	if (c == 'e' || c == 'E') 
	{
		cout << "Desactivando el sistema... " << endl;
		cout << "Variable global running, direccion: " << &run << " con estado " << to_string(run) <<endl; //run -> dirección ; *run -> Desreferenciación
		cout << "Pulse una tecla para salir... " << endl<<endl;
		run = false;
		system("pause");

	}

	else if (c == 'd' || c == 'D') 
	{
		cout << "Activado modo debug" << endl;
		system("pause");
	}

	else {
		cout << "El caracter introducido es: " << c << endl;
		cout << "Introduzca un valor valido" << endl;
		system("pause");
	}
}

void Menu::Mostrar(Cannon_list canList)
{
	cout << "Menu de controles: " << endl;
	cout << "\t 1 -> Activar sistema(s)" << endl;
	cout << "\t 2 -> Estadisticas del sistema" << endl;
	cout << "\t 3 -> Operar cargador" << endl;
	cout << "\t 4 -> Disparar sistema" << endl;
	cout << "\t E -> Salir" << endl << endl;
	
	string strOpt;
	cin >> strOpt;
	cin.ignore();
	if (::checkLength(strOpt)) {
		cout << "Valor introducido incorrecto" << endl;
	}
	else {
		char opt = strOpt[0];
		bool esletra = isalpha(opt);
		if (esletra) {
			Opcion(canList, opt, *this->p_running.get());
		}
		else {
			int intOpt = opt - '0';
			Opcion(canList, strOpt);
		}
	}
}

// TODO: Convertir la lista de Cannon_list en función de argumentos variables

Cannon_list::Cannon_list(shared_ptr<Cannon> can1, shared_ptr<Cannon> can2, shared_ptr<Cannon> can3) {
	// Cannon_list guarda una lista de punteros shared_ptr, que son los cañones activos en el sistema, creados al inicio del programa
	sistemas.push_back(can1);
	sistemas.push_back(can2);
	sistemas.push_back(can3);
}

Cannon_list::~Cannon_list() {
	
}

/*
void Cannon_list::anadirCan()
{
	
}

void Cannon_list::quitarCan(Cannon *can)
{
	
}
*/

void Menu_recarga::mostrar(Cannon_list canList)
{
	cout << "\t\tAdministración de cargadores: " << endl;
	cout << "\t\t\t 1 -> Recarga" << endl;
	cout << "\t\t\t 2 -> sustituir municiones" << endl;
	cout << "\t\t\t E -> Salir" << endl << endl;
}

void Menu_recarga::recargar()
{
}
