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
	unsigned short m_usrtNbWorms;

public:


	CTeam(string _strTeamName,SDL_Color _Color){
		string strNom = "Worm";
		char Buffer[255];
		for (int i = 0; i < MAXWORMS; i++)
		{
			m_pTabWorm[i] = new CWorm(strNom.append(SDL_itoa(i, Buffer, 10)), CSprite, SDL_Rect)
		}
	}

};