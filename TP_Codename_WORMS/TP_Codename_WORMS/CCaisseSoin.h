#ifndef TP_Codename_WORMS_CCaisseSoin_h
#define TP_Codename_WORMS_CCaisseSoin_h


/*!
@CCaisseSoin
@Classe permettant la création d'une caisse de soin
*/
class CCaisseSoin : public CCaisses{
private:

	//Données membres:
	SDL_Texture* m_pTexture; // Texture de l'image à afficher.

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@Paramètres: 
	@Classe héritant 
	*/
	CCaisseSoin(int _iRayon, const char* _Name, unsigned int _uiMasse, SDL_Rect _RectPos, SDL_Texture* _pTexture) :CCaisses(_iRayon,_Name,_uiMasse, _RectPos){
	}





	/*!
	@Accesseurs:
	*/

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CCaisseSoin(){
	}

};

#endif
