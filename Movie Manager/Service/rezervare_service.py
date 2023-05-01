from typing import List

from Domain.rezervare import Rezervare
from Domain.rezervare_validator import \
    RezervareValidator
from Repository.exceptions import NoSuchIdError
from Repository.repository import Repository
from ViewModels.show_revervari_interval_ore \
    import RezervareViewModel


class RezervareService:

    def __init__(self,
                 rezervare_repository: Repository,
                 film_repository: Repository,
                 card_client_repository: Repository,
                 rezervare_valdidator: RezervareValidator
                 ):

        self.rezervare_repository = rezervare_repository
        self.film_repository = film_repository
        self.card_client_repository = card_client_repository
        self.rezervare_validator = rezervare_valdidator

    def add_rezervare(self,
                      id_entity,
                      id_film,
                      id_card_client,
                      data,
                      ora):

        """
        Metoda care adauga o rezervare in
        dictionarul de revervari.
        id_rezervare:id-ul rezervarii
        id_film:id-ul filmului
        id_card_client:id-ul clientului
        data:id-ul cartii
        ora:id-ul orei date
        """
        rezervare = Rezervare(id_entity, id_film,
                              id_card_client, data, ora)
        if self.film_repository.read(id_film) is None:
            raise NoSuchIdError(f'Nu exista filmul '
                                f'cu id-ul {id_film}')

        if self.film_repository.read(id_film).in_program == "0":
            raise NoSuchIdError(f'Nu exista filmul in program')

        film = self.film_repository.read(id_film)
        if film.in_program is False:
            raise Exception(f'Rezervare imposibila;'
                            f' filmul nu este in program')

        if (id_card_client) is not None:
            if self.card_client_repository.read(id_card_client) is None:
                raise NoSuchIdError(f'Nu exista cardul client cu id-ul '
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
        :return: numarul de puncte pe care
         le acumuleza clientul
        """
        film = self.film_repository.read(id_film)
        puncte_acumulate = 0
        puncte_acumulate = puncte_acumulate + 10 / 100 * film.pret_bilet
        return puncte_acumulate

    def update_rezervare(self,
                         id_entity,
                         id_film,
                         id_card_client,
                         data,
                         ora):
        """
        Metoda care modifica o rezervare in
        dictionarul de revervari.
        id_rezervare:id-ul rezervarii
        id_film:id-ul filmului
        id_card_client:id-ul clientului
        data:id-ul cartii
        ora:id-ul orei date
        """
        rezervare = Rezervare(id_entity, id_film,
                              id_card_client, data, ora)
        self.rezervare_validator.rezervare_validate(rezervare)
        self.rezervare_repository.update(rezervare)

    def delete_rezervare(self, id_entity: str):
        self.rezervare_repository.delete(id_entity)

    def get_all(self) -> List[Rezervare]:
        return self.rezervare_repository.read()

    def rezervari_interval_ore(self, ora_start, ora_final):
        '''
        Afisarea rezervarilor dintr-un interval de ore
        :param ora_start: intreg
        :param ora_final: intreg
        :return:
        '''

        rezervari = self.rezervare_repository.read()
        view_models = []
        for rezervare in rezervari:
            if ora_start <= rezervare.ora <= ora_final:
                film = self.film_repository. \
                    get_by_id(rezervare.id_film)
                card_client = self.card_client_repository. \
                    get_by_id(rezervare.id_card_client)
                view_models.append(
                    RezervareViewModel(film,
                                       card_client,
                                       rezervare.data,
                                       rezervare.ora
                                       ))
        return view_models

    def ordonare_filme_numar_rezervari(self):
        """
        :return:
        """
        nr_rezervare_film = {}
        rezultat = []

        for film in self.film_repository.read():
            nr_rezervare_film[film.id_entity] = 0
        for rezervare in self.rezervare_repository.read():
            nr_rezervare_film[rezervare.id_film] += 1
        for id_film in nr_rezervare_film:
            nrRezervari = nr_rezervare_film[id_film]
            rezultat.append({
                "film": self.film_repository.read(id_film),
                "nr_rezervari": nrRezervari
            })
        return sorted(rezultat,
                      key=lambda rezerare_film:
                      rezerare_film["nrRezervari"],
                      reverse=True)

    def rezervari_interval_sterge(self,
                                  data_start,
                                  data_final):
        """

        :param data_start:
        :param data_final:
        :return:
        """
        rezervari = self.rezervare_repository.read()
        for rezervare in rezervari:
            if data_start <= rezervare.data[0:2] \
                    <= data_final:
                self.rezervare_repository.\
                    delete(rezervare.id_entity)
