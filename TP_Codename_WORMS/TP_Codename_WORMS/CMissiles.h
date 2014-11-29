#ifndef TP_Codename_WORMS_CMissiles_h
#define TP_Codename_WORMS_CMissiles_h


/*!
@CMissiles
@Classe permettant la création d'un missile
*/
class CMissiles : public CObjets{
private:
	//Données membres:
	bool boIsExplosed; //Donnée représentant si l'objet est explosé (true) ou non (false)

public:


	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _iRayon: le rayond d'explosion de l'objet
	@param _RectPos: la pos du rectangle de l'objet
	@param _pTexture : texture de l'image à afficher
	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets
	*/
	CMissiles(int _iRayon, SDL_Rect _RectPos, SDL_Texture* _pTexture) :CObjets(_iRayon, _RectPos, _pTexture){
		boIsExplosed = false;
	}
	
	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CMissiles(){
	}

	void Move(){
		
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture du missile
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
	@Méthode:
	@ReactToExplosion
	@Permet de calculer les dommages subit par l'explosion
	*/
	void ReactToExplosion(int _iX, int _iY, int _iRayon){}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}

	bool IsItExplosed(){
		return boIsExplosed;
	}

	void setExplosion(bool _boSet){
		boIsExplosed = _boSet;
	}
	

};

#endif
