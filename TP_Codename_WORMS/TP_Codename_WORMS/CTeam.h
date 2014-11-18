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

	CTeam(string _strTeamName, SDL_Color _Color, CSprite* _Sprite, CFont* _Font){
		string strNom = "Worm";
		char Buffer[255];
		for (int i = 0; i < MAXWORMS; i++)
		{
			strNom.append(SDL_itoa(i, Buffer, 10));
			m_pTabWorm[i] = new CWorm(strNom, _Sprite, _Font, {0,0,0,0});
			strNom.pop_back();
		}
		m_boFocus = false;
		m_pTabWorm[0]->setFocus(true);
		m_uiWormTurn = 0;
		m_uiNbOfPlayingWorms = 1;
	}

	void NextWormTurn(){
		Uint8 temp = (m_uiWormTurn) % m_uiNbOfPlayingWorms;
		if (m_pTabWorm[temp]->isFocused()){
			m_pTabWorm[temp]->setFocus(false);
		}
		m_pTabWorm[(temp + 1) % m_uiNbOfPlayingWorms]->setFocus(true);
		m_uiWormTurn++;
	}

	void draw(SDL_Renderer* _Renderer){
		for (int i = 0; i < m_uiNbOfPlayingWorms; i++)
			m_pTabWorm[i]->Draw(_Renderer);
	}

	/*!
	@Accesseurs
	*/
	void setNbPlayingWorm(Uint8 _uiNumber){ m_uiNbOfPlayingWorms = _uiNumber; }

	void setFocus(bool _boFocus){ m_boFocus = _boFocus; }

	void setTeamColor(SDL_Color _Color) { m_TeamColor = _Color; }

	void setTeamName(string _strName){ m_strTeamName = _strName; }

	bool IsFocussed(){ return m_boFocus; }

	Uint8 getNumberOfPlayingWorms(){ return m_uiNbOfPlayingWorms; }

	string getTeamName(){ return m_strTeamName; }

	CWorm* getPlayingWorm(){ return m_pTabWorm[m_uiWormTurn % m_uiNbOfPlayingWorms]; }



};