#ifndef TP_Codename_WORMS_CBazouka_h
#define TP_Codename_WORMS_CBazouka_h


/*!
@CBazouka
@Classe permettant l'affichage et la rotation du bazouka
*/
class CBazouka{
private:
	//Données membres:
	SDL_Rect m_Rect; //La pos du rectangle de l'objet
	double iAngle; // L'angle de rotation
	SDL_Texture* m_pTexture; // Texture de l'image à afficher.
	CSprite* m_pSprite; // Le sprite de la barre de lancement.

	bool boIsLaunch;
	bool boIsRotated;

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@param _ix _iy : la pos du bazouka (à modifier pour la pos du worms)
	@param _pTexture : texture de l'image à afficher.
	@param _pSprite: le sprite de la barre de lancement.
	@Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets
	*/
	CBazouka(int _ix, int _iy, SDL_Texture* _pTexture, CSprite* _pSprite){ // La position du bazouka devra être remplacer par la position du worms qui s'apprete  a attaquer.
		m_Rect.x = _ix;
		m_Rect.y = _iy;
		m_Rect.w = 52; // Dimension du bazouka
		m_Rect.h = 28; // Dimension du bazouka
		m_pTexture = _pTexture;
		m_pSprite = _pSprite;
		boIsLaunch = false;
		boIsRotated = false;
		double iAngle = 0;
	}

	/*!
	@methodRender
	@param _Renderer : Renderer pour rendre la texture du bazouka
	@return null
	*/
	void Render(SDL_Renderer* _pRenderer){
		if (!boIsRotated)
			SDL_RenderCopy(_pRenderer, m_pTexture, NULL, &m_Rect);
		else
			SDL_RenderCopyEx(_pRenderer, m_pTexture, NULL, &m_Rect, iAngle, NULL, SDL_FLIP_NONE);
		if (boIsLaunch){
			IsLaunch(_pRenderer);
			boIsLaunch = false;
		}
	}

	void IsLaunch(SDL_Renderer* _pRenderer){
		DeterminerSpritePosLaunch();
		m_pSprite->Render(_pRenderer);
	}
	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event* _Event){
		switch (_Event->key.keysym.sym){

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
			boIsLaunch = true;
			break;
		}
	}
	/*!
	@method DeterminerSpritePosLaunch
	@description: permet de set la position du sprite dépendamment si le bazouka est droit ou en angle.
	@return null
	*/

	void DeterminerSpritePosLaunch(){
		m_pSprite->setSpritePos(m_Rect.x, m_Rect.y - 5);
	}



	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CBazouka(){

	}
};

#endif
