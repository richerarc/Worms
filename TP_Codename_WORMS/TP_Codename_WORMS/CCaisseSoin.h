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
<<<<<<< HEAD
	@Paramètres: 
	@Classe héritant 
=======
	@Paramètres: Le nom du labelImage afin de l'identifier, le text à l'intérieur, le font et le rect, et la texture contenant l'image.
	@Classe héritant de CGUIE, donc elle passe les paramètres nécessaires au constructeur de CGUIE
	*/
	CCaisseSoin(const char* _Name, unsigned int _uiMasse, SDL_Rect _RectPos) :CCaisses(_Name, _uiMasse, _RectPos){
	}
	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
>>>>>>> 620d262c90c1eaa43e43336d6e0d57479837c984
	*/
	CCaisseSoin(int _iRayon, SDL_Rect _RectPos , SDL_Texture* _pTexture) :CCaisses(_iRayon, _RectPos,_pTexture){
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
