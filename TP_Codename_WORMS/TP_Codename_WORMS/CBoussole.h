//
//  CBoussole.h
//  TP_Codename_WORMS
//
//  Créé par Kevin Pantelakis le 2014-10-28.
//  Mise à jour par Kevin Pantelakis le 2014-10-29
//  
//

/*!
@class CBoussole.h
@discussion Classe qui représente la boussole.
*/
class CBoussole{
private:
	SDL_Texture* m_pCompass;
	SDL_Texture* m_pArrow;
	SDL_Rect m_RectCompassPosition;
	SDL_Rect m_RectArrowPosition;
	double m_dblAngle;

public:

	CBoussole(SDL_Texture* _CompassTexture, SDL_Texture* _ArrowTexture ){
		m_pCompass = _CompassTexture;
		m_pArrow = _ArrowTexture;
		SDL_QueryTexture(_CompassTexture, NULL, NULL, &m_RectCompassPosition.w, &m_RectCompassPosition.h);
		m_RectCompassPosition.x = WIDTH - m_RectCompassPosition.w;
		m_RectCompassPosition.y = 0;
		SDL_QueryTexture(_ArrowTexture, NULL, NULL, &m_RectArrowPosition.w, &m_RectArrowPosition.h);
		m_RectArrowPosition.x = WIDTH - m_RectArrowPosition.w;
		m_RectArrowPosition.y = 0;
		m_dblAngle = 0;
	}

	~CBoussole(){
	
	}

	void Draw(SDL_Renderer* _Renderer){
		SDL_RenderCopyEx(_Renderer, m_pArrow, NULL, &m_RectArrowPosition, m_dblAngle, NULL, SDL_FLIP_NONE);
	}

	double getAngle(){ return m_dblAngle; }

	void setAngle(double _Angle){ m_dblAngle = _Angle; }


};