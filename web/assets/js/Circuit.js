/* global LOOP_OBJ */

function Circuit(gates, wires) {
  this.gates = gates;
  this.wires = wires;
}


Circuit.prototype.generateJSON = function() {
  let output = {
    gates: {},
    wires: [],
  };

  LOOP_OBJ(this.gates).forEach((name, gate) => {
    output.gates[gate.uuid] = {
      type: gate.type,
    };
  });

  this.wires.forEach(wire => {
    output.wires.push({
      a: wire.a.uuid,
      b: wire.b.uuid,
    });
  });

  return output;
};

define(() => Circuit);
