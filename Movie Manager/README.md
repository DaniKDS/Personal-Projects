
### Mate-info
0. Teste și specificații la toate iterațiile.
1. **Iterația 1** 
   - Toate CRUD-urile, minim încă o funcționalitate diferită de CRUD. Cu validări, arhitectură stratificată cu toate elementele descrise la curs. Salvarea datelor în fișiere.  
   - Fără warning-uri PEP 8.
2. **Iterația 2**
   - Toate funcționalitățile în afară de Undo+Redo. 
   - Repository generic, clase proprii de excepții. 
   - Folosirea type hinting, ABC, protocol.
   - Fără warning-uri PEP 8.
3. **Iterația 3**
   - Implementat Undo+Redo eficient.
   - Refactorizat toate funcționalitățile posibile folosind `map`, `filter`, `list comprehensions`, `reduce`, `filter`.
   - Refactorizat minim o metodă folosind recursivitate.
   - Refactorizat minim două metode folosind lambda.
   - Implementat și folosit o funcție proprie de sortare care să aibă aceeași interfață cu funcția `sorted` din Python.

În toate problemele, **căutare full text** înseamnă că stringul introdus de utilizator se caută în toate câmpurile tuturor entităților menționate. Se returnează toate entitățile în ale căror câmpuri se găsește stringul. Se pot returna entități de tipuri diferite.

2. **Cinema**
    2.1. CRUD film: id, titlu, an apariție, preț bilet, în program. Prețul să fie strict pozitiv.  
    2.2. CRUD card client: id, nume, prenume, CNP, data nașterii (`dd.mm.yyyy`), data înregistrării (`d.mm.yyyy`), puncte acumulate. CNP-ul trebuie să fie unic.  
    2.3. CRUD rezervare: id, id_film, id_card_client (poate fi nul), data și ora. Clientul acumulează pe card `10%` (parte întreagă) din prețul filmului. Se tipărește numărul total de puncte de pe card. Rezervarea se poate face doar dacă filmul este încă în program.  
    2.4. Căutare filme și clienți. Căutare full text.
    2.5. Afișarea tuturor rezervărilor dintr-un interval de ore dat, indiferent de zi./service_rezervare/facut 
    2.6. Afișarea filmelor ordonate descrescător după numărul de rezervări./ service_rezervare /rezolvat
    2.7. Afișarea cardurilor client ordonate descrescător după numărul de puncte de pe card./service_card_client/rezolvat  
    2.8. Ștergerea tuturor rezervărilor dintr-un anumit interval de zile./service_rezervare / 
    2.9. Incrementarea cu o valoare dată a punctelor de pe toate cardurile a căror zi de naștere se află într-un interval dat./card_service   
