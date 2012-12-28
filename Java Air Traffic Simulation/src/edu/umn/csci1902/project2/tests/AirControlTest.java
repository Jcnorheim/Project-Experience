package edu.umn.csci1902.project2.tests;

import static org.junit.Assert.assertEquals;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import edu.umn.csci1902.project2.AirControl;
import edu.umn.csci1902.project2.Plane;

public class AirControlTest {
	
	/**
	 * (1) Test assigned request probably and waiting time requirement
	 * (2) Test incrementing waiting time
	 * (3) Test change in number of planes served
	 * (4) Test the master clock: change and current time
	 * (5) Test the airport and building new runways
	 * (6) Test the queue of requests
	 *     Test the queue of available runways.
	 *     Test the list of busy runways 
	 *     All through requests and grants.
	 */
	
	AirControl airControl;
	
	@Before
	public void setUp() {
		airControl = new AirControl(0.5, 300);
	}
	
	@After
	public void tearDown() {
		airControl = null;
	}
	
	@Test
	public void testCorrectInitiation() {
		assertEquals(airControl.getRunwayRequestLikelihood(), 0.5, 0);
		assertEquals(airControl.getWaitingTimeRequirement(), 300, 0);
		assertEquals(airControl.getTotalWaitingTime(), 0, 0);
		assertEquals(airControl.getNumberOfPlanesServed(), 0);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0, 0);
		assertEquals(airControl.getCurrentTime(), 0, 0);
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
	}
	
	@Test
	public void testMasterClock() {
		assertEquals(airControl.getCurrentTime(), 0, 0);
		airControl.clockStep();
		assertEquals(airControl.getCurrentTime(), 1, 0);
		for (int i = 0; i < 99; i++) {
			airControl.clockStep();
		}
		assertEquals(airControl.getCurrentTime(), 100, 0);
	}
	
	@Test
	public void testChangePlanesServed() {
		assertEquals(airControl.getNumberOfPlanesServed(), 0);
		airControl.increaseNumberOfPlanesServed(1);
		assertEquals(airControl.getNumberOfPlanesServed(), 1);
		airControl.increaseNumberOfPlanesServed(10);
		assertEquals(airControl.getNumberOfPlanesServed(), 11);
	}
	
	@Test
	public void testRunwayRequest() {
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		assertEquals(airControl.getTotalWaitingTime(), 0);
		airControl.receiveRunwayRequest(new Plane("Upper-Medium", airControl.getCurrentTime()));
		assertEquals(airControl.getNumberOfWaitingPlanes(), 1);
		
		for (int i = 0; i < 60; i++) {
			airControl.clockStep();
		}
		airControl.grantRunwayRequest();
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		assertEquals(airControl.getTotalWaitingTime(), 60);
		
	}
	
	@Test
	public void testBuildingNewRunways() {
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		airControl.constructNewRunway();
		assertEquals(airControl.getNumberOfAvailableRunways(), 2);
		for (int i = 0; i < 9; i++) {
			airControl.constructNewRunway();
		}
		assertEquals(airControl.getNumberOfAvailableRunways(), 11);
	}
	
	@Test
	public void testAllPlanesTypesOnRunway() {
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		airControl.receiveRunwayRequest(new Plane("Heavy", airControl.getCurrentTime()));
		assertEquals(airControl.getNumberOfWaitingPlanes(), 1);
		
		for (int i = 0; i < 60; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		airControl.grantRunwayRequest();
		assertEquals(airControl.getTotalWaitingTime(), 60);
		assertEquals(airControl.getNumberOfPlanesServed(), 1);
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		
		for (int i = 0; i < 130; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		
		for (int i = 0; i < 5; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
		
		
		//Upper-Medium Planes
		airControl.receiveRunwayRequest(new Plane("Upper-Medium", airControl.getCurrentTime()));
		assertEquals(airControl.getNumberOfWaitingPlanes(), 1);
		
		for (int i = 0; i < 60; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		airControl.grantRunwayRequest();
		assertEquals(airControl.getTotalWaitingTime(), 120);
		assertEquals(airControl.getNumberOfPlanesServed(), 2);
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		
		for (int i = 0; i < 112; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}

		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
		
		
		//Lower-Medium Planes
		airControl.receiveRunwayRequest(new Plane("Lower-Medium", airControl.getCurrentTime()));
		assertEquals(airControl.getNumberOfWaitingPlanes(), 1);
		
		for (int i = 0; i < 60; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		airControl.grantRunwayRequest();
		assertEquals(airControl.getTotalWaitingTime(), 180);
		assertEquals(airControl.getNumberOfPlanesServed(), 3);
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		
		for (int i = 0; i < 90; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}

		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
		
		//Small Planes
		airControl.receiveRunwayRequest(new Plane("Small", airControl.getCurrentTime()));
		assertEquals(airControl.getNumberOfWaitingPlanes(), 1);
		
		for (int i = 0; i < 60; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		airControl.grantRunwayRequest();
		assertEquals(airControl.getTotalWaitingTime(), 240);
		assertEquals(airControl.getNumberOfPlanesServed(), 4);
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		
		for (int i = 0; i < 68; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}

		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
		
		//Light Planes
		airControl.receiveRunwayRequest(new Plane("Light", airControl.getCurrentTime()));
		assertEquals(airControl.getNumberOfWaitingPlanes(), 1);
		
		for (int i = 0; i < 60; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		airControl.grantRunwayRequest();
		assertEquals(airControl.getTotalWaitingTime(), 300);
		assertEquals(airControl.getNumberOfPlanesServed(), 5);
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		
		for (int i = 0; i < 68; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}

		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
	}
	
	
	@Test
	public void testHeavyPlaneOnRunway() {
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		airControl.receiveRunwayRequest(new Plane("Heavy", airControl.getCurrentTime()));
		assertEquals(airControl.getNumberOfWaitingPlanes(), 1);
		
		for (int i = 0; i < 60; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		airControl.grantRunwayRequest();
		assertEquals(airControl.getTotalWaitingTime(), 60);
		assertEquals(airControl.getNumberOfPlanesServed(), 1);
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		
		for (int i = 0; i < 130; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		
		for (int i = 0; i < 5; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
	}
	
	@Test
	public void testUpperMediumPlaneOnRunway(){
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		airControl.receiveRunwayRequest(new Plane("Upper-Medium", airControl.getCurrentTime()));
		assertEquals(airControl.getNumberOfWaitingPlanes(), 1);
		
		for (int i = 0; i < 60; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		airControl.grantRunwayRequest();
		assertEquals(airControl.getTotalWaitingTime(), 60);
		assertEquals(airControl.getNumberOfPlanesServed(), 1);
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		
		for (int i = 0; i < 111; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		
		for (int i = 0; i < 1; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
	}
	
	@Test
	public void testLowerMediumPlaneOnRunway() {
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		airControl.receiveRunwayRequest(new Plane("Lower-Medium", airControl.getCurrentTime()));
		assertEquals(airControl.getNumberOfWaitingPlanes(), 1);
		
		for (int i = 0; i < 60; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		airControl.grantRunwayRequest();
		assertEquals(airControl.getTotalWaitingTime(), 60);
		assertEquals(airControl.getNumberOfPlanesServed(), 1);
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		
		for (int i = 0; i < 80; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		
		for (int i = 0; i < 10; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
	}
	
	@Test
	public void testSmallPlaneOnRunway() {
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		airControl.receiveRunwayRequest(new Plane("Small", airControl.getCurrentTime()));
		assertEquals(airControl.getNumberOfWaitingPlanes(), 1);
		
		for (int i = 0; i < 60; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		airControl.grantRunwayRequest();
		assertEquals(airControl.getTotalWaitingTime(), 60);
		assertEquals(airControl.getNumberOfPlanesServed(), 1);
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		
		for (int i = 0; i < 50; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		
		for (int i = 0; i < 18; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
	}
	
	@Test
	public void testLightPlaneOnRunway() {
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		airControl.receiveRunwayRequest(new Plane("Light", airControl.getCurrentTime()));
		assertEquals(airControl.getNumberOfWaitingPlanes(), 1);
		
		for (int i = 0; i < 60; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		airControl.grantRunwayRequest();
		assertEquals(airControl.getTotalWaitingTime(), 60);
		assertEquals(airControl.getNumberOfPlanesServed(), 1);
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		assertEquals(airControl.getNumberOfWaitingPlanes(), 0);
		
		for (int i = 0; i < 50; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 0);
		assertEquals(airControl.getNumberOfBusyRunways(), 1);
		
		for (int i = 0; i < 18; i++) {
			airControl.clockStep();
			airControl.updateBusyRunways();
		}
		
		assertEquals(airControl.getNumberOfAvailableRunways(), 1);
		assertEquals(airControl.getNumberOfBusyRunways(), 0);
	}
}
