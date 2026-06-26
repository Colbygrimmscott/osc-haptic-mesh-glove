from pythonosc.osc_server import AsyncIOOSCUDPServer
from pythonosc.dispatcher import Dispatcher
from pythonosc.udp_client import SimpleUDPClient
import asyncio
from typing import List, Any

class VRCHATOSCBridge: 
    def __init__(self, ip: str, port_out: int, port_in: int, haptics_engine):
        """
        Initializes a VRChat OSC Listening server.

        ip: local IP (default is 127.0.0.1)
        port_out: port for VRChat to receive data from (default is 9001)
        port_in: port for VRChat to send data to (default is 9000)
        haptics_engine: reference to haptic feedback calculation engine object
        """
        self.ip = ip
        self.port_out = port_out
        self.port_in = port_in
        self.haptics_engine = haptics_engine

        self.dispatcher = Dispatcher()
        self.transport = None
        self.protocol = None
        self.server = None

        self.client = SimpleUDPClient(self.ip, self.port_out)

        self._initialize_routes()

    def _initialize_routes(self) -> None:
        """
        Maps specific VRChat OSC parameters to functions
        """
        self.dispatcher.map("/avatar/parameters/haptics*", self._handle_haptics)
        #self.dispatcher.map("/avatar/parameters*", self._handle_haptics)

    def _handle_haptics(self, address: str, *osc_arguments: List[Any]) -> None:
        """
        TO-DO : implement haptic engine object and add function call here
        """
        #self.haptics_engine.X 
        print("Haptic info being transmitted")

    def _send_joystick_data(self, x_val: float, y_val: float):
        """
        Sends joystick data through OSC to VRChat.
        Vertical/Horizontal movement are mapped from -1 to 1.
        """
        self.client.send_message("/input/Vertical", y_val)
        self.client.send_message("/input/Horizontal", x_val)
        #TO-DO : Additional function for joystick button

    async def _start_osc_server(self, event_loop):
        """
        Starts the UDP async network socket and adds it into the async event_loop
        """
        self.server = AsyncIOOSCUDPServer((self.ip, self.port_in), self.dispatcher, event_loop)
        self.transport, self.protocol = await self.server.create_serve_endpoint()

    def _close_osc_server(self):
        """
        Closes the network socket when application shuts down
        """
        self.transport.close()
        print("OSC Listener has closed.")