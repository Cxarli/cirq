/* global Port, guid, LOOP_OBJ */

window._gates = {};

function Gate(type, _in, _out) {
  this.uuid = guid();

  this.type = type;
  this.in = _in;
  this.out = _out;

  // Always 1 extra spot for the color
  let amount_ports = _in + _out + 1;
  this.portsPerWidth = Math.ceil(Math.sqrt(amount_ports));
  this.PORT_WIDTH = window.GATE_WIDTH / this.portsPerWidth;

  this.ports = { };

  // Add in-ports
  for (let i=0; i < _in; i++) {
    let name = 'I' + i;
    this.ports[name] = new Port(this, name, this.PORT_WIDTH);
  }

  // Add out-ports
  for (let i=0; i < _out; i++) {
    let name = 'O' + (i + _in);
    this.ports[name] = new Port(this, name, this.PORT_WIDTH);
  }

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
  if (this.gateElem) return this.gateElem;

  let gateElem = document.createElement('div');

  gateElem.uuid = this.uuid;
  gateElem.className = 'gate gate-' + this.type;

  if (this.bgColor) gateElem.style.backgroundColor = this.bgColor;

  gateElem.draggable = true;
  gateElem.dataset.type = this.type;
  gateElem.dataset.clone = false;


  // create ports
  LOOP_OBJ(this.ports).forEach((name, port) => {
    let portElem = port.getElement();

    gateElem.appendChild(portElem);
  });


  this.gateElem = gateElem;
  return gateElem;
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

  LOOP_OBJ(this.ports).forEach((name, port) => {
    let portX = x;
    let portY = y;

    portX += (port.id % this.portsPerWidth) * this.PORT_WIDTH;
    portY += Math.floor(port.id / this.portsPerWidth) * this.PORT_WIDTH;

    port.setPosition(portX, portY);
  });
}


Gate.prototype.destroy = function() {
  if (! this.gateElem) return;

  // Destroy ports
  LOOP_OBJ(this.ports).forEach((name, port) => {
    port.destroy();
  });

  // Remove element
  this.gateElem.parentNode.removeChild(this.gateElem);

  // Remove from global gates list
  delete window._gates[this.uuid];
};


define(() => Gate);
