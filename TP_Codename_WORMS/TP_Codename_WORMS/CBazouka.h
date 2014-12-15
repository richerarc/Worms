#ifndef TP_Codename_WORMS_CBazouka_h
#define TP_Codename_WORMS_CBazouka_h
/*
To Do:

*/



/*!
@CBazouka
@Classe permettant l'affichage et la rotation du bazouka
@MESSAGE IMPORTANT: la texture du bazouka loader devra être celle de droite sans quoi tout va être fucked up;
*/
class CBazouka{
private:
	//Données membres:
	SDL_Rect m_RectBazouka; //La pos du rectangle de l'objet
	SDL_Rect m_RectMissile; //Le rectangle du missile
	double iAngle; // L'angle de rotation
	SDL_Texture* m_pTextureBazouka; // Texture de l'image du Bazouka à afficher.
	SDL_Texture* m_pTextureMissile; // Texture de l'image du Missile à afficher.
	CExplosion* m_pExplosion;// Texture de l'image de l'explosion.
	bool boCharging; // Booléen pour vérifier si le bazouka se prepare a lancer un missile
	bool boIsRotated; // Booléen pour vérifier si le bazouka sera en rotation
	bool boIsLaunch; // Booléen pour vérifier si le bazouka lance un missile
	unsigned int m_uiPower; // Représente le power du missile.
	CPowerBar* m_PowerBar; // Représente une nouvelle barre de lancement
	CWorm* m_Worm; // Représente un pointeur de worm afin d'obtenir sa position et ses states
	SDL_RendererFlip m_flipType; // Représente le type de rotation effectuer sur le bazouka
	CMissiles* m_pMissile;
	float fPosXTempo;
	float fPosYTempo;
	int iPosXTampon;
	int iPosYTampon;
public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@param _Worm: Un pointeur vers le worm qui est focus
	@param _pTexture : Texture de l'image à afficher. NOTE: LA TEXTURE loader doit être celle de droite.
	*/
	CBazouka(SDL_Texture* _pTextureBazouka, SDL_Texture* _pTextureMissile, CExplosion* _pExplosion, CWorm* _pWorm){
		m_RectBazouka = _pWorm->getPosition();
		m_RectBazouka.w = 52;
		m_RectBazouka.h = 28;
		SDL_QueryTexture(_pTextureBazouka, NULL, NULL, &m_RectBazouka.w, &m_RectBazouka.h);//Texture du bazouka.
		SDL_QueryTexture(_pTextureMissile, NULL, NULL, &m_RectMissile.w, &m_RectMissile.h);//Texture du missile.
		m_pTextureBazouka = _pTextureBazouka;
		m_pTextureMissile = _pTextureMissile;
		m_pExplosion = _pExplosion;
		boCharging = false;
		boIsRotated = false;
		boIsLaunch = false;
		iAngle = 0;
		m_uiPower = 0;
		fPosXTempo = 0;
		fPosYTempo = 0;
		m_PowerBar = new CPowerBar(m_RectBazouka);
		m_PowerBar->setPowerLevel(m_uiPower);
		m_Worm = _pWorm;
		m_flipType = SDL_FLIP_NONE;
	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CBazouka(){
		delete m_PowerBar;
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
		if (boIsLaunch){
			m_pMissile->Draw(_pRenderer);
		}
	}

	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event* _Event){
		switch (_Event->type)
		{
		case SDL_KEYDOWN:
			switch (_Event->key.keysym.sym)
			{
			case SDLK_UP:
				boIsRotated = true;
				if (m_Worm->getWormState() == UsingBazzRight){
					if (iAngle != -90)
						iAngle -= 2;
				}
				if (m_Worm->getWormState() == UsingBazzLeft){
					if (iAngle != 90)
						iAngle += 2;
				}
				break;

			case SDLK_DOWN:
				boIsRotated = true;
				if (m_Worm->getWormState() == UsingBazzRight){
					if (iAngle != 90)
						iAngle += 2;
				}
				if (m_Worm->getWormState() == UsingBazzLeft){
					if (iAngle != -90)
						iAngle -= 2;
				}
				break;

			case SDLK_SPACE:
				m_PowerBar->SetPosition(m_RectBazouka.x, m_RectBazouka.y);
				boCharging = true;
				m_PowerBar->PowerUp();
				break;
			}
			break;

		case SDL_KEYUP:
			switch (_Event->key.keysym.sym)
			{

			case SDLK_UP:
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


			case SDLK_DOWN:
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

			case SDLK_SPACE:
				boIsLaunch = true;
				fPosXTempo = 53.9*cos(abs(DegToRad(iAngle - 15)));
				fPosYTempo = 53.9*sin(abs(DegToRad(iAngle - 15)));
				iPosXTampon = fPosXTempo;
				iPosYTampon = fPosYTempo;
				if (fPosXTempo > iPosXTampon + 0.5)
					iPosXTampon++;
				if (fPosYTempo > iPosYTampon + 0.5)
					iPosYTampon++;
				m_RectMissile.x = iPosXTampon;
				m_RectMissile.y = iPosYTampon;

				m_pMissile = new CMissiles(m_RectMissile, m_pTextureMissile, m_PowerBar->getPowerLevel(),m_pExplosion);
				m_pMissile->Move();
				m_PowerBar->setPowerLevel(m_uiPower);
				break;
			}
			break;
		default:
			break;

		}
	}
};

#endif
