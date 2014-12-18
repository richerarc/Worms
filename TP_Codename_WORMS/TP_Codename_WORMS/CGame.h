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

enum Tools{ Knife = 42, JetPack = 51, Bazooka = 69, Grenade = 666 };

unsigned int uiCurrentTool(0);

static void BtnWpnJP(){
	uiCurrentTool = JetPack;
}

static void BtnWpnBZK(){
	uiCurrentTool = Bazooka;
}

static void BtnWpnGND(){
	uiCurrentTool = Grenade;
}

static void BtnWpnKNF(){
	uiCurrentTool = Knife;
}

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
	CMenu* m_MenuWeapons;
	CWorm * ActiveWorm;
	CJetPack * Jetpack;
	CBazouka* Bazouka;
	bool boBegin;

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
	CGame(CMap* _Map, CBoussole* _Boussole, SDL_Renderer* _Renderer, int _NbOfTeam, int _NbOfWormPerTeam, CGestionnaireRessources* _Gestionaire, CMenu* _MenuWeapons){
		TurnTimer = new CTimer();
		m_MenuWeapons = _MenuWeapons;
		m_MenuWeapons->getElement("btnWpnJP")->OnClickAction = BtnWpnJP;
		m_MenuWeapons->getElement("btnWpnBZK")->OnClickAction = BtnWpnBZK;
		m_MenuWeapons->getElement("btnWpnGND")->OnClickAction = BtnWpnGND;
		m_MenuWeapons->getElement("btnWpnKNF")->OnClickAction = BtnWpnKNF;
		boBegin = false;
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
		Jetpack = new CJetPack(ActiveWorm);
		Bazouka = new CBazouka(m_Gestionaire->GetTexture("bazouka")->GetTexture(), m_Gestionaire->GetTexture("missile")->GetTexture(), new CExplosion(m_Gestionaire->GetTexture("BigEx"), 40, m_pMap), ActiveWorm);
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
		delete Jetpack;
		delete Bazouka;
	}

	/*!
	@method NextTurn
	@brief Change le focus des équipes pour le changement de tour.
	*/
	void NextTurn(){
		if (m_boInPlay){
			unsigned int uitemp = m_uiTeamTurn % m_uiNbOfPlayingTeams;
			m_pListeTeam->AllerA(uitemp);
			if (m_pListeTeam->ObtenirElement()->IsFocused()) {
				m_pListeTeam->ObtenirElement()->NextTurn();
				m_pListeTeam->ObtenirElement()->setFocus(false);
			}
			m_pListeTeam->AllerA((uitemp + 1) % m_uiNbOfPlayingTeams);
			m_pListeTeam->ObtenirElement()->setFocus(true);
			m_uiTeamTurn++;
			if ((ActiveWorm != nullptr) && (ActiveWorm->getWormState() == Dead) && (ActiveWorm->getLife() == 0)){
				delete ActiveWorm;
				ActiveWorm = nullptr;
			}
			ActiveWorm = m_pListeTeam->ObtenirElement()->getPlayingWorm();
		}
		CPhysics::RedefineWind();
	}

	/*!
	@method Render
	@brief Affiche le jeu sur la fenetre.
	*/
	void Render(){
		m_pMap->Draw(m_pRenderer);
		double Wind = RadToDeg(CPhysics::GetWind()->getSDLOrientation());
		m_pBoussole->setAngle(Wind);
		m_pBoussole->setWindSpeed(CPhysics::GetWind()->getNorme() * 1000);
		m_pBoussole->Draw(m_pRenderer);
		CObjets* ObjetTemp;
		m_pListeObjets->AllerDebut();
		for (int i = 0; i < m_pListeObjets->Count(); i++){
			ObjetTemp = m_pListeObjets->ObtenirElement();
			if (ObjetTemp->isOutOfBounds()){
				m_pListeObjets->Retirer(true);
			}
			else{
				if (ObjetTemp->HasExploded()){
					m_pListeObjets->Retirer(true);
				}
				else{
					if (!ObjetTemp->IsExploded()){
						ObjetTemp->Move();
					}
					ObjetTemp->Draw(m_pRenderer);
					m_pListeObjets->AllerSuivant();
				}
			}
		}
		if ((m_pListeTeam != nullptr) && (m_pListeTeam->Count())){
			m_pListeTeam->AllerDebut();

			for (int i = 0; i < m_uiNbOfPlayingTeams; i++){
				m_pListeTeam->ObtenirElement()->draw(m_pRenderer);
				m_pListeTeam->AllerSuivant();
			}
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
			case SDL_MOUSEBUTTONUP:
				if (_Event.button.button == SDL_BUTTON_LEFT){
					if (m_MenuWeapons->IsActive()){
						m_MenuWeapons->DeActivateMenu();
					}
				}
				break;
			case SDL_KEYDOWN:
				switch (_Event.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					PauseGame();
					break;
				case SDL_SCANCODE_T:
					NextTurn();
					break;
				}
				break;
			case SDL_KEYUP:
				break;
			}
			if (m_pListeTeam != nullptr){
				m_pListeTeam->AllerDebut();
				for (int i(0); i < m_pListeTeam->Count(); i++){
					if (m_pListeTeam->ObtenirElement()->IsFocused()){
						m_pListeTeam->ObtenirElement()->HandleEvent(_Event);
						break;
					}
					else
						m_pListeTeam->AllerSuivant();
				}
			}
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
			m_pListeObjets->AjouterFin(new CGrenades({ ((rand() % (WIDTH - 10)) + 5), 5, 17, 25 }, m_Gestionaire->GetTexture("grenade")->GetTexture(), new CExplosion(m_Gestionaire->GetTexture("SmallEx"), 25, m_pMap)));
			//m_pListeObjets->AjouterDebut(new CCaisses({((rand() % (WIDTH - 10)) + 5), 30, 30 }, m_Gestionaire->GetTexture("caisse")->GetTexture(), new CExplosion(m_Gestionaire->GetTexture("SmallEx"), 45, m_pMap)));
			//m_pListeObjets->AjouterFin(new CMines({ ((rand() % (WIDTH - 10)) + 5), 5, 12, 8 }, m_Gestionaire->GetTexture("mine")->GetTexture(), m_pSmall_Explosion));
		}

		if (m_pListeObjets->Count() == m_pMap->getMine()){
			if (m_pListeTeam->Count() < m_uiNbOfPlayingTeams){
				string temp("Team");
				char buf[10];
				temp.append(SDL_itoa(m_pListeObjets->Count() + 1, buf, 10));
				m_pListeTeam->AjouterFin(new CTeam(temp, nullptr, m_Gestionaire->GetTexture("wormSprite")->GetTexture(), m_uiNbOfWormPerTeam, m_Gestionaire->GetFont("FontWorm"), m_Gestionaire->GetTexture("SmallEx"), m_pMap));
				temp.pop_back();
			}
		}

		if (m_pListeTeam->Count() == m_uiNbOfPlayingTeams){
			m_pListeTeam->AllerDebut();
			m_pListeTeam->ObtenirElement()->setFocus(true);
			ActiveWorm = m_pListeTeam->ObtenirElement()->getPlayingWorm();
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
		
		if (boBegin){	// Si le jeu ˆ commencŽ
			EnterrerLesMorts();
			if ((ActiveWorm->getWormState() == Dead) || (ActiveWorm->isOutOfBounds())){
				NextTurn();
			}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else{	// sinon si il reste des truc ˆ spawn
			if (DropperTimer->IsElapsed() && (m_pListeTeam->Count() < m_uiNbOfPlayingTeams)){
				DropperTimer->Start();
				Spawn();
			}
			else if (m_pListeTeam->Count() == m_uiNbOfPlayingTeams){
				boBegin = true;
			}
		}
	}

	void EnterrerLesMorts(){
		m_pListeTeam->AllerDebut();
		for (int i = 0; i < m_uiNbOfPlayingTeams; i++){
			if (m_pListeTeam->ObtenirElement()->isDefeated()){
				m_pListeTeam->Retirer(true);
				m_uiNbOfPlayingTeams--;
				if (m_uiNbOfPlayingTeams <= 1){
					m_boInPlay = false;
				}
				else{
					m_pListeTeam->AllerPrecedent();
					m_pListeTeam->ObtenirElement()->setFocus(true);
				}
			}
		}
	}

	/*!
	@method Verify global Explosion
	@brief Vérifier s'il y a des explosions en chaîne
	@param Une pointeur de bazouka
	@return Aucun.
	@discussion None.
	*/
	void VerifyGlobalExplosion(CBazouka* pBazouka){
		if (pBazouka != nullptr){
			if (pBazouka->MissileHasExploded()){
				for (int j = 0; j < m_pListeObjets->Count(); j++){
					m_pListeObjets->AllerA(j);
					m_pListeObjets->ObtenirElement()->ReactToExplosion(pBazouka->MissilePos().x, pBazouka->MissilePos().y, pBazouka->MissileRayon());
				}
			}
		}
		else{
			CObjets* pTemp;
			for (int i = 0; i < m_pListeObjets->Count(); i++){
				m_pListeObjets->AllerA(i);
				if (m_pListeObjets->ObtenirElement()->IsExploded()){
					pTemp = m_pListeObjets->ObtenirElement();
					for (int j = 0; j < m_pListeObjets->Count(); j++){
						m_pListeObjets->AllerA(j);
						m_pListeObjets->ObtenirElement()->ReactToExplosion(pTemp->getPosition().x, pTemp->getPosition().y, pTemp->getRayon());
					}
				}
			}
		}
	}
	/*!
	@method Verify Caisse contact
	@brief Vérifier s'il y a un worm en contact avec une caisse
	@param Une pointeur de caisse
	@return Aucun.
	@discussion None.
	*/
	void VerifyCaisseContact(CCaisses* pCaisses){
		if (pCaisses != nullptr)
			pCaisses->VerifyWormsCollision(ActiveWorm);
	}

	/*!
	@method Acesseurs
	@brief Servent à acceder/modifier aux données membres.
	*/

	CWorm* getActiveWorm(){ return ActiveWorm; }
	Uint8 getNbOfPlayingTeams(){ return m_uiNbOfPlayingTeams; }
	bool inGame(){ return m_boInPlay; }

	void Activate(){ m_boInPlay = true; }
	void DeActivate(){ m_boInPlay = false; }
	void PauseGame(){ m_boPause = true; }
	void ResumeGame(){ m_boPause = false; }
	void setNbOfPlayingTeams(Uint8 _NbOfTeams){ m_uiNbOfPlayingTeams = _NbOfTeams; }




};