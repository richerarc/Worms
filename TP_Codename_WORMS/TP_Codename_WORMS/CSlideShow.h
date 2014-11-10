/*!
 * Fichier pour la classe CSlideShow
 * Créé le 09/11/2014 à 23h15 par Richer Archambault
 */



class CSlideShow : public CGUIE {
private:
	CButton* m_btnNext;
	CButton* m_btnPrev;
	CLabelImage* m_lblContain;
	CListeDC<SDL_Texture*>* m_ListTexture;
	CListeDC<string*>* m_ListText;
	int m_iIMGSelected;
	int m_iTextSelected;
public:
	CSlideShow(const char* _Name, CFont* _Font, SDL_Rect _Rect, CSprite* _SpritePrev, CSprite* _SpriteNext) :CGUIE(_Name, "", _Font, _Rect){
		m_Font->setFontColor(SDL_Color{ 0, 0, 0, 255 });
		m_btnPrev= new CButton("btnPrev", "", _Font, {0, (m_Rect.h / 2), 42, 22}, _SpritePrev);
		m_btnNext = new CButton("btnNext", "", _Font, {(m_Rect.w - 42), (m_Rect.h / 2), 42, 22}, _SpriteNext);
		m_lblContain = new CLabelImage("lblContain", "", _Font, {((m_Rect.w / 2) -((m_Rect.w - 84) / 2)), 0, (m_Rect.w - 84), m_Rect.h}, nullptr);
		m_ListText = new CListeDC<string*>();
		m_ListTexture = new CListeDC<SDL_Texture*>();
		m_iIMGSelected = 0;
		m_iTextSelected = 0;
	}
	
	void ajouterTexture(int _argc, ...){
		va_list argv;
		va_arg(argv, SDL_Texture*);
		
		va_start(argv, _argc);
		for (int i = 0; i < _argc; i++)
			m_ListTexture->AjouterFin(va_arg(argv, SDL_Texture*));
		va_end(argv);
		setlblContain();
	}
	
	void ajouterText(int _argc, ...){
		va_list argv;
		va_arg(argv, SDL_Texture*);
		
		va_start(argv, _argc);
		for (int i = 0; i < _argc; i++)
			m_ListText->AjouterFin(va_arg(argv, string*));
		va_end(argv);
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
				m_btnNext->CGUIE::HandleEvent(_Event);
				m_iIMGSelected = (m_iIMGSelected + 1) % m_ListTexture->Count();
				m_iTextSelected = (m_iTextSelected + 1) % m_ListText->Count();
			}
			else if ((_Event.button.x >= uiXPrev) &&
				(_Event.button.x <= (uiXPrev + m_btnPrev->getWidth())) &&
				(_Event.button.y >= uiYPrev) &&
				(_Event.button.y <= (uiYPrev + m_btnPrev->getHeight()))){
				m_btnPrev->HandleEvent(_Event);
				m_iIMGSelected = (m_iIMGSelected - 1) % m_ListTexture->Count();
				m_iTextSelected = (m_iTextSelected - 1) % m_ListText->Count();
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
			m_ListTexture->AllerA(m_iIMGSelected);
			m_lblContain->setTexture(m_ListTexture->ObtenirElement());
		}
		if (m_ListText->Count()) {
			m_ListText->AllerA(m_iTextSelected);
			m_lblContain->setText(m_ListText->ObtenirElement()->c_str());
		}
		
	}
	
	/*!
	 @method Draw
	 @param _Renderer : Renderer pour rendre le textures du Sprite et du texte du bouton
	 @return null
	 */
	void Draw(SDL_Renderer * _Renderer){
		m_btnNext->Draw(_Renderer);
		m_btnPrev->Draw(_Renderer);
		m_lblContain->Draw(_Renderer);
	}
	
};
