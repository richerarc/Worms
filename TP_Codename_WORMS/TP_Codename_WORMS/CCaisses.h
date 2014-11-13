#ifndef TP_Codename_WORMS_CCaisses_h
#define TP_Codename_WORMS_CCaisses_h


/*!
@CCaisses
@Classe permettant la création d'une caisse
*/
class CCaisses : public CObjets{
private:
	//Données membres:
	SDL_Texture* m_pTexture; // Texture de l'image à afficher.
public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	 @param _Name : le nom de l'objet
	 @param _uiMasse: la masse de l'objet
	 @param _RectPos: la pos du rectangle de l'objet
	 @param _pTexture : texture de l'image à afficher
	@Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets
	*/
	CCaisses(int _iRayon, SDL_Rect _RectPos, SDL_Texture* _pTexture) :CObjets(_iRayon, _RectPos){
		m_pTexture = _pTexture;
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
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CCaisses(){
	}



	/*!
	@Accesseurs:
	*/
	
	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}

};

#endif
