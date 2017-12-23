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

    let name = prompt("Enter a name for this circuit: ");

    if (! name) return;

    return {
        name: name,
        circuit: circuit.generateJSON(),
        customGates: customGates,
    };
}


function generateFile(json) {
    let output = "";

    /*
    full_adder

    [gates] 8
    0e36e9ea IN #I0
    63f0d9e3 IN #I1
    b9f8820d IN #Ci
    2c9ced3a OUT #S
    57f26486 OUT #Co
    e16e5e97 OR
    3752723b half_adder
    45243a79 half_adder

    [wires] 8
    0e36e9ea:I0 3752723b:I0
    63f0d9e3:I1 3752723b:I1
    3752723b:S 45243a79:I0
    b9f8820d:Ci 45243a79:I1
    45243a79:S 2c9ced3a:S
    3752723b:C e16e5e97:I0
    45243a79:C e16e5e97:I1
    e16e5e97:O0 57f26486:Co
    */

    // TODO: Explicitly state the circuit's in- and output names

    output += json.name + "\n";

    output += "\n";

    output += "[gates] " + LOOP_OBJ(json.circuit.gates).length() + "\n";
    LOOP_OBJ(json.circuit.gates).forEach(
        (uuid, data) => {
            output += uuid + " " + data.type + "\n"
        }
    );

    output += "\n";

    output += "[wires] " + LOOP_OBJ(json.circuit.wires).length() + "\n";
    json.circuit.wires.forEach(wire => output += wire.a + " " + wire.b + "\n");

    output += "\n";

    LOOP_OBJ(json.customGates).forEach((name, circuit) => output += generateFile({
        name: name,
        circuit: circuit,
        customGates: {}
    }) + "\n");

    return output;
}
