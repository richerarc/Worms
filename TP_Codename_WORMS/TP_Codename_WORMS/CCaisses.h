#ifndef TP_Codename_WORMS_CCaisses_h
#define TP_Codename_WORMS_CCaisses_h


/*!
@CCaisses
@Classe permettant la création d'une caisse
*/
class CCaisses : public CObjets{
private:
	//Données membres:
	bool boIsExplosed;//Donnée représentant si l'objet est explosé (true) ou non (false).

public:

	/*!
	@method Constructeur
	@brief Permet d'initialiser les données membres.
	@param _TextureExplosion image de l'explosion.
	@param _RectPos: la pos du rectangle de l'objet.
	@param _pTexture : texture de l'image à afficher.
	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets.
	*/
<<<<<<< Updated upstream
	CCaisses(SDL_Texture* _TextureExplosion, SDL_Rect _RectPos, SDL_Texture* _pTexture) :CObjets(_TextureExplosion, _RectPos, _pTexture){
=======
	CCaisses(SDL_Texture* _textureExplosion, SDL_Rect _RectPos, SDL_Texture* _Texture) :CObjets(_textureExplosion, _RectPos, _Texture){
>>>>>>> Stashed changes
		boIsExplosed = false;
	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead.
	*/
	~CCaisses(){
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture de la caisse
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
		m_boFocus = true;
	
	}

	/*!
	@method ReactToExplosion
	@brief réagit a une explosion.
	@param _iX: Position en x de l'explosion.
	@param _iY: Position en y de l'explosion.
	@param _iRayon: Rayon de l'explosion.
	@return Adresse mémoire de l'objet.
	@discussion Aucune.
	*/
	void ReactToExplosion(int _iX, int _iY, int _iRayon){
		boIsExplosed = true;
	}

	void Move(){
		
	}

	/*!
	@method Accesseurs
	@brief Permet d'acceder aux données membres.
	*/

	bool IsItExplosed(){
		return boIsExplosed;
	}

	void setExplosion(bool _boSet){
		boIsExplosed = _boSet;
	}

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}

	


};

#endif
