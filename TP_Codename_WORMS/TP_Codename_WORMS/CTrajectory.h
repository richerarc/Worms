

/*
 Nom : CTrajectory
 Discussion : Classe reprŽsentant la trajectoire d'un point
 */


class CTrajectory{
private:
	CTimer* m_TrajectoryTime;
	CPosition* m_StartPos;
	C2DVector* m_InitSpeed;
	C2DVector* m_ActualSpeed;
	C2DVector* m_Acceleration;
	CPosition* m_ActualPos;
	CPosition* m_NextPos;
	bool m_boStop;
	int rebonds;
public:
	int GetRebonds(){
		return rebonds;
	}


	CTrajectory(CPosition* _StartPos, C2DVector* _Speed, C2DVector* _Acc){
		m_boStop = false;
		m_TrajectoryTime = new CTimer();
		m_StartPos = _StartPos;
		m_InitSpeed = _Speed;
		m_ActualSpeed = new C2DVector(_Speed->getXDebut(),_Speed->getYDebut(),_Speed->getComposanteX(),_Speed->getComposanteY());
		m_Acceleration = _Acc;
		m_ActualPos = new CPosition(m_StartPos->getX(),m_StartPos->getY());
		m_NextPos = new CPosition(m_ActualPos->getX(), m_ActualPos->getY());
		m_Acceleration->setComposanteXY(m_Acceleration->getComposanteX()/42, m_Acceleration->getComposanteY() / 42);
		m_TrajectoryTime->Start();
		rebonds = 0;
	}
	
		//Destructeur...
	~CTrajectory(){
		if (m_StartPos != nullptr){
			if (m_ActualPos == m_StartPos)
				m_ActualPos = nullptr;
			else{
				delete m_ActualPos;
				m_ActualPos = nullptr;
			}
			delete m_StartPos;
		}
		m_StartPos = nullptr;
		if (m_InitSpeed)
			delete m_InitSpeed;
		m_InitSpeed = nullptr;
		if (m_Acceleration)
			delete m_Acceleration;
		m_Acceleration = nullptr;
		if (m_NextPos)
			delete m_NextPos;
		m_NextPos = nullptr;
		delete m_TrajectoryTime;
	}

	/*
	 Method : GetPosition
	 Brief : Fonction qui retourne la variation de la position dans la trajectoire selon le temps
	 Params :
	 _Acceleration : AccŽlŽration appliquŽe ˆ la trajectoire
	 Return : Vecteur reprŽsentant la position au temps passŽ en paramtre
	 */
	void UpdatePosition(){
		if ((m_TrajectoryTime->getElapsedTime() >= 1) && (!m_boStop)){
			m_ActualPos->setX(m_NextPos->getX());
			m_ActualPos->setY(m_NextPos->getY());
			unsigned int dTimeVariation = m_TrajectoryTime->getElapsedTime();
			double DeltaT = 0.5 * dTimeVariation * dTimeVariation;
			double DeltaX = ((m_InitSpeed->getComposanteX()*dTimeVariation) + (DeltaT * m_Acceleration->getComposanteX()))/10000;
			double DeltaY = ((m_InitSpeed->getComposanteY()*dTimeVariation) + (DeltaT * m_Acceleration->getComposanteY()))/10000;
			m_NextPos->setX(m_ActualPos->getX() + DeltaX);
			if (rebonds <= 1)
				m_NextPos->setY(m_ActualPos->getY() + DeltaY);
			else{
				m_NextPos->setY(m_ActualPos->getY() - DeltaY);
			}

			m_ActualSpeed->setComposanteXY(m_InitSpeed->getComposanteX() + m_Acceleration->getComposanteX()/dTimeVariation,
										   m_InitSpeed->getComposanteY() + m_Acceleration->getComposanteY()/dTimeVariation);
		}
	}
	
	CPosition* getNextPos(){
		return m_NextPos;
	}
	
	void UpdateAcceleration(double _CompX, double _CompY){
		m_Acceleration->setComposanteXY(_CompX, _CompY);
	}
	
	void AddAcceleration(C2DVector* _Accel){
		m_Acceleration = m_Acceleration->operator+(_Accel);
	}
	
	/*
	 Method : GetInitSpeed
	 Brief : Fonction qui retourne la vitesse initiale
	 */
	C2DVector* GetInitSpeed(){
		return m_InitSpeed;
	}
	
	void setStratPos(int _X, int _Y){
		m_InitSpeed->setXYDebut(_X, _Y);
		m_ActualSpeed->setXYDebut(_X, _Y);
		m_Acceleration->setXYDebut(_X, _Y);
	}
	
	/*
	 Method : Bounce
	 Brief : ProcŽdure qui ajuste la trajectoire suite ˆ un rebond
	 Params :
	 _Slope : Angle de la pente du point d'impact (en degrŽs)
	 Discussion : Vitesse o le rebond n'arrive pas necessaire, ou ˆ vŽrifier ailleurs
	 Was googled, tout sur internet est vrai plz?
	 http://integraledesmaths.free.fr/idm/PagePrincipale.htm#http://integraledesmaths.free.fr/idm/GeoAPAngDro.htm
	 */
	void Bounce(double _Slope){
		

		double Slope1 = tan(_Slope);
		double Slope2 = tan(m_ActualSpeed->getOrientation());
		double AngleBetweenSlopes = atan((Slope1 - Slope2) / (1 + Slope1*Slope2));
		m_boStop = false;
		double tmpx = m_ActualSpeed->getComposanteX();
		double tmpy = m_ActualSpeed->getComposanteY();
		m_ActualSpeed->setComposanteXY(m_InitSpeed->getComposanteX() + m_Acceleration->getComposanteX()*m_TrajectoryTime->getElapsedTime(),
			(m_InitSpeed->getComposanteY() + m_Acceleration->getComposanteY()*m_TrajectoryTime->getElapsedTime()));

		if (_Slope == 0.0){
			m_InitSpeed->setComposanteXY(m_ActualSpeed->getComposanteX(), -m_ActualSpeed->getComposanteY());
		}
		else{
			m_InitSpeed->setComposanteXY(m_ActualSpeed->getComposanteX(), m_ActualSpeed->getComposanteY());
			if (m_ActualSpeed->getComposanteX() < 0){
				m_InitSpeed->setOrientation(m_InitSpeed->getOrientation()+5*M_PI/4);
			}
			else{
				m_InitSpeed->setOrientation(M_PI + m_InitSpeed->getOrientation() + (M_PI / 4 - AngleBetweenSlopes));
			}
			m_InitSpeed->setComposanteXY(m_InitSpeed->getComposanteX() / 1.3, m_InitSpeed->getComposanteY() / 1.3);
		}
		unsigned int dTimeVariation = m_TrajectoryTime->getElapsedTime();
		double DeltaT = 0.5 * dTimeVariation * dTimeVariation;
		double DeltaX = ((m_InitSpeed->getComposanteX()*dTimeVariation) + (DeltaT * m_Acceleration->getComposanteX())) / 10000;
		double DeltaY = ((m_InitSpeed->getComposanteY()*dTimeVariation) + (DeltaT * m_Acceleration->getComposanteY())) / 10000;

		m_NextPos->setXY(m_ActualPos->getX() + DeltaX,m_ActualPos->getY() + DeltaY);
		m_StartPos->setXY(m_ActualPos->getX(), m_ActualPos->getY());
		if (_Slope == 0.0)
			m_Acceleration->setComposanteXY(m_Acceleration->getComposanteX()/4, 1.6*m_Acceleration->getComposanteY());
		rebonds++;
	}
	
	/*
	 Method : GetActualPosition
	 Brief : Retourne la position actuelle (sans bouger)
	 */
	CPosition* GetActualPosition(){
		return m_ActualPos;
	}
	
	C2DVector* GetActualSpeed(){
		return m_ActualSpeed;
	}
	
	void WipeOut(){
		m_Acceleration->setNorme(0);
		m_InitSpeed->setNorme(0);
		m_ActualSpeed->setNorme(0);
	}
	
	void setSpeed(C2DVector* _Speed){
		delete m_InitSpeed;
		m_InitSpeed = _Speed;
		m_ActualSpeed->setComposanteXY(m_InitSpeed->getComposanteX(), m_InitSpeed->getComposanteY());
	}
	
	void Stop(){
		m_boStop = true;
	}
	
	void Restart(){
		m_boStop = false;
		m_TrajectoryTime->Start();
	}

	bool isStopped(){
		return m_boStop;
	}

	void setActualSpeed(C2DVector* _Speed){
		m_InitSpeed->setComposanteXY(_Speed->getComposanteX(), _Speed->getComposanteY());
		m_ActualSpeed->setComposanteXY(m_InitSpeed->getComposanteX(), m_InitSpeed->getComposanteY());
		delete _Speed;
		m_TrajectoryTime->Start();
		m_StartPos->setXY(m_ActualPos->getX(), m_ActualPos->getY());

	}

	void SetActualPos(int _X, int _Y){
		m_ActualPos->setX(_X);
		m_ActualPos->setY(_Y);
	}

	void SetInitSpeed(double _iX, double _iY){
		m_InitSpeed->setComposanteXY(_iX,_iY);
	}
	

	void SetAcceleration(double _iX, double _iY){
		m_Acceleration->setComposanteXY(_iX, _iY);
	}

	C2DVector* GetAcceleration(){
		return m_Acceleration;
	}

	double getSpeedMagnitude(){
		return m_ActualSpeed->getNorme();
	}
};