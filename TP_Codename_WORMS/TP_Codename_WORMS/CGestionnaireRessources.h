//Classe créée par Dominique Fauteux-Chapleau
//Dernière mise à jour : 5 Novembre 2014


/*
Classe : CGestionnaireRessources
Discussion : Classe pour implémenté un gestionnaire des ressources
*/
#include "CRessource.h"

class CGestionnaireRessources{
private:
	CListeDC<CSprite*>* m_pListeSprites;
	CListeDC<CFont*> m_pListeFonts;
	CListeDC<CMusic*> m_pListeMusics;
public:
	//Constructeur...
	CGestionnaireRessources(){
		m_pListeSprites = new CListeDC<CSprite*>();
		m_pListeFonts = new CListeDC<CFont*>();
		m_pListeMusics = new CListeDC<CMusic*>();
	}

	//Destructeur...
	~CGestionnaireRessources(){
		delete m_pListeSprites;
		delete m_pListeFonts;
		delete m_pListeMusics;
	}

	//Méthodes...

	/*
	Méthode : AjouterSprite
	Brief : Procédure qui ajoute un sprite à la liste appropriée
	Param : _Ressource : Ressource à ajouter
	Discussion : La ressource n'a pas besoin d'être ajouté spécifiquement à la fin, peut être changé
	*/
	void AjouterSprite(CSprite* _Ressource){
		m_pListeSprites->AjouterFin(_Ressource);
	}

	/*
	Méthode : AjouterFont
	Brief : Procédure qui ajoute un font à la liste appropriée
	Param : _Ressource : Ressource à ajouter
	Discussion : La ressource n'a pas besoin d'être ajouté spécifiquement à la fin, peut être changé
	*/
	void AjouterFont(CFont* _Ressource){
		m_pListeFonts->AjouterFin(_Ressource);
	}

	/*
	Méthode : AjouterMusic
	Brief : Procédure qui ajoute une musique à la liste appropriée
	Param : _Ressource : Ressource à ajouter
	Discussion : La ressource n'a pas besoin d'être ajouté spécifiquement à la fin, peut être changé
	*/
	void AjouterMusic(CMusic* _Ressource){
		m_pListeMusics->AjouterFin(_Ressource);
	}


	/*
	Méthode : RetirerSprite
	Brief : Procédure qui retire un sprite à la liste appropriée
	Param : _Name : Ressource à retirer
	*/
	void RetirerSprite(const char* _Name){
		m_pListeSprites->AllerDebut();
		for (int i = 0; i < m_pListeSprites->Count(); i++){
			if (m_pListeSprites->ObtenirElement()->GetName() == _Name){
				m_pListeSprites->Retirer(true);
				i = m_pListeSprites->Count();
			}
			else {
				m_pListeSprites->AllerSuivant();
			}
		}
	}

	/*
	Méthode : RetirerFont
	Brief : Procédure qui retire un font à la liste appropriée
	Param : _Name : Ressource à retirer
	*/
	void RetirerFont(const char* _Name){
		m_pListeFonts->AllerDebut();
		for (int i = 0; i < m_pListeFonts->Count(); i++){
			if (m_pListeFonts->ObtenirElement()->GetName() == _Name){
				m_pListeFonts->Retirer(true);
				i = m_pListeFonts->Count();
			}
			else {
				m_pListeFonts->AllerSuivant();
			}
		}
	}

	/*
	Méthode : RetirerMusic
	Brief : Procédure qui retire une musique à la liste appropriée
	Param : _Name : Ressource à retirer
	*/
	void RetirerMusic(const char* _Name){
		m_pListeMusics->AllerDebut();
		for (int i = 0; i < m_pListeMusics->Count(); i++){
			if (m_pListeMusics->ObtenirElement()->GetName() == _Name){
				m_pListeMusics->Retirer(true);
				i = m_pListeMusics->Count();
			}
			else {
				m_pListeMusics->AllerSuivant();
			}
		}
	}

	/*
	Méthode : GetSprite
	Brief : Fonction qui retourne un sprite de la liste appropriée
	Param : _Name : Nom de la ressource à obtenir
	*/
	CSprite* GetSprite(const char* _Name){
		m_pListeSprites->AllerDebut();
		for (int i = 0; i < m_pListeSprites->Count(); i++){
			if (m_pListeSprites->ObtenirElement()->GetName() == _Name){
				return m_pListeSprites->ObtenirElement();
			}
			else {
				m_pListeSprites->AllerSuivant();
			}
			if (i == m_pListeSprites->Count() - 1){
				return nullptr;
			}
		}
	}

	/*
	Méthode : GetFont
	Brief : Fonction qui retourne un font de la liste appropriée
	Param : _Name : Nom de la ressource à obtenir
	*/
	CSprite* GetFont(const char* _Name){
		m_pListeFonts->AllerDebut();
		for (int i = 0; i < m_pListeFonts->Count(); i++){
			if (m_pListeFonts->ObtenirElement()->GetName() == _Name){
				return m_pListeFonts->ObtenirElement();
			}
			else {
				m_pListeFonts->AllerSuivant();
			}
			if (i == m_pListeFonts->Count() - 1){
				return nullptr;
			}
		}
	}

	/*
	Méthode : GetMusic
	Brief : Fonction qui retourne un font de la liste appropriée
	Param : _Name : Nom de la ressource à obtenir
	*/
	CSprite* GetMusic(const char* _Name){
		m_pListeMusics->AllerDebut();
		for (int i = 0; i < m_pListeMusics->Count(); i++){
			if (m_pListeMusics->ObtenirElement()->GetName() == _Name){
				return m_pListeMusics->ObtenirElement();
			}
			else {
				m_pListeMusics->AllerSuivant();
			}
			if (i == m_pListeMusics->Count() - 1){
				return nullptr;
			}
		}
	}
};