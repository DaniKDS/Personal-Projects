from Domain.card_client_validator import CardClientValidationError
from Domain.film_validator import FilmValidationError
from Domain.rezervare_validator import RezervareValidationError
from Repository.exceptions import DuplicateIdError, NoSuchIdError
from Service.card_client_service import CardClientService
from Service.film_service import FilmService
from Service.rezervare_service import RezervareService


class Console:
    def __init__(self,
                 film_service: FilmService,
                 card_client_service: CardClientService,
                 rezervare_service: RezervareService):

        self.film_service = film_service
        self.card_client_service = card_client_service
        self.rezervare_service = rezervare_service

    def show_menu(self):

        print('a[film|card|rezervare] - '
              'adaugare film sau card sau rezervare.')
        print('u[film|card|rezervare] - '
              'modificare film sau card sau rezervare.')
        print('d[film|card|rezervare] - '
              'stergere film sau card sau rezervare.')
        print('s[film|card|rezervare] - '
              'afisare film sau card sau rezervare.')
        print('src[film|card] - '
              'cautare full text film sau card.')

        print('4.  Căutare filme și clienți. Căutare '
              'full text.')
        print('5.  Afișarea tuturor rezervărilor dintr-un'
              ' interval de ore dat, indiferent de zi.')
        print('6.  Afișarea filmelor ordonate descrescător'
              ' după numărul de rezervări.')
        print('7.  Afișarea cardurilor client ordonate '
              'descrescător după numărul de puncte de pe card.')
        print('8.  Ștergerea tuturor rezervărilor '
              'dintr-un anumit interval de zile.')
        print('9.  Incrementarea cu o valoare dată a '
              'punctelor de pe toate cardurile a căror '
              'zi de naștere se află într-un interval dat.')

        print('x. Iesire')

    def run_console(self):
        while True:
            self.show_menu()
            opt = input('Alegeti optiunea: ')

            if opt == 'afilm':
                self.handle_add_film()
            elif opt == 'acard':
                self.handle_add_card()
            elif opt == 'arezervare':
                self.handle_add_rezervare()
            elif opt == 'ufilm':
                self.handle_update_film()
            elif opt == 'ucard':
                self.handle_update_card()
            elif opt == 'urezervare':
                self.handle_update_rezervare()
            elif opt == 'dfilm':
                self.handle_delete_film()
            elif opt == 'dcard':
                self.handle_delete_card()
            elif opt == 'drezervare':
                self.handle_delete_rezervare()
            elif opt == 'sfilm':
                msg = self.film_service.get_all()
                self.handle_show_all(msg)
            elif opt == 'scard':
                self.handle_show_all(
                    self.card_client_service.get_all())
            elif opt == 'srezervare':
                self.handle_show_all(
                    self.rezervare_service.get_all())
            elif opt == 'srcfilm':
                self.handle_search_film()
            elif opt == 'srccard':
                self.handle_search_card()
            elif opt == '4':
                self.handle_generare()
            elif opt == "5":
                self.handle_rezervari_interval_afisare()
            elif opt == "6":
                self.handle_ordonare_filme_numar_rezervari()
            elif opt == "7":
                self.handle_puncte_clienti_descrescator()
            elif opt == "8":
                self.handle_ui_tranzactii_interval_stergere()
            elif opt == "9":
                self.handle_incrementare_puncte_carduri()
            elif opt == 'x':
                break
            else:
                print('Comanda invalida, reincearca.')

    def handle_add_film(self):
        try:
            id_film = input('Dati id-ul filmului: ')
            titlu = input('Dati titlul: ')
            an_aparitie = input('Dati anul aparitiei: ')
            pret_bilet = float(input('Dati pretul '
                                     'biletului: '))
            in_program = input('Filmul este inca in'
                               ' program? : ')

            self.film_service.add_film(id_film,
                                       titlu,
                                       an_aparitie,
                                       pret_bilet,
                                       in_program)
        except FilmValidationError as ve:
            print('Eroare de validare:', ve)
        except DuplicateIdError as de:
            print('ID dublicat:', de)
        except Exception as ex:
            print('Eroare:', ex)

    def handle_show_all(self, objects):
        for obj in objects:
            print(obj)

    def handle_add_card(self):
        try:
            id_card_client = input('Dati id-ul'
                                   ' cardului clientului: ')
            nume = input('Dati numele: ')
            prenume = input('Dati prenumele: ')
            CNP = input('Dati CNP-ul: ')
            data_nasterii = input('Dati data nasterii: ')
            data_inregistrarii = input('Dati data '
                                       'inregistrarii: ')
            puncte_acumulate = float(input('Dati punctele '
                                           'acumulate: '))
            self.card_client_service.add_card_client(id_card_client,
                                                     nume,
                                                     prenume,
                                                     CNP,
                                                     data_nasterii,
                                                     data_inregistrarii,
                                                     puncte_acumulate)
        except CardClientValidationError as ve:
            print('Eroare de validare:', ve)
        except DuplicateIdError as de:
            print('ID dublicat:', de)
        except Exception as ex:
            print('Eroare:', ex)

    def handle_add_rezervare(self):

        try:
            id_rezervare = input('Dati id-ul rezervarii: ')
            id_film = input('Dati id-ul filmului: ')
            id_card_client = input('Dati id-ul cardului '
                                   'clientului: ')
            data = input('Dati data :')
            ora = input('Dati ora :')

            self.rezervare_service.add_rezervare(id_rezervare,
                                                 id_film,
                                                 id_card_client,
                                                 data,
                                                 ora)
        except RezervareValidationError as ve:
            print('Eroare de validare:', ve)
        except DuplicateIdError as de:
            print('ID dublicat:', de)
        except Exception as ex:
            print('Eroare:', ex)

    def handle_update_film(self):
        try:
            id_film = input('Dati id-ul filmului: ')
            titlu = input('Dati titlul: ')
            an_aparitie = input('Dati anul aparitiei: ')
            pret_bilet = input('Dati pretul biletului: ')
            in_program = input('Dati programul filmului: ')

            self.film_service.update_film(id_film,
                                          titlu,
                                          an_aparitie,
                                          pret_bilet,
                                          in_program)
        except FilmValidationError as ve:
            print('Eroare de validare:', ve)
        except NoSuchIdError as ke:
            print('Eroare de ID:', ke)
        except Exception as ex:
            print('Eroare:', ex)

    def handle_update_card(self):
        try:
            id_card_client = input('Dati id-ul cardului '
                                   'clientului: ')
            nume = input('Dati numele: ')
            prenume = input('Dati prenumele: ')
            CNP = input('Dati CNP-ul: ')
            data_nasterii = input('Dati data nasterii: ')
            data_inregistrarii = input('Dati data inregistrarii: ')
            puncte_acumulate = input('Dati punctele acumulate: ')

            self.card_client_service. \
                update_card_client(id_card_client,
                                   nume,
                                   prenume,
                                   CNP, data_nasterii,
                                   data_inregistrarii,
                                   puncte_acumulate)
        except CardClientValidationError as ve:
            print('Eroare de validare:', ve)
        except DuplicateIdError as de:
            print('ID dublicat:', de)
        except Exception as ex:
            print('Eroare:', ex)

    def handle_update_rezervare(self):
        try:
            id_rezervare = input('Dati id-ul '
                                 'rezervarii: ')
            id_film = input('Dati id-ul filmului: ')
            id_card_client = input('Dati id-ul'
                                   ' cardului clientului: ')
            data = input('Dati data :')
            ora = input('Dati ora :')

            self.rezervare_service. \
                update_rezervare(id_rezervare,
                                 id_film,
                                 id_card_client,
                                 data,
                                 ora)
        except RezervareValidationError as ve:
            print('Eroare de validare:', ve)
        except DuplicateIdError as de:
            print('ID dublicat:', de)
        except Exception as ex:
            print('Eroare:', ex)

    def handle_delete_film(self):
        try:
            id_film = input('Dati id-ul filmului '
                            'care se va sterge: ')
            self.film_service.delete_film(id_film)

        except FilmValidationError as ve:
            print('Eroare de validare:', ve)
        except NoSuchIdError as de:
            print('Eroare de ID:', de)
        except Exception as ex:
            print('Eroare:', ex)

    def handle_delete_card(self):
        try:
            id_card_client = input('Dati id-ul cardului'
                                   ' clientului care se'
                                   ' va sterge: ')
            self.card_client_service.\
                delete_card_client(id_card_client)
        except CardClientValidationError as ve:
            print('Eroare de validare:', ve)
        except NoSuchIdError as de:
            print('Eroare de ID:', de)
        except Exception as ex:
            print('Eroare:', ex)

    def handle_delete_rezervare(self):
        try:
            id_rezervare = input('Dati id-ul'
                                 ' rezervarii: ')

            self.rezervare_service.\
                delete_rezervare(id_rezervare)
        except RezervareValidationError as ve:
            print('Eroare de validare:', ve)
        except DuplicateIdError as de:
            print('ID dublicat:', de)
        except Exception as ex:
            print('Eroare:', ex)

    def handle_search_film(self):
        text = input("Dati textul care se cauta: ")
        self.handle_show_all(self.film_service.search(text))

    def handle_search_card(self):

        text = input("Dati textul care se cauta: ")
        self.handle_show_all(self.
                             card_client_service.search(text))

    def handle_generare(self):
        n = int(input("Dati numarul de filme :"))
        self.film_service.generate(n)

    def handle_rezervari_interval_afisare(self):
        ora_start = input("Dati ora de "
                          "incepere interval ore: ")
        ora_final = input("Dati ora de incheiere "
                          "interval ore: ")
        result_rezervari = self.rezervare_service.\
            rezervari_interval_ore(ora_start, ora_final)
        for rezervare in result_rezervari:
            print(rezervare)

    def handle_ordonare_filme_numar_rezervari(self):
        """
        Ordoneaza filmele dupa numarul
        de rezervari
        :return:filmele ordonate dupa
         numarul de rezervari
        """
        for film in self.rezervare_service.\
                ordonare_filme_numar_rezervari():
            print(film)

    def handle_puncte_clienti_descrescator(self):
        print(self.card_client_service.
              puncte_clienti_descrescator())

    def handle_ui_tranzactii_interval_stergere(self):
        start = input("Dati ziua de la care "
                      "incepe intervalul:")
        end = input("Dati ziua in care se "
                    "termina intervalul:")
        self.rezervare_service.\
            rezervari_interval_sterge(start, end)

    def handle_incrementare_puncte_carduri(self):
        print("Intervalul pentru care "
              "se va face incrementarea"
              "cu o valoare a punctelor: ")
        start = input("Data de start: ")
        end = input("Data de final: ")
        valoare = float(input("Dati valoarea pentru "
                              "incrementare: "))
        print(self.card_client_service.
              incrementare_puncte_carduri(start, end, valoare))
