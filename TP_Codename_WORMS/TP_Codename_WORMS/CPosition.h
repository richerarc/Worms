#include <math.h>

//Change les degrées en radians.
double DegToRad(double _Degre){
	return _Degre * M_PI / 180;
}

//Change les Radians en Degrés.
double RadToDeg(double _Radian){
	return _Radian * 180 / M_PI;
}

#include "C2DVector.h"


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

	void setXY(double _dX, double _dY){
		m_iX = _dX;
		m_iY = _dY;
	}

};