from typing import List, Any

class HapticsEngine:
    def __init__(self):
        self.values = None
        self.prev_values = None

    def _set_values(self, *osc_arguments: List[Any]):
        self.values = osc_arguments

    def _get_values(self):
        data_list = []
        for i in range(0, 30):
            data_list.append(4 * i)
        return data_list