# hash-trash
Implementation of simple 8-bit hashing in different languages using the Gill function

## Usage 

First of all you must clone this project and then cd to the project folder.

### C

1. Cd to the "c" dir;
2. Configure the project using CMake:
```
cmake -B ./build -G <preferred generator>
```
3. Then run build command:
```
cmake --build ./build --config <Debug|Release>
```
4. You've done! The builded binary file(s) available in the build directory.

### Python

1. Cd to the "python" dir;
2. Then run:
```
python main.py
```

### Dart

#### Run

```
$ cd dart/hash_trash
$ dart run
```

#### Build

```
$ cd dart
$ dart compile exe bin/hash_trash.dart
$ bin/hash_trash.exe
```

## License

This project is licensed under the [MIT License](LICENSE).

## Contributors

* [andinoriel](https://github.com/Andinoriel) - C
* [HanGerrel](https://github.com/HanGerrel) - Python
* [IceArrow256](https://github.com/IceArrow256) - Dart
