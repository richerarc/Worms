#include <math.h>

/*
Nom : CTrajectory
Discussion : Classe représentant la trajectoire d'un point
*/


class CTrajectory{
private:
	long m_lTrajectoryStartTime;
	C2DVector* m_StartPos;
	C2DVector* m_TrajectoryInitSpeed;
	C2DVector* m_Acceleration;
	C2DVector* m_ActualPos;
	C2DVector* m_LastPos;
public:
	//Constructeur...
	CTrajectory(C2DVector* _StartPos, C2DVector* _InitSpeed, C2DVector* _Acc){
		m_lTrajectoryStartTime = SDL_GetTicks();
		m_StartPos = _StartPos;
		m_TrajectoryInitSpeed = _InitSpeed;
		m_Acceleration = _Acc;
		m_ActualPos = m_StartPos;
		m_LastPos = new C2DVector(m_ActualPos->getX(), m_ActualPos->getY());
	}

	//Destructeur...
	~CTrajectory(){
		delete m_StartPos;
		delete m_TrajectoryInitSpeed;
		delete m_Acceleration;
		delete m_ActualPos;
		delete m_LastPos;
	}

	/*
	Method : GetPosition
	Brief : Fonction qui retourne la variation de la position dans la trajectoire selon le temps
	Params :
	_Acceleration : Accélération appliquée à la trajectoire
	Return : Vecteur représentant la position au temps passé en paramètre
	*/
	C2DVector* UpdatePosition(){
		/*
		delete m_LastPos;
		C2DVector Tmp(m_ActualPos->getX(),m_ActualPos->getY());

		m_LastPos = new C2DVector(Tmp);
		*/
		m_LastPos->setX(m_ActualPos->getX());
		m_LastPos->setY(m_ActualPos->getY());
		double dTimeVariation = (SDL_GetTicks() - m_lTrajectoryStartTime);
		//double dTimeVarExp2 = dTimeVariation * dTimeVariation;
		m_ActualPos->setX(m_TrajectoryInitSpeed->getX() * dTimeVariation + m_Acceleration->getX()
			/ 2 * dTimeVariation + m_StartPos->getX());
		m_ActualPos->setY(m_TrajectoryInitSpeed->getY() * dTimeVariation + m_Acceleration->getY()
			/ 2 * dTimeVariation + m_StartPos->getY());
		return m_ActualPos;
	}
	/*
	C2DVector* GetPosition(){
		if (m_LastPos != nullptr)
			delete m_LastPos;
		m_LastPos = m_ActualPos;
		
		delete m_LastPos;
		C2DVector Tmp(m_ActualPos->getX(),m_ActualPos->getY());

		m_LastPos = new C2DVector(Tmp);
		

	double dTimeVariation = (SDL_GetTicks() - m_lTrajectoryStartTime);

	C2DVector Tmp(m_TrajectoryInitSpeed->getX() * dTimeVariation + m_Acceleration->getX()
		/ 2 * dTimeVariation + m_StartPos->getX(), m_TrajectoryInitSpeed->getY() * dTimeVariation + m_Acceleration->getY()
		/ 2 * dTimeVariation + m_StartPos->getY());

	//double dTimeVarExp2 = dTimeVariation * dTimeVariation;
	m_ActualPos = new C2DVector(Tmp);
	return Tmp;
}
	*/






	/*
	Method : GetSpeed
	Brief : Fonction qui retourne la vitesse actuelle
	Discussion: MRUA : Vf^2 - Vi^2 = 2(xf-xi)*a
	*/
	C2DVector GetSpeed(){
		C2DVector* TmpPos = UpdatePosition();
		return C2DVector(
			sqrt(2 * (TmpPos->getX() - m_StartPos->getX())* m_Acceleration->getX()),
			sqrt(2 * (TmpPos->getY() - m_StartPos->getY())* m_Acceleration->getY())
			);
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
	void Bounce(double _Slope, C2DVector _Pos, int _Direction){
		//double Angle = acos(_Slope * _Pos.getX() / sqrt(_Speed.getX()*_Speed.getX() + _Speed.getY()*_Speed.getY()));
		//_Pos.setX(_Pos.getX() * )
		/*
		double AngleA = atan(_Slope);
		C2DVector ImpactSpeed = GetSpeed();
		double TrajSlope = sqrt(ImpactSpeed.getX()*ImpactSpeed.getX() + ImpactSpeed.getY()*ImpactSpeed.getY());
		double AngleB = 
		delete m_StartPos;
		m_StartPos = new C2DVector(_Pos);
		//m_TrajectoryInitSpeed = _InitSpeed;
		m_lTrajectoryStartTime = SDL_GetTicks();
		*/
	}

	/*
	Method : GetLastPosition
	Brief : Retourne la position précédente
	*/
	C2DVector* GetLastPosition(){
		return m_LastPos;
	}

	/*
	Method : GetActualPosition
	Brief : Retourne la position actuelle (sans bouger)
	*/
	C2DVector* GetActualPosition(){
		return m_ActualPos;
	}
};