#ifndef TP_Codename_WORMS_CEntity_h
#define TP_Codename_WORMS_CEntity_h

enum EntityStates {Chute = 100, Immobile = 101, Deplacement = 102};


/*!
@CEntity
@Classe Abstraite représentant les entitées affectés par la physique.
*/
class CEntity{
protected:
	SDL_Rect m_RectPosition; // Position de l'Entité
	bool m_boFocus;			 // Indique si l'entité a le Focus
	CTrajectory* m_Trajectoire;
	unsigned int m_EntityState;
	SDL_Texture* m_pTexture;
	C2DVector* m_pForce;
public:

	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@Paramètres:
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
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CEntity(){
		if (m_Trajectoire)
			delete m_Trajectoire;
		m_Trajectoire = nullptr;
	}
	
	virtual void Move(){
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
	}

	/*!
	@Accesseurs:
	*/
	SDL_Rect getPosition(){
		return m_RectPosition;
	}

	bool isFocused(){
		return m_boFocus;
	}

	void setFocus(bool _Focus){
		m_boFocus = _Focus;
	}

	virtual void ReactToExplosion(int,int,int) = 0;
	virtual void HandleEvent(SDL_Event) = 0;

};

#endif
