//Classe créée par Dominique Fauteux-Chapleau
//Dernière mise à jour : 5 Novembre 2014


/*
Classe : CGestionnaireRessources
Discussion : Classe pour implémenté un gestionnaire des ressources
*/
#include "CRessource.h"
#include "CMusic.h"
#include "CSprite.h"
#include "CFont.h"
#include "CTexture.h"
#include "CSurface.h"

class CGestionnaireRessources{
private:
	CListeDC<CSprite*>* m_pListeSprites;  // Liste de Sprites.
	CListeDC<CFont*>* m_pListeFonts;	  // Liste de Police.
	CListeDC<CSound*>* m_pListeSounds;	  // Liste de Sons.
	CListeDC<CTexture*>* m_pListeTexture; // Liste de Textures.
	CListeDC<CSurface*>* m_pListeSurface; // Liste de Surfaces.

public:

	//Constructeur...
	CGestionnaireRessources(){
		m_pListeSprites = new CListeDC<CSprite*>();
		m_pListeFonts = new CListeDC<CFont*>();
		m_pListeSounds = new CListeDC<CSound*>();
		m_pListeTexture = new CListeDC<CTexture*>();
		m_pListeSurface = new CListeDC<CSurface*>();

	}

	//Destructeur...
	~CGestionnaireRessources(){
		delete m_pListeSprites;
		delete m_pListeFonts;
		delete m_pListeSounds;
		delete m_pListeTexture;
		delete m_pListeSurface;
	}

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
	void AjouterMusic(CSound* _Ressource){
		m_pListeSounds->AjouterFin(_Ressource);
	}

	/*!
	@MéthodeAjouterTexture:
	@Brief: Fonction qui ajoute un CTexture de la liste appropriée
	@Paramètre: _Texture  , texture a ajouter.
	*/
	void AjouterTexture(CTexture* _Texture){
		m_pListeTexture->AjouterFin(_Texture);
	}

	/*!
	@Méthode: AjouterSurface:
	@Brief: Fonction qui ajoute un CSurface de la liste appropriée
	@Paramètre: _Surface  , Surface à ajouter.
	*/
	void AjouterSurface(CSurface* _Surface){
		m_pListeSurface->AjouterFin(_Surface);
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
	Méthode : RetirerSound
	Brief : Procédure qui retire une musique à la liste appropriée
	Param : _Name : Ressource à retirer
	*/
	void RetirerSound(const char* _Name){
		m_pListeSounds->AllerDebut();
		for (int i = 0; i < m_pListeSounds->Count(); i++){
			if (m_pListeSounds->ObtenirElement()->GetName() == _Name){
				m_pListeSounds->Retirer(true);
				i = m_pListeSounds->Count();
			}
			else {
				m_pListeSounds->AllerSuivant();
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
		return nullptr;
	}

	/*
	Méthode : GetFont
	Brief : Fonction qui retourne un font de la liste appropriée
	Param : _Name : Nom de la ressource à obtenir
	*/
	CFont* GetFont(const char* _Name){
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
		return nullptr;
	}

	/*
	Méthode : GetMusic
	Brief : Fonction qui retourne un font de la liste appropriée
	Param : _Name : Nom de la ressource à obtenir
	*/
	CSound* GetSound(const char* _Name){
		m_pListeSounds->AllerDebut();
		for (int i = 0; i < m_pListeSounds->Count(); i++){
			if (m_pListeSounds->ObtenirElement()->GetName() == _Name){
				return m_pListeSounds->ObtenirElement();
			}
			else {
				m_pListeSounds->AllerSuivant();
			}
			if (i == m_pListeSounds->Count() - 1){
				return nullptr;
			}
		}
		return nullptr;
	}

	/*!
	@Méthode GetTexture:
	@Brief: Fonction qui retourne un CTexture de la liste appropriée
	@Paramètre: Param : _Name : Nom de la ressource à obtenir
	*/
	CTexture* GetTexture(const char* _Name){
		m_pListeTexture->AllerDebut();
		for (int i = 0; i < m_pListeTexture->Count(); i++){
			if ((m_pListeTexture->ObtenirElement()->GetName()) == _Name){
				return m_pListeTexture->ObtenirElement();
			}
			else {
				m_pListeTexture->AllerSuivant();
			}
			if (i == m_pListeTexture->Count() - 1){
				return nullptr;
			}
		}
		return nullptr;
	}

	/*!
	@Méthode GetTexture:
	@Brief: Fonction qui retourne un CTexture de la liste appropriée
	@Paramètre: Param : _Name : Nom de la ressource à obtenir
	*/
	CSurface* GetSurface(const char* _Name){
		m_pListeSurface->AllerDebut();
		for (int i = 0; i < m_pListeSurface->Count(); i++){
			if (m_pListeSurface->ObtenirElement()->GetName() == _Name){
				return m_pListeSurface->ObtenirElement();
			}
			else {
				m_pListeSurface->AllerSuivant();
			}
			if (i == m_pListeSurface->Count() - 1){
				return nullptr;
			}
		}
		return nullptr;
	}

};