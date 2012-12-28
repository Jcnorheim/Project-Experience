package edu.umn.csci1902.project2;

/**
 * A simple clock will be used to keep track 
 * of the time during the simulation.
 * 
 * @author Emery Mizero
 *
 */
public class Clock {
	
	//Time in seconds
	private long time;
	
	/**
	 * Create a new clock with time set to zero
	 */
	public Clock() {
		this.time = 0;
	}
	
	/**
	 * Increase the time on the clock by a second
	 */
	public void incrementTime() {
		this.time += 1;
	}
	
	/**
	 * Get the current time on the clock in seconds.
	 * @return current time on the clock.
	 */
	public long getTime() {
		return this.time;
	}
}
