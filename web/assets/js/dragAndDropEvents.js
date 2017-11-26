/* global Gate, redrawAllWires */

let dragged = null;


function dragstart(event) {
  // element is picked up
  dragged = event.target;

  if (dragged.draggable) {
    // Otherwise Firefox won't drag this object
    event.dataTransfer.setData('text/plain', 'Yes, I am dragging');
  }
  else {
    event.preventDefault();
  }
}


function dragend(event) {
  // element is released
  dragged = null;
}


function dragover(event) {
  // element enters new zone

  if (event.target.id == 'circuit' || event.target.classList.contains('trash')) {
    // element may be dropped here
    event.preventDefault();
  }
}


function dragenter(event) {
  // element enters droppable zone
}


function dragleave(event) {
  // element leaves droppable zone
}


function drop(event) {
  // element gets dropped
  event.preventDefault();

  // If element is dropped in the trash
  if (event.target.classList.contains('trash')) {
    window._gates[dragged.uuid].destroy();
    return;
  }

  let gate;

  if (dragged.dataset.clone == "true") {
    // Clone old gate
    let type = dragged.dataset.type;
    gate = new Gate(type);

    if (dragged.classList.contains('gate-custom')) {
      gate.setBgColor(dragged.style.backgroundColor);
    }
  }
  else {
    // Re-use old gate
    gate = window._gates[dragged.uuid];
  }

  let x = event.clientX;
  let y = event.clientY;

  // Convert top left to center
  x -= window.GATE_WIDTH / 2;
  y -= window.GATE_WIDTH / 2;

  gate.setPosition(x, y);

  let circuitElem = event.target;
  gate.draw(circuitElem);

  // Redraw wires
  redrawAllWires();
}


document.addEventListener('dragstart', dragstart, false);
document.addEventListener('dragend', dragend, false);
document.addEventListener('dragover', dragover, false);
document.addEventListener('dragenter', dragenter, false);
document.addEventListener('dragleave', dragleave, false);
document.addEventListener('drop', drop, false);
