from pythonosc.osc_server import AsyncIOOSCUDPServer
from pythonosc.dispatcher import Dispatcher
from pythonosc.udp_client import SimpleUDPClient
from typing import List, Any

import asyncio

import src.config
import test_vrc_sim
from src.osc_handler import VRCHATOSCBridge



async def main():
    loop = asyncio.get_running_loop()

    osc_bridge = VRCHATOSCBridge("127.0.0.1", 9000, 9001, 1)

    await osc_bridge._start_osc_server(loop)

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