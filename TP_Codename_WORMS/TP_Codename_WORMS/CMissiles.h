#ifndef TP_Codename_WORMS_CMissiles_h
#define TP_Codename_WORMS_CMissiles_h


/*!
@CGrenades
@Classe permettant la création d'une grenade
*/
class CMissiles : public CObjets{

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@Paramètres: Le nom du labelImage afin de l'identifier, le text à l'intérieur, le font et le rect, et la texture contenant l'image.
	@Classe héritant de CGUIE, donc elle passe les paramètres nécessaires au constructeur de CGUIE
	*/
	CMissiles() :CObjets(){
	}
	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CMissiles(){
	}



	/*!
	@Accesseurs:
	*/

};

#endif
