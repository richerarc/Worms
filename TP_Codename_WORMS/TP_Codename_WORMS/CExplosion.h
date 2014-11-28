#ifndef TP_Codename_WORMS_CExplosion_h
#define TP_Codename_WORMS_CExplosion_h

class CExplosion{
private:
	CSprite* m_pSprite;		//Donnée membre représentant le sprite d'explosion.
	CPosition* m_pPosition;	//Donnée membre représentant la position de l'explosion.

public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _Sprite : le sprite de de l'explosion
	@return Adresse mémoire de l'objet.
	@discussion No discussion is needed.
	*/
	CExplosion(CSprite* _Sprite){
		m_pSprite = _Sprite;
		m_pSprite->setSpritePos(m_pPosition->getX(), m_pPosition->getY());
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la textures du Sprite.
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
		m_pSprite->Render(_pRenderer);
	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CExplosion(){
	}

};

#endif