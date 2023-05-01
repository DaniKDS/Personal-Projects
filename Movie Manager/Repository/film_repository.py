from typing import Dict, Union, Optional, List

import jsonpickle

from Domain.film import Film


class FilmRepository:

    def __init__(self, filename):
        self.filename = filename

    def __read_file(self):
        try:
            with open(self.filename, 'r') as f:
                return jsonpickle.loads(f.read())
        except Exception:
            return {}

    def __write_file(self, objects: Dict[str, Film]):
        with open(self.filename, 'w') as f:
            f.write(jsonpickle.dumps(objects))

    def create(self, film: Film) -> None:
        """
        Functie care va creea o lista de filme
        :param film:filmul curent
        :return:lista creata de filme
        """

        films = self.__read_file()
        if self.read(film.id_film) is not None:
            raise KeyError(f'Exista deja un film cu id-ul {film.id_film}.')

        films[film.id_film] = film
        self.__write_file(films)

    def read(self, id_film=None) -> Union[Optional[Film], List[Film]]:

        """
        Functie care va verifica daca un film e din films
        :param id_film: id-ul votului
        :return:
            - filmul cu id=id_film sau None daca id_film nu e None
            - lista cu toate filmele daca id_film e None
        """

        films = self.__read_file()
        if id_film:
            if id_film in films:
                return films[id_film]
            else:
                return None

        return list(films.values())

    def update(self, film: Film) -> None:
        """
        Functie care va actualiza un film din films
        :param film:filmul dat
        :return:dictionarul format din filme
        """

        films = self.__read_file()
        if self.read(film.id_film) is None:
            msg = f'Nu exista un film cu id-ul {film.id_film} de actualizat.'
            raise KeyError(msg)

        films[film.id_film] = film
        self.__write_file(films)

    def delete(self, id_film: str) -> None:
        """
        Functie care va sterge un film din films
        :param id_film:id-ul unui film
        :return:lista fara filmul cu i_film
        """
        films = self.__read_file()
        if self.read(id_film) is None:
            raise KeyError(
                f'Nu exista un film cu id-ul {id_film} '
                f'pe care sa-l stergem.')

        del films[id_film]
        self.__write_file(films)
