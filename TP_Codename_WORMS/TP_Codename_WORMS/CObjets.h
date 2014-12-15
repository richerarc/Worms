#ifndef TP_Codename_WORMS_CObjets_h
#define TP_Codename_WORMS_CObjets_h


/*!
@CObjets
@Classe permettant la création d'un objet.
*/
class CObjets : public CEntity{
protected:
	//Données membres:

public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _iRayon : le rayon d'explosion
	@param _RectPos : le rect de l'objet
	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de CEntity, elle prend donc les paramètres de CEntity.
	*/
	CObjets(SDL_Rect _RectPos, SDL_Texture* _Texture, CExplosion* _Explosion) :CEntity(_RectPos, _Texture, _Explosion){
		
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
	@Accesseur virtuel IsItExploded
	@brief Permet de savoir si l'objet est explosé ou non.
	@return bool.
	*/
	virtual bool IsExploded(){return false;};
	
	virtual void Detonate(){}
};

#endif
