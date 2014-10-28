//
//  CGUIE.h
//  TP_Codename_WORMS_Mac
//
//  Created by Richer Archambault on 2014-10-28.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//

#include <string>

using namespace std;

#ifndef TP_Codename_WORMS_CGUIE_h
#define TP_Codename_WORMS_CGUIE_h

class CGUIE {
private:
	const char* m_strName;
public:
	CGUIE(const char* _Name){
		m_strName = _Name;
	}
	
	string getName(){
		return m_strName;
	}
};

#endif
