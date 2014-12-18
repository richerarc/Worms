class CTexture :public CRessource{
private:
	SDL_Texture* m_pTexture; // Texture de l'image à afficher
public:

	CTexture(const char* _strName, SDL_Texture* _Texture) : CRessource(_strName){
		m_pTexture = _Texture;
	}

	~CTexture(){
		if (m_pTexture != nullptr){
			SDL_DestroyTexture(m_pTexture);
			m_pTexture = nullptr;
		}
	}

	SDL_Texture* GetTexture(){
		return m_pTexture;
	}

};