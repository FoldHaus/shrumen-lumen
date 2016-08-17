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
		
		this.sequence = "none";
	}

	getLinearActuatorState() {
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
	
	stop(time, callback) {
		console.log("Actuator set to stop");
		var _this = this;
		_this.state = 0;
		setTimeout(function() {
			_this.state = 0;
			callback();
		}, time);
	}
	
	extend(time, callback) {
		console.log("Actuator set to extend");
		var _this = this;
		_this.state = 1;
		setTimeout(function() {
			_this.state = 0;
			callback();
		}, time);
	}
	
	retract(time, callback) {
		console.log("Actuator set to retract");
		var _this = this;
		_this.state = -1;
		setTimeout(function() {
			_this.state = 0;
			callback();
		}, time);
	}
	
	basicSequence() {
		if(this.sequence != 'basic') {
			console.log("Starting basic sequence");
			this.sequence = 'basic';
			
			var _this = this;
			
			//Extend the actuator for 15s
			_this.extend(15000, function() {
				console.log("Extension done");
				//Hold at the top for 15s
				_this.stop(15000, function() {
					console.log("Done stopping at the top");
					//Bring the actuator back down
					_this.retract(15000, function() {
						console.log("Done retracting to bottom");
						//Wait for 30 seconds before finishing sequence.
						_this.stop(30000, function() {
							_this.sequence = 'none';
							console.log("Actuator Rearmed");
							console.log("Sequence Completed w/ Sequence State: " + _this.sequence);
						});
					});
				});
			});
			
		}
		
	}
}

module.exports = LinearActuatorInterface;
