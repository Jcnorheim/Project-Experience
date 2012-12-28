package edu.umn.csci1902.project2;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

/**
 * AirControl is responsible for receiving runway requests
 * and Assigning available runways on a first come first served.
 * AirControl keeps track of the total runway waiting time 
 * as well as the number of planes served.
 * For simulation purpose, it possesses a clock which will be used to keep
 * track of time during the simulation rather than using the real time.
 * Thus 1 hours should run in no time depending on the speed of the simulating computer.
 * 
 * AirControl also has:
 * - ThSe probability of a plane requesting a plane every 15 seconds.
 * - The AirControl's set waiting time requirement.
 * - An airport that its oversees
 * - A queue of runway requests by arriving or departing plane
 *   (No distinction has been made in this project)
 * - A queue of available runways to be assigned to planes
 * - A list of busy runways.
 * 
 * @author Jonathan Norheim norhe003
 */
public class AirControl {

	private final double requestProbability;
	private final long waitingTimeRequirement;
	private long totalWaitingTime;
	private int numberOfPlanesServed;
	private Clock masterClock;
	private Airport airport;
	private Queue<Plane> runwayRequests;
	private Queue<Runway> availableRunways;
	private List<Runway> busyRunways;
	
	/**
	 * Instantiate all data fields.
	 * Instantiate all data fields appropriately
	 * and remember to add all airport's runways to
	 * the queue of available runways.
	 * 
	 * @param requestLikelihood - the likelihood of a runway request every 15 seconds
	 * @param waitTimeReq - the established average time requirement
	 */
	public AirControl(double requestLikelihood, long waitTimeReq) {
		this.requestProbability = requestLikelihood;
		this.waitingTimeRequirement = waitTimeReq;
		this.totalWaitingTime = 0;
		this.numberOfPlanesServed = 0;
		this.masterClock = new Clock();
		this.airport = new Airport();
		this.runwayRequests = new ArrayDeque<Plane>();
		this.availableRunways = new ArrayDeque<Runway>();
		this.busyRunways = new ArrayList<Runway>();
		this.constructNewRunway();
	}
	
	/**
	 * Get probability of a runway request.
	 * 
	 * @return probability of runway request every 15 seconds
	 */
	
	public double getRunwayRequestLikelihood() {
		return requestProbability;
	}
	
	/**
	 * Get the established waiting time requirement.
	 * 
	 * @return average runway waiting time requirement
	 */
	public long getWaitingTimeRequirement() {
		return waitingTimeRequirement;
	}
	
	/**
	 * Get the total waiting time of all planes served thus far.
	 * 
	 * @return total waiting time in seconds
	 */
	public long getTotalWaitingTime() {
		return totalWaitingTime;
	}
	
	/**
	 * Increase the total waiting time by the specified amount of seconds.
	 * 
	 * @param seconds plane's waiting time
	 */
	public void increaseTotalWaitingTime(long seconds) {
		totalWaitingTime += seconds;
	}
	
	/**
	 * Get the total number of planes served thus far.
	 * 
	 * @return number of planes served thus far
	 */
	public int getNumberOfPlanesServed() {
		return numberOfPlanesServed;
	}
	
	/**
	 * Increase the total number of planes served by the specified number of planes.
	 * During the simulation it will usually be one plane at a time.
	 * 
	 * @param numPlanes number of planes
	 */
	public void increaseNumberOfPlanesServed(int numPlanes) {
		numberOfPlanesServed += numPlanes;
	}
	
	/**
	 * Get the current time on the air control's master clock.
	 * 
	 * @return current time on the Master Clock in seconds
	 */
	public long getCurrentTime() {
		return masterClock.getTime();
	}
	
	/**
	 * Increase the time of the master clock by a second.
	 * This method will be called by the simulator every time step.
	 */
	public void clockStep() {
		masterClock.incrementTime();
	}
	
	/**
	 * Get the number of planes currently waiting to be served.
	 * 
	 * @return number of planes waiting to be granted a runway
	 */
	public int getNumberOfWaitingPlanes() {
		return runwayRequests.size();
	}
	
	/**
	 * Get the number of runways available for immediate assignment.
	 * 
	 * @return number of available runways
	 */
	public int getNumberOfAvailableRunways() {
		return this.availableRunways.size();
	}
	
	/**
	 * Get the number of runways that are currently in use.
	 * 
	 * @return number of busy runways.
	 */
	public int getNumberOfBusyRunways() {
		return this.busyRunways.size();
	}
	
	/**
	 * Constructs a new runway and immediately enqueues it
	 * on the list of available runways.
	 * Note that runways are built by the airport.
	 */
	public void constructNewRunway() {
		this.availableRunways.add(new Runway());
	}
	
	/**
	 * Decrement the occupancy time of each busy runway + necessary updates.
	 * Decrement the occupancy time of each runway in the list
	 * of busy runways by one and if a runway's occupancy runs down to zero
	 * remove it from the list of busy runways and enqueue it onto the Queue 
	 * of available runways.
	 * 
	 * This should then be called on every simulation time step.
	 */
	public void updateBusyRunways() {

		Queue<Runway> runwayQueue = new ArrayDeque<Runway>();
		for (Runway runway : busyRunways) {
			runway.decrementOccupancyTime();
			if (runway.getOccupancyTime() == 0) {
				runwayQueue.add(runway);
			}
		}
		for (Runway runway : runwayQueue) {
				busyRunways.remove(runway);
				availableRunways.add(runway);
		}
	}
	
	/**
	 * Receive and Enqueue the requesting plane into the queue of runway requests.
	 * 
	 * @param plane requesting runway
	 */
	public void receiveRunwayRequest(Plane plane) {
		runwayRequests.add(plane);
	}
	
	/**
	 * Grant a runway if any to a requesting plane. Here are the details: 
	 * Get a plane from the runway requests and a runway from the available runways
	 * After getting the type of the plane, occupy the runway with this plane
	 * and provide the appropriate occupancy time.
	 * 
	 * This occupancy time is determined by the plane type using the following:
	 * Heavy		=>	135 seconds (2.25 min)
	 * Upper-Medium	=>	112 seconds (1.87 min)
	 * Lower-Medium =>	90 seconds (1.50 min)
	 * Small		=>	68 seconds (1.14 min)
	 * Light		=>	68 seconds (1.14 min)
	 * 
	 * Finally add this runway to the list of busy runways.
	 * 
	 * Remember to account the plane's waiting time into the total waiting time
	 * and increase the number of planes served.
	 *  
	 * @return true if a request was granted or false otherwise.
	 */
	public boolean grantRunwayRequest() {

		if ((runwayRequests.size() == 0) || (availableRunways.size() == 0)) {
			return false;
		}

		Plane plane = runwayRequests.poll();
		Runway runway = availableRunways.poll();
		long occupancyTime = 0;

		String planeType = plane.getType();
		switch(planeType) {
		case "Heavy": occupancyTime = 135; break;
		case "Upper-Medium": occupancyTime = 112; break;
		case "Lower-Medium": occupancyTime = 90; break;
		case "Small": occupancyTime = 68; break;
		case "Light": occupancyTime = 68; break;
		}
		runway.occupy(plane, occupancyTime);
		busyRunways.add(runway);
		increaseTotalWaitingTime(masterClock.getTime() - plane.getRequestTime());
		this.numberOfPlanesServed++;

		return true;
	}
}
