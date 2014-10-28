//
//  CWindow.h
//  CFenetre
//
//  Created by Richer Archambault on 2014-10-07.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//



#ifndef CFenetre_CWindowManager_h
#define CFenetre_CWindowManager_h


/*!
 @class CWindow
 @discussion Classe Exploitant la SDL pour l'affichage des fenetres
 */
class CWindow {
private:
	SDL_Window* m_pSDLWindow;
	SDL_Renderer* m_pSDLRenderer;
	unsigned int m_uiWindowID;
public:

	CWindow(unsigned int _width, unsigned int _height){
		SDL_CreateWindowAndRenderer(_width, _height, NULL, &m_pSDLWindow, &m_pSDLRenderer);
		m_uiWindowID = SDL_GetWindowID(m_pSDLWindow);
	}

	~CWindow(){
		SDL_DestroyRenderer(m_pSDLRenderer);
		SDL_DestroyWindow(m_pSDLWindow);
	}

	void Refresh(){

		SDL_RenderPresent(m_pSDLRenderer);
	}

	void SetTitle(const char *_Title){
		SDL_SetWindowTitle(m_pSDLWindow, _Title);
	}

	unsigned int GetWindowID(){
		return m_uiWindowID;
	}

	SDL_Renderer* getRenderer(){
		return m_pSDLRenderer;
	}

	SDL_Window* getWindow(){
		return m_pSDLWindow;
	}
};



#endif
