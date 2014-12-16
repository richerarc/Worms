#ifndef TP_Codename_WORMS_CMissiles_h
#define TP_Codename_WORMS_CMissiles_h
enum MissileStates { BazzLeft, BazzRight };
/*!
@CMissiles
@Classe permettant la création d'un missile
*/
class CMissiles : public CObjets{
private:
	//Données membres:
	bool boHasExplosed; //Donnée représentant si l'objet a explosé
	bool boIsexploded; //Donnée représentant si l'objet va explosé (true) ou non (false).
	int m_iPower; // Donnée représentant le power du missile donné par le bazouka.
	int m_iAngle; // Donnée représentant l'angle d'inclinaison du bazouka.
public:


	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _RectPos: la pos du rectangle de l'objet
	@param _Texture: la texture du missile
	@param _iPower: le power du missile
	@param _iAngle : l'angle d'inclinaison du missile
	@param _Explosion: un pointeur vers la classe explosion
	@param _uiMissileState: l'état du missile (gauche - droite)
	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets
	*/
	CMissiles(SDL_Rect _RectPos, SDL_Texture* _Texture, int _iPower, int _iAngle, CExplosion* _Explosion, int _uiMissileState) :CObjets(_RectPos, _Texture, _Explosion){
		boIsexploded = false;
		boHasExplosed = false;
		m_iPower = _iPower;
		m_iAngle = _iAngle;
		m_Trajectoire = nullptr;
		m_EntityState = _uiMissileState;
	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead.
	*/
	~CMissiles(){
	}

	void Move(){
		if (m_Trajectoire == nullptr){
			if (m_EntityState == BazzLeft){
				if (m_iAngle<0)
					m_Trajectoire = CPhysics::Propulsion((new CPosition((double)m_RectPosition.x, (double)m_RectPosition.y)), (new C2DVector(m_RectPosition.x, m_RectPosition.y, 10 * m_iPower * cos(DegToRad(m_iAngle)), 10 * m_iPower* sin(DegToRad(m_iAngle)))), (new C2DVector(m_RectPosition.x, m_RectPosition.y, CPhysics::GetWind()->getComposanteX(), CPhysics::GetGravity())));
				else
					m_Trajectoire = CPhysics::Propulsion((new CPosition((double)m_RectPosition.x, (double)m_RectPosition.y)), (new C2DVector(m_RectPosition.x, m_RectPosition.y, 10 * m_iPower * cos(DegToRad(m_iAngle)), 10 * m_iPower * sin(DegToRad(m_iAngle)))), (new C2DVector(m_RectPosition.x, m_RectPosition.y, CPhysics::GetWind()->getComposanteX(), CPhysics::GetGravity())));
			}
			if (m_EntityState == BazzRight){
				if (m_iAngle>0)
					m_Trajectoire = CPhysics::Propulsion((new CPosition((double)m_RectPosition.x, (double)m_RectPosition.y)), (new C2DVector(m_RectPosition.x, m_RectPosition.y, -10 * m_iPower * cos(DegToRad(m_iAngle)), -10 * m_iPower * sin(DegToRad(m_iAngle)))), (new C2DVector(m_RectPosition.x, m_RectPosition.y, CPhysics::GetWind()->getComposanteX(), CPhysics::GetGravity())));
				else
					m_Trajectoire = CPhysics::Propulsion((new CPosition((double)m_RectPosition.x, (double)m_RectPosition.y)), (new C2DVector(m_RectPosition.x, m_RectPosition.y, -10 * m_iPower * cos(DegToRad(m_iAngle)), -10 * m_iPower * sin(DegToRad(m_iAngle)))), (new C2DVector(m_RectPosition.x, m_RectPosition.y, CPhysics::GetWind()->getComposanteX(), CPhysics::GetGravity())));
			}
		}

		m_Trajectoire->UpdatePosition();
		CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
		if (temp != nullptr){
			if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY()))
				boIsexploded = true;

			m_RectPosition.y = temp->getY();
			m_RectPosition.x = temp->getX();

		}
		else{
			m_RectPosition.x = m_Trajectoire->GetActualPosition()->getX();
			m_RectPosition.y = m_Trajectoire->GetActualPosition()->getY();
		}
	}

/*!
@method Draw
@param _Renderer : Renderer pour rendre la texture du missile
@return null
*/

void Draw(SDL_Renderer* _pRenderer){
	if (!boIsexploded){
		Move();
		SDL_RenderCopyEx(_pRenderer, m_pTexture, NULL, &m_RectPosition, DegToRad(m_Trajectoire->GetInitSpeed()->getOrientation()), NULL, SDL_FLIP_NONE);
	}
	else{
		m_pExplosion->setPositionXY(m_RectPosition.x + 14, m_RectPosition.y + 8);
		m_pExplosion->startExplosion();
		m_pExplosion->Draw(_pRenderer);
		if (m_pExplosion->IsDone()){
			m_pExplosion->ExplodeMap(_pRenderer);
			boHasExplosed = true;
		}


	}
}

/*!
@method HandleEvent
@param _Event : Un SDL_Event pour traiter les evenement
@return null
*/
void HandleEvent(SDL_Event _Event){
	m_boFocus = true;
}

/*!
@method Acesseurs
@brief Servent a acceder/modifier aux données membres.
*/

void setPos(int _ix, int _iy){
	m_RectPosition.x = _ix;
	m_RectPosition.y = _iy;
}

bool IsExploded(){
	return boHasExplosed;
}
void setExplosion(bool _boSet){
	boIsexploded = _boSet;
}


};

#endif
