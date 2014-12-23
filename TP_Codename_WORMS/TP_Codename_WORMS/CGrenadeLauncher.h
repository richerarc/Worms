#ifndef TP_Codename_WORMS_CGrenadeLauncher_h
#define TP_Codename_WORMS_CGrenadeLauncher_h




/*!
@CGrenadeLauncher
@Classe permettant l'affichage d'un lanceur de grenade
*/
class CGrenadeLauncher{
private:
	//Données membres:
	SDL_Rect m_RectGL;				//La pos du rectangle de l'objet
	SDL_Rect m_RectGrenade;			//Le rectangle de la grenade.
	SDL_Texture* m_pTextureGL;		//Texture de l'image du Bazouka à afficher.
	SDL_Texture* m_pTextureGrenade; //Texture de l'image du Missile à afficher.
	CExplosion* m_pExplosion;		//Texture de l'image de l'explosion.
	bool boCharging;				//Booléen pour vérifier si le GL se prepare a lancer un missile
	bool boIsRotated;				//Booléen pour vérifier si le GL sera en rotation
	bool boIsLaunch;				//Booléen pour vérifier si le GL lance un missile
	bool boHasLaunch;				//Booléen pour vérifier si le GL a lancé un missile
	bool boGrenadeIsExploded;		//Booléen pour savoir si la Grenade a explosée
	unsigned int m_uiPower;			//Représente le power du missile.
	CPowerBar* m_PowerBar;			//Représente une nouvelle barre de lancement
	CWorm* m_Worm;					//Représente un pointeur de worm afin d'obtenir sa position et ses states
	SDL_RendererFlip m_flipType;	//Représente le type de rotation effectuer sur le bazouka
	CGrenades* m_pGrenade;			//Un pointeur de grenade
	float fPosXTempo;				//Un float temporaire pour la position du lancer de grenade
	float fPosYTempo;				//Un float temporaire pour la position du lancer de grenade
	int iPosXTampon;				//Un int temporaire pour la position du lancer de grenade
	int iPosYTampon;				//Un int temporaire pour la position du lancer de grenade
	unsigned int m_uiRayon;			//Le rayon d'explosion de la grenade.
	double iAngle;					//L'angle de rotation du GL
	bool m_boInUse;					//Booléen pour vérifier si l'arme est en utilisation
public:

	/*!
	@Constructeur
	@Description:Permet d'initialiser les données membres
	@param _pTextureGL:La texture du grenade launcher
	@param _pTextureGrenade:La texture de la grenade
	@param _Worm: Un pointeur vers le worm qui est focus
	@param _pExplosion :Une nouvelle explosion
	*/
	CGrenadeLauncher(SDL_Texture* _pTextureGL, SDL_Texture* _pTextureGrenade, CExplosion* _pExplosion, CWorm* _pWorm){
		m_RectGL = { 0, 0, 0, 0 };
		SDL_QueryTexture(_pTextureGL, NULL, NULL, &m_RectGL.w, &m_RectGL.h);
		SDL_QueryTexture(_pTextureGrenade, NULL, NULL, &m_RectGrenade.w, &m_RectGrenade.h);
		m_pTextureGL = _pTextureGL;
		m_pTextureGrenade = _pTextureGrenade;
		m_pExplosion = _pExplosion;
		boCharging = false;
		boIsRotated = false;
		boIsLaunch = false;
		boGrenadeIsExploded = false;
		iAngle = 0;
		m_uiPower = 0;
		fPosXTempo = 0;
		fPosYTempo = 0;
		m_flipType = SDL_FLIP_NONE;
		m_PowerBar = new CPowerBar(m_RectGL);
		m_PowerBar->setPowerLevel(m_uiPower);
		m_Worm = _pWorm;
	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CGrenadeLauncher(){
		if (m_PowerBar != nullptr){
			delete m_PowerBar;
			m_PowerBar = nullptr;
		}
	}

	void setGrenadeLauncher(CWorm* _ActualWorm){
		m_Worm = _ActualWorm;
		m_RectGL.x = m_Worm->getPosition().x;
		m_RectGL.y = m_Worm->getPosition().y + 20;
		m_PowerBar->SetPosition(m_RectGL.x, m_RectGL.y);
	}

	/*!
	@method Render
	@brief Dessine sur la fenetre
	@param _pRenderer :Renderer pour rendre la texture du grenade launcher.
	@return null
	*/
	void Render(SDL_Renderer* _pRenderer){
		if (!boIsRotated){
			if (m_Worm->getWormState() == GrenadeLaunchRight)
				SDL_RenderCopyEx(_pRenderer, m_pTextureGL, NULL, &m_RectGL, iAngle, NULL, SDL_FLIP_NONE);
			if (m_Worm->getWormState() == GrenadeLaunchLeft){
				SDL_RenderCopyEx(_pRenderer, m_pTextureGL, NULL, &m_RectGL, iAngle, NULL, SDL_FLIP_HORIZONTAL);
				m_flipType = SDL_FLIP_HORIZONTAL;
			}
		}
		else{
			if (m_Worm->getWormState() == GrenadeLaunchRight){
				SDL_RenderCopyEx(_pRenderer, m_pTextureGL, NULL, &m_RectGL, iAngle, NULL, m_flipType);
			}
			if (m_Worm->getWormState() == GrenadeLaunchLeft){
				SDL_RenderCopyEx(_pRenderer, m_pTextureGL, NULL, &m_RectGL, iAngle, NULL, m_flipType);

			}
		}
		if (boCharging){
			m_PowerBar->Draw(_pRenderer);
		}
		if ((m_pGrenade != nullptr) && boIsLaunch){

			m_pGrenade->Draw(_pRenderer);
			if (m_pGrenade->HasExploded() || m_pGrenade->isOutOfBounds()){
				InitInfoGrenade();
				if (m_pGrenade->isOutOfBounds())
					m_pGrenade->setExplosion(true);
				delete m_pGrenade;
				m_pGrenade = nullptr;
			}
		}
	}

	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event _Event){
		switch (_Event.type)
		{
		case SDL_KEYDOWN:
			switch (_Event.key.keysym.scancode)
			{
			case SDL_SCANCODE_UP:
				boIsRotated = true;
				if (m_Worm->getWormState() == GrenadeLaunchRight){
					if (iAngle != -90)
						iAngle -= 4;
				}
				if (m_Worm->getWormState() == GrenadeLaunchLeft){
					if (iAngle != 90)
						iAngle += 4;
				}
				break;

			case SDL_SCANCODE_DOWN:
				boIsRotated = true;
				if (m_Worm->getWormState() == GrenadeLaunchRight){
					if (iAngle != 90)
						iAngle += 4;
				}
				if (m_Worm->getWormState() == GrenadeLaunchLeft){
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
				if (m_Worm->getWormState() == GrenadeLaunchRight){
					if (iAngle == -90){
						iAngle = 90;
						m_Worm->setWormState(GrenadeLaunchLeft);
						m_flipType = SDL_FLIP_HORIZONTAL;
						break;
					}
				}

				if (m_Worm->getWormState() == GrenadeLaunchLeft){
					if (iAngle == 90){
						iAngle = -90;
						m_Worm->setWormState(GrenadeLaunchRight);
						m_flipType = SDL_FLIP_NONE;
						break;
					}
				}
				break;
			case SDL_SCANCODE_DOWN:
				if (m_Worm->getWormState() == GrenadeLaunchRight){
					if (iAngle == 90){
						iAngle = -90;
						m_Worm->setWormState(GrenadeLaunchLeft);
						m_flipType = SDL_FLIP_HORIZONTAL;
						break;
					}
				}
				if (m_Worm->getWormState() == GrenadeLaunchLeft){
					if (iAngle == -90){
						iAngle = 90;
						m_Worm->setWormState(GrenadeLaunchRight);
						m_flipType = SDL_FLIP_NONE;
						break;
					}
				}
				break;
			case SDL_SCANCODE_SPACE:
				boIsLaunch = true;
				//
				if (m_Worm->getWormState() == GrenadeLaunchLeft){
					fPosYTempo = m_RectGL.y + (-20 * sin(DegToRad(iAngle)));
					fPosXTempo = m_RectGL.x + (-20 * cos(DegToRad(iAngle)));
					iPosXTampon = fPosXTempo;
					iPosYTampon = fPosYTempo;
					if (fPosXTempo > iPosXTampon + 0.5)
						iPosXTampon++;
					if (fPosYTempo > iPosYTampon + 0.5)
						iPosYTampon++;
					m_RectGrenade.x = iPosXTampon;
					m_RectGrenade.y = iPosYTampon;
					m_pGrenade = new CGrenades(m_RectGrenade, m_pTextureGrenade, m_pExplosion, CPhysics::Propulsion((new CPosition((double)m_RectGrenade.x, (double)m_RectGrenade.y)), (new C2DVector(m_RectGrenade.x, m_RectGrenade.y, -3 * (int)m_PowerBar->getPower() * cos(DegToRad(iAngle)), -5 * (int)m_PowerBar->getPower() * sin(DegToRad(iAngle)))), (new C2DVector(m_RectGrenade.x, m_RectGrenade.y, CPhysics::GetWind()->getComposanteX(), CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
					

					}
				if (m_Worm->getWormState() == GrenadeLaunchRight){
					fPosYTempo = m_RectGL.y + (26 * sin(DegToRad(iAngle)));
					fPosXTempo = m_RectGL.x + (45 * cos(DegToRad(iAngle)));
					iPosXTampon = fPosXTempo;
					iPosYTampon = fPosYTempo;
					if (fPosXTempo > iPosXTampon + 0.5)
						iPosXTampon++;
					if (fPosYTempo > iPosYTampon + 0.5)
						iPosYTampon++;
					m_RectGrenade.x = iPosXTampon;
					m_RectGrenade.y = iPosYTampon;
					m_pGrenade = new CGrenades(m_RectGrenade, m_pTextureGrenade, m_pExplosion, CPhysics::Propulsion((new CPosition((double)m_RectGrenade.x, (double)m_RectGrenade.y)), (new C2DVector(m_RectGrenade.x, m_RectGrenade.y, 3 * (int)m_PowerBar->getPower() * cos(DegToRad(iAngle)), 5 * (int)m_PowerBar->getPower() * sin(DegToRad(iAngle)))), (new C2DVector(m_RectGrenade.x, m_RectGrenade.y, CPhysics::GetWind()->getComposanteX(), CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
				}
				boHasLaunch = true;
				

				break;
			case SDL_SCANCODE_LEFT:
				if (m_flipType != SDL_FLIP_HORIZONTAL){
					m_Worm->setWormState(GrenadeLaunchLeft);
					m_flipType = SDL_FLIP_HORIZONTAL;
					iAngle = -iAngle;
				}
				break;
			case SDL_SCANCODE_RIGHT:
				if (m_flipType != SDL_FLIP_NONE){
					m_Worm->setWormState(GrenadeLaunchRight);
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

	void reset(){
		boCharging = false;
		boIsRotated = false;
		boIsLaunch = false;
		boGrenadeIsExploded = false;
		iAngle = 0;
		m_PowerBar->setPowerLevel(0);
		fPosXTempo = 0;
		fPosYTempo = 0;
		m_flipType = SDL_FLIP_NONE;
	}

	/*!
	@method InitInfoMissile
	@brief: Permet d'acceder au information d'un missile explosé.
	@param null
	@return null
	*/
	void InitInfoGrenade(){
		if (m_pGrenade->IsExploded()){
			boGrenadeIsExploded = true;
			m_uiRayon = m_pGrenade->getRayon();
			m_RectGrenade = m_pGrenade->getPosition();
			m_pGrenade->setState(LaunchLeft);
		}
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	int getWormState(){
		return m_Worm->getWormState();
	}

	bool getIfLaunch(){
		return boHasLaunch;
	}

	bool GrenadeHasExploded(){
		return boGrenadeIsExploded;
	}

	SDL_Rect GrenadePos(){
		return m_RectGrenade;
	}

	int GrenadeRayon(){
		return m_uiRayon;
	}

	void setInUse(bool _bo){
		m_boInUse = _bo;
	}

	bool isInUse(){
		return m_boInUse;
	}


	
	CExplosion* getExplosion(){return m_pExplosion;}
};

#endif
