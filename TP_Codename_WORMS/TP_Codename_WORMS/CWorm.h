//
//  CWorm.h
//
//  Created by Jessy Desjardins on 2014-11-11.
//  Copyright (c) 2014 Jessy Desjardins. All rights reserved.
//
#define PI_SUR_DEUX 1.5707963268
#define PI_SUR_TROIS 1.0471975512
#define PI_SUR_QUATRE 0.7853981634
#define PI_SUR_SIX 0.7853981634
#define ANGLEMAX 1.2044640138

#ifndef TP_Codename_WORMS_CWorm_h
#define TP_Codename_WORMS_CWorm_h

// Un worm possde dŽjˆ l'Žtat en chute, immobile, ou en dŽplacement, qu'il tient d'entity

enum WormState { NoMotionLeft, NoMotionRight, MotionLeft, MotionRight, JumpLeft, JumpRight, UsingBazzLeft, UsingBazzRight, Damaged, Largage, SlideLeft, SlideRight, ChuteLeft, ChuteRight, Dead, GrenadeLaunchLeft, GrenadeLaunchRight, KnifeLeft, KnifeRight, JetpackLeftFly, JetpackLeftNoFly, JetpackRightFly, JetpackRightNoFly };


/*!
@CWorm
@Classe permettant la création de la classe des Worm
*/
class CWorm : public CEntity{
private:
	string m_strName;
	int m_iLife; //Donnée représentant la vie actuelle du worm
	CSprite* m_pSprite;//Sprite du worm
	CLabel* m_lblNom;
	SDL_Rect m_BarredeVie;
	SDL_Color* m_TeamColor;
	bool m_boDrawRect;
	double 	m_dblYinitial;
	bool m_boKnifeDone;
	bool m_boPlaying;
public:

	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	@param _iLifeMax : la vie maximum du worm
	@param _pSprite : le sprite du worm
	@param _RectPos : la position du sprite
	@Classe héritant de CEntity
	*/
	CWorm(string _Name, SDL_Texture* _Texture, CSprite* _pSprite, CFont* _Font, SDL_Rect _RectPos, SDL_Color* _Color, CExplosion* _Explosion) :CEntity(_RectPos, _Texture, _Explosion){
		m_strName = _Name;
		m_Angle = 0;
		m_TeamColor = _Color;
		m_pSprite = _pSprite;
		m_pSprite->setSpritePos(_RectPos.x, _RectPos.y);
		m_iLife = 100;
		m_BarredeVie.h = 5;
		m_BarredeVie.w = 50;
		m_BarredeVie.x = _RectPos.x;
		m_BarredeVie.y = _RectPos.y;
		m_lblNom = new CLabel("", m_strName.c_str(), _Font, SDL_Rect{ _RectPos.x, _RectPos.y - 18, 50, 10 });
		m_EntityState = Largage;
		m_boDrawRect = false;
		m_dblYinitial = 0;
		m_boKnifeDone = false;
		m_boPlaying = false;
		m_pSprite->Start();
		

	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CWorm(){
		if (m_pSprite != nullptr){
			delete m_pSprite;
			m_pSprite = nullptr;
		}
		if (m_lblNom != nullptr){
			delete m_lblNom;
			m_lblNom = nullptr;
		}
	}

	/*!
	 @Méthode:
	 @ReactToExplosion
	 @Permet de calculer les dommages subit par l'explosion
	 */
	void ReactToExplosion(CExplosion * _Explosion){
		RecieveDamage(_Explosion, false);
		if (m_EntityState == NoMotionLeft)
			m_EntityState = ChuteLeft;
		else
			m_EntityState = ChuteRight;
	}

	/*!
	 @method HandleEvent
	 @param _Evant : Un SDL_Event pour traiter les evenement
	 @return null
	 */
	void HandleEvent(SDL_Event _Event){
		if (!((m_EntityState == JumpLeft) || (m_EntityState == JumpRight) || (m_EntityState == Largage) || (m_EntityState == ChuteLeft) || (m_EntityState == ChuteRight))) {
			switch (_Event.type) {
			case SDL_KEYDOWN:
				switch (_Event.key.keysym.sym){
				case SDLK_g:
					m_boDrawRect = false;
					break;
				case SDLK_f:
					m_boDrawRect = true;
					break;
				case SDLK_1:
					if ((m_EntityState == NoMotionRight) || (m_EntityState == MotionRight)){
						m_EntityState = UsingBazzRight;
					}
					else{
						m_EntityState = UsingBazzLeft;
					}
					break;
				case SDLK_2:
					if ((m_EntityState == NoMotionRight) || (m_EntityState == MotionRight)){
						m_EntityState = GrenadeLaunchRight;
					}
					else{
						m_EntityState = GrenadeLaunchLeft;
					}
					break;
				case SDLK_3:
					if ((m_EntityState == NoMotionRight) || (m_EntityState == MotionRight)){
						m_EntityState = KnifeRight;
					}
					else{
						m_EntityState = KnifeLeft;
					}
					break;
				case SDLK_4:
					if ((m_EntityState == NoMotionRight) || (m_EntityState == MotionRight)){
						m_EntityState = JetpackRightNoFly;
					}
					else{
						m_EntityState = JetpackLeftNoFly;
					}
					break;
				case SDLK_UP:
				case SDLK_w:
					break;
				case SDLK_LEFT:
				case SDLK_a:
					m_EntityState = MotionLeft;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					m_EntityState = MotionRight;
					break;
				case SDLK_SPACE:
					if ((m_EntityState == NoMotionLeft) || (m_EntityState == MotionLeft))
						m_EntityState = JumpLeft;
					else if ((m_EntityState == NoMotionRight) || (m_EntityState == MotionRight))
						m_EntityState = JumpRight;
					break;
				}
				break;
			case SDL_KEYUP:
				if (m_EntityState == MotionLeft)
					m_EntityState = NoMotionLeft;
				else if (m_EntityState == MotionRight)
					m_EntityState = NoMotionRight;
				break;
			}
		}
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture du Sprite
	@return null
	*/
	void Draw(SDL_Renderer * _Renderer){
		if ((m_EntityState != NoMotionLeft) && (m_EntityState != NoMotionRight))
			Move(_Renderer);
		if (isOutOfBounds()){
			m_EntityState = Dead;
			m_iLife = 0;
		}
		if (((m_EntityState == JumpLeft) || (m_EntityState == JumpRight) || (m_EntityState == KnifeLeft) || (m_EntityState == KnifeRight)) && (m_pSprite->getNbrOfLoop() != 2)){
			m_pSprite->setNbLoop(2);
		}
		else{
			m_pSprite->setNbLoop(-1);
			m_boKnifeDone = false;
		}

		if (m_iLife > 1){
			m_lblNom->Draw(_Renderer);
			SDL_SetRenderDrawColor(_Renderer, m_TeamColor->r, m_TeamColor->g, m_TeamColor->b, 200);
			SDL_SetRenderDrawBlendMode(_Renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(_Renderer, &m_BarredeVie);
			switch (m_EntityState) {
			case KnifeLeft:
					if (m_pSprite->getCurrentAnimation() != 13)
						m_pSprite->setCurrentAnimation(13);
					m_pSprite->Render(_Renderer);
					if (m_pSprite->AnimationIsOver()){
						m_boKnifeDone = true;
						setPosXY(m_RectPosition.x, m_RectPosition.y);
					}
					break;
			case KnifeRight:
					if (m_pSprite->getCurrentAnimation() != 12)
						m_pSprite->setCurrentAnimation(12);
					m_pSprite->Render(_Renderer);
					if (m_pSprite->AnimationIsOver()){
						m_boKnifeDone = true;
						setPosXY(m_RectPosition.x, m_RectPosition.y);
					}
					break;
			case ChuteLeft:
			case SlideLeft:
				if (m_pSprite->getCurrentAnimation() != 15)
					m_pSprite->setCurrentAnimation(15);
				m_pSprite->Render(0, 4, _Renderer);
				break;
			case ChuteRight:
			case SlideRight:
				if (m_pSprite->getCurrentAnimation() != 14)
					m_pSprite->setCurrentAnimation(14);
				m_pSprite->Render(0, 4, _Renderer);
				break;
			case JumpLeft:
				if (m_pSprite->getCurrentAnimation() != 5)
					m_pSprite->setCurrentAnimation(5);
				m_pSprite->Render(_Renderer);
				break;
			case JumpRight:
				if (m_pSprite->getCurrentAnimation() != 4)
					m_pSprite->setCurrentAnimation(4);
				m_pSprite->Render(_Renderer);
				break;
			case NoMotionLeft:
			case UsingBazzLeft:
			case GrenadeLaunchLeft:
				if (m_pSprite->getCurrentAnimation() != 1)
					m_pSprite->setCurrentAnimation(1);
				m_pSprite->Render(_Renderer, 0);
				break;
			case NoMotionRight:
			case UsingBazzRight:
			case GrenadeLaunchRight:
				if (m_pSprite->getCurrentAnimation() != 0)
					m_pSprite->setCurrentAnimation(0);
				m_pSprite->Render(_Renderer, 0);
				break;
			case Largage:
				if (m_pSprite->getCurrentAnimation() != 10)
					m_pSprite->setCurrentAnimation(10);
				m_pSprite->Render(1, 4, _Renderer);
				break;
			case MotionLeft:
				if (m_pSprite->getCurrentAnimation() != 3)
					m_pSprite->setCurrentAnimation(3);
				m_pSprite->Render(0, 4, _Renderer);
				break;
			case MotionRight:
				if (m_pSprite->getCurrentAnimation() != 2)
					m_pSprite->setCurrentAnimation(2);
				m_pSprite->Render(0, 4, _Renderer);
				break;
			case JetpackRightFly:
				if (m_pSprite->getCurrentAnimation() != 10)
					m_pSprite->setCurrentAnimation(10);
				m_pSprite->Render(1, 4, _Renderer);
				break;
			case JetpackRightNoFly:
				if (m_pSprite->getCurrentAnimation() != 10)
					m_pSprite->setCurrentAnimation(10);
				m_pSprite->Render(0, 1, _Renderer);
				break;
			case JetpackLeftFly:
				if (m_pSprite->getCurrentAnimation() != 11)
					m_pSprite->setCurrentAnimation(11);
				m_pSprite->Render(1, 4, _Renderer);
				break;
			case JetpackLeftNoFly:
				if (m_pSprite->getCurrentAnimation() != 11)
					m_pSprite->setCurrentAnimation(11);
				m_pSprite->Render(0, 1, _Renderer);
				break;
			}
			if (m_boDrawRect)
				SDL_RenderDrawRect(_Renderer, &m_RectPosition);
		}
		else if (m_EntityState != Dead){
			if (m_pSprite->getCurrentAnimation() != 16){
				m_pSprite->setCurrentAnimation(16);
				m_pSprite->setNbLoop(0);
			}
			if (m_pSprite->AnimationIsOver()){
				setPosXY(m_RectPosition.x, m_RectPosition.y);
				m_pExplosion->setPositionXY(m_RectPosition.x + 14, m_RectPosition.y + 8);
				m_pExplosion->startExplosion();
				m_pExplosion->ExplodeMap(_Renderer);
				m_pExplosion->Draw(_Renderer);
				if (m_pExplosion->IsDone()){
					m_EntityState = Dead;
				}
			}
			else{
				m_pSprite->Render(_Renderer);
			}
		}

	}
	//			Methode: RecieveDamage()
	//			PARAM :
	//				_ExplosionPos : Position du centre de l'explosion.
	//				_Radius : Rayon(puissance de l'explosion.')
	//				_Knife : Booléen qui détermine si le dégât est causé par l'arme Couteau.

	void RecieveDamage(CExplosion * _Explosion, bool _Knife){
		if (_Knife && ((m_EntityState != KnifeRight) || (m_EntityState != KnifeLeft)) && !m_boPlaying){
			m_iLife -= 30;
		}
		else if (_Explosion != nullptr){

			double Distance = _Explosion->getPosition()->ClaculateDistance((m_RectPosition.x + (m_RectPosition.w / 2)), (m_RectPosition.y + (m_RectPosition.h / 2)));
			if ((Distance <= _Explosion->getRadius())){
				if (Distance > 20)
					m_iLife -= 100 - 100 * (Distance / _Explosion->getRadius());
				else m_iLife = 0;
			}
		}
		if (m_iLife > 1)
			m_BarredeVie.w = m_iLife / 2;
		else{
			m_BarredeVie.w = 0;
			m_iLife = 0;
		}
	}

	/*!
	@Accesseurs:
	*/

	void SetLife(int _iLifeActuelle){
		if (_iLifeActuelle < 1){
			m_iLife = 0;
		}
		else{
			m_iLife = _iLifeActuelle;
			m_BarredeVie.w = _iLifeActuelle / 2;
		}
	}

	int getLife(){ return m_iLife; }

	void setName(string _Name){ m_strName = _Name; }

	string getName(){ return m_strName; }


	void Move(SDL_Renderer* _renderer){
		double ftemp = 0;
		double dbl = 0;
		int i = 0;
		unsigned int uiTempsDeChute = 0;
		SDL_Rect RectCollision;
		SDL_Rect RectTemp;
		SDL_Rect rect;
		if (!(m_EntityState == Largage || m_EntityState == JetpackLeftNoFly || m_EntityState == JetpackRightNoFly || m_EntityState == JetpackLeftFly || m_EntityState == JetpackRightFly || m_EntityState == ChuteLeft || m_EntityState == ChuteRight)){
			RectCollision = { m_RectPosition.x, m_RectPosition.y + m_RectPosition.h / 2, m_RectPosition.w, m_RectPosition.h };
			ftemp = CPhysics::EvaluateSlope(RectCollision);
			SDL_RenderDrawRect(_renderer, &RectCollision);
			dbl = (int)RadToDeg(ftemp);
		}
		if (dbl == NOANGLE){
			if (m_EntityState == MotionLeft){
				m_EntityState = ChuteLeft;
				setPosXY(m_RectPosition.x - 2, m_RectPosition.y);
			}
			else if (m_EntityState == MotionRight){
				m_EntityState = ChuteRight;
				setPosXY(m_RectPosition.x + 2, m_RectPosition.y);
			}

		}
		else if (dbl < -60)
			m_EntityState = SlideLeft;
		else if (dbl > 60){
			m_EntityState = SlideRight;
		}

		switch (m_EntityState) {
		case SlideLeft:
			if (m_Trajectoire == nullptr){
				m_Trajectoire = new CTrajectory(new CPosition(m_RectPosition.x, m_RectPosition.y), new C2DVector(m_RectPosition.x, m_RectPosition.y, -1500., 2.), new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.0, 10 * CPhysics::GetGravity()));
			}
			m_Trajectoire->UpdatePosition();
			if (VerifySliding(CPhysics::EvaluateSlope({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h / 2, m_RectPosition.w, m_RectPosition.h }))){
				CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
				if (temp != nullptr){
					if (((int)temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) && ((int)temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
						m_EntityState = NoMotionLeft;
						delete m_Trajectoire;
						m_Trajectoire = nullptr;
					}
					else{
						UpdateSlidePosition();
						setPosXY(temp->getX(), temp->getY());
					}
				}

				delete temp;
			}
			else{
				m_EntityState = ChuteLeft;
				delete m_Trajectoire;
				m_Trajectoire = nullptr;
			}
			break;
		case SlideRight:
			if (m_Trajectoire == nullptr){
				m_Trajectoire = new CTrajectory(new CPosition(m_RectPosition.x, m_RectPosition.y), new C2DVector(m_RectPosition.x, m_RectPosition.y, 1500., 2.), new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.0, 10 * CPhysics::GetGravity()));
			}
			m_Trajectoire->UpdatePosition();
			if (VerifySliding(CPhysics::EvaluateSlope({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h / 2, m_RectPosition.w, m_RectPosition.h }))){
				CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
				if (temp != nullptr){
					if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) && (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
						m_EntityState = NoMotionRight;
						delete m_Trajectoire;
						m_Trajectoire = nullptr;
					}
					else{
						UpdateSlidePosition();
						setPosXY(temp->getX(), temp->getY());
					}
				}
				delete temp;
			}
			else{
				m_EntityState = ChuteRight;
				delete m_Trajectoire;
				m_Trajectoire = nullptr;
			}
			break;
		case JumpLeft:

			if (m_Trajectoire == nullptr){
				m_Trajectoire = new CTrajectory(new CPosition(m_RectPosition.x, m_RectPosition.y),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, -15.f, -85.f),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.f, CPhysics::GetGravity()));
				m_dblYinitial = m_Trajectoire->GetActualPosition()->getY();
			}
			else
			{

				m_Trajectoire->UpdatePosition();
				if (m_dblYinitial < m_Trajectoire->GetActualPosition()->getY())
				{
					m_EntityState = ChuteLeft;
					break;
				}
				else
				{
					CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
					if (temp != nullptr)
					{

						if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
							m_EntityState = ChuteLeft;
							delete m_Trajectoire;
							m_Trajectoire = nullptr;
							i = 5;
						}
						setPosXY(temp->getX() + i, temp->getY());
						delete temp;
					}
					else{
						setPosXY(m_Trajectoire->GetActualPosition()->getX(), m_Trajectoire->GetActualPosition()->getY());
					}
				}
			}
			break;

		case JumpRight:
			if (m_Trajectoire == nullptr){
				m_Trajectoire = new CTrajectory(new CPosition(m_RectPosition.x, m_RectPosition.y),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, 15.f, -85.f),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.f, CPhysics::GetGravity()));
				m_dblYinitial = m_Trajectoire->GetActualPosition()->getY();
			}
			else{
				m_Trajectoire->UpdatePosition();
				if (m_dblYinitial < m_Trajectoire->GetActualPosition()->getY())
				{
					m_EntityState = ChuteRight;
					break;
				}
				else{
					CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
					if (temp != nullptr)
					{
						if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
							m_EntityState = ChuteRight;
							delete m_Trajectoire;
							m_Trajectoire = nullptr;
							i = 5;
						}
						setPosXY(temp->getX() - i, temp->getY());
						delete temp;
					}
					else{
						setPosXY(m_Trajectoire->GetActualPosition()->getX(), m_Trajectoire->GetActualPosition()->getY());
					}
					if ((m_Trajectoire != nullptr) && (m_Trajectoire->GetActualSpeed()->getComposanteX() < 1)){
						m_EntityState = ChuteRight;
						delete m_Trajectoire;
						m_Trajectoire = nullptr;
					}
				}
			}
			break;
		case MotionRight:

			//SI ON MONTE
			if (dbl <= 0){
				RectCollision = { m_RectPosition.x + m_RectPosition.w - 2, m_RectPosition.y + m_RectPosition.h / 4 * 3, m_RectPosition.w / 2, m_RectPosition.h / 2 - 5 };
				ftemp = RadToDeg(CPhysics::EvaluateSlope(RectCollision));

				SDL_RenderDrawRect(_renderer, &RectCollision);
				//Si l'angle maximum est atteint alors on tomble forcément bloqué.
				if (ftemp == NOANGLE || ftemp == 0){
					CPhysics::Move(&m_RectPosition, RIGHT);
					setPosXY(m_RectPosition.x, m_RectPosition.y);
					if (!CPhysics::verifyGroundCollision({ m_RectPosition.x + 1, m_RectPosition.y + m_RectPosition.h + 1, m_RectPosition.w, 1 }))
						m_EntityState = ChuteRight;
				}
				else if (ftemp < -60){
					break;
				}
				else if (ftemp >= -60){
					if (CPhysics::Move(&m_RectPosition, RIGHT) == MOVING){
						if (!CPhysics::verifyGroundCollision({ m_RectPosition.x + 1, m_RectPosition.y + m_RectPosition.h + 1, m_RectPosition.w, 1 }))
							m_EntityState = ChuteRight;
						else
							CPhysics::HandleGroundCollision(&m_RectPosition, DOWN_UPRIGHT);
						setPosXY(m_RectPosition.x, m_RectPosition.y);
					}
				}
			}
			// Si on descends
			else if (dbl > 0){
				RectCollision = { m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w + ((3 / 4)*m_RectPosition.w) + 5, m_RectPosition.h / 2 };
				ftemp = RadToDeg(CPhysics::EvaluateSlope(RectCollision));
				SDL_RenderDrawRect(_renderer, &RectCollision);

				if (ftemp == NOANGLE || ftemp == 0){
					CPhysics::Move(&m_RectPosition, RIGHT);
					setPosXY(m_RectPosition.x, m_RectPosition.y);
					if (!CPhysics::verifyGroundCollision({ m_RectPosition.x + 1, m_RectPosition.y + m_RectPosition.h + 1, m_RectPosition.w, 1 }))
						m_EntityState = ChuteRight;
				}

				else if (ftemp > 60 && ftemp != (NOANGLE)){
					m_EntityState = SlideRight;
					setPosXY(m_RectPosition.x + 5, m_RectPosition.y);
				}
				else if (ftemp < 60){
					if (CPhysics::Move(&m_RectPosition, RIGHT) == MOVING){
						CPhysics::HandleGroundCollision(&m_RectPosition, CEILINGRIGHT);
						setPosXY(m_RectPosition.x, m_RectPosition.y);
					}
				}
			}
			break;
		case MotionLeft:

			//Si on Monte
			if (dbl >= 0){
				RectCollision = { m_RectPosition.x - m_RectPosition.w / 2, m_RectPosition.y + m_RectPosition.h / 4 * 3, m_RectPosition.w / 2, m_RectPosition.h / 2 - 5 };
				ftemp = RadToDeg(CPhysics::EvaluateSlope(RectCollision));
				SDL_RenderDrawRect(_renderer, &RectCollision);
				if (ftemp == NOANGLE || ftemp == 0){
					CPhysics::Move(&m_RectPosition, LEFT);
					setPosXY(m_RectPosition.x, m_RectPosition.y);
					if (!CPhysics::verifyGroundCollision({ m_RectPosition.x - 1, m_RectPosition.y + m_RectPosition.h + 1, m_RectPosition.w, 1 }))
						m_EntityState = ChuteLeft;
				}
				else if (ftemp > 60){
					break;
				}
				else if (ftemp <= 60){
					if (CPhysics::Move(&m_RectPosition, LEFT) == MOVING){
						if (!CPhysics::verifyGroundCollision({ m_RectPosition.x - 1, m_RectPosition.y + m_RectPosition.h + 1, m_RectPosition.w, 1 }))
							m_EntityState = ChuteLeft;
						else
							CPhysics::HandleGroundCollision(&m_RectPosition, DOWN_UPLEFT);
						setPosXY(m_RectPosition.x, m_RectPosition.y);
					}
				}
			}

			//Si on Descends
			else if (dbl < 0){
				RectCollision = { m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w + ((3 / 4)*m_RectPosition.w), m_RectPosition.h / 2 };
				ftemp = RadToDeg(CPhysics::EvaluateSlope(RectCollision));
				SDL_RenderDrawRect(_renderer, &RectCollision);
				//Si l'angle maximum est atteint alors on tomble forcément en slide.
				if (ftemp < -60){
					m_EntityState = SlideLeft;
					break;
				}
				else if (ftemp > -60){
					if (CPhysics::Move(&m_RectPosition, LEFT) == MOVING){
						CPhysics::HandleGroundCollision(&m_RectPosition, UP_DOWNLEFT);
						setPosXY(m_RectPosition.x, m_RectPosition.y);
					}
				}
			}
			break;
		case ChuteRight:
			RectTemp = { m_RectPosition.x , m_RectPosition.y + m_RectPosition.h + 1, m_RectPosition.w, 1 };
			if (!CPhysics::verifyGroundCollision(RectTemp)){
				if (m_Trajectoire == nullptr){
					m_Trajectoire = new CTrajectory(new CPosition(m_RectPosition.x, m_RectPosition.y),
						new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.f, 0.f),
						new C2DVector(m_RectPosition.x, m_RectPosition.y, CPhysics::GetWind()->getComposanteX() / 4, CPhysics::GetGravity() + CPhysics::GetWind()->getComposanteY() / 4));
				}
				else {
					m_Trajectoire->UpdatePosition();
					CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
					if (temp != nullptr)
					{
						if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
							m_EntityState = NoMotionRight;
							uiTempsDeChute = m_Trajectoire->getSpeedMagnitude();
							if (uiTempsDeChute >= 50)
								SetLife(m_iLife - (uiTempsDeChute / 10));
							delete m_Trajectoire;
							m_Trajectoire = nullptr;
						}
						setPosXY(temp->getX(), temp->getY());
						delete temp;
					}
					else{
						setPosXY(m_Trajectoire->GetActualPosition()->getX(), m_Trajectoire->GetActualPosition()->getY());
					}
				}
			}
			else{
				if (m_Trajectoire != nullptr)
				{
					delete m_Trajectoire;
					m_Trajectoire = nullptr;
				}
				m_EntityState = NoMotionRight;
			}
			break;
		case ChuteLeft:
			RectTemp = { m_RectPosition.x, m_RectPosition.y + m_RectPosition.h + 1, m_RectPosition.w, 1 };
			if (!CPhysics::verifyGroundCollision(RectTemp)){
				if (m_Trajectoire == nullptr){
					m_Trajectoire = new CTrajectory(new CPosition(m_RectPosition.x, m_RectPosition.y),
						new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.f, 0.f),
						new C2DVector(m_RectPosition.x, m_RectPosition.y, CPhysics::GetWind()->getComposanteX() / 4, CPhysics::GetGravity() + CPhysics::GetWind()->getComposanteY() / 4));
				}
				else {
					m_Trajectoire->UpdatePosition();
					CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
					if (temp != nullptr)
					{
						if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
							m_EntityState = NoMotionLeft;
							uiTempsDeChute = m_Trajectoire->getSpeedMagnitude();
							if (uiTempsDeChute >= 50)
								SetLife(m_iLife - (uiTempsDeChute / 10));
							delete m_Trajectoire;
							m_Trajectoire = nullptr;
						}
						setPosXY(temp->getX(), temp->getY());
						delete temp;
					}
					else{
						setPosXY(m_Trajectoire->GetActualPosition()->getX(), m_Trajectoire->GetActualPosition()->getY());
					}
				}
			}
			else{
				if (m_Trajectoire != nullptr){
					delete m_Trajectoire;
					m_Trajectoire = nullptr;
				}
				m_EntityState = NoMotionLeft;
			}
			break;
		case Largage:
			m_Trajectoire->UpdatePosition();
			CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
			if (temp != nullptr)
			{
				if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
					if (VerifySliding(CPhysics::EvaluateSlope({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, 50 }))){
						UpdateSlidePosition();
					}
					else{
						m_EntityState = NoMotionRight;
						delete m_Trajectoire;
						m_Trajectoire = nullptr;
					}
				}
				setPosXY(temp->getX(), temp->getY());
				delete temp;
			}
			else{
				setPosXY(m_Trajectoire->GetActualPosition()->getX(), m_Trajectoire->GetActualPosition()->getY());
			}
			break;
		}
	}

	void setPosXY(int _X, int _Y){
		m_RectPosition.y = _Y;
		m_RectPosition.x = _X;
		m_pSprite->setSpritePos(m_RectPosition.x, m_RectPosition.y);
		m_lblNom->setPos(m_RectPosition.x, m_RectPosition.y - 18);
		m_BarredeVie.x = m_RectPosition.x;
		m_BarredeVie.y = m_RectPosition.y;
	}

	int getWormState(){
		return m_EntityState;
	}
	void setWormState(int _EntityState){
		m_EntityState = _EntityState;
	}
	
	bool KnifeDone(){
		return m_boKnifeDone;
	}
	
	bool isPlaying(){
		return m_boPlaying;
	}
	void setPlaystate(bool _boPlaying){
		m_boPlaying = _boPlaying;
	}
};
#endif
