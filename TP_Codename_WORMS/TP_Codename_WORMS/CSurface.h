class CSurface :public CRessource{
private:
	SDL_Surface* m_pSurface;  // Surface pour les modifications de pixel.
public:

	CSurface(const char* _strName, SDL_Surface* _Surface):CRessource(_strName){
		m_pSurface = _Surface;
	}

	~CSurface(){
		if (m_pSurface != nullptr){
			SDL_FreeSurface(m_pSurface);
			m_pSurface = nullptr;
		}
	}

	SDL_Surface* getSurface(){
		return m_pSurface;
	}

};