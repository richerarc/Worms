class 2DVector{
private:
	double	m_iX,  // m_iY et m_iX:  Positions en X et en Y du vecteur 2D
			m_iY;
public:

	//Contructeur:
	//	Parametres:
	//			_iX, _iY: Les valeurs de position(force) en X et en Y du vecteur 2D
	C2DVector(double _iX, double _iY){
		m_iX = _iX;
		m_iY = _iY;
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