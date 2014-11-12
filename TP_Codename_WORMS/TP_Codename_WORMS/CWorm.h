//
//  CWorm.h
//
//  Created by Jessy Desjardins on 2014-11-11.
//  Copyright (c) 2014 Jessy Desjardins. All rights reserved.
//

#ifndef TP_Codename_WORMS_CWorm_h
#define TP_Codename_WORMS_CWorm_h


/*!
@CWorm
@Classe permettant la création de la classe des Worm
*/
class CWorm : public CEntity{
private:
	int m_iLife; //Donnée représentant la vie actuelle du worm
	int m_iLifeMax;//Donnée représentant la vie maximum du worm
	CSprite* m_pSprite;//Sprite du worm
	
public:
	/*!
	@Constructeur
	@Description: Permet d'initialiser les données membres
	 @param _iLifeMax : la vie maximum du worm
	 @param _pSprite : le sprite du worm
	 @param _RectPos : la position du sprite
	@Classe héritant de CEntity
	*/
	CWorm(int _iLifeMax, CSprite* _pSprite, const char* _Name, unsigned int _uiMasse, SDL_Rect _RectPos) :CEntity(_Name, _uiMasse, _RectPos){
		m_iLife = _iLifeMax;
		m_iLifeMax = _iLifeMax;
		m_pSprite = _pSprite;
		m_pSprite->setSpritePos(_RectPos.x, _RectPos.y);

	}
	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CWorm(){
	}
	/*!
	@Méthode:
	@ReactToExplosion
	@Permet de calculer les dommages subit par l'explosion
	*/
	float ReactToExplosion(CEntity* _pEntity){
		return 0.f;
	}

	/*!
	@method HandleEvent
	@param _Evant : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event _Event){

		switch (_Event.type){

		case SDLK_UP:
		case SDLK_w:
			//
			break;
		case SDLK_LEFT:
		case SDLK_a:
			//
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			//
			break;
		case SDLK_SPACE:
			//
			break;
		}
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture du Sprite 
	@return null
	*/
	void Draw(SDL_Renderer * _Renderer){
		m_pSprite->Render(_Renderer);
	}



	/*!
	@Accesseurs:
	*/
	void SetLife(int _iLifeActuelle){
		m_iLife = _iLifeActuelle;
	}

};

#endif
