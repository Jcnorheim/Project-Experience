package edu.umn.csci1902.project2;

public class RunwayGenerationSimulator extends SimulationEntity {
	
	/**
	 * TODO: Request a new runway to be constructed in order to meet AirControl's time requirement
	 * Important:
	 * - The final average time must be equal to less than Time Requirement + 5 minutes.
	 * - Decrease the final number of runways by one should lead to a higher average time requirement.
	 * - Thus, you may not simply build 10 runways in a go. Be economical. 
	 */
	@Override
	public void timeStep(AirControl airControl) {
		//Goal: build only as many runways as necessary
		//This class seeks to mathematically predict how many runways will be needed and construct them.
		int wait = airControl.getNumberOfWaitingPlanes();
		int busy = airControl.getNumberOfBusyRunways();
		if ((wait >= 1) && (busy <= 2)){
			airControl.constructNewRunway();
		}
		else if ((wait >= 2) && (busy <= 4)) {
			airControl.constructNewRunway();
		}
		else if ((wait > 5) && ((wait / busy) > 0.5)) {
			airControl.constructNewRunway();
		}
	}
}
