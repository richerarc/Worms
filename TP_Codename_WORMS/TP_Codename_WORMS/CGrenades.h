#ifndef TP_Codename_WORMS_CGrenades_h
#define TP_Codename_WORMS_CGrenades_h


/*!
@CGrenades
@Classe permettant la création d'une grenade
*/
class CGrenades : public CObjets{

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@Paramètres: Le nom du labelImage afin de l'identifier, le text à l'intérieur, le font et le rect, et la texture contenant l'image.
	@Classe héritant de CGUIE, donc elle passe les paramètres nécessaires au constructeur de CGUIE
	*/
	CGrenades(const char* _Name, unsigned int _uiMasse, SDL_Rect _RectPos) : CObjets(_Name, _uiMasse, _RectPos){
	}
	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CGrenades(){
	}


	
	/*!
	@Accesseurs:
	*/

};

#endif
