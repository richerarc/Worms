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
		m_Font->setFontColor(SDL_Color{ 0, 0, 0, 255 });
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
		m_Font->setFontColor({0,0,0,255});
		m_Font->RenderText(_Renderer, m_strText.c_str(), m_Rect.x, m_Rect.y);
	}

	/*!
	@Accesseurs:
	*/
	void DefinirFontColor(Uint8 _iR, Uint8 _iB, Uint8 _iG, Uint8 _iA){
		m_Font->setFontColor(SDL_Color{ _iR, _iB, _iG, _iA });
	}

	void DefinirPositionLabel(int _iX, int _iY){
		m_Rect.x = _iX;
		m_Rect.y = _iY;
	}

	int ObtenirWidth(){
		return m_Rect.w;
	}
	int ObtenirHeight(){
		return m_Rect.h;
	}
};
#endif
