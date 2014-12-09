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
	Uint8 m_uiNbOfWorm;
	Uint8 m_uiWormTurn;
	bool m_boFocus;

public:
	
	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _strTeamName: Nom de l'équipe
	@param _Color: Couleur de l'équipe
	@return Adresse mémoire de l'objet.
	@discussion Voilà.
	*/
	CTeam(string _strTeamName, SDL_Color _Color, SDL_Texture* _WormRepo, SDL_Texture* _TexSprite, Uint8 _uiNbWorms, CFont* _Font){
		m_boFocus = false;
		m_uiWormTurn = 0;
		m_TeamColor = _Color;
		m_strTeamName = _strTeamName;
		m_uiNbOfWorm = _uiNbWorms;
		string strNom = "Worm";
		char Buffer[255];
		for (int i = 0; i < _uiNbWorms; i++)
		{
			strNom.append(" ");
			strNom.append(SDL_itoa(i, Buffer, 10));
			//Il manque des données pour créer l'équipes.
			m_pTabWorm[i] = new CWorm(strNom, _WormRepo, new CSprite("", _TexSprite, 10, 17, 80, -1), _Font, { rand() % WIDTH, -50, 30, 50 }, &_Color);
			strNom.pop_back();
			strNom.pop_back();
		}
		m_pTabWorm[0]->setFocus(true);
	}

	/*!
	@method NextTurn
	@brief Change le focus des Worms pour le tour suivant.
	*/
	void NextTurn(){
		Uint8 temp = (m_uiWormTurn) % m_uiNbOfWorm;
		if (m_pTabWorm[temp]->isFocused()){
			m_pTabWorm[temp]->setFocus(false);
		}
		m_pTabWorm[(temp + 1) % m_uiNbOfWorm]->setFocus(true);
		m_uiWormTurn++;
	}

	/*!
	@method Draw
	@brief Affiche l'équipe
	@param SDL_Renderer* _Renderer: Rendu de la fenetre sur laquelle afficher.
	@return Aucun
	@discussion 
	*/
	void draw(SDL_Renderer* _Renderer){
		for (int i = 0; i < m_uiNbOfWorm; i++)
			m_pTabWorm[i]->Draw(_Renderer);
	}
	
	
	void HandleEvent(SDL_Event _Event){
		for (int i(0); i < m_uiNbOfWorm; i++)
			if(m_pTabWorm[i]->isFocused()){
				m_pTabWorm[i]->HandleEvent(_Event);
				break;
			}
	}

	/*!
	@Accesseurs
	*/
	void setFocus(bool _boFocus){ m_boFocus = _boFocus; }

	void setTeamColor(SDL_Color _Color) { m_TeamColor = _Color; }

	void setTeamName(string _strName){ m_strTeamName = _strName; }

	bool IsFocused(){ return m_boFocus; }

	string getTeamName(){ return m_strTeamName; }

	CWorm* getPlayingWorm(){ return m_pTabWorm[m_uiWormTurn %  m_uiNbOfWorm]; }




};