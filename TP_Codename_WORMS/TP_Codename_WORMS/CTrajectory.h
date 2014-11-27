

/*
Nom : CTrajectory
Discussion : Classe représentant la trajectoire d'un point
*/


class CTrajectory{
private:
	CTimer* m_TrajectoryTime;
	CPosition* m_StartPos;
	C2DVector* m_Speed;
	C2DVector* m_Acceleration;
	CPosition* m_ActualPos;
	CPosition* m_NextPos;
	static bool m_boPause;
public:
	//Constructeur...
	CTrajectory(CPosition* _StartPos, C2DVector* _Speed, C2DVector* _Acc){
		m_TrajectoryTime = new CTimer();
		m_StartPos = _StartPos;
		m_Speed = _Speed;
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
		if (m_Speed)
			delete m_Speed;
		m_Speed = nullptr;
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
	CPosition* UpdatePosition(){
		if (!m_boPause){
			m_TrajectoryTime->UnPause();
			m_ActualPos->setX(m_NextPos->getX());
			m_ActualPos->setY(m_NextPos->getY());
			unsigned int dTimeVariation = m_TrajectoryTime->getElapsedTime();
			double DeltaT = 0.5 * dTimeVariation * dTimeVariation;
			double DeltaX = ((m_Speed->getComposanteX() * dTimeVariation) + (DeltaT * m_Acceleration->getComposanteX())) /100000;
			double DeltaY = ((m_Speed->getComposanteY() * dTimeVariation) + (DeltaT * m_Acceleration->getComposanteY())) /100000;
			m_NextPos->setX(m_ActualPos->getX() + DeltaX);
			m_NextPos->setY(m_ActualPos->getY() + DeltaY);
			
		}
		else
			m_TrajectoryTime->Pause();
		return m_ActualPos;
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
	Method : GetSpeed
	Brief : Fonction qui retourne la vitesse actuelle
	Discussion: MRUA : Vf^2 - Vi^2 = 2(xf-xi)*a
	*/
	C2DVector* GetSpeed(){
		return m_Speed;
	}

	/*
	Method : Bounce
	Brief : Procédure qui ajuste la trajectoire suite à un rebond
	Params :
	_Speed : Vitesse à l'impact
	_Slope : Pente du point d'impact
	_Pos : Position de l'impact
	_Direction : Indique si le projectile vient d'en haut ou d'en bas
	*/
	void Bounce(double _Slope, CPosition _Pos, int _Direction){
		//double Angle = acos(_Slope * _Pos.getX() / sqrt(_Speed.getX()*_Speed.getX() + _Speed.getY()*_Speed.getY()));
		//_Pos.setX(_Pos.getX() * )
		/*
		double AngleA = atan(_Slope);
		CPosition ImpactSpeed = GetSpeed();
		double TrajSlope = sqrt(ImpactSpeed.getX()*ImpactSpeed.getX() + ImpactSpeed.getY()*ImpactSpeed.getY());
		double AngleB = 
		delete m_StartPos;
		m_StartPos = new CPosition(_Pos);
		//m_TrajectoryInitSpeed = _InitSpeed;
		m_lTrajectoryStartTime = SDL_GetTicks();
		*/
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
};


bool CTrajectory::m_boPause = false;