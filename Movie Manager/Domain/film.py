from dataclasses import dataclass


@dataclass
class Film:

    id_film: str
    titlu: str
    an_aparitie: str
    pret_bilet: float
    in_program: bool
