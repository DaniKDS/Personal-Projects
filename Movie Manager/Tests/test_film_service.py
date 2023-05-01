from Domain import film_validator
from Domain.film import Film
from Domain.film_validator import FilmValidator
from Repository.json_repository import JsonRepository
from Service.film_service import FilmService
from utils import clear_file


def test_film_service():

    filename = 'test_film_service.json'
    film_validator = FilmValidator()
    clear_file(filename)
    film_repository = JsonRepository(filename)
    film_service = FilmService(film_repository, film_validator)
    added = Film('1', 't1', '1900', 10, False)
    film_validator.film_validate(added)
    film_service.add_film('1', 't1', '1900', 10, False)
    assert film_repository.read(added.id_entity) == added

    added2 = Film('2', 't2', '1900', 20, False)
    film_validator.film_validate(added2)
    film_service.add_film('2', 't2', '1900', 20, False)
    before_update = film_repository.read()
    film_service.update_film('2', 't3', '1900', 20, False)
    assert film_repository.read() != before_update
    film_service.delete_film(added2.id_entity)
    assert film_repository.read(added.id_entity) == added


test_film_service()
