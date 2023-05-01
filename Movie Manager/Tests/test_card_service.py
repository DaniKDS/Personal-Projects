from Domain.card_client import Card_Client
from Repository.json_repository import JsonRepository
from Service.undo_redo_service import UndoRedoService
from Service.card_client_service import CardService
from UserInterface.utils import clear_file


def test_card_service():
    filename = 'test_s_cards.json'
    clear_file(filename)
    card_repository = JsonRepository(filename)
    undo_redo_serv = UndoRedoService()
    card_service = CardService(card_repository, undo_redo_serv)
    params = ('1', 'Johnson', 'Alex', '111', '12.10.01', '19.11.19', 0)
    card_service.add_card(*params)

    gasit = 0
    if card_repository.read('1') is not None:
        gasit = 1
    assert gasit == 1

    params_doi = ('2', 'Peter', 'Alex', '1345', '07.12.2002', '18.09.2018', 9)
    card_service.add_card(*params_doi)
    card_service.delete_card('1')
    gasit = 1
    if card_repository.read('1') is None:
        gasit = 0
    assert gasit == 0

    gasit = 0
    if card_repository.read('2') is not None:
        gasit = 1
    assert gasit == 1

    param = ('2', 'Peter', 'Ivan', '1345', '07.01.2002', '18.09.2018', 100)
    card_service.update_card(*param)
    card = card_repository.read('2')
    assert card.puncte_acumulate == 100
    assert card.prenume_client == 'Ivan'

    param_a = ('3', 'Pines', "Mabel", '1010', '30.08.2003', '19.05.2019', 50)
    card_service.add_card(*param_a)
    gasit = 0
    if card_repository.read('3') is not None:
        gasit = 1
    assert gasit == 1

    lst = card_service.ord_descres_pct()
    card_unu = lst[0]
    assert card_unu.puncte == 100
    assert card_unu.nume_client == 'Peter'

    card_doi = lst[1]
    assert card_doi.nume_client == 'Pines'
    assert card_doi.puncte == 50

    card_service.incrementare_card("01.01.2001", "12.12.2002", 50)
    card_prim = card_repository.read('2')
    card_sec = card_repository.read('3')
    assert card_prim.puncte_acumulate == 150
    assert card_sec.puncte_acumulate == 50
