

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
	static bool m_boPause;
public:
	//Constructeur...
	CTrajectory(CPosition* _StartPos, C2DVector* _Speed, C2DVector* _Acc){
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
		CTrajectory::UnPause();
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
		if (!m_boPause){
			m_TrajectoryTime->UnPause();
			m_ActualPos->setX(m_NextPos->getX());
			m_ActualPos->setY(m_NextPos->getY());
			unsigned int dTimeVariation = m_TrajectoryTime->getElapsedTime();
			double DeltaT = 0.5 * dTimeVariation * dTimeVariation;
			double DeltaX = ((m_InitSpeed->getComposanteX() * dTimeVariation) + (DeltaT * m_Acceleration->getComposanteX())) /100000;
			double DeltaY = ((m_InitSpeed->getComposanteY() * dTimeVariation) + (DeltaT * m_Acceleration->getComposanteY())) /100000;
			m_NextPos->setX(m_ActualPos->getX() + DeltaX);
			m_NextPos->setY(m_ActualPos->getY() + DeltaY);


			//Le code ci-dessous est pour la vitesse actuelle
			m_ActualSpeed->setComposanteXY((DeltaX + DeltaT * m_Acceleration->getComposanteX())/dTimeVariation,
				(DeltaY + DeltaT * m_Acceleration->getComposanteY()) / dTimeVariation);
			
		}
		else
			m_TrajectoryTime->Pause();
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

	/*
	Method : Bounce
	Brief : Procédure qui ajuste la trajectoire suite à un rebond
	Params :
	_Speed : Vitesse à l'impact
	_SlopeAngle : Angle de la pente du point d'impact (en degrés)
	*/
	void Bounce(double _Slope){
		double SlopeAngle = DegToRad(_Slope);
		if (SlopeAngle - M_PI / 2 == m_ActualSpeed->getOrientation() || SlopeAngle + M_PI / 2 == m_ActualSpeed->getOrientation()){
			m_ActualSpeed->setOrientation(m_ActualSpeed->getOrientation() + M_PI);
		}
	}
	
	/*
	Method : GetActualPosition
	Brief : Retourne la position actuelle (sans bouger)
	*/
	CPosition* GetActualPosition(){
		return m_ActualPos;
	}
	
    static void Pause(){
		m_boPause = true;
	}
	
	static void UnPause(){
		m_boPause = false;
	}

	void WipeOut(){
		m_Acceleration->setNorme(0);
		m_Speed->setNorme(0);
	}
};


bool CTrajectory::m_boPause = false;