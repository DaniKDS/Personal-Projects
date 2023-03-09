import string
from typing import List

from Domain.film import Film
from Domain.film_validator import FilmValidator
from Repository.film_repository import FilmRepository
import random


class FilmService:

    def __init__(self,
                 film_repository: FilmRepository,
                 film_validator: FilmValidator):

        self.film_repository = film_repository
        self.film_validator = film_validator

    def add_film(self,
                 id_film,
                 titlu,
                 an_aparitie,
                 pret_bilet,
                 in_program):

        """
        Aceasta medoda adauga un film in dictonarul
        de filme care va fi stocat in film_repository
        id_film:id-ul filmului
        titlu:titlul
        an_aparitie:anul de aparitie
        pret_bilet:pretul de bilet
        in_program:programul dat
        """
        film = Film(id_film, titlu, an_aparitie, pret_bilet, in_program)
        self.film_validator.film_validate(film)
        self.film_repository.create(film)

    def search(self, text):
        result = []
        films = self.film_repository.read()
        for film in films:
            if (text in film.titlu) or \
                    (text in film.id_film) or \
                    (text in film.an_aparitie):
                result.append(film)
        return result

    def update_film(self,
                    id_film,
                    titlu,
                    an_aparitie,
                    pret_bilet,
                    in_program):
        """
        Aceasta medoda modifica un film in dictonarul de filme
        de filme care va fi stocat in film_repository
        id_film:id-ul filmului
        titlu:titlul
        an_aparitie:anul de aparitie
        pret_bilet:pretul de bilet
        in_program:programul dat
        """
        film = Film(id_film, titlu, an_aparitie, pret_bilet, in_program)
        self.film_validator.film_validate(film)
        self.film_repository.update(film)

    def delete_film(self, id_film: str):
        self.film_repository.delete(id_film)

    def get_all(self) -> List[Film]:
        return self.film_repository.read()

    def generate(self, n):
        for i in range(0, n):
            id = str(random.randint(200, 100000000) + i)
            titlu = ''.join(random.choices(string.ascii_lowercase,
                                           k=random.randint(5, 10)))
            an_aparitie = str(random.randint(1990, 2021))
            pret_bilet = random.randint(100, 9000)
            in_program = random.choice([True, False])
            film = Film(id, titlu, an_aparitie, pret_bilet, in_program)
            self.film_repository.create(film)
