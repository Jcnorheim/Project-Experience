package edu.umn.csci1902.project2;

import java.util.ArrayList;
import java.util.List;


public class Airport {
	
	private List<Runway> runways;
	
	/**
	 * Build an airport with ONE runway by default.
	 */
	public Airport() {
		runways = new ArrayList<Runway>();
		this.buildNewRunway();
	}

	/**
	 * Build a new runway and add it to the list of runways.
	 */
	public Runway buildNewRunway() {
		Runway newRunway = new Runway();
		runways.add(newRunway);
		return newRunway;
	}
	
	/**
	 * Get the list of runways at this airport.
	 * 
	 * @return List
	 */
	public List<Runway> getRunways() {
		return this.runways;
	}
}
