#ifndef TP_Codename_WORMS_CExplosion_h
#define TP_Codename_WORMS_CExplosion_h

class CExplosion{
private:
	CSprite* m_pSprite;		//Donnée membre représentant le sprite d'explosion.
	int m_iRadius;    // Le rayon d'action de l'explosion
	SDL_Rect m_RectDestination;
	SDL_Rect m_SpriteDimension;
	CMap* m_pMap;
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _Sprite : le sprite de de l'explosion
	@return Adresse mémoire de l'objet.
	@discussion No discussion is needed.
	*/
	CExplosion(CSprite* _Sprite, int _Radius, CMap* _ActiveMap){
		m_pSprite = _Sprite;
		m_pSprite->setSpritePos(0, 0);
		m_pMap = _ActiveMap;
		m_iRadius = _Radius;
		m_RectDestination.x = 0;
		m_RectDestination.y = 0;
		m_RectDestination.h = _Radius * 2;
		m_RectDestination.w = _Radius * 2;
		m_SpriteDimension = m_pSprite->getRectSource();
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la textures du Sprite.
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
		m_pSprite->Render(_pRenderer);
		if (m_pSprite->AnimationIsOver(false)){
			ExplodeMap();
			m_pMap->ConvertMap(_pRenderer);
		}
	}

	void ExplodeMap(){
		double dblX, dblY ;
		double dblRayon;
		int iTemp;
		for (int y = 0; y <= m_RectDestination.h; y++){
			for (int x = 0; x < m_RectDestination.w; x++)
			{
				dblX = m_iRadius - x;
				dblY = m_iRadius - y;
				dblRayon = sqrt((dblX*dblX) + (dblY*dblY));
				if (dblRayon <= m_iRadius){
					for (int i = 0; i < dblX * 2; i++)
					{
						iTemp = (y + m_RectDestination.y)*m_pMap->getMap()->w + (x + m_RectDestination.x);
						if ((iTemp>=0) && (iTemp<=HEIGHT*WIDTH))
							((unsigned int*)m_pMap->getMap()->pixels)[iTemp] = 0;
						x++;
					}
				}
			}
		}
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


	int getX(){
		return m_RectDestination.x;
	}

	int getY(){
		return m_RectDestination.y;
	}


	CMap* getMap(){ return m_pMap; }
	CSprite* getSprite(){ return m_pSprite; }
	int getRadius(){ return m_iRadius; }

	void setPositionXY(int _iX, int _iY){
		m_RectDestination.x = _iX - m_iRadius;
		m_RectDestination.y = _iY - m_iRadius;
		m_pSprite->setSpritePos(_iX - (m_SpriteDimension.w / 2), _iY - (m_SpriteDimension.h-m_iRadius/3));
	}

};

#endif