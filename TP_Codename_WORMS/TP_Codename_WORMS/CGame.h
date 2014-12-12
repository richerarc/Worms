//
//  CGame.h
//
//  Created by Kevin Pantelakis on 2014-11-11.
//
//

/*!
@class CGame.h
@discussion Classe qui représente une partie.
*/
class CGame{
private:
	Uint8 m_uiTeamTurn;						// Indique a quelle équipe de jouer.
	Uint8 m_uiNbOfPlayingTeams;				// Combien d'équipe participe a la partie.
	Uint8 m_uiNbOfWormPerTeam;				// Combien de Worm par équipe participent a la partie.
	SDL_Renderer* m_pRenderer;				// Rendu de la fenetre du jeu. 
	CBoussole* m_pBoussole;					// Boussole de vents.
	CMap* m_pMap;							// Champ de bataille.
	CListeDC<CTeam*>* m_pListeTeam;			// Liste d'équipe qui participe au jeu.
	CListeDC<CObjets*>* m_pListeObjets;		// Liste d'objets a afficher.
	bool m_boInPlay;						// Indique si la partie est terminé ou non.
	CGestionnaireRessources* m_Gestionaire;	// Gestionnaire de ressources.
	bool m_boPause;							// Indique si le jeu est en pause.
	CTimer* TurnTimer;						// Indique le temps d'un tour.
	CTimer* DropperTimer;					// Indique le Temps avant de faire tomber les worms.
	CWorm * ActiveWorm;
	CJetPack * Jetpack;
	CExplosion* m_explode;
	bool boEx;
	
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _Map : Le champ de battaile à jouer.
	@param _Boussole : La boussole.
	@param _Renderer: Le rendu de la fenetre.
	@param _NbOfTeam : Combien d'équipe pour un partie. 
	@param _NbOfWormPerTeam : Combien de Worm par équipe
	@param  _Gestionaire : Gestionnaire de ressource
	@return Adresse mémoire de l'objet.
	@discussion Nuff said.
	*/
	CGame(CMap* _Map, CBoussole* _Boussole, SDL_Renderer* _Renderer, int _NbOfTeam, int _NbOfWormPerTeam, CGestionnaireRessources* _Gestionaire){
		TurnTimer = new CTimer();
		DropperTimer = new CTimer();
		m_uiNbOfPlayingTeams = _NbOfTeam;
		m_uiNbOfWormPerTeam = _NbOfWormPerTeam;
		m_Gestionaire = _Gestionaire;
		m_pBoussole = _Boussole;
		m_pRenderer = _Renderer;
		m_uiTeamTurn = 0;
		m_boInPlay = false;
		m_boPause = false;
		m_pMap = _Map;
		CPhysics::Init(m_pMap->getMap(), m_pMap->getGravity(), m_pMap->getWind());
		m_pListeTeam = new CListeDC<CTeam*>();
		m_pListeObjets = new CListeDC<CObjets*>();
		Spawn();
		DropperTimer->SetTimer(200);
		DropperTimer->Start();
		ActiveWorm = nullptr;
		Jetpack = nullptr;
		m_Gestionaire->AjouterSprite(new CSprite("explosion1", m_Gestionaire->GetTexture("explosion1")->GetTexture(), 15, 1, 100, 1));
		m_explode = new CExplosion(m_Gestionaire->GetSprite("explosion1"),0);
		boEx = false;
	}
	
	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He dead man... he dead.
	*/
	~CGame(){
		delete m_pListeTeam;
		delete m_pListeObjets;
		delete m_pBoussole;
		CPhysics::Annihilate();
		delete DropperTimer;
		delete TurnTimer;
		delete m_explode;
		delete Jetpack;
	}

	/*!
	@method NextTurn
	@brief Change le focus des équipes pour le changement de tour.
	*/
	void NextTurn(){
		Uint8 uitemp = m_uiTeamTurn % m_uiNbOfPlayingTeams;
		m_pListeTeam->AllerA(uitemp);
		if (m_pListeTeam->ObtenirElement()->IsFocused()) {
			m_pListeTeam->ObtenirElement()->NextTurn();
			m_pListeTeam->ObtenirElement()->setFocus(false);
		}
		for (int i = 0; i < m_uiNbOfPlayingTeams; i++){
			m_pListeTeam->AllerA(i);
			if (m_pListeTeam->ObtenirElement()->IsFocused()){
				for (int k = 0; k < m_uiNbOfWormPerTeam; k++){
					ActiveWorm = m_pListeTeam->ObtenirElement()->getPlayingWorm();
					break;
				}
				break;
			}
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
		double Wind = RadToDeg(CPhysics::GetWind()->getSDLOrientation());
		m_pBoussole->setAngle(Wind);
		m_pBoussole->Draw(m_pRenderer);
		
		m_pListeObjets->AllerDebut();
		for (int i = 0; i < m_pListeObjets->Count(); i++){
			m_pListeObjets->ObtenirElement()->Move();
			m_pListeObjets->ObtenirElement()->Draw(m_pRenderer);
			m_pListeObjets->AllerSuivant();
		}
		if ((m_pListeTeam != nullptr) && (m_pListeTeam->Count())){
			m_pListeTeam->AllerDebut();
			
			for (int i = 0; i < m_uiNbOfPlayingTeams; i++){
				m_pListeTeam->ObtenirElement()->draw(m_pRenderer);
				m_pListeTeam->AllerSuivant();
			}
		}	
		if (m_explode->IsDone()){ boEx = false; }
		if (boEx && !m_explode->IsDone()){
			m_explode->startExplosion();
			m_explode->Draw(m_pRenderer,m_pMap->getMap());
		}
	
	}
	
	/*!
	@method HandleEvent
	@brief Gère les events SDL
	@param _Event: Event SDL.
	@return Aucun
	@discussion None.
	*/
	void HandleEvent(SDL_Event _Event){
		if (!m_boPause){

			switch (_Event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				if (_Event.button.button == SDL_BUTTON_LEFT){
					m_explode->setPositionXY(_Event.button.x, _Event.button.y);
					boEx = true;
				}
				break;


			case SDL_KEYDOWN:
				switch (_Event.key.keysym.sym) 
				{
				case SDLK_ESCAPE:
						PauseGame();
					break;
				}
				break;
			case SDL_KEYUP:
				break;
			}


			switch (_Event.key.keysym.sym) {
				case SDLK_ESCAPE:
					PauseGame();
					break;
			}
			if (m_pListeTeam != nullptr){
				m_pListeTeam->AllerDebut();
				for (int i(0); i < m_pListeTeam->Count(); i++){
					if(m_pListeTeam->ObtenirElement()->IsFocused()){
						m_pListeTeam->ObtenirElement()->HandleEvent(_Event);
						break;
					}
					else
						m_pListeTeam->AllerSuivant();
				}
			}
			if (_Event.key.keysym.sym == SDLK_1 && ActiveWorm != nullptr){
				Jetpack = new CJetPack(ActiveWorm);
			}
			if (Jetpack != nullptr)
				Jetpack->HandleEvent(_Event);

		}
	}

	/*!
	@method Create Team
	@brief Crée les équipes qui vont combattre
	@param Aucun.
	@return Aucun.
	@discussion None.
	*/
	void Spawn(){
		if (m_pListeObjets->Count() < m_pMap->getMine()){
			m_pListeObjets->AjouterFin(new CMines({ ((rand() % (WIDTH - 10)) + 5), 5, 12, 8 }, m_Gestionaire->GetTexture("mine")->GetTexture(), m_Gestionaire->GetTexture("explosion1")->GetTexture()));
		}
		if (m_pListeObjets->Count() == m_pMap->getMine()){
			string temp("Team");
			char buf[10];
			temp.append(SDL_itoa(m_pListeObjets->Count()+1, buf, 10));
			m_pListeTeam->AjouterFin(new CTeam(temp, nullptr, m_Gestionaire->GetTexture("wormSprite")->GetTexture(), m_uiNbOfWormPerTeam, m_Gestionaire->GetFont("FontWorm"), m_Gestionaire->GetTexture("explosion1")->GetTexture()));
			temp.pop_back();
		}
		if (m_pListeTeam->Count() == m_uiNbOfPlayingTeams){
			m_pListeTeam->AllerDebut();
			m_pListeTeam->ObtenirElement()->setFocus(true);
			if (m_pListeTeam->ObtenirElement()->IsFocused())
				for (int k = 0; k < m_uiNbOfWormPerTeam; k++){
					ActiveWorm = m_pListeTeam->ObtenirElement()->getPlayingWorm();
				}
			/*for (int i = 0; i < m_uiNbOfPlayingTeams; i++){
				m_pListeTeam->AllerA(i);
				
					break;
				}
			}*/
		}
	}

	/*!
	@method MainGame
	@brief Fonction des appels qui ne sont pas du titre du render, du tigger d'event et tout et tout.
	@param Aucun.
	@return Aucun.
	@discussion None.
	*/
	void MainGame(){
		if (DropperTimer->IsElapsed()){
			DropperTimer->Start();
			Spawn();
		}
	}

	/*!
	@method Acesseurs
	@brief Servent à acceder/modifier aux données membres.
	*/

	void setNbOfPlayingTeams(Uint8 _NbOfTeams){ m_uiNbOfPlayingTeams = _NbOfTeams; }

	Uint8 getNbOfPlayingTeams(){ return m_uiNbOfPlayingTeams; }
	
	bool inGame(){return m_boInPlay;}
	void Activate(){m_boInPlay = true;}
	void DeActivate(){m_boInPlay = false;}
	void PauseGame(){ m_boPause = true;}
	void ResumeGame(){ m_boPause = false;}


	/*
	Methode getActiveWorm
	*/

	CWorm* getActiveWorm(){
		return ActiveWorm;
	}
};