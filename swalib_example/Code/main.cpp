#include "../../common/stdafx.h"
#include "../../common/sys.h"
#include "../../common/core.h"
#include "Game/Managers/GameController.h"

using namespace std;

//Bucle principal
int Main(void) {
	//Inicializaci�n del juego
	GameController* game = GameController::Init();
	//Mientras no acabe
	while (!game->Finished()) {
		//Actualizaci�n l�gica del nivel
		game->Update();
		//Dibujado del nivel
		game->Draw();
		SYS_Pump();
	}
	//Terminaci�n del nivel
	DEL(game);
	//Fugas de memoria
	DUMP_LEAKS
	return 0;
}
