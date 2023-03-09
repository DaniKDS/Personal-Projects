from dataclasses import dataclass


@dataclass
class Rezervare:
    id_rezervare: str
    id_film: str
    id_card_client: str
    data: str
    ora: str
