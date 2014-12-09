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
#define ANGLEMAX 1.2217304764

#ifndef TP_Codename_WORMS_CWorm_h
#define TP_Codename_WORMS_CWorm_h

// Un worm possde dŽjˆ l'Žtat en chute, immobile, ou en dŽplacement, qu'il tient d'entity
enum WormState {NoMotionLeft, NoMotionRight, MotionLeft, MotionRight, JumpLeft, JumpRight, UsingBazzLeft, UsingBazzRight, Damaged, Largage, SlideLeft, SlideRight};

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
	C2DVector* m_Deplacement;
	SDL_Color* m_TeamColor;
public:

	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	 @param _iLifeMax : la vie maximum du worm
	 @param _pSprite : le sprite du worm
	 @param _RectPos : la position du sprite
	@Classe héritant de CEntity
	*/
	CWorm(string _Name, SDL_Texture* _Texture, CSprite* _pSprite,CFont* _Font,SDL_Rect _RectPos, SDL_Color* _Color) :CEntity(_RectPos, _Texture){
		m_strName = _Name;
		m_TeamColor = _Color;
		m_pSprite = _pSprite;
		m_pSprite->setSpritePos(_RectPos.x, _RectPos.y);
		m_iLife = 100;
		m_BarredeVie.h = 5;
		m_BarredeVie.w = 50;
		m_BarredeVie.x = _RectPos.x;
		m_BarredeVie.y = _RectPos.y;
		m_lblNom = new CLabel("", m_strName.c_str(), _Font, SDL_Rect{_RectPos.x,_RectPos.y - 18,50,10});
		m_EntityState = Largage;
		m_Deplacement = new C2DVector(m_RectPosition.x, m_RectPosition.y, 0,0);
		m_pSprite->Start();

	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CWorm(){
		delete m_pSprite;
	}
	
	/*!
	 @Méthode:
	 @ReactToExplosion
	 @Permet de calculer les dommages subit par l'explosion
	 */
	void ReactToExplosion(int _iX,int _iY,int _Rayon){
		
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
							else
								m_EntityState = JumpRight;
							break;
					}
					break;
				case SDL_KEYUP:
					if (m_EntityState == MotionLeft)
						m_EntityState = NoMotionLeft;
					else
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
		Move();
		m_lblNom->Draw(_Renderer);
		SDL_SetRenderDrawColor(_Renderer, m_TeamColor->r, m_TeamColor->g, m_TeamColor->b, 200);
		SDL_SetRenderDrawBlendMode(_Renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(_Renderer, &m_BarredeVie);
		switch (m_EntityState) {
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
				m_pSprite->Render(0,4,_Renderer);
				break;
			case MotionRight:
				if (m_pSprite->getCurrentAnimation() != 2)
					m_pSprite->setCurrentAnimation(2);
				m_pSprite->Render(0,4,_Renderer);
				break;
		}
		
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

	void Move(){
		float ftemp;
		switch (m_EntityState) {
			case JumpLeft:
				
				break;
			case JumpRight:
				
				break;
			case MotionRight:
				ftemp = CPhysics::EvaluateSlope(new SDL_Rect({m_RectPosition.x, m_RectPosition.y + (m_RectPosition.h / 2), 60, m_RectPosition.h}));
				if (ftemp >= -ANGLEMAX){
					CPhysics::Move(&m_RectPosition, RIGHT);
					CPhysics::VerifyGroundCollision(&m_RectPosition);
					setPosXY(m_RectPosition.x, m_RectPosition.y);
				}
				else if (ftemp >= ANGLEMAX)
					m_EntityState = SlideRight;
				break;
			case MotionLeft:
				ftemp = CPhysics::EvaluateSlope(new SDL_Rect({m_RectPosition.x - m_RectPosition.w, m_RectPosition.y + (m_RectPosition.h / 2), 60, m_RectPosition.h}));
				if (ftemp <= ANGLEMAX){
					CPhysics::Move(&m_RectPosition, LEFT);
					CPhysics::VerifyGroundCollision(&m_RectPosition);
					setPosXY(m_RectPosition.x, m_RectPosition.y);
				}
				else if (ftemp <= -ANGLEMAX)
					m_EntityState = SlideLeft;
				break;
			case Chute:
				if (m_Trajectoire->isStopped()){
					m_Trajectoire->setStratPos(m_RectPosition.x, m_RectPosition.y);
					m_Trajectoire->Restart();
				}
				else{
					m_Trajectoire->UpdatePosition();
					
					CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
					if (temp != nullptr)
					{
						if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY())){
							m_EntityState = NoMotionRight;
							m_Trajectoire->Stop();
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
						m_Trajectoire->Stop();
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
