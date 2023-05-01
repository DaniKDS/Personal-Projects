from copy import deepcopy
from typing import Dict, Union, Optional, List

import jsonpickle
from Domain.card_client import CardClient


class CardClientRepository:

    def __init__(self, filename, cards):
        self.filename = filename
        self.cards = cards

    def __read_file(self):
        try:
            with open(self.filename, 'r') as f:
                return jsonpickle.loads(f.read())
        except Exception:
            return {}

    def __write_file(self, objects: Dict[str, CardClient]):
        with open(self.filename, 'w') as f:
            f.write(jsonpickle.dumps(objects))

    def create(self, card_client: CardClient) -> None:
        """
        Functie care va creea o lista de filme
        :param card_client:filmul curent
        :return:dictionarul format din card-uri
        """

        cards = self.__read_file()
        if self.read(card_client.id_card_client) is not None:
            raise KeyError(f'Exista deja un card client cu id-ul '
                           f'{card_client.id_card_client}.')
        if self.citeste_CNP(card_client.CNP) is not None:
            raise KeyError(f'Exista un client cu CNP-ul '
                           f'{card_client.CNP}')
        cards[card_client.id_card_client] = card_client
        self.__write_file(cards)

    def citeste_CNP(self, CNP):
        cards_client = self.__read_file()
        if CNP:
            for key, card in cards_client.items():
                if card.CNP == CNP:
                    return CNP
            return None

    def read(self, id_card_client=None) ->\
            Union[Optional[CardClient], List[CardClient]]:

        """
        Functie care va verifica daca un card
        :param id_card_client: id-ul votului
        :return:
            - cardul cu id=id_card_client sau None daca
             id_card_client nu e None
            - lista cu toate filmele daca id_card_client e None
        """

        cards = self.__read_file()
        if id_card_client:
            if id_card_client in cards:
                return cards[id_card_client]
            else:
                return None

        return list(cards.values())

    def update(self, card_client: CardClient) -> None:
        """
        Functie care va actualiza un card din cards
        :param card_client:cardul dat
        :return:cardul actualizat
        """

        cards = self.__read_file()
        if self.read(card_client.id_card_client) is None:
            msg = f'Nu exista un film cu id-ul ' \
                  f'{card_client.id_card_client} de actualizat.'
            raise KeyError(msg)

        cards[card_client.id_card_client] = card_client
        self.__write_file(cards)

    def delete(self, id_card_client: str) -> None:
        """
        Functie care va sterge un card din cards
        :param id_card_client:id-ul unui film
        :return:lista fara cardul cu id_card_client
        """
        films = self.__read_file()
        if self.read(id_card_client) is None:
            raise KeyError(
                f'Nu exista un card cu id-ul '
                f'{id_card_client} pe care sa-l stergem.')

        del films[id_card_client]
        self.__write_file(films)
