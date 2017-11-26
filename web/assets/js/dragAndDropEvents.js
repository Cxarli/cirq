/* global Gate, redrawAllWires, LOOP_OBJ */

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
    if (dragged.classList.contains('gate-custom') && dragged.dataset.clone == "true") {
      // Custom gate in the toolbox
      let type = dragged.dataset.type;
      if (confirm("Delete " + type + " ?")) {
        dragged.parentNode.removeChild(dragged);
        dragged = null;
        delete window._customGates[type];
        return;
      }
    }

    let gate = window._gates[dragged.uuid];
    if (gate) gate.destroy();
    return;
  }

  let gate;

  if (dragged.dataset.clone == "true") {
    // Clone old gate
    let type = dragged.dataset.type;
    gate = new Gate(type, parseInt(dragged.dataset.in), parseInt(dragged.dataset.out));

    if (dragged.classList.contains('gate-custom')) {
      gate.setBgColor(dragged.style.backgroundColor);

      // Rename ports to the names of the custom gate ports
      let customGate = window._customGates[type];
      let ionames = customGate.ionames;
      let ins = LOOP_OBJ(customGate.circuit.gates).filter((uuid, gate) => gate.type == 'IN').values();
      let outs = LOOP_OBJ(customGate.circuit.gates).filter((uuid, gate) => gate.type == 'OUT').values();

      LOOP_OBJ(gate.ports).forEach((name, port) => {
        if (port.type == 'IN') {
          port.setName(ionames[ins.pop().uuid]);
        }
        else if (port.type == 'OUT') {
          port.setName(ionames[outs.pop().uuid]);
        }
        else {
          console.error("Ehm, help? port.type ==", port.type);
        }
      });
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
