function setState(state) {
	var tempState = {
		"state": "default"
	};
	if (typeof state  != "string") {
		console.log("wrong state type");
	} else {
		tempState["state"] = state;
	}
	return tempState
}

module.exports = setState;
