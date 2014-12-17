#ifndef TP_Codename_WORMS_CGrenades_h
#define TP_Codename_WORMS_CGrenades_h


/*!
@CGrenades
@Classe permettant la création d'une grenade
*/
class CGrenades : public CObjets{
private:
	//Données membres:
	CTimer* m_pTimer;	// Déclaration d'une nouvelle minuterie pour le temps à écouler avant l'explosion.
	bool boBouncing; //Nom assez explicite
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _iRayon: le rayond d'explosion de l'objetole.
	@param _RectPos: la pos du rectangle de l'objet
	@param _pTexture : texture de l'image à afficher	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets.
	*/
	CGrenades(SDL_Rect _RectPos, SDL_Texture* _Texture, CExplosion* _Explosion) :CObjets(_RectPos, _Texture, _Explosion){
		m_pTimer = new CTimer();
		m_pTimer->SetTimer(500);
		boBouncing = false;
	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead.
	*/
	~CGrenades(){
		delete m_pTimer;
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre le sprite de la grenade
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
		if (!m_boIsexploded){
			SDL_RenderCopy(_pRenderer, m_pTexture, NULL, &m_RectPosition);
		}
		else{
			m_pExplosion->setPositionXY(m_RectPosition.x + 14, m_RectPosition.y + 8);
			m_pExplosion->startExplosion();
			m_pExplosion->ExplodeMap(_pRenderer);
			m_pExplosion->Draw(_pRenderer);
			if (m_pExplosion->IsDone()){
				m_boHasExplosed = true;
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
			if (m_Trajectoire->GetInitSpeed())
				m_Trajectoire->WipeOut();
			break;
		case Chute:
			if (m_Trajectoire->GetRebonds() == 1){
				char* tamere = "en short";
			}
			m_Trajectoire->UpdatePosition();
			

			CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
			if (temp != nullptr)
			{
				if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
					double SpeedNorm = m_Trajectoire->GetActualSpeed()->getNorme();
					double Slope = CPhysics::EvaluateSlope({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, 50 });
					if (SpeedNorm < 1. || boBouncing){
						if (m_Trajectoire->GetRebonds() > 1){
							int a = 0;
						}
							//if (VerifySliding()){
							//UpdateSlidePosition();
						//}
						//else{
							//double Slope = CPhysics::EvaluateSlope({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, 50 });
							//if (Slope < M_PI / 4 && Slope > 0 || Slope < -M_PI / 4 && Slope < 0){
						m_EntityState = Immobile;
							//}
						//}
					}
					else {
						m_Trajectoire->Bounce(Slope);
						boBouncing = true;
						/*
						SDL_Rect Impact = { m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, 50 };
						m_Trajectoire->Bounce(0);
						*/
						/*
						int iCollision = CPhysics::VerifyGroundCollision(m_RectPosition);
						if (iCollision != NOCONTACT){

						m_Trajectoire->Bounce(Slope);
						boBouncing = true;
						m_Trajectoire->GetTest()->Start();
						//m_Trajectoire->Restart();
						
							/*
							int iCollision = CPhysics::VerifyGroundCollision(m_RectPosition);
							if (iCollision != NOCONTACT){

							if (iCollision == GROUND){
							SDL_Rect* Impact = new SDL_Rect({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, 50 });
							m_Trajectoire->Bounce(CPhysics::EvaluateSlope(Impact));
							delete Impact;
							}
							}
							*/
					}
				}
				else{
					m_EntityState = Chute;
					if (boBouncing){
						int dsfcghfbd = 4567932;
					}
					//boBouncing = false;
				}

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
		int iCollision = CPhysics::VerifyGroundCollision(m_RectPosition);
		if (iCollision != NOCONTACT){
			if (iCollision == GROUND){
				SDL_Rect* Impact = new SDL_Rect({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, 50});
				m_Trajectoire->Bounce(CPhysics::EvaluateSlope(Impact));
				delete Impact;
			}
		}
		m_Trajectoire->UpdatePosition();
		int iX = m_Trajectoire->GetActualPosition()->getX();
		int iY = m_Trajectoire->GetActualPosition()->getY();
		m_RectPosition.x = iX;
		m_RectPosition.y = iY;
		*/
	}

};

#endif
