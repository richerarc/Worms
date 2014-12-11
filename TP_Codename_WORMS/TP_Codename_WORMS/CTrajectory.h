

/*
Nom : CTrajectory
Discussion : Classe représentant la trajectoire d'un point
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
	bool m_boSliding;
public:
	//Constructeur...
	CTrajectory(CPosition* _StartPos, C2DVector* _Speed, C2DVector* _Acc){
		m_boStop = false;
		m_boSliding = false;
		m_TrajectoryTime = new CTimer();
		m_StartPos = _StartPos;
		m_InitSpeed = _Speed;
		m_ActualSpeed = _Speed;
		m_Acceleration = _Acc;
		m_ActualPos = m_StartPos;
		m_NextPos = new CPosition(m_ActualPos->getX(), m_ActualPos->getY());
		m_TrajectoryTime->Start();
	}

	//Destructeur...
	~CTrajectory(){
		if (m_StartPos){
			if (m_ActualPos == m_StartPos)
				m_ActualPos = nullptr;
			else
				delete m_ActualPos;
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
	_Acceleration : Accélération appliquée à la trajectoire
	Return : Vecteur représentant la position au temps passé en paramètre
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
			m_NextPos->setY(m_ActualPos->getY() + DeltaY);
			
			m_ActualSpeed->setComposanteXY(m_InitSpeed->getComposanteX() + m_Acceleration->getComposanteX()/dTimeVariation,
				m_InitSpeed->getComposanteY() + m_Acceleration->getComposanteY()/dTimeVariation);
			

			//Le code ci-dessous est pour la vitesse actuelle
			//m_ActualSpeed->setComposanteXY((DeltaX + DeltaT * m_Acceleration->getComposanteX()) / dTimeVariation ,
				//(DeltaY + DeltaT * m_Acceleration->getComposanteY()) / dTimeVariation );
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
	Brief : Procédure qui ajuste la trajectoire suite à un rebond
	Params :
	_Speed : Vitesse à l'impact
	_SlopeAngle : Angle de la pente du point d'impact (en degrés)
	Discussion : Vitesse où le rebond n'arrive pas necessaire, ou à vérifier ailleurs
	Was googled, tout sur internet est vrai plz?
	http://integraledesmaths.free.fr/idm/PagePrincipale.htm#http://integraledesmaths.free.fr/idm/GeoAPAngDro.htm
	*/
	void Bounce(double _Slope){
		double Slope1 = tan(_Slope);
		double Slope2 = tan(m_ActualSpeed->getOrientation());
		double AngleBetweenSlopes = atan((Slope1 - Slope2) / (1 + Slope1*Slope2));
		//if (m_ActualSpeed->getOrientation() > M_PI/2)
		//m_ActualSpeed->setOrientation(2 * (M_PI / 2 - _Slope) + AngleBetweenSlopes);
		//else
		if (_Slope == 0.0){
			m_ActualSpeed->setOrientation(- m_ActualSpeed->getOrientation());//done
		}
		else{
			if (_Slope < 0.0){
				m_ActualSpeed->setOrientation(AngleBetweenSlopes + M_PI); //done
			}
			else {
				m_ActualSpeed->setOrientation(AngleBetweenSlopes);
			}
		}
		m_InitSpeed->setComposanteXY(30 * m_ActualSpeed->getComposanteX(), 30 * m_ActualSpeed->getComposanteY());
		m_StartPos->setXY(m_ActualPos->getX(), m_ActualPos->getY());
		m_InitSpeed->setDOUBLE_XY_START(m_StartPos->getX(), m_StartPos->getY());
		delete m_NextPos;
		m_NextPos = new CPosition(m_ActualPos->getX(), m_ActualPos->getY());
		m_TrajectoryTime->Start();
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
	
	bool IsSliding(){
		return m_boSliding;
	}

	void StartSlide(){
		m_boSliding = true;
	}

	void StopSlide(){
		m_boSliding = false;
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
	
};