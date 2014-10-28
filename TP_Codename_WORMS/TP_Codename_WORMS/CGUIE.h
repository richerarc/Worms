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
	
	virtual void Draw(SDL_Renderer* _Renderer){}
	
	string getName(){
		return m_strName;
	}
	
};

#endif
