use gate::*;
use port::*;
use portgate::*;
use connection::*;

use std::collections::HashMap;


#[derive(Debug, Clone)]
pub struct Circuit {
    pub gates: HashMap<String, Gate>,
}


impl Circuit {
    pub fn new() -> Circuit {
        Circuit {
            gates: HashMap::new(),
        }
    }


    pub fn connect(&mut self, connection: &Connection) {
        // gate_from -> gate_to
        {
            let gate_from = self.gates.get_mut(&connection.from.gate_uuid).unwrap();
            gate_from.ports.get_mut(&connection.from.port_uuid).unwrap().connections.push(connection.clone());
        }

        // gate_to -> gate_from
        {
            let gate_to = self.gates.get_mut(&connection.to.gate_uuid).unwrap();
            gate_to.ports.get_mut(&connection.to.port_uuid).unwrap().connections.push(connection.clone().reverse());
        }
    }


    pub fn get_inputs(&self) -> Vec<String> {
        self.gates
            .iter()
            .filter(|&(_, gate)| gate.gate_type == "IN")
            .map(|(name, _)| name.clone() + ":O0")
            .collect()
    }


    pub fn get_outputs(&self) -> Vec<String> {
        self.gates
            .iter()
            .filter(|&(_, gate)| gate.gate_type == "OUT")
            .map(|(name, _)| name.clone() + ":I0")
            .collect()
    }


    pub fn get_gate_by_uuid(&self, gate_uuid: &String) -> &Gate {
        self.gates
            .iter()
            .find(|&(uuid, _)| uuid == gate_uuid)
            .unwrap()
            .1
    }


    pub fn get_mut_gate_by_uuid(&mut self, gate_uuid: &String) -> &mut Gate {
        self.gates
            .iter_mut()
            .find(|&(uuid, _)| uuid == gate_uuid)
            .unwrap()
            .1
    }


    pub fn get_port_by_portgate(&self, portgate: &PortGate) -> &Port {
        self.get_gate_by_uuid(&portgate.gate_uuid)
            .get_port_by_uuid(&portgate.port_uuid)
    }


    pub fn get_mut_port_by_portgate(&mut self, portgate: &PortGate) -> &mut Port {
        self.get_mut_gate_by_uuid(&portgate.gate_uuid)
            .get_mut_port_by_uuid(&portgate.port_uuid)
    }


    pub fn spread_port(&mut self, portgate: &PortGate) {
        let (state, connections) = {
            let port = self.get_port_by_portgate(portgate).clone();

            (port.state.clone(), port.connections.clone())
        };

        for connection in connections {
            let reset_states = {
                let gate = self.get_mut_gate_by_uuid(&connection.to.gate_uuid);

                {
                    let port = gate.get_mut_port_by_uuid(&connection.to.port_uuid);
                    port.set_state(state);
                }

                gate.reset_state()
            };

            for portgate in reset_states {
                self.spread_port(&portgate);
            }
        }
    }


    pub fn toggle_port(&mut self, portgate: &PortGate) {
        {
            let port = self.get_mut_port_by_portgate(portgate);
            port.toggle();
        }

        self.spread_port(portgate);
    }


    pub fn stringify(&self) -> String {
        let mut string = String::new();

        for (gate_uuid, gate) in &self.gates {
            string += &format!("{}: {}\n", gate_uuid, gate.stringify());
        }

        return string;
    }


    pub fn stringify_inputs(&self) -> String {
        self
            .get_inputs()
            .iter()
            .map(|input| {
                let portgate = PortGate::from(input.to_owned());

                format!("I {}: {}", portgate.gate_uuid, self.get_port_by_portgate(&portgate).state)
            })
            .collect::<Vec<String>>()
            .join("\n")
    }


    pub fn stringify_outputs(&self) -> String {
        self
            .get_outputs()
            .iter()
            .map(|output| {
                let portgate = PortGate::from(output.to_owned());

                format!("O {}: {}", portgate.gate_uuid, self.get_port_by_portgate(&portgate).state)
            })
            .collect::<Vec<String>>()
            .join("\n")
    }
}
