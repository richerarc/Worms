//
//  CWorm.h
//
//  Created by Jessy Desjardins on 2014-11-11.
//  Copyright (c) 2014 Jessy Desjardins. All rights reserved.
//

#ifndef TP_Codename_WORMS_CWorm_h
#define TP_Codename_WORMS_CWorm_h

// Un worm possde dŽjˆ l'Žtat en chute, immobile, ou en dŽplacement, qu'il tient d'entity
enum WormState {MotionLeft = 101, MotionRight = 201, JumpLeft = 102, JumpRight = 202, UtilisationOutil = 103, Damaged = 104, Largage = 100, NoMotionLeft = 301, NoMotionRight = 302};

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
				if ((m_EntityState == NoMotionLeft) || (m_EntityState == MotionLeft))
					m_EntityState = JumpLeft;
				else
					m_EntityState = JumpRight;

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
				
    break;
				
			default:
    break;
		}
		if (m_EntityState == Immobile) {
			SDL_RenderCopy(_Renderer, m_pTexture, NULL, &m_RectPosition);
		}
		else if (m_EntityState == Largage){
			m_pSprite->setCurrentAnimation(8);
			m_pSprite->Render(1, 4, _Renderer);
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
		int iTemp = CPhysics::VerifyGroundCollision(m_RectPosition);
		if (iTemp != NOCONTACT)
			m_EntityState = Immobile;
		switch (m_EntityState) {
			case Largage:
				CPosition temp =  *m_Trajectoire->UpdatePosition();
				CPhysics::VerifyNextPosition(m_Trajectoire->GetActualPosition(), m_Trajectoire->getNextPos(), m_RectPosition);
				m_RectPosition.y = temp.getY();
				m_RectPosition.x = temp.getX();
				m_pSprite->setSpritePos(m_RectPosition.x, m_RectPosition.y);
				break;
		}
	}
};

#endif
