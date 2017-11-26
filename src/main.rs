extern crate serde_json;

use serde_json::*;

use std::fs::*;
use std::io::*;

mod port;
mod gate;
mod portgate;
mod circuit;
mod connection;

use gate::*;
use circuit::*;
use connection::*;
use portgate::*;


fn main() {
    let inputfile = "./tests/xor.json";

    let mut jsonstring = String::new();
    File::open(inputfile).unwrap().read_to_string(&mut jsonstring).ok();

    let json: Value = serde_json::from_str(&jsonstring).unwrap();

    let json_circuit = json.get("circuit").unwrap();
    let json_gates = json_circuit.get("gates").unwrap().as_object().unwrap();
    let json_wires = json_circuit.get("wires").unwrap().as_array().unwrap();

    let mut circuit = Circuit::new();

    for (uuid, json_gate) in json_gates {
        let gate_type = json_gate.get("type").unwrap().as_str().unwrap().to_owned();
        let gate = Gate::new(uuid.to_owned(), gate_type);

        circuit.gates.insert(uuid.to_owned(), gate);
    }


    for json_wire in json_wires {
        let port_from = json_wire.get("a").unwrap().as_str().unwrap().to_owned();
        let port_to = json_wire.get("b").unwrap().as_str().unwrap().to_owned();

        let connection = Connection::new(
            PortGate::from(port_from),
            PortGate::from(port_to),
        );

        circuit.connect(&connection);
    }


    let inputs = circuit.get_inputs();

    // Prepare circuit
    for input in &inputs {
        circuit.spread_port(&PortGate::from(input.to_owned()));
    }

    println!("inputs: {}", circuit.get_inputs().len());
    println!("outputs: {}", circuit.get_outputs().len());


    println!("{}\n{}", circuit.stringify_inputs(), circuit.stringify_outputs());

    println!("####");
    circuit.toggle_port(&PortGate::from(inputs[0].to_owned()));
    println!("{}\n{}", circuit.stringify_inputs(), circuit.stringify_outputs());

    println!("####");
    circuit.toggle_port(&PortGate::from(inputs[1].to_owned()));
    circuit.toggle_port(&PortGate::from(inputs[0].to_owned()));
    println!("{}\n{}", circuit.stringify_inputs(), circuit.stringify_outputs());

    println!("####");
    circuit.toggle_port(&PortGate::from(inputs[0].to_owned()));
    println!("{}\n{}", circuit.stringify_inputs(), circuit.stringify_outputs());
}
