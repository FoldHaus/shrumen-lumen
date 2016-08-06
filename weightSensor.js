class WeightSensor {
	constructor() {
		this.recentValues = []
		this.state = false;
	}

	addValueToRecents(value) {
		if(this.recentValues.length <= 10) {
			this.recentValues.push(value)
		}
		else {
			this.recentValues.shift();
			this.recentValues.push(value)
		}
	}

	stepSense(value) {
		var thresholdScaler = 3;
		var recents = this.recentValues;
		console.log("New Value: " + value)
		console.log("Recents: " + recents)

		if(recents.length > 0) {
			var recentValueSum = recents.reduce(function(a, b) {
				return (a+b);
			});
			var recentValuesAverage = recentValueSum / recents.length;
			console.log("Recent Average: " + recentValuesAverage)

			if(value > thresholdScaler*recentValuesAverage) {
				this.state = true;
				console.log("Changed state to true")
			}
			else if (value < (1/thresholdScaler)*recentValuesAverage) {
				this.state = false;
				console.log("Changed state to false")
			}
		}

		this.addValueToRecents(value);
		return this.state;
	}
}

module.exports = WeightSensor;