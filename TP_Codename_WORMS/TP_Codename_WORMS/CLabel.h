//
//  CLabel.h
//  TP_Codename_WORMS_Mac
//
//  Créé par Jessy Desjardins le 2014-10-28.
//  Mise à jour par Jessy Desjardins le 2014-10-29
//  
//

#ifndef TP_Codename_WORMS_CLabel_h
#define TP_Codename_WORMS_CLabel_h




/*!
@class CLabel
@Permet la création et l'utilisation d'un label.
*/
class CLabel : public CGUIE {
private:

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@Paramètres: Le nom du labelImage afin de l'identifier, le text à l'intérieur, le font et le rect.
	@Classe héritant de CGUIE, donc elle passe les paramètres nécessaires au constructeur de CGUIE
	*/

	CLabel(const char* _Name, const char* _strText, CFont* _Font, SDL_Rect _Rect) :CGUIE(_Name, _strText, _Font, _Rect){

	}
	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CLabel(){
	}

	/*!
	@Méthode Draw:
	@Fonction permettant de dessiner le Label sur le renderer.
	@Paramètre: Le renderer sur lequel on dessine l'image
	*/
	void Draw(SDL_Renderer* _Renderer){
		m_Font->setFontColor(SDL_Color{ 0, 0, 0, 0 });
		SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(_Renderer, &m_Rect);
		m_Font->RenderText(_Renderer, m_strText.c_str(), m_Rect.x, m_Rect.y);
	}

	/*!
	@Accesseurs:
	*/
	int ObtenirWidth(){
		return m_Rect.w;
	}
	int ObtenirHeight(){
		return m_Rect.h;
	}
};




/*!
@CLabelImage
@Classe permettant la création et l'affichage d'un label contenant du texte et une image.
*/
class CLabelImage : public CLabel {
private:
	//Données membres:
	SDL_Texture* m_pTexture;

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@Paramètres: Le nom du labelImage afin de l'identifier, le text à l'intérieur, le font et le rect, et la texture contenant l'image.
	@Classe héritant de CGUIE, donc elle passe les paramètres nécessaires au constructeur de CGUIE
	*/
	CLabelImage(const char* _Name, const char* _strText, CFont* _Font, SDL_Rect _Rect, SDL_Texture* _Texture) :CLabel(_Name,, _strText, _Font, _Rect){
		m_pTexture = _Texture;
	}
	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CLabelImage(){
		SDL_DestroyTexture(m_pTexture);
	}
	/*!
	@Méthode Draw:
	@Fonction permettant de dessiner le LabelImage sur le renderer.
	@Paramètre: Le renderer sur lequel on dessine l'image
	*/
	void Draw(SDL_Renderer* _Renderer){
		m_Font->setFontColor(SDL_Color{ 0, 0, 0, 0 });
		SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(_Renderer, &m_Rect);
		SDL_RenderCopy(_Renderer, m_pTexture, NULL, &m_Rect);
		m_Font->RenderText(_Renderer, m_strText.c_str(), m_Rect.x, m_Rect.y);
	}

	/*!
	@Accesseurs:
	*/

	int ObtenirWidth(){
		return m_Rect.w;
	}
	int ObtenirHeight(){
		return m_Rect.h;
	}
};

#endif
