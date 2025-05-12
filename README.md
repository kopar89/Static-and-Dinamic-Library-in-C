# Static-and-Dinamic-Library-in-C

___Задачи___

1) Написать функции, для умножения методом Штрассена и обычный алгоритм умножения.
2) Компиляция статической и динамической библиотеки.
3) Сборкка с помощью makefile.


После написания всех 3 файлов, нужно скомпилировать их. Пользовался следующими командами.


___Сборка статической библиотеки___


1) __gcc -c matrix_operations.c -o matrix_operations.o__

Где gcc-компилятор, -с означает компиляция, matrix_operations.c - сам файл, -o matrix_operations.o - на выходе получаю обьектный файл.

2) __ar crs libmatrix_operations.a ./matrix_operations.o__


Где
ar — утилита для создания архивов.

c — создать архив.

r — вставить файл в архив.

s — создать индекс символов (нужно для использования компоновщиком).

libmatrix_operations.a — имя статической библиотеки.

./matrix_operations.o — объектный файл, который мы добавляем в библиотеку.

Заключительный шаг 

3) __g++ ./main.c -L. -libmatrix.a -o matrix_main_static__

g++ — компилятор C++ (используется для C-файла, что не критично, но не обязательно).

./main.c — исходный файл.

-L. — указание компоновщику искать библиотеки в текущей директории.

-libmatrix.a — подключение библиотеки libmatrix.a.

-o matrix_main_static — имя итогового исполняемого файла.


Для запуска программы нужно ввести в терминал следующую команду.

4) __./matrix_main_static__


![](https://github.com/kopar89/block/blob/main/lib.png?raw=true)



___Сборка динамической библиотеки___

Компиляция обьектного файла.



1) __gcc -fPIC -c matrix_operations.c__

-fPIC — означает "Position Independent Code" (положение-независимый код), необходим для создания .so (shared object).

-c — только компиляция без линковки.

matrix_operations.c → matrix_operations.o.


Создание самой динамической библиотеки

2) __gcc -shared -o libmatrix_operations.so matrix_operations.o__


-shared — указывает компилятору создать динамическую библиотеку.

-o libmatrix_operations.so — выходной файл (shared object, .so).

На выходе получается libmatrix_operations.so.


Компиляция и связь с главным файлом. 


3) __gcc -L. -o main_dinamic main.c -lmatrix_operations__


-L. — ищет библиотеки в текущей директории.

-lmatrix_operations — означает libmatrix_operations.so (убираем lib и .so).

Результат: создаётся исполняемый файл main_dinamic.

Библиотека собрана! Но при запуске, столкнулся со следующей проблемой: error while loading shared libraries: libmatrix_operations.so: cannot open shared object file: No such file or directory.

Для решения ее нужно было добавить путь к библиотеке, чтобы ее найти

__export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/adminko/Рабочий\ стол__


После чего можно проверить работу библиотеки используя терминал.



![](https://github.com/kopar89/block/blob/main/dinamic_1.png?raw=true)


![](https://github.com/kopar89/block/blob/main/dinamic_2.png?raw=true)


