class WeightSensorInterface {
	constructor(sensorNumber) {
		this.sensorNumber = sensorNumber;
		this.state = false;
	}

	stepSense(value) {
		var thresholdValue = 15;

		if(value > thresholdValue) {
			this.state = true;
		}
		else {
			this.state = false;
		}
		
		return this.state;
	}

	getState() {
		return this.state;
	}

	registerNewData(sensorData) {
		var response = this.stepSense(sensorData);
		return response;
	}
}

module.exports = WeightSensorInterface;
