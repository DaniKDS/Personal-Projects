from typing import List

from Domain.rezervare import Rezervare
from Domain.rezervare_validator import RezervareValidator
from Repository.card_client_repository import CardClientRepository
from Repository.film_repository import FilmRepository
from Repository.rezervare_repository import RezervareRepository


class RezervareService:

    def __init__(self,
                 rezervare_repository: RezervareRepository,
                 film_repository: FilmRepository,
                 card_client_repository: CardClientRepository,
                 rezervare_valdidator: RezervareValidator
                 ):

        self.rezervare_repository = rezervare_repository
        self.film_repository = film_repository
        self.card_client_repository = card_client_repository
        self.rezervare_validator = rezervare_valdidator

    def add_rezervare(self,
                      id_rezervare,
                      id_film,
                      id_card_client,
                      data,
                      ora):

        """
        Metoda care adauga o rezervare in dictionarul de revervari.
        id_rezervare:id-ul rezervarii
        id_film:id-ul filmului
        id_card_client:id-ul clientului
        data:id-ul cartii
        ora:id-ul orei date
        """
        rezervare = Rezervare(id_rezervare, id_film, id_card_client, data, ora)
        if self.film_repository.read(id_film) is None:
            raise KeyError(f'Nu exista filmul cu id-ul {id_film}')

        if self.film_repository.read(id_film).in_program == "0":
            raise KeyError(f'Nu exista filmul in program')

        film = self.film_repository.read(id_film)
        if film.in_program is False:
            raise Exception(f'Rezervare imposibila;'
                            f' filmul nu este in program')

        if (id_card_client) is not None:
            if self.card_client_repository.read(id_card_client) is None:
                raise KeyError(f'Nu exista cardul client cu id-ul '
                               f'{id_card_client}')

        card = self.card_client_repository.read(id_card_client)
        puncte_acumulate1 = self.puncte_acumulate(id_film)
        if card is not None:
            card.puncte_acumulate += puncte_acumulate1
            self.card_client_repository.update(card)

        self.rezervare_validator.rezervare_validate(rezervare)
        self.rezervare_repository.create(rezervare)

    def puncte_acumulate(self, id_film):
        """
        Afiseaza punctele acumulate
        :param id_film: id-ul filmului
        :return: numarul de puncte pe care le acumuleza clientul
        """
        film = self.film_repository.read(id_film)
        puncte_acumulate = 0
        puncte_acumulate = puncte_acumulate + 10 / 100 * film.pret_bilet
        return puncte_acumulate

    def update_rezervare(self,
                         id_rezervare,
                         id_film,
                         id_card_client,
                         data,
                         ora):
        """
        Metoda care modifica o rezervare in dictionarul de revervari.
        id_rezervare:id-ul rezervarii
        id_film:id-ul filmului
        id_card_client:id-ul clientului
        data:id-ul cartii
        ora:id-ul orei date
        """
        rezervare = Rezervare(id_rezervare, id_film, id_card_client, data, ora)
        self.rezervare_validator.rezervare_validate(rezervare)
        self.rezervare_repository.update(rezervare)

    def delete_rezervare(self, id_rezervare: str):
        self.rezervare_repository.delete(id_rezervare)

    def get_all(self) -> List[Rezervare]:
        return self.rezervare_repository.read()
