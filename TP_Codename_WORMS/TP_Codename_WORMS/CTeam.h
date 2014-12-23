//
//  CTeam.h
//  
//  Created by Kevin Pantelakis on 2014-11-11.
//
#define MAXWORMS 6

/*!
@class CTeam
@discussion Classe représentant une équipe.
*/
class CTeam{
private:
	string m_strTeamName;
	CListeDC<CWorm*>* m_pListWorm;
	SDL_Color m_TeamColor;
	unsigned int m_uiNbOfWorm;
	unsigned int m_uiWormTurn;
	bool m_boFocus;
	bool m_bodefeated;
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _strTeamName: Nom de l'équipe
	@param _Color: Couleur de l'équipe
	@return Adresse mémoire de l'objet.
	@discussion Voilà.
	*/
	CTeam(string _strTeamName, SDL_Texture* _WormRepo, SDL_Texture* _TexSprite, unsigned int _uiNbWorms, CFont* _Font, CTexture* _TextureExplosion, CMap* _Map){
		m_boFocus = false;
		m_bodefeated = false;
		m_pListWorm = new CListeDC<CWorm*>();
		m_uiWormTurn = 0;
		m_TeamColor = { static_cast<Uint8>((SDL_GetTicks() - rand()) % 255 + 1), static_cast<Uint8>((rand() + SDL_GetTicks()) % 255 + 1), static_cast<Uint8>((SDL_GetTicks() * rand()) % 255 + 1), 255 };
		m_strTeamName = _strTeamName;
		m_uiNbOfWorm = _uiNbWorms;
		string strNom = "Worm";
		char Buffer[255];
		for (int i = 0; i < _uiNbWorms; i++)
		{
			strNom.append(" ");
			strNom.append(SDL_itoa(i, Buffer, 10));
			m_pListWorm->AjouterFin(new CWorm(strNom, _WormRepo, new CSprite("", _TexSprite, 10, 17, 80, -1), _Font, { rand() % WIDTH, -50, 30, 50 }, &m_TeamColor, new CExplosion(_TextureExplosion, 50, _Map)));
			strNom.pop_back();
			strNom.pop_back();
		}
		m_pListWorm->AllerDebut();
		m_pListWorm->ObtenirElement()->setFocus(true);
	}

	~CTeam(){
		delete m_pListWorm;
	}

	/*!
	@method NextTurn
	@brief Change le focus des Worms pour le tour suivant.
	*/
	void NextTurn(){
		if (m_pListWorm->Count() > 1){
			unsigned int temp = (m_uiWormTurn) % m_uiNbOfWorm;
			m_pListWorm->AllerA(temp);
			if (m_pListWorm->ObtenirElement()->isFocused()){
				m_pListWorm->ObtenirElement()->setFocus(false);
				m_pListWorm->ObtenirElement()->setPlaystate(false);
			}
			m_pListWorm->AllerA((temp + 1) % m_uiNbOfWorm);
			m_pListWorm->ObtenirElement()->setFocus(true);
			m_uiWormTurn++;
		}
	}

	/*!
	@method Draw
	@brief Affiche l'équipe
	@param SDL_Renderer* _Renderer: Rendu de la fenetre sur laquelle afficher.
	@return Aucun
	@discussion
	*/
	void draw(SDL_Renderer* _Renderer){
		if (m_pListWorm->Count()){
			m_pListWorm->AllerDebut();
			for (int i = 0; i < m_uiNbOfWorm; i++){
				m_pListWorm->ObtenirElement()->Draw(_Renderer);
				m_pListWorm->AllerSuivant();
			}
		}
	}


	void HandleEvent(SDL_Event _Event){
		m_pListWorm->AllerDebut();
		for (int i(0); i < m_uiNbOfWorm; i++){
			if (m_pListWorm->ObtenirElement()->isFocused()){
				m_pListWorm->ObtenirElement()->HandleEvent(_Event);
				break;
			}
			m_pListWorm->AllerSuivant();
		}
	}

	/*!
	@Accesseurs
	*/
	void setFocus(bool _boFocus){ m_boFocus = _boFocus; }

	void setTeamColor(SDL_Color _Color) { m_TeamColor = _Color; }

	void setTeamName(string _strName){ m_strTeamName = _strName; }

	bool IsFocused(){ return m_boFocus; }

	string getTeamName(){ return m_strTeamName; }

	CWorm* getPlayingWorm(){
		m_pListWorm->AllerDebut();
		for (int i = 0; i < m_uiNbOfWorm; i++){
			if (m_pListWorm->ObtenirElement()->isFocused())
				return m_pListWorm->ObtenirElement();
			m_pListWorm->AllerSuivant();
		}
		return nullptr;
	}

	bool isDefeated(){
		return m_bodefeated;
	}

	CListeDC<CWorm*>* getListeWorm(){
		return m_pListWorm;
	}

	/*!
	 @Méthode:
	 @ReactToExplosion
	 @Permet de calculer les dommages subit par l'explosion
	 */
	void ReactToExplosion(CExplosion * _Explosion){
		for (int i = 0; i < m_pListWorm->Count(); i++){
			m_pListWorm->AllerA(i);
			m_pListWorm->ObtenirElement()->ReactToExplosion(_Explosion);
		}
	}

	int EnterrerLesMorts(){
		int itemp = 0;
		if (!m_pListWorm->Count()){
			m_bodefeated = true;
		}
		m_pListWorm->AllerDebut();
		for (int i = 0; i < m_pListWorm->Count(); i++){
			if (m_pListWorm->ObtenirElement()->getWormState() == Dead){
				if (!m_pListWorm->ObtenirElement()->isPlaying()){
					m_pListWorm->Retirer(false);
					itemp++;
					if (m_pListWorm->Count()){
						if (m_pListWorm->ObtenirElement()->isFocused()){
							m_pListWorm->AllerPrecedent();
							m_pListWorm->ObtenirElement()->setFocus(false);
						}
					}
					else{
						m_bodefeated = true;
					}
				}
				else{
					if (m_pListWorm->ObtenirElement()->isFocused()){
						m_pListWorm->Retirer(false);
						itemp++;
						if (m_pListWorm->Count()){
							m_pListWorm->AllerPrecedent();
							m_pListWorm->ObtenirElement()->setFocus(false);
						}
						else{
							m_bodefeated = true;
						}
					}
					else{
						m_pListWorm->Retirer(false);
						itemp++;
					}
				}
			}
			else{
				m_pListWorm->AllerSuivant();
			}
		}
		return itemp;
	}





};