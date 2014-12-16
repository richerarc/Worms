#ifndef TP_Codename_WORMS_CMissiles_h
#define TP_Codename_WORMS_CMissiles_h


/*!
@CMissiles
@Classe permettant la création d'un missile
*/
class CMissiles : public CObjets{
private:
	//Données membres:
	bool boIsexploded; //Donnée représentant si l'objet est explosé (true) ou non (false)
	int m_uiPower; // Donnée représentant le power passer par la CPowerBarre
	int m_uiAngle; // Angle du bazouka
public:


	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _iRayon: le rayond d'explosion de l'objet
	@param _RectPos: la pos du rectangle de l'objet
	@param _pTexture : texture de l'image à afficher
	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets
	*/

	CMissiles(SDL_Rect _RectPos, SDL_Texture* _Texture, int _uiPower, CExplosion* _Explosion) :CObjets( _RectPos, _Texture, _Explosion){
		boIsexploded = false;
		m_uiPower = _uiPower;
		m_uiAngle = _uiAngle;
		m_Trajectoire = nullptr;
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
			m_Trajectoire = CPhysics::Propulsion((new CPosition((double)m_RectPosition.x, (double)m_RectPosition.y)), (new C2DVector(m_RectPosition.x, m_RectPosition.y, 10 * m_uiPower * cos(DegToRad(m_uiAngle)), m_uiPower * sin(DegToRad(m_uiAngle)))), (new C2DVector(m_RectPosition.x, m_RectPosition.y, CPhysics::GetWind()->getComposanteX(), CPhysics::GetGravity())));
		}
		m_Trajectoire->UpdatePosition();
		m_RectPosition.x = m_Trajectoire->GetActualPosition()->getX();
		m_RectPosition.y = m_Trajectoire->GetActualPosition()->getY();
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture du missile
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
		Move();
		SDL_RenderCopy(_pRenderer, m_pTexture, NULL, &m_RectPosition);
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
	@Méthode:
	@ReactToExplosion
	@Permet de calculer les dommages subit par l'explosion
	*/
	void ReactToExplosion(int _iX, int _iY, int _iRayon){}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}

	bool IsItexploded(){
		return boIsexploded;
	}

	void setExplosion(bool _boSet){
		boIsexploded = _boSet;
	}


};

#endif
