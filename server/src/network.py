import asyncio
import socket
import struct
from typing import List, Any

from src.haptics_engine import HapticsEngine

class GloveDatagramProtocol(asyncio.DatagramProtocol):
    def __init__(self, data_received_callback):
        self.data_received_callback = data_received_callback
        self.transport = None

    def connection_made(self, transport):
        self.transport = transport
    
    def datagram_received(self, data, addr):
        self.data_received_callback(data, addr)


class GloveUDPSender:
    def __init__(self, glove_ip: str, local_ip: str, port_in: int, port_out: int, haptics_engine: HapticsEngine):
        self.glove_ip = glove_ip
        self.local_ip = local_ip
        self.port_in = port_in
        self.port_out = port_out
        self.haptics_engine = haptics_engine

        self.inputs = {
            "joy_x": 0,
            "joy_y": 0,
            "joy_btn": 0,
            "btn_a": 0,
            "btn_b": 0
        }

        self.transport = None
        self.protocol = None

    def _pack_motor_controls(self):
        motor_PWM_values = self.haptics_engine._get_values()

        packet_format = "<h" + 30 * "B"

        return struct.pack(packet_format, 0x03BF, *[int(val) for val in motor_PWM_values])         

    def _handle_data(self, data, address):
        incoming_packet_format = '<3H3B'
        incoming_packet_data = struct.unpack(incoming_packet_format, data)

        self.inputs["joy_x"] = incoming_packet_data[1]
        self.inputs["joy_y"] = incoming_packet_data[2]
        self.inputs["joy_btn"] = incoming_packet_data[3]
        self.inputs["btn_a"] = incoming_packet_data[4]
        self.inputs["btn_b"] = incoming_packet_data[5]


        print(f"Received {len(data)} bytes from {address}.")
        print(incoming_packet_data)

    async def _start_udp_server(self, event_loop):        
        self.transport, self.protocol = await event_loop.create_datagram_endpoint(lambda: GloveDatagramProtocol(self._handle_data), local_addr = (self.local_ip, self.port_in))

        try:
            while True:
                packed_data = self._pack_motor_controls()
                self.transport.sendto(packed_data, (self.glove_ip, self.port_out))

                await asyncio.sleep(0.02)


        except asyncio.CancelledError:
            self.transport.close()
            print("ESP32 Sender has closed.")

    
