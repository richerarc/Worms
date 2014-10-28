//
//  CMusic.h
//  Ate5
//
//  Created by Richer Archambault on 2014-10-15.
//  Copyright (c) 2014 Richer Archambault. All rights reserved.
//

#ifndef Ate5_CMusic_h
#define Ate5_CMusic_h

#define BUFFER 1024


/*!
 @class CMusic
 @discussion Classe pour la ressourse de son
 */
class CMusic {
private:
	Mix_Music* m_pMusic;
	static bool m_boInitialized;
public:
	CMusic(const char* _Path){
		if (!m_boInitialized){
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, BUFFER);
			Mix_AllocateChannels(0);
			m_boInitialized = true;
		}
		m_pMusic = Mix_LoadMUS(_Path);
	}
	~CMusic(){
		Mix_FreeMusic(m_pMusic);
	}
	
	/*!
	 @method Play
	 @brief methode pour faire jouer la musique
	 @param _inbrOfLoop : nombre de fois que le musique doit être jouer
	 @return Aucun
	 */
	void Play(int _inbrOfLoop){
		if (!Mix_PlayingMusic())
			Mix_PlayMusic(m_pMusic, _inbrOfLoop);
		else
			Mix_ResumeMusic();
	}
	
	/*!
	 @method Pause
	 @brief methode pour mettre la musique en pause
	 @param Aucun
	 @return Aucun
	 */
	void Pause(){
		if (Mix_PlayingMusic())
			Mix_PauseMusic();
	}
};


bool CMusic::m_boInitialized = false;

#endif
