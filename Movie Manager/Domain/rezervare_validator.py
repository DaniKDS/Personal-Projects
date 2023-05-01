from datetime import datetime
from Domain.rezervare import Rezervare


class RezervareValidator:
    def rezervare_validate(self, rezervare: Rezervare):
        try:
            # print(rezervare.data)
            datetime.strptime(rezervare.data, '%d.%m.%Y')
        except ValueError:
            raise ValueError("Formatul datei trebuie sa fie: DD.MM.YYYY")
