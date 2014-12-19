#ifndef TP_Codename_WORMS_CEntity_h
#define TP_Codename_WORMS_CEntity_h

enum EntityStates { Chute = 100, Immobile = 101, Deplacement = 102 };


/*!
@CEntity
@Classe Abstraite représentant les entitées affectés par la physique.
*/
class CEntity{
protected:
	SDL_Rect m_RectPosition;	// Position de l'Entité
	bool m_boFocus;				// Indique si l'entité a le Focus
	CTrajectory* m_Trajectoire;	// Trajectoire de l'objet
	unsigned int m_EntityState;	// État actuel de l'objet
	SDL_Texture* m_pTexture;	// Texture de l'entité
	float m_Angle;
	CExplosion* m_pExplosion;  // Nuclear DATA
	int test;

public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _Rectpos: Position de l'entité
	@param _ArrowTexture: Texture de l'entité.
	@return Adresse mémoire de l'objet.
	@discussion Intialise un objet qui subbit les forces gravitationnelles.
	*/
	CEntity(SDL_Rect _RectPos, SDL_Texture* _EntityTexture, CExplosion* _Explosion){
		m_pExplosion = _Explosion;
		m_RectPosition = _RectPos;
		m_boFocus = false;
		m_Trajectoire = nullptr;
		m_EntityState = Chute;
		m_pTexture = _EntityTexture;
		m_Trajectoire = CPhysics::Propulsion(new CPosition(m_RectPosition.x, m_RectPosition.y), new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.f, 2.f), new C2DVector(m_RectPosition.x, m_RectPosition.y, double(0), double(CPhysics::GetGravity())));
		m_Angle = 0;
		test = 0;
	}

	/*!
	@method Destructeur:
	@brief Permet de détruire les objets créés en mémoire
	*/
	~CEntity(){
		if (m_Trajectoire != nullptr){
			delete m_Trajectoire;
			m_Trajectoire = nullptr;
		}
		if ((m_pExplosion != nullptr) && !((m_EntityState == 1000) || (m_EntityState == 1001))){
			delete m_pExplosion;
			m_pExplosion = nullptr;
		}
	}

	/*!
	@method Move
	@brief déplace l'objet selon sa trajectoire
	@param Aucun
	@return Aucun
	@discussion I HAVE NO IDEA WHY MY CODE WORKS.
	*/
	virtual void Move(){
		switch (m_EntityState) {
		case Immobile:
			if (m_Trajectoire->GetInitSpeed())
				m_Trajectoire->WipeOut();
			break;
		case Chute:
				m_Trajectoire->UpdatePosition();

				CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
				if (temp != nullptr)
				{
					if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY()))
						m_EntityState = Immobile;
					else
						m_EntityState = Chute;
					
					m_RectPosition.y = temp->getY();
					m_RectPosition.x = temp->getX();
					delete temp;
				}
				else{
					m_RectPosition.x = m_Trajectoire->GetActualPosition()->getX();
					m_RectPosition.y = m_Trajectoire->GetActualPosition()->getY();
				}
			break;
		}

		/*
		int iTemp = CPhysics::VerifyGroundCollision(m_RectPosition);
		if (iTemp != NOCONTACT)
		m_EntityState = Immobile;
		switch (m_EntityState) {
		case Immobile:
		if (m_Trajectoire->GetInitSpeed())
		m_Trajectoire->WipeOut();
		break;
		case Chute:
		m_Trajectoire->UpdatePosition();
		CPosition* temp =  CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
		if (temp != nullptr){
		m_RectPosition.y = temp->getY();
		m_RectPosition.x = temp->getX();
		}
		else{
		m_RectPosition.x = m_Trajectoire->GetActualPosition()->getX();
		m_RectPosition.y = m_Trajectoire->GetActualPosition()->getY();
		}
		delete temp;
		break;
		}
		*/
	}

	/*
	Method : VerifySliding
	Brief : Fonction qui retourne si l'entité est en glissade, et qui le fait glisser s'il devrait le faire
	Params :
		_Angle : Angle de la pente
	Return : true : L'entité glisse
	false : L'entité ne glisse pas
	*/
	bool VerifySliding(double _Angle){
		if (_Angle == 0.0){
			return false;
		}
		else {
			if (_Angle > 0.0){
				if (_Angle > M_PI/3){
					return true;
				}
			}
			else{
				if (_Angle < -M_PI / 3){
					return true;
				}
			}
		}
		return false;
	}

	/*
	Method : UpdateSlidePosition
	Brief : Fonction qui ajuste la position en considérant que l'entité est en train de glisser
	Params :
	Return : Position de l'entité à ce moment
	*/
	void setTrajectory(CTrajectory* _Trajectoire){
		m_Trajectoire = _Trajectoire;
	}

	void UpdateSlidePosition(){
		double dStartSlope = CPhysics::EvaluateSlope({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, 50 });
		bool boOnGround = false;
		int iDecalage = 0;
		if (dStartSlope < 0){
			for (int i = 0; i < m_RectPosition.w; i++){
				if (((unsigned int*)CPhysics::GetMap()->pixels)[CPhysics::GetMap()->w * (m_RectPosition.y + m_RectPosition.h-1) + m_RectPosition.x + i - iDecalage] > TRANSPARENCY && !boOnGround){
					iDecalage++;
				}
				else {
					iDecalage = m_RectPosition.w - iDecalage;
					i = m_RectPosition.w;
				}
			}
			
			m_RectPosition.x = m_RectPosition.x + iDecalage;
			m_Trajectoire->GetActualSpeed()->setComposanteXY(m_Trajectoire->GetActualSpeed()->getNorme() * cos(dStartSlope),
				m_Trajectoire->GetActualSpeed()->getNorme() * sin(dStartSlope));
			m_Trajectoire->GetInitSpeed()->setOrientation(dStartSlope + M_PI);
			m_Trajectoire->GetAcceleration()->setOrientation(dStartSlope + M_PI);
			m_Trajectoire->GetAcceleration()->setNorme(m_Trajectoire->GetAcceleration()->getNorme()/1.1);
		}
		else{
			for (int i = 0; i < m_RectPosition.w; i++){
				if (((unsigned int*)CPhysics::GetMap()->pixels)[CPhysics::GetMap()->w * (m_RectPosition.y + m_RectPosition.h-1) + m_RectPosition.x + i + iDecalage] > TRANSPARENCY && !boOnGround){
					iDecalage++;
				}
				else {
					iDecalage = m_RectPosition.w - iDecalage;
					i = m_RectPosition.w;
				}
			}
			
			m_RectPosition.x = m_RectPosition.x - iDecalage;
			m_Trajectoire->GetActualSpeed()->setComposanteXY(m_Trajectoire->GetActualSpeed()->getNorme() * cos(dStartSlope),
				m_Trajectoire->GetActualSpeed()->getNorme() * sin(dStartSlope));
			m_Trajectoire->GetInitSpeed()->setOrientation(dStartSlope);
			m_Trajectoire->GetAcceleration()->setOrientation(dStartSlope);
			m_Trajectoire->GetAcceleration()->setNorme(m_Trajectoire->GetAcceleration()->getNorme()/1.1);
		}
		m_Trajectoire->SetActualPos(m_RectPosition.x, m_RectPosition.y);
		test++;
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/
	SDL_Rect getPosition(){
		return m_RectPosition;
	}

	CTrajectory* getTrajectoire(){
		return m_Trajectoire;
	}

	bool isFocused(){
		return m_boFocus;
	}

	void setFocus(bool _Focus){
		m_boFocus = _Focus;
	}
	unsigned int getRayon(){
		return m_pExplosion->getRadius();
	}
	virtual void ReactToExplosion(int, int, int){};
	virtual void HandleEvent(SDL_Event){};
	
	virtual bool isOutOfBounds(){
		if ((m_RectPosition.x < 0) || (m_RectPosition.x > WIDTH) || (m_RectPosition.y > HEIGHT)){
			return true;
		}
		return false;
	}

};

#endif
