#include <EthernetUdp.h>
#include <Ethernet_Generic_Impl.h>
#include <SPI.h>

IPAddress mcast(192, 168, 0, 3);
uint16_t mcast_port = 42069;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE};



char packetBuffer[255];                    // buffer to hold incoming packet
char ReplyBuffer[] = "ACK";            // a string to send back

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;


// Replace the default SPI object with one using your pins


void setup()
{
    Serial.begin(115200);

    while (!Serial && millis() < 5000);

    Serial.print("\nStart UDPSend on ");
    Serial.print(BOARD_NAME);
        
    // Default of MISO = D12, MOSI = D11, SCK = D13
    SPI.begin();

    pinMode(D10, OUTPUT);        // CS
    digitalWrite(D10, HIGH);

    Serial.println("SPI.begin() succeeded");
    Ethernet.init (SS);
    W5100.init();
    Serial.println(W5100.getChip());
        // Serial.println("A");
    Ethernet.begin(mac, mcast);
    Serial.print(F("Connected! IP address: "));
    Serial.println(Ethernet.localIP());

    Serial.print("Chip id: 0x");
    Serial.println(Ethernet.getChip(), HEX);

    delay(1000);

    Serial.println(F("\nStarting connection to server..."));
    // if you get a connection, report back via serial:
    Udp.begin(mcast_port);
}

void loop()
{
    // if there's data available, read a packet
    Udp.beginPacket(IPAddress(192, 168, 0, 255), 42069);
    Udp.write("Hello!");
    Udp.endPacket();

}