/*!
 * Fichier pour la classe CWorms
 * Créé le 06/11/2014 à 13h50 par Richer Archambault
 */

#include <iostream>
#include <fstream>

#include "CTimer.h"
#include "CListeDC.h"
#include "CGestionnaireRessources.h"
#include "CWindow.h"
#include "CGUIE.h"
#include "CLabel.h"
#include "ClabelImage.h"
#include "CButton.h"
#include "CTextBox.h"
#include "CSlideShow.h"
#include "CMenu.h"
#include "CEntity.h"
#include "CObjets.h"
#include "CMines.h"
#include "CMissiles.h"
#include "CGrenades.h"
#include "CCaisses.h"
#include "CCaisseSoin.h"
#include "CExplosion.h"
#include "CWorm.h"
#include "CTeam.h"
#include "CMap.h"
#include "CBoussole.h"
#include "CGame.h"



/*!
 @class CWorms
 @discussion Classe principale du projet, dans lequel se fait la gestion de l'affichage et des SDLEvent.
 */
class CWorms {
private:
	static CWindow* m_pWindow;						// Fenêtre principale de l'application.
	static CMenu* m_MenuPrincipal;					// Menu principal du jeu
	static CMenu* m_MenuNewGame;					// Menu Nouvelle partie
	static CMenu* m_MenuPause;						// Menu Pause
	static CMenu* m_MenuNewTeam;					// Menu Création d'une nouvelle équipe.
	static SDL_Event* m_pEvent;						// Event SDL
	static bool m_boRun;							// Indique si le jeu est en terminé ou non.
	static bool m_boInMenu;							// Indique si on se trouve dans un menu.
	static CGestionnaireRessources* m_Gestionaire;	// Gestionnaire de Resource pour le Worms
	static CTeam* TabTeam[4];
	static CMap* TabMap[4];
	static fstream* m_SaveFile;
public:
	
	static void Start(){
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
	
	static void Render(){
		SDL_RenderClear(m_pWindow->getRenderer());
		if (m_boInMenu){
			SDL_SetRenderDrawColor(m_pWindow->getRenderer(), 255, 255, 255, 1);
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
	
	static void LoadResources(string _argv){
		string strPath(_argv); //Donnée membre représentant le chemin du fichier.
		unsigned int uiPosString = (strPath.length() - 1); // Donnée membre représentant une position dans la string.
#if defined(__APPLE__) && defined(__MACH__)
		while (strPath[uiPosString] != '/'){
			strPath.erase(uiPosString, 1);
			uiPosString--;
		}
#elif defined (_WIN32)
		while (strPath[uiPosString] != '\\'){
			strPath.erase(uiPosString, 1);
			uiPosString--;
		}
#endif
		strPath.append("Ressources");
#if defined(__APPLE__) && defined(__MACH__)
		strPath.append("/");
#elif defined (_WIN32)
		strPath.append("\\");
#endif
		string FileName[13] = {"Arpegius.ttf", "Btn1.png", "BtnL.png", "BtnR.png", "map1.png", "background1.png", "map2.png", "background2.png", "map3.png", "background3.png", "map4.png", "background4.png", "SavedData.dat"};
		string strFilePath[13];
		for (int i = 0; i < 13; i++){
			strFilePath[i] = strPath;
			strFilePath[i].append(FileName[i]);
		}
		m_Gestionaire->AjouterFont(new CFont("FontMenu", strFilePath[0].c_str(), 30));
		m_Gestionaire->AjouterTexture(new CTexture("TextureBtn", IMG_LoadTexture(m_pWindow->getRenderer(),strFilePath[1].c_str())));
		m_Gestionaire->AjouterTexture(new CTexture("TextureBtnL", IMG_LoadTexture(m_pWindow->getRenderer(),strFilePath[2].c_str())));
		m_Gestionaire->AjouterTexture(new CTexture("TextureBtnR", IMG_LoadTexture(m_pWindow->getRenderer(),strFilePath[3].c_str())));
			/* Sprite pour le menu principal */
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnNG", m_Gestionaire->GetTexture("TextureBtn")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnQ", m_Gestionaire->GetTexture("TextureBtn")->GetTexture(), 2, 1, 0, 0));
			/* Sprite pour le menu New Game */
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnCancelNG", m_Gestionaire->GetTexture("TextureBtn")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnCancelNT", m_Gestionaire->GetTexture("TextureBtn")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnCancelP", m_Gestionaire->GetTexture("TextureBtn")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnPlay", m_Gestionaire->GetTexture("TextureBtn")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnNT", m_Gestionaire->GetTexture("TextureBtn")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteMapLeft", m_Gestionaire->GetTexture("TextureBtnL")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteMapRight", m_Gestionaire->GetTexture("TextureBtnR")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteTeamLeft", m_Gestionaire->GetTexture("TextureBtnL")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteTeamRight", m_Gestionaire->GetTexture("TextureBtnR")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnP1", m_Gestionaire->GetTexture("TextureBtn")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnP2", m_Gestionaire->GetTexture("TextureBtn")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnP3", m_Gestionaire->GetTexture("TextureBtn")->GetTexture(), 2, 1, 0, 0));
		m_Gestionaire->AjouterSprite(new CSprite("SpriteBtnP4", m_Gestionaire->GetTexture("TextureBtn")->GetTexture(), 2, 1, 0, 0));
			/* Map et leur background */
		m_Gestionaire->AjouterSurface(new CSurface("map1", IMG_Load(strFilePath[4].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("background1", IMG_Load(strFilePath[5].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("map2", IMG_Load(strFilePath[6].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("background2", IMG_Load(strFilePath[7].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("map3", IMG_Load(strFilePath[8].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("background3", IMG_Load(strFilePath[9].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("map4", IMG_Load(strFilePath[10].c_str())));
		m_Gestionaire->AjouterSurface(new CSurface("background4", IMG_Load(strFilePath[11].c_str())));
		/* The potato is a lie */
		
		m_SaveFile->open(strFilePath[12].c_str());
	}
	
	static void LoadData(){
		string strReader, strObj, tabParam[4];
		Uint8 itterator;
		char buf[1024];
		while (!m_SaveFile->eof()) {
			m_SaveFile->getline(buf, sizeof(buf));
			strReader = buf;
			strObj = strReader.substr(0,4);
			itterator = SDL_atoi(&strReader[5]);
			if (strObj == "MMap"){
				for (int i = 0; i < 4; i++){
					m_SaveFile->getline(buf, sizeof(buf));
					strReader = buf;
					if (strReader.substr(0,4) == "Name"){
						strReader.erase(0, 5);
						tabParam[0] = strReader;
					}
					else if (strReader.substr(0,4) == "Grvt"){
						strReader.erase(0, 5);
						tabParam[1] = strReader;
					}
					else if (strReader.substr(0,4) == "Wind"){
						strReader.erase(0, 5);
						tabParam[2] = strReader;
					}
					else if (strReader.substr(0,4) == "Mine"){
						strReader.erase(0, 5);
						tabParam[3] = strReader;
					}
				}
				TabMap[itterator] = new CMap(tabParam[0], m_Gestionaire->GetTexture("background1")->GetTexture(), m_Gestionaire->GetSurface("map1")->getSurface(), SDL_atoi(tabParam[1].c_str()), SDL_atoi(tabParam[2].c_str()), SDL_atoi(tabParam[3].c_str()));
			}
			else if (strObj == "Team"){
				m_SaveFile->getline(buf, sizeof(buf));
				strReader = buf;
				strReader.erase(0, 5);
			
			}
		}
	}
	static void SaveData(){
		
		// Banana Banana Banana...
		
	}
	
	static void Quit(){
		delete m_pWindow;
		delete m_MenuPrincipal;
		delete m_MenuNewGame;
		delete m_MenuPause;
		delete m_MenuNewTeam;
		delete m_pEvent;
		m_SaveFile->close();
		delete m_SaveFile;
	}
	
	
	static void Init(string _argv){
		m_pWindow = new CWindow("Worms", WIDTH, HEIGHT);
		m_MenuPrincipal = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
		m_MenuNewGame = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
		m_MenuPause = new CMenu(m_pWindow->getRenderer(), {0, 0, (WIDTH / 2), (HEIGHT / 2)});
		m_MenuNewTeam = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
		m_pEvent = new SDL_Event();
		m_Gestionaire = new CGestionnaireRessources();
		
		LoadResources(_argv);
		LoadData();
		
			//
			// Initialisation du menu Principal
			//
		m_MenuPrincipal->AddElement(new CButton("btnNewGame", "New Game", m_Gestionaire->GetFont("FontMenu"), {0,0,10,10}, m_Gestionaire->GetSprite("SpriteBtnNG")), 800, 200, 162, 33);
		m_MenuPrincipal->AddElement(new CButton("btnQuit", "Quit", m_Gestionaire->GetFont("FontMenu"), {0,0,10,10}, m_Gestionaire->GetSprite("SpriteBtnQ")), 800, 500, 162, 33);
		m_MenuPrincipal->AddElement(new CLabel("lblWorms", "Worms", m_Gestionaire->GetFont("FontMenu"), {0, 0, 10, 10}), 100, 100, 400, 200);
		m_MenuPrincipal->getElement("btnQuit")->OnClickAction = BtnQuit;
		m_MenuPrincipal->getElement("btnNewGame")->OnClickAction = BtnNewGame;
		m_MenuPrincipal->ActivateMenu();
			//
			// Initialisation du menu NewGame
			//
		m_MenuNewGame->AddElement(new CLabel("lblNewGame", "Create a new game", m_Gestionaire->GetFont("FontMenu"), {}), 0, 0, 100, 20);
		m_MenuNewGame->AddElement(new CButton("btnCancelNG", "Cancel", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteBtnCancelNG")), 20, (HEIGHT - 66), 162, 33);
		m_MenuNewGame->getElement("btnCancelNG")->OnClickAction = BtnCancelNG;
		m_MenuNewGame->AddElement(new CButton("btnPlay", "Play", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteBtnPlay")), ((WIDTH / 2) - 81), (HEIGHT - 66), 162, 33);
		m_MenuNewGame->AddElement(new CButton("btnNTeam", "New Team", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteBtnNT")), (WIDTH - 182), (HEIGHT - 66), 162, 33);
		m_MenuNewGame->getElement("btnNTeam")->OnClickAction = BtnNewTeam;
		CSlideShow* SSTemp = new CSlideShow("SSMap", m_Gestionaire->GetFont("FontMenu"), {20, 40, 600, 300}, m_Gestionaire->GetSprite("SpriteMapLeft"), m_Gestionaire->GetSprite("SpriteMapRight"));
		SSTemp->ajouterTexture(4, SDL_CreateTextureFromSurface(m_pWindow->getRenderer(), m_Gestionaire->GetSurface("map1")->getSurface()), SDL_CreateTextureFromSurface(m_pWindow->getRenderer(), m_Gestionaire->GetSurface("map2")->getSurface()), SDL_CreateTextureFromSurface(m_pWindow->getRenderer(), m_Gestionaire->GetSurface("map3")->getSurface()), SDL_CreateTextureFromSurface(m_pWindow->getRenderer(), m_Gestionaire->GetSurface("map4")->getSurface()));
		SSTemp->setOnClickNext(BtnMapNext);
		SSTemp->setOnClickPrev(BtnMapPrev);
		m_MenuNewGame->AddElement(SSTemp, 20, 40, 600, 300);
		m_MenuNewGame->AddElement(new CLabel("lblMapName", "Map : ", m_Gestionaire->GetFont("FontMenu"), {}), 62, 420, 100, 20);
		m_MenuNewGame->AddElement(new CLabel("lblMapInfo", "Wind : ", m_Gestionaire->GetFont("FontMenu"), {}), 62, 460, 100, 20);
		CSlideShow* SSTemp2 = new CSlideShow("SSTeam", m_Gestionaire->GetFont("FontMenu"), {660, 40, 600, 300}, m_Gestionaire->GetSprite("SpriteTeamLeft"), m_Gestionaire->GetSprite("SpriteTeamRight"));
		SSTemp2->ajouterText(4, new string("Team Ritch"), new string("Team Kev"), new string("Team Die-Jess"), new string("Team Dom"));
		m_MenuNewGame->AddElement(SSTemp2, 660, 40, 600, 300);
		m_MenuNewGame->AddElement(new CLabel("lblPlayer1", "Player 1 : ", m_Gestionaire->GetFont("FontMenu"), {}), 702, 380, 100, 20);
		m_MenuNewGame->AddElement(new CButton("btnP1", "Add/Remove", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteBtnP1")), WIDTH - 182, 380, 162, 33);
		m_MenuNewGame->getElement("btnP1")->OnClickAction = BtnAddRemP1;
		m_MenuNewGame->AddElement(new CLabel("lblPlayer2", "Player 2 : ", m_Gestionaire->GetFont("FontMenu"), {}), 702, 420, 100, 20);
		m_MenuNewGame->AddElement(new CButton("btnP2", "Add/Remove", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteBtnP2")), WIDTH - 182, 420, 162, 33);
		m_MenuNewGame->getElement("btnP2")->OnClickAction = BtnAddRemP2;
		m_MenuNewGame->AddElement(new CLabel("lblPlayer3", "Player 3 : ", m_Gestionaire->GetFont("FontMenu"), {}), 702, 460, 100, 20);
		m_MenuNewGame->AddElement(new CButton("btnP3", "Add/Remove", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteBtnP3")), WIDTH - 182, 460, 162, 33);
		m_MenuNewGame->getElement("btnP3")->OnClickAction = BtnAddRemP3;
		m_MenuNewGame->AddElement(new CLabel("lblPlayer4", "Player 4 : ", m_Gestionaire->GetFont("FontMenu"), {}), 702, 500, 100, 20);
		m_MenuNewGame->AddElement(new CButton("btnP4", "Add/Remove", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteBtnP4")), WIDTH - 182, 500, 162, 33);
		m_MenuNewGame->getElement("btnP4")->OnClickAction = BtnAddRemP4;
			//
			// Initialisation du menu NewTeam
			//
		m_MenuNewTeam->AddElement(new CButton("btnCancelNT", "Cancel", m_Gestionaire->GetFont("FontMenu"), {}, m_Gestionaire->GetSprite("SpriteBtnCancelNT")), 20, (HEIGHT - 66), 162, 33);
		m_MenuNewTeam->getElement("btnCancelNT")->OnClickAction = BtnCancelNT;
		m_MenuNewTeam->AddElement(new CLabel("lblTxtTName", "Name your team", m_Gestionaire->GetFont("FontMenu"), {}), 20, 20, 100, 20);
		m_MenuNewTeam->AddElement(new CTextBox("txtTeamName", "", m_Gestionaire->GetFont("FontMenu"), {20, 50, 200, 30}, m_pWindow->getRenderer()), 20, 50, 200, 30);
	}
	
		//
		// Définition des action de chaque bouton dans les menu.
		//
	static void BtnQuit(){
		m_boRun = false;
	}
	static void BtnNewGame(){
		m_MenuPrincipal->DeActivateMenu();
		m_MenuNewGame->ActivateMenu();
	}
	static void BtnCancelNG(){
		m_MenuNewGame->DeActivateMenu();
		m_MenuPrincipal->ActivateMenu();
	}
	static void BtnCancelNT(){
		m_MenuNewTeam->DeActivateMenu();
		m_MenuNewGame->ActivateMenu();
	}
	static void BtnNewTeam(){
		m_MenuNewGame->DeActivateMenu();
		m_MenuNewTeam->ActivateMenu();
	}
	static void BtnMapNext(){
		m_MenuNewGame->getElement("lblMapName")->setText("Map : Yolo");
		m_MenuNewGame->getElement("lblMapInfo")->setText("Wind : Evil");
	}
	static void BtnMapPrev(){
		m_MenuNewGame->getElement("lblMapName")->setText("Map : Yolo");
		m_MenuNewGame->getElement("lblMapInfo")->setText("Wind : Evil");
	}
	static void BtnAddRemP1(){
		string temp = m_MenuNewGame->getElement("lblPlayer1")->getText();
		if (temp[temp.length() - 2] == ':'){
			temp.append(m_MenuNewGame->getElement("SSTeam")->getText());
			m_MenuNewGame->getElement("lblPlayer1")->setText(temp.c_str());
		}
		else
			m_MenuNewGame->getElement("lblPlayer1")->setText("Player 1 : ");
	}
	static void BtnAddRemP2(){
		string temp = m_MenuNewGame->getElement("lblPlayer2")->getText();
		if (temp[temp.length() - 2] == ':'){
			temp.append(m_MenuNewGame->getElement("SSTeam")->getText());
			m_MenuNewGame->getElement("lblPlayer2")->setText(temp.c_str());
		}
		else
			m_MenuNewGame->getElement("lblPlayer2")->setText("Player 2 : ");
	}
	static void BtnAddRemP3(){
		string temp = m_MenuNewGame->getElement("lblPlayer3")->getText();
		if (temp[temp.length() - 2] == ':'){
			temp.append(m_MenuNewGame->getElement("SSTeam")->getText());
			m_MenuNewGame->getElement("lblPlayer3")->setText(temp.c_str());
		}
		else
			m_MenuNewGame->getElement("lblPlayer3")->setText("Player 3 : ");
	}
	static void BtnAddRemP4(){
		string temp = m_MenuNewGame->getElement("lblPlayer4")->getText();
		if (temp[temp.length() - 2] == ':'){
			temp.append(m_MenuNewGame->getElement("SSTeam")->getText());
			m_MenuNewGame->getElement("lblPlayer4")->setText(temp.c_str());
		}
		else
			m_MenuNewGame->getElement("lblPlayer4")->setText("Player 4 : ");
	}
	
};

	// Initialisation des données membre statique

CWindow* CWorms::m_pWindow = nullptr;
CMenu* CWorms::m_MenuPrincipal = nullptr;
CMenu* CWorms::m_MenuNewGame = nullptr;
CMenu* CWorms::m_MenuPause = nullptr;
CMenu* CWorms::m_MenuNewTeam = nullptr;
bool CWorms::m_boInMenu = true;
SDL_Event* CWorms::m_pEvent = nullptr;
CGestionnaireRessources* CWorms::m_Gestionaire = nullptr;
bool CWorms::m_boRun = true;
CTeam* CWorms::TabTeam[4];
CMap* CWorms::TabMap[4];
fstream* CWorms::m_SaveFile = new fstream();

