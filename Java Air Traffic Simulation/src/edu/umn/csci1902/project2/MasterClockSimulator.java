package edu.umn.csci1902.project2;

public class MasterClockSimulator extends SimulationEntity{

	/**
	 * Increase the time of the Master Clock by one second, each time step.
	 */
	@Override
	public void timeStep(AirControl airControl){
		airControl.clockStep();
	}
	
}
