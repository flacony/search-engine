# Проект "search_engine"

Проект **search_engine** представляет собой простой поисковый движок, написанный на C++.

## Описание проекта

Программа предназначена для выполнения поиска в текстовых документах на основе конфигурационных файлов и запросов пользователя. В зависимости от переданных аргументов командной строки, программа определяет источники файлов и расположение результирующего файла.

## Запуск программы

### Без аргументов

Если программа запускается без аргументов, она ищет в директории исполняемого файла папку "config", в которой должны находиться файлы `config.json` и `requests.json`. Затем программа создает и записывает результаты поиска в файл `answers.json` в той же директории.

```bash
./search_engine
```

### С одним аргументом

При указании одного аргумента программа считает его путем к директории "config", где ожидаются файлы `config.json` и `requests.json`. Файл `answers.json` будет создан в указанной директории.

```bash
./search_engine /path/to/config
```

### С двумя аргументами

Если переданы два аргумента, программа рассматривает их как полные пути к файлам `config.json` и `requests.json`. Файл 'answers.json' будет создан в папке "config" в текущей директории исполняемого файла.

```bash
./search_engine /path/to/config.json /path/to/requests.json
```

### С тремя аргументами

При указании трех аргументов программа считает их путями к файлам `config.json`, `requests.json` и `answers.json` соответственно.

```bash
./search_engine /path/to/config.json /path/to/requests.json /path/to/answers.json
```


__Если по указанным путям не найдены `config.json` или `requests.json`, программа завершается с ошибкой!__
## Формат файлов

### config.json

`config.json` - это конфигурационный файл, определяющий параметры поиска и пути к документам.

__Если `config.json` не будет содержать полей "config" и "files", программа завершится с ошибкой!__

Пример структуры файла:

```json
{
    "config": {
        "name": "SearchEngine",
        "version": "0.1",
        "max_responses": 5 
    },
    "files": [
        "path/to/text_file001.txt",
        "path/to/text_file002.txt"
    ]
}
```


- "max_responses" - максимальное количество ответов на каждый запрос.  
- "files" - содержит пути к текстовым документам, по которым будет проводиться поиск.

Эти поля заполняются пользователем перед запуском программы.


### requests.json

`requests.json` - файл запросов, содержащий запросы пользователя для поиска. Пример структуры файла:

```json
{
    "requests": [
        "first request",
        "second request"
    ]
}
```
Поле "requests" заполняется пользователем перед запуском программы.  

Шаблоны файлов `config.json` и `requests.json` можно найти в папке ["config"](./config).

### answers.json

`answers.json` - файл с результатами поиска. Пример структуры файла:

```json
{
    "answers": {
        "request001": {
            "relevance": [
                {
                    "doc_id": 7,
                    "rank": 1.0
                },
                {
                    "doc_id": 0,
                    "rank": 0.5
                }
            ],
            "result": "true"
        },
        "request002": {
            "result": "false"
        }
    }
}
```

- "request001" - порядковый номер запроса, по которому сформирован ответ.  
- "result" - индикатор наличия ответов на запрос. Принимает значение "true", если был найден хотя бы один документ.  
- "docid" - порядковый номер документа (начиная с нуля) из представленного списка "files" в файле `config.json`.  
- "rank" - относительная релевантность документа. 


## Требования

- Компилятор C++17 или выше
- Стандартная библиотека C++
- CMake версии 3.5 или выше

## Зависимости

Проект использует следующие библиотеки, которые устанавливаются автоматически при сборке с использованием CMake:

- [Google Test](https://github.com/google/googletest) - для модульного тестирования
- [nlohmann/json](https://github.com/nlohmann/json) - для работы с JSON

## Лицензия

Проект распространяется под [MIT лицензией](LICENSE.txt).
