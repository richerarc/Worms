#define TRANSPARENCY 0 //16777215 //268435455
#define GROUND 0x00000001
#define CEILING 0x00000010
#define LEFT 0x00000100
#define RIGHT 0x00001000
#define GROUNDLEFT (GROUND|LEFT)
#define GROUNDRIGHT (GROUND|RIGHT)
#define CEILINGLEFT (CEILING|LEFT)
#define CEILINGRIGHT (CEILING|RIGHT)
#define NOCONTACT 0x00000000
#define UNDERGROUND (GROUND|CEILING|LEFT|RIGHT)
#define GROUNDCEILING (GROUND|CEILING)
#define MOVING 420
#define BLOCKED 666
#define FROMBOTTOM 12345
#define FROMTOP 67890


class CPhysics{
private:
	static C2DVector * m_Wind;			// Le vent
	static double m_Gravity;			// La gravité
	static int m_MaxSpeed;				// La vitesse maximum
	static int m_MaxWindSpeed;			// Le vent maximum
	static SDL_Surface * m_Map;			// Le Cham de battaile ou la physique aura son effet.

public:

	/*!
	@method Init.
	@brief Initialise les données membres.
	@param _map: Champ de battaile
	@param _gravity: Gravité qui influra sur les entitées
	@param _maxWind: Vent maximum.
	@return Adresse mémoire de l'objet.
	@discussion Comme tous les données membres sont statiques, Le init agit comme un constructeur.
	*/
	static void Init(SDL_Surface* _map, double _gravity, int _maxWind){
		m_Wind = new C2DVector(0,0,0,0);
		m_Map = _map;
		m_Gravity = _gravity;
		m_MaxWindSpeed = _maxWind;
		RedefineWind();
	}

	/*!
	@method Annihilate.
	@brief Agit comme un destructeur, met tout a nullptr
	@return Aucun
	@discussion Aucune
	*/
	static void Annihilate(){
		m_Map = nullptr;
		m_Gravity = 0;
		m_MaxWindSpeed = 0;
		delete m_Wind;
		m_Wind = nullptr;
	}

	/*!
	@method RedefineWind
	@brief  Permet de changer aleatoirement la direction du vent.
	@param Aucun.
	@return Aucun
	@discussion Aucune.
	*/
	static void RedefineWind(){
		m_Wind->setNorme(rand() % m_MaxWindSpeed);
		m_Wind->setOrientation(rand() % 360);
	}

	/*!
	@method Verify collision
	@brief Vérifie si deux rect se touche
	@param _Collider: Le rect en mouvement
	@param _Collidee: Le rect immobile .
	@return true si il y a un collision?
	@return false si il n'en a pas
	@discussion Aucune.
	*/
	static bool VerifyCollision(SDL_Rect _Collider, SDL_Rect _Collidee){
		if ((_Collider.x + _Collider.w > _Collidee.x) || (_Collider.x < _Collidee.x + _Collidee.w)){
			if ((_Collider.y + _Collider.h > _Collidee.y) || (_Collider.y < _Collidee.y + _Collidee.h)){
				return true;
			}
		}
		return false;
	}

	/*!
	@method VerifyNextPosition
	@brief Vérifie la position prochaine pour les collisions.
	@param _Trajectoire: Trajectoire a parcourir par l'objet.
	@param _EntityRect: Rect de l'objet qui tombe
	@return La position de la collision si il y en a une.
	@return La position finale si la trajectoire c'est fait sans collisions.
	@return nullptr si le déplacement n'est pas significatif.
	@discussion Aucune.
	*/
	static CPosition* VerifyNextPosition(CTrajectory* _Trajectoire, SDL_Rect _EntityRect){
		C2DVector* pVector = new C2DVector((int)_Trajectoire->GetActualPosition()->getX(), (int)_Trajectoire->GetActualPosition()->getY(), (int)_Trajectoire->getNextPos()->getX(), (int)_Trajectoire->getNextPos()->getY());
		if (pVector->getNorme()){
			CPosition* CollisionPosition = new CPosition(0.f, 0.f);
			pVector->Normalize();
			int iX, iY;
			iX = pVector->getComposanteX() + pVector->getXDebut();
			iY = pVector->getComposanteY() + pVector->getYDebut();
			while ((pVector->getXfin() >= pVector->getXDebut()) &&
				(pVector->getYfin() >= pVector->getYDebut()))
			{
				//x>0 y>0
				if (((pVector->getComposanteX()) > 0) && (pVector->getComposanteY() > 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + _EntityRect.h)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}
					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + i)) + (iX + _EntityRect.w)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}
				}

				//x>0 y<0
				if (((pVector->getComposanteX()) > 0) && (pVector->getComposanteY() < 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}


					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + i)) + (iX + _EntityRect.w)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}
				}

				//x<0 y>0
				if (((pVector->getComposanteX()) < 0) && (pVector->getComposanteY() > 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + _EntityRect.h)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}
					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + i)) + (iX)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}
				}

				//x<0 y<0
				if (((pVector->getComposanteX()) < 0) && (pVector->getComposanteY() < 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}
					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + 1)) + (iX)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}
				}

				//x=0 y>0
				if (((pVector->getComposanteX()) == 0) && (pVector->getComposanteY() > 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + _EntityRect.h)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}
				}

				//x=0 y<0
				if (((pVector->getComposanteX()) == 0) && (pVector->getComposanteY() < 0)){
					for (int i = 0; i < _EntityRect.w; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY)) + (iX + i)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}
				}

				//x>0 y=0
				if (((pVector->getComposanteX()) > 0) && (pVector->getComposanteY() == 0)){
					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + i)) + (iX + _EntityRect.w)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}
				}

				//x<0 y=0
				if (((pVector->getComposanteX()) < 0) && (pVector->getComposanteY() == 0)){
					for (int i = 0; i < _EntityRect.h; i++)
					{
						if (((unsigned int*)m_Map->pixels)[(m_Map->w * (iY + 1)) + (iX)] > TRANSPARENCY){
							CollisionPosition->setXY(iX, iY);
							delete pVector;
							return CollisionPosition;
						}
					}
				}
				iX = pVector->getComposanteX() + pVector->getXDebut();
				iY = pVector->getComposanteY() + pVector->getYDebut();
				pVector->setXYDebut(iX, iY);

			}
			CollisionPosition->setXY(pVector->getXfin(), pVector->getYfin());
			delete pVector;
			return CollisionPosition;
		}
		delete pVector;
		return nullptr;
	}

	/*!
	@method Evaluate Slope
	@brief  Fonction qui retourne la pente (en degrés) à partir d'une section de la map
	@param _Pos : Position dans la surface où la pente est évaluée
	@param _Direction : Direction de laquelle vient l'entité impliquée
	@return L'angle de la pennte en degré;
	@discussion À FAIRE : Évaluer une collision "de coté"
	*/
	static double EvaluateSlope(SDL_Rect* _Rect){
		double Slope = 0;
		bool first = false;
		int PreviousY;
		double PointsSignificatifs = 0;
		for (int x = _Rect->x; x < _Rect->x + _Rect->w; x++){
			for (int y = _Rect->y; y < _Rect->y + _Rect->h; y++){
				if (((unsigned int*)m_Map->pixels)[m_Map->w * (y)+x] >TRANSPARENCY){
					if (((unsigned int*)m_Map->pixels)[m_Map->w * (y + 1) + x] == 0
						|| ((unsigned int*)m_Map->pixels)[m_Map->w * (y - 1) + x] == 0){
						double TmpY = y;
						if (first)
							Slope = Slope + (TmpY - PreviousY);
						else
							first = true;
						PreviousY = TmpY;
						PointsSignificatifs++;
						y = _Rect->y + _Rect->h;
					}
				}
			}
		}
		double Angle = atan(Slope / (PointsSignificatifs - 1));
		if (Angle < 0){
			Angle = Angle + 2 * M_PI;
		}

		return Angle;
	}

	/*!
	@method Slide
	@brief  Fonction qui donne la trajectoire d'un glissement
	@param _Vector: Vitesse et direction initial du glissement
	@param _X : Position initial de l'entité
	@return La trajectoire du glissement
	@discussion À FAIRE
	*/
	static CTrajectory * Slide(CPosition * _Vector, int _X, int _Y){
		return nullptr;
	}

	/*!
	@method Propulsion
	@brief  Retourne une trajectoire selon un vitesse de départ et un accélération
	@param _PosInit: Position initiale de l'objet subbisant la propulsion
	@param _Vit: Vitesse et direction initial du glissement
	@param _Acc: Position initial de l'entité
	@return La trajectoire de ala propuslion
	@discussion Aucune.
	*/
	static CTrajectory* Propulsion(CPosition* _PosInit, C2DVector* _Vit, C2DVector* _Acc){
		return new CTrajectory(_PosInit, _Vit, _Acc);
	}

	/*!
	@method Move
	@brief  Fonction qui ajuste la position suite à un mouvement sans accélération
	@param _Rect : Rectangle se déplaçant
	@param _Direction : Bool de la direction empruntée (true = gauche, false = droite))
	@return BLOCKED: Si l'entité est pognée
	@return MOVING: Si l'entité peut continuer
	@discussion Ne déplace actuellement que d'un pixel sur l'axe X, à changer si voulu La hauteur (en pixels) d'une pente "escaladable" en y sera à déterminer (actuellement 3 pixels)
	*/
	static int Move(SDL_Rect* _Rect, int _Direction){
		if (_Direction == LEFT){
			for (int i = 0; i < _Rect->h + 3; i++){
				if (!(((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect->y + i) + _Rect->x - 1] == 0)){
					if (i < _Rect->h - 3)
						return BLOCKED;
					else {
						if (i < _Rect->h){
							_Rect->y = _Rect->y - (_Rect->h - i);
						}
						else {
							bool Verif = true;
							for (int j = 0; j < _Rect->w; j++){
								if ((((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect->y + _Rect->h) + _Rect->x + j - 1] != 0)){
									Verif = true;
									j = _Rect->w;
								}
							}
							if (Verif)
								_Rect->y = _Rect->y + (_Rect->h - i);
						}
					}
				}
			}
			_Rect->x = _Rect->x - 1;
			return MOVING;
		}
		else{
			for (int i = 0; i < _Rect->h + 3; i++){
				if (!(((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect->y + i) + _Rect->x + _Rect->w] == 0)){
					if (i < _Rect->h - 3)
						return BLOCKED;
					else {
						if (i < _Rect->h){
							_Rect->y = _Rect->y - (_Rect->h - i);
						}
						else {
							bool Verif = true;
							for (int j = 0; j < _Rect->w; j++){
								if ((((unsigned int*)m_Map->pixels)[m_Map->w * (_Rect->y + _Rect->h) + _Rect->x + j - 1] != 0)){
									Verif = true;
									j = _Rect->w;
								}
							}
							if (Verif)
								_Rect->y = _Rect->y + (_Rect->h - i);
						}
					}
				}
			}
			_Rect->x = _Rect->x + 1;
			return MOVING;
		}
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	static C2DVector* GetWind(){
		return m_Wind;
	}
	static double GetGravity(){
		return m_Gravity;
	}
	static void setGravity(double _d){
		m_Gravity = _d;
	}
};
C2DVector * CPhysics::m_Wind = nullptr;
double CPhysics::m_Gravity = 1;
int CPhysics::m_MaxSpeed = 1;
int CPhysics::m_MaxWindSpeed = 50;
SDL_Surface * CPhysics::m_Map = nullptr;