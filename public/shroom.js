class ShroomAPI {
  constructor(ip, $http) {
    this.ip = ip;
    this.$http = $http;
    this.connected = true;
  }

  updateState() {
    var self = this;
    self.getState();
    self.getLinearActuator();
    self.getWeightSensor();
  }

  getState() {
    var self = this;
    this.$http.get(this.ip + "/state", {timeout: 1000}).then(function(data){
      self.data = data.data;
      self.connected = true;
    }, function(){
      self.connected = self.connected && false;
    });
  }

  getWeightSensor() {
    var self = this;
    this.$http.get(this.ip + "/weightsensor", {timeout: 1000}).then(function(data){
      self.weightsensor = data.data;
      self.connected = true;
    }, function(){
      self.connected = self.connected && false;
    });
  }

  getLinearActuator() {
    var self = this;
    this.$http.get(this.ip + "/linearactuator", {timeout: 1000}).then(function(data){
      self.actuator = data.data;
      self.connected = true;
    }, function(){
      self.connected = self.connected && false;
    });
  }

}



angular.module('todoApp', [])
  .controller('ShroomController', function($http) {
    var self = this;
    this.ips = [
      'http://10.1.3.115:3000',
      'http://1.1.1.1:3000',
      'http://1.1.1.2:3000',
      'http://1.1.1.3:3000',
      'http://1.1.1.4:3000',
      'http://1.1.1.5:3000'
    ];

    this.shrooms = []

    for(var ipI in this.ips){
      var ip = this.ips[ipI];
      var shroom = new ShroomAPI(ip, $http);
      this.shrooms.push(shroom);
    }

    setInterval(function(){
      for(var shroom in self.shrooms){
        self.shrooms[shroom].updateState();
      }
    }, 500);
  });