package edu.umn.csci1902.project2;

import java.util.Random;

public class RunwayRequestSimulator extends SimulationEntity {

	/**
	 * Randomly generate runway requests
	 * Make request by newly arriving or departing planes using airControl's request probability (per 15 seconds).  
	 * Randomly decide the type of the plane (0.2 chance per type)
	 * Accepted types(Please restrict yourself to these):
	 *   Heavy, Upper-Medium, Lower-Medium, Small, and Light.
	 *   
	 * Use the Math library for the random number generator.
	 */
	@Override
	public void timeStep(AirControl airControl) {

		Random random = new Random();
		float randomFloat = random.nextFloat();
		if (randomFloat <= airControl.getRunwayRequestLikelihood()){
			randomFloat = random.nextFloat();
			if (randomFloat < 0.2) {
				airControl.receiveRunwayRequest(new Plane("Heavy", airControl.getCurrentTime()));
			}
			else if (randomFloat < 0.4) {
				airControl.receiveRunwayRequest(new Plane("Upper-Medium", airControl.getCurrentTime()));
			}
			else if (randomFloat < 0.6) {
				airControl.receiveRunwayRequest(new Plane("Lower-Medium", airControl.getCurrentTime()));
			}
			else if (randomFloat < 0.8) {
				airControl.receiveRunwayRequest(new Plane("Small", airControl.getCurrentTime()));
			}
			else {
				airControl.receiveRunwayRequest(new Plane("Light", airControl.getCurrentTime()));
			}
		}
	}
}
