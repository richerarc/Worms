#ifndef TP_Codename_WORMS_CMines_h
#define TP_Codename_WORMS_CMines_h


/*!
@CMines
@Classe permettant la création d'une mines
*/
class CMines : public CObjets{
private:

public:
	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _RectPos: la pos du rectangle de l'objet
	@param _pTexture: texture de l'image à afficher
	@param _Explosion: Une explosion passée à Entity.
	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets
	*/
	CMines(SDL_Rect _RectPos, SDL_Texture* _Texture, CExplosion* _Explosion) :CObjets(_RectPos, _Texture, _Explosion){
	}

	/*!
	@Destructeur:
	@Permet de détruire les objets créés en mémoire
	*/
	~CMines(){
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture de la mine
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
		if (!m_boIsexploded){
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
	@param _iX : La position en x de l'explosion
	@param _iY : La position en y de l'explosion
	@param _iRayon : Le rayon de l'explosion
	@return null
	*/
	void ReactToExplosion(int _iX, int _iY, int _iRayon){
		//Objet a droite de l'explosion
		if (m_RectPosition.x >= _iX && !m_boIsexploded){
			if (m_RectPosition.y >= _iY && !m_boIsexploded){
				if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow((m_RectPosition.y - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
				else if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow((m_RectPosition.y + 8 - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
			}

			if (m_RectPosition.y <= _iY && !m_boIsexploded){
				if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow((_iY - m_RectPosition.y), 2))) < _iRayon)
					m_boIsexploded = true;
				else if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow((_iY - m_RectPosition.y + 8), 2))) < _iRayon)
					m_boIsexploded = true;
			}

		}
		//Objet a gauche de l'explosion
		if (m_RectPosition.x <= _iX && !m_boIsexploded){
			if (m_RectPosition.y >= _iY && !m_boIsexploded){
				if (sqrt((pow((_iX - m_RectPosition.x + 24), 2) + pow((m_RectPosition.y - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
				else if (sqrt((pow((_iX - m_RectPosition.x + 24), 2) + pow((m_RectPosition.y + 8 - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
			}

			if (m_RectPosition.y <= _iY && !m_boIsexploded){
				if (sqrt((pow((_iX - m_RectPosition.x + 24), 2) + pow((_iY - m_RectPosition.y), 2))) < _iRayon)
					m_boIsexploded = true;
				else if (sqrt((pow((_iX - m_RectPosition.x + 24), 2) + pow((_iY - m_RectPosition.y + 8), 2))) < _iRayon)
					m_boIsexploded = true;
			}
		}
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


};

#endif
