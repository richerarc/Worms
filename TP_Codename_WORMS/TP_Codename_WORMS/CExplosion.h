#ifndef TP_Codename_WORMS_CExplosion_h
#define TP_Codename_WORMS_CExplosion_h

class CExplosion{
private:
	CSprite* m_pSprite;		//Donnée membre représentant le sprite d'explosion.
	static SDL_Surface* m_ExplosionMask;
	int m_Range;    // Le rayon d'action de l'explosion
	SDL_Rect m_RectSource;
	SDL_Rect m_RectDestination;
	SDL_Rect m_SpriteDimension;
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _Sprite : le sprite de de l'explosion
	@return Adresse mémoire de l'objet.
	@discussion No discussion is needed.
	*/
	CExplosion(CSprite* _Sprite, int _Range){
		m_pSprite = _Sprite;
		m_pSprite->setSpritePos(0, 0);
		m_RectSource.x = _Range;
		m_RectSource.y = 0;
		m_RectSource.h = m_ExplosionMask->h;
		m_RectSource.w = m_ExplosionMask->w / 3;
		m_RectDestination.x = 0;
		m_RectDestination.y = 0;
		m_RectDestination.h = m_RectSource.h;
		m_RectDestination.w = m_RectSource.w;
		m_SpriteDimension = m_pSprite->getRectSource();
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la textures du Sprite.
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer, SDL_Surface* _Map){
		m_pSprite->Render(_pRenderer);
		if (m_pSprite->AnimationIsOver(false)){
			ExplodeMap(_Map);
		}
	}

	void ExplodeMap(SDL_Surface* _Map){
		unsigned int temp;
		switch (m_RectSource.x)
		{
		case 0:
			for (int i = 0; i < m_RectSource.h * m_RectSource.w; i++) {
				temp = (((unsigned int*)m_ExplosionMask->pixels)[i]);
				if ((i>0) && !(i % 100)){ i += 200; }
				if (temp != 0){
					if (((unsigned int*)_Map->pixels)[0] > 0){ ((unsigned int*)_Map->pixels)[i + m_pSprite->getX()] = 0; }
				}
			}
			break;
		case 1:
			for (int i = m_RectSource.h * m_RectSource.w; i < m_RectSource.h * (m_RectSource.w * 2); i++) {}
			break;
		case 2:
			for (int i = m_RectSource.h * m_RectSource.w; i < m_RectSource.h * (m_RectSource.w * 3); i++) {}
			break;
		}


	/*	if (pixelsDutrou[i] == TRANSPARENT)
		Pixelsdelamap[posdeDépart + i] = TRANSPARENT;*/
	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CExplosion(){
	}

	void startExplosion(){
		m_pSprite->Start();
	}

	bool IsDone(){ return m_pSprite->AnimationIsOver(true); }


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
		return m_RectDestination.x;
	}

	int getY(){
		return m_RectDestination.y;
	}

	int getRange(){
		return m_Range;
	}

	void setPositionXY(int _iX, int _iY){
		m_RectDestination.x = _iX - (m_RectSource.w / 2);
		m_RectDestination.y = _iY - (m_RectSource.h / 2);
		m_pSprite->setSpritePos(_iX-(m_SpriteDimension.w/2), _iY-(m_SpriteDimension.h));
	}

};

SDL_Surface* CExplosion::m_ExplosionMask = nullptr;
#endif