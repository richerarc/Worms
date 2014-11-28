#define BUFFER 1024
class CSound : public CRessource{
private:
	Mix_Music* m_pSound;		 // Musique à jouer
	static bool m_boInitialized; // Indique si la musique à été initialisé.
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _Name Texture du son.
	@param _Path emplacement de la musique.
	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de Ressource, elle prend donc les paramètres de CRessource.
	*/
	CSound(const char* _Name, const char* _Path) : CRessource(_Name){
		if (!m_boInitialized){
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, BUFFER);
			Mix_AllocateChannels(0);
			m_boInitialized = true;
		}
		m_pSound = Mix_LoadMUS(_Path);
	}

	~CSound(){
		Mix_FreeMusic(m_pSound);
	}

	/*!
	@method Play
	@brief methode pour faire jouer la musique
	@param _inbrOfLoop : nombre de fois que le musique doit être jouer
	@return Aucun
	*/
	void Play(int _inbrOfLoop){
		if (!Mix_PlayingMusic())
			Mix_PlayMusic(m_pSound, _inbrOfLoop);
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
bool CSound::m_boInitialized = false;