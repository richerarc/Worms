class CPowerBar{
private:

	SDL_Rect m_RectPower; //Dimension et position de la powerbar
	bool m_boActive;
	bool m_boReversePowerBar; // Booléen pour vérifier si la barre de lancement ira dans le sense contraire.
	unsigned int m_uiPower; // Représente la longueuer du Fill Rect.
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _Rect rect de l'objet qui a une powerbar
	@return Adresse mémoire de l'objet.
	@discussion Classe héritant de CObjets, elle prend donc les paramètres du constructeur CObjets
	*/
	CPowerBar(SDL_Rect _Rect){
		m_boActive = false;
		m_boReversePowerBar = false;
		m_RectPower.x = _Rect.x;
		m_RectPower.y = _Rect.y;
		m_RectPower.w = 0;
		m_RectPower.h = 10;
	}

	/*!
	@method Destructeur:
	@brief Permet  de détruire les objets créés en mémoire
	*/
	~CPowerBar(){}

	/*!
	@method <#name#>
	@brief <#Short description#>
	@param <#Paremeter#>
	@return <#Return value#>
	@discussion <#Other code info#>
	*/
	void Draw(SDL_Renderer* _pRenderer){
		SetDimension();
		SDL_SetRenderDrawColor(_pRenderer, (m_uiPower * 5), (250 - (m_uiPower * 5)), 0, 255);
		SDL_RenderFillRect(_pRenderer, &m_RectPower);
		SDL_SetRenderDrawColor(_pRenderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(_pRenderer, &m_RectPower);
	}

	/*!
	@method <#name#>
	@brief <#Short description#>
	@param <#Paremeter#>
	@return <#Return value#>
	@discussion <#Other code info#>
	*/
	void PowerUp(){
		if (m_uiPower <= 50 && !m_boReversePowerBar){
			if (m_uiPower == 50)
				m_boReversePowerBar = true;
			else
				m_uiPower++;
		}
		else if (m_boReversePowerBar){
			if (m_uiPower == 0)
				m_boReversePowerBar = false;
			else
				m_uiPower--;
		}
	}

	/*!
	@method PowerDown
	@brief permet de décrémenter le power.
	*/
	void PowerDown(){
		m_uiPower--;
	}

	/*!
	@method Accesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	void SetDimension(){
		m_RectPower.w = m_uiPower;
	}
	void SetPosition(int _ix, int _iy){
		m_RectPower.x = _ix;
		m_RectPower.y = _iy - 15;
	}

	//Power en pourcentage
	unsigned int getPowerLevel(){
		unsigned int temp = m_uiPower * 2;
//		m_uiPower = 0;
		return temp;
	}
	//Power en entier
	unsigned int getPower(){
		return m_uiPower;
	}
	void setPowerLevel(unsigned int _ipower){ m_uiPower = _ipower; }
};