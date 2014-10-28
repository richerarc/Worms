//
//  CTimer.h
//  CFenetre
//
//  Created by Richer Archambault on 2014-10-07.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//

#ifndef CFenetre_CTimer_h
#define CFenetre_CTimer_h



class CTimer {
private:
	unsigned int m_uiTikcs,
				 m_uiTimeToElapse;
public:
	CTimer(){
		m_uiTikcs = 0;
		m_uiTimeToElapse = 0;
	}
	
	void Start(){
		m_uiTikcs = SDL_GetTicks();
	}
	
	void SetTimer(unsigned int _timeToElapse){
		m_uiTimeToElapse = _timeToElapse;
	}
	
	bool IsElapsed(){
		return ((SDL_GetTicks() - m_uiTikcs) >= m_uiTimeToElapse);
	}
};

#endif
