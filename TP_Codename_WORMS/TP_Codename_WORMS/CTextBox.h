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
	SDL_Texture* m_texture; // Texture de la textBox
	SDL_Renderer* m_MenuRenderer; // Rendu.
	SDL_Rect m_RectFrame;
	bool m_boClick , m_boShift;
public:
	
	/*!
	 @method Constucteur
	 @param _Name : le nom du Controle visuel
	 @param _strText : le text contenu dans le controle
	 @param _Font : La police de caractère pour dessiner le texte
	 @param _Rect : le rectangle pour les information d'affichage (position, hauteur largeur)
	 */
	CTextBox(const char* _Name, string _strText, CFont* _Font, SDL_Rect _Rect, SDL_Renderer* _MenuRenderer) : CGUIE(_Name, _strText, _Font, _Rect){
		m_strText = "";
		m_MenuRenderer = _MenuRenderer;
		m_Rect.x += 1;
		m_Rect.y += 1;
		m_RectFrame.x = m_Rect.x - 2;
		m_RectFrame.y = m_Rect.y - 2;
		m_RectFrame.w = m_Rect.w + 2;
		m_RectFrame.h = m_Rect.h + 2;
		m_boClick = true;
		m_boShift = false;
	}
	
	~CTextBox(){
		SDL_DestroyTexture(m_texture);
	}
	
	/*!
	 @method HandleEvent
	 @brief Méthode pour gérer l'events d'un clic de souri, recu par le menu
	 @param Aucun
	 @return Aucun
	 */
	void HandleEvent(SDL_Event _Event){
		if ((m_boFocussed) && !(m_strText[m_strText.length() - 1] == '_'))
			m_strText.push_back('_');
		switch (_Event.type) {
			case SDL_MOUSEBUTTONDOWN:
				if (!m_boClick) {
					m_boClick = true;
					m_boFocussed = false;
					if(*m_strText.rbegin() == '_')
						m_strText.pop_back();
				}
				else m_boClick = false;
				break;
				
			case SDL_KEYUP:
				if ((_Event.key.keysym.sym == SDLK_RSHIFT) || (_Event.key.keysym.sym == SDLK_LSHIFT))
					m_boShift = false;
				break;
				
			case SDL_KEYDOWN:
				switch (_Event.key.keysym.sym) {
					case SDLK_LSHIFT:
					case SDLK_RSHIFT:
						m_boShift = true;
						break;
					case SDLK_ESCAPE:			// Pour sortir de l'édition de la textBox
					case SDLK_RETURN:			// il faut appuyer sur enter ou sur escape
						if(*m_strText.rbegin() == '_')
							m_strText.pop_back();
						m_boFocussed = false;
						break;
					case SDLK_BACKSPACE:
						if (m_strText != "_"){
							m_strText.pop_back();
							m_strText.pop_back();
							m_strText.push_back('_');
						}
						break;
					default:
						if (m_strText.length() < (m_Rect.w / 12)) {
							m_strText.pop_back();
							if (m_boShift)
								_Event.key.keysym.sym = toupper(_Event.key.keysym.sym);
							m_strText.push_back(_Event.key.keysym.sym);
							m_strText.push_back('_');
						}
						break;
				}
				break;
		}
		Draw(m_MenuRenderer);				// On applique les modification de la string
		SDL_RenderPresent(m_MenuRenderer);  // directement en live à l'écran
	}
	
	/*!
	 @method Draw
	 @brief Fonction virtuel pour dessiner le contrôle visuel sur un Renderer
	 @param _Renderer : Le renderer sur lequel dessiner
	 @return Aucun
	 */
	void Draw(SDL_Renderer* _Renderer){
		m_Font->setFontColor(SDL_Color{0,0,0,255});
		SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(_Renderer, &m_RectFrame);
		SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(_Renderer, &m_Rect);
		m_Font->RenderText(_Renderer, m_strText.c_str(), m_Rect.x, m_Rect.y);
	}
	
	
	bool isTextBox(){return true;}
};




#endif
