package edu.umn.csci1902.project2.tests;

import static org.junit.Assert.assertEquals;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import edu.umn.csci1902.project2.Clock;

public class ClockTest {
	
	Clock clock;
	
	@Before
	public void setUp() {
		clock = new Clock();
	}
	
	@After
	public void tearDown() {
		clock = null;
	}
	
	@Test
	public void testNewClock() {
		assertEquals(clock.getTime(), 0);
	}
	
	@Test
	public void testClockSteps() {
		clock.incrementTime();
		assertEquals(clock.getTime(), 1);
		for (int i = 0; i < 50; i++) {
			clock.incrementTime();
		}
		assertEquals(clock.getTime(), 51);
	}
	
}
