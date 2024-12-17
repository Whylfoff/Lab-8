#include <iostream>
#include <sstream>
#include <cstring>
const int MAXWORDS = 100; // Максимальное количество слов
const int MAXWORDLENGTH = 50; // Максимальная длина слова
bool isvowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}
void removevowels(char* word) {
    char result[MAXWORDLENGTH] = {0};
    int j = 0;
    for (int i = 0; word[i] != '0'; i++) {
        if (!isvowel(word[i])) {
            result[j++] = word[i];
        }
    }
    result[j] = '0';
    strcpy(word, result);
}
void duplicateconsonants(char* word) {
    char result[MAXWORDLENGTH] = {0};
    int j = 0;
    for (int i = 0; word[i] != '0'; i++) {
        result[j++] = word[i];
        if (!isvowel(word[i])) {
            result[j++] = word[i]; // дублируем согласную
        }
    }
    result[j] = '0';
    strcpy(word, result);
}

int countvowels(const char* word) {
    int count = 0;
    for (int i = 0; word[i] != '0'; i++) {
        if (isvowel(word[i])) {
            count++;
        }
    }
    return count;
}
bool hasduplicates(char words[][MAXWORDLENGTH], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                return true;
            }
        }
    }
    return false;
}
void sortwords(char words[][MAXWORDLENGTH], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                char temp[MAXWORDLENGTH];
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], temp);
            }
        }
    }
}
int main() {
    char input[500]; // Вводимая строка
    char words[MAXWORDS][MAXWORDLENGTH]; // Массив для хранения слов
    int wordCount = 0;
    std::cout << "Введите текст: ";
    std::cin.getline(input, sizeof(input));
    // Разбиваем строку на слова
    char* token = strtok(input, " ");
    while (token != nullptr && wordCount < MAXWORDS) {
        strcpy(words[wordCount++], token);
        token = strtok(nullptr, " ");
    }
    // проверяем наличие дубликатов
    bool duplicatesExist = hasduplicates(words, wordCount);
    // обрабатываем слова
    for (int i = 0; i < wordCount; i++) {
        if (duplicatesExist) {
            removevowels(words[i]);
        } else {
            if (countvowels(words[i]) <= 3) {
                duplicateconsonants(words[i]);
            }
        }
    }

    // сортируем слова
    sortwords(words, wordCount);
    // удаляем дубликаты при выводе
    std::cout << "Результат:\n";
    for (int i = 0; i < wordCount; i++) {
        if (i == 0 || strcmp(words[i], words[i - 1]) != 0) { 
            std::cout << words[i] << "\n";
        }
    }

    return 0;
}
