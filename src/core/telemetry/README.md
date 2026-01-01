# Network Stack


## Media Independent
| Layer | Design | Notes |
| --- | --- | --- |
| Application | Tasks/Solutions | Fuzzy here, but task-dependent |
| Session/Presentation | Decodes/encodes Packets! OP codes, etc.  | Decrypt and encrypt packet to individual tasks/solutions with each datatype |
<!-- | Session | ACKs, Vehicle ID | |  -->

## Protocol Specific
| Layer | Design | Notes |
| --- | --- | --- |
| Transport | UDP, port 40000 (all telemetry), retries | Makes sure packets are reliably sent and received to their proper destinations |
| Data Link / Network | Board-to-board connections (unique MAC, static IP) | Not used for direct things like UART. e.g. Arduino Ethernet library stack |
| Physical | Radio/Ethernet | The wires and stuff (Ethernet, HardwareSerial, etc.) |

# Implementation

## PacketWizard (Transport ←→ Session/Presentation)
Takes data to make protocol-independent data.

Down the model (high to low level):
- Takes in data (and length) from Tasks
- Outputs byte array to Transport layer with:
    - Timestamp milliseconds (4 bytes)
    - VID / Sequence Number (1 byte)
    - OP Code (1 byte)
    - Data length (1 byte)
    - Data (N byte)
    - Checksum (2 bytes)

Up the model (low to high level):
- Takes in raw byte array from Transport layer
- Decodes to TelemetryServer with:
    - Timestamp milliseconds (4 bytes)
    - VID / Sequence Number (1 byte)
    - Data length (1 byte)
    - Data (N byte)

## TelemetryServer (Transport ←→ Session/Presentation)
Sequencing and routing individual packets.

## Tasks (Presentation ←→ Application)
Presentation layer seems more complicated than it needs to be. Each tasks takes 

Down the model (high to low level):
- Takes in data (and length) from Tasks
- Outputs data and length to TelemetryServer

Up the model (low to high level):
- Takes in raw byte array from Transport layer
- Decodes to Tasks with:
    - Timestamp milliseconds (4 bytes)
    - VID / Sequence Number (1 byte)
    - Data length (1 byte)
    - Data (N byte)