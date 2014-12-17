//
//  CInGame.h
//
//  Created by Kevin Pantelakis on 2014-11-11.
//

/*!
 @class CMap
 @discussion Classe pour l'affichage de la carte durant la partie
 */
class CMap {
private:
	string m_strName;				// Nom du champ de battaile.
	SDL_Texture* m_Background;		// Background du champ de battaileé
	SDL_Surface* m_Map;				// Champ de battaile.
	SDL_Texture* m_MapConverted;	// Champ de battaile convertié
	SDL_Surface* m_ExplosionMask;	// Masque d'explosion.
	unsigned int m_uiGravity;		// Gravité du Champ de battaile.
	unsigned int m_uiMaxWind;		// Vent maximum du Champ de battaile.
	unsigned int m_uiNbrMine;		// Nombre de mines maximum du Champ de battaile
	bool m_boModified;				// Indique si le Champ de battaile a été converti ou pas.
public:

	/*!
	 @method Constructeur
	 @param _Name: Nom du Champ de battaile
	 @param _Background : Le background de la map
	 @param _Map : Le foreground de la map
	 @param _Gravity : La gravité en jeux sur la map
	 @param _MaxWind : Le maximum que la valuer du vent peut prendre
	 @param _NbrMine : Le nombre de mine a display au départ sur la map
	 @return Aucun
	 */
	CMap(string _Name, SDL_Texture* _Background, SDL_Surface* _Map, unsigned int _Gravity, unsigned int _MaxWind, unsigned int _NbrMine){
		m_Background = _Background;
		m_Map = _Map;
		m_MapConverted = nullptr;
		m_uiGravity = _Gravity;
		m_uiMaxWind = _MaxWind;
		m_uiNbrMine = _NbrMine;
		m_strName = _Name;
		m_boModified = true;
	}
	/*!
	 @method Destructeur.
	 @brief Suddenly destroy our world.
	 @discussion Boom.
	 */
	~CMap(){
	
	}

	void ConvertMap(SDL_Renderer* _Renderer){
		if (m_MapConverted != nullptr){
			SDL_DestroyTexture(m_MapConverted);
		}
		m_MapConverted = SDL_CreateTextureFromSurface(_Renderer, m_Map);
		m_boModified = false;
	}

	/*!
	@method Draw
	@brief Imprime le Champ de battaile sur le rendu du la fênetre
	@param  _Renderer: Rendu de la fênetre.
	@return Aucun.
	*/
	void Draw(SDL_Renderer* _Renderer){
		if (m_boModified)
			ConvertMap(_Renderer);
		SDL_RenderCopy(_Renderer, m_Background, NULL, NULL);
		SDL_RenderCopy(_Renderer, m_MapConverted, NULL, NULL);
	}
	
	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	string getName(){
		return m_strName;
	}
	
	int getWind(){
		return m_uiMaxWind;
	}
	int getGravity(){
		return m_uiGravity;
	}
	int getMine(){
		return m_uiNbrMine;
	}
	
	SDL_Surface* getMap(){
		return m_Map;
	}
};