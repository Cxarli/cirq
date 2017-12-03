/* globals Circuit, CustomGate, Template, HTMLToElem, LOOP_OBJ, CLONE */


const GATE_INNER_TEMPLATE = new Template("{{TYPE}}<br>&nbsp; &lt; {{IN}}<br>&nbsp; &gt; {{OUT}}");

const CUSTOM_GATE_TEMPLATE = new Template(
  '<div' +
    ' class="gate gate-custom gate-{{TYPE}}"'+
    ' style="background-color: {{BGCOLOR}}"' +
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

  let bgcolor = prompt("Color?");
  if ( bgcolor === null ) return;

  let circuit = new Circuit(CLONE(window._gates), CLONE(window._wires));

  let ionames = {};


  // Make sure all in- and outputs have names
  let failed = false;
  LOOP_OBJ(window._gates).forEach((uuid, gate) => {
    if (failed) return;

    if (gate.type == 'IN' || gate.type == 'OUT') {
      // get port
      let port = gate.ports['I0'] || gate.ports['O0'];

      // check if name is set
      if (! port.nameset) {
        alert("Failed to create custom gate: Not all in- and outputs have names.");
        failed = true;
        return;
      }

      // add port name to ionames
      ionames[uuid] = port.name;
    }
  });
  if (failed) return;


  // Create new gate
  let newgate = new CustomGate(type, ionames, circuit);
  window._customGates[type] = newgate;
  console.log(newgate);


  // Create element
  // TODO: Move logic to CustomGate.js
  let gateHTML = CUSTOM_GATE_TEMPLATE.apply({
    type: type,
    bgcolor: bgcolor,
    in: newgate.in(),
    out: newgate.out(),
  });

  // Add element
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

addInfoToGates();


function clearCircuit() {
  // Destroy all wires
  window._wires.forEach(wire => {
    wire.destroy();
  });

  // Destroy all gates
  LOOP_OBJ(window._gates).forEach((name, gate) => {
    gate.destroy();
  });


  // Check that everything is gone
  let circuit = document.getElementById('circuit');

  if (circuit.children.length > 0) {
    console.log("circuit not empty?");
    console.log(circuit.children);

    // force remove child
    circuit.children.forEach(child => circuit.removeChild(child));
  }

  if (LOOP_OBJ(window._gates).length() > 0) {
    console.log("_gates not empty?");
    console.log(window._gates);

    // force remove gates
    window._gates = {};
  }

  if (window._wires > 0) {
    console.log("_wires not empty?");
    console.log(window._wires);

    // force remove wires
    window._wires = [];
  }
}


function generateJSON() {
  // Create current circuit
  let circuit = new Circuit(CLONE(window._gates), CLONE(window._wires));

  // Get custom gates
  let customGates = window._customGates;
  customGates = LOOP_OBJ(customGates)
    // convert inner circuits to json
    .map((_, customGate) => customGate.circuit.generateJSON())
    .removeLoop();

  return {
    circuit: circuit.generateJSON(),
    customGates: customGates,
  };
}


function generateFile() {
  let json = generateJSON();
  /*
    {
     "circuit": {
      "gates": {
       "eec2fc01": { "type": "AND" },
       "da2ecd25": { "type": "IN" },
       "daa53637": { "type": "IN" },
       "2aedae8e": { "type": "OUT" },
       "6306ee7f": { "type": "NOT" }
      },
      "wires": [
       { "a": "da2ecd25:O0", "b": "eec2fc01:I0" },
       { "a": "daa53637:O0", "b": "eec2fc01:I1" },
       { "a": "eec2fc01:O2", "b": "6306ee7f:I0" },
       { "a": "6306ee7f:O1", "b": "2aedae8e:I0" }
      ]
     },
     "customGates": {}
    }
  */

  let output = "";

  /*
    NAND

    [gates] 5
    da2ecd25 IN
    daa53637 IN
    eec2fc01 AND
    6306ee7f NOT
    2aedae8e OUT

    [wires] 4
    da2ecd25:O0 eec2fc01:I0
    daa53637:O0 eec2fc01:I1
    eec2fc01:O0 6306ee7f:I0
    6306ee7f:O0 2aedae8e:I0
  */

  // TODO: Get this name from somewhere?
  output += json.name + "\n";
  output += "\n";
  output += "[gates] " + LOOP_OBJ(json.circuit.gates).length() + "\n";
  LOOP_OBJ(json.circuit.gates).forEach((uuid, data) => uuid + " " + data.type + "\n");
  output += "\n";
  output += "[gates] " + LOOP_OBJ(json.circuit.wires).length() + "\n";
  json.circuit.wires.forEach(wire => wire.a + " " + wire.b + "\n");

  return output;
}
