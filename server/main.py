from pythonosc.osc_server import AsyncIOOSCUDPServer
from pythonosc.dispatcher import Dispatcher
from pythonosc.udp_client import SimpleUDPClient
from typing import List, Any

import asyncio

from src.config import *
from src.osc_handler import VRCHATOSCBridge
from src.haptics_engine import HapticsEngine
from src.network import GloveUDPSender



async def main():
    loop = asyncio.get_running_loop()

    haptics_engine = HapticsEngine()
    osc_bridge = VRCHATOSCBridge(LOCAL_IP, VR_CHAT_PORT_IN, VR_CHAT_PORT_OUT, haptics_engine)
    glove_udp_sender = GloveUDPSender(GLOVE_IP, DESKTOP_IP, LOCAL_PORT, GLOVE_PORT, haptics_engine)

    await osc_bridge._start_osc_server(loop)
    glove_udp_task = asyncio.create_task(glove_udp_sender._start_udp_server(loop))
    

    print()

    try:
        while True:
            await asyncio.sleep(0.02)

            controller_input_data = glove_udp_sender.inputs

            vrchat_normalized_x = (controller_input_data["joy_x"] - 2048) / 2048.0
            vrchat_normalized_y = (controller_input_data["joy_y"] - 2048) / 2048.0

            osc_bridge._send_joystick_data(vrchat_normalized_x, vrchat_normalized_y, controller_input_data["joy_btn"])

    except KeyboardInterrupt:
        print("Shutting down server..")
    finally:
        glove_udp_task.cancel()
        await asyncio.gather(glove_udp_task, return_exceptions=True)

    #test_vrc_sim.run_simulator()



if __name__ == "__main__":
    asyncio.run(main())