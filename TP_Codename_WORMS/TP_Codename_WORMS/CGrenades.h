#ifndef TP_Codename_WORMS_CGrenades_h
#define TP_Codename_WORMS_CGrenades_h


/*!
@CGrenades
@Classe permettant la création d'une grenade
*/
class CGrenades : public CObjets{
private:
	//Données membres:
	CTimer* m_pTimer;//Déclaration d'une nouvelle minuterie pour le temps à écouler avant l'explosion.
	bool boBouncing;//Booléen pour vérifier les rebonds.
	int m_iAngle; //Un angle pour la rotation de la grenade.

public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _iRayon: le rayond d'explosion de l'objetole.
	@param _RectPos: la pos du rectangle de l'objet
	@param _pTexture : texture de l'image à afficher	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets.
	*/
	CGrenades(SDL_Rect _RectPos, SDL_Texture* _Texture, CExplosion* _Explosion, CTrajectory* _Trajectory) :CObjets(_RectPos, _Texture, _Explosion){
		m_pTimer = new CTimer();
		m_pTimer->SetTimer(500);
		boBouncing = false;
		delete m_Trajectoire;
		m_Trajectoire = nullptr;
		m_Trajectoire = _Trajectory;
		m_EntityState = Chute;
		m_iAngle = 0;

	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead.
	*/
	~CGrenades(){
		if (m_pTimer != nullptr){
			delete m_pTimer;
			m_pTimer = nullptr;
		}
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre le sprite de la grenade
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
		if (!m_boIsexploded){
			Move();
			if (m_EntityState != Immobile){
				if (m_EntityState == GrenadeLaunchLeft)
					m_iAngle -= 4;
				else
					m_iAngle += 4;
			}
			SDL_RenderCopyEx(_pRenderer, m_pTexture, NULL, &m_RectPosition,m_iAngle,NULL,SDL_FLIP_NONE);
		}
		else{
			m_pExplosion->setPositionXY(m_RectPosition.x + 14, m_RectPosition.y + 8);
			m_pExplosion->startExplosion();
			m_pExplosion->ExplodeMap(_pRenderer);
			m_pExplosion->Draw(_pRenderer);
			if (m_pExplosion->IsDone()){
				m_boHasExplosed = true;
				m_pExplosion->ExplodeMap(_pRenderer);
				CEntity::m_uiCurrentNbrOfEntityExplosed++;
			}
		}
	}

	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event _Event){
	}

	/*!
	@Méthode:
	@ReactToExplosion
	@Permet de calculer les dommages subit par l'explosion
	*/
	void ReactToExplosion(int _iX, int _iY, int _iRayon){}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/
	

	void setExplosion(bool _boSet){
		m_boIsexploded = _boSet;
	}

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}


	void Move(){
		if (boBouncing && !m_pTimer->HasStarted()){
			m_pTimer->Start();
		}
		if (m_pTimer->IsElapsed()){
			m_boIsexploded = true;
		}
		switch (m_EntityState){
		case Immobile:
			break;
		case Chute:
			if (m_Trajectoire == nullptr){
				m_Trajectoire = new CTrajectory(new CPosition(m_RectPosition.x, m_RectPosition.y), new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.f,0.f), new C2DVector(m_RectPosition.x, m_RectPosition.y, CPhysics::GetWind()->getComposanteX(), CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()));
			}
			m_Trajectoire->UpdatePosition();
			CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
			if (temp != nullptr)
			{
				if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
					double SpeedNorm = m_Trajectoire->GetActualSpeed()->getNorme();
					double Slope = CPhysics::EvaluateSlope({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, 50 });
					if (boBouncing){
						if (VerifySliding(Slope)){
							UpdateSlidePosition();
						}
						else {
							m_EntityState = Immobile;
							boBouncing = false;
							delete m_Trajectoire;
							m_Trajectoire = nullptr;
						}
					}
					else {
						m_Trajectoire->Bounce(Slope);
						boBouncing = true;
					}
				}
				else{
					m_EntityState = Chute;
				}

				m_RectPosition.y = temp->getY();
				m_RectPosition.x = temp->getX();
		//		delete temp;
			}
			else{
				m_RectPosition.x = m_Trajectoire->GetActualPosition()->getX();
				m_RectPosition.y = m_Trajectoire->GetActualPosition()->getY();
			}
			break;
		}
	}
	
	void setState(int _EntityState){
		m_EntityState = _EntityState;
	}

};

#endif
