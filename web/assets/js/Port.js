function Port(gate, name) {
  this.name = name;
  this.gate = gate;
  this.uuid = gate.uuid + ':' + name;
  this.type = name.charAt(0);

  this.connections = [];
}


Port.prototype.attachPort= function(newport) {
  if (this.connections.contains(newport)) {
    // Do not re-attach
    return;
  }

  this.connections.push(newport);

  newport.attachPort(this);
};


Port.prototype.detachPort = function(newport) {
  if (! this.connections.contains(newport)) {
    // Do not detach if not attached
    return;
  }

  this.connections.remove(newport);

  newport.detachPort(this);
};

define(() => Port);
