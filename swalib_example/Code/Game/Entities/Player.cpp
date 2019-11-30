#include "../../../../common/stdafx.h"
#include "Player.h"
#include "../Managers/graphics_engine.h"

//Solo habr� un jugador ya que para este tipo de juego no se tiene pensado a�adir multijugador debido a ser un juego narrativo (con di�logos)
//Decisi�n de dise�o de nivel (aunque se podr�a hacer multijugador)
Player* Player::m_player = nullptr;

Player* Player::create() {
	delete Player::m_player;
	Player::m_player = NEW(Player,());
	return Player::m_player;
}

Player* Player::GetPlayer() {
	return m_player;
}

void Player::DeletePlayer()
{
	DEL(m_player);
}
