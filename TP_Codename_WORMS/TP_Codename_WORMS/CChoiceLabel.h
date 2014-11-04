class  CChoiceLabel :public CGUIE{
private:
	CButton* m_pPrevButton;
	CButton* m_pNextButton;
	CLabelImage* m_pLabelMap;
public:
	CChoiceLabel(const char* _Name, SDL_Rect _Rect, CSprite* _SpritePrev, CSprite* _SpriteNext, SDL_Texture* _Texture) :CGUIE(_Name, "", nullptr, _Rect){
		m_pPrevButton = new CButton("NextBtn","",nullptr,_Rect,_SpritePrev);
		m_pNextButton = new CButton("PrevBtn","",nullptr,_Rect,_SpriteNext);
		m_pLabelMap = new CLabelImage("LblMap","",nullptr,_Rect,_Texture);
	}

	~CChoiceLabel(){
		delete m_pPrevButton;
		delete m_pNextButton;
		delete m_pLabelMap;
	}

	void OnClick(){
		if ( != nullptr){
			OnClickAction();
		}
	}

};