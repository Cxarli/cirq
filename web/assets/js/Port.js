window._ports = {};

function Port(gate, name, width) {
  this.name = name;
  this.gate = gate;
  this.uuid = gate.uuid + ':' + name;
  this.type = (name.charAt(0) == 'I' ? 'in' : 'out');
  this.id = parseInt(name.substring(1));

  this.width = width;

  window._ports[this.uuid] = this;

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


Port.prototype.getElement = function() {
  if (this.portElem) return this.portElem;

  let portElem = document.createElement('div');
  portElem.className = 'port port-' + this.type;
  portElem.uuid = this.uuid;

  portElem.port_width = this.width;
  portElem.style.height = portElem.style.width = this.width + 'px';

  portElem.innerHTML = this.name;

  this.portElem = portElem;
  return portElem;
};


Port.prototype.setPosition = function(x, y) {
  if (! this.portElem) this.getElement();

  this.portElem.style.left = (x + window.GATE_BORDER) + 'px';
  this.portElem.style.top = (y + window.GATE_BORDER) + 'px';

  this.portElem.x = x;
  this.portElem.y = y;
};


Port.prototype.destroy = function() {
  // Remove element
  if (this.portElem) this.portElem.parentNode.removeChild(this.portElem);

  // Delete from global list
  delete window._ports[this.uuid];

  // Remove wires which connect to this port
  if (window._wires) {
    let uuid = this.uuid;

    window._wires = window._wires.filter(wire => {
      // Check if wire connects this element
      if (wire.a.uuid == uuid || wire.b.uuid == uuid) {
        wire.destroy();
        return false;
      }

      return true;
    });
  }
};

define(() => Port);
