from typing import List

from Domain.card_client import CardClient
from Domain.card_client_validator import CardClientValidator
from Repository.card_client_repository import CardClientRepository


class CardClientService:

    def __init__(self,
                 card_client_repository: CardClientRepository,
                 card_client_validator: CardClientValidator):

        self.card_client_repository = card_client_repository
        self.card_client_validator = card_client_validator

    def add_card_client(self,
                        id_card_client,
                        nume,
                        prenume,
                        CNP,
                        data_nasterii,
                        data_intregistrarii,
                        puncte_acumulate):

        """
        Aceasta metoda adauga un card_client in dictionarul de card_client
        id_card_client: id-ul clientului
        nume: numele
        prenume: prenumlele
        CNP: CNP-ul
        data_nasterii: data nasterii
        data_intregistrarii: data inregistrarii
        puncte_acumulate: punctele stranse):
        """
        card_client = CardClient(id_card_client,
                                 nume,
                                 prenume,
                                 CNP,
                                 data_nasterii,
                                 data_intregistrarii,
                                 puncte_acumulate)

        self.card_client_validator.card_client_validate(card_client)
        self.card_client_repository.create(card_client)

    def search(self, text):
        result = []
        cards = self.card_client_repository.read()
        for card in cards:
            if (text in card.id_card_client) or \
                    (text in card.nume) or \
                    (text in card.prenume) or \
                    (text in card.CNP) or \
                    (text in card.data_nasterii) or \
                    (text in card.data_inregistrarii) or \
                    (text in card.puncte_acumulate):
                result.append(card)
        return result

    def update_card_client(self,
                           id_card_client,
                           nume,
                           prenume,
                           CNP,
                           data_nasterii,
                           data_intregistrarii,
                           puncte_acumulate):
        """
            Aceasta metoda adauga un card_client in dictionarul de card_client
            id_card_client: id-ul clientului
            nume: numele
            prenume: prenumlele
            CNP: CNP-ul
            data_nasterii: data nasterii
            data_intregistrarii: data inregistrarii
            puncte_acumulate: punctele stranse):
        """
        card_client = CardClient(id_card_client,
                                 nume,
                                 prenume,
                                 CNP,
                                 data_nasterii,
                                 data_intregistrarii,
                                 puncte_acumulate)
        if self.card_client_repository.read(CNP) is not None:
            raise KeyError(f'Nu avem un CNP cu CNP- ul  {CNP} de actualizat')
        self.card_client_validator.card_client_validate(card_client)
        self.card_client_repository.update(card_client)

    def delete_card_client(self, id_card_client: str):
        self.card_client_repository.delete(id_card_client)

    def get_all(self) -> List[CardClient]:
        return self.card_client_repository.read()
