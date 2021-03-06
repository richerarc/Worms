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
protected:
	const char* m_strName;  // Nom du contrôle visuel.
	string m_strText;		//Text que contien le Contrôle visuel.
	CFont* m_Font;			// Police utilisé.
	SDL_Rect m_Rect;		// Rect d'affichage.
	bool m_boFocussed;		// Indique si le contrôle est actif.

public:
	void(*OnClickAction)();

	/*!
	@method Constucteur
	@param _Name : le nom du Controle visuel
	@param _strText : le text contenu dans le controle
	@param _Font : La police de caractère pour dessiner le texte
	@param _Rect : le rectangle pour les information d'affichage (position, hauteur largeur)
	*/
	CGUIE(const char* _Name, string _strText, CFont* _Font, SDL_Rect _Rect){
		m_strName = _Name;
		m_strText = _strText;
		m_Font = _Font;
		m_Rect.x = _Rect.x;
		m_Rect.y = _Rect.y;
		m_Rect.w = _Rect.w;
		m_Rect.h = _Rect.h;
		m_boFocussed = false;
	}

	~CGUIE(){
	}

	/*!
	@method Draw
	@brief Fonction virtuel pour dessiner le contrôle visuel sur un Renderer
	@param _Renderer : Le renderer sur lequel dessiner
	@return Aucun
	*/
	virtual void Draw(SDL_Renderer* _Renderer){};

	/*!
	@method HandleEvent
	@param _Evant : Un SDL_Event pour traiter les evenement
	@return null
	*/
	virtual void HandleEvent(SDL_Event _Event){};

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	string getName(){
		return m_strName;
	}

	void setText(const char* _Text){
		m_strText = _Text;
	}

	virtual void setPos(int _ix, int _iy){
		m_Rect.x = _ix;
		m_Rect.y = _iy;
	}

	virtual void setSize(int _iw, int _ih){
		m_Rect.w = _iw;
		m_Rect.h = _ih;
	}

	unsigned int getX(){
		return m_Rect.x;
	}

	unsigned int getY(){
		return m_Rect.y;
	}

	unsigned int getWidth(){
		return m_Rect.w;
	}

	unsigned int getHeight(){
		return m_Rect.h;
	}

	virtual string getText(){
		return m_strText;
	}

	virtual bool isFocussed(){ return m_boFocussed; }

	virtual void setFocus(bool _Focus){ m_boFocussed = _Focus; }

	virtual bool isTextBox(){ return false; }
};

#endif
