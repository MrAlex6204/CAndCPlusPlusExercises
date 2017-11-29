
using namespace System;
using namespace std;

#define FILAS 40	
#define COLUMNAS 60

#define VIDA 4
#define BORDE 1
#define PUERTA 6
#define BLOCK 3
#define LLAVE 8
//DEFINIR COLORES
#define COLOR_VIDA ConsoleColor::Red
#define COLOR_BORDE ConsoleColor::Cyan
#define COLOR_PUERTA ConsoleColor::Cyan
#define COLOR_BLOCK ConsoleColor::Green
#define COLOR_LLAVE ConsoleColor::DarkGreen

//DEFINIR COLORES
#define CHR_VIDA (char)3
#define CHR_BORDE (char)178
#define CHR_PUERTA_ABIERTA (char)176
#define CHR_PUERTA_CERRADA (char)178
#define CHR_BLOCK (char)5
#define CHR_LLAVE (char)5



//DEFINIMOS LAS TECLAS
#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77
//DEFINIMOS EL TAMANO DE LA PANTALLA
#define SCREEN_WIDTH  65
#define SCREEN_HEIGHT 42
//DEFINIMOS LA DIRECCION A MOVER
#define DIR_DERECHA  1
#define DIR_IZQUIERDA -1
#define DIR_ABAJO  1
#define DIR_ARRIBA -1



void inicio();
void gameover();
void imprimir_mapa();
void terminado();
void escribir_odd(char[], bool*, ConsoleColor, ConsoleColor, int, int);
void escribir(char[], ConsoleColor, int, int);
void abrir_puerta(int[FILAS][COLUMNAS]);

void nivel_1();
void nivel_2();
void nivel_3();
void nivel_4();

void juego_nivel1();
void juego_nivel2();
void juego_nivel3();
void juego_nivel4();


struct Pos{//Estructura para el manejo de las posiciones
public:
	int x;
	int y;

	void set(int x, int y){
		this->x = x;
		this->y = y;
	}

	bool match(int x, int y){
		return (this->x == x && this->y == y);
	}

	bool match(Pos p){
		return (this->x == p.x && this->y == p.y);
	}


};

struct Bala{//Descripcion de Bala
public:
	bool enabled = false;
	Pos pos;
	int velocidad;
	void dibujar(int balaChr, ConsoleColor clr){
		Console::SetCursorPosition(this->pos.x, this->pos.y);
		Console::ForegroundColor = clr;
		cout << (char)balaChr;
	}
	void borrar(Pos p){
		Console::SetCursorPosition(p.x, p.y);
		cout << (char)32;
	}
};

struct Nave{//Descripcion de Nave
public:
	int dir;
	Pos pos;
	int velocidad;
	Bala bala;
	void dibujar(Pos p, int direccion, ConsoleColor clr){
		Console::SetCursorPosition(p.x, p.y);
		Console::ForegroundColor = clr;

		switch (direccion){//Dibujar nave a :
		case ABAJO:
			Console::SetCursorPosition(p.x, p.y);
			cout << (char)32 << (char)32 << (char)30 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 1);
			cout << (char)32 << (char)40 << (char)15 << (char)41 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 2);
			cout << (char)30 << (char)186 << (char)19 << (char)186 << (char)30;
			break;
		case ARRIBA:
			Console::SetCursorPosition(p.x, p.y);
			cout << (char)31 << (char)186 << (char)139 << (char)186 << (char)31;
			Console::SetCursorPosition(p.x, p.y + 1);
			cout << (char)32 << (char)40 << (char)15 << (char)41 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 2);
			cout << (char)32 << (char)32 << (char)31 << (char)32 << (char)32;
			break;
		case IZQUIERDA:
			Console::SetCursorPosition(p.x, p.y);
			cout << (char)16 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 1);
			cout << (char)240 << (char)92 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 2);
			cout << (char)240 << (char)15 << (char)16;
			Console::SetCursorPosition(p.x, p.y + 3);
			cout << (char)240 << (char)47 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 4);
			cout << (char)16 << (char)32 << (char)32;
			break;
		case DERECHA:
			Console::SetCursorPosition(p.x, p.y);
			cout << (char)32 << (char)32 << (char)32 << (char)17;
			Console::SetCursorPosition(p.x, p.y + 1);
			cout << (char)32 << (char)32 << (char)47 << (char)240;
			Console::SetCursorPosition(p.x, p.y + 2);
			cout << (char)32 << (char)17 << (char)15 << (char)240;
			Console::SetCursorPosition(p.x, p.y + 3);
			cout << (char)32 << (char)32 << (char)92 << (char)240;
			Console::SetCursorPosition(p.x, p.y + 4);
			cout << (char)32 << (char)32 << (char)32 << (char)17;
			break;
		}

	};
	void borrar(Pos p, int direccion){

		switch (direccion){//Dibujar nave a :
		case ABAJO:
			Console::SetCursorPosition(p.x, p.y);
			cout << (char)32 << (char)32 << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 1);
			cout << (char)32 << (char)32 << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 2);
			cout << (char)32 << (char)32 << (char)32 << (char)32 << (char)32;
			break;
		case ARRIBA:
			Console::SetCursorPosition(p.x, p.y);
			cout << (char)32 << (char)32 << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 1);
			cout << (char)32 << (char)32 << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 2);
			cout << (char)32 << (char)32 << (char)32 << (char)32 << (char)32;
			break;
		case IZQUIERDA:
			Console::SetCursorPosition(p.x, p.y);
			cout << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 1);
			cout << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 2);
			cout << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 3);
			cout << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 4);
			cout << (char)32 << (char)32 << (char)32;
			break;
		case DERECHA:
			Console::SetCursorPosition(p.x, p.y);
			cout << (char)32 << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 1);
			cout << (char)32 << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 2);
			cout << (char)32 << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 3);
			cout << (char)32 << (char)32 << (char)32 << (char)32;
			Console::SetCursorPosition(p.x, p.y + 4);
			cout << (char)32 << (char)32 << (char)32 << (char)32;
			break;
		}

	}
};

struct Character{
private:
	bool odd = false;
	Pos p;
public:
	Character(int x, int y){
		this->p.x = x;
		this->p.y = y;
	}
	void move_to(Pos new_pos, ConsoleColor clr){

		Console::ForegroundColor = clr;
		this->odd = !this->odd;
		//Limpiar posicion anterior
		Console::SetCursorPosition(this->p.x, this->p.y);
		cout << (char)0;		

		//Actualizar posicion
		this->p = new_pos;
		Console::SetCursorPosition(new_pos.x, new_pos.y);
		cout << (char)12;			

	}

};