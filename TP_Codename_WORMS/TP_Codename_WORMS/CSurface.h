class CSurface :public CRessource{
public:
	SDL_Surface* m_pSurface;
private:

	CSurface(const char* _strName, SDL_Surface* _Surface):CRessource(_strName){
		m_pSurface = _Surface;
	}

	~CSurface(){}

	SDL_Surface* getSurface(){
		return m_pSurface;
	}

};