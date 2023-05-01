from Domain.card_client import CardClient
from Repository.card_client_repository import CardClientRepository
from utils import clear_file


def test_card_client_repository():
    filename = 'test_card_client_repository.json'
    clear_file(filename)
    card_client_repository = CardClientRepository(filename, [])
    added = CardClient('1', 'Aladin',
                       'Marcu', '4444424688585',
                       '12.04.2002', '12.04.2021', 344)
    card_client_repository.create(added)
    assert card_client_repository.read(added.id_card_client) == added
