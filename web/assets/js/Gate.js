/* global Port, guid */

window._gates = {};

function Gate(type) {
  this.uuid = guid();

  this.type = type;

  this.ports = {
    'I0': new Port(this, 'I0'),
    'I1': new Port(this, 'I1'),
    'O0': new Port(this, 'O0'),
  };

  window._gates[this.uuid] = this;
}


Gate.prototype.attachPortToPort = function(port, newport) {
  this.ports[port].attachPort(newport);
};


Gate.prototype.detachPortFromPort = function(port, newport) {
  this.ports[port].detachPort(newport);
};


Gate.prototype.setBgColor = function(bgColor) {
  this.bgColor = bgColor;
};


Gate.prototype.getElement = function() {
  if (this.elem) return this.elem;

  let elem = document.createElement('div');

  elem.uuid = this.uuid;
  elem.className = 'gate gate-' + this.type;

  if (this.bgColor) elem.style.backgroundColor = this.bgColor;

  elem.draggable = true;
  elem.dataset.type = this.type;
  elem.dataset.clone = false;

  this.elem = elem;
  return elem;
};


Gate.prototype.draw = function(circuitElem) {
  let gateElem = this.getElement();
  circuitElem.appendChild(gateElem);
};


Gate.prototype.setPosition = function(x, y) {
  let gateElem = this.getElement();

  // Set position
  gateElem.style.left = x + 'px';
  gateElem.style.top = y + 'px';

  // Set coordinates
  gateElem.x = x;
  gateElem.y = y;
}


Gate.prototype.destroy = function() {
  if (! this.elem) return;

  // Remove element
  this.elem.parentNode.removeChild(this.elem);

  // Remove from global gates list
  delete window._gates[this.uuid];

  // Remove wires which connect to this element
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

define(() => Gate);
