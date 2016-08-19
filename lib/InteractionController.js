class InteractionController {
	constructor(weightSensor, pad, linearActuator, animationsInterface) {
		this.weightSensor = weightSensor;
		this.pad = pad;
		this.linearActuator = linearActuator;
		this.animationsInterface = animationsInterface;
	}

	handleInteraction() {
		var ws = this.weightSensor;
		var pad = this.pad;
		var la = this.linearActuator;
		
		var wsState = ws.getState();
		var tis = ws.getTimeInState();
		if (ws.getIsCalibrated() == true) {
			console.log("TIS: " + tis);
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
		else {
			pad.purple();
		}		
	}

	startAnimationLoop(switchTime) {
		var switchTimeMilliSecs = min2MillSecs(switchTime);
		var aniController = this.animationsInterface;

		//Change the animation from the default
		aniController.next();

		//Set a timer to continually change the animation
		var looper = setInterval(aniController.next.bind(aniController), switchTimeMilliSecs);
		aniController.setLooper(looper);
	}


}

//Help function for converting minutes to milliseconds
function min2MillSecs(mins) {
	return mins*60*1000;
}

module.exports = InteractionController;
