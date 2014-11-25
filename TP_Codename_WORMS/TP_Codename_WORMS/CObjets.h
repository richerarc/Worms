#ifndef TP_Codename_WORMS_CObjets_h
#define TP_Codename_WORMS_CObjets_h


/*!
@CObjets
@Classe permettant la création d'un objet.
*/
class CObjets : public CEntity{
protected:
	//Données membres:
	int m_iRayon; //Donnée représentant la longueur du rayon du rect(circulaire).

public:

	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	 @param _iRayon : le rayon d'explosion
	 @param _RectPos : le rect de l'objet
	@Classe héritant de CEntity, elle prend donc les paramètres de CEntity.
	*/
	CObjets(int _iRayon, SDL_Rect _RectPos, SDL_Texture* _Texture) :CEntity(_RectPos, _Texture){
		m_iRayon = _iRayon;
	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CObjets(){
	}

	/*!
	@method Draw
	@brief Fonction virtuel pour dessiner l'entitée sur un Renderer
	@param _Renderer : Le renderer sur lequel dessiner
	@return Aucun
	*/
	virtual void Draw(SDL_Renderer*) = 0;

	/*!
	@Accesseur virtuel IsItExplosed
	@brief Permet de savoir si l'objet est explosé ou non.
	@return bool.
	*/
	virtual bool IsItExplosed(){return false;};

	/*!
	@Accesseurs:
	*/
	int getRayon(){
		return m_iRayon;
	}
};

#endif
