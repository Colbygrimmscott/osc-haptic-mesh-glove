from pythonosc.osc_server import AsyncIOOSCUDPServer
from pythonosc.dispatcher import Dispatcher
from pythonosc.udp_client import SimpleUDPClient
import asyncio
from typing import List, Any

class VRCHATOSCListener: 
    def __init__(self, ip: str, port: int, haptics_engine):
        """
        Initializes a VRChat OSC Listening server.

        ip: local IP (default is 127.0.0.1)
        port: port VRChat sends data out of (default is 9000)
        haptics_engine: reference to haptic feedback calculation engine object
        """
        self.ip = ip
        self.port = port
        self.haptics_engine = haptics_engine

        self.dispatcher = Dispatcher()
        self.transport = None
        self.protocol = None
        self.server = None

    def _initialize_routes(self) -> None:
        """
        Maps specific VRChat OSC parameters to functions
        """
        self.dispatcher.map("/avatar/parameters/haptics*", self._handle_haptics)

    def _handle_haptics(self, address: str, *osc_arguments: List[Any]) -> None:
        """
        TO-DO : implement haptic engine object and add function call here
        """
        #self.haptics_engine.X 
        print()

    async def _start_osc_server(self):
        """
        Starts the UDP async network socket and adds it into the async event_loop
        """
        self.server = AsyncIOOSCUDPServer((self.ip, self.port), self.dispatcher, asyncio.get_event_loop())
        self.transport, self.protocol = await self.server.create_serve_endpoint()

    def _close_osc_server(self):
        """
        Closes the network socket when application shuts down
        """
        self.transport.close()
        print("OSC Listener has closed.")