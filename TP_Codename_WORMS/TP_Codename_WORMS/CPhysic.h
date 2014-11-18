

static class CPhysics{
private:
	static C2DVector * m_Wind;
	static double m_Gravity;
	static int m_MaxSpeed;
	static int m_MaxWindSpeed;

public:
	// Constructeur:
	//	Parametres: _Gravity - affecte la valeur de la gravité (1 fois par jeu).
	//				_MaxSpeed - affecte la valeur maximale de l'accélération gravitationnelle.
	//				_MaxWindSpeed - affecte la valeur maximale de la force du vent sur un axe (donc maximum: MaxWindSpeed sur X + MaxWindSpeed sur Y).
	//CPhysics(){
		//m_Wind->setX(0);
		//m_Wind->setY(0);
		//m_Gravity = 1;
		//m_MaxSpeed = 1;
		//m_MaxWindSpeed = 50;
	//}

	//Méthode: RedefineWind permet de changer aleatoirement la direction du vent.
	void RedefineWind(){
		m_Wind->setX(rand() % (m_MaxWindSpeed) - m_MaxWindSpeed/2);
		m_Wind->setY(rand() % (m_MaxWindSpeed) - m_MaxWindSpeed/2);
	}

	//Méthode: VerifyCollision permet de vérifier une collision entre deux rectangles
	//		Paramètres: _Collider - Rectangle qui crée la collision, donc est en mouvement.
	//					_Collidee - Rectangle qui reçoit la collision, donc est immobile.
	bool VerifyCollision(SDL_Rect _Collider, SDL_Rect _Collidee){
		if ((_Collider.x + _Collider.w > _Collidee.x) || (_Collider.x < _Collidee.x + _Collidee.w)){
			if ((_Collider.y + _Collider.h > _Collidee.y) || (_Collider.y < _Collidee.y + _Collidee.h)){
				return true;
			}
		}
		return false;
	}

	//Méthode: Fall:	Calcule la trajectoire d'une chute d'une entité.
	//			Paramètres:	_Vit - Vecteur(vitesse et direction) initiale de la chute.
	//						_Pos - Position initiale de l'entité.
	CTrajectory Fall(C2DVector * _Vit, C2DVector * _Pos){
		CTrajectory Fall = CTrajectory(_Pos,_Vit);
		return Fall;
	}

	//Méthode: Fall:	Calcule la trajectoire d'un glissement d'une entité.
	//			Paramètres:	_Vector - Vecteur(vitesse et direction) initiale du glissement.
	//						_X et _Y - Positions en X et en Y intiales de l'entité.
	CTrajectory * Slide(C2DVector * _Vector, int _X, int _Y){

	}

	/*Méthode : Propulsion
	Brief : Fonction qui retourne la trajectoire d'une entité propulsée
	Params :
	_PosInit : Position initiale de la propulsion
	_Vit : Vitesse initiale de la propulsion
	*/
	CTrajectory Propulsion(C2DVector* _PosInit, C2DVector* _Vit){
		return CTrajectory(_PosInit, _Vit);
	}

	//Accesseurs...
	static C2DVector* GetWind(){
		return m_Wind;
	}
	static double GetGravity(){
		return m_Gravity;
	}
};
C2DVector * CPhysics::m_Wind = new C2DVector(0.,0.);
double CPhysics::m_Gravity = 1;
int CPhysics::m_MaxSpeed = 1;
int CPhysics::m_MaxWindSpeed =50;