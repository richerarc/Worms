//
//  CGUIE.h
//  TP_Codename_WORMS_Mac
//
//  Created by Richer Archambault on 2014-10-28.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//

#include <string>
#include "CRessource.h"

using namespace std;

#ifndef TP_Codename_WORMS_CGUIE_h
#define TP_Codename_WORMS_CGUIE_h


/*!
 @class CGUIE
 @discussion Classe de base pour les éléments de controles visuels
 */
class CGUIE {
private:
	const char* m_strName;
	string m_strText;
	CFont* m_Font;
	SDL_Rect m_Rect;
	
public:
	CGUIE(const char* _Name, string _strText, CFont* _Font, SDL_Rect _Rect){
		m_strName = _Name;
		m_strText = _strText;
		m_Font = _Font;
		m_Rect.x = _Rect.x;
		m_Rect.y = _Rect.y;
		m_Rect.w = _Rect.w;
		m_Rect.h = _Rect.h;
	}
	
	/*!
	 @method Draw
	 @brief Fonction virtuel pour dessiner le contrôle visuel sur un Renderer
	 @param _Renderer : Le renderer sur lequel dessiner
	 @return Aucun
	 */
	virtual void Draw(SDL_Renderer* _Renderer);
	
		//Accesseur

	string getName(){
		return m_strName;
	}
	
	void setText(const char* _Text){
		m_strText = _Text;
	}
	
	void setPos(int _ix, int _iy){
		m_Rect.x = _ix;
		m_Rect.y = _iy;
	}
	
	void setSize(int _iw, int _ih){
		m_Rect.w = _iw;
		m_Rect.h = _ih;
	}
};

#endif