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

  // Add gates to output
  LOOP_OBJ(this.gates).forEach((uuid, gate) => {
    output.gates[uuid] = {
      // Only store type
      type: gate.type,
    };
  });


  // Add wires to output
  this.wires.forEach(wire => {
    output.wires.push({
      a: wire.a.uuid,
      b: wire.b.uuid,
    });
  });


  return output;
};


define(() => Circuit);
