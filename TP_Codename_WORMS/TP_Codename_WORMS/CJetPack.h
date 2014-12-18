#ifndef TP_Codename_WORMS_CJetPack_h
#define TP_Codename_WORMS_CJetPack_h

/* Liste de chose TOO DOOO :
-Faire en sorte que le worm en jetpack rotate dépendament si tu vas a gauche ou droite
-Tester
*/
/*!
 @class CJetPack
 @discussion Classe permettant l'affichage et l'utilisation du JetPack
 */
class CJetPack{
private:
	//Données membres:
	SDL_Rect m_RectJetPack;
	SDL_Rect m_RectSurface;		// La pos du rectangle de la surface de la barre de gaz
	CPowerBar* m_pBarreGaz;		// Surface de la barre de lancement.
	bool boBarreGaz;			// Booléen pour vérifier si la barre de lancement sera afficher
	double m_iAngle;			// L'angle d'orientation du vecteur de déplacement
	double m_iNorme;			// La norme du vecteur de déplacement
	CTimer* m_pTimer;			// Une minuterie pour décrémenter le power à tous les "x" secondes
	CWorm * Worm;
	bool m_boInUse;
	bool boGaz;

public:


	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _RectWorm: le rect position du worm qui s'apprete à s'envoler
	@return Adresse mémoire de l'objet.
	@discussion No discussion is needed.
	*/
	CJetPack(CWorm* _pWorm){
		Worm = _pWorm;
		m_RectJetPack = {0,0,0,0};
		m_pBarreGaz = new CPowerBar(m_RectSurface);
		m_pBarreGaz->setPowerLevel(100);
		m_iAngle = 0;
		m_iNorme = 20;
		boBarreGaz = false;
		m_pTimer = new CTimer();
		m_pTimer->SetTimer(100);
		boGaz = false;

	}
	
	void setJetPack(CWorm* _ActualWorm){
		Worm = _ActualWorm;
		m_RectJetPack.x = Worm->getPosition().x;
		m_RectJetPack.y = Worm->getPosition().y;
		m_pBarreGaz->SetPosition(m_RectJetPack.x, m_RectJetPack.y);
	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead. spotted
	*/
	~CJetPack(){
	}

	/*!
	@methodRender
	@param _pRenderer : Renderer pour render la barre de gaz
	@return null
	*/
	void Render(SDL_Renderer* _pRenderer){
		m_pBarreGaz->Draw(_pRenderer);
	}

	/*!
	 @method Deplacer
	 @brief Deplace le jetpack
	 @param _RectPosInitiale: position initiale du worm
	 @param _Angle : angle du vecteur deplacement.
	 @return Aucun
	 @discussion none.
	 */
	/*void Deplacer(SDL_Rect* _RectPosInitiale, double _Angle){
		_RectPosInitiale->x += m_iNorme * cos(_Angle);
		_RectPosInitiale->y += m_iNorme * sin(_Angle);
		m_RectJetPack = _RectPosInitiale;
		}*/

	/*!
	 @method HandleEvent
	 @param _Event : Un SDL_Event pour traiter les evenement
	 @return null
	 */
	void RefreshPosWorm(CWorm* _pWorm){
		_pWorm->setPosXY(m_RectJetPack.x, m_RectJetPack.y);
	}
	void HandleEvent(SDL_Event _Event){
		switch (_Event.type) {
		case SDL_KEYDOWN:
			switch (_Event.key.keysym.sym){
			case SDLK_UP:
				if (!boGaz){
					C2DVector * Vector = new C2DVector(0,0,0.,1.);
					Worm->getTrajectoire()->AddAcceleration(Vector);
					delete Vector;
				}

				boGaz = true;
				if (m_pBarreGaz->getPower() <= 0){
					boGaz = false;
					C2DVector * Vector = new C2DVector(0, 0, 0., -1.);
					Worm->getTrajectoire()->AddAcceleration(Vector);
					delete Vector;
				}
				else{
					m_pBarreGaz->PowerDown();
				}
				if (boGaz)
				break;
			case SDLK_LEFT:
				if (!boGaz){
					C2DVector * Vector = new C2DVector(0, 0, -1., 0.);
					Worm->getTrajectoire()->AddAcceleration(Vector);
					delete Vector;
				}
				boGaz = true;
				if (m_pBarreGaz->getPower() <= 0){
					boGaz = false;
					C2DVector * Vector = new C2DVector(0, 0, 1., 0.);
					Worm->getTrajectoire()->AddAcceleration(Vector);
					delete Vector;
				}
				else{
					m_pBarreGaz->PowerDown();
				}
				break;
			case SDLK_RIGHT:
				if (!boGaz){
					C2DVector * Vector = new C2DVector(0, 0, 1., 0.);
					Worm->getTrajectoire()->AddAcceleration(Vector);
					delete Vector;
				}
				boGaz = true;
				if (m_pBarreGaz->getPower() <= 0){
					boGaz = false;
					C2DVector * Vector = new C2DVector(0, 0, -1., 0.);
					Worm->getTrajectoire()->AddAcceleration(Vector);
					delete Vector;
				}
				else{
					m_pBarreGaz->PowerDown();
				}
				break;
			}
			break;

		case SDL_KEYUP:
			switch (_Event.key.keysym.sym){
			case(SDLK_UP) :
				boGaz = false;
				break;

			case(SDLK_LEFT) :
				boGaz = false;
				break;

			case(SDLK_RIGHT) :
				boGaz = false;
				break;
			}
			break;
		}

	}

	
	void setInUse(bool _bo){
		m_boInUse = _bo;
	}
	
	bool isInUse(){
		return m_boInUse;
	}


};

#endif
