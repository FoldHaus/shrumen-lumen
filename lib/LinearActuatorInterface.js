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
	}

	getLinearActuatorState(weightSensor) {

		this.state = weightSensor.getState();
		return state;
	}

	setLinearActuatorState(newState) {
		this.state = newState;
	}
}

module.exports = LinearActuatorInterface;
