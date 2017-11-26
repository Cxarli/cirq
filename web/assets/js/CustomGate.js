/* globals LOOP_OBJ */


function CustomGate(type, ionames, circuit) {
  this.type = type;
  this.ionames = ionames;
  this.circuit = circuit;
}


CustomGate.prototype.in = function() {
  let _in = 0;

  LOOP_OBJ(this.circuit.gates).forEach((name, gate) => {
    if (gate.type == 'IN') _in++;
  });

  return _in;
};


CustomGate.prototype.out = function() {
  let _out = 0;

  LOOP_OBJ(this.circuit.gates).forEach((name, gate) => {
    if (gate.type == 'OUT') _out++;
  });

  return _out;
};


define(() => CustomGate);
