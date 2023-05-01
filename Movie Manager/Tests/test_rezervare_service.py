from Domain.card_client import CardClient
from Domain.card_client_validator import CardClientValidator
from Domain.film import Film
from Domain.film_validator import FilmValidator
from Domain.rezervare import Rezervare
from Domain.rezervare_validator import RezervareValidator
from Repository.json_repository import JsonRepository
from Service.card_client_service import CardClientService
from Service.film_service import FilmService
from Service.rezervare_service import RezervareService
from utils import clear_file


def test_rezervare_service():
    filename = 'test_reservation_service.json'
    filename2 = 'test_card2.json'
    filename3 = 'test_film2.json'
    clear_file(filename)
    clear_file(filename2)
    clear_file(filename3)
    rezervare_repository = JsonRepository(filename)
    card_client_repository = JsonRepository(filename2)
    film_repository = JsonRepository(filename3)

    rezervare_validator = RezervareValidator()
    film_validator = FilmValidator()
    card_client_validator = CardClientValidator()

    film_service = FilmService(film_repository,
                               film_validator)
    film_validator = FilmValidator()
    added = Film('1', 'film1', '2001', 10, True)
    film_validator.film_validate(added)
    film_service.add_film('1', 'film1', '2001', 10, True)

    card_client_service = CardClientService(card_client_repository,
                                            card_client_validator)
    added = CardClient('1', 'nume1', 'pren1', '11102000',
                       '03.02.2001', '20.10.2001', 1000)
    card_client_validator.card_client_validate(added)
    card_client_service.add_card_client('1', 'nume1',
                                        'pren1', '11102000',
                                        '03.02.2001',
                                        '20.10.2001', 1000)

    rezervare_service = RezervareService(rezervare_repository,
                                         film_repository,
                                         card_client_repository,
                                         rezervare_validator)

    added = Rezervare('1', '1', '1', '12.12.2002', '12')
    rezervare_validator.rezervare_validate(added)
    card = card_client_repository.read('1')
    accumulated_points = rezervare_service.puncte_acumulate('1')
    if card is not None:
        card.puncte_acumulate += accumulated_points
        card_client_repository.update(card)
    rezervare_service.add_rezervare('1', '1', '1',
                                    '12.12.2002', '12')
    assert rezervare_repository.read(added.id_card_client) == added

    added2 = Rezervare('3', '1', '1', '12.12.1211', '12')
    rezervare_validator.rezervare_validate(added2)
    rezervare_service.add_rezervare('3', '1', '1',
                                    '12.12.1211', '12')
    before_update = rezervare_repository.read()
    rezervare_service.update_rezervare('3', '1', '1',
                                       '13.11.1234', '13:11')
    assert rezervare_repository.read() != before_update
    rezervare_service.delete_rezervare(added2.id_entity)
    assert rezervare_repository.read(added.id_entity) == added


test_rezervare_service()
