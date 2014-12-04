class CMrow{
private:
	SDL_Rect m_RectPos;
public:
	CMrow(SDL_Rect _pRectpos){
		m_RectPos.x = _pRectPos.x;
		m_RectPos.y = _pRectPos.y;
	}
	SDL_Rect getRect(){
		return m_RectPos;
	}
};