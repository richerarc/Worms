#include <math.h>


class CPosition{
private:
	double	m_iX,  // m_iY et m_iX:  Positions en X et en Y du vecteur 2D
		m_iY;
public:

	//Contructeur:
	//	Parametres:
	//			_iX, _iY: Les valeurs de position(force) en X et en Y du vecteur 2D
	CPosition(double _iX, double _iY){
		m_iX = _iX;
		m_iY = _iY;
	}

	//Redefinition de l'opérateur +:
	//
	CPosition * operator+ (CPosition * _Vector){
		return new CPosition(m_iX + _Vector->getX(), m_iY + _Vector->getY());
	}

	//Accesseurs...

	//	getX(), getY() :
	//			permettent de retourner les valeurs des positions en x et en y.
	//	setX(int), setY(int) :
	//			permettent de  modifier les valeurs des positions en X et en Y avec les valeurs passées en paramètre.
	double getX(){
		return m_iX;
	}
	double getY(){
		return m_iY;
	}
	void setX(double _iX){
		m_iX = _iX;
	}
	void setY(double _iY){
		m_iY = _iY;
	}

};

class C2DVector{

private:
	int	m_XOrigine,  // m_iY et m_iX:  Positions en X et en Y du vecteur 2D
		m_YOrigine,
		m_XFin,
		m_YFin;

	double	m_Norme,
		m_Orientation;

public:

	//Contructeur:
	//	Parametres:
	//			_iX, _iY: Les valeurs de position(force) en X et en Y du vecteur 2D
	C2DVector(int _XDepart, int _YDepart, double _Norme, double _AngleRad){
		m_XOrigine = _XDepart;
		m_YOrigine = _YDepart;
		m_Norme = _Norme;
		m_Orientation = _AngleRad;
		m_XFin = _XDepart + (_Norme * cos(_AngleRad));
		m_YFin = _YDepart + (_Norme * sin(_AngleRad));
	}

	C2DVector(int _XDepart, int _YDepart, int _Xfin, int _Yfin){
		m_XOrigine = _XDepart;
		m_YOrigine = _YDepart;
		m_XFin = _Xfin;
		m_YFin = _Yfin;
		m_Norme = sqrt(pow(_Xfin - _XDepart, 2) + pow(_Yfin - _YDepart, 2));
		int x = _Xfin - _XDepart;
		int y = _Yfin - _YDepart;
		m_Orientation = atan(y /x);
		if ((x < 0) || ((x < 0) && (y < 0)))
			m_Orientation = M_PI + m_Orientation;
		else if (y < 0)
			m_Orientation = (2 * M_PI) + m_Orientation;
	}

	//Redefinition de l'opérateur +:
	//
	C2DVector * operator+ (C2DVector * _Vector){
		return new C2DVector(m_XOrigine, m_YOrigine, (_Vector->getXfin() + m_XFin), (_Vector->getYfin() + m_YFin) );
	}

	//Accesseurs...

	int getXfin(){ return m_XFin; }
	int getYfin(){ return m_YFin; }
	int getXDebut(){ return m_XOrigine; }
	int getYDebut(){ return m_YOrigine; }

	void setXfin(int _x){ m_XFin = _x; }
	void setYfin(int _y){ m_YFin = _y; }
	void setXDebut(int _x){ m_XOrigine = _x; }
	void setYDebut(int _y){ m_YOrigine = _y; }

};