//
//  CTeam.h
//  
//  Created by Kevin Pantelakis on 2014-11-11.
//
#define MAXWORMS 6
/*!
@class CTeam
@discussion Classe représentant une équipe.
*/
class CTeam{
private:
	string m_strTeamName;
	CWorm* m_pTabWorm[6];
	SDL_Color m_TeamColor;
	Uint8 m_uiNbOfPlayingWorms;
	Uint8 m_uiWormTurn;
	bool m_boFocus;

public:

	CTeam(string _strTeamName, SDL_Color _Color, CSprite* _Sprite, SDL_Rect _Rect, CFont* _Font){
		string strNom = "Worm";
		char Buffer[255];
		for (int i = 0; i < MAXWORMS; i++)
		{
			strNom.append(SDL_itoa(i, Buffer, 10));
			m_pTabWorm[i] = new CWorm(strNom, _Sprite, _Font, _Rect);
			strNom.pop_back();
		}
		m_boFocus = false;
		m_pTabWorm[0]->setFocus(true);
		m_uiWormTurn = 0;
	}


	void setFocus(bool _boFocus){ m_boFocus = _boFocus; }

	bool IsFocussed(){ return m_boFocus; }

	void NextWormTurn(){
		if (m_pTabWorm[(m_uiWormTurn - 1) % 6]->isFocused()){
			m_pTabWorm[(m_uiWormTurn - 1) % 6]->setFocus(false);
		}
		m_pTabWorm[m_uiWormTurn % 6]->setFocus(true);
	}

	void setTeamName(string _strName){
		m_strTeamName = _strName; 
	}

	CWorm* getPlayingWorm(){ return m_pTabWorm[m_uiWormTurn % 6]; }

	void setTeamColor(SDL_Color _Color){
		m_TeamColor = _Color;
	}

};