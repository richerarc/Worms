#ifndef TP_Codename_WORMS_CBazouka_h
#define TP_Codename_WORMS_CBazouka_h
/*!
@CBazouka
@Classe permettant l'affichage et la rotation du bazouka
@MESSAGE IMPORTANT: la texture du bazouka loader devra être celle de droite sans quoi tout va être fucked up;
*/
class CBazouka{
private:
	//Données membres:
	SDL_Rect m_RectBazouka;				//La pos du rectangle de l'objet
	SDL_Rect m_RectMissile;				//Le rectangle du missile
	double iAngle;						// L'angle de rotation
	SDL_Texture* m_pTextureBazouka;		// Texture de l'image du Bazouka à afficher.
	SDL_Texture* m_pTextureMissile;		// Texture de l'image du Missile à afficher.
	CExplosion* m_pExplosion;			// Texture de l'image de l'explosion.
	bool boCharging;					// Booléen pour vérifier si le bazouka se prepare a lancer un missile
	bool boIsRotated;					// Booléen pour vérifier si le bazouka sera en rotation
	bool boIsLaunch;					// Booléen pour vérifier si le bazouka lance un missile
	bool boHasLaunch;					// Booléen pour vérifier si le bazouka a lancé un missile
	bool boMissileIsExploded;			// Booléen pour savoir si le missile à explosé
	unsigned int m_uiPower;				// Représente le power du missile.
	CPowerBar* m_PowerBar;				// Représente une nouvelle barre de lancement
	CWorm* m_Worm;						// Représente un pointeur de worm afin d'obtenir sa position et ses states
	SDL_RendererFlip m_flipType;		// Représente le type de rotation effectuer sur le bazouka
	CMissiles* m_pMissile;				// Représente un missile
	float fPosXTempo;
	float fPosYTempo;
	int iPosXTampon;
	int iPosYTampon;
	unsigned int m_uiRayon;				// Représente le rayon d'explosion
	bool m_boInUse;						// Représente si le bazouka est en utilisation
public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@param _Worm: Un pointeur vers le worm qui est focus
	@param _pTexture : Texture de l'image à afficher. NOTE: LA TEXTURE loader doit être celle de droite.
	*/
	CBazouka(SDL_Texture* _pTextureBazouka, SDL_Texture* _pTextureMissile, CExplosion* _pExplosion, CWorm* _pWorm){
		m_RectBazouka = {0,0,0,0};
		SDL_QueryTexture(_pTextureBazouka, NULL, NULL, &m_RectBazouka.w, &m_RectBazouka.h);//Texture du bazouka.
		SDL_QueryTexture(_pTextureMissile, NULL, NULL, &m_RectMissile.w, &m_RectMissile.h);//Texture du missile.
		m_pTextureBazouka = _pTextureBazouka;
		m_pTextureMissile = _pTextureMissile;
		m_pExplosion = _pExplosion;
		boCharging = false;
		boIsRotated = false;
		boIsLaunch = false;
		boHasLaunch = false;
		boMissileIsExploded = false;
		m_boInUse = false;
		iAngle = 0;
		m_uiPower = 0;
		fPosXTempo = 0;
		fPosYTempo = 0;
		m_flipType = SDL_FLIP_NONE;
		m_PowerBar = new CPowerBar(m_RectBazouka);
		m_PowerBar->setPowerLevel(m_uiPower);
		m_Worm = _pWorm;
		m_uiRayon = m_pExplosion->getRadius();
		m_pMissile = nullptr;
	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CBazouka(){
		if (m_PowerBar != nullptr){
			delete m_PowerBar;
			m_PowerBar = nullptr;
		}
	}
	/*!
	@method setBazooka
	@brief: Permet de seter le bazouka à l'endroit où se trouve le worm jouant
	@param _ActualWorm: le worm jouant.
	@return null
	*/
	void setBazooka(CWorm* _ActualWorm){
		m_Worm = _ActualWorm;
		m_RectBazouka.x = m_Worm->getPosition().x;
		m_RectBazouka.y = m_Worm->getPosition().y + 20;
		m_PowerBar->SetPosition(m_RectBazouka.x, m_RectBazouka.y);
	}
	
	/*!
	@methodRender
	@param _pRenderer : Renderer pour rendre la texture du bazouka
	@return null
	*/
	void Render(SDL_Renderer* _pRenderer){
		if (!boIsRotated){
			if (m_Worm->getWormState() == UsingBazzRight)
				SDL_RenderCopyEx(_pRenderer, m_pTextureBazouka, NULL, &m_RectBazouka, iAngle, NULL, SDL_FLIP_NONE);
			if (m_Worm->getWormState() == UsingBazzLeft){
				SDL_RenderCopyEx(_pRenderer, m_pTextureBazouka, NULL, &m_RectBazouka, iAngle, NULL, SDL_FLIP_HORIZONTAL);
				m_flipType = SDL_FLIP_HORIZONTAL;
			}
		}
		else{
			if (m_Worm->getWormState() == UsingBazzRight){
				SDL_RenderCopyEx(_pRenderer, m_pTextureBazouka, NULL, &m_RectBazouka, iAngle, NULL, m_flipType);
			}
			if (m_Worm->getWormState() == UsingBazzLeft){
				SDL_RenderCopyEx(_pRenderer, m_pTextureBazouka, NULL, &m_RectBazouka, iAngle, NULL, m_flipType);
				
			}
		}
		if (boCharging){
			m_PowerBar->Draw(_pRenderer);
		}
		if ((m_pMissile != nullptr) && boIsLaunch){
			
			m_pMissile->Draw(_pRenderer);
			if (m_pMissile->HasExploded() || m_pMissile->isOutOfBounds()){
				if (m_pMissile->isOutOfBounds())
					m_pMissile->setExplosion(true);
				InitInfoMissile();
				delete m_pMissile;
				m_pMissile = nullptr;
				boHasLaunch = false;
			}
		}
	}

	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event _Event){
		if (!boHasLaunch) {
			switch (_Event.type)
			{
			case SDL_KEYDOWN:
				switch (_Event.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
					boIsRotated = true;
					if (m_Worm->getWormState() == UsingBazzRight){
						if (iAngle != -90)
							iAngle -= 4;
					}
					if (m_Worm->getWormState() == UsingBazzLeft){
						if (iAngle != 90)
							iAngle += 4;
					}
					break;

				case SDL_SCANCODE_DOWN:
					boIsRotated = true;
					if (m_Worm->getWormState() == UsingBazzRight){
						if (iAngle != 90)
							iAngle += 4;
					}
					if (m_Worm->getWormState() == UsingBazzLeft){
						if (iAngle != -90)
							iAngle -= 4;
					}
					break;

				case SDL_SCANCODE_SPACE:
					boCharging = true;
					m_PowerBar->PowerUp();
					break;
				}
				break;

			case SDL_KEYUP:
				switch (_Event.key.keysym.scancode)
				{

				case SDL_SCANCODE_UP:
					if (m_Worm->getWormState() == UsingBazzRight){
						if (iAngle == -90){
							iAngle = 90;
							m_Worm->setWormState(UsingBazzLeft);
							m_flipType = SDL_FLIP_HORIZONTAL;
							break;
						}
					}

					if (m_Worm->getWormState() == UsingBazzLeft){
						if (iAngle == 90){
							iAngle = -90;
							m_Worm->setWormState(UsingBazzRight);
							m_flipType = SDL_FLIP_NONE;
							break;
						}
					}
					break;


				case SDL_SCANCODE_DOWN:
					if (m_Worm->getWormState() == UsingBazzRight){
						if (iAngle == 90){
							iAngle = -90;
							m_Worm->setWormState(UsingBazzLeft);
							m_flipType = SDL_FLIP_HORIZONTAL;
							break;
						}
					}
					if (m_Worm->getWormState() == UsingBazzLeft){
						if (iAngle == -90){
							iAngle = 90;
							m_Worm->setWormState(UsingBazzRight);
							m_flipType = SDL_FLIP_NONE;
							break;
						}
					}
					break;

				case SDL_SCANCODE_SPACE:
					boIsLaunch = true;
					if (m_Worm->getWormState() == UsingBazzLeft){
						fPosYTempo = m_RectBazouka.y + (-20 * sin(DegToRad(iAngle)));
						fPosXTempo = m_RectBazouka.x + (-20 * cos(DegToRad(iAngle)));
						iPosXTampon = fPosXTempo;
						iPosYTampon = fPosYTempo;
						if (fPosXTempo > iPosXTampon + 2.5)
							iPosXTampon++;
						if (fPosYTempo > iPosYTampon + 2.5)
							iPosYTampon++;
						m_RectMissile.x = iPosXTampon;
						m_RectMissile.y = iPosYTampon;
						m_pMissile = new CMissiles(m_RectMissile, m_pTextureMissile, m_PowerBar->getPowerLevel(), iAngle, m_pExplosion, LaunchRight);
					}
					if (m_Worm->getWormState() == UsingBazzRight){
						fPosYTempo = m_RectBazouka.y + (40 * sin(DegToRad(iAngle)));
						fPosXTempo = m_RectBazouka.x + (49 * cos(DegToRad(iAngle)));
						iPosXTampon = fPosXTempo;
						iPosYTampon = fPosYTempo;
						if (fPosXTempo > iPosXTampon + 2.5)
							iPosXTampon++;
						if (fPosYTempo > iPosYTampon + 2.5)
							iPosYTampon++;
						m_RectMissile.x = iPosXTampon;
						m_RectMissile.y = iPosYTampon;
						m_pMissile = new CMissiles(m_RectMissile, m_pTextureMissile, m_PowerBar->getPowerLevel(), iAngle, m_pExplosion, LaunchLeft);

					}
					boHasLaunch = true;
					m_PowerBar->setPowerLevel(m_uiPower);

					break;
				case SDL_SCANCODE_LEFT:
					if (m_flipType != SDL_FLIP_HORIZONTAL){
						m_Worm->setWormState(UsingBazzLeft);
						m_flipType = SDL_FLIP_HORIZONTAL;
						iAngle = -iAngle;
					}
					break;
				case SDL_SCANCODE_RIGHT:
					if (m_flipType != SDL_FLIP_NONE){
						m_Worm->setWormState(UsingBazzRight);
						m_flipType = SDL_FLIP_NONE;
						iAngle = -iAngle;
					}

					break;
				}
				break;
			default:
				break;

			}
		}
	}
	/*!
	@method InitInfoMissile
	@brief: Permet d'acceder au information d'un missile explosé.
	@param null 
	@return null
	*/
	void InitInfoMissile(){
		if (m_pMissile->IsExploded()){
			boMissileIsExploded = true;
			m_uiRayon = m_pMissile->getRayon();
			m_RectMissile = m_pMissile->getPosition();

		}
	}

	/*!
	@method reset
	@brief: Permet de reseter les informations du bazouka
	@param null
	@return null
	*/
	void reset(){
		boCharging = false;
		boIsRotated = false;
		boIsLaunch = false;
		boMissileIsExploded = false;
		iAngle = 0;
		m_uiPower = 0;
		fPosXTempo = 0;
		fPosYTempo = 0;
		m_flipType = SDL_FLIP_NONE;
	}


	/*!
	@Accesseurs
	*/
	int getWormState(){return m_Worm->getWormState();}
	bool getIfLaunch(){return boHasLaunch;}
	bool MissileHasExploded(){return boMissileIsExploded;}
	bool MissileWillExplode(){
		if (m_pMissile)
			return m_pMissile->IsExploding();
		return true;}
	SDL_Rect MissilePos(){return m_RectMissile;}
	int MissileRayon(){return m_uiRayon;}
	void setInUse(bool _bo){m_boInUse = _bo;}
	void SetExplose(bool _boExplose){m_pMissile->setExplosion(_boExplose);}
	bool MissileExplosing(){return m_pExplosion->HasStarted();}
	CExplosion* getExplosion(){return m_pExplosion;}
	bool isInUse(){return m_boInUse;}
};

#endif
