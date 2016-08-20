class InteractionController {
	constructor(weightSensor, pad, linearActuator) {
		this.weightSensor = weightSensor;
		this.pad = pad;
		this.linearActuator = linearActuator;
		
		this.safetyMode = false;
	}

	handleInteraction() {
		var ws = this.weightSensor;
		var pad = this.pad;
		var la = this.linearActuator;
		
		var wsState = ws.getState();
		var tis = ws.getTimeInState();
		
		if(this.safetyMode == false) {
			if(wsState == true && tis >= 2) {
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
		else {
			if(wsState == true && tis >= 2) {
				console.log("In Safety Mode. Can't move until it's unlocked");
			}
		}		
	}

	handleInteractionRequests() {
		var pad = this.pad;
		var la = this.linearActuator;
		
		if(this.safetyMode == false) {
			
			if(la.sequence == 'none') {
				la.basicSequence();
				pad.blue();
			}
			else {
				console.log("Can't do anything. Sequence in progress.");
			}
		}
		else {
			console.log("Can't execute animation. In safety mode.");
		}

	}
	
	handleSafetyModeRequests(signal) {
		var pad = this.pad;
		var la = this.linearActuator;
		
		if(signal == 'lock') {
			if(la.sequence != 'safety') {
				this.safetyMode = true;
				
				pad.red();
				la.safetyModeSequence();
			}
		}
		else {
			this.safetyMode = false;
		}
	
	}

}

module.exports = InteractionController;
