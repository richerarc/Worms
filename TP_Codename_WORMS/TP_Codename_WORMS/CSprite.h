class CSprite : public CRessource{
private:
	SDL_Texture* m_pTexture;
	SDL_Rect m_rSource;
	SDL_Rect m_rDest;
	CTimer* m_pTimer;
	int m_NbrFrame;
	int m_currentFrame;
	int m_NbrAnimation;
	int m_currentAnimation;
	unsigned int m_uinbLoop;
	unsigned int m_uiCurrentLoop;
	bool m_boActif;


	void setRectSource(){
		if (m_pTimer->IsElapsed() && m_boActif && (m_uiCurrentLoop < m_uinbLoop)){
			m_pTimer->Start();
			m_currentFrame = (++m_currentFrame) % m_NbrFrame;
			m_rSource.x = (m_rSource.w * m_currentFrame);
			if (m_currentFrame == m_NbrFrame - 1)
				m_uiCurrentLoop++;
		}
	}
public:
	CSprite(const char* _Name, SDL_Texture* _Texture, int _nbrFrame, int _nbrAnimation, int _delai, int _loop) : CRessource(_Name){
		m_pTexture = _Texture;
		m_NbrFrame = _nbrFrame;
		m_NbrAnimation = _nbrAnimation;
		m_pTimer = new CTimer();
		m_pTimer->SetTimer(_delai);
		SDL_QueryTexture(m_pTexture, NULL, NULL, &m_rSource.w, &m_rSource.h);
		m_rSource.w = (m_rSource.w / m_NbrFrame);
		m_rSource.h = m_rSource.h / m_NbrAnimation;
		m_rSource.x = 0;
		m_rSource.y = 0;
		m_rDest.x = 500;
		m_rDest.y = 200;
		m_rDest.w = m_rSource.w;
		m_rDest.h = m_rSource.h;
		m_pTimer->Start();
		m_currentFrame = 0;
		m_boActif = true;
		m_uinbLoop = _loop;
		if (!m_uinbLoop)
			m_uinbLoop = 1;
		m_uiCurrentLoop = 0;
	}
	~CSprite(){
		delete m_pTimer;
		SDL_DestroyTexture(m_pTexture);
	}


	void setSpritePos(int _ix, int _iy){
		m_rDest.x = _ix;
		m_rDest.y = _iy;
	}

	void Start(){
		m_boActif = true;
	}

	void Pause(){
		m_boActif = false;
	}

	void setNbLoop(int _loop){
		m_uinbLoop = _loop;
		if (!m_uinbLoop)
			m_uinbLoop = 1;
	}

	int getCurrentAnimation(){
		return m_currentAnimation;
	}

	int getX(){
		return m_rDest.x;
	}
	int getY(){
		return m_rDest.y;
	}

	void setCurrentAnimation(int _currentAni){
		m_currentAnimation = _currentAni;
		m_rSource.y = m_rSource.h * m_currentAnimation;
	}
	/*!
	@method Render
	@brief Methode pour render le sprite à l'écran
	@param _Renderer : Le rendrerer sur lequel dessiner le sprite
	@return Aucun
	*/
	void Render(SDL_Renderer* _Renderer){
		setRectSource();
		SDL_RenderCopy(_Renderer, m_pTexture, &m_rSource, &m_rDest);
	}
};