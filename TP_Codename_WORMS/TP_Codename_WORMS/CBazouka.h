#ifndef TP_Codename_WORMS_CBazouka_h
#define TP_Codename_WORMS_CBazouka_h
/*
To Do:
- Handle Event case down
- Tester
*/

/*!
@CBazouka
@Classe permettant l'affichage et la rotation du bazouka
*/
class CBazouka{
private:
	//Données membres:
	SDL_Rect m_Rect; //La pos du rectangle de l'objet
	SDL_Rect m_RectSurface; //La pos du rectangle de l'objet
	double iAngle; // L'angle de rotation
	SDL_Texture* m_pTexture; // Texture de l'image à afficher.
	bool m_boCharging; // Booléen pour vérifier si le bazouka va lancer un missile
	unsigned int m_uiPower; // Représente le power du missile.
	CPowerBar* m_PowerBar;
	CWorm* m_Worm;
public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@param _Worm: Un pointeur vers le worm qui est focus
	@param _pTexture : Texture de l'image à afficher. NOTE: LA TEXTURE loader doit être celle de droite.
	*/
	CBazouka(SDL_Texture* _pTexture, CWorm* _pWorm){
		m_Rect = _pWorm->getPosition();
		m_RectSurface = _pWorm->getPosition();
		m_Rect.w = 52;
		m_Rect.h = 28;
		SDL_QueryTexture(_pTexture, NULL, NULL, &m_Rect.w, &m_Rect.h);//Dimension du bazooka
		m_pTexture = _pTexture;
		m_boCharging = false;
		iAngle = 0;
		m_uiPower = 0;
		m_PowerBar = new CPowerBar(m_RectSurface);
		m_PowerBar->setPowerLevel(m_uiPower);
		m_Worm = _pWorm;

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
		if (m_Worm->getWormState() == UsingBazzRight)
			SDL_RenderCopyEx(_pRenderer, m_pTexture, NULL, &m_Rect, iAngle, NULL, SDL_FLIP_NONE);
		else
		if (m_Worm->getWormState() == UsingBazzLeft)
			SDL_RenderCopyEx(_pRenderer, m_pTexture, NULL, &m_Rect, iAngle, NULL, SDL_FLIP_VERTICAL);
	
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
				if (m_Worm->getWormState() == UsingBazzRight){
					if (iAngle >= 90 && iAngle <= 270) iAngle += 180;
					if (iAngle >= -90 && iAngle <= 90) iAngle--;
				}
				if (m_Worm->getWormState() == UsingBazzLeft){
					if (iAngle >= -90 && iAngle <= 90) iAngle += 180;
					if (iAngle >= 90 && iAngle <= 270) iAngle++;
				}
				break;

			case SDLK_DOWN:
				if (m_Worm->getWormState() == UsingBazzRight){
					if (iAngle >= 90 && iAngle <= 270) iAngle += 180;
					if (iAngle >= -90 && iAngle <= 90) iAngle++;
				}
				if (m_Worm->getWormState() == UsingBazzLeft){
					if (iAngle >= -90 && iAngle <= 90) iAngle += 180;
					if (iAngle >= 90 && iAngle <= 270) iAngle--;
				}
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
