/* global calculateLength, calculateRadians */

window._wires = [];

function Wire(a, b) {
  this.a = a;
  this.b = b;

  this.uuid = 'wire#' + a.uuid + '/' + b.uuid;

  window._wires.push(this);
}


Wire.prototype.getElement = function() {
  if (this.elem) return this.elem;

  let wireElem = document.createElement('div');

  wireElem.uuid = this.uuid;
  wireElem.className = 'wire';

  wireElem.addEventListener('click', this.clicked.bind(this));

  this.applyElement(wireElem);

  this.elem = wireElem;
  return wireElem;
};


Wire.prototype.clicked = function(event) {
  if (event.ctrlKey) {
    this.destroy();
  }
};


Wire.prototype.applyElement = function(wireElem) {
  // a should always be left from b
  if (this.a.x > this.b.x) {
    // swap a and b
    let _ = this.b;
    this.b = this.a;
    this.a = _;
  }

  // Process gate coordinates
  let ax = this.a.x,
      ay = this.a.y,
      bx = this.b.x,
      by = this.b.y;

  if (isNaN(ax + ay + bx + by)) {
    console.error("Failed to create wire: invalid coordinates", ax, ay, bx, by);
    return;
  }

  // Convert top left to center coordinates
  ax += this.a.port_width / 2;
  ay += this.a.port_width / 2;
  bx += this.b.port_width / 2;
  by += this.b.port_width / 2;


  // Calculate length
  let length = calculateLength(ax, ay, bx, by);

  wireElem.style.height = length + 'px';


  // Calculate position
  let x = ax + window.WIRE_WIDTH / 2,
      y = ay + window.WIRE_WIDTH / 2;

  wireElem.style.left = x + 'px';
  wireElem.style.top = y + 'px';


  // Calculate rotation
  let rotation = calculateRadians(ax, ay, bx, by) - Math.PI / 2;

  wireElem.style.transform = 'rotate(' + rotation + 'rad)';
  wireElem.style.transformOrigin = 'top left';
}


Wire.prototype.draw = function(circuitElem) {
  circuitElem.appendChild(this.getElement());
};


Wire.prototype.destroy = function() {
  this.elem.parentNode && this.elem.parentNode.removeChild(this.elem);
  this.elem = null;

  // Remove from global wires list
  let uuid = this.uuid;
  window._wires = window._wires.filter(wire => wire.uuid != uuid);
};


Wire.prototype.redraw = function(circuitElem) {
  if (! this.elem) {
    this.getElement();
  }

  this.applyElement(this.elem);
  this.draw(circuitElem);
};


define(() => Wire);
