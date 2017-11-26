use port::*;
use portgate::*;

use std::collections::HashMap;


#[derive(Debug, Clone)]
pub struct Gate {
    pub uuid: String,
    pub gate_type: String,
    pub ports: HashMap<String, Port>,
}


impl Gate {
    pub fn new(uuid: String, gate_type: String) -> Gate {
        let mut ports: HashMap<String, Port> = HashMap::new();

        match &*gate_type {

            // TODO: These portnames are not static anymore!

            "OUT" => {
                ports.insert("I0".to_owned(), Port::new(PortType::In));
            },

            "IN" => {
                ports.insert("O0".to_owned(), Port::new(PortType::Out));
            },

            "AND" => {
                ports.insert("I0".to_owned(), Port::new(PortType::In));
                ports.insert("I1".to_owned(), Port::new(PortType::In));
                ports.insert("O2".to_owned(), Port::new(PortType::Out));
            },

            "OR" => {
                ports.insert("I0".to_owned(), Port::new(PortType::In));
                ports.insert("I1".to_owned(), Port::new(PortType::In));
                ports.insert("O2".to_owned(), Port::new(PortType::Out));
            },

            "NOT" => {
                ports.insert("I0".to_owned(), Port::new(PortType::In));
                ports.insert("O1".to_owned(), Port::new(PortType::Out));
            },

            _ => panic!("Unknown gate type {}", gate_type),
        }

        Gate {
            uuid: uuid,
            gate_type: gate_type.to_owned(),
            ports: ports,
        }
    }


    pub fn reset_state(&mut self) -> Vec<PortGate> {
        let mut to_spread = vec! { };

        match &*self.gate_type {

            // TODO: These portnames are not static anymore!

            "AND" => {
                let state = {
                    let i0 = self.ports.get("I0").unwrap();
                    let i1 = self.ports.get("I1").unwrap();

                    i0.state && i1.state
                };

                let o2 = self.ports.get_mut("O2").unwrap();
                o2.set_state(state);

                to_spread.push(PortGate {
                    gate_uuid: self.uuid.clone(),
                    port_uuid: "O2".to_owned(),
                });
            },


            "OR" => {
                let state = {
                    let i0 = self.ports.get("I0").unwrap();
                    let i1 = self.ports.get("I1").unwrap();

                    i0.state || i1.state
                };

                let o2 = self.ports.get_mut("O2").unwrap();
                o2.set_state(state);

                to_spread.push(PortGate {
                    gate_uuid: self.uuid.clone(),
                    port_uuid: "O2".to_owned(),
                });
            },


            "NOT" => {
                let state = {
                    let i0 = self.ports.get("I0").unwrap();

                    ! i0.state
                };

                let o1 = self.ports.get_mut("O1").unwrap();
                o1.set_state(state);

                to_spread.push(PortGate {
                    gate_uuid: self.uuid.clone(),
                    port_uuid: "O1".to_owned(),
                });
            },


            "OUT" => {

            },

            "IN" => {
                panic!("Set IN state?");
            },


            gate_type => panic!("Unknown gate type {}", gate_type),
        }


        return to_spread;
    }


    pub fn get_port_by_uuid(&self, port_uuid: &String) -> &Port {
        self
            .ports
            .get(port_uuid)
            .unwrap()
    }


    pub fn get_mut_port_by_uuid(&mut self, port_uuid: &String) -> &mut Port {
        self
            .ports
            .get_mut(port_uuid)
            .unwrap()
    }
}
