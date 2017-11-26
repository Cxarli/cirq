use connection::*;


#[derive(Debug, Clone)]
pub struct Port {
    pub port_type: PortType,
    pub state: bool,
    pub connections: Vec<Connection>,
}


#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PortType {
    In,
    Out,
}


impl Port {
    pub fn new(port_type: PortType) -> Port {
        Port {
            port_type: port_type,
            state: false,
            connections: vec! {},
        }
    }


    #[allow(dead_code)]
    pub fn on(&mut self) {
        self.state = true;
    }


    #[allow(dead_code)]
    pub fn off(&mut self) {
        self.state = false;
    }


    pub fn toggle(&mut self) {
        self.state = ! self.state;
    }


    pub fn set_state(&mut self, state: bool) {
        self.state = state;
    }


    pub fn stringify(&self) -> String {
        let mut string = String::new();

        string += if self.state { "true" } else { "false" };

        return string;
    }
}
