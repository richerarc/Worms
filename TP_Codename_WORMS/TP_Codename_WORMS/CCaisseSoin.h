#ifndef TP_Codename_WORMS_CCaisseSoin_h
#define TP_Codename_WORMS_CCaisseSoin_h


/*!
@CCaisseSoin
@Classe permettant la création d'une caisse de soin
*/
class CCaisseSoin : public CCaisses{

public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@Paramètres: Le nom du labelImage afin de l'identifier, le text à l'intérieur, le font et le rect, et la texture contenant l'image.
	@Classe héritant de CGUIE, donc elle passe les paramètres nécessaires au constructeur de CGUIE
	*/
	CCaisseSoin() :CCaisses(){
	}
	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CCaisseSoin(){
	}



	/*!
	@Accesseurs:
	*/

};

#endif
