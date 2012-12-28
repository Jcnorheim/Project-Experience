package edu.umn.csci1902.project2;

/**
 * Define a plane object with two properties:
 *   The type of the plane which can be: 
 *     Heavy, Upper-Medium, Lower-Medium, Small and Light.
 *   The time at the plane requested the runway
 *   
 * For the purpose of the simulation, a plane object
 * will be created at runway request time.
 * 
 * @author Emery Mizero
 *
 */
public class Plane {
	
	private final String type;
	private final long requestTime;
	
	/**
	 * Build a plane object given the two parameters below.
	 * @param type	string that describes the size of the plane
	 * @param requestTime	time of runway request
	 */
	public Plane(String type, long requestTime) {
		this.type = type;
		this.requestTime = requestTime;
	}

	/**
	 * Get the type of the plane
	 * @return type of plane
	 */
	public String getType() {
		return this.type;	
	}
	
	/**
	 * Get the time when the plane requested a runway
	 * @return time of runway request
	 */
	public long getRequestTime() {
		return this.requestTime;
	}
}
