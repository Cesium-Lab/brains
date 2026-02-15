# Network Stack


## Media Independent
| Layer | Design | Notes |
| --- | --- | --- |
| Application | Tasks/Solutions | Fuzzy here, but task-dependent |
| Session/Presentation | Packet encoding/decoding  | Decrypt and encrypt packet to individual tasks/solutions with each datatype. OP codes, etc. |
<!-- | Session | ACKs, Vehicle ID | |  -->

## Protocol Specific
| Layer | Design | Notes |
| --- | --- | --- |
| Transport | UDP, port 40000 (all telemetry), retries | Makes sure packets are reliably sent and received to their proper destinations |
| Data Link / Network | Board-to-board connections (unique MAC, static IP) | Not used for direct things like UART. e.g. Arduino Ethernet library stack |
| Physical | Radio/Ethernet | The wires and hardware (Ethernet, HardwareSerial, etc.) |

# Implementation

## PacketWizard (Transport ←→ Session/Presentation)
Functional class that takes data to make protocol-independent data.

Down the stack (high → low):
- Takes in data (and length) from TelemetryServer's queue
- Encodes byte array to Transport layer with:
  - Timestamp milliseconds (4 bytes)
  - VID (5 bits) / Sequence Number (2 bits) - (1 byte)
  - OP Code (1 byte)
  - Data length (1 byte)
  - Data (N bytes)
  - Checksum (2 bytes)
- Sends to lower transport layer

Up the stack (low → high):
- Takes in raw byte array from Transport layer
- Decodes to TelemetryServer with:
  - Timestamp milliseconds (4 bytes)
  - VID (5 bits) / Sequence Number (2 bits) - (1 byte)
  - Data length (1 byte)
  - Data (N bytes)

## TelemetryServer (Session/Presentation)
Straight-up lives at this layer

Down the stack (high → low):
- Splits message from Task into 1 or more packets
- Adds header
  - Timestamp milliseconds (4 bytes)
  - VID (5 bits) / Sequence Number (2 bits) - (1 byte)
  - Data length (1 byte)
  - Data (N bytes)
  - Checksum (2 bytes)
- Puts in its OWN queue for the PacketWizard to put into lower layers

Up the stack (low → high):
- Received decoded packet with
  - Timestamp milliseconds (4 bytes)
  - VID (5 bits) / Sequence Number (2 bits) - (1 byte)
  - Data length (1 byte)
  - Data (N bytes)
- Reassembles multi-packet messages based on VID and SEQ number
- Routes to task

## Tasks (Presentation ←→ Application)

Down the stack (high → low):
- Creates data format into a long byte array
- Outputs data and length to TelemetryServer

Up the stack (low → high):
- Receives data from TelemetryServer
- Converts to task-specific structure

# Sequencing
Message is "hashed" based on Vehicle ID and Task OP Code, with specific data assembled based on SEQ number:
- 0 - Single packet
- 1 - Start of multi-packet sequence
- 2 - Continuation of sequence
- 3 - End of sequence

e.g. A 3-length packet would have SEQ numbers of [1,2,3], and a 2-length packet would have [1,3]