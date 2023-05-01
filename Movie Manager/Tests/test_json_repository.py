from Domain.film import Film
from Repository.json_repository import JsonRepository
from utils import clear_file


def test_json_repository():
    filename = 'test_films.json'
    clear_file(filename)
    film_repository = JsonRepository(filename)
    added = Film('1', 'Fast and Furious', '2010', 10, True)
    film_repository.create(added)
    assert film_repository.read(added.id_entity) == added


test_json_repository()
