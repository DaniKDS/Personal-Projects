from dataclasses import dataclass

from Domain.entity import Entity


@dataclass
class CardClient(Entity):
    nume: str
    prenume: str
    CNP: str
    data_nasterii: str
    data_inregistrarii: str
    puncte_acumulate: float
