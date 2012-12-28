package edu.umn.csci1902.project2.tests;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import edu.umn.csci1902.project2.Plane;
import edu.umn.csci1902.project2.Runway;

public class RunwayTest {

	Runway runway;
	
	@Before
	public void setUp() {
		runway = new Runway();
	}
	
	@After
	public void tearDown() {
		runway = null;
	}
	
	@Test
	public void testOccupancy() {
		assertTrue(!runway.isOccupied());
		runway.occupy(new Plane("Heavy", 60), 135);
		assertTrue(runway.isOccupied());
	}
	
	@Test
	public void testOccupancyTime() {
		assertEquals(runway.getOccupancyTime(), 0);
		runway.occupy(new Plane("Heavy", 60), 135);
		assertEquals(runway.getOccupancyTime(), 135);
		runway.decrementOccupancyTime();
		assertEquals(runway.getOccupancyTime(), 134);
		for (int i = 0; i < 50; i++) {
			runway.decrementOccupancyTime();
		}
		assertEquals(runway.getOccupancyTime(), 84);
	}
}
