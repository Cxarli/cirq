/* globals Circuit, CustomGate, Template, HTMLToElem, LOOP_OBJ, CLONE */

const GATE_INNER_TEMPLATE = new Template("{{TYPE}}<br>&nbsp; &lt; {{IN}}<br>&nbsp; &gt; {{OUT}}");
const CUSTOM_GATE_TEMPLATE = new Template(
  '<div' +
    ' class="gate gate-custom gate-{{TYPE}}"'+
    ' style="background-color: {{COLOR}}"' +
    ' draggable="true"' +
    ' data-clone="true"' +
    ' data-type="{{TYPE}}"' +
    ' data-in="{{IN}}"' +
    ' data-out="{{OUT}}">' +
      GATE_INNER_TEMPLATE.html +
  '</div>'
);

window._customGates = [];


function createCustomGateFromCurrentCircuit() {
  let type = prompt("Type?");
  if ( type === null ) return;

  let color = prompt("Color?");
  if ( color === null ) return;

  let circuit = new Circuit(CLONE(window._gates), CLONE(window._wires));

  let newgate = new CustomGate(type, circuit);
  window._customGates[type] = newgate;
  console.log(newgate);

  let gateHTML = CUSTOM_GATE_TEMPLATE.apply({
    type: type,
    color: color,
    in: newgate.in(),
    out: newgate.out(),
  });

  let gateElem = HTMLToElem(gateHTML);
  document.querySelector('.toolbox .box.custom').appendChild(gateElem);
}


function addInfoToGates() {
  let gates = document.querySelectorAll('.toolbox .gate');

  gates.forEach(gate => {
    gate.innerHTML = GATE_INNER_TEMPLATE.apply({
      type: gate.dataset.type,
      in: gate.dataset.in,
      out: gate.dataset.out,
    });
  });
}


function clearCircuit() {
  window._wires.forEach(wire => {
    wire.destroy();
  });

  LOOP_OBJ(window._gates).forEach((name, gate) => {
    gate.destroy();
  });


  // Checks that everything is gone
  let circuit = document.getElementById('circuit');

  if (circuit.children.length > 0) {
    console.log("circuit not empty?");
    console.log(circuit.children);

    circuit.children.forEach(child => circuit.removeChild(child));
  }

  if (LOOP_OBJ(window._gates).length() > 0) {
    console.log("_gates not empty?");
    console.log(window._gates);

    window._gates = {};
  }

  if (window._wires > 0) {
    console.log("_wires not empty?");
    console.log(window._wires);

    window._wires = [];
  }
}


function generateJSON() {
  let circuit = new Circuit(window._gates, window._wires);
  let customGates = window._customGates;

  customGates = LOOP_OBJ(customGates).map((name, customGate) => customGate.circuit.generateJSON());

  return {
    circuit: circuit.generateJSON(),
    customGates: customGates,
  };
}


addInfoToGates();
