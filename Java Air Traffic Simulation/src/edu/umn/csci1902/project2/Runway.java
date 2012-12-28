package edu.umn.csci1902.project2;

/**
 * A simple runway with two properties:
 * the plane on the runway and an indicator of
 * how long this runway will remain occupied.
 * If the latter is zero, then a non-null plane
 * indicates the plane that last used the runway
 * 
 * @author Emery Mizero
 *
 */

public class Runway {
	
	private long occupancyTime;
	private Plane planeOnRunway;
	
	/**
	 * Builds an unoccupied runway with its occupancy time
	 * set to zero and plane on set to null.
	 */
	public Runway(){
		this.occupancyTime = 0;
		this.planeOnRunway = null;
	}
	
	/**
	 * Indicates whether the runway is occupied or not
	 * @return true if the runway is occupied and false otherwise
	 */
	public boolean isOccupied() {
		return !(this.occupancyTime == 0);
	}
	
	/**
	 * Change the runway to be occupied or not be occupied
	 * @param plane plane to use the runway
	 * @param occupancyTime time that the runway will be occupied
	 * @return true if the runway was free or false otherwise
	 */
	public boolean occupy(Plane plane, long occupancyTime) {
		boolean result = false;
		if (!isOccupied()) {
			this.occupancyTime = occupancyTime;
			this.planeOnRunway = plane;
		}
		return result;
	}
	
	/**
	 * Get the current plane on the runway if any
	 * If occupancy time has run down, 
	 * then get the plane that last used the runway
	 * @return current or last plane on runway or null if none thus far
	 */
	public Plane getPlaneOnRunway() {
		return this.planeOnRunway;
	}
	
	/**
	 * Get the time remaining until the runway is free
	 * of zero if free.
	 * @return time remaining until free
	 */
	public long getOccupancyTime() {
		return this.occupancyTime;
	}
	
	/**
	 * Decrement the runway occupancy time by one
	 */
	public void decrementOccupancyTime() {
		if (isOccupied()) {
			this.occupancyTime--;
		}
	}
}
