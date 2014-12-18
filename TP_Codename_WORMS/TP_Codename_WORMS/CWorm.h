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
enum WormState { NoMotionLeft, NoMotionRight, MotionLeft, MotionRight, JumpLeft, JumpRight, UsingBazzLeft, UsingBazzRight, Damaged, Largage, SlideLeft, SlideRight, ChuteLeft, ChuteRight, Dead };

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
	void ReactToExplosion(int _iX, int _iY, int _Rayon){

	}

	/*!
	 @method HandleEvent
	 @param _Evant : Un SDL_Event pour traiter les evenement
	 @return null
	 */
	void HandleEvent(SDL_Event _Event){
		if ((m_EntityState != JumpLeft) && (m_EntityState != JumpRight) && (m_EntityState != Largage)) {
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
		if (((m_EntityState == JumpLeft) || (m_EntityState == JumpRight)) && (m_pSprite->getNbrOfLoop() != 2)){
			m_pSprite->setNbLoop(2);
		}
		else{
			m_pSprite->setNbLoop(-1);
		}

		if (m_iLife){
			m_lblNom->Draw(_Renderer);
			SDL_SetRenderDrawColor(_Renderer, m_TeamColor->r, m_TeamColor->g, m_TeamColor->b, 200);
			SDL_SetRenderDrawBlendMode(_Renderer, SDL_BLENDMODE_BLEND);
			SDL_RenderFillRect(_Renderer, &m_BarredeVie);
			switch (m_EntityState) {
			case ChuteLeft:
				if (m_pSprite->getCurrentAnimation() != 15)
					m_pSprite->setCurrentAnimation(15);
				m_pSprite->Render(0, 4, _Renderer);
				break;
			case ChuteRight:
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
				if (m_pSprite->getCurrentAnimation() != 1)
					m_pSprite->setCurrentAnimation(1);
				m_pSprite->Render(_Renderer, 0);
				break;
			case NoMotionRight:
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
		if (_Knife){
			m_iLife -= 30;
		}
		else if (_Explosion != nullptr){

			float Distance = _Explosion->getPosition()->ClaculateDistance((m_RectPosition.x + (m_RectPosition.w / 2)), (m_RectPosition.y + (m_RectPosition.h / 2)));
			if (Distance <= _Explosion->getRadius()){
				m_iLife -= 110 - 100 * (Distance / _Explosion->getRadius());
			}
		}
		m_BarredeVie.w = m_iLife / 2;
	}

	/*!
	@Accesseurs:
	*/

	void SetLife(int _iLifeActuelle){
		m_iLife = _iLifeActuelle;
		m_BarredeVie.w = _iLifeActuelle / 2;
	}

	int getLife(){ return m_iLife; }

	void setName(string _Name){ m_strName = _Name; }

	string getName(){ return m_strName; }


	void Move(SDL_Renderer* _renderer){
		float ftemp = 0;
		double dbl = 0;
		SDL_Rect RectCollision;
		if (m_EntityState != Largage){
			RectCollision = { m_RectPosition.x, m_RectPosition.y + m_RectPosition.h / 2, m_RectPosition.w, m_RectPosition.h };
			ftemp = CPhysics::EvaluateSlope(RectCollision);
			dbl = RadToDeg(ftemp);
		}

		switch (m_EntityState) {
		case JumpLeft:
			if (m_Trajectoire == nullptr){
				m_Trajectoire = new CTrajectory(new CPosition(m_RectPosition.x, m_RectPosition.y),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, -15.f, -85.f),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.f, CPhysics::GetGravity()));
			}
			else{
				m_Trajectoire->UpdatePosition();

				CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
				if (temp != nullptr)
				{
					if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
						m_EntityState = NoMotionLeft;
						delete m_Trajectoire;
						m_Trajectoire = nullptr;
					}
					setPosXY(temp->getX(), temp->getY());
					delete temp;
				}
				else{
					setPosXY(m_Trajectoire->GetActualPosition()->getX(), m_Trajectoire->GetActualPosition()->getY());
				}
				if ((m_Trajectoire != nullptr) && (m_Trajectoire->GetActualSpeed()->getComposanteX() > -1)){
					m_EntityState = ChuteLeft;
					delete m_Trajectoire;
					m_Trajectoire = nullptr;
				}
			}
			break;
		case JumpRight:
			if (m_Trajectoire == nullptr){
				m_Trajectoire = new CTrajectory(new CPosition(m_RectPosition.x, m_RectPosition.y),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, 15.f, -85.f),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.f, CPhysics::GetGravity()));
			}
			else{
				m_Trajectoire->UpdatePosition();

				CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
				if (temp != nullptr)
				{
					if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
						m_EntityState = NoMotionRight;
						delete m_Trajectoire;
						m_Trajectoire = nullptr;
					}
					setPosXY(temp->getX(), temp->getY());
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
			break;
		case MotionRight:
			//SI ON MONTE
			if (dbl <= 0){
				RectCollision = { m_RectPosition.x + m_RectPosition.w, m_RectPosition.y + m_RectPosition.h / 4 * 3, m_RectPosition.w / 2, m_RectPosition.h / 2 };
				ftemp = RadToDeg(CPhysics::EvaluateSlope(RectCollision)); SDL_RenderDrawRect(_renderer, &RectCollision);
				//Si l'angle maximum est atteint alors on tomble forcément bloqué.
				if (ftemp < -60){
					break;
				}
				if (ftemp >= -60){
					if (CPhysics::Move(&m_RectPosition, RIGHT) == MOVING){
						CPhysics::HandleGroundCollision(&m_RectPosition, DOWN_UPRIGHT);
						setPosXY(m_RectPosition.x, m_RectPosition.y);
					}
				}
			}
			// Si on descends
			else if (dbl > 0){
				RectCollision = { m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w + ((3 / 4)*m_RectPosition.w), m_RectPosition.h / 2 };
				ftemp = RadToDeg(CPhysics::EvaluateSlope(RectCollision)); SDL_RenderDrawRect(_renderer, &RectCollision);
				if (ftemp > 60){
					m_EntityState = NoMotionRight;//slIDErIGHT
				}
				if (ftemp < 60){
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
				RectCollision = { m_RectPosition.x - m_RectPosition.w / 2, m_RectPosition.y + m_RectPosition.h / 4 * 3, m_RectPosition.w / 2, m_RectPosition.h / 2 };
				ftemp = RadToDeg(CPhysics::EvaluateSlope(RectCollision)); SDL_RenderDrawRect(_renderer, &RectCollision);
				if (ftemp > 60){
					break;
				}
				if (ftemp <= 60){
					if (CPhysics::Move(&m_RectPosition,LEFT) == MOVING){
						CPhysics::HandleGroundCollision(&m_RectPosition, DOWN_UPLEFT);
						setPosXY(m_RectPosition.x, m_RectPosition.y);
					}
				}
			}

			//Si on Descends
			else if (dbl < 0){
				RectCollision = { m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w + ((3 / 4)*m_RectPosition.w), m_RectPosition.h / 2 };
				ftemp = RadToDeg(CPhysics::EvaluateSlope(RectCollision)); SDL_RenderDrawRect(_renderer, &RectCollision);
				//Si l'angle maximum est atteint alors on tomble forcément bloqué.
				if (ftemp < -60){
					m_EntityState = NoMotionLeft;//SlideLeft;
				}
				if (ftemp > -60){
					if (CPhysics::Move(&m_RectPosition, LEFT) == MOVING){
						CPhysics::HandleGroundCollision(&m_RectPosition, UP_DOWNLEFT);
						setPosXY(m_RectPosition.x, m_RectPosition.y);
					}
				}
			}

			break;
		case ChuteRight:
			if (m_Trajectoire == nullptr){
				m_Trajectoire = new CTrajectory(new CPosition(m_RectPosition.x, m_RectPosition.y),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.f, 0.f),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, CPhysics::GetWind()->getComposanteX() / 4, CPhysics::GetGravity() + CPhysics::GetWind()->getComposanteY() / 4));
			}
			else {
				CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
				if (temp != nullptr)
				{
					if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
						m_EntityState = NoMotionRight;
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
			break;
		case ChuteLeft:
			if (m_Trajectoire == nullptr){
				m_Trajectoire = new CTrajectory(new CPosition(m_RectPosition.x, m_RectPosition.y),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, 0.f, 0.f),
					new C2DVector(m_RectPosition.x, m_RectPosition.y, CPhysics::GetWind()->getComposanteX() / 4, CPhysics::GetGravity() + CPhysics::GetWind()->getComposanteY() / 4));
			}
			else {
				CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
				if (temp != nullptr)
				{
					if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
						m_EntityState = NoMotionLeft;
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
			break;
		case Largage:
			m_Trajectoire->UpdatePosition();

			CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
			if (temp != nullptr)
			{
				if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
					m_EntityState = NoMotionRight;
					delete m_Trajectoire;
					m_Trajectoire = nullptr;
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
};
#endif
