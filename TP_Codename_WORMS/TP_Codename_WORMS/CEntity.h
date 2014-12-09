#ifndef TP_Codename_WORMS_CEntity_h
#define TP_Codename_WORMS_CEntity_h

enum EntityStates { Chute = 100, Immobile = 101, Deplacement = 102 };


/*!
@CEntity
@Classe Abstraite repr�sentant les entit�es affect�s par la physique.
*/
class CEntity{
protected:
	SDL_Rect m_RectPosition;	// Position de l'Entit�
	bool m_boFocus;				// Indique si l'entit� a le Focus
	CTrajectory* m_Trajectoire;	// Trajectoire de l'objet
	unsigned int m_EntityState;	// �tat actuel de l'objet
	SDL_Texture* m_pTexture;	// Texture de l'entit�
public:

	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _Rectpos: Position de l'entit�
	@param _ArrowTexture: Texture de l'entit�.
	@return Adresse m�moire de l'objet.
	@discussion Intialise un objet qui subbit les forces gravitationnelles.
	*/
	CEntity(SDL_Rect _RectPos, SDL_Texture* _Texture){
		m_RectPosition = _RectPos;
		m_boFocus = false;
		m_Trajectoire = nullptr;
		m_EntityState = Chute;
		m_pTexture = _Texture;
		m_Trajectoire = CPhysics::Propulsion(new CPosition(m_RectPosition.x, m_RectPosition.y), new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.f, 2.f), new C2DVector(m_RectPosition.x, m_RectPosition.y, double(0), double(CPhysics::GetGravity())));
	}

	/*!
	@method Destructeur:
	@brief Permet de d�truire les objets cr��s en m�moire
	*/
	~CEntity(){
		if (m_Trajectoire)
			delete m_Trajectoire;
		m_Trajectoire = nullptr;
	}


	/*
	Method : VerifySliding
	Brief : Fonction qui retourne si l'entit� est en glissade, et qui le fait glisser s'il devrait le faire
	Params :
	Return : true : L'entit� glisse
	false : L'entit� ne glisse pas
	*/
	bool VerifySliding(){
		if (m_Trajectoire->IsSliding()){
			return true;
		}
		SDL_Rect* RectTmp = new SDL_Rect({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, 50 });
		double dStartSlope = CPhysics::EvaluateSlope(RectTmp);
		if (dStartSlope > M_PI / 2 && dStartSlope > 0 || dStartSlope > -M_PI / 2 && dStartSlope < 0){
			m_Trajectoire->StartSliding();
		}
		else {
			m_Trajectoire->StopSliding();
		}
		if (m_Trajectoire->GetActualSpeed()->getNorme() < 200)
			m_Trajectoire->StopSliding();
		return m_Trajectoire->IsSliding();
	}

	/*
	Method : UpdateSlidePosition
	Brief : Fonction qui ajuste la position en consid�rant que l'entit� est en train de glisser
	Params :
	Return : Position de l'entit� � ce moment
	*/
	void UpdateSlidePosition(){
		m_Trajectoire->UpdatePosition();
		SDL_Rect* RectTmp = new SDL_Rect({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, 50 });
		double dStartSlope = CPhysics::EvaluateSlope(RectTmp);
		delete RectTmp;
		bool boOnGround = false;
		int iDecalage = 0;
		if (dStartSlope < 0){ //Va vers la gauche...
			while (!boOnGround){
				for (int i = 0; i < m_RectPosition.w; i++){
					if (((unsigned int*)CPhysics::GetMap()->pixels)[CPhysics::GetMap()->w * (m_RectPosition.y + m_RectPosition.h - 1) + m_RectPosition.x + i - iDecalage] > TRANSPARENCY){
						iDecalage++;
						i = m_RectPosition.w;
					}
					else {
						boOnGround = true;
					}
				}
			}
			m_RectPosition.x = m_RectPosition.x - iDecalage;
			m_RectPosition.y = m_Trajectoire->GetActualPosition()->getY();
			C2DVector* TmpSpeed = new C2DVector(m_RectPosition.x, m_RectPosition.x,
				m_Trajectoire->GetActualSpeed()->getNorme() * cos(dStartSlope),
				m_Trajectoire->GetActualSpeed()->getNorme() * sin(dStartSlope));
			m_Trajectoire->setActualSpeed(TmpSpeed);
		}
		else{ //...ou vers la droite
			while (!boOnGround){
				for (int i = 0; i < m_RectPosition.w; i++){
					if (((unsigned int*)CPhysics::GetMap()->pixels)[CPhysics::GetMap()->w * (m_RectPosition.y + m_RectPosition.h - 1) + m_RectPosition.x + i + iDecalage] > TRANSPARENCY){
						iDecalage++;
						i = m_RectPosition.w;
					}
					else {
						boOnGround = true;
					}
				}
			}
			m_RectPosition.x = m_RectPosition.x + iDecalage;
			m_RectPosition.y = m_Trajectoire->GetActualPosition()->getY();
			C2DVector* TmpSpeed = new C2DVector(m_RectPosition.x, m_RectPosition.x,
				m_Trajectoire->GetActualSpeed()->getNorme() * cos(dStartSlope),
				m_Trajectoire->GetActualSpeed()->getNorme() * sin(dStartSlope));
			m_Trajectoire->setActualSpeed(TmpSpeed);
		}
		m_Trajectoire->SetActualPos(m_RectPosition.x, m_RectPosition.y);
	}


	/*!
	@method Move
	@brief d�place l'objet selon sa trajectoire
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
			if (!VerifySliding())
				m_Trajectoire->UpdatePosition();
			else
				UpdateSlidePosition();

				CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
				if (temp != nullptr)
				{
					if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY()))
						if (!VerifySliding())
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

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux donn�es membres.
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

	virtual void ReactToExplosion(int, int, int) = 0;
	virtual void HandleEvent(SDL_Event) = 0;

};

#endif
