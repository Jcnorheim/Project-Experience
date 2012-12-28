package edu.umn.csci1902.project2.tests;

import static org.junit.Assert.assertEquals;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import edu.umn.csci1902.project2.Airport;

public class AirportTest {

	Airport airport;
	
	@Before
	public void setUp() {
		airport = new Airport();
	}
	
	@After
	public void tearDown() {
		airport = null;
	}
	
	@Test
	public void testOneDefaultRunway() {
		assertEquals(airport.getRunways().size(), 1);
	}
	
	@Test
	public void testRunwayAdditions() {
		airport.buildNewRunway();
		assertEquals(airport.getRunways().size(), 2);
		for (int i = 0; i < 8; i++) {
			airport.buildNewRunway();
		}
		assertEquals(airport.getRunways().size(), 10);
	}
}
