#include "C2DVector.h"


class CPosition{
private:
	double	m_iX,  // m_iY et m_iX:  Positions en X et en Y du vecteur 2D
		m_iY;
public:

	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _iX: Position en x
	@param _iY: Position en y
	@return Adresse m�moire de l'objet.
	@discussion None.
	*/
	CPosition(double _iX, double _iY){
		m_iX = _iX;
		m_iY = _iY;
	}

	/*!
	@method operator+
	@brief red�finition de l'op�rateur +
	@param _YDepart: Position Y de D�part du vecteur
	@return Adresse m�moire de l'objet.
	@discussion pour additioner des positions
	*/
	CPosition * operator+ (CPosition * _Vector){
		return new CPosition(m_iX + _Vector->getX(), m_iY + _Vector->getY());
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux donn�es membres.
	*/

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