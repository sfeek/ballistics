// Angular conversion functions to make things a little easier. 
// Source is in _angle.c
double DegtoMOA(double deg); // Converts degrees to minutes of angle
double DegtoRad(double deg); // Converts degrees to radians
double MOAtoDeg(double moa); // Converts minutes of angle to degrees
double MOAtoRad(double moa); // Converts minutes of angle to radians
double RadtoDeg(double rad); // Converts radians to degrees
double RadtoMOA(double rad); // Converts radiants to minutes of angle


// A function to calculate ballistic retardation values based on standard drag functions.
double retard(int DragFunction, double DragCoefficient, double Vi);
/* Arguments:
		DragFunction:  G1, G2, G3, G4, G5, G6, G7, or G8.  All are enumerated above.
		DragCoefficient:  The coefficient of drag for the projectile for the given drag function.
		Vi:  The Velocity of the projectile.
	
	Return Value: 
		The function returns the projectile drag retardation velocity, in ft/s per second.
		
*/




// A function to compute the windage deflection for a given crosswind speed,
// given flight time in a vacuum, and given flight time in real life.
// Returns the windage correction needed in inches.
// Source is in "_windage.c"
double Windage(double WindSpeed, double Vi, double x, double t);
/* Arguments:
		WindSpeed:  The wind velocity in mi/hr.
		Vi:  The initial velocity of the projectile (muzzle velocity).
		x:  The range at which you wish to determine windage, in feet.
		t:  The time it has taken the projectile to traverse the range x, in seconds.
	
	Return Value:
		Returns the amount of windage correction, in inches, required to achieve zero on a target at the given range.
		
*/

// Functions to resolve any wind / angle combination into headwind and crosswind components.
// Source is in "_windage.c"
double HeadWind(double WindSpeed, double WindAngle);
double CrossWind(double WindSpeed, double WindAngle);
/* Arguments:
		WindSpeed:  The wind velocity, in mi/hr.
		WindAngle:  The angle from which the wind is coming, in degrees.
					0 degrees is from straight ahead
					90 degrees is from right to left
					180 degrees is from directly behind
					270 or -90 degrees is from left to right.
	
	Return value:
		Returns the headwind or crosswind velocity component, in mi/hr.
*/



// A function to determine the bore angle needed to achieve a target zero at Range yards
// (at standard conditions and on level ground.)
// Source is in "_zero.c"

