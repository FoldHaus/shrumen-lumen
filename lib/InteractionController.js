class InteractionController {
	constructor(weightSensor, pad, linearActuator) {
		this.weightSensor = weightSensor;
		this.pad = pad;
		this.linearActuator = linearActuator;
	}

	handleInteraction() {
		var ws = this.weightSensor;
		var pad = this.pad;
		var la = this.linearActuator;
		
		var wsState = ws.getState();
		var tis = ws.getTimeInState();
		var laPos = la.getPositionState();
		
		console.log(JSON.stringify(laPos));
		console.log(wsState);
		
		if(wsState == true) {
			//Haven't stood on the pad for long enough
			if(tis <= 2) {
				console.log("Haven't stood on the pad for long enough");
				pad.red();
				la.stop();
			}
			//You've been on long enough, start extending.
			else if( tis > 2 && tis < 15) {
				console.log("You've been on long enough, start extending.");
				la.extend();
				pad.blue();
				la.setPositionState(false, false, true);	
			}
			//Full extension, you can't do anything
			else if( tis >= 15) {
				console.log("Full extension, you can't do anything");
				la.stop();
				pad.blue();
				la.setPositionState(true, false, false);		
			}
		}
		else if (wsState == false) {
			//Starting sequence
			if(tis <= 2 && laPos.isRetracted == true) {
				console.log("Starting sequence");
				pad.green();
				la.stop();
				la.setPositionState(false, true, false);
			}
			//Stop the actuator. Redundant
			else if(tis <= 2 && laPos.isExtended == true) {
				console.log("Stop the actuator. Redundant");
				pad.blue();
				la.stop();
				la.setPositionState(true, false, false);
			}
			//You got off, but it's still going to the top
			else if(tis >= 15 && laPos.isTransitioning == true) {
				console.log("You got off, but it's still going to the top");
				pad.blue();
				la.stop();
				la.setPositionState(true, false, false);
			}
			//Waited at the top for a while, retract
			else if(tis >= 20 && laPos.isExtended == true) {
				console.log("Waited at the top for a while, retract");
				pad.blue();
				la.retract();
				la.setPositionState(false, false, true);
			}
			//Rearm the pad
			else if( tis >= 12 && laPos.isRetracted == true) {
				console.log("Rearm the pad");
				pad.green();
				la.stop();
				la.setPositionState(false, true, false);
			}
				
		}
		
	}

}

module.exports = InteractionController;
