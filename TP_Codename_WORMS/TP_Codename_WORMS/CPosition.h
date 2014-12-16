#include "C2DVector.h"


class CPosition{
private:
	double	m_iX,  // m_iY et m_iX:  Positions en X et en Y du vecteur 2D
		m_iY;
	bool m_boState;
public:

	/*!
	@method Constructeur.
	@brief Initialise les données membres.
	@param _iX: Position en x
	@param _iY: Position en y
	@return Adresse mémoire de l'objet.
	@discussion None.
	*/
	CPosition(double _iX, double _iY){
		m_iX = _iX;
		m_iY = _iY;
		m_boState = false;
	}

	/*!
	@method operator+
	@brief redéfinition de l'opérateur +
	@param _YDepart: Position Y de Départ du vecteur
	@return Adresse mémoire de l'objet.
	@discussion pour additioner des positions
	*/
	CPosition * operator+ (CPosition * _Vector){
		return new CPosition(m_iX + _Vector->getX(), m_iY + _Vector->getY());
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux données membres.
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

	//Methode CalculateDistance()
	//retour: float (Distance entre deux points.
	//Parametres: Soit un CPosition * ou des valeurs de x et y

	float ClaculateDistance(CPosition * _ComparePosition){
		return sqrt(pow(m_iX - _ComparePosition->getX(), 2)*pow(m_iY - _ComparePosition->getY(), 2));
	}
	float ClaculateDistance( float _X, float _Y){
		return sqrt(pow(m_iX - _X, 2)*pow(m_iY - _Y, 2));
	}
	bool getState(){ return m_boState; }
	void setState(bool _boState){ m_boState = _boState; }

};