class CSprite : public CRessource{
private:
	SDL_Texture* m_pTexture;		// Texture du sprite.
	SDL_Rect m_rSource;				// Informations Source.
	SDL_Rect m_rDest;				// Information sur la destination
	CTimer* m_pTimer;				// Temps entre les images.
	int m_NbrFrame;					// Nombre de Frames que contiennent l'immage en x.
	int m_currentFrame;				// On est rendu l'animation (en x).
	int m_NbrAnimation;				// Nombre d'Animation en y.
	int m_currentAnimation;			// On on est rendu en y.
	unsigned int m_uinbLoop;		// Combien de fois devons nous repeter l'animation.
	unsigned int m_uiCurrentLoop;	// A quel répétiton l'animation est rendue.
	bool m_boActif;					// Indique si l'Animation joue ou non.


	void setRectSource(){
		if (m_pTimer->IsElapsed() && m_boActif && (m_uiCurrentLoop < m_uinbLoop)){
			m_pTimer->Start();
			m_currentFrame = (++m_currentFrame) % m_NbrFrame;
			m_rSource.x = (m_rSource.w * m_currentFrame);
			if (m_currentFrame == m_NbrFrame - 1)
				m_uiCurrentLoop++;
		}
	}
	
	void setRectSource(int _StartFrame, int _NbFrameUsed){
		if (m_pTimer->IsElapsed() && m_boActif && (m_uiCurrentLoop < m_uinbLoop)){
			m_pTimer->Start();
			m_currentFrame = ((m_currentFrame + 1) % (_NbFrameUsed)) + _StartFrame;
			m_rSource.x = (m_rSource.w * m_currentFrame);
			if (m_currentFrame == _NbFrameUsed - 1)
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
		m_rDest.x = 0;
		m_rDest.y = 0;
		m_rDest.w = m_rSource.w;
		m_rDest.h = m_rSource.h;
		m_pTimer->Start();
		m_currentFrame = 0;
		m_boActif = false;
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

	bool AnimationIsOver(bool _boreset){
		if (m_currentFrame == m_NbrFrame - 1){
			if (_boreset){
				SDL_QueryTexture(m_pTexture, NULL, NULL, &m_rSource.w, &m_rSource.h);
				m_rSource.w = (m_rSource.w / m_NbrFrame);
				m_rSource.h = m_rSource.h / m_NbrAnimation;
				m_rSource.x = 0;
				m_rSource.y = 0;
				m_rDest.x = 0;
				m_rDest.y = 0;
				m_rDest.w = m_rSource.w;
				m_rDest.h = m_rSource.h;
				m_pTimer->Start();
				m_currentFrame = 0;
				m_uiCurrentLoop = 0;
				m_boActif = false;
			}
			return true;
		}
		return false;
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
		m_currentFrame = 0;
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
	
	void Render(unsigned int _StartFrame, unsigned int _NbOfFrameUsed, SDL_Renderer* _Renderer){
		setRectSource(_StartFrame, _NbOfFrameUsed);
		SDL_RenderCopy(_Renderer, m_pTexture, &m_rSource, &m_rDest);
	}
	
	void Render(SDL_Renderer* _Renderer , int _iIMG){
		m_rSource.x = _iIMG * m_rSource.w;
		SDL_RenderCopy(_Renderer, m_pTexture, &m_rSource, &m_rDest);
	}
	
	void Render(unsigned int _StartFrame, unsigned int _NbOfFrameUsed, SDL_Renderer* _Renderer, double _Angle){
		setRectSource(_StartFrame, _NbOfFrameUsed);
		SDL_RenderCopyEx(_Renderer, m_pTexture, &m_rSource, &m_rDest, RadToDeg(_Angle), NULL, SDL_FLIP_NONE);
	}
	
};