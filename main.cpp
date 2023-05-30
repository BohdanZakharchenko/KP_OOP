#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <chrono>
#include <set>
#include <unordered_set>
#include <utility>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;


class Stadium {
private:
    string name;
    string type;
    int capacity;

public:
    Stadium(string n, string t, int c) {
        name = n;
        type = t;
        capacity = c;
    }

    string getName() const {
        return name;
    }

    void setName(const string& n) {
        name = n;
    }

    string getType() const {
        return type;
    }

    void setType(const string& t) {
        type = t;
    }

    int getCapacity() const {
        return capacity;
    }

    void setCapacity(int c) {
        capacity = c;
    }

    // Функція для зчитування даних про стадіони з файлу
    static vector<Stadium> readStadiumsFromFile(string filename) {
        vector<Stadium> stadiums;
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                string name = line.substr(0, line.find(" "));
                line = line.substr(line.find(" ") + 1);
                int capacity = stoi(line);
                string type = line.substr(line.find(" ") + 1);
                line = line.substr(line.find(" ") + 1);
                Stadium stadium(name, type, capacity);
                stadiums.push_back(stadium);
            }
            inputFile.close();
        }
        return stadiums;
    }

    // Функція для фільтрації стадіонів за типом покриття
    static vector<Stadium> filterStadiumsByType(vector<Stadium> stadiums, int type) {
        vector<Stadium> filteredStadiums;
        string searchedType;
        switch (type) {
        case 0: {
            cout << "Ви тосно бажаєте вийти з програми? " << endl
                << "Для підтвердження натисніть будь-яку клавішу на клавіатурі";
            cin.get();
            exit(0);
            break;
        }
        case 1: {
            searchedType = "Грунт";
            break;
        }
        case 2: {
            searchedType = "Трава";
            break;
        }
        case 3: {
            searchedType = "Плитка";
            break;
        }
        case 4: {
            for (int i = 0; i < stadiums.size(); i++) {
                if (stadiums[i].type == "Грунт" || stadiums[i].type == "Трава" || stadiums[i].type == "Плитка") {
                    filteredStadiums.push_back(stadiums[i]);
                }
            }
            return filteredStadiums;
        }
        }
        for (int i = 0; i < stadiums.size(); i++) {
            if (stadiums[i].type == searchedType) {
                filteredStadiums.push_back(stadiums[i]);
            }
        }
        return filteredStadiums;
    }

    // Функція для виводу даних про стадіони
    static void printStadiums(vector<Stadium> stadiums) {
        cout << "Кількість знайдених стадіонів: " << stadiums.size() << endl;
        for (int i = 0; i < stadiums.size(); i++) {
            cout << i + 1 << ". Споруда: " << stadiums[i].name << endl
                << " Тип покриття: " << stadiums[i].type << endl
                << " Місткість споруди: " << stadiums[i].capacity << endl
                << "----------------------------------------------------" << endl;
        }
        // Коментар після циклу for, який був помилково розміщений після рядку `}` закриваючої фігурної дужки циклу
    }
};


class Athlete {
public:
    string nameOfAthlete;
    vector<string> kindOfSport;
    string athleteCategory;
    vector<string> trainer;
    string trainerCategory;
    string building;
    string sportClub;
    string dividingLine;



    //Функція для зчитування даних про спортсменів
    static vector<Athlete> readAthletesFromFile(const string& filename) {
        vector<Athlete> athletes;
        ifstream input(filename);
        if (!input) {
            cout << "Error: Unable to open file." << endl;
            return athletes;
        }
        string line;
        while (getline(input, line)) {
            Athlete athlete;
            athlete.nameOfAthlete = line;
            getline(input, line);
            string sport;
            for (size_t i = 0; i < line.length(); i++) {
                if (line[i] == ',' || line[i] == ' ') {
                    if (!sport.empty()) {
                        athlete.kindOfSport.push_back(sport);
                        sport.clear();
                    }
                }
                else {
                    sport.push_back(line[i]);
                }
            }
            if (!sport.empty()) {
                athlete.kindOfSport.push_back(sport);
            }
            getline(input, athlete.athleteCategory);
            string trainers;
            string trainersString;
            getline(input, trainersString);
            for (size_t i = 0; i < trainersString.length(); i++) {
                if (trainersString[i] == ',') {
                    if (!trainers.empty()) {
                        athlete.trainer.push_back(trainers);
                        trainers.clear();
                    }
                }
                else {
                    trainers.push_back(trainersString[i]);
                }
            }
            if (!trainers.empty()) {
                athlete.trainer.push_back(trainers);
            }
            getline(input, athlete.trainerCategory);
            getline(input, athlete.building);
            getline(input, athlete.sportClub);
            getline(input, athlete.dividingLine);

            athletes.push_back(athlete);
        }
        input.close();

        return athletes;
    }

    //Функція для фільтрації даних про спортсменів за видом спорту та розрядом спортсмена
    static vector<Athlete> filterAthletesBySportAndDivision(vector<Athlete> athletes, int type) {
        vector<Athlete> filteredAthletes;
        string searchedSport;
        string searchedCategory;
        int typeCategory;
        switch (type) {
        case 0:
            cout << "Ви тосно бажаєте вийти з програми? " << endl
                << "Для підтвердження натисніть будь-яку клавішу на клавіатурі";
            cin.get();
            exit(0);
            break;
        case 1:
            searchedSport = "Теніс";
            cout << "===== ТЕНІС =====" << endl;
            cout << endl << "Оберіть розряд атлета:" << endl
                << "0 - Отримати список всіх спорстменів, які займаються цим видом спорту" << endl
                << "1 - аматори" << endl
                << "2 - Кандидат у майстри спорту" << endl
                << "3 - Майстер спорту" << endl;
            cin >> typeCategory;
            switch (typeCategory)
            {
            case 1:
                searchedCategory = "Аматор";
                break;
            case 2:
                searchedCategory = "Кандидат у майстри спорту";
                break;
            case 3:
                searchedCategory = "Майстер спорту";
                break;
            default:
                cout << "Помилка! Такого варіанту не існує" << endl;
                break;
            }
            break;
        case 2:
            searchedSport = "Плавання";
            cout << "===== ПЛАВАНННЯ =====" << endl;
            cout << endl << "Оберіть розряд атлета:" << endl
                << "0 - Отримати список всіх спорстменів, які займаються цим видом спорту" << endl
                << "1 - аматори" << endl
                << "2 - Кандидат у майстри спорту" << endl
                << "3 - Майстер спорту" << endl;
            cin >> typeCategory;
            switch (typeCategory)
            {
            case 1:
                searchedCategory = "Аматор";
                break;
            case 2:
                searchedCategory = "Кандидат у майстри спорту";
                break;
            case 3:
                searchedCategory = "Майстер спорту";
                break;
            default:
                cout << "Помилка! Такого варіанту не існує" << endl;
                break;
            }
            break;
        case 3:
            searchedSport = "Футбол";
            cout << "===== ФУТБОЛ =====" << endl;
            cout << endl << "Оберіть розряд атлета:" << endl
                << "0 - Отримати список всіх спорстменів, які займаються цим видом спорту" << endl
                << "1 - аматори" << endl
                << "2 - Кандидат у майстри спорту" << endl
                << "3 - Майстер спорту" << endl;
            cin >> typeCategory;
            switch (typeCategory)
            {
            case 1:
                searchedCategory = "Аматор";
                break;
            case 2:
                searchedCategory = "Кандидат у майстри спорту";
                break;
            case 3:
                searchedCategory = "Майстер спорту";
                break;
            default:
                cout << "Помилка! Такого варіанту не існує" << endl;
                break;
            }
            break;
        default:
            cout << "Invalid type parameter." << endl;
            exit(1);
        }

        for (const auto& athlete : athletes) {
            for (const auto& sport : athlete.kindOfSport) {
                if (sport == searchedSport && athlete.athleteCategory == searchedCategory) {
                    filteredAthletes.push_back(athlete);
                    break;
                }
            }

        }
        return filteredAthletes;
    }

    //Фукнкція для фільтрації спортсменів за тренерами та розрядами спортсменів
    static vector<Athlete> filteringAthletesByTrainers(vector<Athlete> athletes, int type) {
        vector<Athlete> filteredAthletes;
        string searchedSport;
        string searchedCategory;
        int typeCategory;
        switch (type) {
        case 0:
            cout << "Ви тосно бажаєте вийти з програми? " << endl
                << "Для підтвердження натисніть будь-яку клавішу на клавіатурі";
            cin.get();
            exit(0);
            break;
        case 1:
            searchedSport = "Волик Сергій Максимович";
            cout << "===== ВОЛИК СЕРГІЙ МАКСИМОВИЧ =====" << endl;
            cout << endl << "Оберіть розряд атлета:" << endl
                << "0 - Отримати список всіх спорстменів, які займаються у цього тренера" << endl
                << "1 - аматори" << endl
                << "2 - Кандидат у майстри спорту" << endl
                << "3 - Майстер спорту" << endl;
            cin >> typeCategory;
            switch (typeCategory)
            {
            case 0:
                for (const auto& athlete : athletes) {
                    for (const auto& trainers : athlete.trainer) {
                        if (trainers == searchedSport) {
                            filteredAthletes.push_back(athlete);
                            break;
                        }
                    }

                }
                return filteredAthletes;
                break;
            case 1:
                searchedCategory = "Аматор";
                break;
            case 2:
                searchedCategory = "Кандидат у майстри спорту";
                break;
            case 3:
                searchedCategory = "Майстер спорту";
                break;
            default:
                cout << "Помилка! Такого варіанту не існує" << endl;
                break;
            }
            break;
        case 2:
            searchedSport = "Кузьменко Олена Миколаївна";
            cout << "===== КУЗЬМЕНКО ОЛЕНА МИКОЛАЇВНА =====" << endl;
            cout << endl << "Оберіть розряд атлета:" << endl
                << "0 - Отримати список всіх спорстменів, які займаються у цього тренера" << endl
                << "1 - аматори" << endl
                << "2 - Кандидат у майстри спорту" << endl
                << "3 - Майстер спорту" << endl;
            cin >> typeCategory;
            switch (typeCategory)
            {
            case 0:
                for (const auto& athlete : athletes) {
                    for (const auto& trainers : athlete.trainer) {
                        if (trainers == searchedSport) {
                            filteredAthletes.push_back(athlete);
                            break;
                        }
                    }

                }
                return filteredAthletes;
                break;
            case 1:
                searchedCategory = "Аматор";
                break;
            case 2:
                searchedCategory = "Кандидат у майстри спорту";
                break;
            case 3:
                searchedCategory = "Майстер спорту";
                break;
            default:
                cout << "Помилка! Такого варіанту не існує" << endl;
                break;
            }
            break;
        case 3:
            searchedSport = "Синьков Олександр Олександрович";
            cout << "===== СИНЬКОВ ОЛЕКСАНДР ОЛЕКСАНДРОВИЧ =====" << endl;
            cout << endl << "Оберіть розряд атлета:" << endl
                << "0 - Отримати список всіх спорстменів, які займаються у цього тренера" << endl
                << "1 - аматори" << endl
                << "2 - Кандидат у майстри спорту" << endl
                << "3 - Майстер спорту" << endl;
            cin >> typeCategory;
            switch (typeCategory)
            {
            case 0:
                for (const auto& athlete : athletes) {
                    for (const auto& trainers : athlete.trainer) {
                        if (trainers == searchedSport) {
                            filteredAthletes.push_back(athlete);
                            break;
                        }
                    }

                }
                return filteredAthletes;
                break;
            case 1:
                searchedCategory = "Аматор";
                break;
            case 2:
                searchedCategory = "Кандидат у майстри спорту";
                break;
            case 3:
                searchedCategory = "Майстер спорту";
                break;
            default:
                cout << "Помилка! Такого варіанту не існує" << endl;
                break;
            }
            break;
        case 4:
            searchedSport = "Петренко Андрій Юрійович";
            cout << "===== ПЕРТРЕНКО АНДРІЙ ЮРІЙОВИЧ =====" << endl;
            cout << endl << "Оберіть розряд атлета:" << endl
                << "0 - Отримати список всіх спорстменів, які займаються у цього тренера" << endl
                << "1 - аматори" << endl
                << "2 - Кандидат у майстри спорту" << endl
                << "3 - Майстер спорту" << endl;
            cin >> typeCategory;
            switch (typeCategory)
            {
            case 0:
                for (const auto& athlete : athletes) {
                    for (const auto& trainers : athlete.trainer) {
                        if (trainers == searchedSport) {
                            filteredAthletes.push_back(athlete);
                            break;
                        }
                    }

                }
                return filteredAthletes;
                break;
            case 1:
                searchedCategory = "Аматор";
                break;
            case 2:
                searchedCategory = "Кандидат у майстри спорту";
                break;
            case 3:
                searchedCategory = "Майстер спорту";
                break;
            default:
                cout << "Помилка! Такого варіанту не існує" << endl;
                break;
            }
            break;
        default:
            cout << "Invalid type parameter." << endl;
            exit(1);
        }

        for (const auto& athlete : athletes) {
            for (const auto& trainers : athlete.trainer) {
                if (trainers == searchedSport && athlete.athleteCategory == searchedCategory) {
                    filteredAthletes.push_back(athlete);
                    break;
                }
            }

        }
        return filteredAthletes;

    }

    //Функція для фільтрації спортсменів які  займаютьс більш ніж одним видом спорту
    static vector<Athlete> filterAthletesWithMultipleSports(const vector<Athlete>& athletes) {
        vector<Athlete> filteredAthletes;
        string ChoiceOfSport1;
        string ChoiceOfSport2;
        int numChoiceOfSport1;
        int numChoiceOfSport2;
        cout << "1 - теніс;" << endl
            << "2 - плавання;" << endl
            << "3 - футбол;" << endl;
        cout << "Оберіть перший вид спорту: ";
        cin >> numChoiceOfSport1;
        cout << "Оберіть другий вид спорту: ";
        cin >> numChoiceOfSport2;
        switch (numChoiceOfSport1) {
        case 1:
            ChoiceOfSport1 = "Теніс";
            break;
        case 2:
            ChoiceOfSport1 = "Плавання";
            break;
        case 3:
            ChoiceOfSport1 = "Футбол";
            break;
        default:
            cout << "Помилка! Не правильне значення!" << endl;
            break;
        }
        switch (numChoiceOfSport2) {
        case 1:
            ChoiceOfSport2 = "Теніс";
            break;
        case 2:
            ChoiceOfSport2 = "Плавання";
            break;
        case 3:
            ChoiceOfSport2 = "Футбол";
            break;
        default:
            cout << "Помилка! Не правильне значення!" << endl;
            break;
        }
        for (const Athlete& athlete : athletes) {
            if (athlete.kindOfSport.size() > 1) {
                bool hasFirstSport = false;
                bool hasSecondSport = false;
                for (const auto& sport : athlete.kindOfSport) {
                    if (sport == ChoiceOfSport1) {
                        hasFirstSport = true;
                    }
                    else if (sport == ChoiceOfSport2) {
                        hasSecondSport = true;
                    }
                }
                if (hasFirstSport && hasSecondSport) {
                    filteredAthletes.push_back(athlete);
                }
            }
        }
        return filteredAthletes;
    }

    // Функія для фільтрації тренерів за спортсменом
    static vector<Athlete> filterAthletesByName(const vector<Athlete>& athletes) {
        vector<Athlete> filteredAthletes;
        string athleteName;
        int numAthleteName;
        int numcout = 1;
        for (const Athlete& athlete : athletes) {
            cout << numcout << " - " << athlete.nameOfAthlete << endl;
            numcout++;
        }
        cin >> numAthleteName;
        switch (numAthleteName)
        {
        case 1:
            athleteName = "Фіртин Роман Олексійович";
            break;
        case 2:
            athleteName = "Зорінська Тетяна Миколаївна";
            break;
        case 3:
            athleteName = "Коваленко Олексій Віталійович";
            break;
        case 4:
            athleteName = "Шевченко Марина Василівна";
            break;
        case 5:
            athleteName = "Литвиненко Тетяна Ігорівна";
            break;
        case 6:
            athleteName = "Григоренко Олександр Михайлович";
            break;
        case 7:
            athleteName = "Романенко Людмила Володимирівна";
            break;
        case 8:
            athleteName = "Кузьменко Василь Петрович";
            break;


        default:
            break;
        }
        for (const auto& athlete : athletes) {
            if (athlete.nameOfAthlete == athleteName) {
                filteredAthletes.push_back(athlete);
            }
        }

        return filteredAthletes;
    }

    //Функція для фільтрування тренерів за видом спорту
    static vector<Athlete> filterTrainersBySport(const vector<Athlete>& athletes, const string& sport) {
        vector<Athlete> trainers;

        for (const auto& athlete : athletes) {
            for (size_t i = 0; i < athlete.kindOfSport.size(); i++) {
                if (athlete.kindOfSport[i] == sport && i < athlete.trainer.size()) {
                    trainers.push_back(athlete);
                    break;
                }
            }
        }

        return trainers;
    }

    //Функція для виводу інформації про спортсменів
    static void printAthletes(const vector<Athlete>& athletes) {
        cout << "======================================================" << endl;
        for (const Athlete& athlete : athletes) {
            cout << "ПІБ атлета: " << athlete.nameOfAthlete << endl;
            cout << "Вил спорту: ";
            for (const string& sport : athlete.kindOfSport) {
                cout << sport << ", ";
            }
            cout << endl;
            cout << "Розряд атлета: " << athlete.athleteCategory << endl;
            cout << "Тренер: ";
            for (size_t i = 0; i < athlete.trainer.size(); i++) {
                cout << athlete.trainer[i];
                if (i != athlete.trainer.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
            cout << "Розряд тренера: " << athlete.trainerCategory << endl;
            cout << "Будівля: " << athlete.building << endl;
            cout << "Спортивний клуб: " << athlete.sportClub << endl;
            cout << athlete.dividingLine << endl;

        }
        
    }

    //Фунція для виводу списку тренерів зазаначеного спортсмена
    static void printAthletesTrainers(const vector<Athlete>& athletes) {
        if (athletes.empty()) {
            cout << "No athletes found." << endl;
            return;
        }

        for (const auto& athlete : athletes) {
            cout << "Тренери атлета " << athlete.nameOfAthlete << ":" << endl;
            for (const auto& trainer : athlete.trainer) {
                cout << "- " << trainer << endl;
            }
            cout << endl;
        }
    }

    //Функція для друку тренерів певного виду спорту
    static void printTrainers(const vector<Athlete>& trainers, const string& sport) {
        cout << "Тренери за видом спорту " << sport << ":" << endl;
        unordered_set<string> uniqueTrainers;

        for (const auto& athlete : trainers) {
            for (size_t i = 0; i < athlete.kindOfSport.size(); i++) {
                if (athlete.kindOfSport[i] == sport && i < athlete.trainer.size()) {
                    uniqueTrainers.emplace(athlete.trainer[i]);
                }
            }
        }

        for (const auto& trainer : uniqueTrainers) {
            cout << "- " << trainer << endl;
        }
    }
};


class Competition
{
public:
    string nameOfTheCompetition;
    string sport;
    string organizer;
    string date;
    string buildins;
    string firstPlace;
    string secondPlace;
    string thirdPlace;
    string dividingLine;


    //Функція для читання даних про спортивні змагання
   static vector<Competition> readCompetitionsFromFile(const std::string& filename) {
        vector<Competition> competitions;
        ifstream file(filename);

        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                Competition competition;
                competition.nameOfTheCompetition = line;
                getline(file, competition.sport);
                getline(file, competition.organizer);
                getline(file, competition.date);
                getline(file, competition.buildins);
                getline(file, competition.firstPlace);
                getline(file, competition.secondPlace);
                getline(file, competition.thirdPlace);
                getline(file, competition.dividingLine);

                competitions.push_back(competition);
            }

            file.close();
        }
        else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }

        return competitions;
    }


    //Функція для фільтрації учасників змагань за клубами
   static void filterAndPrintOfClubsAndCompetitors(const vector<Athlete>& athletes, const vector<Competition>& competitions) {
        map<string, int> clubWinnersCount;

        for (const auto& athlete : athletes) {
            const string& club = athlete.sportClub;
            const string& athleteName = athlete.nameOfAthlete;
            for (const auto& competition : competitions) {
                if (athleteName == competition.firstPlace || athleteName == competition.secondPlace || athleteName == competition.thirdPlace) {
                    clubWinnersCount[club]++;
                    break;
                }
            }
        }
        for (const auto& pair : clubWinnersCount) {
            cout << "Клуб: " << pair.first << endl
                << "Кількість учасників змагань: " << pair.second << endl
                << "-----------------------------------------------------------------" << endl;
        }
    }

    //Функція для фільтрації атлетів за не участю в змаганнях
   static vector<Athlete> filterAthletesParticipatingInCompetitions(const vector<Athlete>& athletesList, const vector<Competition>& competitions) {
        vector<Athlete> filteredAthletes;

        for (const auto& athlete : athletesList) {
            const string& athleteName = athlete.nameOfAthlete;
            bool isParticipating = false;

            for (const auto& competition : competitions) {
                if (athleteName == competition.firstPlace || athleteName == competition.secondPlace || athleteName == competition.thirdPlace) {
                    isParticipating = true;
                    break;
                }
            }

            if (!isParticipating) {
                filteredAthletes.push_back(athlete);
            }
        }

        return filteredAthletes;
    }

    //Функція для фільтрації змагань за датою проведення
   static vector<Competition> filterCompetitionsByDate(const vector<Competition>& competitions, int daysAgo) {
        vector<Competition> filteredCompetitions;

        auto currentTime = chrono::system_clock::now();
        auto targetTime = currentTime - chrono::hours(24 * daysAgo);
        for (const auto& competition : competitions) {
            int year, month, day;
            sscanf(competition.date.c_str(), "%d-%d-%d", &year, &month, &day);
            std::tm targetTimeStruct{};
            targetTimeStruct.tm_year = year - 1900;
            targetTimeStruct.tm_mon = month - 1;
            targetTimeStruct.tm_mday = day;
            auto targetTimePoint = chrono::system_clock::from_time_t(mktime(&targetTimeStruct));
            if (targetTimePoint >= targetTime) {
                filteredCompetitions.push_back(competition);
            }
        }

        return filteredCompetitions;
    }

    //Функція для фільтрації змагань за організаторами
   static vector<Competition> filterCompetitionsByOrganizer(const vector<Competition>& competitions) {
        vector<Competition> filteredCompetitionsByOrgainizer;
        string nameOrganizer;
        int numOrganizer;
        cout << "1 - Тенісна асоціація;" << endl
            << "2 - Футбольна асоціація;" << endl
            << "3 - Спортивний комітет;" << endl;
        cin >> numOrganizer;
        switch (numOrganizer)
        {
        case 1:
            nameOrganizer = "Тенісна асоціація";
            break;
        case 2:
            nameOrganizer = "Футбольна асоціація";
            break;
        case 3:
            nameOrganizer = "Спортивний комітет";
            break;
        default:
            break;
        }

        for (const auto& competition : competitions) {
            if (competition.organizer == nameOrganizer) {
                filteredCompetitionsByOrgainizer.push_back(competition);
            }
        }

        return filteredCompetitionsByOrgainizer;
    }

    //Функція для фільтрації призерів змагань за назвою змагання
   static vector<Competition> filterWinnersByCompetitions(const vector<Competition>& competitions) {
        vector<Competition> filteredCompetitions;
        int numNameOfTheCompetition;
        int numcout = 1;
        string valueNameOfTheCompetition;
        for (const auto& competition : competitions) {
            cout << numcout << " - " << competition.nameOfTheCompetition << endl;
            numcout++;
        }
        /* cout << "Оберіть змагання, щоб дізнатися його переможців:" << endl
             << "1 - Кубок тенісу;" << endl
             << "2 - Зоряний Кубок;" << endl
             << "3 - Кубок Дельфіна." << endl;*/
        cin >> numNameOfTheCompetition;
        switch (numNameOfTheCompetition)
        {
        case 1:
            valueNameOfTheCompetition = "Кубок тенісу";
            break;
        case 2:
            valueNameOfTheCompetition = "Зоряний Кубок";
            break;
        case 3:
            valueNameOfTheCompetition = "Кубок Дельфіна";
            break;
        default:
            break;
        }
        for (const auto& competition : competitions) {
            if (competition.nameOfTheCompetition == valueNameOfTheCompetition) {
                filteredCompetitions.push_back(competition);
            }
        }

        return filteredCompetitions;
    }

    //Функція для фільтрації змагань проведених в певній бідівлі вцілому або зазначеного виду спорту
   static vector<Competition> filterCompetitionsByBuilding(const vector<Competition>& competitions) {
        vector<Competition> filteredCompetitions;
        int numBuilding;
        int numSport;
        string nameBuilding;
        string nameSport;
        cout << "Оберіть будівлю :" << endl
            << "1 - Корт\"Прикарпаття\"; " << endl
            << "2 - Стадіон\"Славутич\";" << endl
            << "3 - Басейн\"Центральний\"." << endl;
        cin >> numBuilding;
        switch (numBuilding)
        {
        case 1:
            nameBuilding = "Корт\"Прикарпаття\"";
            break;
        case 2:
            nameBuilding = "Стадіон\"Славутич\"";
            break;
        case 3:
            nameBuilding = "Басейн\"Центральний\"";
            break;
        default:
            break;
        }
        cout << "\========= " << nameBuilding << " =========/" << endl
            << "Оберіть вид спорту з якого мали відбуватися змагання:" << endl
            << "0 - Отримати перелік всіх змагань в заданій будівлі;" << endl
            << "1 - Теніс;" << endl
            << "2 - Футбол;" << endl
            << "3 - Плавання." << endl;
        cin >> numSport;
        switch (numSport)
        {
        case 0:
            for (const auto& competition : competitions) {
                if (competition.buildins == nameBuilding) {
                    filteredCompetitions.push_back(competition);
                }
            }
            return filteredCompetitions;
            break;
        case 1:
            nameSport = "Теніс";
            break;
        case 2:
            nameSport = "Футбол";
            break;
        case 3:
            nameSport = "Плавання";
            break;
        default:
            cout << "Помилка! Ви ввели хибне значення!" << endl;
            break;
        }
        for (const auto& competition : competitions) {
            if (competition.buildins == nameBuilding && competition.sport == nameSport) {
                filteredCompetitions.push_back(competition);
            }
        }

        return filteredCompetitions;
    }

    //Фунція для отримання списку будівель та дат проведення змагань
   static void printUniqueBuildingsAndDates(const std::vector<Competition>& competitions) {
        std::set<std::string> uniqueBuildings;

        for (const auto& competition : competitions) {
            uniqueBuildings.insert(competition.buildins);
        }

        for (const auto& building : uniqueBuildings) {
            std::cout << "Змагання в будівлі: " << building << std::endl;
            for (const auto& competition : competitions) {
                if (competition.buildins == building) {
                    std::cout << "- Дата проведення: " << competition.date << std::endl;
                }
            }
            std::cout << std::endl;
        }
    }


    //Функція для фільтрації змагань за організаторами та кількістю проведених ними змагань
   static void countAndPrintOrganizers(const vector<Competition>& competitions) {
        map<string, int> organizerCounts;

        for (const auto& competition : competitions) {
            const string& organizer = competition.organizer;
            organizerCounts[organizer]++;
        }

        std::cout << "Організатори змагань та кількість змагань, які вони провели:" << std::endl;
        for (const auto& pair : organizerCounts) {
            const string& organizer = pair.first;
            int count = pair.second;
            std::cout << "- " << organizer << ": " << count << " змагань" << std::endl;
        }
    }


    //Функція для виводу даних про змагання
   static void printCompetitions(const vector<Competition>& competitions) {
        for (const auto& competition : competitions) {
            cout << "Назва змагання: " << competition.nameOfTheCompetition << endl;
            cout << "Вид спорту: " << competition.sport << endl;
            cout << "Організатор: " << competition.organizer << endl;
            cout << "Дата проведення: " << competition.date << endl;
            cout << "Місце проведення: " << competition.buildins << endl;
            cout << competition.dividingLine << endl;
        }
    }

    //Функція для друку списку переможців завданого змагання
   static void printCompetitionsWinners(const vector<Competition>& competitions) {
        for (const auto& competition : competitions) {
            cout << "\========= " << competition.nameOfTheCompetition << " =========/" << endl;
            cout << "ПРИЗЕРИ: " << endl;
            cout << "I місце: " << competition.firstPlace << endl;
            cout << "  II місце: " << competition.secondPlace << endl;
            cout << "      III місце: " << competition.thirdPlace << endl;
            cout << competition.dividingLine << endl;
        }
    }

    //Функція для виводу атлетів, які не приймали участь в змаганнях протягом зазначеного часу
   static void printAthletesNotParticipateInCompetitions(const vector<Athlete>& athletes) {
        cout << "======================================================" << endl;
        for (const Athlete& athlete : athletes) {
            cout << "- " << athlete.nameOfAthlete << endl;
            cout << athlete.dividingLine << endl;

        }
    }
};


int main() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Отримуємо поточні атрибути
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(handle, &bufferInfo);

    // Отримуємо поточний колір фону
    WORD attributes = bufferInfo.wAttributes;

    // Змінюємо атрибути тексту
    WORD newAttributes = (attributes & 0xFFF0) | BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    SetConsoleTextAttribute(handle, newAttributes);

    // Отримуємо розміри консолі
    COORD consoleSize = bufferInfo.dwSize;
    DWORD consoleCells = consoleSize.X * consoleSize.Y;

    // Заповнюємо всю консоль білим фоном
    DWORD charsWritten;
    FillConsoleOutputCharacter(handle, ' ', consoleCells, { 0, 0 }, &charsWritten);
    FillConsoleOutputAttribute(handle, newAttributes, consoleCells, { 0, 0 }, &charsWritten);



    SetConsoleOutputCP(1251);
    bool running = true;
    while (running) {
    int typeOfRequest;
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl
        << "0 - вийти з програми; " << endl
        << "1 - Отримати перелік спортивних споруд зазначеного типу в цілому або такі що задовольняють заданим характеристикам;" << endl
        << "2 - Отримати список спортсменів, що займаються зазначеним видом спорту в цілому або не нижче певного розряду." << endl
        << "3 - Отримати список спортсменів, що тренуються у якогось тренера в цілому або не нижче певного розряду." << endl
        << "4 - Отримати список спортсменів, що займаються більш ніж одним видом спорту із зазначенням цих видів спорту. " << endl
        << "5 - Отримати список тренерів зазначеного спортсмена." << endl
        << "6 - Отримати перелік змагань, проведених протягом заданого періоду часу в цілому або зазначеним організатором. " << endl
        << "7 - Отримати список призерів зазначеного змагання. " << endl
        << "8 - Отримати перелік змагань, проведених у зазначеній спортивній споруді в цілому або з певного виду спорту. " << endl
        << "9 - Отримати перелік спортивних клубів і число спортсменів цих клубів, що брали участь у спортивних змаганнях протягом заданого інтервалу часу. " << endl
        << "10 - Отримати список тренерів за певним видом спорту. " << endl
        << "11 - Отримати список спортсменів, які не брали участь в жодних змаганнях протягом певного періоду часу. " << endl
        << "12 - Отримати список організаторів змагань і число проведених ними змагань протягом певного періоду часу. " << endl
        << "13 - Отримати перелік спортивних споруд та дати проведення на них змагань протягом певного періоду часу." << endl;
    cin >> typeOfRequest;
    string filename;
    vector<Stadium> allStadiums;
    vector<Stadium> filteredStadiums;
    vector<Athlete> allAthletes;
    vector<Athlete> filteredAthletes;
    vector<Athlete> filteredTrainers;
    vector<Athlete> athletes;
    vector<Competition> filteredCompetitions;
    vector<Competition> filteredCompetitionsByOrgainizer;
    vector<Competition> competitions;
    int daysAgo;
    int type;
    int requestVariantNumber;
    int numSport;
    string nameSport;
    allStadiums = Stadium::readStadiumsFromFile("buildings.txt");
    allAthletes = Athlete::readAthletesFromFile("athletes.txt");
    competitions = Competition::readCompetitionsFromFile("competitions.txt");
    switch (typeOfRequest)
    {
    case 0:
        cout << "eror";
        break;

    case 1:
        cout << "Оберіть критерій пошуку стадіону за типом покриття:" << endl
            << "0 - вийти з програми;" << endl
            << "1 - вивести спортивні будівлі з покритям: Грунт;" << endl
            << "2 - вивести спортивні будівлі з покритям: Трава;" << endl
            << "3 - вивести спортивні будівлі з покритям: Плитка;" << endl
            << "4 - вивести  список всіх спортивних споруд" << endl;
        cin >> type;
        filteredStadiums = Stadium::filterStadiumsByType(allStadiums, type);
        cout << "Stadiums with " << type << " coating:" << endl;
        Stadium::printStadiums(filteredStadiums);
        break;
    case 2:
        cout << "Оберіть критерій пошуку спортсмена за видом спорту:" << endl
            << "0 - вийти з програми;" << endl
            << "1 - Отримати список спортсменів, що займаються тенісом;" << endl
            << "2 - Отримати список спортсменів, що займаються плаванням;" << endl
            << "3 - Отримати список спортсменів, що займаються футболом" << endl;
        cin >> type;

        filteredAthletes = Athlete::filterAthletesBySportAndDivision(allAthletes, type);
        Athlete::printAthletes(filteredAthletes);
        break;
        
      
    case 3:
        cout << "Оберіть тренера:" << endl
            << "1 - Волик Сергій Максимович;" << endl
            << "2 - Кузьменко Олена Миколаївна;" << endl
            << "3 - Синьков Олександр Олександрович;" << endl
            << "2 - Петренко Андрій Юрійович;" << endl;
        cin >> type;

        filteredAthletes = Athlete::filteringAthletesByTrainers(allAthletes, type);
        Athlete::printAthletes(filteredAthletes);
        break;
    case 4:
        filteredAthletes = Athlete::filterAthletesWithMultipleSports(allAthletes);
        Athlete::printAthletes(filteredAthletes);
        break;
    case 5:
        filteredAthletes = Athlete::filterAthletesByName(allAthletes);
        Athlete::printAthletesTrainers(filteredAthletes);
        break;
    case 6:
        cout<<"1 - Отримати список змагань, які відбулись на протязі зазначеного часу вцілому;" <<endl 
            <<"2 - Отримати список змагань, які відбулись на протязі зазначеного часу із зазначеням організаторів" << endl;
        cin >> requestVariantNumber;
            switch (requestVariantNumber)
            {
            case 1:
                Competition::printCompetitions(competitions);
                break;
            case 2:
                
                cout << "Скільки днів тому пройшло змагання? ";
                cin >> daysAgo;
                filteredCompetitions = Competition::filterCompetitionsByDate(competitions, daysAgo);
                filteredCompetitionsByOrgainizer = Competition::filterCompetitionsByOrganizer(filteredCompetitions);
                cout << "Змагання які відбулися протягом  " << daysAgo << " минувших днів:" << endl;
                Competition::printCompetitions(filteredCompetitionsByOrgainizer);
                break;
            default:
                break;
            }
            break;
    case 7:
        filteredCompetitions = Competition::filterWinnersByCompetitions(competitions);
        Competition::printCompetitionsWinners(filteredCompetitions);
        break;
    case 8:
        filteredCompetitions = Competition::filterCompetitionsByBuilding(competitions);
        Competition::printCompetitions(filteredCompetitions);
        break;
    case 9:
        cout << "Скільки днів тому пройшло змагання? ";
        cin >> daysAgo;
        filteredCompetitions = Competition::filterCompetitionsByDate(competitions, daysAgo);
        Competition::filterAndPrintOfClubsAndCompetitors(allAthletes, filteredCompetitions);
  
        break;
    case 10:
        cout << "1 - Отримати список тренерів, що тренують тенісу;" << endl
            << "2 - Отримати список тренерів, що займаються плаванню;" << endl
            << "3 - Отримати список тренерів, що займаються футболу" << endl;
        cin >> numSport;
        switch (numSport)
        {
        case 1:
            nameSport = "Теніс";
            break;
        case 2:
            nameSport = "Плавання";
            break;
        case 3:
            nameSport = "Футбол";
            break;
        default:
            break;
        }
        filteredTrainers = Athlete::filterTrainersBySport(allAthletes, nameSport);
        Athlete::printTrainers(filteredTrainers, nameSport);
        break;
    case 11:
        cout << "Скільки днів тому пройшло змагання? ";
        cin >> daysAgo;
        filteredCompetitions = Competition::filterCompetitionsByDate(competitions, daysAgo);
        filteredTrainers = Competition::filterAthletesParticipatingInCompetitions(allAthletes, filteredCompetitions);
        Competition::printAthletesNotParticipateInCompetitions(filteredTrainers);
        break;
    case 12:
       
        cout << "Скільки днів тому пройшло змагання? ";
        cin >> daysAgo;
        filteredCompetitions = Competition::filterCompetitionsByDate(competitions, daysAgo);
        Competition::countAndPrintOrganizers(filteredCompetitions);
        break;
    case 13:
        cout << "Скільки днів тому пройшло змагання? ";
        cin >> daysAgo;
        filteredCompetitions = Competition::filterCompetitionsByDate(competitions, daysAgo);
        Competition::printUniqueBuildingsAndDates(filteredCompetitions);
        break;
    }
    cout << "Бажаєте продовжити? (y/n): ";
    char choice;
    cin >> choice;
    if (choice != 'y' && choice != 'Y') {
        running = false;
    }
    }
    return 0;
}

    