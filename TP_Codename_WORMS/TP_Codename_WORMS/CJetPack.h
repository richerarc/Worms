#ifndef TP_Codename_WORMS_CJetPack_h
#define TP_Codename_WORMS_CJetPack_h

/* Liste de chose TOO DOOO :
  - Vérifier avec les nazi si le jetpack sera une texture en vole et un sprite au sol ou whatever
  - Incorporer la physique à tout sa pour le deplacement (HandleEvent)
  - La position x et y dans le constructeur devra être remplacer par possiblement un rectPos du worms.
  - La barre de gaz fait sa saloppe je sais pas pk mais la changer par une CPowerBarre de Kev.
  - Peut-etre ben aussi vérifier la position ou je vais mettre la CPowerBarre (avec le jet pack ou dans un coin obscure)
  - Me faire du popcorn
*/


/*!
@CJetPack
@Classe permettant l'affichage et l'utilisation du JetPack
*/
class CJetPack{
private:
	//Données membres:
	SDL_Rect m_Rect; //La pos du rectangle de l'objet
	SDL_Rect m_RectSurface; //La pos du rectangle de la surface de la barre de gaz
	SDL_Texture* m_pTexture; // Texture de l'image à afficher.
	SDL_Surface* m_pSurfaceBarreLancement; // Surface de la barre de lancement.
	bool boBarreGaz; // Booléen pour vérifier si la barre de lancement sera afficher
	unsigned int iGaz; // Représente le gaz restant au jet pack
	C2DVecteur

public:

	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@param _ix _iy : la pos du jet pack (à modifier pour la pos du worms)
	@param _pTexture : texture de l'image à afficher.
	*/
	CJetPack(int _ix, int _iy, SDL_Texture* _pTexture){ // La position du jet pack devra être remplacer par la position du worms
		m_Rect.x = _ix;
		m_Rect.y = _iy;
		m_Rect.w = 52; // Dimension du jet pack
		m_Rect.h = 28;
		m_pTexture = _pTexture;
		m_pSurfaceBarreLancement = SDL_CreateRGBSurface(0, 0, 0, 10, 2500, 0, 0, 0);
		boBarreGaz = false;
		iGaz = 50;
	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CJetPack(){
	}

	/*!
	@methodRender
	@param _pRenderer : Renderer pour rendre la texture du jet Pack
	@return null
	*/
	void Render(SDL_Renderer* _pRenderer){
		//Ceci est temporaire, devra probablement être modifier par un sprite de worms + jetpack
		SDL_RenderCopy(_pRenderer, m_pTexture, NULL, &m_Rect);
		IsLaunch(_pRenderer);

	}

	/*!
	@method IsLaunch
	@description: permet de faire afficher la barre de lancement.
	@param _pRenderer: Renderer pour rendre la surface de la barre de gaz
	@return null
	*/
	void IsLaunch(SDL_Renderer* _pRenderer){

		SetRectSurface(iGaz);
		SDL_SetRenderDrawColor(_pRenderer, 255, 0, 0, 0);
		SDL_RenderFillRect(_pRenderer, &m_RectSurface);


	}

	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event* _Event){

		//TO DOOO
		switch (_Event->key.keysym.sym){
		case SDLK_LEFT:
			break;

		case SDLK_SPACE:
			iGaz--;
			break;

		}
	}

	/*!
	@method SetRectSurface
	@description: permet de set la position et la dimension du rect de la barre de gaz
	@param: _iWidth: la largeur du rect
	*/
	void SetRectSurface(int _iWidth){
		m_RectSurface.x = m_Rect.x;
		m_RectSurface.y = m_Rect.y - 15;
		m_RectSurface.w = _iWidth;

	}

};

#endif
