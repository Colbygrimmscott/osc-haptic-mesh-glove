from pythonosc.osc_server import AsyncIOOSCUDPServer
from pythonosc.dispatcher import Dispatcher
from pythonosc.udp_client import SimpleUDPClient
from typing import List, Any

import asyncio

from src.config import *
import test_vrc_sim
from src.osc_handler import VRCHATOSCBridge
from src.haptics_engine import HapticsEngine
from src.network import GloveUDPSender



async def main():
    loop = asyncio.get_running_loop()

    haptics_engine = HapticsEngine()
    osc_bridge = VRCHATOSCBridge(DESKTOP_IP, VR_CHAT_PORT_IN, VR_CHAT_PORT_OUT, haptics_engine)
    glove_udp_sender = GloveUDPSender(GLOVE_IP, GLOVE_PORT, haptics_engine)

    await osc_bridge._start_osc_server(loop)
    await glove_udp_sender._start_udp_server(loop)
    

    print()

    while True:
        await asyncio.sleep(1)
        osc_bridge._send_joystick_data(0.5, 0.5)
        await asyncio.sleep(1)
        osc_bridge._send_joystick_data(-0.5, 0.5)
        await asyncio.sleep(1)
        osc_bridge._send_joystick_data(-0.5, -0.5)
        await asyncio.sleep(1)
        osc_bridge._send_joystick_data(0.5, -0.5)
        await asyncio.sleep(1)
        osc_bridge._send_joystick_data(0.0, 0.0)

    #test_vrc_sim.run_simulator()



if __name__ == "__main__":
    asyncio.run(main())