//
//  CGame.h
//
//  Created by Kevin Pantelakis on 2014-11-11.
//
// TO DO: PARLER A RICHER POUR LE TABLEAU INT POUR LES INDICES DES ÉQUIPES QUI JOUENT
//        COMME SA ON EVITRAIS D'UTILISER UNE LISTE ET ON AURAIT SEULEMENT UN TABLEAU
//		  D'ÉQUIPE POUR TOUT LE PROGRAMME.
//

/*!
@class CGame.h
@discussion Classe qui représente une partie.
*/
class CGame{
private:
	Uint8 m_uiTeamTurn;					// Indique a quelle équipe de jouer.
	Uint8 m_uiNbOfPlayingTeams;			// Combien d'équipe participe a la partie.
	SDL_Renderer* m_pRenderer;			// Rendu de la fenetre du jeu. 
	CBoussole* m_pBoussole;				// Boussole de vents.
	CMap* m_pMap;						// Champ de bataille.
	CListeDC<CTeam*>* m_pListeTeam;		// Liste d'équipe qui participe au jeu.
	CListeDC<CObjets*>* m_pListeObjets; // Liste d'objets a afficher.
	bool m_boInPlay;					// Indique si la partie est terminé ou non.
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param CMap* _Map : Map a jouer.
	@param CBoussole* _Boussole : La boussole.
	@param SDL_Renderer* _Renderer: Le rendu de la fenetre.
	@return Adresse mémoire de l'objet.
	@discussion Nuff said.
	*/
	CGame(CMap* _Map, CBoussole* _Boussole, SDL_Renderer* _Renderer, SDL_Texture* _WormTexture, int _NbOfTeam, int _NbOfWormPerTeam){
		m_pListeTeam = new CListeDC<CTeam*>();
		string temp("Team");
		char buf[10];
		for (int i = 0; i < _NbOfTeam; i++){
			temp.append(SDL_itoa(i, buf, 10));
			m_pListeTeam->AjouterFin(new CTeam(temp, {i * 200, i * 100, i * 50, 1}, _WormTexture, _NbOfWormPerTeam));
		}
		m_pListeObjets = new CListeDC<CObjets*>();
		m_pMap = _Map;
		m_pBoussole = _Boussole;
		m_pRenderer = _Renderer;
		m_uiNbOfPlayingTeams = 0;
		m_uiTeamTurn = 0;
		m_boInPlay = false;
	}
	
	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He dead man... he dead.
	*/
	~CGame(){
		delete m_pListeTeam;
		delete m_pMap;
		delete m_pBoussole;
		delete m_pListeObjets;
	}

	/*!
	@method NextTurn
	@brief Change le focus des équipes pour le changement de tour.
	*/
	void NextTurn(){
		Uint8 uitemp = m_uiTeamTurn % m_uiNbOfPlayingTeams;
		m_pListeTeam->AllerA(uitemp);
		if (m_pListeTeam->ObtenirElement()->IsFocused()) { 
			m_pListeTeam->ObtenirElement()->setFocus(false);
		}
		m_pListeTeam->AllerA((uitemp + 1) % m_uiNbOfPlayingTeams);
		m_pListeTeam->ObtenirElement()->setFocus(true);
	}

	/*!
	@method Render
	@brief Affiche le jeu sur la fenetre.
	*/
	void Render(){
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

	//Papoi,papoi
	void AjouterTeam(CTeam* _team){
		m_pListeTeam->AjouterFin(_team);
	}
	
	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	void setNbOfPlayingTeams(Uint8 _NbOfTeams){ m_uiNbOfPlayingTeams = _NbOfTeams; }

	Uint8 getNbOfPlayingTeams(){ return m_uiNbOfPlayingTeams; }

};