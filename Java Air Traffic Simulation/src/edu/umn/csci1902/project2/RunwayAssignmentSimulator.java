package edu.umn.csci1902.project2;

public class RunwayAssignmentSimulator extends SimulationEntity {

	/**
	 * TODO: Grant runway requests if there is a runway available and existing pending requests
	 * Decrement by 1 the Occupancy time of all busy runways and enqueue available runways 
	 * with runways whose occupancy time fall to zero.
	 */
	@Override
	public void timeStep(AirControl airControl) {
		airControl.grantRunwayRequest();
		airControl.updateBusyRunways();
	}	
}
