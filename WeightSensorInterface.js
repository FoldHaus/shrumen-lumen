class WeightSensorInterface {
	constructor() {
		this.weightSensors = {};
	}

	registerNewData(sensorNum, sensorData) {
		var response;

		if(sensorNum in this.weightSensors) {
			var ws = this.weightSensors[sensorNum];
			response = ws.stepSense(sensorData);
		}
		else {
			var sensor = new WeightSensor(sensorNum);
			response = sensor.stepSense(sensorData);
			this.weightSensors[sensorNum] = sensor;
		}

		return response;
	}
}



class WeightSensor {
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
}

module.exports = WeightSensorInterface;
