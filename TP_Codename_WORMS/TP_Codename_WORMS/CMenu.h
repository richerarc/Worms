/*!
@class CMenus
@discussion Classe qui représente les menus
*/
class CMenu{
private:
	CListeDC<CGUIE*>* m_pList;
	SDL_Renderer* m_pRenderer;
public:

	/*!
	@ Constructeur
	@brief Initialise les données membres
	@param _Window : Fenêtre ou afficher le renderer
	@return l'adresse mémoire de l'objet 
	*/
	CMenu(SDL_Window* _Window){
		m_pList = new CListeDC < CGUIE* >;
		SDL_CreateRenderer(_Window, NULL, NULL);
	}

	bool AddElement(CGUIE* _Element, unsigned int _uiX, unsigned int _uiY, unsigned int _uiW, unsigned int _uiH){
		for (int i = 0; i < m_pList->Count(); i++)
		{
			if (m_pList->ObtenirElement()->getName() == _Element->getName())
				return false;
			m_pList->AllerSuivant();
		}
		m_pList->AjouterFin(_Element);
		return true;
	}

	void setOnScreenPos(const char* _Name, unsigned int _uiX, unsigned int _uiY){
		m_pList->AllerDebut();
		for (int i = 0; i < m_pList->Count(); i++)
		{
			if (m_pList->ObtenirElement()->getName() == _Name){
				m_pList->ObtenirElement()->setPos(_uiX, _uiY);
				break;
			}
			m_pList->AllerSuivant();
		}
	}

	void setSize(const char* _Name, unsigned int _uiWidth, unsigned int _uiHeight){
		m_pList->AllerDebut();
		for (int i = 0; i < m_pList->Count(); i++)
		{
			if (m_pList->ObtenirElement()->getName() == _Name){
				m_pList->ObtenirElement()->setPos(_uiWidth,_uiHeight);
				break;
			}
			m_pList->AllerSuivant();
		}
	}
};