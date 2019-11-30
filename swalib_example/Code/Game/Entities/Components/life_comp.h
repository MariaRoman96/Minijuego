#pragma once
#ifndef _NEW_LIFE_COMP_H_
#define _NEW_LIFE_COMP_H_

#include "../../../../../common/core.h"
#include "component.h"
#include <vector>
#include "../../../../../common/BehaviourTree.h"

using namespace std;

//Componente de la vida
class cLifeComp : public cComponent
{
protected:
	//Vidas iniciales/m�ximas del jugador (para reiniciar correctamente)
	int m_initLifes;
	//Vidas actuales del jugador
	int m_lifes;
	//Si el jugador es invulnerable o no
	bool m_inv;
	//Tiempo de invulnerabilidad
	float m_invTime;
	//Control del tiempo total que ha pasado
	float m_waitTime;
	//Tiempo que dura la visibilidad durante el tiempo de invulnerabilidad
	float m_invTicksTime;
	//Tiempo que dura la invisibilidad durante el tiempo de invulnerabilidad
	float m_blankTime;
public:
	cLifeComp(int lifes, float invTime, float invTicksTime, float blankTime);
	cLifeComp() {};
	virtual void Slot(float fTimeDiff) override;
	inline const int &GetLifes() const { return m_lifes; }
	inline void Setlifes(int lifes) { m_lifes = lifes; }
	inline const bool &GetInv() const { return m_inv; }
	inline void SetInv(bool inv) { m_inv = inv; }
	inline const float &GetInvTicks() const { return m_invTicksTime; }
	inline void SetInvTicks(float invTicks) { m_invTicksTime = invTicks; }
	inline const float &GetBlankTime() const { return m_blankTime; }
	inline void SetBlankTime(bool blankTime) { m_blankTime = blankTime; }
	inline const int &GetInitLifes() const { return m_initLifes; }
	inline void SetInitLifes(int initPlayerLifes) { m_initLifes = initPlayerLifes; }

	virtual void ReceiveMessage(cMessage &message) override;
};

//Componente de la l�gica del boss, se encuentra aqu� ya que hereda de la vida y a�ade funciones extras debido a que el boss ir� perdiendo vida
//a medida que dispara
class cBossLogicComp : public cLifeComp
{
public:
	//Informaci�n extra de los proyectiles del boss
	struct bossEnem {
		float maxSpeedEnemy;
		float minSpeedEnemy;
		bool rotateEnemy = false;
		float error = 0.0f;
	};
	cBossLogicComp(vector<vec3> poss, float roundWait, float initWait, bool random, int lifes, bossEnem enemyData);
	~cBossLogicComp() { DEL(m_behaviourTree); };
	bool GetContinue(float fTimeDiff);
	inline void SetContinue(bool cont) { m_continue = cont; }
	inline const float &GetTime() const { return m_time; }
	inline void SetTime(float time) { m_time = time; }
	inline const bossEnem &GetData() const { return m_enemyData; }
	inline void SetData(bossEnem data) { m_enemyData = data; }

	inline vector<vector<vector<string>>> GetBehaviourTree() { return m_behaviourTreeData; }
	static vector<vector<vector<string>>> default_string;
	void SetBehaviourTree(vector<vector<vector<string>>> data = default_string);

	void ReconstructBehaviour();

	void finishLogic();

	virtual void Slot(float fTimeDiff) override;

	virtual void ReceiveMessage(cMessage &message) override;
private:
	//�ndice del vector de posiciones en el que se encuentra el boss
	int m_index;
	//Vector de posiciones que el boss ir� recorriendo, si random es false se recorrer� la lista en orden, en caso contrario se recorrer� aleatoriamente
	//Dicho vector est� compuesto por 2 valores (posici�n) y un tercer valor que indica el tiempo que permanecer� en dicha posici�n, la posici�n inicial es la
	//primera del vector
	vector<vec3> m_poss;
	//Tiempo de espera entre disparo y disparo a menor tiempo mayor cantidad de disparos
	float m_roundWait;
	//Tiempo restante para cambiar de posici�n
	float m_timePos;
	//Variable de gesti�n del tiempo (controla el tiempo que ha pasado en total)
	float m_time;
	//Variable que indica si continua la l�gica (spawn de enemigos) o no
	bool m_continue;
	//Datos de los enemigos (proyectiles del boss)
	bossEnem m_enemyData;
	//Behaviour Tree Data
	vector<vector<vector<string>>> m_behaviourTreeData;
	//Behaviour Tree
	BehaviourTree* m_behaviourTree;
};

#endif
