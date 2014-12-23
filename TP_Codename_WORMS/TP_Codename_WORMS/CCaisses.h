#ifndef TP_Codename_WORMS_CCaisses_h
#define TP_Codename_WORMS_CCaisses_h


/*!
@CCaisses
@Classe permettant la création d'une caisse
*/
class CCaisses : public CObjets{
private:
public:

	/*!
	@method Constructeur
	@brief Permet d'initialiser les données membres.
	@param _TextureExplosion image de l'explosion.
	@param _RectPos: la pos du rectangle de l'objet.
	@param _pTexture : texture de l'image à afficher.
	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets.
	*/
	CCaisses(SDL_Rect _RectPos, SDL_Texture* _Texture, CExplosion* _Explosion) :CObjets(_RectPos, _Texture, _Explosion){
	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead.
	*/
	~CCaisses(){
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture de la caisse
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
		if (!m_boIsexploded){
			Move();
			if ((!m_Angle) && (m_EntityState == Immobile))
				m_Angle = CPhysics::EvaluateSlope({ m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, m_RectPosition.h });
			SDL_RenderCopyEx(_pRenderer, m_pTexture, NULL, &m_RectPosition, RadToDeg(m_Angle), NULL, SDL_FLIP_NONE);
		}
		else{
			m_pExplosion->setPositionXY(m_RectPosition.x + 14, m_RectPosition.y + 8);
			m_pExplosion->startExplosion();
			m_pExplosion->ExplodeMap(_pRenderer);
			m_pExplosion->Draw(_pRenderer);
			if (m_pExplosion->IsDone()){
				m_boHasExplosed = true;
				m_pExplosion->ExplodeMap(_pRenderer);
				CEntity::m_uiCurrentNbrOfEntityExplosed++;
			}
		}



	}

	/*!
	@method ReactToExplosion
	@brief réagit a une explosion.
	@param _iX: Position en x de l'explosion.
	@param _iY: Position en y de l'explosion.
	@param _iRayon: Rayon de l'explosion.
	@return Adresse mémoire de l'objet.
	@discussion Aucune.
	*/
	void ReactToExplosion(int _iX, int _iY, int _iRayon){
		//Objet a droite de l'explosion
		if (m_RectPosition.x >= _iX && !m_boIsexploded){
			if (m_RectPosition.y >= _iY && !m_boIsexploded){
				if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow((m_RectPosition.y - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
			}
			if (m_RectPosition.y <= _iY && !m_boIsexploded){
				if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow((_iY - m_RectPosition.y), 2))) < _iRayon)
					m_boIsexploded = true;
			}
			if (m_RectPosition.y + 30 >= _iY && !m_boIsexploded){
				if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow(((m_RectPosition.y + 30) - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
			}
			if (m_RectPosition.y + 30 <= _iY && !m_boIsexploded){
				if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow((_iY - (m_RectPosition.y + 30)), 2))) < _iRayon)
					m_boIsexploded = true;
			}

		}
		//Objet a gauche de l'explosion
		if (m_RectPosition.x <= _iX && !m_boIsexploded){
			if (m_RectPosition.y >= _iY && !m_boIsexploded){
				if (sqrt((pow((_iX - m_RectPosition.x + 30), 2) + pow((m_RectPosition.y - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
			}
			if (m_RectPosition.y <= _iY && !m_boIsexploded){
				if (sqrt((pow((_iX - m_RectPosition.x + 30), 2) + pow((m_RectPosition.y + 30 - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
			}
			if (m_RectPosition.y + 30 >= _iY && !m_boIsexploded){
				if (sqrt((pow((_iX - m_RectPosition.x + 30), 2) + pow((_iY - m_RectPosition.y), 2))) < _iRayon)
					m_boIsexploded = true;
			}
			if (m_RectPosition.y + 30 <= _iY && !m_boIsexploded){
				if (sqrt((pow((_iX - m_RectPosition.x + 30), 2) + pow((_iY - m_RectPosition.y + 30), 2))) < _iRayon)
					m_boIsexploded = true;
			}
		}
	}
	
	/*!
	@method GiveLife
	@brief Calculer le nombre de point de vie rendu au worm.
	@param _pWorm: Un pointeur de worm qui gagnera de la vie
	@return nothing
	@discussion La condition est de 80pts de vie puisque en haut de 80, 25% de vie de + va au dessus de 100.
	*/
	void GiveLife(CWorm* _pWorm){
		if (_pWorm->getLife() <= 80)
			_pWorm->SetLife(_pWorm->getLife() + (_pWorm->getLife() * 25 / 100));
		else
			_pWorm->SetLife(100);

	}

	/*!
	@method Accesseurs
	@brief Permet d'acceder aux données membres.
	*/
	void VerifyWormsCollision(CWorm* _pWorm){
		if (_pWorm->getPosition().x == m_RectPosition.x && _pWorm->getPosition().y == m_RectPosition.y)
			GiveLife(_pWorm);
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	void setExplosion(bool _boSet){
		m_boIsexploded = _boSet;
	}

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}

	bool isCarePackage(){return true;}

};

#endif
