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
	int	m_XOrigine,
		m_YOrigine,
		m_XFin,
		m_YFin;

	double	m_Norme,
		m_Orientation,
		m_ComposanteX,
		m_ComposanteY;

public:

	C2DVector(int _XDepart, int _YDepart, double _Norme, double _AngleRad){
		m_XOrigine = _XDepart;
		m_YOrigine = _YDepart;
		m_Norme = _Norme;
		m_Orientation = _AngleRad;
		m_ComposanteX = _Norme * cos(_AngleRad);
		m_ComposanteY = _Norme * sin(_AngleRad);
		m_XFin = _XDepart + (m_ComposanteX);
		m_YFin = _YDepart + (m_ComposanteY);
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
		return new C2DVector(m_XOrigine, m_YOrigine, m_ComposanteX + _Vector->getComposanteX(), m_ComposanteY + _Vector->getComposanteY());
	}

	//Accesseurs...

	int getXfin(){ return m_XFin; }
	int getYfin(){ return m_YFin; }
	int getXDebut(){ return m_XOrigine; }
	int getYDebut(){ return m_YOrigine; }
	double getNorme(){ return m_Norme; }
	double getOrientation(){ return m_Orientation; }
	double getComposanteX(){ return (double)(m_Norme*cos(m_Orientation)); }
	double getComposanteY(){ return (double)(m_Norme*sin(m_Orientation)); }

	void setXfin(int _x){ m_XFin = _x; }
	void setYfin(int _y){ m_YFin = _y; }
	void setXDebut(int _x){ m_XOrigine = _x; }
	void setYDebut(int _y){ m_YOrigine = _y; }
	void setNorme(double _Norme){ m_Norme = _Norme; }
	void setOrientation(double _AngleRadian){ m_Orientation = _AngleRadian; }

};