#ifndef TP_Codename_WORMS_CMines_h
#define TP_Codename_WORMS_CMines_h


/*!
@CGrenades
@Classe permettant la création d'une grenade
*/
class CMines : public CObjets{

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@Paramètres: Le nom du labelImage afin de l'identifier, le text à l'intérieur, le font et le rect, et la texture contenant l'image.
	@Classe héritant de CGUIE, donc elle passe les paramètres nécessaires au constructeur de CGUIE
	*/
	CMines() :CObjets(){
	}
	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CMines(){
	}



	/*!
	@Accesseurs:
	*/

};

#endif
