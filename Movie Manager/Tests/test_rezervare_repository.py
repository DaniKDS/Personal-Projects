from Domain.rezervare import Rezervare
from Repository.rezervare_repository import RezervareRepository
from utils import clear_file


def test_revervare_repository():
    filename = 'test_revervare_repository.json'
    clear_file(filename)
    rezervare_repository = RezervareRepository(filename)
    added = Rezervare('1', '1', '1', '11.03.2012', '14.50')
    rezervare_repository.create(added)
    assert rezervare_repository.read(added.id_film) == added
