//
//  CListBox.h
//  TP_Codename_WORMS_Mac
//
//  Created by Richer Archambault on 2014-10-28.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//

#ifndef TP_Codename_WORMS_CListBox_h
#define TP_Codename_WORMS_CListBox_h



struct MousePosOnClick {
	static int x;
	static int y;
};

int MousePosOnClick::x = 0;
int MousePosOnClick::y = 0;

/*!
 @class CListBoxItem
 @discussion Classe de base pour implémenter un element de listbox.
 */
class CListBoxItem {
protected:
	const char* m_strName;
	SDL_Rect m_Rect;
	bool m_boSelected;
public:
	
	/*!
	 @method Constructeur
	 @param _Name : Le nom de l'item
	 @param _Rect : La taille et la position de l'item
	 @return Aucun
	 */
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
	
	//
	//Accesseur
	//
	void setSelection(bool _boSelected){
		m_boSelected = _boSelected;
	}
	
	void setSize(int _iw, int _ih){
		m_Rect.w = _iw;
		m_Rect.h = _ih;
	}
	
	void setPos(int _ix, int _iy){
		m_Rect.x =_ix;
		m_Rect.y =_iy;
	}
	
	SDL_Rect getRect(){
		return m_Rect;
	}
	
};

/*!
 @class CLBTextItem
 @discussion Classe pour implémenter un element de listbox s'affichant par du texte
 */
class CLBTextItem : public CListBoxItem {
private:
	CFont* m_Font;
	string m_strText;
public:
	
	/*!
	 @method Constructeur
	 @param _Name : Le nom de l'item
	 @param _Rect : La taille et la position de l'item
	 @param _Font : La police de caractère pour écrire le texte
	 @param _Text : Le texte afficher comme étant l'item
	 @return Aucun
	 */
	CLBTextItem(const char* _Name, SDL_Rect _Rect, CFont* _Font, string _Text) : CListBoxItem(_Name, _Rect){
		
	}
	~CLBTextItem(){
		delete m_Font;
	}
	
	/*!
	 @method Draw
	 @brief Fonction pour dessiner le contrôle visuel sur un Renderer
	 @param _Renderer : Le renderer sur lequel dessiner
	 @return Aucun
	 */
	void Draw(SDL_Renderer* _Renderer){
		if (m_boSelected) {
			m_Font->setFontColor(SDL_Color{255,255,255,255});
			SDL_SetRenderDrawColor(_Renderer, 55, 55, 55, 120);
		}
		else{
			m_Font->setFontColor(SDL_Color{0,0,0,255});
			SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 120);
		}
		SDL_RenderFillRect(_Renderer, &m_Rect);
		m_Font->RenderText(_Renderer, m_strText.c_str(), m_Rect.x, m_Rect.y);
	}
};


/*!
 @class CLBImgItem
 @discussion Classe pour implémenter un element de listbox s'affichant par une image
 */
class CLBImgItem : public CListBoxItem {
private:
	SDL_Texture* m_Texture;
	SDL_Rect m_BgRect;
public:
	
	/*!
	 @method Constructeur
	 @param _Name : Le nom de l'item
	 @param _Rect : La taille et la position de l'item
	 @param _Texture : La texture a dessiné comme étant l'item 
	 @return Aucun
	 */
	CLBImgItem(const char* _Name, SDL_Rect _Rect, SDL_Texture* _Texture) : CListBoxItem(_Name, _Rect){
		m_Texture = _Texture;
		m_BgRect.x = m_Rect.x;
		m_BgRect.y = m_Rect.y;
		m_BgRect.w = m_Rect.w;
		m_BgRect.h = m_Rect.h;
		m_Rect.x -= 3;
		m_Rect.y -= 3;
		m_Rect.w -= 6;
		m_Rect.h -= 6;
		
	}
	~CLBImgItem(){
		SDL_DestroyTexture(m_Texture);
	}
	
	/*!
	 @method Draw
	 @brief Fonction pour dessiner le contrôle visuel sur un Renderer
	 @param _Renderer : Le renderer sur lequel dessiner
	 @return Aucun
	 */
	void Draw(SDL_Renderer* _Renderer){
		if (m_boSelected)
			SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 200);
		else
			SDL_SetRenderDrawColor(_Renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(_Renderer, &m_BgRect);
		SDL_RenderCopy(_Renderer, m_Texture, NULL, &m_Rect);
	}
};

/*!
 @class CListbox
 @discussion Classe pour l'inplémentation d'une listbox
 */
class CListBox : public CGUIE{
private:
	CListeDC<CListBoxItem*>* m_pListItem;
	int m_iItemWidth;
	int m_iItemHeight;
	int m_iMaxItemPerLine;
	int m_iCurrentNbItemOnCurrentLine;
	int m_iCurrentLine;
public:
	void (*OnClickAction)();
	
	/*!
	 @method Constucteur
	 @param _Name : Le nom du Controle visuel
	 @param _strText : Le text contenu dans le controle
	 @param _Font : La police de caractère pour dessiner le texte
	 @param _Rect : Le rectangle pour les information d'affichage (position, hauteur largeur)
	 @param _ItemWidth : La largeur d'un item de la list box
	 @param _ItemHeight : La hauteur d'un item dans la list box
	 */
	CListBox(const char* _Name, string _strText, CFont* _Font, SDL_Rect _Rect, int _ItemWidth, int _ItemHeight) : CGUIE(_Name, _strText, _Font, _Rect){
		m_pListItem = new CListeDC<CListBoxItem*>();
		m_iItemWidth = _ItemWidth;
		m_iItemHeight = _ItemHeight;
		m_iMaxItemPerLine = m_Rect.w / m_iItemWidth;
		m_iCurrentNbItemOnCurrentLine = 0;
		m_iCurrentLine = 0;
	}
	~CListBox(){
		delete m_pListItem;
	}
	
	/*!
	 @method Ajouter
	 @brief Méthode pour ajouté un item dans la listBox
	 @param _Item : L'item à ajouté dans la listbox
	 @return Aucun
	 */
	void Ajouter(CListBoxItem* _Item){
		_Item->setSize(m_iItemWidth, m_iItemHeight);
		_Item->setPos(m_iItemWidth * m_iCurrentNbItemOnCurrentLine, m_iItemHeight * m_iCurrentLine);
		if (m_iCurrentNbItemOnCurrentLine < m_iMaxItemPerLine)
			m_iCurrentNbItemOnCurrentLine++;
		else{
			m_iCurrentLine++;
			m_iCurrentNbItemOnCurrentLine = 0;
		}
		m_pListItem->AjouterFin(_Item);
	}
	
	/*!
	 @method Retirer
	 @brief Méthode pour retirer un item dans la listBox
	 @param _Name : Le nom de l'item à retirer de la listbox
	 @return Aucun
	 */
	void Retirer(const char* _Name){
		//TODO
	}
	
	/*!
	 @method OnClick
	 @brief Méthode pour gérer l'events d'un clic de souri, recu par le menu
	 @param Aucun
	 @return Aucun
	 */
	void OnClick(){
		OnClickAction();
		
	}
};


#endif
