//
//  CWorm.h
//
//  Created by Jessy Desjardins on 2014-11-11.
//  Copyright (c) 2014 Jessy Desjardins. All rights reserved.
//

#ifndef TP_Codename_WORMS_CWorm_h
#define TP_Codename_WORMS_CWorm_h

// Un worm possde dŽjˆ l'Žtat en chute, immobile, ou en dŽplacement, qu'il tient d'entity
enum WormState {NoMotionLeft, NoMotionRight, MotionLeft, MotionRight, JumpLeft, JumpRight, UtilisationOutil, Damaged, Largage};

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
public:

	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	 @param _iLifeMax : la vie maximum du worm
	 @param _pSprite : le sprite du worm
	 @param _RectPos : la position du sprite
	@Classe héritant de CEntity
	*/
	CWorm(string _Name, SDL_Texture* _Texture, CSprite* _pSprite,CFont* _Font,SDL_Rect _RectPos) :CEntity(_RectPos, _Texture){
		m_strName = _Name;
		m_pSprite = _pSprite;
		m_pSprite->setSpritePos(_RectPos.x, _RectPos.y);
		m_iLife = 100;
		m_BarredeVie.h = 10;
		m_BarredeVie.w = 50;
		m_BarredeVie.x = _RectPos.x;
		m_BarredeVie.y = _RectPos.y + 10;
		m_lblNom = new CLabel("", m_strName.c_str(), _Font, SDL_Rect{_RectPos.x,_RectPos.y + 20,50,10});
		m_EntityState = Largage;
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
		
		switch (_Event.type) {
			case SDL_KEYDOWN:
				switch (_Event.key.keysym.sym){
					case SDLK_UP:
					case SDLK_w:
							if ((m_EntityState == NoMotionLeft) || (m_EntityState == MotionLeft))
								m_EntityState = JumpLeft;
							else
								m_EntityState = JumpRight;
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
							//To do
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

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture du Sprite 
	@return null
	*/
	void Draw(SDL_Renderer * _Renderer){
		Move();
		switch (m_EntityState) {
			case NoMotionLeft:
				m_pSprite->setCurrentAnimation(1);
				m_pSprite->Render(_Renderer, 0);
    			break;
			case NoMotionRight:
				m_pSprite->setCurrentAnimation(0);
				m_pSprite->Render(_Renderer, 0);
				break;
			case Largage:
				m_pSprite->setCurrentAnimation(10);
				m_pSprite->Render(1, 4, _Renderer);
				break;
			case MotionLeft:
				m_pSprite->setCurrentAnimation(3);
				m_pSprite->Render(_Renderer);
				break;
			case MotionRight:
				m_pSprite->setCurrentAnimation(2);
				m_pSprite->Render(_Renderer);
				break;
		}
		
	}

	/*!
	@Accesseurs:
	*/

	void SetLife(int _iLifeActuelle){
		m_iLife = _iLifeActuelle;
	}

	int getLife(){ return m_iLife; }

	void setName(string _Name){ m_strName = _Name; }

	string getName(){ return m_strName; }

	void Move(){
		switch (m_EntityState) {
			case MotionRight:
				break;
			case MotionLeft:
				break;
			case Largage:
				m_Trajectoire->UpdatePosition();
				
				CPosition* temp = CPhysics::VerifyNextPosition(m_Trajectoire, m_RectPosition);
				if (temp != nullptr)
				{
					if ((temp->getX() != (int)m_Trajectoire->getNextPos()->getX()) || (temp->getY() != (int)m_Trajectoire->getNextPos()->getY()))
						m_EntityState = NoMotionRight;
					else
						m_EntityState = Largage;
					
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
	}
};

#endif
