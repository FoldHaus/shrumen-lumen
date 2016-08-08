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
		this.recentValues = [];
		this.state = false;
	}

	addValueToRecents(value) {
		if(this.recentValues.length <= 5) {
			this.recentValues.push(value)
		}
		else {
			this.recentValues.shift();
			this.recentValues.push(value)
		}
	}

	stepSense(value) {
		// var thresholdScaler = 3;
		// var recents = this.recentValues;
		// console.log("New Value: " + value)
		// console.log("Recents: " + recents)

		// if(recents.length > 0) {
		// 	var recentValueSum = recents.reduce(function(a, b) {
		// 		return (a+b);
		// 	});
		// 	var recentValuesAverage = recentValueSum / recents.length;
		// 	console.log("Recent Average: " + recentValuesAverage)

		// 	if(value > thresholdScaler*recentValuesAverage) {
		// 		this.state = true;
		// 		console.log("Changed state to true")
		// 	}
		// 	else if (value < (1/thresholdScaler)*recentValuesAverage) {
		// 		this.state = false;
		// 		console.log("Changed state to false")
		// 	}
		// }

		// this.addValueToRecents(value);
		// return this.state;

		if(value > 15) {
			this.state = true;
		}
		else {
			this.state = false;
		}
		
		return this.state;
	}
}

module.exports = WeightSensorInterface;
