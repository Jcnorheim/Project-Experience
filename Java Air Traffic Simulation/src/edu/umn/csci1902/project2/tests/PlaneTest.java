package edu.umn.csci1902.project2.tests;



import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import edu.umn.csci1902.project2.Plane;

public class PlaneTest {
	
	Plane plane;
	
	@Before
	public void setUp() {
		plane = new Plane("Heavy", 60);
	}
	
	@After
	public void tearDown() {
		plane = null;
	}
	
	@Test
	public void testPlaneProperties() {
		assertTrue(plane.getType().equals("Heavy"));
		assertEquals(plane.getRequestTime(), 60);
	}

}
