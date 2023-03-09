from Domain import film_validator
from Domain.film_validator import FilmValidator
from Repository.film_repository import FilmRepository
from Service.film_service import FilmService
from utils import clear_file


def test_film_service():

    filename = 'test_film_service.json'
    film_repository = FilmRepository(filename)
    film_validator = FilmValidator()
    film_service = FilmService(film_repository, film_validator)
    assert film_service.search("1999") != []
