package edu.umn.csci1902.project2;

import java.util.ArrayList;
import java.util.List;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		if (args.length == 4) {
			
			// Get the first argument - probability of runway request every 15 seconds
			double runwayRequestProbability = Double.valueOf(args[0]).doubleValue();
			
			// Get the second argument - runway waiting time requirement in seconds
			long waitTimeReq = Long.valueOf(args[1]).longValue();
			
			// Get the Third argument - initial number of runway - Note that 0 and 1 are equivalent
			int NumRunways = Integer.valueOf(args[2]).intValue();
			
			// Get the fourth argument - simulation period in seconds
			long simulationPeriod = Long.valueOf(args[3]).longValue();
			
			// Print a Startup message
			System.out.println("Now Starting the Airport Runway Assignment Simulator!");
			System.out.println("---Simulating " + (simulationPeriod / 3600.0) + " hours of airport activity");
			System.out.println();
			
			// Create the main airControl object and construct extra runways if NumRunways > 1
			AirControl airTrafficControl = new AirControl(runwayRequestProbability, waitTimeReq);
			
			// Have the airTrafficControl construct more runways to meet number specified in the third argument.
			// Only construct new runways if NumRunways is greater than 1.
			for (int i = 1; i < NumRunways; i++) {
				airTrafficControl.constructNewRunway();
			}
			
			
			// Create a collection of simulation entities and add our four simulators
			List<SimulationEntity> simulationEntities = new ArrayList<SimulationEntity>();
			simulationEntities.add(new RunwayRequestSimulator());
			simulationEntities.add(new RunwayAssignmentSimulator());
			simulationEntities.add(new RunwayGenerationSimulator());

			// 30 minutes period between printing summaries: see expected output
			long printDelay = 1800;
			
			// Loop for the duration of the simulation: each execution is a one second time step.
			for (long i = 0; i < simulationPeriod; i++) {

				// Time step each simulation entity in the collection of simulation entities that you created above.
				airTrafficControl.clockStep();

				for (SimulationEntity simulationEntity: simulationEntities) {
					simulationEntity.timeStep(airTrafficControl);
				}

				// Print the expected output: use period above (printDelay)
				int numberOfPlanesServed = airTrafficControl.getNumberOfPlanesServed();
				long totalWaitingTime = airTrafficControl.getTotalWaitingTime();
				int numberOfWaitingPlanes = airTrafficControl.getNumberOfWaitingPlanes();
				int totalNumberOfRunways = airTrafficControl.getNumberOfAvailableRunways() + airTrafficControl.getNumberOfBusyRunways();

				if (numberOfPlanesServed == 0) {
					System.out.println("Number of Planes Served: " + numberOfPlanesServed);
					System.out.println();
				}
				else if ((i % printDelay) == 0) {
					System.out.println("Number of Planes Served: "
						+ numberOfPlanesServed + "		"
						+ "Total Waiting time: " + totalWaitingTime);
					System.out.println("Number of Waiting Planes: "
						+ numberOfWaitingPlanes + "		"
						+ "Total Number of Runways: " + totalNumberOfRunways);
					System.out.println("Average Waiting Time: " + (totalWaitingTime / numberOfPlanesServed));
					System.out.println();
				}
			}
			System.out.println("Simulation Completed!");
		}
		else {
			System.out.println("Simulation failed to start! Received: " + args.length + " instead of 4:");
			System.out.println("First argument: Probability of runway request every 15 seconds");
			System.out.println("Second argument: Waiting time requirement in seconds");
			System.out.println("Third argument: Number of initial runways");
			System.out.println("Fourth argument: Amount of activity time (in seconds) to simulate");
		}
	}
}
