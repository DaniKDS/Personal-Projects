from datetime import datetime


from Domain.card_client import CardClient


class CardClientValidationError(Exception):
    pass


class CardClientValidator:

    def card_client_validate(self, card_client: CardClient):
        try:
            datetime.strptime(card_client.data_nasterii,
                              '%d.%m.%Y')
            datetime.strptime(card_client.data_inregistrarii,
                              '%d.%m.%Y')

        except ValueError:
            raise ValueError("Formatul datei trebuie "
                             "sa fie: DD.MM.YYYY")
