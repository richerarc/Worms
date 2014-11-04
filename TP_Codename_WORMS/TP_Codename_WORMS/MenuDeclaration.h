/*!
 * Fichier pour la déclaration des Menu et de leurs fonction
 */


/*!
@discussion Déclaration de la Window.
*/
CWindow* Window = new CWindow(WIDTH,HEIGHT);
CGestionnaireRessources* GestionnaireDeResources = new CGestionnaireRessources();

void LoadResources(){
	GestionnaireDeResources->Ajouter(new CFont("Font", "C:\\Users\\1303126\\Documents\\GitHub\\Worms\\Ressources\\Archeologicaps.ttf", 18));
	GestionnaireDeResources->Ajouter(new CSprite("SpriteBtnFleche", IMG_LoadTexture(Window->getRenderer(), "C:\\Users\\1303126\\Documents\\GitHub\\Worms\\Ressources\\Btn2.png"), 2, 4, 10, 0));
	GestionnaireDeResources->Ajouter(new CSprite("SpriteBtnClick", IMG_LoadTexture(Window->getRenderer(), "C:\\Users\\1303126\\Documents\\GitHub\\Worms\\Ressources\\Btn1.png"), 2, 4, 10, 0));
}

/*!
 @discussion Déclaration du Menu Principal.
 */
CMenu* MenuPrincipal = new CMenu(Window->getRenderer(), {0,0,WIDTH,HEIGHT});
CButton* ButtonNewGame;
CButton* ButtonQuit;






CMenu* MenuNewGame;
CMenu* MenuNewTeam;
CMenu* MenuPause;
