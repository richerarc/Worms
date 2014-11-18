//
//  CGame.h
//
//  Created by Kevin Pantelakis on 2014-11-11.
//
class CGame{
private:
	Uint8 m_uiTeamTurn;
	Uint8 m_uiNbOfPlayingTeams;
	SDL_Renderer* m_pRenderer;
	CBoussole* m_pBoussole;
	CMap* m_pMap;
	CListeDC<CTeam*>* m_pListeTeam;
	CListeDC<CObjets*>* m_pListeObjets;
	bool m_boInPlay;
public:

	CGame(CListeDC<CTeam*>* _Teams, CListeDC<CObjets*>* _ListeObjets, CMap* _Map, CBoussole* _Boussole, SDL_Renderer* _Renderer){
		m_pListeTeam = _Teams;
		m_pListeObjets = _ListeObjets;
		m_pMap = _Map;
		m_pBoussole = _Boussole;
		m_pRenderer = _Renderer;
		m_uiNbOfPlayingTeams = 0;
		m_uiTeamTurn = 0;
		m_boInPlay = false;
	}

	~CGame(){
		delete m_pListeTeam;
		delete m_pMap;
		delete m_pBoussole;
	}

	void NextTurn(){
		Uint8 uitemp = m_uiTeamTurn % m_uiNbOfPlayingTeams;
		m_pListeTeam->AllerA(uitemp);
		if (m_pListeTeam->ObtenirElement()->IsFocussed()) { 
			m_pListeTeam->ObtenirElement()->setFocus(false);
		}
		m_pListeTeam->AllerA((uitemp + 1) % m_uiNbOfPlayingTeams);
		m_pListeTeam->ObtenirElement()->setFocus(true);
	}

	void Renderer(){
		m_pMap->Draw(m_pRenderer);
		m_pBoussole->Draw(m_pRenderer);
		m_pListeTeam->AllerDebut();
		m_pListeObjets->AllerDebut();
		for (int i = 0; i < m_uiNbOfPlayingTeams; i++)
		{
			m_pListeTeam->ObtenirElement()->draw(m_pRenderer);
			m_pListeTeam->AllerSuivant();
		}
		for (int i = 0; i < m_pListeObjets->Count(); i++)
		{
			m_pListeObjets->ObtenirElement()->Draw(m_pRenderer);
			m_pListeTeam->AllerSuivant();
		}
	}

	void setNbOfPlayingTeams(Uint8 _NbOfTeams){ m_uiNbOfPlayingTeams = _NbOfTeams; }

	Uint8 getNbOfPlayingTeams(){ return m_uiNbOfPlayingTeams; }

};