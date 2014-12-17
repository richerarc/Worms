#ifndef TP_Codename_WORMS_CGrenades_h
#define TP_Codename_WORMS_CGrenades_h


/*!
@CGrenades
@Classe permettant la cr�ation d'une grenade
*/
class CGrenades : public CObjets{
private:
	//Donn�es membres:
	CTimer* m_pTimer;	// D�claration d'une nouvelle minuterie pour le temps � �couler avant l'explosion.
	bool boIsexploded;	// Donn�e repr�sentant si l'objet est explos� (true) ou non (false)
	bool boBouncing; //Nom assez explicite

public:

	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _iRayon: le rayond d'explosion de l'objetole.
	@param _RectPos: la pos du rectangle de l'objet
	@param _pTexture : texture de l'image � afficher	@return Adresse m�moire de l'objet.
	@discussion Classe h�ritant de CObjets, elle prend donc les param�tres du constructeur CObjets.
	*/
	CGrenades(SDL_Rect _RectPos, SDL_Texture* _Texture, CExplosion* _Explosion) :CObjets(_RectPos, _Texture, _Explosion){
		m_pTimer = new CTimer();
		m_pTimer->SetTimer(1000);
		m_pTimer->Start();
		boIsexploded = false;
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
		SDL_RenderCopy(_pRenderer, m_pTexture, NULL, &m_RectPosition);
	}

	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event _Event){
		m_boFocus = true;
		if (m_pTimer->IsElapsed())
			boIsexploded = true;
	}

	/*!
	@M�thode:
	@ReactToExplosion
	@Permet de calculer les dommages subit par l'explosion
	*/
	void ReactToExplosion(int _iX, int _iY, int _iRayon){}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux donn�es membres.
	*/

	bool IsItexploded(){
		return boIsexploded;
	}

	void setExplosion(bool _boSet){
		boIsexploded = _boSet;
	}

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}


	void Move(){
		switch (m_EntityState){
		case Immobile:
			if (m_Trajectoire->GetInitSpeed())
				m_Trajectoire->WipeOut();
			break;
		case Chute:
			if (m_Trajectoire->GetRebonds() == 1){
				int tamere = 0;
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
						}
							//UpdateSlidePosition();
						//}
						//else{
							//double Slope = CPhysics::EvaluateSlope({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, 50 });
							//if (Slope < M_PI / 4 && Slope > 0 || Slope < -M_PI / 4 && Slope < 0){
					}
					else {
						if (VerifySliding(Slope)){
							UpdateSlidePosition();
						}
						else{
							m_Trajectoire->Bounce(Slope);
							boBouncing = true;
						}
					}
				}
				else{
					m_EntityState = Chute;
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
	}

};

#endif
