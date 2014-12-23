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

CWorm * ActiveWorm;

static void BtnWpnJP(){
	if((ActiveWorm->getWormState() == NoMotionLeft)){
		ActiveWorm->setWormState(JetpackLeftNoFly);
	}
	else{
		ActiveWorm->setWormState(JetpackRightNoFly);
	}
}

static void BtnWpnBZK(){
	if((ActiveWorm->getWormState() == NoMotionLeft)){
		ActiveWorm->setWormState(UsingBazzLeft);
	}
	else{
		ActiveWorm->setWormState(UsingBazzRight);
	}
}

static void BtnWpnGND(){
	if((ActiveWorm->getWormState() == NoMotionLeft)){
		ActiveWorm->setWormState(GrenadeLaunchLeft);
	}
	else{
		ActiveWorm->setWormState(GrenadeLaunchRight);
	}
}

static void BtnWpnKNF(){
	if((ActiveWorm->getWormState() == NoMotionLeft)){
		ActiveWorm->setWormState(KnifeLeft);
	}
	else{
		ActiveWorm->setWormState(KnifeRight);
	}
}

class CGame{
private:
	Uint8 m_uiTeamTurn;						// Indique a quelle équipe de jouer.
	Uint8 m_uiNbOfPlayingTeams;				// Combien d'équipe participe a la partie.
	Uint8 m_uiNbOfWormPerTeam;				// Combien de Worm par équipe participent a la partie.
	unsigned int m_uiNbrOfWormsAlive;
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
	CJetPack * m_pJetpack;
	CBazouka* m_pBazouka;
	CGrenadeLauncher* m_pLauncher;
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
		m_MenuWeapons->getElement("btnWpnGNDL")->OnClickAction = BtnWpnGND;
		m_MenuWeapons->getElement("btnWpnKNF")->OnClickAction = BtnWpnKNF;
		boBegin = false;
		DropperTimer = new CTimer();
		m_uiNbOfPlayingTeams = _NbOfTeam;
		m_uiNbrOfWormsAlive = m_uiNbOfPlayingTeams * m_uiNbOfWormPerTeam;
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
		m_pJetpack = new CJetPack(ActiveWorm);
		m_pBazouka = new CBazouka(m_Gestionaire->GetTexture("bazouka")->GetTexture(), m_Gestionaire->GetTexture("missile")->GetTexture(), new CExplosion(m_Gestionaire->GetTexture("BigEx"), 60, m_pMap), ActiveWorm);
		m_pLauncher = new CGrenadeLauncher(m_Gestionaire->GetTexture("launcher")->GetTexture(), m_Gestionaire->GetTexture("grenade")->GetTexture(), new CExplosion(m_Gestionaire->GetTexture("SmallEx"), 40, m_pMap), ActiveWorm);
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
		delete m_pJetpack;
		delete m_pBazouka;
		delete m_pLauncher;
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
			ActiveWorm->setPlaystate(true);
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
		
		if (ActiveWorm != nullptr){
			switch (ActiveWorm->getWormState()) {
				case JetpackLeftFly:
				case JetpackLeftNoFly:
				case JetpackRightFly:
				case JetpackRightNoFly:
					m_pJetpack->Render(m_pRenderer);
					break;
				case UsingBazzLeft:
				case UsingBazzRight:
					m_pBazouka->Render(m_pRenderer);
					break;
				case GrenadeLaunchLeft:
				case GrenadeLaunchRight:
					m_pLauncher->Render(m_pRenderer);
					break;
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
			if (ActiveWorm != nullptr){
				switch (ActiveWorm->getWormState()) {
					case JetpackLeftFly:
					case JetpackLeftNoFly:
					case JetpackRightFly:
					case JetpackRightNoFly:
						m_pJetpack->HandleEvent(_Event);
						break;
					case UsingBazzLeft:
					case UsingBazzRight:
						m_pBazouka->HandleEvent(_Event);
						break;
					case GrenadeLaunchLeft:
					case GrenadeLaunchRight:
						m_pLauncher->HandleEvent(_Event);
						break;
					default:
						ActiveWorm->HandleEvent(_Event);
						break;
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
			m_pListeObjets->AjouterFin(new CMines({ ((rand() % (WIDTH - 10)) + 5), 5, 12, 8 }, m_Gestionaire->GetTexture("mine")->GetTexture(), new CExplosion(m_Gestionaire->GetTexture("SmallEx"), 50, m_pMap)));
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
			ActiveWorm->setPlaystate(true);
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
			int itemp = EnterrerLesMorts();
			for (int i = 0; i< itemp; i++){
				m_pListeObjets->AjouterFin(new CCaisses({ ((rand() % (WIDTH - 10)) + 5), 5, 20, 18 }, m_Gestionaire->GetTexture("caisse")->GetTexture(), new CExplosion(m_Gestionaire->GetTexture("BigEx"), 55, m_pMap)));
			}
			if ((ActiveWorm->getWormState() == Dead) || (ActiveWorm->isOutOfBounds())){
				NextTurn();
			}
			
			if (ActiveWorm->isDamaged()){
				NextTurn();
			}
			
			else{
				switch (ActiveWorm->getWormState()) {
					case UsingBazzLeft:
					case UsingBazzRight:
						if (m_pBazouka->isInUse() && m_pBazouka->MissileHasExploded()){
							if (ActiveWorm->getWormState() == UsingBazzRight){
								ActiveWorm->setWormState(NoMotionRight);
							}
							else{
								ActiveWorm->setWormState(NoMotionLeft);
							}
							NextTurn();
							VerifyGlobalExplosion();
							m_pBazouka->setInUse(false);
							m_pBazouka->reset();
						}
						else{
							m_pBazouka->setBazooka(ActiveWorm);
							m_pBazouka->setInUse(true);
						}
						break;
					case JetpackLeftNoFly:
					case JetpackRightNoFly:
						if (m_pJetpack->isInUse() && m_pJetpack->isLanded()){
							if (ActiveWorm->getWormState() == JetpackRightNoFly){
								ActiveWorm->setWormState(NoMotionRight);
							}
							else{
								ActiveWorm->setWormState(NoMotionLeft);
							}
							m_pJetpack->setInUse(false);
							m_pJetpack->reset();
						}
						else{
							m_pJetpack->setJetPack(ActiveWorm);
							m_pJetpack->setInUse(true);
						}
						break;
					case GrenadeLaunchLeft:
					case GrenadeLaunchRight:
						if (m_pLauncher->isInUse() && m_pLauncher->GrenadeHasExploded()){
							if (ActiveWorm->getWormState() == GrenadeLaunchRight){
								ActiveWorm->setWormState(NoMotionRight);
							}
							else{
								ActiveWorm->setWormState(NoMotionLeft);
							}
							VerifyGlobalExplosion();
							NextTurn();
							m_pLauncher->setInUse(false);
							m_pLauncher->reset();
						}
						else{
							m_pLauncher->setGrenadeLauncher(ActiveWorm);
							m_pLauncher->setInUse(true);
						}
						break;
					case KnifeLeft:
					case KnifeRight:
						if (ActiveWorm->KnifeDone()){
							CTeam* TeamTemp;
							m_pListeTeam->AllerDebut();
							for (int i = 0; i < m_pListeTeam->Count(); i++) {
								TeamTemp = m_pListeTeam->ObtenirElement();
								for (int j = 0; j < TeamTemp->getListeWorm()->Count(); j++){
									TeamTemp->getListeWorm()->AllerA(j);
									if (!TeamTemp->getListeWorm()->ObtenirElement()->isPlaying()){
										if (CPhysics::VerifyCollision(ActiveWorm->getPosition(), TeamTemp->getListeWorm()->ObtenirElement()->getPosition())){
											TeamTemp->getListeWorm()->ObtenirElement()->RecieveDamage(nullptr, true);
										}
									}
								}
								m_pListeTeam->AllerSuivant();
							}
							if (ActiveWorm->getWormState() == KnifeLeft)
								ActiveWorm->setWormState(NoMotionLeft);
							else
								ActiveWorm->setWormState(NoMotionRight);
							NextTurn();
						}
						break;
						
				}
			}
			if (CEntity::m_uiTotalNbrOfEntityExplosed != CEntity::m_uiCurrentNbrOfEntityExplosed){
				VerifyGlobalExplosion();
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

	int EnterrerLesMorts(){
		int itemp = 0;
		m_pListeTeam->AllerDebut();
		for (int i = 0; i < m_uiNbOfPlayingTeams; i++){
			itemp += m_pListeTeam->ObtenirElement()->EnterrerLesMorts();
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
			m_pListeTeam->AllerSuivant();
		}
		return itemp;
	}

	/*!
	@method Verify global Explosion
	@brief Vérifier s'il y a des explosions en chaîne
	@param Une pointeur de bazouka
	@return Aucun.
	@discussion None.
	*/
	void VerifyGlobalExplosion(){
		if ((m_pBazouka != nullptr) && (m_pBazouka->isInUse())){
			if (m_pBazouka->MissileHasExploded()){
				for (int j = 0; j < m_pListeObjets->Count(); j++){
					m_pListeObjets->AllerA(j);
					m_pListeObjets->ObtenirElement()->ReactToExplosion(m_pBazouka->MissilePos().x, m_pBazouka->MissilePos().y, m_pBazouka->MissileRayon());
					if (m_pListeObjets->ObtenirElement()->IsExploded()){
						CEntity::m_uiCurrentNbrOfEntityExplosed++;
					}
				}
				for (int i = 0; i < m_pListeTeam->Count(); i++) {
					m_pListeTeam->AllerA(i);
					m_pListeTeam->ObtenirElement()->ReactToExplosion(m_pBazouka->getExplosion());
				}
				CEntity::m_uiTotalNbrOfEntityExplosed++;
			}
		}
		if ((m_pLauncher != nullptr) && (m_pLauncher->isInUse())){
			if (m_pLauncher->GrenadeHasExploded()){
				for (int j = 0; j < m_pListeObjets->Count(); j++){
					m_pListeObjets->AllerA(j);
					m_pListeObjets->ObtenirElement()->ReactToExplosion(m_pLauncher->GrenadePos().x, m_pLauncher->GrenadePos().y, m_pLauncher->GrenadeRayon());
					if (m_pListeObjets->ObtenirElement()->IsExploded()){
						CEntity::m_uiCurrentNbrOfEntityExplosed++;
					}
				}
				for (int i = 0; i < m_pListeTeam->Count(); i++) {
					m_pListeTeam->AllerA(i);
					m_pListeTeam->ObtenirElement()->ReactToExplosion(m_pLauncher->getExplosion());
				}
				CEntity::m_uiTotalNbrOfEntityExplosed++;
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
						if (m_pListeObjets->ObtenirElement()->IsExploded()){
							CEntity::m_uiCurrentNbrOfEntityExplosed++;
						}
					}
					for (int i = 0; i < m_pListeTeam->Count(); i++) {
						m_pListeTeam->AllerA(i);
						m_pListeTeam->ObtenirElement()->ReactToExplosion(pTemp->getExplosion());
					}
					CEntity::m_uiTotalNbrOfEntityExplosed++;
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