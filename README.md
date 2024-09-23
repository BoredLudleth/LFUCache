# LFU кэш
### Дисклеймер
Всем привет!
Данный проект выполнен в учебных целях в рамках курса по C++. 

Целью данного проекта является написание LFU(least frequently used) и идеального кэша.

## Компиляция
```
cd LFUCache/
cmake -S ./ -B build/
cmake --build build
cd build/
```
Для запуска проекта требуется:

```
./lfu < path_to_test_file
./perfect < path_to_test_file
./cache_test
```

Опционально можно изменить формат вывода. В новом формате будет помимо попаданий, будет выведено время работы кэша.

```
./lfu DEBUG < path_to_test_file
./perfect DEBUG < path_to_test_file
```

## Ввод/вывод
На вход программа принимает m - размер кэша, n - количество страниц, передаваемых на вход и сами страницы.

На выходе мы получим количества попаданий и времена работы для обоих кэшей.