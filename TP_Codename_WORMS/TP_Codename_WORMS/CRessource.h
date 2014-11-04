//
//  CRessource.h
//  TP_Codename_WORMS_Mac
//
//  Created by Richer Archambault on 2014-10-28.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//

#define BUFFER 1024

#ifndef TP_Codename_WORMS_CRessource_h
#define TP_Codename_WORMS_CRessource_h


/*
@class CRessource
@discussion Classe représentant une ressource du gestionnaire
*/

class CRessource {
private:
	const char* m_strName;
	
public:
	//Constructeur...
	CRessource(const char* _Name){
		m_strName = _Name;
	}

	//Destructeur...
	~CRessource(){
		
	}

	//Accesseur...
	const char* GetName(){
		return m_strName;
	}
};


/*!
 @class CFont
 @discussion Classe pour l'implémentation des police et affichage de texte
 */
class CFont : public CRessource{
private:
	TTF_Font* m_pFont; 			// Membre pour loader la font
	SDL_Surface* m_pSurface;	// Membre pour render du texte
	SDL_Texture* m_pTexture;	// membre pour l'affichage du texte
	SDL_Color m_Color;			// Membre pour la couleur du texte
	SDL_Rect m_Rect;			// Section de l'affichage
	int iSize;                  //Représente la taille de la police de caractère
public:
	
	/*!
	 @method Constructeur
	 @param _FontPath : cosnt char* pour acqueillir le chemin fichier
	 @param _iSize : Int pour la grandeur de la police
	 */
	CFont(const char* _Name, const char* _FontPath, int _iSize) : CRessource(_Name){
		m_pFont = TTF_OpenFont(_FontPath, _iSize);
		m_Color = {0, 0, 0, 255};
	}
		//Destructeur
	~CFont(){
		TTF_CloseFont(m_pFont);
		SDL_DestroyTexture(m_pTexture);
		SDL_FreeSurface(m_pSurface);
	}
	
		//Accesseur
	void setFontColor(SDL_Color _Color){
		m_Color = _Color;
	}

	int getFontSize(){
		return iSize;
	}
	
	/*!
	 @method RenderText
	 @brief methode pour render du text à l'écran
	 @param _Renderer : Le renderer sur le quel afficher
	 @param _chrtext : Le text à afficher
	 @param _ix : Position en x
	 @param _iy : Position en y
	 @return Aucun
	 */
	void RenderText(SDL_Renderer* _Renderer, const char* _chrText, int _ix, int _iy){
		m_pSurface = TTF_RenderText_Solid(m_pFont, _chrText, m_Color);
		m_pTexture = SDL_CreateTextureFromSurface(_Renderer, m_pSurface);
		SDL_QueryTexture(m_pTexture, NULL, NULL, &m_Rect.w, &m_Rect.h);
		m_Rect.x = _ix;
		m_Rect.y = _iy;
		SDL_RenderCopy(_Renderer, m_pTexture, NULL, &m_Rect);
	}
};


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
		m_rSource.w = (m_rSource.w / m_NbrFrame) ;
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
	
	void Start_Pause(){
		m_boActif = !m_boActif;
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



class CMusic : CRessource{
private:
	Mix_Music* m_pMusic;
	static bool m_boInitialized;
public:
	CMusic(const char* _Name, const char* _Path) : CRessource(_Name){
		if (!m_boInitialized){
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, BUFFER);
			Mix_AllocateChannels(0);
			m_boInitialized = true;
		}
		m_pMusic = Mix_LoadMUS(_Path);
	}
	~CMusic(){
		Mix_FreeMusic(m_pMusic);
	}
	
	/*!
	 @method Play
	 @brief methode pour faire jouer la musique
	 @param _inbrOfLoop : nombre de fois que le musique doit être jouer
	 @return Aucun
	 */
	void Play(int _inbrOfLoop){
		if (!Mix_PlayingMusic())
			Mix_PlayMusic(m_pMusic, _inbrOfLoop);
		else
			Mix_ResumeMusic();
	}
	
	/*!
	 @method Pause
	 @brief methode pour mettre la musique en pause
	 @param Aucun
	 @return Aucun
	 */
	void Pause(){
		if (Mix_PlayingMusic())
			Mix_PauseMusic();
	}
};


bool CMusic::m_boInitialized = false;
#endif
