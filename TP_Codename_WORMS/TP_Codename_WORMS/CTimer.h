//
//  CTimer.h
//  CFenetre
//
//  Created by Richer Archambault on 2014-10-07.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//

#ifndef CFenetre_CTimer_h
#define CFenetre_CTimer_h


/*!
 @class CTimer
 @discussion Classe pour implémenté une minuterie
 */
class CTimer {
private:
	unsigned int m_uiTicks,			// Nombre de ticks du départ du timer (miliSecondes).
				 m_uiTimeToElapse;	// Combien de ticks avant le déclenchement(miliSecondes).
	bool m_boPause;
	bool m_boIsStart;

public:

	/*!
	 @method Constructeur
	 */
	CTimer(){
		m_uiTicks = 0;
		m_uiTimeToElapse = 0;
		m_boPause = false;
		m_boIsStart = false;
	}
	
	/*!
	 @method Start
	 @brief Méthode qui démarre la minuterie
	 */
	void Start(){
		m_uiTicks = SDL_GetTicks();
		m_boIsStart = true;
	}
	
	/*!
	 @method SetTimer
	 @brief Méthode qui ajuste le temps de la minuterie
	 @param _timeToElapse : Entier du temps à écouler 
	 */
	void SetTimer(unsigned int _timeToElapse){
		m_uiTimeToElapse = _timeToElapse;
	}
	
	/*!
	 @method IsElapsed
	 @brief Fonction qui retourne par un bool si le temps de la minuterie est écoulé ou non
	 @return true : la minuterie est écoulée
	 @return false : la minuterie n'est pas écoulée
	 */
	bool IsElapsed(){
		return ((SDL_GetTicks() - m_uiTicks) >= m_uiTimeToElapse);
	}

	/*!
	@method HasStarted
	@brief Fonction qui retourne par un bool si la minuterie est commencée ou non
	@return true : la minuterie est start
	@return false : la minuterie n'est pas start
	*/
	bool HasStarted(){
		return m_boIsStart;
	}
	/*!
	 @method Pause
	 @brief Méthode qui redéfinie le temps de la minuterie pour la mettre en pause
	 */
	void Pause(){
		m_uiTimeToElapse = m_uiTimeToElapse - (SDL_GetTicks() - m_uiTicks);
		m_boPause = true;
	}

	/*!
	 @method UnPause
	 @brief Méthode qui appelle Start pour redémarrer la minuterie
	 @discussion Assez superflu, mais pratique pour ne pas oublier de redémarrer la minuterie après une pause
	 */
	void UnPause(){
		if (m_boPause){
			Start();
			m_boPause = false;
		}
	}
	
	unsigned int getElapsedTime(){
		return SDL_GetTicks() - m_uiTicks;
	}
};

#endif
