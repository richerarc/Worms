#define GROUND 1111
#define CEILING 2222
#define LEFT 3333
#define RIGHT 4444
#define GROUNDLEFT 5555
#define GROUNDRIGHT 6666
#define CEILINGLEFT 7777
#define CEILINGRIGHT 8888
#define NOCONTACT 9999
#define GROUNDCEILING 1337
#define MOVING 420
#define BLOCKED 666
#define FROMBOTTOM 12345
#define FROMTOP 67890

class CTrajectory;
static class CPhysics{
private:
	static C2DVector * m_Wind;
	static double m_Gravity;
	static int m_MaxSpeed;
	static int m_MaxWindSpeed;
	static SDL_Surface * m_Map;

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
	static void RedefineWind(){
		m_Wind->setX(rand() % (m_MaxWindSpeed)-m_MaxWindSpeed / 2);
		m_Wind->setY(rand() % (m_MaxWindSpeed)-m_MaxWindSpeed / 2);
	}

	//Méthode: VerifyCollision permet de vérifier une collision entre deux rectangles
	//		Paramètres: _Collider - Rectangle qui crée la collision, donc est en mouvement.
	//					_Collidee - Rectangle qui reçoit la collision, donc est immobile.
	static bool VerifyCollision(SDL_Rect _Collider, SDL_Rect _Collidee){
		if ((_Collider.x + _Collider.w > _Collidee.x) || (_Collider.x < _Collidee.x + _Collidee.w)){
			if ((_Collider.y + _Collider.h > _Collidee.y) || (_Collider.y < _Collidee.y + _Collidee.h)){
				return true;
			}
		}
		return false;
	}

	/*
	Méthode : VerifyGroundCollision
	Brief : Fonction qui retourne par un entier l'état d'un rect par rapport au terrain
	Params :
	_Rect : Rectangle dont on vérifie la collision
	Return :
	NOCONTACT : Le rectangle ne touche à rien
	GROUND : Le rectangle touche au sol
	LEFT : Le rectangle touche le terrain à gauche
	RIGHT : Le rectangle touche le terrain à droite
	CEILING : Le rectangle touche le plafond
	GROUNDLEFT : Le rectangle touche le sol et la gauche
	GROUNDRIGHT : Le rectangle touche le sol et la droite
	CEILINGLEFT : Le rectangle touche le plafond et la gauche
	CEILINGRIGHT : Le rectangle touche le plafond et la droite
	GROUNDCEILING : Le rectangle touche au plafond et au sol
	*/
	//Valeur de la transparence : 16777215

	//À VÉRIFIER + optimisations possibles
	static int VerifyGroundCollision(SDL_Rect _Rect){
		bool boGround = false;
		bool boCeiling = false;
		bool boLeft = false;
		bool boRight = false;
		for (int i = 0; i < _Rect.w; i++){
			if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y + _Rect.h) + _Rect.x + i] == 0 && !boGround){
				boGround = true;
			}
			if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y - 2) + _Rect.x + i] == 0 && !boCeiling){
				boCeiling = true;
			}
		}
		for (int i = 0; i < _Rect.h; i++){
			if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y - 1 + i) + _Rect.x + _Rect.w + 1] == 0 && !boRight){
				boRight = true;
			}
			if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y - 1 + i) + _Rect.x - 1] == 0 && !boLeft){
				boLeft = true;
			}
		}
		if (boGround){
			if (boCeiling)
				return GROUNDCEILING;
			if (boLeft)
				return GROUNDLEFT;
			if (boRight)
				return GROUNDRIGHT;
			return GROUND;
		}
		else {
			if (boCeiling){
				if (boLeft)
					return CEILINGLEFT;
				if (boRight)
					return CEILINGRIGHT;
				return CEILING;
			}
			else {
				if (boRight)
					return RIGHT;
				if (boLeft)
					return LEFT;
				return NOCONTACT;
			}
		}
	}

	/*
	Méthode : EvaluateSlope
	Brief : Fonction qui retourne la pente à partir d'une section de la map
	Params :
	_Pos : Position dans la surface où la pente est évaluée
	_Direction : Direction de laquelle vient l'entité impliquée
	Discussion : À FAIRE : Évaluer une collision "de coté"
	*/
	static double EvaluateSlope (C2DVector* _Pos, int _Direction){
		double ValueTab[9];
		SDL_Rect _Rect;
		_Rect.h = 9;
		_Rect.w = 9;
		_Rect.x = _Pos->getX() - 5;
		_Rect.y = _Pos->getY() - 5;
		for (int x = 0; x < _Rect.w; x++){
			for (int y = 0; y < _Rect.h; y++){
				if (_Direction == FROMTOP){
					if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y - 1 + y) + _Rect.w] != 0){
						ValueTab[x] = y + 1;
						y = _Rect.h;
					}
				}
				else{
					if (((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.y - 1 + y) + _Rect.w] != 0){
						ValueTab[x] = y + 1;
					}
				}
			}
		}
		double Med1Y = (ValueTab[0] + ValueTab[1] + ValueTab[2] + ValueTab[3]) / 4;
		double Med2Y = (ValueTab[5] + ValueTab[6] + ValueTab[7] + ValueTab[8]) / 4;
		return (Med2Y - Med1Y)/5;
	}


	//Méthode: Fall:	Calcule la trajectoire d'un glissement d'une entité.
	//			Paramètres:	_Vector - Vecteur(vitesse et direction) initiale du glissement.
	//						_X et _Y - Positions en X et en Y intiales de l'entité.
	static CTrajectory * Slide(C2DVector * _Vector, int _X, int _Y){
		return nullptr;
	}

	/*Méthode : Propulsion
	Brief : Fonction qui retourne la trajectoire d'une entité propulsée
	Params :
	_PosInit : Position initiale de la propulsion
	_Vit : Vitesse initiale de la propulsion
	*/
	static CTrajectory* Propulsion(C2DVector* _PosInit, C2DVector* _Vit){
		return new CTrajectory(_PosInit, _Vit);
	}

	/*
	Méthode : Move
	Brief : Fonction qui ajuste la position suite à un mouvement sans accélération
	Params:
	_Rect : Rectangle se déplaçant
	_Direction : Bool de la direction empruntée
	true : gauche
	false : droite
	Return : true : déplacement effectué
	false : déplacement non effectué
	Discussion : Ne déplace actuellement que d'un pixel sur l'axe X, à changer si voulu
	La hauteur (en pixels) d'une pente "escaladable" en y sera à déterminer (actuellement 3 pixels)
	*/
	static bool Move(SDL_Rect _Rect, bool _Direction){
		if (_Direction){
			for (int i = 0; i < _Rect.h + 3; i++){
				if (!(((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.x - 1 + i) + _Rect.x - 1] == 0)){
					if (i < _Rect.h - 3)
						return BLOCKED;
					else {
						_Rect.y = _Rect.y + (_Rect.h - i);
					}
				}
				if (i == _Rect.h + 2){
					_Rect.y = _Rect.y + (_Rect.h - i);
				}
			}
			_Rect.x = _Rect.x - 1;
			return MOVING;
		}
		else{
			for (int i = 0; i < _Rect.h + 3; i++){
				if (!(((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect.x - 1 + i) + _Rect.x + _Rect.w] == 0)){
					if (i < _Rect.h - 3)
						return BLOCKED;
					else {
						_Rect.y = _Rect.y + (_Rect.h - i);
					}
				}
				if (i == _Rect.h + 2){
					_Rect.y = _Rect.y + (_Rect.h - i);
				}
			}
			_Rect.x = _Rect.x + 1;
			return MOVING;

		}
	}

	//Accesseurs...
	static C2DVector* GetWind(){
		return m_Wind;
	}
	static double GetGravity(){
		return m_Gravity;
	}
};
C2DVector * CPhysics::m_Wind = new C2DVector(0., 0.);
double CPhysics::m_Gravity = 1;
int CPhysics::m_MaxSpeed = 1;
int CPhysics::m_MaxWindSpeed = 50;
SDL_Surface * CPhysics::m_Map = nullptr;