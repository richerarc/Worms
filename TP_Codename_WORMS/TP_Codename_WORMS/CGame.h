//
//  CGame.h
//
//  Created by Kevin Pantelakis on 2014-11-11.
//
class CGame{
private:

	CListeDC<CTeam*>* m_pListeTeam;
	CListeDC<CObjets*>* m_pListeObjets;
	CMap* m_pMap;
	CBoussole* m_pBoussole;
	SDL_Renderer* m_pRenderer;


public:

	CGame(CListeDC<CTeam*>* _Teams, CListeDC<CObjets*>* _ListeObjets, CMap* _Map, CBoussole* _Boussole, SDL_Renderer* _Renderer){
		m_pListeTeam = _Teams;
		m_pListeObjets = _ListeObjets;
		m_pMap = _Map;
		m_pBoussole = _Boussole;
		m_pRenderer = _Renderer;
	}

	~CGame(){
		delete m_pListeTeam;
		delete m_pMap;
		delete m_pBoussole;
	}

};