class LinearActuatorInterface {
	constructor(speed = 1024) {
		//Speed for the linear actuator
		this.speed = speed; 

		//The state to be sent to the linear actuator.
		//Each value encodes a different state
		//  0: Stop
		//  1: Extend
		// -1: Retract
		this.state = 0;
		this.isExtended = false;
		this.isRetracted = true;
		this.isTransitioning = false;
	}

	getLinearActuatorState(weightSensor) {

		this.state = (weightSensor.getState() == true) ? 1 : 0;
		console.log("WEIGHT SENSOR STATE: " + weightSensor.getState());
		return this.state;
	}

	setLinearActuatorState(newState) {
		this.state = newState;
	}
	
	getPositionState() {
		var respObj = {
			extended: this.isExtended,
			retracted: this.isRetracted,
			transitioning: this.isTransitioning
		}
		
		return respObj;
	}
	
	setPositionState(isExtended, isRetracted, isTransitioning) {
		this.isExtended = isExtended;
		this.isRetracted = isRetracted;
		this.isTransitioning = isTransitioning;
	}
	stop() {
		this.state = 0;
	}
	
	extend() {
		this.state = 1;
	}
	
	retract() {
		this.state = -1;
	}
}

module.exports = LinearActuatorInterface;
