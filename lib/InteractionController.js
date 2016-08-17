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
		
		if(wsState == true && tis >= 5) {
			if(la.sequence == 'none') {
				la.basicSequence();
				pad.blue();
			}
			else {
				console.log("Can't do anything. Sequence in progress.");
			}
		}
		else {
			if(la.sequence == 'none') {
				pad.green();
			}
		}		
	}

}

module.exports = InteractionController;
