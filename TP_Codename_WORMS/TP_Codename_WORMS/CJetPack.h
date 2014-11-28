#ifndef TP_Codename_WORMS_CJetPack_h
#define TP_Codename_WORMS_CJetPack_h

/* Liste de chose TOO DOOO :
-Afficher la barre de gaz
*/
/*!
 @class CJetPack
 @discussion Classe permettant l'affichage et l'utilisation du JetPack
 */
class CJetPack{
private:
	//Données membres:
	SDL_Rect m_RectWorm;
	SDL_Rect m_RectSurface;		// La pos du rectangle de la surface de la barre de gaz
	SDL_Texture* m_pTexture;	// Texture de l'image à afficher.
	CPowerBar* m_pBarreGaz;		// Surface de la barre de lancement.
	bool boBarreGaz;			// Booléen pour vérifier si la barre de lancement sera afficher
	double m_iAngle;			// 
	double m_iNorme;			// 
	C2DVector* m_pVecteur;		// 
	CTimer* m_pTimer;			// 


public:


	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _ix _iy : la pos du jet pack (à modifier pour la pos du worms)
	@param _pTexture : texture de l'image à afficher.
	@return Adresse mémoire de l'objet.
	@discussion No discussion is needed.
	*/
	CJetPack(int _ix, int _iy, SDL_Rect _RectWorm){ // La position du jet pack devra être remplacer par la position du worms
		m_RectSurface = _RectWorm;
		m_RectWorm = _RectWorm;
		m_pBarreGaz = new CPowerBar(m_RectSurface);
		m_pBarreGaz->setPowerLevel(100);
		m_iAngle = 0;
		m_iNorme = 20;
		m_pVecteur = new C2DVector(m_iNorme, m_iAngle, _ix, _iy);
		boBarreGaz = false;
		m_pTimer = new CTimer();
		m_pTimer->SetTimer(100);

	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead.
	*/
	~CJetPack(){
	}

	/*!
	@methodRender
	@param _pRenderer : Renderer pour rendre la texture du jet Pack
	@return null
	*/
	void Render(SDL_Renderer* _pRenderer){
		m_pBarreGaz->Draw(_pRenderer);
	}

	/*!
	@method Deplacer
	@brief Deplace le jetpack
	@param _RectPosInitiale: position initiale du worm
	@param _Angle : angle du vecteur depolacement j'imagine.
	@return Aucun
	@discussion none.
	*/
	void Deplacer(SDL_Rect _RectPosInitiale, double _Angle){
		_RectPosInitiale.x += m_iNorme * cos(_Angle);
		_RectPosInitiale.y += m_iNorme * sin(_Angle);
		m_RectWorm = _RectPosInitiale;
	}
	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event* _Event){
		switch (_Event->key.keysym.sym){
		case SDLK_LEFT:
			if (!m_pTimer->IsElapsed()){
				m_pTimer->Start();
			}
			Deplacer(m_RectWorm, (M_PI));
			if (m_pTimer->IsElapsed()){
				if (m_pBarreGaz->getPowerLevel() != 0){
					m_pBarreGaz->PowerDown();
					m_pTimer->Start();
				}
			}

			break;

		case SDLK_UP:
			if (!m_pTimer->IsElapsed()){
				m_pTimer->Start();
			}

			Deplacer(m_RectWorm, (M_PI / 2));
			if (m_pTimer->IsElapsed()){
				if (m_pBarreGaz->getPowerLevel() != 0){
					m_pBarreGaz->PowerDown();
					m_pTimer->Start();
				}
			}
			break;
		case SDLK_RIGHT:
			if (!m_pTimer->IsElapsed()){
				m_pTimer->Start();
			}
			Deplacer(m_RectWorm, 0);
			if (m_pTimer->IsElapsed()){
				if (m_pBarreGaz->getPowerLevel() != 0){
					m_pBarreGaz->PowerDown();
					m_pTimer->Start();
				}
			}
			break;

		}
	}


};

#endif
