#include <stdio.h>
#include <stdlib.h>
#include "bclib.h"
#include "ballistics.h"

int ballistic_coefficient(void)
{
	char buffer[80];
	double dc,iv,at,tp,bp,rh,tv;
	double drv,drd,md;
	double guess_current,guess_high,guess_low;
	int atm,df;
	double* sln=NULL;
	
	printf("\n\n\t * Ballistic Coefficient Calculator * \n");
	
	while(1)
	{
		printf("\nEnter Muzzle Velocity (ft/s) : ");
		sgets(buffer,80);
		iv = atof(buffer);
		if (iv > 0) break;
		printf("Muzzle Velocity must be > 0!\n");
	}
	
	while(1)
	{
		printf("\nEnter Down Range Velocity (ft/s) : ");
		sgets(buffer,80);
		drv = atof(buffer);
		if (drv > 0 || drv < iv) break;
		printf("Down Range Velocity must be > 0 and < Muzzle Velocity!\n");
	}
	
	while(1)
	{
		printf("\nEnter Down Range Distance (yds) : ");
		sgets(buffer,80);
		drd = atof(buffer);
		if (drd > 0) break;
		printf("Down Range Distance must be > 0!\n");
	}
	
	while(1)
	{
		printf("\n");
		printf("G0 Roundball\n");
		printf("G1 Ingalls (by far the most popular)\n");
		printf("G2 (Aberdeen J projectile)\n");
		printf("G5 (short 7.5deg boat-tail, 6.19 calibers long tangent ogive)\n");
		printf("G6 (flatbase, 6 calibers long secant ogive)\n");
		printf("G7 (long 7.5deg boat-tail, 10 calibers tangent ogive)\n");
		printf("G8 (flatbase, 10 calibers long secant ogive)\n");
		
		
		printf("\nEnter Drag Model 0,1,2,5,6,7 or 8 : ");
		sgets(buffer,80);
		df = atoi(buffer);
		if (df == 0) break;
		if (df == 1) break;
		if (df == 2) break;
		if (df == 5) break;
		if (df == 6) break;
		if (df == 7) break;
		if (df == 8) break;
		printf("Drag Model must be 0,1,2,5,6,7 or 8!\n");
	}
	
	atm = 0;
	
	printf("\nCorrect for Atmospheric Conditions (Y/N) : ");
	sgets(buffer,80);
	if (buffer[0] == 'Y' || buffer[0] == 'y')
	{
		atm = 1;
		while(1)
		{
			printf("\nEnter Altitude (ft) : ");
			sgets(buffer,80);
			at = atof(buffer);
			if (at >= 0) break;
			printf("Altitude must be >= 0!\n");
		}

		while(1)
		{
			printf("\nEnter Temperature (F) : ");
			sgets(buffer,80);
			tp = atof(buffer);
			if (tp > -100) break;
			printf("Temperature must be > -100 deg!\n");
		}

		while(1)
		{
			printf("\nEnter Barometric Pressure (in Hg) : ");
			sgets(buffer,80);
			bp = atof(buffer);
			if (bp > 20 && bp < 35) break;
			printf("Barometric Pressure must be > 20 and < 35!\n");
		}

		while(1)
		{
			printf("\nEnter Relative Humidity (%%) : ");
			sgets(buffer,80);
			rh = atof(buffer)/100;
			if (rh >= 0 && rh <= 100) break;
			printf("Relative Humidity must be between 0 and 100%%!\n");
		}
	}
	
	guess_current = 0.5;
	guess_low = 0.0;
	guess_high = 2.0;
		
	while(1)
	{
		dc = guess_current;
		
		if (atm == 1) dc = AtmCorrect(dc, at, bp, tp, rh);
		
		sln=NULL;
		
		md = SolveAll(df,dc, iv, 0, 0, 0, 0, 0, &sln);
		tv = GetVelocity(sln,drd);
				
		if (fabs(tv-drv) < 2) break;
		
		if (tv > drv)
		{
			guess_high = guess_current;
			guess_current = (guess_current + guess_low) / 2;
		}
		else
		{
			guess_low = guess_current;
			guess_current = (guess_current + guess_high) / 2;
		}
	}
	printf("\n\n G%d BC = %3.3f\n\n",df,guess_current);
	return 0;		
}
	

int trajectory (void)
{
	char buffer[80];
	
	double dc,pw,iv,zr,sh,sa,wv,wa,at,tp,bp,rh,za,tv,cl,vcl,hcl,vd;
	double vmoa,vmils,hmoa,hmils;
	int md,mr,df,yi,x;
	double* sln=NULL;
	int spbr[5];
	int scope;
	
	printf("\n\n\t * Trajectory Calculator * \n");
	
	while(1)
	{
		printf("\nEnter Ballistic Coefficient : ");
		sgets(buffer,80);
		dc = atof(buffer);
		if (dc > 0 && dc < 2) break;
		printf("Ballistic Coefficient must > 0 and < 2!\n");
	}
	
	while(1)
	{
		printf("\n");
		printf("G0 Roundball\n");
		printf("G1 Ingalls (by far the most popular)\n");
		printf("G2 (Aberdeen J projectile)\n");
		printf("G5 (short 7.5deg boat-tail, 6.19 calibers long tangent ogive)\n");
		printf("G6 (flatbase, 6 calibers long secant ogive)\n");
		printf("G7 (long 7.5deg boat-tail, 10 calibers tangent ogive)\n");
		printf("G8 (flatbase, 10 calibers long secant ogive)\n");
		
		
		printf("\nEnter Drag Model 0,1,2,5,6,7 or 8 : ");
		sgets(buffer,80);
		df = atoi(buffer);
		if (df == 0) break;
		if (df == 1) break;
		if (df == 2) break;
		if (df == 5) break;
		if (df == 6) break;
		if (df == 7) break;
		if (df == 8) break;
		printf("Drag Model must be 0,1,2,5,6,7 or 8!\n");
	}
		
	while(1)
	{
		printf("\nEnter Bullet Weight (gr) : ");
		sgets(buffer,80);
		pw = atof(buffer);
		if (pw >= 1) break;
		printf("Bullet Weight must be >= 1 grain!\n");
	}
	
	while(1)
	{
		printf("\nEnter Muzzle Velocity (ft/s) : ");
		sgets(buffer,80);
		iv = atof(buffer);
		if (iv > 0) break;
		printf("Muzzle Velocity must be > 0!\n");
	}
	
	while(1)
	{
		printf("\nEnter Zero Range (yds) : ");
		sgets(buffer,80);
		zr = atof(buffer);
		if (zr >= 1) break;
		printf("Zero Range must be >= 1 yard!\n");
	}
	
	while(1)
	{
		printf("\nEnter Sight Height Above Bore (in) : ");
		sgets(buffer,80);
		sh = atof(buffer);
		if (sh > 0) break;
		printf("Sight Height must be > 0!\n");
	}

	while(1)
	{
		printf("\nEnter Shooting Angle (deg)  ");
		printf("\n\t+90\n");
		printf("\t 0 \n");
		printf("\t-90\n :");
		sgets(buffer,80);
		sa = atof(buffer);
		if (sa >= -90 && sa <= 90) break;
		printf("Shooting Angle must be between -90 and +90!\n");
	}
	
	while(1)
	{
		printf("\nEnter Wind Velocity (mph) : ");
		sgets(buffer,80);
		wv = atof(buffer);
		if (wv >= 0) break;
		printf("Wind Velocity cannot be < 0!\n");
	}
	
	while(1)
	{
		printf("\nEnter Wind Angle is Coming From (0-360 deg)");
		printf("\n\t 0\n");
		printf("270\t\t90\n");
		printf("\t180\n :");
		sgets(buffer,80);
		wa = atof(buffer);
		if (wa >= 0 && wa <= 360) break;
		printf("Wind Angle must be between 0 and 360 deg!\n");
	}

	printf("\nScope (Y/N) : ");
	sgets(buffer,80);
	scope = 0;
	if (buffer[0] == 'Y' || buffer[0] == 'y')
	{
		while(1)
		{	
			printf("\nEnter # Clicks to Move Scope 1 inch @ 100 yrds : ");
			sgets(buffer,80);
			cl = atof(buffer);
			if (cl >= 0) break;
			printf("# Clicks must not be < 0!\n");
		}
		scope = 1;	
	}

	while(1)
	{
		printf("\nEnter Vitals Diameter (in): ");
		sgets(buffer,80);
		vd = atof(buffer);
		if (vd >= 1) break;
		printf("Vitals Diameter must be at least 1 inch!\n");
	}
		
	printf("\nCorrect for Atmospheric Conditions (Y/N) : ");
	sgets(buffer,80);
	if (buffer[0] == 'Y' || buffer[0] == 'y')
	{
		while(1)
		{
			printf("\nEnter Altitude (ft) : ");
			sgets(buffer,80);
			at = atof(buffer);
			if (at >= 0) break;
			printf("Altitude must be >= 0!\n");
		}

		while(1)
		{
			printf("\nEnter Temperature (F) : ");
			sgets(buffer,80);
			tp = atof(buffer);
			if (tp > -100) break;
			printf("Temperature must be > -100 deg!\n");
		}

		while(1)
		{
			printf("\nEnter Barometric Pressure (in Hg) : ");
			sgets(buffer,80);
			bp = atof(buffer);
			if (bp > 20 && bp < 35) break;
			printf("Barometric Pressure must be > 20 and < 35!\n");
		}

		while(1)
		{
			printf("\nEnter Relative Humidity (%%) : ");
			sgets(buffer,80);
			rh = atof(buffer)/100;
			if (rh >= 0 && rh <= 100) break;
			printf("Relative Humidity must be between 0 and 100%%!\n");
		}
		
		dc = AtmCorrect(dc, at, bp, tp, rh);
	}
	
	za = ZeroAngle(df, dc, iv, sh, zr, 0.0);
		
	md = SolveAll(df, dc, iv, sh, sa, za, wv, wa, &sln);
	
	while(1)
	{
		printf("\nEnter Maximum Range (yds) up to %d yds for Table : ",md);
		sgets(buffer,80);
		mr = atoi(buffer);
		if (mr > 0 && mr < md) break;
		printf("Maximum Table Range must be > 0 and < %d yds!\n",md);
	}
	
	while(1)
	{
		printf("\nEnter Yardage Increment (yds) for Table : ");
		sgets(buffer,80);
		yi = atoi(buffer);
		if (yi >= 1 && yi < md) break;
		printf("Yardage Increment must be between 1 and %d yds!\n",md);
	}
	
	pbr(df, dc, iv, sh, vd, zr, spbr);
	
	printf("\n\n\t * Ballistic Information * \n");
	printf("\nFinal Ballistic Coefficient: %3.3f\n", dc);
	printf("Ballistic Model: G%d\n",df);
	printf("Muzzle Velocity: %3.0f fps\n",iv);
	printf("Muzzle Energy: %3.0f ft/lb\n",(pw * iv * iv)/450436);
	printf("Absolute Maximum Range: %d yds\n",md);
	printf("Zero Range: %3.0f yds\n",zr);
	printf("Shooting Angle: %3.1f deg\n",sa);
	if (spbr[4]/100.0 >= 0)
		printf("\n\nPBR Sight in for %3.0f yds: %3.1f in high\n",zr,fabs(spbr[4]/100.0));
	else
		printf("\n\nPBR Sight in for %3.0f yds: %3.1f in low\n",zr,fabs(spbr[4]/100.0));
	printf("\tPBR Vital Area Diameter: %3.1f in\n",vd);
	printf("\tPBR Near Zero: %d yds\n",spbr[0]);
	printf("\tPBR Far Zero: %d yds\n", spbr[1]);
	printf("\tMinimum PBR: %d yds\n",spbr[2]);
	printf("\tMaximum PBR: %d yds\n",spbr[3]);
	printf("\n\nWind Speed %3.1f mph from %3.1f deg\n",wv,wa);
	
	
	printf("\n\n\t * Flight Characteristics *\n");
	printf("\n\nDIST\tBD\tWind\tV\tE\tT\n");
	printf("(yds)\t(in)\t(in)\t(ft/s)\t(ft/lb)\t(sec)\n");
	for (x=yi;x<=mr;x+=yi)
	{
		printf("%d\t",x);
		printf("%3.1f\t",GetPath(sln,x));
		printf("%3.1f\t",GetWindage(sln,x));
		tv = GetVelocity(sln,x);
		printf("%3.0f\t",tv);
		printf("%3.0f\t",(pw * tv * tv)/450436);
		printf("%3.2f\n",GetTime(sln,x));
	} 
	printf("\n\n\n");
	if (scope)
	{
		printf("\t * Scope Adjustments *\n");
		printf("\n\nDIST\tVMOA\tVCLKS\tVMILS\tHMOA\tHCLKS\tHMILS\n");
	
		for (x=yi;x<=mr;x+=yi)
		{
			vcl=GetMOA(sln,x)*cl;
			hcl=GetWindageMOA(sln,x)*cl;
			vmoa = GetMOA(sln,x);
			vmils = GetMOA(sln,x)*0.2908;
			hmoa = GetWindageMOA(sln,x);
			hmils = GetWindageMOA(sln,x)*0.2908;
		
			printf("%d\t",x);
			if (vmoa > 0)
				printf("U%3.1f\t",vmoa);
			else
				printf("D%3.1f\t",fabs(vmoa));
				
			if (vcl > 0)
				printf("U%3.0f\t",vcl);
			else
				printf("D%3.0f\t",fabs(vcl));
			
			if (vmils > 0)
				printf("U%3.1f\t",vmils);
			else
				printf("D%3.1f\t",fabs(vmils));
			
			if (hmoa > 0)
				printf("R%3.1f\t",hmoa);
			else
				printf("L%3.1f\t",fabs(hmoa));
			
			if (hcl > 0)
				printf("R%3.0f\t",hcl);
			else
				printf("L%3.0f\t",fabs(hcl));
			
			if (hmils > 0)	
				printf("R%3.1f\t",hmils);
			else
				printf("L%3.1f\t",fabs(hmils));
			printf("\n");
		}
	}	 
	
	return 0;
}

int mildot(void)
{
	char buffer[80];
	double tsize,mildots,distance;
	
	printf("\n\n\t * Distance to Target from Mil-Dots * \n");
	
	while(1)
	{
		printf("\nTarget Size (in) : ");
		sgets(buffer,80);
		tsize = atof(buffer);
		if (tsize > 0) break;
		printf("Targe Size must be > 0!\n");
	}
	
	while(1)
	{
		printf("\n# of Mil-Dots: ");
		sgets(buffer,80);
		mildots = atof(buffer);
		if (mildots > 0) break;
		printf("# of Mil-Dots must be > 0!\n");
	}
	
	distance = (tsize * 27.778) / mildots;
	
	printf("\n\nDistance to Target : %3.1f yds\n",distance);
	
	return 0;

}

int twist_rate(void)
{
	char buffer[80];
	double tr,bl,v,d;
	
	printf("\n\n\t * Optimum Twist Rate * \n");
	
	while(1)
	{
		printf("\nBore Groove Diameter (in) : ");
		sgets(buffer,80);
		d = atof(buffer);
		if (d > 0) break;
		printf("Bore Groove Diameter must be > 0!\n");
	}
	
	while(1)
	{
		printf("\nBullet Length (in) : ");
		sgets(buffer,80);
		bl = atof(buffer);
		if (bl > 0) break;
		printf("Bullet Length must be > 0!\n");
	}
	
	while(1)
	{
		printf("\nBullet Velocity (fps) : ");
		sgets(buffer,80);
		v = atof(buffer);
		if (v > 0) break;
		printf("Bullet Velocity must be > 0!\n");
	}
	
	tr = (3.5 * sqrt(v) * d*d) / bl;
	
	printf("\n\nOptimum Twist Rate : 1 twist in %3.1f in\n",tr);
	
	return 0;

}


int main(void)
{
	char buffer[3];
	int selection,done;
	done = 0;
	
	while (1)
	{
		printf("\n\n   **** Ballistic Calculator Menu ****\n\n");
		printf(" 1. Calculate Trajectory\n");
		printf(" 2. Calculate Ballistic Coefficient\n");
		printf(" 3. Calculate Distance to Target from Mil-Dots\n");
		printf(" 4. Calculate Optimum Twist Rate\n");
	
		printf("\n 99. Exit\n\n");
		printf("Enter Selection: ");
		
		sgets(buffer,sizeof buffer);
		selection = atoi(buffer);
		
		printf("\n\n");
		
		switch (selection)
		{
			case 1:
				trajectory();
				PauseForEnterKey();
				break;
				
			case 2:
				ballistic_coefficient();
				PauseForEnterKey();
				break;
				
			case 3:
				mildot();
				PauseForEnterKey();
				break;
			
			case 4:
				twist_rate();
				PauseForEnterKey();
				break;
					
			case 99:
				done = 1;
				break;
				
			default:
				printf("Invalid Entry\n");
				break;
		}
		if (done == 1) break;
	}
	return 0;
}


	
