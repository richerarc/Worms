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
	//Constructeur...
	CRessource(const char* _Name){
		m_strName = _Name;
	}

	//Destructeur...
	~CRessource(){
		
	}

	//Accesseur...
	const char* GetName(){
		return m_strName;
	}
};

#endif
