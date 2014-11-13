class CExplosion{
private:
	CSprite* m_pSprite;
	SDL_Rect m_Rect;
public:
	CExplosion(CSprite* _Sprite, SDL_Rect _Rect){
		m_pSprite = _Sprite;
		m_Rect = _Rect;
	}
};