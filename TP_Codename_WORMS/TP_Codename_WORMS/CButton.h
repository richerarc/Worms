//
//  CButton.h
//  TP_Codename_WORMS_Mac
//
//  Created by Richer Archambault on 2014-10-28.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//

#ifndef TP_Codename_WORMS_CButton_h
#define TP_Codename_WORMS_CButton_h

/*!
 @class CButton
 @discussion Classe pour implémenter un bouton
 */
class CButton : public CGUIE{
private:
	CSprite * m_Sprite;
public:
	CButton(const char* _Name, string _strText, CFont* _Font, SDL_Rect _Rect, CSprite * _Sprite) : CGUIE(_Name, _strText, _Font, _Rect){
		m_Sprite = _Sprite;
	}
	void(*OnClickAction)();
	void OnClick(){
		if (OnClickAction != nullptr){
			m_Sprite->setCurrentAnimation(2);
		}
	}
	void Draw(SDL_Renderer * _Renderer){
		m_Sprite->Render(_Renderer);
		m_Font->setFontColor(SDL_Color{ 0, 0, 0, 0 });
		SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(_Renderer, &m_Rect);
		m_Font->RenderText(_Renderer, m_strText.c_str(), m_Rect.x, m_Rect.y);
	}
	~CButton(){
		delete m_Sprite;
	}
	
};



#endif
