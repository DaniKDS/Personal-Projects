from dataclasses import dataclass


@dataclass
class CardClient:

    id_card_client: str
    nume: str
    prenume: str
    CNP: str
    data_nasterii: str
    data_inregistrarii: str
    puncte_acumulate: float
