//Classe créée par Dominique Fauteux-Chapleau
//Dernière mise à jour : 2 Novembre 2014


/*
Classe : CGestionnaireRessources
Discussion : Classe pour implémenté un gestionnaire des ressources
*/
#include "CListeDC.h"
#include "CRessource.h"

class CGestionnaireRessources{
private:
	ClisteDC<CRessource>* m_pListeRessources;
public:
	//Constructeur...
	CGestionnaireRessources(){
		m_pListeRessources = new CListeDC<CRessource*>();
	}

	//Destructeur...
	~CGestionnaireRessources(){
		delete m_pListeRessources;
	}

	//Méthodes...

	/*
	Méthode : Ajouter
	Brief : Procédure qui ajoute une ressource à la liste
	Param : _Ressource : Ressource à ajouter
	Discussion : La ressource n'a pas besoin d'être ajouté spécifiquement à la fin, peut être changé
				 De plus, on doit décider s'il faut vérifier qu'une ressource déjà dans le liste possède
				 déjà le nom de la nouvelle ressource.
	*/
	void Ajouter(CRessource* _Ressource){
		m_pListeRessources->AjouterFin(_Ressource);
	}

	/*
	Méthode : Retirer
	Brief : Procédure qui retire une ressource à la liste
	Param : _Name : Ressource à retirer
	Discussion : Noter que GetName() n'existe pas dans CRessource et sera à ajouter.
	*/
	void Retirer(const char* _Name){
		m_pListeRessources->AllerDebut();
		for (int i = 0; i < m_pListeRessources->Count(); i++){
			if (m_pListeRessources->ObtenirElement()->GetName() == _Name){
				m_pListeRessources->Retirer(true);
				i = m_pListeRessources->Count();
			}
			else {
				m_pListeRessources->AllerSuivant();
			}
		}
	}

	/*
	Méthode : Obtenir
	Brief : Fonction qui retourne une ressource de la liste
	Param : _Name : Nom de la ressource à obtenir
	Discussion : Noter que GetName() n'existe pas dans CRessource et sera à ajouter.
	*/
	CRessource* Obtenir(const char* _Name){
		m_pListeRessources->AllerDebut();
		for (int i = 0; i < m_pListeRessources->Count(); i++){
			if (m_pListeRessources->ObtenirElement()->GetName() == _Name){
				return m_pListeRessources->ObtenirElement();
			}
			else {
				m_pListeRessources->AllerSuivant();
			}
			if (i == m_pListeRessources->Count() - 1){
				return nullptr;
			}
		}
	}
};