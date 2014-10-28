/*	
420-202-RE : Structure de données "la Liste doublement chaînée"
Classe CListeDC
Crée le 15 avril 2014 par Kevin Pantelakis( DA : 1303126  /  E-mail : kev.pantelakis@gail.com)
*/
template <class T>
class CCelluleListeDC{
private:

	CCelluleListeDC<T>* m_pSuivant;	  // Pointeur de cellule suivante.
	CCelluleListeDC<T>* m_pPrecedent; // Pointeur de cellule précédente.
	T m_Element;				   	  // Élément a contenir dans la liste.

public:

	//Constructeur
	//Paramètre : l'élément a contenir dans la file et les pointeurs de cellule suivante et précédente.
	//Retour: L'adresse mémoire.
	CCelluleListeDC(T _Element,CCelluleListeDC<T>* _Precedent, CCelluleListeDC<T>* _Suivant){
		m_Element = _Element;
		m_pPrecedent = _Precedent;
		m_pSuivant = _Suivant;
	}

	//Destructeur
	~CCelluleListeDC(){
	}

	//Acesseurs.

	T getElement(){
		return m_Element;
	}

	CCelluleListeDC<T>* getSuivant(){
		return m_pSuivant;
	}

	CCelluleListeDC<T>* getPrecedent(){
		return m_pPrecedent;
	}

	void setSuivant(CCelluleListeDC<T>* _pSuivant){
		m_pSuivant = _pSuivant;
	}

	void setPrecedent(CCelluleListeDC<T>* _pPrecedent){
		m_pPrecedent = _pPrecedent;
	}

};
template <class T>
class CListeDC{
private:

	CCelluleListeDC<T>* m_pDerniere;// Pointe sur la dernière cellule.
	CCelluleListeDC<T>* m_pCurseur; // Pointeur sur une cellule quelconque.
	unsigned int m_uiCompte;		// Nombre de cellule dans la liste.

public:

	//Constructeur
	CListeDC(){
		m_pDerniere = nullptr;
		m_pCurseur = nullptr;
		m_uiCompte = 0;
	}

	//Destructeur
	~CListeDC(){
		AllerDebut();
		while(m_pDerniere != nullptr)
			 Retirer(true);
	}

	//Méthodes.

	/********************************************************************************
	But: Mettre le curseur au début de la liste.

	Paramètres: Aucun.

	Retour: true si l'opération s'est faite et false si elle ne s'est pas exécutée.
	********************************************************************************/
	bool AllerDebut(){
		if(m_pDerniere != nullptr)
		{
			m_pCurseur = m_pDerniere->getSuivant();
			return true;
		}
		return false;
	}

	/********************************************************************************
	But:  Mettre le curseur a la fin de la liste.

	Paramètres: Aucun

	Retour: true si l'opération s'est faite et false si elle ne s'est pas exécutée.
	********************************************************************************/
	bool AllerFin(){
		if(m_pDerniere != nullptr)
		{
			m_pCurseur = m_pDerniere;
			return true;
		}
		return false;
	}

	/********************************************************************************
	But: Déplacer le curseur sur son suivant.

	Paramètres: Aucun.

	Retour: true si l'opération s'est faite et false si elle ne s'est pas exécutée.
	********************************************************************************/
	bool AllerSuivant(){
		if((m_pDerniere != nullptr) && (m_pCurseur->getSuivant() != m_pDerniere->getSuivant())){
			m_pCurseur = m_pCurseur->getSuivant();
			return true;
		}
		return false;
	}
	
	/****************************************************************************************
	But: Déplacer le curseur sur son précédent.

	Paramètres: Aucun.

	Retour: Retour: true si l'opération s'est faite et false si elle ne s'est pas exécutée.
	****************************************************************************************/
	bool AllerPrecedent(){
		if((m_pDerniere != nullptr) && (m_pCurseur->getPrecedent() != m_pDerniere)){
			m_pCurseur = m_pCurseur->getPrecedent();
			return true;
		}
		return false;
	}

	/*****************************************************************************************
	But: Met le curseur à la position désirée.

	Paramètres: unsigned int _uiPosition détermine la position ou mettre le curseur

	Retour: true si l'opération s'est faite et false si elle ne s'est pas exécutée.
	*****************************************************************************************/
	bool AllerA(unsigned int _uiPosition){
		if (_uiPosition >= m_uiCompte)
			return false;

		if (m_pDerniere != nullptr)
		{
			if(_uiPosition > (m_uiCompte / 2))
			{
				AllerFin();
				for(unsigned int ui = 0; ui < (m_uiCompte - _uiPosition) - 1; ui++)
					AllerPrecedent();
			}
			else
			{
				AllerDebut();
				for(unsigned int ui = 0; ui < (_uiPosition); ui++)
					AllerSuivant();
			}
			return true;
		}
		return false;
	}

	/******************************************************
	But: Ajoute une cellule au début de la liste.

	Paramètres: T _Element l'élément a lister.

	Retour: Aucun.
	*******************************************************/
	void AjouterDebut(T _Element){
		if(m_pDerniere == nullptr)
		{
			m_pDerniere = new CCelluleListeDC<T>(_Element,nullptr,nullptr);
			m_pDerniere->setSuivant(m_pDerniere);
			m_pDerniere->setPrecedent(m_pDerniere);
			m_uiCompte++;
		}
		else
		{
			m_pDerniere->setSuivant(new CCelluleListeDC<T>(_Element,m_pDerniere,m_pDerniere->getSuivant()));
			m_pDerniere->getSuivant()->getSuivant()->setPrecedent(m_pDerniere->getSuivant());
			m_uiCompte++;
		}
	}

	/******************************************************
	But: Ajoute une cellule à la fin de la liste.

	Paramètres: T _Element l'élément a lister.

	Retour: Aucun.
	*******************************************************/
	void AjouterFin(T _Element){
		if(m_pDerniere == nullptr)
		{
			m_pDerniere = new CCelluleListeDC<T>(_Element,nullptr,nullptr);
			m_pDerniere->setSuivant(m_pDerniere);
			m_pDerniere->setPrecedent(m_pDerniere);
			m_uiCompte++;
		}
		else
		{
			m_pDerniere->setSuivant(new CCelluleListeDC<T>(_Element,m_pDerniere,m_pDerniere->getSuivant()));
			m_pDerniere->getSuivant()->getSuivant()->setPrecedent(m_pDerniere->getSuivant());
			m_pDerniere = m_pDerniere->getSuivant();
			m_uiCompte++;
		}
	}

	/********************************************************************************
	But: Insère une cellule à l'endroit indiqué par le curseur

	Paramètres: T _Element l'élément a lister.

	Retour: true si l'opération s'est faite et false si elle ne s'est pas exécutée.
	*********************************************************************************/
	void Inserer(T _Element){
		
		//if(m_pCurseur == nullptr)
		//	return false;

		m_pCurseur = new CCelluleListeDC<T>(_Element,m_pCurseur->getPrecedent(),m_pCurseur);
		m_pCurseur->getPrecedent()->setSuivant(m_pCurseur);
		m_pCurseur->getSuivant()->setPrecedent(m_pCurseur);
		m_uiCompte++;

		//return true;
	}
	
	/*******************************************************************************
	But: Retire une cellule de la liste.

	Paramètres: bool _boSupprimer: supprimer ou non l'élément

	Retour: true si l'opération s'est faite et false si elle ne s'est pas exécutée.
	********************************************************************************/
	bool Retirer(bool _boSupprimer){
	
		if(m_pCurseur == nullptr)
			return false;

		CCelluleListeDC<T>* pCelltemp = m_pCurseur;
		m_pCurseur->getPrecedent()->setSuivant(m_pCurseur->getSuivant());
		m_pCurseur->getSuivant()->setPrecedent(m_pCurseur->getPrecedent());

		if(m_pCurseur == m_pDerniere){
			m_pCurseur = m_pCurseur->getPrecedent();
			m_pDerniere = m_pDerniere->getPrecedent();
		}
		else
			m_pCurseur = m_pCurseur->getSuivant();

		if (_boSupprimer)
			delete pCelltemp->getElement();

		delete pCelltemp;
		m_uiCompte--;
		if(!m_uiCompte)
		{
			m_pCurseur = nullptr;
			m_pDerniere = nullptr;
		}
		return true;
	}

	//Acesseurs//

	/******************************************************
	But: Obtient l'élément ou se trouve le curseur.

	Paramètres: Aucun.

	Retour: Retourne l'élément présent dans la liste.
	*******************************************************/
	T ObtenirElement(){
		if (m_pCurseur != nullptr)
			return m_pCurseur->getElement();
		return nullptr;
	}

	unsigned int Compte(){
		return m_uiCompte;
	}
};