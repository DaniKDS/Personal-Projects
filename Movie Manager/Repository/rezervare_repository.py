from typing import Dict, Union, Optional, List

import jsonpickle

from Domain.rezervare import Rezervare


class RezervareRepository:

    def __init__(self, filename):
        self.filename = filename

    def __read_file(self):
        try:
            with open(self.filename, 'r') as f:
                return jsonpickle.loads(f.read())
        except Exception:
            return {}

    def __write_file(self, objects: Dict[str, Rezervare]):
        with open(self.filename, 'w') as f:
            f.write(jsonpickle.dumps(objects))

    def create(self, rezervare: Rezervare) -> None:
        """
        Functie care va creea o lista de rezervari
        :param rezervare:rezervarea curenta
        :return:dictionar de rezervari
        """

        rezervations = self.__read_file()
        if self.read(rezervare.id_rezervare) is not None:
            raise KeyError(f'Exista deja un film cu id-ul '
                           f'{rezervare.id_rezervare}.')

        rezervations[rezervare.id_film] = rezervare
        self.__write_file(rezervations)

    def read(self, id_rezervare=None) -> \
            Union[Optional[Rezervare], List[Rezervare]]:

        """
        Functie care va verifica daca o rezervare se afla in reservations
        :param id_rezervare: id-ul rezervarii
        :return:
        - rezervarea cu id=id_rezervare sau None daca id_rezervare nu e None
        - lista cu toate rezervarile daca id_rezervare e None
        """

        rezervations = self.__read_file()
        if id_rezervare:
            if id_rezervare in rezervations:
                return rezervations[id_rezervare]
            else:
                return None

        return list(rezervations.values())

    def update(self, rezervare: Rezervare) -> None:
        """
        Functie care va actualiza o rezervare din rezervari
        :param rezervare:rezervarea data
        :return:dictionarul format din rezervari
        """

        reservations = self.__read_file()
        if self.read(rezervare.id_rezervare) is None:
            msg = f'Nu exista o rezervare cu id-ul ' \
                  f'{rezervare.id_rezervare} de actualizat.'
            raise KeyError(msg)

        reservations[rezervare.id_rezervare] = rezervare
        self.__write_file(reservations)

    def delete(self, id_rezervare: str) -> None:
        """
        Functie care va sterge o rezervare din rezervations
        :param id_rezervare:id-ul unei rezervari
        :return:lista fara rezervarea id_rezervare
        """
        reservations = self.__read_file()
        if self.read(id_rezervare) is None:
            raise KeyError(
                f'Nu exista o rezervare cu id-ul '
                f'{id_rezervare} pe care sa o stergem.')

        del reservations[id_rezervare]
        self.__write_file(reservations)
