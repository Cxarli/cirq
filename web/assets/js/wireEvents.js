/* global Wire */

let firstTarget = null, secondTarget = null;

function mousedown(event) {
  // Make sure SHIFT is pressed
  if (! event.shiftKey) return;

  firstTarget = event.target;
}


function mouseup(event) {
  // Make sure we got a first target
  if (! firstTarget) return;

  secondTarget = event.target;

  createWire();
}


function createWire() {
  if (! isValidTarget(firstTarget) || ! isValidTarget(secondTarget)) {
    console.error("Invalid destination for wire");
    return;
  }

  // Create wire
  let wire = new Wire(firstTarget, secondTarget);

  // Draw wire
  let circuitElem = document.getElementById('circuit');
  wire.draw(circuitElem);
}


function isValidTarget(target) {
  return target.classList.contains('gate') && target.dataset.clone != "true";
}


function redrawAllWires() {
  let circuitElem = document.getElementById('circuit');

  window._wires.forEach(wire => {
    wire.redraw(circuitElem);
  });
}


document.addEventListener('mousedown', mousedown, false);
document.addEventListener('mouseup', mouseup, false);
