var moment = require('moment');

class WeightSensorInterface {
	constructor(sensorNumber) {
		this.sensorNumber = sensorNumber;
		this.state = false;
		this.startTime = moment();
		this.timeDiff = 0;
		this.timeInState = 0;
		this.value = null;
	}

	stepSense(value) {
		// Store value
		this.value = value;

		var thresholdValueMin = 15;
		var thresholdValueMax = 400;
		var oldState = this.state;
		var newState;

		if(value > thresholdValueMin && value < thresholdValueMax) {
			newState = true;
		}
		else {
			newState = false;
		}
		// If there state change...
		if(newState != oldState) {
			this.timeDiff = moment().diff(this.startTime, 'seconds');
			this.startTime = moment();
			//~ console.log("TimeDiff: " + this.timeDiff);
		}
		else {
			this.timeInState = moment().diff(this.startTime, 'seconds');
			//~ console.log("TimeInState: " + this.timeInState);
		}
		
		this.state = newState;
		return this.state;
	}

	getRawData() {
		return this.value;
	}

	getState() {
		return this.state;
	}
	
	getTimeDiff() {
		return this.timeDiff;
	}
	
	getTimeInState() {
		return this.timeInState;
	}
	
	getStateAndTimeDiff() {	
		var respObj = {
			currentState: getState(),
			timeDiff: getTimeDiff()
		}
	
		return respObj;	
	}


	registerNewData(sensorData) {
		var response = this.stepSense(sensorData);
		return response;
	}
}

module.exports = WeightSensorInterface;
