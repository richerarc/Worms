#ifndef TP_Codename_WORMS_CBazouka_h
#define TP_Codename_WORMS_CBazouka_h


/*!
@CBazouka
@Classe permettant l'affichage et la rotation du bazouka
*/
class CBazouka{
private:
	//Données membres:
	SDL_Rect m_Rect;			// La pos du rectangle de l'objet
	SDL_Rect m_RectSurface;		// La pos du rectangle de l'objet
	double iAngle;				// L'angle de rotation
	SDL_Texture* m_pTexture;	// Texture de l'image à afficher.
	bool m_boCharging;			// Booléen pour vérifier si le bazouka va lancer un missile
	bool boIsRotated;			// Booléen pour vérifier si le bazouka sera en rotation
	unsigned int m_uiPower;		// Représente le power du missile.
	CPowerBar* m_PowerBar;		// Barre de puissance.
public:

	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@param _ix _iy : la pos du bazouka (à modifier pour la pos du worms)
	@param _pTexture : texture de l'image à afficher.
	@Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets
	*/
	CBazouka(int _ix, int _iy, SDL_Texture* _pTexture){ // La position du bazouka devra être remplacer par la position du worms qui s'apprete  a attaquer.
		m_Rect.x = _ix;
		m_Rect.y = _iy;
		SDL_QueryTexture(_pTexture, NULL, NULL, &m_Rect.w, &m_Rect.h);//Dimension du bazooka
		m_pTexture = _pTexture;
		m_boCharging = false;
		boIsRotated = false;
		iAngle = 0;
		m_uiPower = 0;
		m_PowerBar = new CPowerBar(m_Rect);
	}

	/*!
	@method Destructeur:
	@brief Permet  de détruire les objets créés en mémoire
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

		if (!boIsRotated)
			SDL_RenderCopy(_pRenderer, m_pTexture, NULL, &m_Rect);
		else
			SDL_RenderCopyEx(_pRenderer, m_pTexture, NULL, &m_Rect, iAngle, NULL, SDL_FLIP_NONE);

		if (m_boCharging){
			m_PowerBar->Draw(_pRenderer);
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
				if (iAngle > -360)
					iAngle--;
				else{
					iAngle = 0;
					iAngle--;
				}
				boIsRotated = true;
				break;

			case SDLK_DOWN:
				iAngle++;
				if (iAngle > 360)
					iAngle = 0;
				boIsRotated = true;
				break;

			case SDLK_SPACE:
				m_PowerBar->SetPosition(m_Rect.x, m_Rect.y);
				m_boCharging = true;
				m_PowerBar->PowerUp();
				break;
			}
			break;

		case SDL_KEYUP:
			switch (_Event->key.keysym.sym)
			{
			case SDLK_UP:
				break;

			case SDLK_DOWN:
				break;

			case SDLK_SPACE:
				m_uiPower = m_PowerBar->getPowerLevel();
				break;
			}
			break;
			
		default:
			break;
		}
	}
};

#endif
