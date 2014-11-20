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
public:
	//Constructeur...
	CTrajectory(C2DVector* _StartPos, C2DVector* _InitSpeed){
		m_lTrajectoryStartTime = SDL_GetTicks();
		m_StartPos = _StartPos;
		m_TrajectoryInitSpeed = _InitSpeed;
	}

	//Destructeur...
	~CTrajectory(){
		delete m_StartPos;
		delete m_TrajectoryInitSpeed;
	}

	/*
	Method : GetPosition
	Brief : Fonction qui retourne la variation de la position dans la trajectoire selon le temps
	Params :
	_time : Temps passé depuis le début de la trajectoire
	Return : Vecteur représentant la position au temps passé en paramètre
	*/
	C2DVector GetPosition(){
		double dTimeVariation = (SDL_GetTicks() - m_lTrajectoryStartTime);
		double dTimeVarExp2 = dTimeVariation * dTimeVariation;
		C2DVector Position = C2DVector(m_TrajectoryInitSpeed->getX() * dTimeVariation + CPhysics::GetWind()->getX()
			/ 2 * dTimeVarExp2 + m_StartPos->getX(),
			m_TrajectoryInitSpeed->getY() * dTimeVariation + (CPhysics::GetWind()->getY() + CPhysics::GetGravity())
			/ 2 * dTimeVarExp2 + m_StartPos->getY());
		return Position;
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
	void Bounce(C2DVector _Speed, double _Slope, C2DVector _Pos, int _Direction){
		//delete m_StartPos;
		//double Angle = acos(_Slope * _Pos.getX() / sqrt(_Speed.getX()*_Speed.getX() + _Speed.getY()*_Speed.getY()));
		//_Pos.setX(_Pos.getX() * )
		//m_StartPos = new C2DVector(_Pos);
		//m_TrajectoryInitSpeed = _InitSpeed;
		//m_lTrajectoryStartTime = SDL_GetTicks();
	}

	/*
	Method : GetSpeed
	Brief : Fonction qui retourne la vitesse actuelle
	Discussion: MRUA : Vf^2 - Vi^2 = 2(xf-xi)*a
	*/
	C2DVector GetSpeed(){
		return C2DVector(
			sqrt(2 *(GetPosition().getX() - m_StartPos->getX())* CPhysics::GetWind()->getX()),
			sqrt(2 * (GetPosition().getY() - m_StartPos->getY())* (CPhysics::GetWind()->getY() + CPhysics::GetGravity()))
			);
	}
};