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
	CSprite * m_Sprite;  // Sprite du boutton.
	bool m_boClicked;    // Indique si le bouton à été cliqué.
	SDL_Rect m_RectText; // Position du texte.
public:
	
	/*!
	 @method Constucteur
	 @param _Name : le nom du Controle visuel
	 @param _strText : le text contenu dans le controle
	 @param _Font : La police de caractère pour dessiner le texte
	 @param _Rect : le rectangle pour les information d'affichage (position, hauteur largeur)
	 @param _Sprite : le Sprite qui sert à afficher les versions on/off du bouton
	 */
	CButton(const char* _Name, string _strText, CFont* _Font, SDL_Rect _Rect, CSprite * _Sprite) : CGUIE(_Name, _strText, _Font, _Rect){
		m_Sprite = _Sprite;
		OnClickAction = nullptr;
		m_boClicked = false;
		m_RectText.x = m_Rect.x;
		m_RectText.y = m_Rect.y;
		m_RectText.w = m_Rect.w;
		m_RectText.h = m_Rect.h;
		m_Sprite->setSpritePos(m_Rect.x, m_Rect.y);
	}

	/*!
	@method HandleEvent
	@param _Evant : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event _Event){
		if (_Event.type == SDL_MOUSEBUTTONDOWN){
			if (OnClickAction != nullptr)
				OnClickAction();
			m_boClicked = true;
		}
	}

	//Acesseurs.

	void setPos(int _ix, int _iy){
		m_Rect.x = _ix;
		m_Rect.y = _iy;
		setTextPos(_ix, _iy);
		m_Sprite->setSpritePos(m_Rect.x, m_Rect.y);
	}

	void setTextPos(int _ix, int _iy){
		m_RectText.x = _ix;
		m_RectText.y = _iy;
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre le textures du Sprite et du texte du bouton
	@return null
	*/
	void Draw(SDL_Renderer * _Renderer){
		if (m_boFocussed && (m_RectText.x == m_Rect.x))
			setTextPos(m_RectText.x + 10, m_Rect.y);
		else if (!m_boFocussed && (m_RectText.x != m_Rect.x))
			setTextPos(m_Rect.x, m_Rect.y);
		
		if (m_boClicked){
			m_Sprite->Render(_Renderer, 1);
			m_boClicked = false;
		}
		else
			m_Sprite->Render(_Renderer, 0);
		m_Font->setFontColor(SDL_Color{ 255, 255, 255, 0 });
		m_Font->RenderText(_Renderer, m_strText.c_str(), m_RectText.x, m_RectText.y);
	}

	/*!
	@method Destructeur : Permet de détruire les objets créés en mémoire
	*/
	~CButton(){
	}

};
#endif
