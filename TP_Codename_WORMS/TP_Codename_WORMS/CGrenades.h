#ifndef TP_Codename_WORMS_CGrenades_h
#define TP_Codename_WORMS_CGrenades_h


/*!
@CGrenades
@Classe permettant la création d'une grenade
*/
class CGrenades : public CObjets{
private:
	//Données membres:
	CTimer* m_pTimer; // Déclaration d'une nouvelle minuterie pour le temps à écouler avant l'explosion.
	SDL_Texture* m_pTexture; // Texture de l'image à afficher.

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	 @param _iRayon: le rayond d'explosion de l'objet
	 @param _Name : le nom de l'objet
	 @param _uiMasse: la masse de l'objet
	 @param _RectPos: la pos du rectangle de l'objet
	 @param _pTexture : texture de l'image à afficher
	@Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets
	*/
	CGrenades(int _iRayon, const char* _Name, SDL_Rect _RectPos, SDL_Texture* _pTexture) :CObjets(_iRayon,_Name,_RectPos){
		m_pTexture = _pTexture;
		m_pTimer = new CTimer();
		m_pTimer->SetTimer(1000);
		m_pTimer->Start();
		m_iRayon = _iRayon;

	}
	
	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre le textures du Sprite et du texte du bouton
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
		SDL_RenderCopy(_pRenderer, m_pTexture, NULL, &m_RectPosition);
	}


	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event _Event){
		// TO do
	}
	
	/*!
	@method IsExplose
	@param null
	@return bool: Explose=true / Unexplose=false;
	*/
	bool IsExplose(){
		return m_pTimer->IsElapsed();
	}

	/*!
	@Accesseurs:
	*/

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CGrenades(){
	}


};

#endif
