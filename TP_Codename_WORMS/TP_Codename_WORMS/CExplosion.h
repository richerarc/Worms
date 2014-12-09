#ifndef TP_Codename_WORMS_CExplosion_h
#define TP_Codename_WORMS_CExplosion_h

class CExplosion{
private:
	CSprite* m_pSprite;		//Donnée membre représentant le sprite d'explosion.
	CPosition* m_pPosition;	//Donnée membre représentant la position de l'explosion.
	static SDL_Surface* m_ExplosionMask;
	int m_Range;    // Le rayon d'action de l'explosion
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _Sprite : le sprite de de l'explosion
	@return Adresse mémoire de l'objet.
	@discussion No discussion is needed.
	*/
	CExplosion(CSprite* _Sprite, CPosition* _Pos){
		m_pSprite = _Sprite;
		m_pSprite->setSpritePos(m_pPosition->getX(), m_pPosition->getY());
		m_pPosition = _Pos;
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




	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	static void setExplosionMask(SDL_Surface* _ExplosionMask){
		m_ExplosionMask = _ExplosionMask;
	}
	
	static SDL_Surface* getMask(){
		return m_ExplosionMask;
	}
	
	int getX(){
		return m_pPosition->getX();
	}
	
	int getY(){
		return m_pPosition->getY();
	}
	
	int getRange(){
		return m_Range;
	}
	
};

SDL_Surface* CExplosion::m_ExplosionMask = nullptr;
#endif