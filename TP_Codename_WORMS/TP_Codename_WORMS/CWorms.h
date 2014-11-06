/*!
 * Fichier pour la classe CWorms
 * Créé le 06/11/2014 à 13h50 par Richer Archambault
 */

#include "CTimer.h"
#include "CListeDC.h"
#include "CGestionnaireRessources.h"
#include "CWindow.h"
#include "CGUIE.h"
#include "CLabel.h"
#include "ClabelImage.h"
#include "CButton.h"
#include "CTextBox.h"
#include "CMenu.h"

class CWorms {
private:
	CWindow* m_pWindow;
	CMenu* m_MenuPrincipal;
	CMenu* m_MenuNewGame;
	CMenu* m_MenuPause;
	CMenu* m_MenuNewTeam;
	SDL_Event* m_pEvent;
	bool m_boRun, m_boInMenu;
	CGestionnaireRessources* m_Gestionaire;
public:
	
	CWorms(){
		m_pWindow = new CWindow("Worms", WIDTH, HEIGHT);
		m_MenuPrincipal = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
		m_MenuNewGame = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
		m_MenuPause = new CMenu(m_pWindow->getRenderer(), {0, 0, (WIDTH / 2), (HEIGHT / 2)});
		m_MenuNewTeam = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
		m_boRun = true;
		m_boInMenu = true;
		m_pEvent = new SDL_Event();
		m_Gestionaire = new CGestionnaireRessources();
	}
	
	~CWorms(){
		delete m_pWindow;
		delete m_MenuPrincipal;
		delete m_MenuNewGame;
		delete m_MenuPause;
		delete m_MenuNewTeam;
		delete m_pEvent;
	}
	
	void Start(){
		while (m_boRun) {
			Render();
			while (SDL_PollEvent(m_pEvent)) {
				if (m_boInMenu){
					if (m_MenuPrincipal->IsActive())
						m_MenuPrincipal->HandleEvent(*m_pEvent);
					else if (m_MenuNewGame->IsActive())
						m_MenuNewGame->HandleEvent(*m_pEvent);
					else if (m_MenuNewTeam->IsActive())
						m_MenuNewTeam->HandleEvent(*m_pEvent);
					else if (m_MenuPause->IsActive())
						m_MenuPause->HandleEvent(*m_pEvent);
				}
				
				// Event In-Game.
					switch (m_pEvent->type) {
						default:
							break;
					}
			}
		}
	}
	
	void Render(){
		SDL_RenderClear(m_pWindow->getRenderer());
		if (m_boInMenu){
			if (m_MenuPrincipal->IsActive())
				m_MenuPrincipal->Render();
			else if (m_MenuNewGame->IsActive())
				m_MenuNewGame->Render();
			else if (m_MenuNewTeam->IsActive())
				m_MenuNewTeam->Render();
			else if (m_MenuPause->IsActive())
				m_MenuPause->Render();
		}
		else{		//Affichage in-game.
			
		}
		m_pWindow->Refresh();
	}
	
	void LoadResources(){
		m_Gestionaire->AjouterFont(new CFont("FontMenu", "/Users/richer/worms/Ressources/Arpegius.ttf", 30));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnFleche", IMG_LoadTexture(m_pWindow->getRenderer(), "/Users/richer/worms/Ressources/Btn2.png"), 2, 4, 10, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnNG", IMG_LoadTexture(m_pWindow->getRenderer(), "/Users/richer/worms/Ressources/Btn1.png"), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnQ", IMG_LoadTexture(m_pWindow->getRenderer(), "/Users/richer/worms/Ressources/Btn1.png"), 2, 1, 0, 0));
	}
	
	void Init(){
		LoadResources();
			// Initialisation du menu Principal
		m_MenuPrincipal->AddElement(new CButton("btnNewGame", "New Game", m_Gestionaire->GetFont("FontMenu"), {0,0,10,10}, m_Gestionaire->GetSprite("SpriteBtnNG")), 800, 200, 162, 33);
		m_MenuPrincipal->AddElement(new CButton("btnQuit", "Quit", m_Gestionaire->GetFont("FontMenu"), {0,0,10,10}, m_Gestionaire->GetSprite("SpriteBtnQ")), 800, 500, 162, 33);
		m_MenuPrincipal->AddElement(new CLabel("lblWorms", "Worms", m_Gestionaire->GetFont("FontMenu"), {0, 0, 10, 10}), (WIDTH/2 - 200), (HEIGHT/2 - 200), 400, 200);
		m_MenuPrincipal->ActivateMenu();
	}
};
