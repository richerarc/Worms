/*!
@class CMenus
@discussion Classe qui représente les menus
*/
class CMenu{
private:
	CListeDC<CGUIE*>* m_pList;
	SDL_Renderer* m_pRenderer;
public:


	CMenu(SDL_Window* _Window){
		m_pList = new CListeDC < CGUIE* >;
		SDL_CreateRenderer(_Window, NULL, NULL);

	}

};