/*!
 * Fichier pour la classe CSlideShow
 * Créé le 09/11/2014 à 23h15 par Richer Archambault
 */

class CSlideShow : public CGUIE {
private:
	CButton* m_btnNext;					   // Boutton Suivant.
	CButton* m_btnPrev;					   // Boutton Précédant.
	CLabelImage* m_lblContain;			   // Label Image a afficher.
	CListeDC<SDL_Texture*>* m_ListTexture; // Liste de texture.
	CListeDC<string*>* m_ListText;		   // Liste de Textes.
	unsigned int m_uiCurrentSlide;		   // slide à afficher
	unsigned int m_uiCount;				   // Nombre d'élément dans le slideshow
	SDL_Rect m_RectFilled;
public:
	CSlideShow(const char* _Name, CFont* _Font, SDL_Rect _Rect, CSprite* _SpritePrev, CSprite* _SpriteNext) :CGUIE(_Name, "", _Font, _Rect){
		m_Font->setFontColor(SDL_Color{ 0, 0, 0, 255 });
		if (m_Rect.h <= 22){
			m_btnPrev= new CButton("btnPrev", "", _Font, {m_Rect.x, m_Rect.y, 42, 22}, _SpritePrev);
			m_lblContain = new CLabelImage("lblContain", "", _Font, {m_Rect.x + 42 + (m_Rect.w - 110), m_Rect.y - 4, (m_Rect.w - 84), m_Rect.h}, nullptr);
			m_btnNext = new CButton("btnNext", "", _Font, {(m_Rect.x + 42 + (m_Rect.w - 84)), m_Rect.y, 42, 22}, _SpriteNext);
		}
		else{
			m_btnPrev= new CButton("btnPrev", "", _Font, {m_Rect.x, (m_Rect.h / 2), 42, 22}, _SpritePrev);
			m_lblContain = new CLabelImage("lblContain", "", _Font, {m_Rect.x + 42, m_Rect.y, (m_Rect.w - 84), m_Rect.h}, nullptr);
			m_btnNext = new CButton("btnNext", "", _Font, {(m_Rect.x + 42 + (m_Rect.w - 84)), (m_Rect.h / 2), 42, 22}, _SpriteNext);
		}
		m_ListText = new CListeDC<string*>();
		m_ListTexture = new CListeDC<SDL_Texture*>();
		m_uiCurrentSlide = 0;
		m_uiCount = 0;
		m_RectFilled = {m_Rect.x + 42, m_Rect.y, m_Rect.w - 84, m_Rect.h};
	}
	
	void ajouterTexture(int _argc, ...){										//
		va_list argv;															//
		va_start(argv, _argc);													// Attention, Une slide, est
		for (int i = 0; i < _argc; i++)											// une texture sur laquelle
			m_ListTexture->AjouterFin(va_arg(argv, SDL_Texture*));				// on affiche du texte, pour m'avoir
		va_end(argv);															// que du texte, ne pas mettre de texture.
		m_uiCount = m_ListTexture->Count();										//
		setlblContain();														//
	}																			//
																				//
	void ajouterText(int _argc, ...){											//
		va_list argv;															//
		va_start(argv, _argc);													//
		for (int i = 0; i < _argc; i++)											//
			m_ListText->AjouterFin(va_arg(argv, string*));						//
		va_end(argv);
		if (!m_ListTexture->Count())
			m_uiCount = m_ListText->Count();
		setlblContain();
	}
	
	/*!
	 @method HandleEvent
	 @param _Evant : Un SDL_Event pour traiter les evenement
	 @return null
	 */
	void HandleEvent(SDL_Event _Event){
		int uiXNext, uiYNext, uiXPrev, uiYPrev;
		if (_Event.type == SDL_MOUSEBUTTONDOWN){
			uiXNext = m_btnNext->getX();
			uiYNext = m_btnNext->getY();
			uiXPrev = m_btnPrev->getX();
			uiYPrev = m_btnPrev->getY();
			if ((_Event.button.x >= uiXNext) &&
				(_Event.button.x <= (uiXNext + m_btnNext->getWidth())) &&
				(_Event.button.y >= uiYNext) &&
				(_Event.button.y <= (uiYNext + m_btnNext->getHeight()))){
				m_uiCurrentSlide = (m_uiCurrentSlide + 1) % m_uiCount;
				m_btnNext->HandleEvent(_Event);
			}
			else if ((_Event.button.x >= uiXPrev) &&
				(_Event.button.x <= (uiXPrev + m_btnPrev->getWidth())) &&
				(_Event.button.y >= uiYPrev) &&
				(_Event.button.y <= (uiYPrev + m_btnPrev->getHeight()))){
				m_uiCurrentSlide = (m_uiCurrentSlide - 1) % m_uiCount;
				m_btnPrev->HandleEvent(_Event);
			}
			setlblContain();
		}
	}
	
	/*!
	 @method setlblContain
	 @brief Methode pour configurer le contenue du label.
	 @param Aucun
	 @return Aucun
	 */
	void setlblContain(){
		if (m_ListTexture->Count()){
			m_ListTexture->AllerA(m_uiCurrentSlide);
			m_lblContain->setTexture(m_ListTexture->ObtenirElement());
		}
		if (m_ListText->Count()) {
			m_ListText->AllerA(m_uiCurrentSlide);
			m_lblContain->setText(m_ListText->ObtenirElement()->c_str());
		}
		
	}
	
	/*!
	 @method setOnClickPrev
	 @brief Methode pour configurer l'action onclick du bouton previous.
	 @param Aucun
	 @return Aucun
	 */
	void setOnClickPrev(void(*_func)()){
		m_btnPrev->OnClickAction = _func;
	}
	
	/*!
	 @method setOnClickNext
	 @brief Methode pour configurer l'action onclick du bouton next.
	 @param Aucun
	 @return Aucun
	 */
	void setOnClickNext(void(*_func)()){
		m_btnNext->OnClickAction = _func;
	}
	
	string getText(){
		m_ListText->AllerA(m_uiCurrentSlide);
		return *m_ListText->ObtenirElement();
	}
	
	/*!
	 @method Draw
	 @param _Renderer : Renderer pour rendre le textures du Sprite et du texte du bouton
	 @return null
	 */
	void Draw(SDL_Renderer * _Renderer){
		SDL_SetRenderDrawColor(_Renderer, 210, 214, 217, 1);
		SDL_RenderFillRect(_Renderer, &m_RectFilled);
		m_btnNext->Draw(_Renderer);
		m_btnPrev->Draw(_Renderer);
		m_Font->setFontColor({0,0,0,255});
		m_lblContain->Draw(_Renderer);
		SDL_SetRenderDrawColor(_Renderer, 255, 255, 255, 1);
	}
	
	unsigned int getCurrentSlideId(){
		return m_uiCurrentSlide;
	}
	
};
