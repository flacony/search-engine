# Project "search_engine"

The **search_engine** project is a simple search engine written in C++.

## Project Description

The program is designed to perform search in text documents based on configuration files and user queries. Depending on the command-line arguments passed, the program determines the sources of files and the location of the resulting file.

## Running the Program

### Without Arguments

If the program is run without arguments, it looks for a "config" folder in the directory of the executable, where `config.json` and `requests.json` files are expected to be found. Then the program creates and writes the search results to the `answers.json` file in the same directory.

```bash
./search_engine
```

### With One Argument

When specifying one argument, the program considers it as the path to the "config" directory, where `config.json` and `requests.json` files are expected. The `answers.json` file will be created in the specified directory.

```bash
./search_engine /path/to/config
```

### With Two Arguments

If two arguments are passed, the program considers them as the full paths to the `config.json` and `requests.json` files. The `answers.json` file will be created in the "config" folder in the current directory of the executable file.

```bash
./search_engine /path/to/config.json /path/to/requests.json
```

### With Three Arguments

When specifying three arguments, the program considers them as paths to the `config.json`, `requests.json`, and `answers.json` files respectively.

```bash
./search_engine /path/to/config.json /path/to/requests.json /path/to/answers.json
```


__If `config.json` or `requests.json` are not found at the specified paths, the program exits with an error!__


## File Formats

### config.json

`config.json` is a configuration file that defines search parameters and paths to documents.

__If `config.json` does not contain the "config" and "files" fields, the program exits with an error!__

Example file structure:

```json
{
    "config": {
        "name": "SearchEngine",
        "version": "0.1",
        "max_responses": 4
    },
    "files": [
        "path/to/file000.txt",
        "path/to/file001.txt",
        "path/to/file002.txt"
    ]
}
```


- "max_responses" - the maximum number of responses for each query.  
- "files" - contains paths to text documents to be searched.

These fields are filled in by the user before running the program.


### requests.json

`requests.json` is a file of queries containing user queries for search. Example file structure:

```json
{
    "requests": [
        "first request",
        "second request"
    ]
}
```
The "requests" field is filled in by the user before running the program.  

The templates of the files `config.json` and `requests.json` can be found in the folder ["config"](./config).

### answers.json

`answers.json` is a file with search results. Example file structure:

```json
{
    "answers": {
        "request001": {
            "relevance": [
                {
                    "doc_id": 2,
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

- "request001" - the sequential number of the query for which the response is generated.  
- "result" - an indicator of whether there are responses to the query. It takes the value "true" if at least one document was found.  
- "doc_id" - the sequential number of the document (starting from zero) from the presented list of "files" in the `config.json` file.  
- "rank" - the relative relevance of the document. 


## Requirements

- C++17 compiler or higher
- CMake version 3.5 or higher

## Dependencies

The project uses the following libraries, which are automatically installed during the build using CMake:

- [Google Test](https://github.com/google/googletest) - for unit testing
- [nlohmann/json](https://github.com/nlohmann/json) - for JSON handling

## License

The project is distributed under the [MIT license](LICENCE.txt).
