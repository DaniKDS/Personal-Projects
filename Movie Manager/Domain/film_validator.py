from Domain.film import Film


class FilmValidator:

    def film_validate(self, film: Film):

        if film.pret_bilet < 0:
            raise ValueError('Pretul biletului trebuie'
                             f'sa fie unul strict pozitiv')
