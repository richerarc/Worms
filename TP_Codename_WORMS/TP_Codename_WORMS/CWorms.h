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
	
	void LoadResources(string _argv){
		string strPath(_argv); //Donnée membre représentant le chemin du fichier.
		unsigned int uiPosString = (strPath.length() - 1); // Donnée membre représentant une position dans la string.
#if defined(__APPLE__) && defined(__MACH__)
		while (strPath[uiPosString] != '/'){
			strPath.erase(uiPosString, 1);
			uiPosString--;
		}
#elif defined (_win32)
		while (strPath[uiPosString] != '\\'){
			strPath.erase(uiPosString, 1);
			uiPosString--;
		}
#endif
		strPath.append("Ressources");
#if defined(__APPLE__) && defined(__MACH__)
		strPath.append("/");
#elif defined (_win32)
		strPath.append("\\");
#endif
		string FileName[3] = {"Arpegius.ttf", "Btn1.png", "Btn2.png"};
		string strFilePath[3];
		for (int i = 0; i < 3; i++){
			strFilePath[i] = strPath;
			strFilePath[i].append(FileName[i]);
		}
		m_Gestionaire->AjouterFont(new CFont("FontMenu", strFilePath[0].c_str(), 30));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnFleche", IMG_LoadTexture(m_pWindow->getRenderer(), strFilePath[2].c_str()), 2, 4, 10, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnNG", IMG_LoadTexture(m_pWindow->getRenderer(),strFilePath[1].c_str()), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnQ", IMG_LoadTexture(m_pWindow->getRenderer(), strFilePath[1].c_str()), 2, 1, 0, 0));
	}
	
	void Init(string _argv){
		LoadResources(_argv);
			//
			// Initialisation du menu Principal
			//
		m_MenuPrincipal->AddElement(new CButton("btnNewGame", "New Game", m_Gestionaire->GetFont("FontMenu"), {0,0,10,10}, m_Gestionaire->GetSprite("SpriteBtnNG")), 800, 200, 162, 33);
		m_MenuPrincipal->AddElement(new CButton("btnQuit", "Quit", m_Gestionaire->GetFont("FontMenu"), {0,0,10,10}, m_Gestionaire->GetSprite("SpriteBtnQ")), 800, 500, 162, 33);
		m_MenuPrincipal->AddElement(new CLabel("lblWorms", "Worms", m_Gestionaire->GetFont("FontMenu"), {0, 0, 10, 10}), (WIDTH/2 - 200), (HEIGHT/2 - 200), 400, 200);
		m_MenuPrincipal->ActivateMenu();
			//
			// Initialisation du menu NewGame
			//
		
	}
	
		//
		// Définition des action de chaque bouton dans les menu.
		//
	
	
	
};
