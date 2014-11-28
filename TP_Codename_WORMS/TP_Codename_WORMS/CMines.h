#ifndef TP_Codename_WORMS_CMines_h
#define TP_Codename_WORMS_CMines_h


/*!
@CMines
@Classe permettant la création d'une mines
*/
class CMines : public CObjets{
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
	CMines(int _iRayon, SDL_Rect _RectPos, SDL_Texture* _Texture) :CObjets(_iRayon, _RectPos, _Texture){
		boIsExplosed = false;
	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CMines(){
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture de la mine
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
	void ReactToExplosion(int _iX, int _iY, int _iRayon){
		boIsExplosed = true;
	}

	/*!
	@Accesseurs:
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
