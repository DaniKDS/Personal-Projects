from Domain.film import Film
from Repository.film_repository import FilmRepository
from utils import clear_file


def test_film_repository():
    filename = 'test_films_repository.json'
    clear_file(filename)
    film_repository = FilmRepository(filename)
    added = Film('1', 'Piratii', '1956', 44, 'antena1')
    film_repository.create(added)
    assert film_repository.read(added.id_film) == added
