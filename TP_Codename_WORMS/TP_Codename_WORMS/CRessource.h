//
//  CRessource.h
//  TP_Codename_WORMS_Mac
//
//  Created by Richer Archambault on 2014-10-28.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//


#ifndef TP_Codename_WORMS_CRessource_h
#define TP_Codename_WORMS_CRessource_h


/*
@class CRessource
@discussion Classe représentant une ressource du gestionnaire
*/
class CRessource {
private:
	const char* m_strName; // Nom de la ressource pour faciliter l'accès.
	
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _Name Nom de la ressource
	@return Adresse mémoire de l'objet.
	@discussion Avec un nom C'est plus facile de retrouver une ressource.
	*/
	CRessource(const char* _Name){
		m_strName = _Name;
	}

	/*!
	@method Destructeur:
	@brief Permet  de détruire les objets créés en mémoire
	*/
	~CRessource(){
		
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/
	const char* GetName(){
		return m_strName;
	}
};

#endif
