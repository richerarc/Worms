#include "C2DVector.h"
//#include <time.h>

class CPhysics{
private:
	C2DVector * m_Wind;
	double m_Gravity;
	double m_MaxSpeed;
	double m_MaxWindSpeed;
	//srand(time(NULL));

public:
	// Constructeur:
	//	Parametres: _Gravity - affecte la valeur de la gravité (1 fois par jeu).
	//				_MaxSpeed - affecte la valeur maximale de l'accélération gravitationnelle.
	//				_MaxWindSpeed - affecte la valeur maximale de la force du vent sur un axe (donc maximum: MaxWindSpeed sur X + MaxWindSpeed sur Y).
	CPhysics(){
		m_Wind->setX(0);
		m_Wind->setY(0);
		m_Gravity = 1;
		m_MaxSpeed = 1;
		m_MaxWindSpeed = 50;
	}
	
	//Méthode: RedefineWind permet de changer aleatoirement la direction du vent.
	void RedefineWind(){
		m_Wind->setX(rand() % (m_MaxWindSpeed / 2) - (MaxWindSpeed / 4));
		m_Wind->setY(rand() % (m_MaxWindSpeed / 2) - (MaxWindSpeed / 4));
	}

	//Méthode: VerifyCollision permet de vérifier une collision entre deux entités
	//		Paramètres: _Collider - Entité qui crée la collision, donc est en mouvement.
	//					_Collidee - Entité qui reçoit la collision, donc est immobile.
	bool VerifyCollision(CEntity* _Collider, CEntity* _Collidee){

	}
	
	//Méthode: Fall:	Calcule la trajectoire d'une chute d'une entité.
	//			Paramètres:	_Vector - Vecteur(vitesse et direction) initiale de la chute.
	//						_X et _Y - Positions en X et en Y intiales de l'entité.
	CTrajectory * Fall(C2DVector * _Vector, int _X, int _Y){

	}

	//Méthode: Fall:	Calcule la trajectoire d'un glissement d'une entité.
	//			Paramètres:	_Vector - Vecteur(vitesse et direction) initiale du glissement.
	//						_X et _Y - Positions en X et en Y intiales de l'entité.
	CTrajectory * Slide(C2DVector * _Vector, int _X, int _Y){

	}

	/*Méthode : Propulsion
	Brief : Fonction qui retourne la trajectoire d'une chose propulsée
	Params :
	_PosInit : Position initiale de la propulsion
	_Vit : Vitesse initiale de la propulsion
	*/
	CTrajectory * Propulsion(C2DVector* _PosInit, C2DVector* _Vit){
		return CTrajectory(_PosInit, _Vit);
	}



};