#ifndef TP_Codename_WORMS_CJetPack_h
#define TP_Codename_WORMS_CJetPack_h

/*!
 @class CJetPack
 @discussion Classe permettant l'affichage et l'utilisation du JetPack
 */
class CJetPack{
private:
	//Données membres:
	SDL_Rect m_pBarreGaz;// Surface de la barre de lancement.
	CWorm * Worm;//Un pointeur de worm actif.
	bool m_boInUse;//Booléen représentant si le jetpack est en utilisation ou pas
	bool boGaz;//Booléen représentant si le gaz est enfoncer pour une premiere fois.
	C2DVector * Vector;//Vecteur pour changer les déplacements du worm
public:


	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _Worm: Un pointeur vers le worm qui s'apprete à s'envoler.
	@return Adresse mémoire de l'objet.
	@discussion No discussion is needed.
	*/
	CJetPack(CWorm* _pWorm){
		Worm = _pWorm;
		m_pBarreGaz = { 0, 0, 5, 50 };
		boGaz = false;
	}

	/*!
	@method setJetPack
	@brief Permet de setter le jetpack
	@param _Worm: Un pointeur vers le actuel worm
	*/
	void setJetPack(CWorm* _ActualWorm){
		Worm = _ActualWorm;
		m_pBarreGaz.x = Worm->getPosition().x - 5;
		m_pBarreGaz.y = Worm->getPosition().y;
	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead. spotted
	*/
	~CJetPack(){
	}

	/*!
	@method Render
	@param _pRenderer : Renderer pour render la barre de gaz
	@return null
	*/
	void Render(SDL_Renderer* _pRenderer){
		SDL_SetRenderDrawColor(_pRenderer, (250 - (m_pBarreGaz.h * 5)), (m_pBarreGaz.h * 5), 0, 255);
		m_pBarreGaz.y = Worm->getPosition().y;
		m_pBarreGaz.x = Worm->getPosition().x - 5;
		SDL_RenderFillRect(_pRenderer, &m_pBarreGaz);
		MoveWorm();
	}

	/*!
	@method MoveWorm
	@brief Permet le mouvement du worm avec le JetPack
	@param null
	@return null
	*/
	void MoveWorm(){
		if (Worm != nullptr){
			if (Worm->getTrajectoire() != nullptr){
				Worm->getTrajectoire()->UpdatePosition();
				Worm->setPosXY(Worm->getTrajectoire()->GetActualPosition()->getX(), Worm->getTrajectoire()->GetActualPosition()->getY());
				CPosition* temp = CPhysics::VerifyNextPosition(Worm->getTrajectoire(), Worm->getPosition());
				if (temp != nullptr)
				{
					if ((temp->getX() != (int)Worm->getTrajectoire()->getNextPos()->getX()) || (temp->getY() != (int)Worm->getTrajectoire()->getNextPos()->getY())){
						if (Worm->getWormState() == ChuteRight)
							Worm->setWormState(NoMotionRight);
						else
							Worm->setWormState(NoMotionLeft);

						delete Worm->getTrajectoire();
						Worm->setTrajectory(nullptr);
					}
					Worm->setPosXY(temp->getX(), temp->getY());
					delete temp;
				}
			}
		}
	}
	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event _Event){
		switch (_Event.type) {
			// -----------KEY DOWN-------------------
		case SDL_KEYDOWN:
			switch (_Event.key.keysym.sym){
				//JetPack monte...
			case SDLK_SPACE:
			case SDLK_UP:
				if (Worm != nullptr){
					//Si c'est la premiere montée
					if (!boGaz){
						if (Worm->getTrajectoire() == nullptr)
							Worm->setTrajectory(new CTrajectory(new CPosition(Worm->getPosition().x, Worm->getPosition().y), new C2DVector(Worm->getPosition().x, Worm->getPosition().y, 0., -60.), new C2DVector(Worm->getPosition().x, Worm->getPosition().y, CPhysics::GetWind()->getComposanteX(), (CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
						if (Worm->getTrajectoire() != nullptr){
							Worm->setTrajectory(new CTrajectory(new CPosition(Worm->getPosition().x, Worm->getPosition().y), new C2DVector(Worm->getPosition().x, Worm->getPosition().y, 0., -60.), new C2DVector(Worm->getPosition().x, Worm->getPosition().y, CPhysics::GetWind()->getComposanteX(), (CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
							Worm->getTrajectoire()->AddAcceleration(new C2DVector(Worm->getPosition().x, Worm->getPosition().y, 0.,-0.3));
							boGaz = true;
						}
					}
						if ((Worm->getWormState() == NoMotionLeft) || (Worm->getWormState() == JetpackLeftNoFly))
							Worm->setWormState(JetpackLeftFly);
						else if ((Worm->getWormState() == NoMotionRight) || (Worm->getWormState() == JetpackRightNoFly))
							Worm->setWormState(JetpackRightFly);
					
					if (boGaz){
						//Si il n'y a plus de gaz...
						if (m_pBarreGaz.h <= 0){
							boGaz = false;
							if (Worm->getTrajectoire() != nullptr){
								Vector = new C2DVector(Worm->getPosition().x, Worm->getPosition().y, Worm->getTrajectoire()->GetActualSpeed()->getComposanteX(), Worm->getTrajectoire()->GetActualSpeed()->getComposanteY());
								delete Worm->getTrajectoire();
								Worm->setTrajectory(new CTrajectory(new CPosition(Worm->getPosition().x, Worm->getPosition().y), Vector, new C2DVector(Worm->getPosition().x, Worm->getPosition().y, CPhysics::GetWind()->getComposanteX(), (CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
							}
							if ((Worm->getWormState() == NoMotionLeft) || (Worm->getWormState() == JetpackLeftFly))
								Worm->setWormState(ChuteLeft);

							else if ((Worm->getWormState() == NoMotionRight) || (Worm->getWormState() == JetpackRightFly))
								Worm->setWormState(ChuteRight);
						}
						else{
							m_pBarreGaz.h--;
						}
					}
				}


				break;
			case SDLK_LEFT:
				if (Worm != nullptr){
					if (!boGaz){
						if (Worm->getTrajectoire() != nullptr){
							Worm->setTrajectory(new CTrajectory(new CPosition(Worm->getPosition().x, Worm->getPosition().y), new C2DVector(Worm->getPosition().x, Worm->getPosition().y, 0., -60.), new C2DVector(Worm->getPosition().x, Worm->getPosition().y, CPhysics::GetWind()->getComposanteX(), (CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
							Worm->getTrajectoire()->AddAcceleration(new C2DVector(Worm->getPosition().x, Worm->getPosition().y, -0.2, -0.1));
							boGaz = true;
						}
						Worm->setWormState(JetpackLeftFly);
					}
					if (boGaz){
						if (m_pBarreGaz.h <= 0){
							boGaz = false;
							if (Worm->getTrajectoire() != nullptr){
								Vector = new C2DVector(Worm->getPosition().x, Worm->getPosition().y, Worm->getTrajectoire()->GetActualSpeed()->getComposanteX(), Worm->getTrajectoire()->GetActualSpeed()->getComposanteY());
								delete Worm->getTrajectoire();
								Worm->setTrajectory(new CTrajectory(new CPosition(Worm->getPosition().x, Worm->getPosition().y), Vector, new C2DVector(Worm->getPosition().x, Worm->getPosition().y, CPhysics::GetWind()->getComposanteX(), (CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
							}
							if ((Worm->getWormState() == NoMotionLeft) || (Worm->getWormState() == JetpackLeftFly))
								Worm->setWormState(ChuteLeft);
						}
						else{
							m_pBarreGaz.h--;
						}
					}
				}
				break;
			case SDLK_RIGHT:
				if (Worm != nullptr){
					if (!boGaz){
						if (Worm->getTrajectoire() != nullptr){
							Worm->setTrajectory(new CTrajectory(new CPosition(Worm->getPosition().x, Worm->getPosition().y), new C2DVector(Worm->getPosition().x, Worm->getPosition().y, 0., -60.), new C2DVector(Worm->getPosition().x, Worm->getPosition().y, CPhysics::GetWind()->getComposanteX(), (CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
							Worm->getTrajectoire()->AddAcceleration(new C2DVector(Worm->getPosition().x, Worm->getPosition().y, 0.2, -0.1));
							boGaz = true;
						}
						Worm->setWormState(JetpackRightFly);
					}
					if (boGaz){
						if (m_pBarreGaz.h <= 0){
							boGaz = false;
							if (Worm->getTrajectoire() != nullptr){
								Vector = new C2DVector(Worm->getPosition().x, Worm->getPosition().y, Worm->getTrajectoire()->GetActualSpeed()->getComposanteX(), Worm->getTrajectoire()->GetActualSpeed()->getComposanteY());
								delete Worm->getTrajectoire();
								Worm->setTrajectory(new CTrajectory(new CPosition(Worm->getPosition().x, Worm->getPosition().y), Vector, new C2DVector(Worm->getPosition().x, Worm->getPosition().y, CPhysics::GetWind()->getComposanteX(), (CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
							}
							if ((Worm->getWormState() == NoMotionRight) || (Worm->getWormState() == JetpackRightFly))
								Worm->setWormState(ChuteRight);
						}
						else{
							m_pBarreGaz.h--;
						}
					}
				}
				break;

			}
			break;


			// ------KEY UP ------------

		case SDL_KEYUP:
			switch (_Event.key.keysym.sym){
			case SDLK_SPACE:
			case(SDLK_UP):
				if (Worm->getTrajectoire() != nullptr){
					Vector = new C2DVector(Worm->getPosition().x, Worm->getPosition().y, Worm->getTrajectoire()->GetActualSpeed()->getComposanteX(), Worm->getTrajectoire()->GetActualSpeed()->getComposanteY());
					delete Worm->getTrajectoire();
					Worm->setTrajectory(new CTrajectory(new CPosition(Worm->getPosition().x, Worm->getPosition().y), Vector, new C2DVector(Worm->getPosition().x, Worm->getPosition().y, CPhysics::GetWind()->getComposanteX(), (CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
					Vector = nullptr;
				}
				boGaz = false;
				if ((Worm->getWormState() == NoMotionLeft) || (Worm->getWormState() == JetpackLeftFly))
					Worm->setWormState(JetpackLeftNoFly);
				else if ((Worm->getWormState() == NoMotionRight) || (Worm->getWormState() == JetpackRightFly))
					Worm->setWormState(JetpackRightNoFly);
				break;

			case(SDLK_LEFT):
				if (Worm->getTrajectoire() != nullptr){
					Vector = new C2DVector(Worm->getPosition().x, Worm->getPosition().y, Worm->getTrajectoire()->GetActualSpeed()->getComposanteX(), Worm->getTrajectoire()->GetActualSpeed()->getComposanteY());
					delete Worm->getTrajectoire();
					Worm->setTrajectory(new CTrajectory(new CPosition(Worm->getPosition().x, Worm->getPosition().y), Vector, new C2DVector(Worm->getPosition().x, Worm->getPosition().y, CPhysics::GetWind()->getComposanteX(), (CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
					Vector = nullptr;
				}
				boGaz = false;
				Worm->setWormState(JetpackLeftNoFly);
				break;

			case(SDLK_RIGHT):
				if (Worm->getTrajectoire() != nullptr){
					Vector = new C2DVector(Worm->getPosition().x, Worm->getPosition().y, Worm->getTrajectoire()->GetActualSpeed()->getComposanteX(), Worm->getTrajectoire()->GetActualSpeed()->getComposanteY());
					delete Worm->getTrajectoire();
					Worm->setTrajectory(new CTrajectory(new CPosition(Worm->getPosition().x, Worm->getPosition().y), Vector, new C2DVector(Worm->getPosition().x, Worm->getPosition().y, CPhysics::GetWind()->getComposanteX(), (CPhysics::GetWind()->getComposanteY() + CPhysics::GetGravity()))));
					Vector = nullptr;
				}
				boGaz = false;
				Worm->setWormState(JetpackRightNoFly);
				break;
			}
			break;

		}
	}
	//Accesseurs:
	void setInUse(bool _bo){
		m_boInUse = _bo;
	}
	bool isInUse(){
		return m_boInUse;
	}
	bool isLanded(){
		return (!m_pBarreGaz.h);
	}
	
	void reset(){
		m_pBarreGaz.h = 50;
	}


};

#endif
