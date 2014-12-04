class CMrow{
private:
	SDL_Rect m_RectPos;
public:
	CMrow(){
		m_RectPos.x = 100;
		m_RectPos.y = 100;
	}
	SDL_Rect getRect(){
		return m_RectPos;
	}
};