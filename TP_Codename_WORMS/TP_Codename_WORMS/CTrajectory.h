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
		return C2DVector(m_TrajectoryInitSpeed->getX() * dTimeVariation + m_Wind->getX()
			/ 2 * dTimeVariation * dTimeVariation + m_StartPos->getX(),
			m_TrajectoryInitSpeed->getY() * dTimeVariation + (m_Wind->getY() - CPhysics::GetGravity())
			/ 2 * dTimeVariation * dTimeVariation + m_StartPos->getY()
			);
	}

};