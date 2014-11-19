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
	Uint8 m_pNumberOfWorm;
	Uint8 m_uiNbOfPlayingWorms;
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
	CTeam(string _strTeamName, SDL_Color _Color){
		m_boFocus = false;
		m_uiWormTurn = 0;
		m_pNumberOfWorm = 0;
		m_uiNbOfPlayingWorms = 0;
	}

	/*!
	@method NextTurn
	@brief Change le focus des Worms pour le tour suivant.
	*/
	void NextTurn(){
		Uint8 temp = (m_uiWormTurn) % m_uiNbOfPlayingWorms;
		if (m_pTabWorm[temp]->isFocused()){
			m_pTabWorm[temp]->setFocus(false);
		}
		m_pTabWorm[(temp + 1) % m_uiNbOfPlayingWorms]->setFocus(true);
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
		for (int i = 0; i < m_uiNbOfPlayingWorms; i++)
			m_pTabWorm[i]->Draw(_Renderer);
	}

	/*!
	@method AddWorn
	@brief Ajoute un Worm à l'équipe.
	@param _Worm : le worm a ajouter.
	*/
	void AddWorm(CWorm* _Worm){
		m_pTabWorm[m_pNumberOfWorm] = _Worm;

		if (!m_pNumberOfWorm)
			m_pTabWorm[m_pNumberOfWorm]->setFocus(true);
		else
			m_pTabWorm[m_pNumberOfWorm]->setFocus(false);

		m_pNumberOfWorm++;
	}

	/*!
	@Accesseurs
	*/
	void setNbPlayingWorm(Uint8 _uiNumber){ m_uiNbOfPlayingWorms = _uiNumber; }

	void setFocus(bool _boFocus){ m_boFocus = _boFocus; }

	void setTeamColor(SDL_Color _Color) { m_TeamColor = _Color; }

	void setTeamName(string _strName){ m_strTeamName = _strName; }

	bool IsFocused(){ return m_boFocus; }

	Uint8 getNumberOfPlayingWorms(){ return m_uiNbOfPlayingWorms; }

	string getTeamName(){ return m_strTeamName; }

	CWorm* getPlayingWorm(){ return m_pTabWorm[m_uiWormTurn % m_uiNbOfPlayingWorms]; }



};