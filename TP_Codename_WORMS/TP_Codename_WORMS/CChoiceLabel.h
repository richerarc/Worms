class  CChoiceLabel :public CGUIE{
private:
	CButton* PrevButton;
	CButton* NextButton;
	CLabelImage* LabelMap;
public:
	CChoiceLabel(const char* _Name, const char* _strText, CFont* _Font, SDL_Rect _Rect, CButton* _PrevBtn , CButton* _Nextbtn, CLabel* _LabelMap) :CGUIE(){}

	~CChoiceLabel(){}


};