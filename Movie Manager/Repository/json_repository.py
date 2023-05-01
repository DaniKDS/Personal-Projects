from copy import deepcopy

import jsonpickle
from typing import Dict, Union, Optional, List, Type

from Domain.entity import Entity
from Repository.exceptions import DuplicateIdError,\
    NoSuchIdError
from Repository.repository import Repository


class JsonRepository(Repository):
    def __init__(self, filename):
        self.filename = filename

    def __read_file(self):
        try:
            with open(self.filename, 'r') as f:
                return jsonpickle.loads(f.read())
        except Exception:
            return {}

    def __write_file(self, objects: Dict[str, Entity]):
        with open(self.filename, 'w') as f:
            f.write(jsonpickle.dumps(objects))

    def create(self, entity: Entity) -> None:
        """
        :param entity:
        :return:
        """

        entities = self.__read_file()
        if self.read(entity.id_entity) is not None:
            raise DuplicateIdError(f'Exista deja o'
                                   f' entitate cu id-ul'
                                   f' {entity.id_entity}.')

        entities[entity.id_entity] = entity
        self.__write_file(entities)

    def read(self, id_entity: object = None)\
            -> Type[Union[Optional[Entity], List[Entity]]]:
        """
        Functie care va afisa lista cu totate entitatile daca
        id_entity e None,entitatea cu id_entity daca
         id_entity diferit e none
        :param id_entity: id-ul filmului
        :return:
            - entitatea cu id=id_entity sau None daca
             id_entity nu e None
            - lista cu toate entitatile daca id_entity e None
        """

        entities = self.__read_file()
        if id_entity:
            if id_entity in entities:
                return entities[id_entity]
            else:
                return None

        return list(entities.values())

    def update(self, entity: Entity) -> None:
        """
        Functie care va face update pe o entitate
        :param entity:entitatea care se va modifica
        :return:cerinta data
        """

        entities = self.__read_file()
        if self.read(entity.id_entity) is None:
            msg = f'Nu exista o entitate cu id-ul ' \
                  f'{entity.id_entity} de actualizat.'
            raise NoSuchIdError(msg)

        entities[entity.id_entity] = entity
        self.__write_file(entities)

    def delete(self, id_entity: str) -> None:
        """
        Sterge o entitate cu id_entitate
        :param id_entity:entitatea care se va sterge.
        :return:
        """
        entities = self.__read_file()
        if self.read(id_entity) is None:
            raise NoSuchIdError(
                f'Nu exista o entitate cu id-ul '
                f'{id_entity} pe care sa o stergem.')

        del entities[id_entity]
        self.__write_file(entities)

    def get_by_id(self, id_entitate):
        """
        Copiaza id-ul unei entitati
        :param id_entitate: id-ul entitatii respective
        :return: il retine cu deepcopy
        """
        self.__read_file()
        if id_entitate in self.filename:
            return deepcopy(self.filename[id_entitate])
        return None
