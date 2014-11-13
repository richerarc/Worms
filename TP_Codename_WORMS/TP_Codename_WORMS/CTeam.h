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

public:
	CTeam(string _strTeamName,SDL_Color _Color,CSprite* _Sprite,SDL_Rect _Rect){
		string strNom = "Worm";
		char Buffer[255];
		for (int i = 0; i < MAXWORMS; i++)
		{
			strNom.append(SDL_itoa(i, Buffer, 10));
			m_pTabWorm[i] = new CWorm(strNom, _Sprite, _Rect);
		}
	}

	void setTeamName(string _strName){ m_strTeamName = _strName; }

	CWorm* getWorm(Uint8 _ui8Pos){
		return m_pTabWorm[_ui8Pos];
	}

	void setTeamColor(SDL_Color _Color){
		m_TeamColor = _Color;
	}

};