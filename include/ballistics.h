// GNU Ballistics Library
// Originally created by Derek Yates
// Now available free under the GNU GPL
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef __lib_ballistics__
#define __lib_ballistics__
#define __BCOMP_MAXRANGE__ 50001
#define GRAVITY (-32.194)


enum __DragFunctions {G0 = 0, G1, G2, G3, G4, G5, G6, G7, G8};
#include <math.h>
#include <stdlib.h>

#include "internal.h" // Internal use functions


double ZeroAngle (int DragFunction, double DragCoefficient, double Vi, double SightHeight, double ZeroRange, double yIntercept);
/*  Arguments:
		DragFunction:  The drag function to use (G0, G1, G2, G5, G6, G7, G8)
		DragCoefficient:  The coefficient of drag for the projectile, for the supplied drag function.
		Vi:  The initial velocity of the projectile, in feet/s
		SightHeight:  The height of the sighting system above the bore centerline, in inches.
					  Most scopes fall in the 1.6 to 2.0 inch range.
		ZeroRange:  The range in yards, at which you wish the projectile to intersect yIntercept.
		yIntercept:  The height, in inches, you wish for the projectile to be when it crosses ZeroRange yards.
					This is usually 0 for a target zero, but could be any number.  For example if you wish
					to sight your rifle in 1.5" high at 100 yds, then you would set yIntercept to 1.5, and ZeroRange to 100

	Return Value:
		Returns the angle of the bore relative to the sighting system, in degrees.
*/



// A function to correct a "standard" Drag Coefficient for differing atmospheric conditions.
// Returns the corrected drag coefficient for supplied drag coefficient and atmospheric conditions.
double AtmCorrect (double DragCoefficient, double Altitude, double Barometer, double Temperature, double RelativeHumidity);
/* Arguments:
		DragCoefficient:  The coefficient of drag for a given projectile.
		Altitude:  The altitude above sea level in feet.  Standard altitude is 0 feet above sea level.
		Barometer:  The barometric pressure in inches of mercury (in Hg).
					This is not "absolute" pressure, it is the "standardized" pressure reported in the papers and news.
					Standard pressure is 29.53 in Hg.
		Temperature:  The temperature in Fahrenheit.  Standard temperature is 59 degrees.
		RelativeHumidity:  The relative humidity fraction.  Ranges from 0.00 to 1.00, with 0.50 being 50% relative humidity.
							Standard humidity is 78%

	Return Value:
		The function returns a ballistic coefficient, corrected for the supplied atmospheric conditions.
*/


// A function to generate a ballistic solution table in 1 yard increments, up to __BCOMP_MAXRANGE__.
// Source is in "_solve.c"
int SolveAll (int DragFunction, double DragCoefficient, double Vi, double SightHeight, \
              double ShootingAngle, double ZeroAngle, double WindSpeed, double WindAngle, double **Solution);
/* Arguments:
		DragFunction:  The drag function you wish to use for the solution (G1, G2, G5, G6, G7, or G8)
		DragCoefficient:  The coefficient of drag for the projectile you wish to model.
		Vi:  The projectile initial velocity.
		SightHeight:  The height of the sighting system above the bore centerline.
						Most scopes are in the 1.5"-2.0" range.
		ShootingAngle:  The uphill or downhill shooting angle, in degrees.  Usually 0, but can be anything from
						90 (directly up), to -90 (directly down).
		ZeroAngle:  The angle of the sighting system relative to the bore, in degrees.  This can be easily computed
					using the ZeroAngle() function documented above.
		WindSpeed:  The wind velocity, in mi/hr
		WindAngle:  The angle at which the wind is approaching from, in degrees.
					0 degrees is a straight headwind
					90 degrees is from right to left
					180 degrees is a straight tailwind
					-90 or 270 degrees is from left to right.
		Solution:	A pointer provided for accessing the solution after it has been generated.
					Memory for this pointer is allocated in the function, so the user does not need
					to worry about it.  This solution can be passed to the retrieval functions to get
					useful data from the solution.
	Return Value:
					This function returns an integer representing the maximum valid range of the
					solution.  This also indicates the maximum number of rows in the solution matrix,
					and should not be exceeded in order to avoid a memory segmentation fault.

*/

// Functions for retrieving data from a solution generated with SolveAll()
double GetRange (double *sln, int yardage); // Returns range, in yards.
double GetPath (double *sln, int yardage); // Returns projectile path, in inches, relative to the line of sight.
double GetMOA (double *sln, int yardage); // Returns an estimated elevation correction for achieving a zero at this range.
// this is useful for "click charts" and the like.
double GetTime (double *sln, int yardage); // Returns the projectile's time of flight to this range.
double GetWindage (double *sln, int yardage); // Returns the windage correction in inches required to achieve zero at this range.
double GetWindageMOA (double *sln, int yardage); // Returns an approximate windage correction in MOA to achieve a zero at this range.
double GetVelocity (double *sln, int yardage); // Returns the projectile's total velocity (Vector product of Vx and Vy)
double GetVx (double *sln, int yardage); // Returns the velocity of the projectile in the bore direction.
double GetVy (double *sln, int yardage); // Returns the velocity of the projectile perpendicular to the bore direction.

// For very steep shooting angles, Vx can actually become what you would think of as Vy relative to the ground,
// because Vx is referencing the bore's axis.  All computations are carried out relative to the bore's axis, and
// have very little to do with the ground's orientation.


// A helper function for finding the PBR for a cartridge.
int pbr (int DragFunction, double DragCoefficient, double Vi, double SightHeight, double VitalSize, int SightinYards, int *oresult);
/* Arguments:
		DragFunction:  The drag function you wish to use for the solution (G1, G2, G5, G6, G7, or G8)
		DragCoefficient:  The coefficient of drag for the projectile you wish to model.
		Vi:  The projectile initial velocity.
		SightHeight:  The height of the sighting system above the bore centerline.
						Most scopes are in the 1.5"-2.0" range.
		VitalSize:  Diameter of the circle representing the vitals and/or target rings
		SightinYards: Distance to sight-in target

		oresult:	A pointer provided for accessing the solution after it has been generated.

	Return Value: 	0 if successful
					oresult[0]= Near Zero
					oresult[1]= Far zero
					oresult[2]= Minimum PBR
					oresult[3]= Maximum PBR
					oresult[4]= Sight-in height (in 100ths of an inch)
*/
#endif



