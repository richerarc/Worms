#ifndef TP_Codename_WORMS_CObjets_h
#define TP_Codename_WORMS_CObjets_h


/*!
@CGrenades
@Classe permettant la création d'une grenade
*/
class CObjets : public CEntity{
protected:
	//Données membres:
	int m_iRayon; //Donnée représentant la longueur du rayon de l'explosion.

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	 @param _iRayon : le rayon d'explosion
	 @param _Name : le nom de l'entitée
	 @param _uiMasse : la masse de l'entitée
	 @param _RectPos : le rect de l'entitée
	@Classe héritant de CEntity, elle prend donc les paramètres de CEntity.
	*/
<<<<<<< HEAD
	CObjets(int _iRayon, SDL_Rect _RectPos) :CEntity(_RectPos){
		m_iRayon = _iRayon;
=======
	CObjets(const char* _Name, unsigned int _uiMasse,SDL_Rect _RectPos) : CEntity( _Name, _uiMasse, _RectPos){
>>>>>>> 620d262c90c1eaa43e43336d6e0d57479837c984
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
	virtual void Draw(SDL_Renderer* _Renderer){};


	/*!
	@Accesseurs:
	*/
	int getRayon(){
		return m_iRayon;
	}

};

#endif
