var moment = require('moment');
var _ = require('lodash');

class WeightSensorInterface {
	constructor(sensorNumber) {
		this.sensorNumber = sensorNumber;
		this.state = false;
		this.startTime = moment();
		this.timeDiff = 0;
		this.timeInState = 0;
		this.calibratedTopValue = 400;
		this.calibratedBottomValue = 15;
		this.calibratedLengthSteps = 10;
		this.calArr = [];
		this.isCalibrated = false;
	}
	
	calibrate(value) {
		var calArr = this.calArr;
		calArr.push(value)
		if (calArr.length == this.calibratedLengthSteps) {
			var medianVal = median(calArr);
			this.isCalibrated = true;
			this.startTime = moment();
			this.calibratedBottomValue = medianVal*8; 
			this.calibratedTopValue = medianVal*150; 
			
			if(this.calibratedBottomValue > 50) {
				this.calibratedBottomValue = 15;
				this.calibratedTopValue = 400;
			}
			
			console.log("Calibrated Bottom Threshold Value " + this.calibratedBottomValue);
			console.log("Calibrated Top Threshold Value " + this.calibratedTopValue);
		}
		
	}

	stepSense(value) {
		
		if (!this.isCalibrated) {
			this.calibrate(value)
			return false;
		}
		
		var oldState = this.state;
		var newState;

		if(value > this.calibratedBottomValue && value < this.calibratedTopValue) {
			newState = true;
		}
		else {
			newState = false;
		}
		// If there state change...
		if(newState != oldState) {
			this.timeDiff = moment().diff(this.startTime, 'seconds');
			this.timeInState = 0;
			this.startTime = moment();
		}
		else {
			this.timeInState = moment().diff(this.startTime, 'seconds');
		}
		
		this.state = newState;
		return this.state;
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

	getIsCalibrated() {
		return this.isCalibrated;
	}

	registerNewData(sensorData) {
		var response = this.stepSense(sensorData);
		return response;
	}
}

function median(values) {

    values.sort( function(a,b) {return a - b;} );

    var half = Math.floor(values.length/2);

    if(values.length % 2)
        return values[half];
    else
        return (values[half-1] + values[half]) / 2.0;
}

module.exports = WeightSensorInterface;
