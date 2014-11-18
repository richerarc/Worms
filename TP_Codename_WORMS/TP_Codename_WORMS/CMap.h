//
//  CInGame.h
//
//  Created by Kevin Pantelakis on 2014-11-11.
//
#define IDTransparence 16777215 // Représente le numéro de couleur de la transparence.

/*!
 @class CMap
 @discussion Classe pour l'affichage de la carte durant la partie
 */
class CMap {
private:
	string m_strName;
	SDL_Texture* m_Background;
	SDL_Surface* m_Map;
	SDL_Texture* m_MapConverted;
	SDL_Surface* m_ExplosionMask;
	unsigned int m_uiGravity;
	unsigned int m_uiMaxWind;
	unsigned int m_uiNbrMine;
public:

	/*!
	 @method Constructeur
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
		m_uiGravity = _Gravity;
		m_uiMaxWind = _MaxWind;
		m_uiNbrMine = _NbrMine;
	}

	void ConvertMap(SDL_Renderer* _Renderer){
		m_MapConverted = SDL_CreateTextureFromSurface(_Renderer, m_Map);
	}

	void ExplodeMap(SDL_Renderer* _Renderer, SDL_Rect _ExplosionPos){
		int iPosTableau = (_ExplosionPos.y * m_Map->w) + _ExplosionPos.x; // Variable représentant la position du pixel du rect dans un tableau 1D
		for (int i = 0; i < (_ExplosionPos.w * _ExplosionPos.h); i++){
			if ((unsigned int*)m_ExplosionMask->pixels)[i] != IDTransparence)
				iPosTableau += 1;
			else
				m_Map->pixels[iPosTableau] = IDTransparence;
		}
			ConvertMap(_Renderer);
	}

	void Draw(SDL_Renderer* _Renderer){
		if (m_MapConverted == nullptr)
			ConvertMap(_Renderer);
		SDL_RenderCopy(_Renderer, m_Background, NULL, NULL);
		SDL_RenderCopy(_Renderer, m_MapConverted, NULL, NULL);
	}


};