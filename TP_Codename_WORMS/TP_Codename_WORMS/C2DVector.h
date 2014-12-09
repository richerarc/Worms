//
//  C2DVector.h
//  TP_Codename_WORMS
//
//  Créé par Kevin Pantelakis.
//  Mise à jour par Kevin Pantelakis le 2014-11-27
//  
// S'arranger que le vecteur prennne (avec trois n) les angles en degrŽs.

/*!
@class C2DVector
@discussion Classe qui un Vecteur à 2 coordonées
*/
class C2DVector{
private:
	int	m_XOrigine,		// Cordonnée X de départ
		m_YOrigine,		// Cordonnée Y de départ
		m_XFin,			// Cordonnée X de Fin
		m_YFin;			// Cordonnée Y de Fin

	double	m_Norme,	// Norme du vecteur.
		m_Orientation,	// Orientation.
		m_ComposanteX,	// Composante X.
		m_ComposanteY;	// Composante Y.

	double m_XStart,
		m_YStart,
		m_XEnd,
		m_YEnd;
public:



	~C2DVector(){

	}

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _XDepart: Position X de départ du vecteur
	@param _YDepart: Position Y de Départ du vecteur
	@param _Xfin: Position X de fin du vecteur
	@param _Yfin: Position Y de fin du vecteur
	@return Adresse mémoire de l'objet.
	@discussion Initialise un vecteur avec sa position de départ et sa position de fin.
	*/
	C2DVector(int _XDepart, int _YDepart, int _Xfin, int _Yfin){
		m_XOrigine = _XDepart;
		m_YOrigine = _YDepart;
		m_XFin = _Xfin;
		m_YFin = _Yfin;
		m_XStart = (double)m_XOrigine;
		m_YStart = (double)m_YOrigine;
		m_XEnd = (double)m_XFin;
		m_YEnd = (double)m_YFin;
		m_Norme = sqrt(pow(_Xfin - _XDepart, 2) + pow(_Yfin - _YDepart, 2));
		m_ComposanteX = _Xfin - _XDepart;
		m_ComposanteY = _Yfin - _YDepart;
		if ((m_ComposanteX == 0) && (m_ComposanteY > 0))
			m_Orientation = M_PI / 2;
		else if ((m_ComposanteX == 0) && (m_ComposanteY < 0))
			m_Orientation = 1.5 * M_PI;
		else if ((m_ComposanteX > 0) && (m_ComposanteY == 0))
			m_Orientation = 0;
		else if ((m_ComposanteX < 0) && (m_ComposanteY == 0))
			m_Orientation = M_PI;
		else{
			m_Orientation = atan(m_ComposanteY / m_ComposanteX);
			if ((m_ComposanteX < 0) || ((m_ComposanteX < 0) && (m_ComposanteY < 0)))
				m_Orientation = M_PI + m_Orientation;
			else if (m_ComposanteY < 0)
				m_Orientation = (2 * M_PI) + m_Orientation;
		}
	}

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _XDepart: Position X de départ du vecteur.
	@param _YDepart: Position Y de Départ du vecteur.
	@param _Compx: Composante X du vecteur.
	@param _CompY: Composante y du vecteur.
	@return Adresse mémoire de l'objet.
	@discussion Initialise un vecteur avec sa position de départ et ses composantes.
	*/
	C2DVector(int _XDepart, int _YDepart, double _CompX, double _CompY){
		m_XOrigine = _XDepart;
		m_YOrigine = _YDepart;
		m_ComposanteX = _CompX;
		m_ComposanteY = _CompY;
		m_XFin = _XDepart + (m_ComposanteX);
		m_YFin = _YDepart + (m_ComposanteY);
		m_XStart = (double)m_XOrigine;
		m_YStart = (double)m_YOrigine;
		m_XEnd = m_XStart + (m_ComposanteX);
		m_YEnd = m_YStart + (m_ComposanteY);

		m_Norme = sqrt(pow(m_ComposanteX, 2) + pow(m_ComposanteY, 2));
		if ((m_ComposanteX == 0) && (m_ComposanteY > 0))
			m_Orientation = M_PI / 2;
		else if ((m_ComposanteX == 0) && (m_ComposanteY < 0))
			m_Orientation = 1.5 * M_PI;
		else if ((m_ComposanteX > 0) && (m_ComposanteY == 0))
			m_Orientation = 0;
		else if ((m_ComposanteX < 0) && (m_ComposanteY == 0))
			m_Orientation = M_PI;
		else{
			m_Orientation = atan(m_ComposanteY / m_ComposanteX);
			if ((m_ComposanteX < 0) || ((m_ComposanteX < 0) && (m_ComposanteY < 0)))
				m_Orientation = M_PI + m_Orientation;
			else if (m_ComposanteY < 0)
				m_Orientation = (2 * M_PI) + m_Orientation;
		}
	}

	//Redefinition de l'opérateur +:
	//
	C2DVector * operator+ (C2DVector * _Vector){
		return new C2DVector(m_XOrigine, m_YOrigine, m_ComposanteX + _Vector->getComposanteX(), m_ComposanteY + _Vector->getComposanteY());
	}


	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
	*/

	int getXfin(){ return m_XFin; }
	int getYfin(){ return m_YFin; }
	int getXDebut(){ return m_XOrigine; }
	int getYDebut(){ return m_YOrigine; }
	double getXEnd(){ return m_XEnd; }
	double getYEnd(){ return m_YEnd; }
	double getXStart(){ return m_XStart; }
	double getYStart(){ return m_YStart; }
	double getNorme(){ return m_Norme; }
	double getOrientation(){ return m_Orientation; }
	double getComposanteX(){ return m_ComposanteX; }
	double getComposanteY(){ return m_ComposanteY; }

	/*!
	@method getSDLOrientation
	@brief Obtient l'orientation voulue selon le système d'axe en affichage graphique.
	@discussion Simple lorsqu'on a compris mais difficile a comprendre quand on as appris tout le contraire depuit le début de nos études.
	*/
	double getSDLOrientation(){

		if (m_ComposanteX == 0 && m_ComposanteY < 0){ return 0; }

		if (m_ComposanteX == 0 && m_ComposanteY > 0){ return M_PI; }

		if (m_ComposanteX < 0 && m_ComposanteY == 0){ return 3 * M_PI / 2; }

		if (m_ComposanteX > 0 && m_ComposanteY == 0){ M_PI / 2; }

		if ((m_ComposanteX > 0 && m_ComposanteY < 0) || (m_ComposanteX > 0 && m_ComposanteY > 0)){
			return ((M_PI / 2) + atan(m_ComposanteY / m_ComposanteX));
		}

		if (m_ComposanteX < 0 && m_ComposanteY < 0){
			return (atan(m_ComposanteY / m_ComposanteX) - (M_PI / 2));
		}

		if (m_ComposanteX < 0 && m_ComposanteY > 0){
			return (atan(m_ComposanteY / m_ComposanteX) + (3 * M_PI / 2));
		}

		return NULL;
	}

	void setDOUBLE_XY_END(double _x, double _y){
		m_XEnd = _x;
		m_YEnd = _y;
	}
	void setDOUBLE_XY_START(double _x, double _y){
		m_XStart = _x;
		m_YStart = _y;
	}
	void setXYfin(int _x, int _y){
		m_XFin = _x;
		m_YFin = _y;
	}
	void setXYDebut(int _x, int _y){
		m_XOrigine = _x;
		m_YOrigine = _y;
	}
	void setComposanteXY(double _CompX, double _CompY){
		m_ComposanteX = _CompX;
		m_ComposanteY = _CompY;
		m_XFin = m_XOrigine + (m_ComposanteX);
		m_YFin = m_YOrigine + (m_ComposanteY);
		m_XEnd = m_XStart + (m_ComposanteX);
		m_YEnd = m_YStart + (m_ComposanteY);;
		m_Norme = sqrt(pow(m_XFin - m_XOrigine, 2) + pow(m_YFin - m_YOrigine, 2));
		if ((m_ComposanteX == 0) && (m_ComposanteY > 0))
			m_Orientation = M_PI / 2;
		else if ((m_ComposanteX == 0) && (m_ComposanteY < 0))
			m_Orientation = 1.5 * M_PI;
		else if ((m_ComposanteX > 0) && (m_ComposanteY == 0))
			m_Orientation = 0;
		else if ((m_ComposanteX < 0) && (m_ComposanteY == 0))
			m_Orientation = M_PI;
		else{
			m_Orientation = atan(m_ComposanteY / m_ComposanteX);
			if ((m_ComposanteX < 0) || ((m_ComposanteX < 0) && (m_ComposanteY < 0)))
				m_Orientation = M_PI + m_Orientation;
			else if (m_ComposanteY < 0)
				m_Orientation = (2 * M_PI) + m_Orientation;
		}
	}
	void setNorme(double _Norme){
		m_Norme = _Norme;
		m_ComposanteX = m_Norme * cos(m_Orientation);
		m_ComposanteY = m_Norme * sin(m_Orientation);
		m_XFin = m_XOrigine + (m_ComposanteX);
		m_YFin = m_YOrigine + (m_ComposanteY);
		m_XEnd = m_XStart + (m_ComposanteX);
		m_YEnd = m_YStart + (m_ComposanteY);

	}
	void setOrientation(double _AngleRadian){
		m_Orientation = _AngleRadian;
		m_ComposanteX = m_Norme * cos(m_Orientation);
		m_ComposanteY = m_Norme * sin(m_Orientation);
		m_XFin = m_XOrigine + (m_ComposanteX);
		m_YFin = m_YOrigine + (m_ComposanteY);
		m_XEnd = m_XStart + (m_ComposanteX);
		m_YEnd = m_YStart + (m_ComposanteY);
	}

	/*!
	@method Normalize
	@brief Normalise un vecteur.
	@discussion Donne un vecteur de norme 1 mais avec la même orientation.
	*/
	void Normalize(){
		if (m_Norme)
			m_Norme /= (m_Norme / 2);
		m_ComposanteX = cos(m_Orientation);
		m_ComposanteY = sin(m_Orientation);
	}



};