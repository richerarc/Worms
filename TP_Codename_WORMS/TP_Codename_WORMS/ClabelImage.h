#ifndef TP_Codename_WORMS_CLabelImage_h
#define TP_Codename_WORMS_CLabelImage_h


/*!
@CLabelImage
@Classe permettant la création et l'affichage d'un label contenant du texte et une image.
*/
class CLabelImage : public CLabel {
private:
	//Données membres:
	SDL_Texture* m_pTexture; // Texture de l'image à afficher.

public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param  _Name :Le nom du labelImage afin de l'identifier.
	@param  _strText le text à l'intérieur.
	@param _Font: la police utilisée
	@param _Rect: le rect.
	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de CGUIE, donc elle passe les paramètres nécessaires au constructeur de CGUIE.
	*/
	CLabelImage(const char* _Name, const char* _strText, CFont* _Font, SDL_Rect _Rect, SDL_Texture* _Texture) :CLabel(_Name, _strText, _Font, _Rect){
		m_pTexture = _Texture;
		m_Font->setFontColor(SDL_Color{ 0, 0, 0, 0 });

	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead.
	*/
	~CLabelImage(){
	}


	/*!
	@method Draw:
	@brief permet de dessiner le LabelImage sur le renderer.
	@param Le renderer sur lequel on dessine l'image
	@discussion: none
	*/
	void Draw(SDL_Renderer* _Renderer){
		SDL_RenderCopy(_Renderer, m_pTexture, NULL, &m_Rect);
		m_Font->RenderText(_Renderer, m_strText.c_str(), m_Rect.x, m_Rect.y);
	}

	/*!
	@method AutoSize
	@brief Fonction permettant de rendre l'image du label de la même dimension que le texte.
	@discussion: none
	*/
	void Autosize(){
		m_Rect.w = m_strText.length() * (m_Font->getFontSize());
		m_Rect.h = m_Font->getFontSize();
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
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
	
	void setTexture(SDL_Texture* _texture){
		m_pTexture = _texture;
	}
};

#endif
