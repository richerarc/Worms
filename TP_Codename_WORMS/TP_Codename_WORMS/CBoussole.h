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
	SDL_Texture* m_pArrow;			// Image de la flèche (Rotation).
	SDL_Rect m_RectArrowPosition;	// Position de la fleche.
	double m_dblAngle;				// Angle de la rotation en degrés.
	CLabel* m_pLabel;				//Le label de la boussole
	unsigned int m_uiSpeed;			//La vitesse du vent
	string m_strWindSpeed;			//L'affichage de la vitesse du vent
	
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param SDL_Texture* _CompassTexture Texture de la boussole.
	@param SDL_Texture* _ArrowTexture Texture de la flèche.
	@return Adresse mémoire de l'objet.
	@discussion No discussion is needed.
	*/
	CBoussole(SDL_Texture* _ArrowTexture, CFont* _Font){
		m_pArrow = _ArrowTexture;
		SDL_QueryTexture(_ArrowTexture, NULL, NULL, &m_RectArrowPosition.w, &m_RectArrowPosition.h);
		m_RectArrowPosition.x = WIDTH - m_RectArrowPosition.w - 5;
		m_RectArrowPosition.y = 5;
		m_dblAngle = 0;
		m_strWindSpeed =  "0 px/ms";
		m_uiSpeed = 0;
		m_pLabel = new CLabel("lbleWind",m_strWindSpeed.c_str(), _Font, { m_RectArrowPosition.x + 15, m_RectArrowPosition.y + m_RectArrowPosition.h + 1, 30, 30 });
	}

	/*!
	@method Destructeur.
	@brief Destroy.
	@discussion He is dead.
	*/
	~CBoussole(){
	}

	/*!
	@method Draw
	@brief Affiche et Rotationne la fleche et le Compas
	@param SDL_Renderer* _Renderer: Rendu de la fenetre sur laquelle afficher.
	@return Aucun
	@discussion LOOK IT'S SPINNING! MUCH ROTATION! VERY BOSS! AWESOME COMPASS! WOW!.
	*/
	void Draw(SDL_Renderer* _Renderer){
		SDL_RenderCopyEx(_Renderer, m_pArrow, NULL, &m_RectArrowPosition, m_dblAngle, NULL, SDL_FLIP_NONE);
		m_pLabel->Draw(_Renderer);
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	double getAngle(){ return m_dblAngle; }

	void setAngle(double _Angle){ m_dblAngle = _Angle; }

	void setWindSpeed(unsigned int _uiSpeed){
		char temp[10];
		m_strWindSpeed = SDL_uitoa(_uiSpeed, temp, 10);
		m_strWindSpeed.append(" px/ms");
		m_pLabel->setText(m_strWindSpeed.c_str());
	}
};