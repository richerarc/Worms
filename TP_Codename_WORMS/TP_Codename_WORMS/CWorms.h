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
public:
	
	CWorms(){
		m_pWindow = new CWindow("Worms", WIDTH, HEIGHT);
		m_MenuPrincipal = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
		m_MenuNewGame = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
		m_MenuPause = new CMenu(m_pWindow->getRenderer(), {0, 0, (WIDTH / 2), (HEIGHT / 2)});
		m_MenuNewTeam = new CMenu(m_pWindow->getRenderer(), {0, 0, WIDTH, HEIGHT});
	}
	
	~CWorms(){
		delete m_pWindow;
		delete m_MenuPrincipal;
		delete m_MenuNewGame;
		delete m_MenuPause;
		delete m_MenuNewTeam;
	}
	
	
	
	void Init(){
		
	}
	
	void Quit(){
		
	}
};
