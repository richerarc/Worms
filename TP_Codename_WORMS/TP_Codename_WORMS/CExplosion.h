#ifndef TP_Codename_WORMS_CExplosion_h
#define TP_Codename_WORMS_CExplosion_h

class CExplosion{
private:
	CSprite* m_pSprite;//Donnée membre représentant le sprite d'explosion.
	CPosition* m_pPosition; //Donnée membre représentant la position de l'explosion.

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@param _Sprite : le sprite de l'objet
	@param _RectPos : le rect de l'objet
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