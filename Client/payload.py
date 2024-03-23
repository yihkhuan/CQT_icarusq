from dataclasses import dataclass
from typing import Optional, List

@dataclass
class Payload:
    name: str
    type: str #GET/POST,
    endpoint: str
    parameters: Optional[List[str]]
