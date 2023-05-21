### UBB-FMI
0. Tests and specifications for all iterations.
1. **Iteration 1**
   - All CRUD operations with at least one additional functionality. Validations included. Layered architecture with all elements described in the course. Data persistence using files.
   - No PEP 8 warnings.
2. **Iteration 2**
   - All functionalities except Undo+Redo.
   - Generic repository, custom exception classes.
   - Type hinting, ABC, protocol usage.
   - No PEP 8 warnings.
3. **Iteration 3**
   - Efficient implementation of Undo+Redo.
   - Refactoring of all possible functionalities using `map`, `filter`, `list comprehensions`, `reduce`, `filter`.
   - Refactoring of at least one method using recursion.
   - Refactoring of at least two methods using lambda.
   - Implementation and usage of a custom sorting function with the same interface as Python's `sorted` function.

In all problems, **full-text search** means that the user-entered string is searched in all fields of all mentioned entities. All entities in whose fields the string is found are returned. Entities of different types can be returned.

2. **Cinema**
    2.1. Film CRUD: id, title, release year, ticket price, currently running. The ticket price must be strictly positive.
    2.2. Client card CRUD: id, first name, last name, CNP, date of birth (`dd.mm.yyyy`), registration date (`d.mm.yyyy`), accumulated points. CNP must be unique.
    2.3. Reservation CRUD: id, film id, client card id (can be null), date and time. The client accumulates `10%` (integer part) of the film's price on the card. The total number of points on the card is printed. Reservation can only be made if the film is currently running.
    2.4. Search for films and clients. Full-text search.
    2.5. Display all reservations within a given time interval, regardless of the day./service_rezervare/facut
    2.6. Display films sorted in descending order by the number of reservations./service_rezervare/rezolvat
    2.7. Display client cards sorted in descending order by the number of points on the card./service_card_client/rezolvat
    2.8. Delete all reservations within a specific range of days./service_rezervare/
    2.9. Increase the points on all cards whose date of birth falls within a given interval by a given value./card_service

Please refer to the corresponding sections for detailed explanations of each iteration and problem.

## Installation

To run this project locally, follow these steps:

1. Clone the repository: `git clone https://github.com/your/repository.git`
2. Navigate to the project directory: `cd project-directory`
3. Install the dependencies: `npm install`
4. Build the project: `npm run build`
5. Start the application: `npm start`

Make sure you have [Node.js](https://nodejs.org) installed on your machine.

## Contributing

Contributions are welcome! If you would like to contribute to this project, please follow these steps:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/your-feature`
3. Make your changes and commit them: `git commit -m 'Add your feature'`
4. Push to the branch: `git push origin feature/your-feature`
5. Submit a pull request
