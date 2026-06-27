import asyncio
import socket
import struct
from typing import List, Any

class GloveUDPSender:
    def __init__(self, glove_ip: str, port: int, haptics_engine):
        self.glove_ip = glove_ip
        self.port_out = port
        self.haptics_engine = haptics_engine

        #self.sock = None
        self.transport = None

    def _pack_motor_controls(self):
        #motor_PWM_values = self.haptics_engine._get_values

        packet_format = "<h" + 30 * "B"

        return struct.pack(packet_format, 0xABCD, *motor_PWM_values)


    def _receive_data(self):
        #Maybe remove the while loop here and put it in main?
        while True:
            data, address = self.sock.recvfrom(4096)
            self._handle_data(data, address)
            

    def _handle_data(self, data, address):
        print(f"Received {len(data)} bytes from {address}.")

    async def _start_udp_server(self):
        loop = asyncio.get_running_loop()
        transport, _ = await loop.create_datagram_endpoint(asyncio.DatagramProtocol, remote_addr = (self.glove_ip, self.port))

        try:
            while True:
                packed_data = self._pack_motor_controls
                self.transport.sendto(packed_data)

                await asyncio.sleep(0.02)


        except asyncio.CancelledError:
            self.transport.close()
            print("ESP32 Sender has closed.")

    
