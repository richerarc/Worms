//
//  CTextBox.h
//  TP_Codename_WORMS_Mac
//
//  Created by Richer Archambault on 2014-10-28.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//

#ifndef TP_Codename_WORMS_CTextBox_h
#define TP_Codename_WORMS_CTextBox_h

/*!
 @class CTextBox
 @discussion Classe représentant une boite de texte
 */
class CTextBox : public CGUIE{
	SDL_Texture* m_texture;
	SDL_Renderer* m_MenuRenderer;
public:
	
	/*!
	 @method Constucteur
	 @param _Name : le nom du Controle visuel
	 @param _strText : le text contenu dans le controle
	 @param _Font : La police de caractère pour dessiner le texte
	 @param _Rect : le rectangle pour les information d'affichage (position, hauteur largeur)
	 */
	CTextBox(const char* _Name, string _strText, CFont* _Font, SDL_Rect _Rect, SDL_Renderer* _MenuRenderer) : CGUIE(_Name, _strText, _Font, _Rect){
		m_strText = "_";
		m_MenuRenderer = _MenuRenderer;
	}
	
	void OnClick(int _x, int _y){
		SDL_Event Event;
		bool boLoop = true;
		bool boShift = false;
		if ((_x >= m_Rect.x) && (_y >= m_Rect.y) && (_x <= m_Rect.x + m_Rect.w) && (_y <= m_Rect.y + m_Rect.h)){
			while (boLoop){
				while (SDL_PollEvent(&Event)) {
					switch (Event.type){
						case SDL_KEYUP:
							if ((Event.key.keysym.sym == SDLK_RSHIFT) || (Event.key.keysym.sym == SDLK_LSHIFT))
								boShift = true;
							break;
						case SDL_KEYDOWN:
							switch (Event.key.keysym.sym) {
								case SDLK_LSHIFT:
								case SDLK_RSHIFT:
									boShift = true;
									break;
								case SDLK_ESCAPE:
								case SDLK_RETURN:
									boLoop = false;
									if(*m_strText.rbegin() == '_')
										m_strText.pop_back();
									break;
								case SDLK_BACKSPACE:
									if (!m_strText.empty())
										m_strText.pop_back();
									break;
								default:
									if (m_strText.length() < 20) {
										m_strText.pop_back();
										if (boShift)
											Event.key.keysym.sym = toupper(Event.key.keysym.sym);
										m_strText.push_back(Event.key.keysym.sym);
										m_strText.push_back('_');
									}
									
							}
							break;
					}
					break;
				}
				Draw(m_MenuRenderer);
				SDL_RenderPresent(m_MenuRenderer);
			}
		}
	}
	
	void Draw(SDL_Renderer* _Renderer){
		m_Font->setFontColor(SDL_Color{0,0,0,255});
		SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(_Renderer, &m_Rect);
		m_Font->RenderText(_Renderer, m_strText.c_str(), m_Rect.x, m_Rect.y);
	}
	
};




#endif
