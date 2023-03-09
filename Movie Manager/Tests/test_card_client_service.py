from Domain import card_client_validator
from Domain.card_client import CardClient
from Domain.card_client_validator import CardClientValidator
from Repository.card_client_repository import CardClientRepository
from Service.card_client_service import CardClientService
from utils import clear_file


def test_card_client_service():

    filename = 'test_card_client_service.json'
    card_client_repository = CardClientRepository(filename, [])
    card_client_validator = CardClientValidator()
    card_client_service = CardClientService(card_client_repository,
                                            card_client_validator)
    assert card_client_service.search("dani") != []
