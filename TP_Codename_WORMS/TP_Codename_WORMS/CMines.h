#ifndef TP_Codename_WORMS_CMines_h
#define TP_Codename_WORMS_CMines_h


/*!
@CMines
@Classe permettant la création d'une mines
*/
class CMines : public CObjets{
private:

	//Données membres:
	bool boIsexploded; //Donnée représentant si l'objet est explosé (true) ou non (false)

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
	CMines(SDL_Texture* _textureExplosion, SDL_Rect _RectPos, SDL_Texture* _Texture) :CObjets(_textureExplosion, _RectPos, _Texture){
		boIsexploded = false;
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
			//SDL_RenderCopy(_pRenderer, m_pTexture, NULL, &m_RectPosition);
		if ((!m_Angle) && (m_EntityState == Immobile))
			m_Angle = CPhysics::EvaluateSlope(new SDL_Rect({m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, m_RectPosition.h}));
		SDL_RenderCopyEx(_pRenderer, m_pTexture, NULL, &m_RectPosition, RadToDeg(m_Angle), NULL, SDL_FLIP_NONE);
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
		boIsexploded = true;
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	bool IsItexploded(){
		return boIsexploded;
	}

	void setExplosion(bool _boSet){
		boIsexploded = _boSet;
	}

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}


};

#endif
