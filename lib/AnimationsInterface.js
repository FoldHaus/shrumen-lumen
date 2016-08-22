class AnimationsInterface {
	constructor() {
		this.state = 'default';
		this.looper = null;
		this.animations = ["gradient", "colorwipe", "pulse", "sweep", "bubblesgold", "twinkles", "bubbles"];
	}

	setState(state) {
		var tempState = {
			"state": this.state
		};

		if (typeof state  != "string") {
			console.log("wrong state type");
		} else {
			tempState["state"] = state;
		}
		return tempState
	}

	setLooper(looper) {
		this.looper = looper;
	}

	next() {
		var anims = this.animations;
		var currentIndex = anims.indexOf(this.state);
		var nextIndex = (currentIndex + 1) % anims.length;
		
		this.state = anims[nextIndex];

		console.log("New State: " + this.state);

		return this.state;
	}

	getState() {
		return this.state;
	}

}

module.exports = AnimationsInterface;
