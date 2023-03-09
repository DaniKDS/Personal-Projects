from Domain import film
from Domain.card_client_validator import CardClientValidator
from Domain.film import Film
from Domain.film_validator import FilmValidator
from Domain.rezervare_validator import RezervareValidator
from Repository.card_client_repository import CardClientRepository
from Repository.film_repository import FilmRepository
from Repository.rezervare_repository import RezervareRepository
from Service.card_client_service import CardClientService
from Service.film_service import FilmService
from Service.rezervare_service import RezervareService
from Tests.test_card_client_repository import test_card_client_repository
from Tests.test_card_client_service import test_card_client_service
from Tests.test_film_repository import test_film_repository
from Tests.test_film_service import test_film_service
from Tests.test_rezervare_repository import test_revervare_repository
from Tests.test_rezervare_service import test_rezervare_service
from UserInterface.console import Console


def main():

    film_repository = FilmRepository('films.json')
    film_validator = FilmValidator()
    film_service = FilmService(film_repository, film_validator)

    card_client_repository = CardClientRepository('cards.json', [])
    card_client_validator = CardClientValidator()
    card_client_service = CardClientService(card_client_repository,
                                            card_client_validator)

    rezervare_repository = RezervareRepository('rezervations.json')
    rezervare_validator = RezervareValidator()
    rezervare_service = RezervareService(rezervare_repository,
                                         film_repository,
                                         card_client_repository,
                                         rezervare_validator)

    console = Console(film_service, card_client_service, rezervare_service)
    console.run_console()


if __name__ == '__main__':
    test_film_repository()
    test_card_client_repository()
    test_revervare_repository()
    test_film_service()
    test_card_client_service()
    test_rezervare_service()
    main()
