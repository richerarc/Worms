//
//  CListBox.h
//  TP_Codename_WORMS_Mac
//
//  Created by Richer Archambault on 2014-10-28.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//

#ifndef TP_Codename_WORMS_CListBox_h
#define TP_Codename_WORMS_CListBox_h

class CListBoxItem {
protected:
	const char* m_strName;
	SDL_Rect m_Rect;
public:
	CListBoxItem(const char* _Name, SDL_Rect _Rect){
		m_strName = _Name;
		m_Rect.x = _Rect.x;
		m_Rect.y = _Rect.y;
		m_Rect.w = _Rect.w;
		m_Rect.h = _Rect.h;
	}
	
	~CListBoxItem(){
		delete  m_strName;
	}
};

class CLBTextItem : public CListBoxItem {
private:
	CFont* m_Font;
	string m_strText;
public:
	
};

class CLBImgItem : public CListBoxItem {
private:
	
public:
	
};

/*!
 @class CListbox
 @discussion Classe pour l'inplémentation d'une listbox
 */
class CListBox {
private:
	
public:
	
};


#endif
