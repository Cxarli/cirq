#[derive(Debug, Clone)]
pub struct PortGate {
    pub gate_uuid: String,
    pub port_uuid: String,
}


impl PortGate {
    pub fn stringify(&self) -> String {
        format!("{}:{}", self.gate_uuid, self.port_uuid)
    }
}


impl From<String> for PortGate {
    fn from(port_name: String) -> PortGate {
        let gate_uuid = port_name.split(":").nth(0).unwrap().to_owned();
        let port_uuid = port_name.split(":").nth(1).unwrap().to_owned();

        PortGate {
            gate_uuid,
            port_uuid,
        }
    }
}
