use portgate::*;

#[derive(Debug, Clone)]
pub struct Connection {
    pub from: PortGate,
    pub to: PortGate,
}


impl Connection {
    pub fn new(from: PortGate, to: PortGate) -> Connection {
        Connection {
            from,
            to
        }
    }


    pub fn reverse(self) -> Connection {
        Connection {
            from: self.to,
            to: self.from,
        }
    }
}
