

/*
 Nom : CTrajectory
 Discussion : Classe reprŽsentant la trajectoire d'un point
 */


class CTrajectory{
private:
	CTimer* m_TrajectoryTime;
	CTimer* m_Test;
	CPosition* m_StartPos;
	C2DVector* m_InitSpeed;
	C2DVector* m_ActualSpeed;
	C2DVector* m_Acceleration;
	CPosition* m_ActualPos;
	CPosition* m_NextPos;
	bool m_boStop;
	bool m_boSliding;
	int rebonds;
public:
	int GetRebonds(){
		return rebonds;
	}

	CTimer* GetTest(){
		return m_Test;
	}
	CTrajectory(CPosition* _StartPos, C2DVector* _Speed, C2DVector* _Acc){
		m_boStop = false;
		m_boSliding = false;
		m_TrajectoryTime = new CTimer();
		m_Test = new CTimer();
		m_StartPos = _StartPos;
		m_InitSpeed = _Speed;
		m_ActualSpeed = _Speed;
		m_Acceleration = _Acc;
		m_ActualPos = new CPosition(m_StartPos->getX(),m_StartPos->getY());
		m_NextPos = new CPosition(m_ActualPos->getX(), m_ActualPos->getY());
		m_Acceleration->setComposanteXY(m_Acceleration->getComposanteX()/42, m_Acceleration->getComposanteY() / 42);
		m_TrajectoryTime->Start();
		m_Test->Start();
		rebonds = 0;
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
	 _Acceleration : AccŽlŽration appliquŽe ˆ la trajectoire
	 Return : Vecteur reprŽsentant la position au temps passŽ en paramtre
	 */
	void UpdatePosition(){
		double acttestx = m_ActualPos->getX();
		double acttesty = m_ActualPos->getY();
		double nextestx = m_NextPos->getX();
		double nextesty = m_NextPos->getY();
		double norm = m_ActualSpeed->getNorme();
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
			
			
				//Le code ci-dessous est pour la vitesse actuelle
				//	m_ActualSpeed->setComposanteXY((DeltaX + DeltaT * m_Acceleration->getComposanteX()) / dTimeVariation ,
				//	(DeltaY + DeltaT * m_Acceleration->getComposanteY()) / dTimeVariation );

			if (rebonds == 5){
				int i = 0;
			}



			//m_ActualSpeed->setComposanteXY(sqrt(m_InitSpeed->getComposanteX()*m_InitSpeed->getComposanteX()+2*m_Acceleration->getComposanteX()*(m_NextPos->getX() - m_ActualPos->getX())),
				//sqrt(m_InitSpeed->getComposanteY()*m_InitSpeed->getComposanteY() + 2 * m_Acceleration->getComposanteY()*(m_NextPos->getY() - m_ActualPos->getY())));


			//m_ActualSpeed->setComposanteXY(m_InitSpeed->getComposanteX() + m_Acceleration->getComposanteX()/dTimeVariation,
				//m_InitSpeed->getComposanteY() + m_Acceleration->getComposanteY()/dTimeVariation);
			

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
	 Brief : ProcŽdure qui ajuste la trajectoire suite ˆ un rebond
	 Params :
	 _Speed : Vitesse ˆ l'impact
	 _SlopeAngle : Angle de la pente du point d'impact (en degrŽs)
	 Discussion : Vitesse o le rebond n'arrive pas necessaire, ou ˆ vŽrifier ailleurs
	 Was googled, tout sur internet est vrai plz?
	 http://integraledesmaths.free.fr/idm/PagePrincipale.htm#http://integraledesmaths.free.fr/idm/GeoAPAngDro.htm
	 */
	void Bounce(double _Slope){
		if (rebonds == 3){
			int i = 0;
		}

		double Slope1 = tan(_Slope);
		double Slope2 = tan(m_ActualSpeed->getOrientation());
		double AngleBetweenSlopes = atan((Slope1 - Slope2) / (1 + Slope1*Slope2));

		m_boStop = false;
		m_boSliding = false;
		double tmpx = m_ActualSpeed->getComposanteX();
		double tmpy = m_ActualSpeed->getComposanteY();
		m_ActualSpeed->setComposanteXY(m_ActualSpeed->getComposanteX(),
			(m_InitSpeed->getComposanteY() + m_Acceleration->getComposanteY()*m_TrajectoryTime->getElapsedTime()));
		m_InitSpeed->setComposanteXY(m_ActualSpeed->getComposanteX(), -m_ActualSpeed->getComposanteY());
		
		unsigned int dTimeVariation = m_TrajectoryTime->getElapsedTime();
		double DeltaT = 0.5 * dTimeVariation * dTimeVariation;
		double DeltaX = ((m_InitSpeed->getComposanteX()*dTimeVariation) + (DeltaT * m_Acceleration->getComposanteX())) / 10000;
		double DeltaY = ((m_InitSpeed->getComposanteY()*dTimeVariation) + (DeltaT * m_Acceleration->getComposanteY())) / 10000;


		m_NextPos->setXY(m_ActualPos->getX() + DeltaX,
			m_ActualPos->getY() + DeltaY);
		m_StartPos->setXY(m_ActualPos->getX(), m_ActualPos->getY());

		m_Acceleration->setComposanteXY(m_Acceleration->getComposanteX() / 2, 1.6*m_Acceleration->getComposanteY());
		//if (rebonds > 0){
		//m_TrajectoryTime->Start();
		//}
		//m_TrajectoryTime->Start();
		if (rebonds == 1){
			int i = 0;
		}
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